/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <fci.h>
#include <fdi.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_fdi.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_cabinet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_cabinet);
#endif

struct qemu_FDICreate
{
    struct qemu_syscall super;
    uint64_t pfnalloc;
    uint64_t pfnfree;
    uint64_t pfnopen;
    uint64_t pfnread;
    uint64_t pfnwrite;
    uint64_t pfnclose;
    uint64_t pfnseek;
    uint64_t cpuType;
    uint64_t perf;
};

struct FDI_read_cb
{
    uint64_t func;
    uint64_t hf, pv, cb;
};

struct FDI_open_cb
{
    uint64_t func;
    uint64_t file, flag, mode;
};

struct FDI_close_cb
{
    uint64_t func;
    uint64_t hf;
};

struct FDI_seek_cb
{
    uint64_t func;
    uint64_t hf;
    uint64_t dist;
    uint64_t seektype;
};

#ifdef QEMU_DLL_GUEST

UINT __fastcall fdi_readwrite_guest(struct FDI_read_cb *call)
{
    PFNREAD fn = (PFNREAD)(ULONG_PTR)call->func;
    return fn(call->hf, (void *)(ULONG_PTR)call->pv, call->cb);
}

INT_PTR __fastcall fdi_open_guest(struct FDI_open_cb *call)
{
    PFNOPEN fn = (PFNOPEN)(ULONG_PTR)call->func;
    return fn((char *)(ULONG_PTR)call->file, call->flag, call->mode);
}

int __fastcall fdi_close_guest(struct FDI_close_cb *call)
{
    PFNCLOSE fn = (PFNCLOSE)(ULONG_PTR)call->func;
    return fn(call->hf);
}

LONG __fastcall fdi_seek_guest(struct FDI_seek_cb *call)
{
    PFNSEEK fn = (PFNSEEK)(ULONG_PTR)call->func;
    return fn(call->hf, call->dist, call->seektype);
}

WINBASEAPI HFDI CDECL FDICreate(PFNALLOC pfnalloc, PFNFREE pfnfree, PFNOPEN pfnopen, PFNREAD pfnread,
        PFNWRITE pfnwrite, PFNCLOSE pfnclose, PFNSEEK pfnseek, int cpuType, PERF perf)
{
    struct qemu_FDICreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDICREATE);
    call.pfnalloc = (ULONG_PTR)pfnalloc;
    call.pfnfree = (ULONG_PTR)pfnfree;
    call.pfnopen = (ULONG_PTR)pfnopen;
    call.pfnread = (ULONG_PTR)pfnread;
    call.pfnwrite = (ULONG_PTR)pfnwrite;
    call.pfnclose = (ULONG_PTR)pfnclose;
    call.pfnseek = (ULONG_PTR)pfnseek;
    call.cpuType = cpuType;
    call.perf = (ULONG_PTR)perf;

    qemu_syscall(&call.super);

    return (HFDI)(ULONG_PTR)call.super.iret;
}

#else

static INT_PTR CDECL host_open(char *pszFile, int oflag, int pmode)
{
    struct qemu_fxi *fdi = cabinet_tls;
    struct FDI_open_cb call;
    INT_PTR ret;

    call.func = fdi->open;
    call.file = QEMU_H2G(pszFile);
    call.flag = oflag;
    call.mode = pmode;

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fdi_open_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %p.\n", (void *)ret);

    return ret;
}

