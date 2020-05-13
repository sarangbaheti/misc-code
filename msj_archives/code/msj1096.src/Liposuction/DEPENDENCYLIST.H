//==========================================
// LIPO32/LIPOSUCTION32 - Matt Pietrek 1996
// Microsoft Systems Journal, October 1996
// FILE: DEPENDENCYLIST.CPP
//==========================================
#ifndef __DEPLIST_H__
#define __DEPLIST_H__

//
// This structure represents one executable file in a module dependency list.
// Both the base filename and the complete path are stored.
//
struct MODULE_FILE_INFO
{
    MODULE_FILE_INFO * m_pNext;
    char    m_szBaseName[MAX_PATH];
    char    m_szFullName[MAX_PATH];
};
typedef MODULE_FILE_INFO * PMODULE_FILE_INFO;

//
// The MODULE_DEPENDENCY_LIST class creates a linked list of MODULE_FILE_INFO
// structures.  In theory, this list will represent every executable file
// loaded by the Win32 loader when the executable is loaded.  The class creates
// the list by starting with the file passed to the constructor, and recursing
// through all the import tables.
//
class MODULE_DEPENDENCY_LIST
{
    public:
        
    MODULE_DEPENDENCY_LIST( PSTR pszFileName );
    ~MODULE_DEPENDENCY_LIST( );
    
    PMODULE_FILE_INFO GetNextModule( PMODULE_FILE_INFO p );
        
    PMODULE_FILE_INFO LookupModule( PSTR pszFileName, BOOL fFullName );

    unsigned GetNumberOfModules( void ){ return m_cModules; }

    protected:
        
    unsigned            m_cModules;     // Number of modules in list
    PMODULE_FILE_INFO   m_pList;        // Pointer to head of linked list
    
    void AddModule( PSTR pszFullName ); // Recursively adds modules to the list
};

#endif
