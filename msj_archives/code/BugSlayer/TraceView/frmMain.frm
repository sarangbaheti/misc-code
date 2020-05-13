VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form frmMain
   Caption         =   "TraceView"
   ClientHeight    =   3195
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Tag             =   "1000"
   Begin ComctlLib.Toolbar tbToolbar
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4680
      _ExtentX        =   8255
      _ExtentY        =   741
      ButtonWidth     =   635
      ButtonHeight    =   582
      AllowCustomize  =   0   'False
      Appearance      =   1
      ImageList       =   "imlTBImages"
      _Version        =   327680
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7}
         NumButtons      =   13
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2500"
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2501"
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2502"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2503"
            Object.Tag             =   ""
            ImageIndex      =   4
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2504"
            Object.Tag             =   ""
            ImageIndex      =   5
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button9 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2505"
            Object.Tag             =   ""
            ImageIndex      =   6
            Style           =   1
         EndProperty
         BeginProperty Button10 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2506"
            Object.Tag             =   ""
            ImageIndex      =   7
            Style           =   1
         EndProperty
         BeginProperty Button11 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2507"
            Object.Tag             =   ""
            ImageIndex      =   8
            Style           =   1
         EndProperty
         BeginProperty Button12 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2508"
            Object.Tag             =   ""
            ImageIndex      =   9
            Style           =   1
         EndProperty
         BeginProperty Button13 {0713F354-850A-101B-AFC0-4210102A8DA7}
            Key             =   ""
            Object.ToolTipText     =   "2509"
            Object.Tag             =   ""
            ImageIndex      =   10
            Style           =   1
         EndProperty
      EndProperty
      MouseIcon       =   "frmMain.frx":0000
   End
   Begin MSComDlg.CommonDialog cdlgCommonDlg
      Left            =   3960
      Top             =   1560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
      CancelError     =   -1  'True
      DefaultExt      =   "txt"
      DialogTitle     =   "Save Trace File"
      FileName        =   "Trace.txt"
      Filter          =   "Trace (*.txt)|*.txt"
   End
   Begin VB.TextBox txtEdit
      Height          =   855
      HideSelection   =   0   'False
      Left            =   0
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   2
      Top             =   480
      Width           =   3975
   End
   Begin ComctlLib.StatusBar sbStatusBar
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   2940
      Width           =   4680
      _ExtentX        =   8255
      _ExtentY        =   450
      SimpleText      =   ""
      _Version        =   327680
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7}
         NumPanels       =   2
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7}
            AutoSize        =   1
            Object.Width           =   5186
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7}
            Style           =   5
            TextSave        =   "12:32 AM"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      MouseIcon       =   "frmMain.frx":001C
   End
   Begin ComctlLib.ImageList imlTBImages
      Left            =   4080
      Top             =   600
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327680
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7}
         NumListImages   =   10
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":0038
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":01CA
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":035C
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":046E
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":0580
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":0692
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":07A4
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":08B6
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":09C8
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7}
            Picture         =   "frmMain.frx":0ADA
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile
      Caption         =   "2000"
      Begin VB.Menu mnuFileSaveAs
         Caption         =   "2001"
      End
      Begin VB.Menu mnuWhyDoSepsHaveToHaveAName
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit
         Caption         =   "2002"
      End
   End
   Begin VB.Menu mnuEdit
      Caption         =   "2100"
      Begin VB.Menu mnuEditCopy
         Caption         =   "2101"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuWhyDoSepsHaveToHaveAName2
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSelectAll
         Caption         =   "2102"
      End
      Begin VB.Menu mnuWhyDoSepsHaveToHaveAName3
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditClear
         Caption         =   "2103"
      End
      Begin VB.Menu mnuWhyDoSepsHaveToHaveAName4
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditFind
         Caption         =   "2104"
         Shortcut        =   ^F
      End
      Begin VB.Menu mnuEditFindPrev
         Caption         =   "2105"
      End
      Begin VB.Menu mnuEditFindNext
         Caption         =   "2106"
         Shortcut        =   {F3}
      End
   End
   Begin VB.Menu mnuView
      Caption         =   "2200"
      Begin VB.Menu mnuViewToolbar
         Caption         =   "2201"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewStatusBar
         Caption         =   "2202"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuWhyDoSepsHaveToHaveAName5
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewOnTop
         Caption         =   "2203"
      End
      Begin VB.Menu mnuViewFont
         Caption         =   "2204"
      End
   End
   Begin VB.Menu mnuTrace
      Caption         =   "2300"
      Begin VB.Menu mnuTraceShowTimeStamp
         Caption         =   "2301"
      End
      Begin VB.Menu mnuTraceShowItemNumber
         Caption         =   "2302"
      End
      Begin VB.Menu mnuTraceShowPID
         Caption         =   "2303"
      End
      Begin VB.Menu mnuTraceShowODS
         Caption         =   "2304"
      End
      Begin VB.Menu mnuTraceAddCRLF
         Caption         =   "2305"
      End
   End
   Begin VB.Menu mnuHelp
      Caption         =   "2400"
      Begin VB.Menu mnuHelpAbout
         Caption         =   "2401"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' John Robbins
' Microsoft Systems Journal, December 1997 - Bugslayer Column!
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Constant values used with saving and restoring the settings.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Const k_SETTINGS_SECTION As String = "MainSettings"
Private Const k_MAINLEFT_KEY As String = "MainLeft"
Private Const k_MAINTOP_KEY As String = "MainTop"
Private Const k_MAINWIDTH_KEY As String = "MainWidth"
Private Const k_MAINHEIGHT_KEY As String = "MainHeight"
Private Const k_EDITFONTNAME_KEY As String = "EditFontName"
Private Const k_EDITFONTSIZE_KEY As String = "EditFontSize"
Private Const k_EDITFONTWEIGHT_KEY As String = "EditFontWeight"
Private Const k_EDITFONTBOLD_KEY As String = "EditFontBold"
Private Const k_EDITFONTITALIC_KEY As String = "EditFontItalic"
Private Const k_TOPMOSTWINDOW_KEY As String = "TopMostWindow"

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Private form variables.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The modal find dialog.
Private g_frmFind As frmFind
' The flag that indicates if we have shown the find dialog for the
'  first time.
Private g_bShowFind As Boolean
' The flag that indicates that this window is floating on top.
Private g_bOnTop As Boolean
' The actual trace server object.
Private WithEvents g_Trc As Trace
Attribute g_Trc.VB_VarHelpID = -1


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The Form Handlers
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()

    ' Get the resources for this form hooked up.
    LoadFormResStrings Me

    ' Save a bunch of property gets on the App.Title by getting it once.
    Dim strTitle As String
    strTitle = App.Title

    ' Get the location settings for the main window.
    With Me
        .Left = GetSetting(strTitle, _
                           k_SETTINGS_SECTION, _
                           k_MAINLEFT_KEY, _
                           .Left)
        .Top = GetSetting(strTitle, _
                          k_SETTINGS_SECTION, _
                          k_MAINTOP_KEY, _
                          .Top)
        .Width = GetSetting(strTitle, _
                            k_SETTINGS_SECTION, _
                            k_MAINWIDTH_KEY, _
                            .Width)
        .Height = GetSetting(strTitle, _
                             k_SETTINGS_SECTION, _
                             k_MAINHEIGHT_KEY, _
                             .Height)
    End With    ' Me

    ' Get the settings for the edit control font.
    With txtEdit.Font
        .Name = GetSetting(strTitle, _
                           k_SETTINGS_SECTION, _
                           k_EDITFONTNAME_KEY, _
                           .Name)
        .Size = GetSetting(strTitle, _
                           k_SETTINGS_SECTION, _
                           k_EDITFONTSIZE_KEY, _
                           .Size)
        .Weight = GetSetting(strTitle, _
                             k_SETTINGS_SECTION, _
                             k_EDITFONTWEIGHT_KEY, _
                             .Weight)
        .Bold = GetSetting(strTitle, _
                           k_SETTINGS_SECTION, _
                           k_EDITFONTBOLD_KEY, _
                           .Bold)

        .Italic = GetSetting(strTitle, _
                             k_SETTINGS_SECTION, _
                             k_EDITFONTITALIC_KEY, _
                             .Italic)
    End With    ' txtEdit.Font

    ' Get the on top state.

    g_bOnTop = GetSetting(strTitle, _
                          k_SETTINGS_SECTION, _
                          k_TOPMOSTWINDOW_KEY, _
                          False)

    If (True = g_bOnTop) Then
        mnuViewOnTop.Checked = True
        SetWindowAsTopMost Me.hwnd, True
    End If


    ' Create the find form.
    Set g_frmFind = New frmFind

    ' Tell the find form the edit control it can manipulate.
    Set g_frmFind.EditCtl = txtEdit

    ' We have never shown the find dialog yet.
    g_bShowFind = False

    ' Get a hold of the Trace Server.
    Set g_Trc = New Trace

    ' Set the state of all the trace menu and button items based on the
    '  current state as reported by the trace server.
    With g_Trc
        CoordinateMenuAndButton .ShowTimeStamps, _
                                mnuTraceShowTimeStamp, _
                                k_TBB_SHOWTIMESTAMP
        CoordinateMenuAndButton .ShowItemNumber, _
                                mnuTraceShowItemNumber, _
                                k_TBB_SHOWITEMNUMBER
        CoordinateMenuAndButton .ShowPID, _
                                mnuTraceShowPID, _
                                k_TBB_SHOWPID
        CoordinateMenuAndButton .ShowTraceAsODS, _
                                mnuTraceShowODS, _
                                k_TBB_SHOWODS
        CoordinateMenuAndButton .AddCRLF, _
                                mnuTraceAddCRLF, _
                                k_TBB_ADDCRLF
    End With    ' g_Trc

    g_Trc.Trace "Started up TraceView!" + vbCrLf

