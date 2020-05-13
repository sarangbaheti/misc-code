// IOCTL control codes for sample WDM driver
// Written by Walter Oney

#ifndef SIMPLEIOCTL_H
#define SIMPLEIOCTL_H

#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or devioctl.h before this file")
#endif

#define IOCTL_SIMPLE_GETVER	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif
