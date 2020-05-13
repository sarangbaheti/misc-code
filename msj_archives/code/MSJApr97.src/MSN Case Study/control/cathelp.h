//////////////////////////////////////////////////////////////////////////////
//
// cathelp.H
//
// Copyright 1996  Microsoft Corporation.  All Rights Reserved.
//
//
// parikr 6/21/96	v1.0
//
// component category helper functions header file
//
//////////////////////////////////////////////////////////////////////////////

#include "comcat.h"

// Helper function to create a component category and associated description
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);

// Helper function to register a CLSID as belonging to a component category
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);

// Helper function to unregister a CLSID as belonging to a component category
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