End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set g_frmFind = Nothing
    Set g_Trc = Nothing

    ' Save a bunch of property gets on the App.Title by getting it once.
    Dim strTitle As String
    strTitle = App.Title

    ' If not minimized, save the latest window location.
    If Me.WindowState <> vbMinimized Then
        With Me
            SaveSetting strTitle, _
                        k_SETTINGS_SECTION, _
                        k_MAINLEFT_KEY, _
                        .Left
            SaveSetting strTitle, _
                        k_SETTINGS_SECTION, _
                        k_MAINTOP_KEY, _
                        .Top
            SaveSetting strTitle, _
                        k_SETTINGS_SECTION, _
                        k_MAINWIDTH_KEY, _
                        .Width
            SaveSetting strTitle, _
                        k_SETTINGS_SECTION, _
                        k_MAINHEIGHT_KEY, _
                        .Height
        End With    ' Me
    End If

    ' Save the current font for the edit control.
    With txtEdit.Font
        SaveSetting strTitle, _
                    k_SETTINGS_SECTION, _
                    k_EDITFONTNAME_KEY, _
                    .Name

        SaveSetting strTitle, _
                    k_SETTINGS_SECTION, _
                    k_EDITFONTSIZE_KEY, _
                    .Size

        SaveSetting strTitle, _
                    k_SETTINGS_SECTION, _
                    k_EDITFONTWEIGHT_KEY, _
                    .Weight

        SaveSetting strTitle, _
                    k_SETTINGS_SECTION, _
                    k_EDITFONTBOLD_KEY, _
                    .Bold

        SaveSetting strTitle, _
                    k_SETTINGS_SECTION, _
                    k_EDITFONTITALIC_KEY, _
                    .Italic
    End With    ' txtEdit.Font

    ' Save the on top setting.
    SaveSetting strTitle, _
                k_SETTINGS_SECTION, _
                k_TOPMOSTWINDOW_KEY, _
                g_bOnTop

End Sub

Private Sub Form_Resize()

    ' Only handle the resizing if the app is not minimized.
    If Me.WindowState <> vbMinimized Then

        ' Make the edit control the same size as the client area.
        Dim lHeight As Long
        Dim lTop As Long

        ' Always start out that the edit control will be full size.
        lTop = 0
        lHeight = Me.ScaleHeight

        If (True = tbToolbar.Visible) Then
            ' Subtract the height of the toolbar.
            lHeight = lHeight - tbToolbar.Height
            ' Move the top down past the toolbar.
            lTop = tbToolbar.Height
        End If

        If (True = sbStatusBar.Visible) Then
            ' Subtract off the height of status bar.
            lHeight = lHeight - sbStatusBar.Height
        End If

        With txtEdit
            .Top = lTop
            .Left = 0
            .Height = lHeight
            .Width = Me.ScaleWidth
        End With
    End If
