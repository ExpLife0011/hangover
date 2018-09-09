/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#ifndef QEMU_WINDOWSCODECS_H
#define QEMU_WINDOWSCODECS_H

enum windowscodecs_calls
{
    CALL_COMPONENTFACTORY_ADDREF = 0,
    CALL_COMPONENTFACTORY_CREATE_HOST,
    CALL_COMPONENTFACTORY_CREATEBITMAP,
    CALL_COMPONENTFACTORY_CREATEBITMAPCLIPPER,
    CALL_COMPONENTFACTORY_CREATEBITMAPFLIPROTATOR,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMHBITMAP,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMHICON,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMMEMORY,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMSOURCE,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMSOURCERECT,
    CALL_COMPONENTFACTORY_CREATEBITMAPSCALER,
    CALL_COMPONENTFACTORY_CREATECOLORCONTEXT,
    CALL_COMPONENTFACTORY_CREATECOLORTRANSFORMER,
    CALL_COMPONENTFACTORY_CREATECOMPONENTENUMERATOR,
    CALL_COMPONENTFACTORY_CREATECOMPONENTINFO,
    CALL_COMPONENTFACTORY_CREATEDECODER,
    CALL_COMPONENTFACTORY_CREATEDECODERFROMFILEHANDLE,
    CALL_COMPONENTFACTORY_CREATEDECODERFROMFILENAME,
    CALL_COMPONENTFACTORY_CREATEDECODERFROMSTREAM,
    CALL_COMPONENTFACTORY_CREATEENCODER,
    CALL_COMPONENTFACTORY_CREATEENCODERPROPERTYBAG,
    CALL_COMPONENTFACTORY_CREATEFASTMETADATAENCODERFROMDECODER,
    CALL_COMPONENTFACTORY_CREATEFASTMETADATAENCODERFROMFRAMEDECODE,
    CALL_COMPONENTFACTORY_CREATEFORMATCONVERTER,
    CALL_COMPONENTFACTORY_CREATEMETADATAREADER,
    CALL_COMPONENTFACTORY_CREATEMETADATAREADERFROMCONTAINER,
    CALL_COMPONENTFACTORY_CREATEMETADATAWRITER,
    CALL_COMPONENTFACTORY_CREATEMETADATAWRITERFROMREADER,
    CALL_COMPONENTFACTORY_CREATEPALETTE,
    CALL_COMPONENTFACTORY_CREATEQUERYREADERFROMBLOCKREADER,
    CALL_COMPONENTFACTORY_CREATEQUERYWRITER,
    CALL_COMPONENTFACTORY_CREATEQUERYWRITERFROMBLOCKWRITER,
    CALL_COMPONENTFACTORY_CREATEQUERYWRITERFROMREADER,
    CALL_COMPONENTFACTORY_CREATESTREAM,
    CALL_COMPONENTFACTORY_QUERYINTERFACE,
    CALL_COMPONENTFACTORY_RELEASE,
    CALL_IMILBITMAPIMPL_COPYPALETTE,
    CALL_IMILBITMAPIMPL_COPYPIXELS,
    CALL_IMILBITMAPIMPL_GETPIXELFORMAT,
    CALL_IMILBITMAPIMPL_GETRESOLUTION,
    CALL_IMILBITMAPIMPL_GETSIZE,
    CALL_IMILBITMAPIMPL_QUERYINTERFACE,
    CALL_IMILBITMAPIMPL_UNKNOWNMETHOD1,
    CALL_IMILUNKNOWN1IMPL_QUERYINTERFACE,
    CALL_IMILUNKNOWN2IMPL_QUERYINTERFACE,
    CALL_IMILUNKNOWN2IMPL_UNKNOWNMETHOD1,
    CALL_INIT_DLL,
    CALL_WICBITMAP_ADDREF,
    CALL_WICBITMAP_COPYPALETTE,
    CALL_WICBITMAP_COPYPIXELS,
    CALL_WICBITMAP_GETPIXELFORMAT,
    CALL_WICBITMAP_GETRESOLUTION,
    CALL_WICBITMAP_GETSIZE,
    CALL_WICBITMAP_LOCK,
    CALL_WICBITMAP_QUERYINTERFACE,
    CALL_WICBITMAP_RELEASE,
    CALL_WICBITMAP_SETPALETTE,
    CALL_WICBITMAP_SETRESOLUTION,
    CALL_WICBITMAPCLIPPER_ADDREF,
    CALL_WICBITMAPCLIPPER_COPYPALETTE,
    CALL_WICBITMAPCLIPPER_COPYPIXELS,
    CALL_WICBITMAPCLIPPER_GETPIXELFORMAT,
    CALL_WICBITMAPCLIPPER_GETRESOLUTION,
    CALL_WICBITMAPCLIPPER_GETSIZE,
    CALL_WICBITMAPCLIPPER_INITIALIZE,
    CALL_WICBITMAPCLIPPER_QUERYINTERFACE,
    CALL_WICBITMAPCLIPPER_RELEASE,
    CALL_WICBITMAPDECODER_ADDREF,
    CALL_WICBITMAPDECODER_COPYPALETTE,
    CALL_WICBITMAPDECODER_CREATE_HOST,
    CALL_WICBITMAPDECODER_GETCOLORCONTEXTS,
    CALL_WICBITMAPDECODER_GETCONTAINERFORMAT,
    CALL_WICBITMAPDECODER_GETDECODERINFO,
    CALL_WICBITMAPDECODER_GETFRAME,
    CALL_WICBITMAPDECODER_GETFRAMECOUNT,
    CALL_WICBITMAPDECODER_GETMETADATAQUERYREADER,
    CALL_WICBITMAPDECODER_GETPREVIEW,
    CALL_WICBITMAPDECODER_GETTHUMBNAIL,
    CALL_WICBITMAPDECODER_INITIALIZE,
    CALL_WICBITMAPDECODER_QUERYCAPABILITY,
    CALL_WICBITMAPDECODER_QUERYINTERFACE,
    CALL_WICBITMAPDECODER_RELEASE,
    CALL_WICBITMAPENCODER_ADDREF,
    CALL_WICBITMAPENCODER_COMMIT,
    CALL_WICBITMAPENCODER_CREATENEWFRAME,
    CALL_WICBITMAPENCODER_GETCONTAINERFORMAT,
    CALL_WICBITMAPENCODER_GETENCODERINFO,
    CALL_WICBITMAPENCODER_GETMETADATAQUERYWRITER,
    CALL_WICBITMAPENCODER_INITIALIZE,
    CALL_WICBITMAPENCODER_QUERYINTERFACE,
    CALL_WICBITMAPENCODER_RELEASE,
    CALL_WICBITMAPENCODER_SETCOLORCONTEXTS,
    CALL_WICBITMAPENCODER_SETPALETTE,
    CALL_WICBITMAPENCODER_SETPREVIEW,
    CALL_WICBITMAPENCODER_SETTHUMBNAIL,
    CALL_WICBITMAPFRAMEDECODE_ADDREF,
    CALL_WICBITMAPFRAMEDECODE_COPYPALETTE,
    CALL_WICBITMAPFRAMEDECODE_COPYPIXELS,
    CALL_WICBITMAPFRAMEDECODE_GETCOLORCONTEXTS,
    CALL_WICBITMAPFRAMEDECODE_GETMETADATAQUERYREADER,
    CALL_WICBITMAPFRAMEDECODE_GETPIXELFORMAT,
    CALL_WICBITMAPFRAMEDECODE_GETRESOLUTION,
    CALL_WICBITMAPFRAMEDECODE_GETSIZE,
    CALL_WICBITMAPFRAMEDECODE_GETTHUMBNAIL,
    CALL_WICBITMAPFRAMEDECODE_QUERYINTERFACE,
    CALL_WICBITMAPFRAMEDECODE_RELEASE,
    CALL_WICBITMAPFRAMEENCODE_ADDREF,
    CALL_WICBITMAPFRAMEENCODE_COMMIT,
    CALL_WICBITMAPFRAMEENCODE_GETMETADATAQUERYWRITER,
    CALL_WICBITMAPFRAMEENCODE_INITIALIZE,
    CALL_WICBITMAPFRAMEENCODE_QUERYINTERFACE,
    CALL_WICBITMAPFRAMEENCODE_RELEASE,
    CALL_WICBITMAPFRAMEENCODE_SETCOLORCONTEXTS,
    CALL_WICBITMAPFRAMEENCODE_SETPALETTE,
    CALL_WICBITMAPFRAMEENCODE_SETPIXELFORMAT,
    CALL_WICBITMAPFRAMEENCODE_SETRESOLUTION,
    CALL_WICBITMAPFRAMEENCODE_SETSIZE,
    CALL_WICBITMAPFRAMEENCODE_SETTHUMBNAIL,
    CALL_WICBITMAPFRAMEENCODE_WRITEPIXELS,
    CALL_WICBITMAPFRAMEENCODE_WRITESOURCE,
    CALL_WICBITMAPLOCK_ADDREF,
    CALL_WICBITMAPLOCK_GETDATAPOINTER,
    CALL_WICBITMAPLOCK_GETPIXELFORMAT,
    CALL_WICBITMAPLOCK_GETSIZE,
    CALL_WICBITMAPLOCK_GETSTRIDE,
    CALL_WICBITMAPLOCK_QUERYINTERFACE,
    CALL_WICBITMAPLOCK_RELEASE,
    CALL_WICCONVERTBITMAPSOURCE,
    CALL_WICCREATEBITMAPFROMSECTIONEX,
    CALL_WICMAPGUIDTOSHORTNAME,
    CALL_WICMAPSCHEMATONAME,
    CALL_WICMAPSHORTNAMETOGUID,
    CALL_WICPALETTE_ADDREF,
    CALL_WICPALETTE_GETCOLORCOUNT,
    CALL_WICPALETTE_GETCOLORS,
    CALL_WICPALETTE_GETTYPE,
    CALL_WICPALETTE_HASALPHA,
    CALL_WICPALETTE_INITIALIZECUSTOM,
    CALL_WICPALETTE_INITIALIZEFROMBITMAP,
    CALL_WICPALETTE_INITIALIZEFROMPALETTE,
    CALL_WICPALETTE_INITIALIZEPREDEFINED,
    CALL_WICPALETTE_ISBLACKWHITE,
    CALL_WICPALETTE_ISGRAYSCALE,
    CALL_WICPALETTE_QUERYINTERFACE,
    CALL_WICPALETTE_RELEASE,
};

