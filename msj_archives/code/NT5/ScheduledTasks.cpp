//=============================================================
// Matt Pietrek
// Microsoft Systems Journal, November 1997
// FILE: ScheduledTasks.CPP
// To compile: CL /DUNICODE=1 /D_UNICODE=1 ScheduledTasks.CPP \
//             mstask.lib ole32.lib
//=============================================================
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <mstask.h>
#include <tchar.h>

//=========================================================================
// Preprocessor macro that combines a bunch of often used boilerplate code.
// Prints out the results of the preceding operation, and bails out via
// _leave if the operation failed.
//=========================================================================
#define HANDLE_RESULT_CODE( x, hr ) \
        if ( SUCCEEDED(hr) ) { _tprintf( _T("%s worked\n"), _T(#x) ); } \
        else { _tprintf( _T("%s failed %x\n"), _T(#x), hr ); _leave; }
        
int main()
{
    CoInitialize( 0 );

    ITaskScheduler * pITaskScheduler = 0;
    ITask * pITask = 0;
    ITaskTrigger * pITaskTrigger = 0;
        
    _try
    {
        HRESULT hr;


        //=====================================================================
        // Create the ITaskScheduler interface instance
        //=====================================================================
        hr = CoCreateInstance(  CLSID_CTaskScheduler,     // REFCLSID
                                0,                          // LPUNKNOWN outer
                                CLSCTX_SERVER,              // CLSCTX
                                IID_ITaskScheduler,
                                (LPVOID *)&pITaskScheduler );
        HANDLE_RESULT_CODE( "CoCreateInstance(CLSID_CTaskScheduler)", hr );
        
        LPWSTR ppwszComputer;
        
        //=====================================================================
        // Retrieve and print out the name of the target computer
        //=====================================================================
        pITaskScheduler->GetTargetComputer( &ppwszComputer );     
        HANDLE_RESULT_CODE( "pITaskScheduler->GetTargetComputer", hr );
        _tprintf( _T("Target computer: %s\n"), ppwszComputer );


        //=====================================================================
        // Free the string allocated by ::GetTargetComputer
        //=====================================================================
        CoTaskMemFree( ppwszComputer );

        
        //=====================================================================
        // Create the ITask interface instance
        //=====================================================================
        hr = pITaskScheduler->NewWorkItem(_T("MyHappyWorkItem"),
                                            CLSID_CTask,
                                            IID_ITask,
                                            (LPUNKNOWN *)&pITask );                                 
        HANDLE_RESULT_CODE( "pITaskScheduler->NewWorkItem", hr );


        //=====================================================================
        // Set the name of the program associated with the ITask
        //=====================================================================
        hr = pITask->SetApplicationName( _T("CALC.EXE") );
        HANDLE_RESULT_CODE( "pITask->SetApplicationName", hr );
        
        
        //=====================================================================
        // Create an ITaskTrigger interface associated with the ITask
        //=====================================================================
        WORD iNewTrigger;   
        hr = pITask->CreateTrigger( &iNewTrigger, &pITaskTrigger );     
        HANDLE_RESULT_CODE( "pITask->CreateTrigger", hr );

        TASK_TRIGGER trigger;


        //=====================================================================
        // Retrieve the default value for the task trigger
        //=====================================================================
        pITaskTrigger->GetTrigger( &trigger );
        HANDLE_RESULT_CODE( "pITaskTrigger->GetTrigger", hr );

        trigger.wStartMinute++;     // Bump the start time up by one minute
        
        //=====================================================================
        // Store new task trigger values
        //=====================================================================
        pITaskTrigger->SetTrigger( &trigger );
        HANDLE_RESULT_CODE( "pITaskTrigger->SetTrigger", hr );
            
        //=====================================================================
        // Display the user interface that allows the user to change task info
        //=====================================================================
        hr = pITask->EditWorkItem( 0, 0 );
        HANDLE_RESULT_CODE( "pITask->EditWorkItem", hr );
        
        //=====================================================================
        // Get rid of the task, so that our demo doesn't leave litter behind
        //=====================================================================
        pITaskScheduler->Delete( _T("MyHappyWorkItem") );
        HANDLE_RESULT_CODE( "pITaskScheduler->Delete", hr );
    }
    __finally
    {
        if ( pITaskTrigger )
            pITaskTrigger->Release();

        if ( pITask )
            pITask->Release();

        if ( pITaskScheduler )
            pITaskScheduler->Release();
                    
        CoUninitialize();
    }
    
    return 0;
}