End Sub

Private Sub Form_GotFocus()
    ' Always force the focus to the edit control.
    txtEdit.SetFocus
End Sub


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The File Menu Handlers
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub mnuFileSaveAs_Click()

    On Error GoTo mnuFileSaveAs_Click_Error

    ' Prepare to call the save as dialog.
    cdlgCommonDlg.Flags = 0
    cdlgCommonDlg.Flags = cdlOFNHideReadOnly Or cdlOFNOverwritePrompt

    ' Do it.
    cdlgCommonDlg.ShowSave

    ' Write out the file.
    Dim iFile As Integer

    iFile = FreeFile

    Screen.MousePointer = vbHourglass

    Open cdlgCommonDlg.filename For Output As #iFile

    Print #iFile, txtEdit.Text

    Close #iFile

    Screen.MousePointer = vbDefault

    Exit Sub

mnuFileSaveAs_Click_Error:
    Screen.MousePointer = vbDefault

    ' If the error was anything other than cancel, show it.
    If (cdlCancel <> Err.Number) Then
        MsgBox (Err.Description)
    End If
End Sub

Private Sub mnuFileExit_Click()

    Unload Me

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The Edit Menu Handlers
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub mnuEditCopy_Click()
    If (0 <> txtEdit.SelLength) Then
        Clipboard.SetText txtEdit.SelText
    End If
End Sub

Private Sub mnuEditSelectAll_Click()
    txtEdit.SelStart = 0
    txtEdit.SelLength = Len(txtEdit.Text)
    CoordinateCopyMenuAndButton
End Sub

Private Sub mnuEditClear_Click()
    txtEdit.Text = ""
    CoordinateCopyMenuAndButton
End Sub

Private Sub mnuEditFind_Click()
    If (False = g_bShowFind) Then
        g_frmFind.Show vbModeless, Me
    Else
        g_frmFind.Visible = True
        g_frmFind.SetFocus
    End If
End Sub

Private Sub mnuEditFindPrev_Click()
    g_frmFind.UpDirection = 1
    If (Len(g_frmFind.FindString) > 0) Then
        g_frmFind.FindIt
    Else
        mnuEditFind_Click
    End If
End Sub

Private Sub mnuEditFindNext_Click()
    g_frmFind.UpDirection = 0
    If (Len(g_frmFind.FindString) > 0) Then
        g_frmFind.FindIt
    Else
        mnuEditFind_Click
    End If
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The View Menu Handlers
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub mnuViewToolbar_Click()
    ' Toggle the state of the toolbar.
    If (True = mnuViewToolbar.Checked) Then
        mnuViewToolbar.Checked = False
        tbToolbar.Visible = False
    Else
        mnuViewToolbar.Checked = True
        tbToolbar.Visible = True
    End If
    Form_Resize
End Sub

Private Sub mnuViewStatusBar_Click()
    ' Toggle the state of the toolbar.
    If (True = mnuViewStatusBar.Checked) Then
        mnuViewStatusBar.Checked = False
        sbStatusBar.Visible = False
    Else
        mnuViewStatusBar.Checked = True
        sbStatusBar.Visible = True
    End If
    Form_Resize
End Sub

Private Sub mnuViewOnTop_Click()
    g_bOnTop = Not g_bOnTop
    mnuViewOnTop.Checked = g_bOnTop
    SetWindowAsTopMost Me.hwnd, g_bOnTop
End Sub

