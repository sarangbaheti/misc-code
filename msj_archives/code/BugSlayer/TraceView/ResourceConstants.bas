Attribute VB_Name = "ResourceConstants"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' John Robbins
' Microsoft Systems Journal, December 1997 - Bugslayer Column!
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' All resource string constants go in this file!

Option Explicit

' The application name
Public Const k_APPNAME As Long = 1000

' The menu constants.
Public Const k_MNUFILE As Long = 2000
Public Const k_MNUFILESAVEAS As Long = 2001
Public Const k_MNUFILEEXIT As Long = 2002

Public Const k_MNUEDIT As Long = 2100
Public Const k_MNUEDITCOPY As Long = 2101
Public Const k_MNUEDITSELECTALL As Long = 2102
Public Const k_MNUEDITCLEAR As Long = 2103
Public Const k_MNUEDITFIND As Long = 2104
Public Const k_MNUEDITFINDPREV As Long = 2105
Public Const k_MNUEDITFINDNEXT As Long = 2106

Public Const k_MNUVIEW As Long = 2200
Public Const k_MNUVIEWTOOLBAR As Long = 2201
Public Const k_MNUVIEWSTATUSBAR As Long = 2202
Public Const k_MNUVIEWONTOP As Long = 2203
Public Const k_MNUVIEWFONT As Long = 2204

Public Const k_MNUTRACE As Long = 2300
Public Const k_MNUTRACESHOWTIMESTAMP As Long = 2301
Public Const k_MNUTRACESHOWNUMBER As Long = 2302
Public Const k_MNUTRACESHOWPID As Long = 2303
Public Const k_MNUTRACESHOWODS As Long = 2304
Public Const k_MNUTRACEADDCRLF As Long = 2305

Public Const k_MNUHELP As Long = 2400
Public Const k_MNUHELPABOUT As Long = 2401

' The actual toolbar button constants.  This does not include the
'  separator values.
Public Const k_TBB_SAVEAS As Long = 1
Public Const k_TBB_COPY As Long = 3
Public Const k_TBB_FIND As Long = 5
Public Const k_TBB_FINDPREV As Long = 6
Public Const k_TBB_FINDNEXT As Long = 7
Public Const k_TBB_SHOWTIMESTAMP As Long = 9
Public Const k_TBB_SHOWITEMNUMBER As Long = 10
Public Const k_TBB_SHOWPID As Long = 11
Public Const k_TBB_SHOWODS As Long = 12
Public Const k_TBB_ADDCRLF As Long = 13

' The find dialog constants.
Public Const k_FINDWHATLABEL As Long = 2600
Public Const k_FINDNEXTBTN As Long = 2601
Public Const k_CANCELBTN As Long = 2602
Public Const k_MATCHCASECBX As Long = 2603
Public Const k_DIRECTIONGB As Long = 2604
Public Const k_UPDIRECTIONOB As Long = 2605
Public Const k_DOWNDIRECTIONOB As Long = 2606
Public Const k_FINDDIALOGCAPTION As Long = 2607