DEFINE_GUID(IID_IMILBitmapSource,0x7543696a,0xbc8d,0x46b0,0x5f,0x81,0x8d,0x95,0x72,0x89,0x72,0xbe);
#define INTERFACE IMILBitmapSource
DECLARE_INTERFACE_(IMILBitmapSource,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID,void **) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IMILBitmapSource methods ***/
    STDMETHOD_(HRESULT,GetSize)(THIS_ UINT *,UINT *);
    STDMETHOD_(HRESULT,GetPixelFormat)(THIS_ int *);
    STDMETHOD_(HRESULT,GetResolution)(THIS_ double *,double *);
    STDMETHOD_(HRESULT,CopyPalette)(THIS_ IWICPalette *);
    STDMETHOD_(HRESULT,CopyPixels)(THIS_ const WICRect *,UINT,UINT,BYTE *);
    STDMETHOD_(HRESULT,UnknownMethod1)(THIS_ void **);
};
#undef INTERFACE

#define INTERFACE IMILUnknown1
DECLARE_INTERFACE_(IMILUnknown1,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID,void **) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
};
#undef INTERFACE

#define INTERFACE IMILUnknown2
DECLARE_INTERFACE_(IMILUnknown2,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID,void **) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** unknown methods ***/
    STDMETHOD_(HRESULT,UnknownMethod1)(THIS_ void *, void *) PURE;
};
#undef INTERFACE

