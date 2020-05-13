//==========================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: PEExportList.H
//==========================================

#ifndef __PEEXPORTLIST_H
#define __PEEXPORTLIST_H

typedef enum ExportedSymbolInfoFlags
{
    EXPSYMINFO_MATCH = 1
};

struct ExportedSymbolInfo
{
    char *      m_pszName;
    unsigned    m_flags;
};

const int PEExportListGrowSize = 100;

class PEExportList
{
    ExportedSymbolInfo *    m_pSymbols;
    unsigned                m_symbolCount;
    
    public:
    
    PEExportList( void );
    ~PEExportList( void );
    
    ExportedSymbolInfo * AddSymbol( char * pszSymbolName );
    ExportedSymbolInfo * LookupSymbol( char * pszSymbolName );
    ExportedSymbolInfo * GetNextSymbol( ExportedSymbolInfo * );
};

#endif
