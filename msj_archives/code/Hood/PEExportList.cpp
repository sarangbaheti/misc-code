//==========================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: ExportList.CPP
//==========================================
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include "PEExportList.h"

PEExportList::PEExportList( void )
{
    m_pSymbols = 0;
    m_symbolCount = 0;
}

PEExportList::~PEExportList( void )
{
    ExportedSymbolInfo * pCurrent = m_pSymbols;
    
    for ( unsigned i = 0; i < m_symbolCount; i++, pCurrent++ )
    {
        free( pCurrent->m_pszName );    
    }
}
    
ExportedSymbolInfo *
PEExportList::AddSymbol( char * pszSymbolName )
{
    if ( 0 == (m_symbolCount % PEExportListGrowSize) )
    {
        m_pSymbols = (ExportedSymbolInfo *)
            realloc(m_pSymbols,
                    (m_symbolCount + PEExportListGrowSize)
                    * sizeof(ExportedSymbolInfo) );
    }

    ExportedSymbolInfo * pCurrent = &m_pSymbols[m_symbolCount];

    pCurrent->m_pszName = strdup( pszSymbolName );
    pCurrent->m_flags = 0;
    
    m_symbolCount++;
    
    return pCurrent;        
}

ExportedSymbolInfo *
PEExportList::LookupSymbol( char * pszSymbolName )
{
    ExportedSymbolInfo * pSymbol = 0;
    
    while ( pSymbol = GetNextSymbol( pSymbol ) )
    {
        if ( 0 == strcmp(pSymbol->m_pszName, pszSymbolName) )
            break;
    }
    
    return pSymbol;
}

ExportedSymbolInfo *
PEExportList::GetNextSymbol( ExportedSymbolInfo * pSymbol )
{
    ExportedSymbolInfo * pEndSymbol = &m_pSymbols[m_symbolCount];

    if ( 0 == pSymbol && m_symbolCount )
    {
        return m_pSymbols;
    }
    else
    {
        pSymbol++;
        
        if ( pSymbol < pEndSymbol )
            return pSymbol;
        else
            return 0;
    }
}

