////////////////////////////////////////////////////////////////
// InjectDLL 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CInjectDll makes it easy to inject a DLL into Windows 95 processes, by
// hiding all the mechanics of windows message hooks. To use it:
//
// * Derive a new class from CInjectDLL and override OnInject to do something
//   the first time your DLL is injected into a new process. Advanced: you
//   can also override OnHookProc to do stuff every time the hook is called.
//
// * Instantiate a CInjectDll object mydll in your DLL. If you're using MFC,
//   you can multiply derive your DLL app object from CWinApp *and* CInjectDll.
//
// * Write exportable functions MyDllInit and MyDllTerm that call
//   mydll.Inject() and mydll.Remove().
//
// * Add the following line to your DLL's module definition (.DEF) file:
//			SECTIONS .InjectDll READ WRITE SHARED
//   This creates the shared data segment "InjectDll" CInjectDll uses.
//
// * Write a "starter app" that calls MyDllInit when it starts up;
//   MyDllTerm when it shuts down.
//
class CInjectDll {
private:
	static CInjectDll* g_pThis;	// global CInjectDll ptr: one per process
	static HHOOK g_hHook;			// systemwide global shared by all processes
	static LRESULT CALLBACK	HookProc(int nCode, WPARAM wp, LPARAM lp);
protected:
	virtual LRESULT OnHookProc(int nCode, WPARAM wp, LPARAM lp);
	virtual void OnInject();
public:
	CInjectDll();
	~CInjectDll();
	enum { E_ALREADY_INJECTED=1, E_INJECT_FAILED };
	int  Inject(HINSTANCE hInstance, int nHookType);
	BOOL Remove();
};
