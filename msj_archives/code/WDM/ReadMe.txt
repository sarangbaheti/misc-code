This directory contains three projects intended for use with
Microsoft Visual C++ Version 4.2:

SIMPLE.MAK is the sample WDM driver discussed in the magazine article.
The SIMPLE project includes:

	CONTROL.CPP		Handle IRP_MJ_DEVICE_CONTROL requests. The only
					one implemented by this sample is IOCTL_SIMPLE_GETVER,
					which returns the revision level of the driver.

	DRIVER.H		Declarations, especially including the DRIVE_EXTENSION
					structure used in this driver.

	DRIVERENTRY.CPP	Common routines, including the DriverEntry and AddDevice
					functions as well as several others.

	MAKEFILE		Standard kernel-mode driver make file.

	MAKEFILE.INC	Extensions to make file.
					
	PLUGPLAY.CPP	Handle IRP_MJ_PNP requests.

	POWER.CPP		Handle IRP_MJ_POWER requests.

	READWRITE.CPP	Handle IRP_MJ_WRITE requests. This module also actually
					implements the IRP_MN_START_DEVICE and IRP_MN_SET_POWER
					requests at the device level.

	SIMPLEIOCTL.H	Declaration of the IOCTL code used by this driver. This
					header is also intended for inclusion in application code
					that needs to invoke SIMPLE's control functions.

	SOURCES			Standard control file for the kernel-mode BUILD process.

	WDMBUILD.BAT	Batch file to bridge between the VC++ build command and the
					standard kernel-mode BUILD command.

	WCO.INF			Setup control file for use in Memphis to install this driver.

	Note that the source files contain "@" comments for the AutoDuck automatic
	documentation tool. That's a free tool available from the Microsoft FTP
	server.

TEST.MAK is a test program that illustrates how to use the sample driver. This
project contains just one file:

	TEST.CPP		The test program itself.

MYVXD.MAK is a dynamically loadable VxD used with the TEST program to show how
you go about calling a WDM driver from a VxD. This project contains:

	DEVCTRL.ASM		Declarations and control procedure

	MYVXD.CPP		The VxD code itself.

	MYVXD.DEF		Module definition file used to build the VxD.

	MYVXD.H			Header file shared with the TEST program.

	STDVXD.H		Standard declarations for my VxD projects.

To build and test the sample driver, follow this procedure:

	1.	You must have the Windows 95 Device Driver Kit and the Memphis DDK
		installed. Using the Tools/Options/Directories property page, make
		sure that the Win95 DDK's BIN, INC32, and LIB directories are in
		the obvious search paths.

	2.	Copy the WDMBUILD.BAT file somewhere that's always in your path.

	3.	Be sure that the MSDEVDIR environment variable is set before Windows
		starts. Modify your AUTOEXEC.BAT to set it if necessary.

	4.	Modify the VXD.MAK and MAKEFILE.INC files to point to the directory
		(if any) where you have Soft-Ice/W version 3.x installed. If you don't
		own a copy of Soft-Ice/W, remove the command lines that refer to it.

	5.	Build all three projects. There should be no warnings, except that the
		link step for MYVXD will generate a bunch of benign warnings about
		mismatched segment attributes.

	6.	Use the "Install New Hardware" Wizard in Control Panel to install the
		SIMPLE device. You'll indicate you're installing an "Other" device, and
		you'll use the "Have Disk" button to direct the wizard to the project
		directory containing the INF file.

	7.	At an MS-DOS prompt, change to the project directory and issue the
		command "DEBUG\TEST". (Don't just change to the DEBUG subdirectory,
		because the test program then won't be able to find MYVXD.VXD.) The
		test program should exercise the IOCTL interface to SIMPLE and report
		the results.

	8.	Using the Device Manager (reached from the System control panel applet),
		determine the port address and IRQ that the Windows Configuration Manager
		assigned to the fake device. Use the following Soft-Ice/W command to
		establish a breakpoint on OUT operations to the port:

			BPIO -h <portaddr> W

		Now launch the test program with the "-dowrite" command-line option. You
		should reach the I/O breakpoint immediately. Use the command "? AL" to
		inspect the contents of the AL register, which is being written by the
		HAL. It should be the character 'H'. Use the "GO" command to restart
		execution.

		Hot-key back to Soft-Ice/W and issue the "GENINT <intno>" command to
		simulate a hardware interrupt on your IRQ. The interrupt number to use
		is 50h plus the IRQ your were assigned. I.e., if you get IRQ 10, use
		5Ah as the interrupt number. You should get another I/O breakpoint, and
		you should repeat the previous step.

		After several cycles of I/O breakpoint, restart, simulated interrupt,
		you'll see that the driver has written the string "Hi!" to the output
		port. The test program will report that it successfully transferred 3
		bytes.

		Don't be tempted to speed up the test process by just issuing the GENINT
		instruction at the I/O breakpoint. In my experience, this hangs the system.