/* WARNING: .NET Media Integration Layer (MIL) directly dereferences
 * BitmapImpl members and depends on its exact layout.
 *
 * TODO: I just copied the struct from Wine, most of the fields are
 * not used by the wrapper. They'll probably need syncing between
 * host and guest when methods are called. Note that they can only
 * be written by the guest as the host might have an incompatible
 * view on them. */
struct qemu_wic_bitmap
{
    /* Guest fields */
    IMILUnknown1 IMILUnknown1_iface;
    LONG ref;
    IMILBitmapSource IMILBitmapSource_iface;
    IWICBitmap IWICBitmap_iface;
    IMILUnknown2 IMILUnknown2_iface;
    IWICPalette *palette;
    int palette_set;
    LONG lock; /* 0 if not locked, -1 if locked for writing, count if locked for reading */
    BYTE *data;
    void *view; /* used if data is a section created by an application */
    UINT offset; /* offset into view */
    UINT width, height;
    UINT stride;
    UINT bpp;
    WICPixelFormatGUID pixelformat;
    double dpix, dpiy;
    CRITICAL_SECTION cs;

    /* Host fields */
    IMILUnknown1 *unk1_host;
    IMILBitmapSource *source_host;
    IWICBitmap *bitmap_host;
    IMILUnknown2 *unk2_host;
};

