/*********************************************************************
**  NAME:  SwDocView.h
**
**       SolidWorks generated file.
**
** CONTAINS:
**
**    COPYRIGHT 2014 (c) NCCS.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       SwDocView.h , 24.2
**    DATE AND TIME OF LAST  MODIFICATION
**       08/13/14 , 14:42:14
*********************************************************************/
// DocView.h : Declaration of the CDocView

#pragma once
#include "SwUnibase.h"
#include "SwUnibase_i.h"
#include "Swresource.h"       // main symbols
#include <comsvcs.h>
class CSwDocument;
#define ID_MODELVIEW_EVENTS 4


// CDocView

class ATL_NO_VTABLE CDocView :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDocView, &CLSID_DocView>,
	public IDispatchImpl<IDocView, &IID_IDocView, &LIBID_SwUnibaseLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispEventImpl<ID_MODELVIEW_EVENTS, CDocView, &__uuidof(DModelViewEvents), &LIBID_SldWorks, ID_SLDWORKS_TLB_MAJOR, ID_SLDWORKS_TLB_MINOR>
{
	typedef IDispEventImpl<ID_MODELVIEW_EVENTS, CDocView, &__uuidof(DModelViewEvents), &LIBID_SldWorks, ID_SLDWORKS_TLB_MAJOR, ID_SLDWORKS_TLB_MINOR> CModelViewEvents;

private:
	CComPtr<IModelView> modelView;
	CSwUnibase *userAddin;
	CSwDocument *parentDoc;

public:
	CDocView()
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DOCVIEW)

DECLARE_NOT_AGGREGATABLE(CDocView)

BEGIN_COM_MAP(CDocView)
	COM_INTERFACE_ENTRY(IDocView)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()




// IDocView
public:
	//Utility Methods
	void Init(CSwUnibase *theApp, IModelView *iModelView, CSwDocument *iParent);
	VARIANT_BOOL AttachEventHandlers();
	VARIANT_BOOL DetachEventHandlers();

	//Event Handlers
	STDMETHOD(OnDestroy)(long destroyType);
	STDMETHOD(OnRepaint)(long paintType);

	//Event Sinks
BEGIN_SINK_MAP(CDocView)
	SINK_ENTRY_EX(ID_MODELVIEW_EVENTS, __uuidof(DModelViewEvents), swViewDestroyNotify2, OnDestroy)
	SINK_ENTRY_EX(ID_MODELVIEW_EVENTS, __uuidof(DModelViewEvents), swViewRepaintNotify, OnRepaint)
END_SINK_MAP()
};

OBJECT_ENTRY_AUTO(__uuidof(DocView), CDocView)