Private Sub mnuViewFont_Click()

    On Error GoTo mnuViewFont_Click_Error

    With cdlgCommonDlg
        .Flags = 0
        .Flags = cdlCFBoth And (Not cdlCFEffects)
        .FontName = txtEdit.Font.Name
        .FontSize = txtEdit.Font.Size
        .FontBold = txtEdit.Font.Bold
        .FontItalic = txtEdit.Font.Italic
    End With

    cdlgCommonDlg.ShowFont

    With txtEdit.Font
        .Name = cdlgCommonDlg.FontName
        .Size = cdlgCommonDlg.FontSize
        .Bold = cdlgCommonDlg.FontBold
        .Italic = cdlgCommonDlg.FontItalic
    End With

    Exit Sub

mnuViewFont_Click_Error:

    ' If the error was anything other than cancel, show it.
    If (cdlCancel <> Err.Number) Then
        MsgBox (Err.Description)
    End If

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The Trace Menu Handlers
'   Note that none of these actually change the menu items, the menu
'   items are changed in the event handlers below.  Changing these
'   properties force an event so that all viewers are coordinated.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub mnuTraceShowTimeStamp_Click()
    g_Trc.ShowTimeStamps = Not g_Trc.ShowTimeStamps
End Sub

Private Sub mnuTraceShowItemNumber_Click()
    g_Trc.ShowItemNumber = Not g_Trc.ShowItemNumber
End Sub

Private Sub mnuTraceShowPID_Click()
    g_Trc.ShowPID = Not g_Trc.ShowPID
End Sub

Private Sub mnuTraceShowODS_Click()
    g_Trc.ShowTraceAsODS = Not g_Trc.ShowTraceAsODS
End Sub

Private Sub mnuTraceAddCRLF_Click()
    g_Trc.AddCRLF = Not g_Trc.AddCRLF
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The Help Menu Handlers
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub mnuHelpAbout_Click()

    Dim frmA As frmAbout

    Set frmA = New frmAbout

    frmA.Show 1, Me

    Set frmA = Nothing

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The Toolbar Handlers
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub tbToolbar_ButtonClick(ByVal Button As ComctlLib.Button)

    Select Case Button.Index
        Case k_TBB_SAVEAS
            mnuFileSaveAs_Click
        Case k_TBB_COPY
            mnuEditCopy_Click
        Case k_TBB_FIND
            mnuEditFind_Click
        Case k_TBB_FINDPREV
            mnuEditFindPrev_Click
        Case k_TBB_FINDNEXT
            mnuEditFindNext_Click
        Case k_TBB_SHOWTIMESTAMP
            mnuTraceShowTimeStamp_Click
        Case k_TBB_SHOWITEMNUMBER
            mnuTraceShowItemNumber_Click
        Case k_TBB_SHOWPID
            mnuTraceShowPID_Click
        Case k_TBB_SHOWODS
            mnuTraceShowODS_Click
        Case k_TBB_ADDCRLF
            mnuTraceAddCRLF_Click
        Case Else
            Debug.Assert False
    End Select

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The Edit Control Event Handlers.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub txtEdit_Change()
    CoordinateCopyMenuAndButton
End Sub

Private Sub txtEdit_MouseUp(Button As Integer, _
                            Shift As Integer, _
                            x As Single, _
                            y As Single)
    CoordinateCopyMenuAndButton
End Sub

Private Sub txtEdit_KeyUp(KeyCode As Integer, Shift As Integer)
    CoordinateCopyMenuAndButton
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The TraceSrv event handlers.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub g_Trc_TraceEvent(ByVal bstrText As String)
    AppendText bstrText
End Sub

Private Sub g_Trc_ChangeShowTimeStamps(ByVal bNewVal As Boolean)
    CoordinateMenuAndButton g_Trc.ShowTimeStamps, _
                            mnuTraceShowTimeStamp, _
                            k_TBB_SHOWTIMESTAMP
End Sub

Private Sub g_Trc_ChangeShowItemNumber(ByVal bNewVal As Boolean)
    CoordinateMenuAndButton g_Trc.ShowItemNumber, _
                            mnuTraceShowItemNumber, _
                            k_TBB_SHOWITEMNUMBER
End Sub

Private Sub g_Trc_ChangeShowPID(ByVal bNewVal As Boolean)
    CoordinateMenuAndButton g_Trc.ShowPID, _
                            mnuTraceShowPID, _
                            k_TBB_SHOWPID