struct qemu_wic_frame_encode
{
    /* Guest fields */
    IWICBitmapFrameEncode IWICBitmapFrameEncode_iface;

    /* Host fields */
    IWICBitmapFrameEncode *host;
};

struct qemu_wic_encode
{
    /* Guest fields */
    IWICBitmapEncoder IWICBitmapEncoder_iface;
    IStream *stream;

    /* struct qemu_wic_frame_encode *frame; */

    /* Host fields */
    IWICBitmapEncoder *host;
    /* Put some stream wrapper vtable here */
};

struct qemu_wic_decoder
{
    /* Host fields */
    IWICBitmapDecoder IWICBitmapDecoder_iface;
    IWICBitmapFrameDecode IWICBitmapFrameDecode_iface;

    /* Guest fields */
    IWICBitmapDecoder *host_bitmap;
    IWICBitmapFrameDecode *host_frame;
};

struct qemu_wic_palette
{
    /* Guest fields */
    IWICPalette IWICPalette_iface;

    /* Host fields */
    IWICPalette *host;
};

struct qemu_wic_clipper
{
    /* Guest fields */
    IWICBitmapClipper IWICBitmapClipper_iface;

    /* Host fields */
    IWICBitmapClipper *host;
    struct qemu_wic_clipper *source_clipper;
    struct qemu_wic_bitmap *source_bitmap;
};

/* This is a reverse wrapper. */
struct qemu_bitmap_source
{
    /* Host fields. */
    IWICBitmapSource IWICBitmapSource_iface;
    uint64_t guest;
    LONG ref;
};

DEFINE_GUID(CLSID_WineTgaDecoder, 0xb11fc79a,0x67cc,0x43e6,0xa9,0xce,0xe3,0xd5,0x49,0x45,0xd3,0x04);
DEFINE_GUID(CLSID_WICIcnsEncoder, 0x312fb6f1,0xb767,0x409d,0x8a,0x6d,0x0f,0xc1,0x54,0xd4,0xf0,0x5c);
DEFINE_GUID(GUID_WineContainerFormatTga, 0x0c44fda1,0xa5c5,0x4298,0x96,0x85,0x47,0x3f,0xc1,0x7c,0xd3,0x22);
DEFINE_GUID(GUID_VendorWine, 0xddf46da1,0x7dc1,0x404e,0x98,0xf2,0xef,0xa4,0x8d,0xfc,0x95,0x0a);