static UINT CDECL host_read(INT_PTR hf, void *pv, UINT cb)
{
    struct qemu_fxi *fdi = cabinet_tls;
    struct FDI_read_cb call;
    UINT ret;

    call.func = fdi->read;
    call.hf = hf;
    call.pv = QEMU_H2G(pv);
    call.cb = cb;

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fdi_readwrite_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static UINT CDECL host_write(INT_PTR hf, void *pv, UINT cb)
{
    struct qemu_fxi *fdi = cabinet_tls;
    struct FDI_read_cb call;
    UINT ret;

    call.func = fdi->write;
    call.hf = hf;
    call.pv = QEMU_H2G(pv);
    call.cb = cb;

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fdi_readwrite_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static int CDECL host_close(INT_PTR hf)
{
    struct qemu_fxi *fdi = cabinet_tls;
    struct FDI_close_cb call;
    int ret;

    call.func = fdi->close;
    call.hf = hf;

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fdi_close_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static LONG CDECL host_seek(INT_PTR hf, LONG dist, int seektype)
{
    struct qemu_fxi *fdi = cabinet_tls;
    struct FDI_seek_cb call;
    int ret;

    call.func = fdi->seek;
    call.hf = hf;
    call.dist = dist;
    call.seektype = seektype;

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fdi_seek_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

void qemu_FDICreate(struct qemu_syscall *call)
{
    struct qemu_FDICreate *c = (struct qemu_FDICreate *)call;
    struct qemu_fxi *fdi;
    struct qemu_fxi *old_tls = cabinet_tls;

    WINE_TRACE("\n");
    fdi = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*fdi));
    if (!fdi)
        WINE_ERR("Out of memory\n");

    fdi->alloc = c->pfnalloc;
    fdi->free = c->pfnfree;
    fdi->open = c->pfnopen;
    fdi->read = c->pfnread;
    fdi->write = c->pfnwrite;
    fdi->close = c->pfnclose;
    fdi->seek = c->pfnseek;

    cabinet_tls = fdi;

    fdi->host.fdi = FDICreate(c->pfnalloc ? host_alloc : NULL, c->pfnfree ? host_free : NULL,
            c->pfnopen ? host_open : NULL, c->pfnread ? host_read : NULL, c->pfnwrite ? host_write : NULL,
            c->pfnclose ? host_close : NULL, c->pfnseek ? host_seek : NULL, c->cpuType, QEMU_G2H(c->perf));

    cabinet_tls = old_tls;

    if (!fdi->host.fdi)
    {
        HeapFree(GetProcessHeap(), 0, fdi);
        fdi = NULL;
    }

    c->super.iret = QEMU_H2G(fdi);

}

#endif

struct qemu_FDIIsCabinet
{
    struct qemu_syscall super;
    uint64_t hfdi;
    uint64_t hf;
    uint64_t pfdici;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FDIIsCabinet(HFDI hfdi, INT_PTR hf, PFDICABINETINFO pfdici)
{
    struct qemu_FDIIsCabinet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDIISCABINET);
    call.hfdi = (ULONG_PTR)hfdi;
    call.hf = hf;
    call.pfdici = (ULONG_PTR)pfdici;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FDIIsCabinet(struct qemu_syscall *call)
{
    struct qemu_FDIIsCabinet *c = (struct qemu_FDIIsCabinet *)call;
    struct qemu_fxi *fdi;
    struct qemu_fxi *old_tls = cabinet_tls;

    /* FDICABINETINFO has the same size on 32 and 64 bit. */
    WINE_TRACE("\n");
    fdi = QEMU_G2H(c->hfdi);

    cabinet_tls = fdi;
    c->super.iret = FDIIsCabinet(fdi->host.fdi, c->hf, QEMU_G2H(c->pfdici));
    cabinet_tls = old_tls;
}

#endif

struct qemu_FDICopy
{
    struct qemu_syscall super;
    uint64_t hfdi;
    uint64_t pszCabinet;
    uint64_t pszCabPath;
    uint64_t flags;
    uint64_t pfnfdin;
    uint64_t pfnfdid;
    uint64_t pvUser;
};

struct FDI_progress_cb
{
    uint64_t func;
    uint64_t fdint, fdin;
};

#ifdef QEMU_DLL_GUEST

INT_PTR __fastcall fdi_progress_guest(struct FDI_progress_cb *call)
{
    PFNFDINOTIFY fn = (PFNFDINOTIFY)(ULONG_PTR)call->func;
    return fn(call->fdint, (FDINOTIFICATION *)(ULONG_PTR)call->fdin);
}

WINBASEAPI BOOL CDECL FDICopy(HFDI hfdi, char *pszCabinet, char *pszCabPath, int flags, PFNFDINOTIFY pfnfdin,
        PFNFDIDECRYPT pfnfdid, void *pvUser)
{
    struct qemu_FDICopy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDICOPY);
    call.hfdi = (ULONG_PTR)hfdi;
    call.pszCabinet = (ULONG_PTR)pszCabinet;
    call.pszCabPath = (ULONG_PTR)pszCabPath;
    call.flags = flags;
    call.pfnfdin = (ULONG_PTR)pfnfdin;
    call.pfnfdid = (ULONG_PTR)pfnfdid;
    call.pvUser = (ULONG_PTR)pvUser;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static INT_PTR CDECL host_progress(FDINOTIFICATIONTYPE fdint, FDINOTIFICATION *pfdin)
{
    struct qemu_fxi *fdi = cabinet_tls;
    struct FDI_progress_cb call;
    INT_PTR ret;
    struct qemu_FDINOTIFICATION fdin32;

    call.func = fdi->progress;
    call.fdint = fdint;
#if GUEST_BIT == HOST_BIT
    call.fdin = QEMU_H2G(pfdin);
#else
    FDINOTIFICATION_h2g(&fdin32, pfdin);
    call.fdin = QEMU_H2G(&fdin32);
#endif

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fdi_progress_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %p.\n", (void *)ret);

    return ret;
}

static int CDECL host_decrypt(FDIDECRYPT *did)
{
    WINE_FIXME("Unimplemented\n");
    return 0;
}

void qemu_FDICopy(struct qemu_syscall *call)
{
    struct qemu_FDICopy *c = (struct qemu_FDICopy *)call;
    struct qemu_fxi *fdi;
    struct qemu_fxi *old_tls = cabinet_tls;
    uint64_t old_progress;

    WINE_TRACE("\n");
    fdi = QEMU_G2H(c->hfdi);
    old_progress = fdi->progress;
    fdi->progress = c->pfnfdin;

    cabinet_tls = fdi;
    c->super.iret = FDICopy(fdi->host.fdi, QEMU_G2H(c->pszCabinet), QEMU_G2H(c->pszCabPath), c->flags,
            c->pfnfdin ? host_progress : NULL, c->pfnfdid ? host_decrypt : NULL, QEMU_G2H(c->pvUser));
    cabinet_tls = old_tls;

    fdi->progress = old_progress;
}

#endif

struct qemu_FDIDestroy
{
    struct qemu_syscall super;
    uint64_t hfdi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FDIDestroy(HFDI hfdi)
{
    struct qemu_FDIDestroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDIDESTROY);
    call.hfdi = (ULONG_PTR)hfdi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FDIDestroy(struct qemu_syscall *call)
{
    struct qemu_FDIDestroy *c = (struct qemu_FDIDestroy *)call;
    struct qemu_fxi *fdi;
    struct qemu_fxi *old_tls = cabinet_tls;

    WINE_TRACE("\n");
    fdi = QEMU_G2H(c->hfdi);

    cabinet_tls = fdi;
    c->super.iret = FDIDestroy(fdi->host.fdi);
    cabinet_tls = old_tls;

    if (c->super.iret)
        HeapFree(GetProcessHeap(), 0, fdi);
}

#endif

struct qemu_FDITruncateCabinet
{
    struct qemu_syscall super;
    uint64_t hfdi;
    uint64_t pszCabinetName;
    uint64_t iFolderToDelete;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FDITruncateCabinet(HFDI hfdi, char *pszCabinetName, USHORT iFolderToDelete)
{
    struct qemu_FDITruncateCabinet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDITRUNCATECABINET);
    call.hfdi = (ULONG_PTR)hfdi;
    call.pszCabinetName = (ULONG_PTR)pszCabinetName;
    call.iFolderToDelete = iFolderToDelete;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FDITruncateCabinet(struct qemu_syscall *call)
{
    struct qemu_FDITruncateCabinet *c = (struct qemu_FDITruncateCabinet *)call;
    struct qemu_fxi *fdi;
    struct qemu_fxi *old_tls = cabinet_tls;

    WINE_FIXME("Unverified!\n");
    fdi = QEMU_G2H(c->hfdi);

    cabinet_tls = fdi;
    c->super.iret = FDITruncateCabinet(fdi->host.fdi, QEMU_G2H(c->pszCabinetName), c->iFolderToDelete);
    cabinet_tls = old_tls;
}

#endif

