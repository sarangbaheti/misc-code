/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Sat Feb 22 21:15:31 1997
 */
/* Compiler settings for CPP_component.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IStock = {0xC8D363E5,0xFC5C,0x11CF,{0xA2,0x88,0x00,0xA0,0xC9,0x05,0xA4,0x57}};


const IID LIBID_CPP_COMPONENTLib = {0xC8D363E3,0xFC5C,0x11CF,{0xA2,0x88,0x00,0xA0,0xC9,0x05,0xA4,0x57}};


const CLSID CLSID_CStock = {0xC8D363E9,0xFC5C,0x11CF,{0xA2,0x88,0x00,0xA0,0xC9,0x05,0xA4,0x57}};


#ifdef __cplusplus
}
#endif