#ifdef QEMU_DLL_GUEST

typedef HRESULT (*class_constructor)(const IID *, void **);
extern HRESULT Decoder_CreateInstance(const IID *iid, void **obj);
extern HRESULT Encoder_CreateInstance(const IID *iid, void **obj);
HRESULT ComponentFactory_CreateInstance(const IID *iid, void **obj);

IWICBitmap *WICBitmap_init_guest(struct qemu_wic_bitmap *bitmap);
void WICPalette_init_guest(struct qemu_wic_palette *palette);
void WICBitmapClipper_init_guest(struct qemu_wic_clipper *clipper);

struct qemu_wic_palette *unsafe_impl_from_IWICPalette(IWICPalette *iface);

/* For detection of our own IWICBitmapSource objects. */
const IWICBitmapClipperVtbl WICBitmapClipper_Vtbl;
const IWICBitmapVtbl WICBitmap_Vtbl;

static inline struct qemu_wic_bitmap *impl_from_IWICBitmap(IWICBitmap *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_bitmap, IWICBitmap_iface);
}

static inline struct qemu_wic_clipper *impl_from_IWICBitmapClipper(IWICBitmapClipper *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_clipper, IWICBitmapClipper_iface);
}

#else

extern const struct qemu_ops *qemu_ops;

