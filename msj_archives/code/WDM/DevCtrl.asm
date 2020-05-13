;    DevCtrl.asm -- Device control procedure for MYVXD.VXD

	.386p
	include vmm.inc
	include debug.inc


Declare_Virtual_Device MYVXD, 4, 10, MYVXD_control,\
	Undefined_Device_ID, Undefined_Init_Order

;------------------------------------------------------------------------------
;    Control function:
;------------------------------------------------------------------------------

Begin_Control_Dispatch MYVXD

Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
Control_Dispatch W32_DeviceIoControl, _OnW32DeviceIoControl, cCall, <esi>

End_Control_Dispatch MYVXD

	end