End Sub

Private Sub g_Trc_ChangeShowTraceAsODS(ByVal bNewVal As Boolean)
    CoordinateMenuAndButton g_Trc.ShowTraceAsODS, _
                            mnuTraceShowODS, _
                            k_TBB_SHOWODS
End Sub

Private Sub g_Trc_ChangeAddCRLF(ByVal bNewVal As Boolean)
    CoordinateMenuAndButton g_Trc.AddCRLF, _
                            mnuTraceAddCRLF, _
                            k_TBB_ADDCRLF
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Private helper functions.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' FUNCTION      :   CoordinateMenuAndButton
' DISCUSSION    :
'   Handles setting the state of the trace menus and toolbars.
' PARAMETERS    :
'   bState  - The boolean state value.
'   mnuIn   - The menu to set.
'   lButton - The number of the button to set.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub CoordinateMenuAndButton(bState As Boolean, _
                                    mnuIn As Menu, _
                                    lButton As Long)
    ' Toggle the menu and the button.
    If (False = bState) Then
        mnuIn.Checked = False
        tbToolbar.Buttons(lButton).Value = tbrUnpressed
    Else
        mnuIn.Checked = True
        tbToolbar.Buttons(lButton).Value = tbrPressed
    End If
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' FUNCTION      :   CoordinateCopyMenuAndButton
' DISCUSSION    :
'   Takes care of setting the state of the Edit|Copy menu and toolbar
'   button based in the amount of text selected.  This needs to be called
'   in many places and I did not want duplicate code running around.
' PARAMETERS    :
'   None
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub CoordinateCopyMenuAndButton()
    If (0 <> txtEdit.SelLength) Then
        mnuEditCopy.Enabled = True
        tbToolbar.Buttons(k_TBB_COPY).Enabled = True

    Else
        mnuEditCopy.Enabled = False
        tbToolbar.Buttons(k_TBB_COPY).Enabled = False
    End If
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' FUNCTION      :   AppendText
' DISCUSSION    :
'   Appends the text in strText to the edit control.
' PARAMETERS    :
'   strText - The string to append.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub AppendText(strText As String)

    ' The flag to know if we are supposed to put the cursor back or not.
    Dim bPutCursorBack As Boolean
    ' The initial cursor position in the edit control.
    Dim lInitialCursorPos As Long
    ' The initial selection length in the edit control.
    Dim lInitialSelLen As Long
    ' The length of the text in the edit control.
    Dim lTextLen As Long

    With txtEdit
        ' Initialize everything.
        bPutCursorBack = False
        lInitialCursorPos = .SelStart
        lInitialSelLen = .SelLength
        lTextLen = Len(.Text)

        ' If the cursor is not at the end, put it there.
        If (lInitialCursorPos <> lTextLen) Then
            .SelStart = lTextLen
            .SelLength = 0
            bPutCursorBack = True
        End If

        ' Append the text on the end.
        .Text = .Text + strText

        ' Put the cursor back if needed.
        If (True = bPutCursorBack) Then
            .SelStart = lInitialCursorPos
        Else
            .SelStart = Len(txtEdit.Text)
        End If

        ' If there was text previously selected, reselect it.
        If (0 <> lInitialSelLen) Then
            .SelLength = lInitialSelLen
        End If
    End With    ' txtEdit

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' FUNCTION      :   SetWindowAsTopMost
' DISCUSSION    :
'   Sets the window handle passed in hWnd as a top most window if bTop
'   is TRUE.  Otherwise, sets the window to a normal window.
' PARAMETERS    :
'   hWnd - The window to set.
'   bTop - True for forcing hWnd to topmost.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub SetWindowAsTopMost(hwnd As Long, bTop As Boolean)
    Dim lDummy As Long
    Dim lMsg As Long

    If (True = bTop) Then
        lMsg = HWND_TOPMOST
    Else
        lMsg = HWND_NOTOPMOST
    End If

    lDummy = SetWindowPos(hwnd, _
                            lMsg, _
                            0, _
                            0, _
                            0, _
                            0, _
                            SWP_NOMOVE Or SWP_NOSIZE)
End Sub
