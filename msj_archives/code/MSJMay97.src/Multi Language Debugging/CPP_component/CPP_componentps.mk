
CPP_componentps.dll: dlldata.obj CPP_component_p.obj CPP_component_i.obj
	link /dll /out:CPP_componentps.dll /def:CPP_componentps.def /entry:DllMain dlldata.obj CPP_component_p.obj CPP_component_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del CPP_componentps.dll
	@del CPP_componentps.lib
	@del CPP_componentps.exp
	@del dlldata.obj
	@del CPP_component_p.obj
	@del CPP_component_i.obj
