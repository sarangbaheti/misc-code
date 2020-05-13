
TraceSrvps.dll: dlldata.obj TraceSrv_p.obj TraceSrv_i.obj
	link /dll /out:TraceSrvps.dll /def:TraceSrvps.def /entry:DllMain dlldata.obj TraceSrv_p.obj TraceSrv_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del TraceSrvps.dll
	@del TraceSrvps.lib
	@del TraceSrvps.exp
	@del dlldata.obj
	@del TraceSrv_p.obj
	@del TraceSrv_i.obj