void qemu_ComponentFactory_AddRef(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmap(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapClipper(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFlipRotator(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromHBITMAP(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromHICON(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromMemory(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromSource(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromSourceRect(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapScaler(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateColorContext(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateColorTransformer(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateComponentEnumerator(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateComponentInfo(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoder(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoderFromFileHandle(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoderFromFilename(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoderFromStream(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateEncoder(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateEncoderPropertyBag(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateFormatConverter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataReaderFromContainer(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataWriter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataWriterFromReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreatePalette(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryReaderFromBlockReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryWriter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryWriterFromBlockWriter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryWriterFromReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateStream(struct qemu_syscall *call);
void qemu_ComponentFactory_QueryInterface(struct qemu_syscall *call);
void qemu_ComponentFactory_Release(struct qemu_syscall *call);
void qemu_ComponentFactory_create_host(struct qemu_syscall *call);
void qemu_IMILBitmapImpl_CopyPalette(struct qemu_syscall *call);
void qemu_IMILBitmapImpl_CopyPixels(struct qemu_syscall *call);
void qemu_IMILBitmapImpl_GetPixelFormat(struct qemu_syscall *call);
void qemu_IMILBitmapImpl_GetResolution(struct qemu_syscall *call);
void qemu_IMILBitmapImpl_GetSize(struct qemu_syscall *call);
void qemu_IMILBitmapImpl_QueryInterface(struct qemu_syscall *call);
void qemu_IMILBitmapImpl_UnknownMethod1(struct qemu_syscall *call);
void qemu_IMILUnknown1Impl_QueryInterface(struct qemu_syscall *call);
void qemu_IMILUnknown2Impl_QueryInterface(struct qemu_syscall *call);
void qemu_IMILUnknown2Impl_UnknownMethod1(struct qemu_syscall *call);
void qemu_WICBitmapClipper_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapClipper_CopyPalette(struct qemu_syscall *call);
void qemu_WICBitmapClipper_CopyPixels(struct qemu_syscall *call);
void qemu_WICBitmapClipper_GetPixelFormat(struct qemu_syscall *call);
void qemu_WICBitmapClipper_GetResolution(struct qemu_syscall *call);
void qemu_WICBitmapClipper_GetSize(struct qemu_syscall *call);
void qemu_WICBitmapClipper_Initialize(struct qemu_syscall *call);
void qemu_WICBitmapClipper_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapClipper_Release(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_CopyPalette(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_create_host(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetContainerFormat(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetDecoderInfo(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetFrame(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetFrameCount(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetMetadataQueryReader(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetPreview(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_Initialize(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_QueryCapability(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_Release(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_Commit(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_CreateNewFrame(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_GetContainerFormat(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_GetEncoderInfo(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_GetMetadataQueryWriter(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_Initialize(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_Release(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetPalette(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetPreview(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_CopyPalette(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_CopyPixels(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetMetadataQueryReader(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetPixelFormat(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetResolution(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetSize(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_Release(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_Commit(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_GetMetadataQueryWriter(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_Initialize(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_Release(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetPalette(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetPixelFormat(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetResolution(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetSize(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_WritePixels(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_WriteSource(struct qemu_syscall *call);
void qemu_WICBitmapLock_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapLock_GetDataPointer(struct qemu_syscall *call);
void qemu_WICBitmapLock_GetPixelFormat(struct qemu_syscall *call);
void qemu_WICBitmapLock_GetSize(struct qemu_syscall *call);
void qemu_WICBitmapLock_GetStride(struct qemu_syscall *call);
void qemu_WICBitmapLock_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapLock_Release(struct qemu_syscall *call);
void qemu_WICBitmap_AddRef(struct qemu_syscall *call);
void qemu_WICBitmap_CopyPalette(struct qemu_syscall *call);
void qemu_WICBitmap_CopyPixels(struct qemu_syscall *call);
void qemu_WICBitmap_GetPixelFormat(struct qemu_syscall *call);
void qemu_WICBitmap_GetResolution(struct qemu_syscall *call);
void qemu_WICBitmap_GetSize(struct qemu_syscall *call);
void qemu_WICBitmap_Lock(struct qemu_syscall *call);
void qemu_WICBitmap_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmap_Release(struct qemu_syscall *call);
void qemu_WICBitmap_SetPalette(struct qemu_syscall *call);
void qemu_WICBitmap_SetResolution(struct qemu_syscall *call);
void qemu_WICConvertBitmapSource(struct qemu_syscall *call);
void qemu_WICCreateBitmapFromSectionEx(struct qemu_syscall *call);
void qemu_WICMapGuidToShortName(struct qemu_syscall *call);
void qemu_WICMapSchemaToName(struct qemu_syscall *call);
void qemu_WICMapShortNameToGuid(struct qemu_syscall *call);
void qemu_WICPalette_AddRef(struct qemu_syscall *call);
void qemu_WICPalette_GetColorCount(struct qemu_syscall *call);
void qemu_WICPalette_GetColors(struct qemu_syscall *call);
void qemu_WICPalette_GetType(struct qemu_syscall *call);
void qemu_WICPalette_HasAlpha(struct qemu_syscall *call);
void qemu_WICPalette_InitializeCustom(struct qemu_syscall *call);
void qemu_WICPalette_InitializeFromBitmap(struct qemu_syscall *call);
void qemu_WICPalette_InitializeFromPalette(struct qemu_syscall *call);
void qemu_WICPalette_InitializePredefined(struct qemu_syscall *call);
void qemu_WICPalette_IsBlackWhite(struct qemu_syscall *call);
void qemu_WICPalette_IsGrayscale(struct qemu_syscall *call);
void qemu_WICPalette_QueryInterface(struct qemu_syscall *call);
void qemu_WICPalette_Release(struct qemu_syscall *call);

struct qemu_wic_bitmap *WICBitmap_create_host(IWICBitmap *host);
struct qemu_wic_palette *WICPalette_create_host(IWICPalette *host);
struct qemu_wic_clipper *WICBitmapClipper_create_host(IWICBitmapClipper *host);

ULONG qemu_WICBitmap_Release_internal(struct qemu_wic_bitmap *bitmap);

struct qemu_bitmap_source *bitmap_source_wrapper_create(uint64_t guest);

#endif

#endif
