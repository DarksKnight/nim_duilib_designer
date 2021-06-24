// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFCLIENT_BROWSER_OSR_DRAGDROP_WIN_H_
#define CEF_TESTS_CEFCLIENT_BROWSER_OSR_DRAGDROP_WIN_H_
#pragma once

// When generating projects with CMake the CEF_USE_ATL value will be defined
// automatically if using a supported Visual Studio version. Pass -DUSE_ATL=OFF
// to the CMake command-line to disable use of ATL.
// Uncomment this line to manually enable ATL support.
// #define CEF_USE_ATL 1

#include <atlcomcli.h>
#include <objidl.h>
#include <stdio.h>

#include "osr_dragdrop_events.h"

namespace client {

#define DEFAULT_QUERY_INTERFACE(__Class) \
  HRESULT __stdcall QueryInterface(const IID& iid, void** object) { \
    *object = NULL; \
    if (IsEqualIID(iid, IID_IUnknown)) { \
      IUnknown* obj = this; \
      *object = obj; \
    } else if (IsEqualIID(iid, IID_ ## __Class)) { \
      __Class* obj = this; \
      *object = obj; \
    } else { \
      return E_NOINTERFACE; \
    } \
    AddRef(); \
    return S_OK; \
  }
#define IUNKNOWN_IMPLEMENTATION \
  ULONG __stdcall AddRef() { \
    return ++ref_count_; \
  } \
  ULONG __stdcall Release() { \
    if (--ref_count_ == 0) { \
      delete this; \
      return 0U; \
    } \
    return ref_count_; \
  } \
  protected: \
  ULONG ref_count_;


class DropTargetWin : public IDropTarget {
 public:
  CefBrowserHost::DragOperationsMask StartDragging(
	  OsrDragEvents *browser_handler,
      CefRefPtr<CefDragData> drag_data,
      CefRenderHandler::DragOperationsMask allowed_ops,
      int x, int y);

  // IDropTarget implementation:
  HRESULT __stdcall DragEnter(IDataObject* data_object,
                              DWORD key_state,
                              POINTL cursor_position,
                              DWORD* effect);

  HRESULT __stdcall DragOver(DWORD key_state,
                             POINTL cursor_position,
                             DWORD* effect);

  HRESULT __stdcall DragLeave();

  HRESULT __stdcall Drop(IDataObject* data_object,
                         DWORD key_state,
                         POINTL cursor_position,
                         DWORD* effect);

  // ��shared_ptr�����������ڣ�����ComPtr
  DEFAULT_QUERY_INTERFACE(IDropTarget)
  ULONG __stdcall AddRef() { return 1; }
  ULONG __stdcall Release() { return 1; }

 public:
  HWND GetHWND() { return hWnd_; };
  DropTargetWin(HWND hWnd)
      : hWnd_(hWnd) { }
  virtual ~DropTargetWin() { }

 private:
  HWND hWnd_ = NULL;

  CefRefPtr<CefDragData> current_drag_data_;
  OsrDragEvents *browser_handler_ = nullptr;
};
using DropTargetHandle = std::shared_ptr<client::DropTargetWin>;

class DropSourceWin : public IDropSource {
 public:
  static CComPtr<DropSourceWin> Create();

  // IDropSource implementation:
  HRESULT __stdcall GiveFeedback(DWORD dwEffect);

  HRESULT __stdcall QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState);

  DEFAULT_QUERY_INTERFACE(IDropSource)
  IUNKNOWN_IMPLEMENTATION

 protected:
  explicit DropSourceWin() : ref_count_(0) {}
  virtual ~DropSourceWin() {}
};

class DragEnumFormatEtc : public IEnumFORMATETC {
 public:
  static HRESULT CreateEnumFormatEtc(UINT cfmt,
                                     FORMATETC* afmt,
                                     IEnumFORMATETC** ppEnumFormatEtc);

  //
  // IEnumFormatEtc members
  //
  HRESULT __stdcall Next(ULONG celt,
                         FORMATETC * pFormatEtc,
                         ULONG * pceltFetched);
  HRESULT __stdcall Skip(ULONG celt);
  HRESULT __stdcall Reset(void);
  HRESULT __stdcall Clone(IEnumFORMATETC ** ppEnumFormatEtc);

  //
  // Construction / Destruction
  //
  DragEnumFormatEtc(FORMATETC *pFormatEtc, int nNumFormats);
  ~DragEnumFormatEtc();

  static void DeepCopyFormatEtc(FORMATETC *dest, FORMATETC *source);

  DEFAULT_QUERY_INTERFACE(IEnumFORMATETC)
  IUNKNOWN_IMPLEMENTATION

 private:
  ULONG m_nIndex;  // current enumerator index
  ULONG m_nNumFormats;  // number of FORMATETC members
  FORMATETC* m_pFormatEtc;  // array of FORMATETC objects
};

class DataObjectWin : public IDataObject {
 public:
  static CComPtr<DataObjectWin> Create(FORMATETC* fmtetc,
                                       STGMEDIUM* stgmed,
                                       int count);

  // IDataObject memberS
  HRESULT __stdcall GetDataHere(FORMATETC* pFormatEtc, STGMEDIUM *pmedium);
  HRESULT __stdcall QueryGetData(FORMATETC* pFormatEtc);
  HRESULT __stdcall GetCanonicalFormatEtc(FORMATETC* pFormatEct,
                                          FORMATETC* pFormatEtcOut);
  HRESULT __stdcall SetData(FORMATETC* pFormatEtc,
                            STGMEDIUM* pMedium,
                            BOOL fRelease);
  HRESULT __stdcall DAdvise(FORMATETC* pFormatEtc,
                            DWORD advf,
                            IAdviseSink*,
                            DWORD*);
  HRESULT __stdcall DUnadvise(DWORD dwConnection);
  HRESULT __stdcall EnumDAdvise(IEnumSTATDATA **ppEnumAdvise);

  HRESULT __stdcall EnumFormatEtc(DWORD dwDirection,
                                  IEnumFORMATETC **ppEnumFormatEtc);
  HRESULT __stdcall GetData(FORMATETC *pFormatEtc, STGMEDIUM *pMedium);

  DEFAULT_QUERY_INTERFACE(IDataObject)
  IUNKNOWN_IMPLEMENTATION

 protected:
  int m_nNumFormats;
  FORMATETC* m_pFormatEtc;
  STGMEDIUM* m_pStgMedium;

  static HGLOBAL DupGlobalMem(HGLOBAL hMem);

  int LookupFormatEtc(FORMATETC *pFormatEtc);

  explicit DataObjectWin(FORMATETC *fmtetc, STGMEDIUM *stgmed, int count);
};

}  // namespace client

#endif  // CEF_TESTS_CEFCLIENT_BROWSER_OSR_DRAGDROP_WIN_H_
