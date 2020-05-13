VERSION 5.00
Begin VB.Form frmFind
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Find"
   ClientHeight    =   1470
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5955
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1470
   ScaleWidth      =   5955
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Tag             =   "2607"
   Begin VB.Frame Frame1
      Caption         =   "Direction"
      Height          =   855
      Left            =   2040
      TabIndex        =   3
      Tag             =   "2604"
      Top             =   480
      Width           =   2415
      Begin VB.OptionButton rbDown
         Caption         =   "Down"
         Height          =   255
         Left            =   1320
         TabIndex        =   5
         Tag             =   "2606"
         Top             =   360
         Width           =   975
      End
      Begin VB.OptionButton rbUp
         Caption         =   "Up"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Tag             =   "2605"
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.CheckBox cbxCase
      Caption         =   "Match Case"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Tag             =   "2603"
      Top             =   840
      Width           =   1575
   End
   Begin VB.CommandButton btnCancel
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4680
      TabIndex        =   7
      Tag             =   "2602"
      Top             =   720
      Width           =   1095
   End
   Begin VB.CommandButton btnFindNext
      Caption         =   "Find &Next"
      Default         =   -1  'True
      Height          =   375
      Left            =   4680
      TabIndex        =   6
      Tag             =   "2601"
      Top             =   120
      Width           =   1095
   End
   Begin VB.TextBox txtToFind
      Height          =   285
      Left            =   1560
      TabIndex        =   1
      Top             =   120
      Width           =   2895
   End
   Begin VB.Label Label1
      Caption         =   "Find What:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Tag             =   "2600"
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmFind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' John Robbins
' Microsoft Systems Journal, December 1997 - Bugslayer Column!
' This is lifted and modified from the VB SDINote sample.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Constants
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Const k_FINDSETTINGS_SECTION As String = "FindSettings"
Private Const k_FINDLEFT_KEY As String = "FindLeft"
Private Const k_FINDTOP_KEY As String = "FindTop"
Private Const k_FINDWIDTH_KEY As String = "FindWidth"
Private Const k_FINDHEIGHT_KEY As String = "FindHeight"

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Public variables
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' BUG BUG
'  Right now, this find dialog is only hooked into an edit control.
'  This should get genericised so that it can be used by anything.
'  Eventually, instead of the edit control, this should be some abstract
'  base class with methods for doing the searching.
' The edit control this instance of the find dialog will work with.
Public EditCtl As TextBox

' The default string to find.  Before showing the form, set this variable
'  to default value.
Public FindString As String

' Look upwards?  Set to one to look up.  Zero looks down.
Public UpDirection As Long

' The match case flag.  Set to one to match case.
Public MatchCase As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Private variables
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The flag that indicates if this is a first time lookup.
Private FirstTime As Boolean

' The current position in the edit control when we start the find.
Private CurrPos As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The initialization stuff.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub Form_Initialize()

    ' Set everything to known values.
    Set EditCtl = Nothing
    FindString = ""
    UpDirection = 0
    MatchCase = 0

End Sub


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The Form Handlers
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()

    ' Load the resource strings for the form.
    LoadFormResStrings Me

    ' Get the settings for the find dialog.
    Me.Left = GetSetting(App.Title, _
                         k_FINDSETTINGS_SECTION, _
                         k_FINDLEFT_KEY, _
                         Me.Left)
    Me.Top = GetSetting(App.Title, _
                        k_FINDSETTINGS_SECTION, _
                        k_FINDTOP_KEY, _
                        Me.Top)
    Me.Width = GetSetting(App.Title, _
                          k_FINDSETTINGS_SECTION, _
                          k_FINDWIDTH_KEY, _
                          Me.Width)
    Me.Height = GetSetting(App.Title, _
                           k_FINDSETTINGS_SECTION, _
                           k_FINDHEIGHT_KEY, _
                           Me.Height)

    txtToFind.Text = FindString
    If ("" = FindString) Then
        btnFindNext.Enabled = False
    End If
    If (1 = UpDirection) Then
        rbUp.Value = True
    Else
        rbDown.Value = True
    End If
    cbxCase.Value = MatchCase

End Sub

Private Sub Form_Unload(Cancel As Integer)
    SaveSetting App.Title, _
                k_FINDSETTINGS_SECTION, _
                k_FINDLEFT_KEY, _
                Me.Left
    SaveSetting App.Title, _
                k_FINDSETTINGS_SECTION, _
                k_FINDTOP_KEY, _
                Me.Top
    SaveSetting App.Title, _
                k_FINDSETTINGS_SECTION, _
                k_FINDWIDTH_KEY, _
                Me.Width
    SaveSetting App.Title, _
                k_FINDSETTINGS_SECTION, _
                k_FINDHEIGHT_KEY, _
                Me.Height
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Button handlers.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Private Sub btnCancel_Click()

    ' Save the default values for next time.
    FindString = txtToFind.Text
    If (True = rbUp.Value) Then
        UpDirection = 1
    Else
        UpDirection = 0
    End If
    MatchCase = cbxCase.Value

    'Unload Me
    Me.Hide

End Sub

Private Sub btnFindNext_Click()
    FindString = txtToFind.Text

    If (True = rbUp.Value) Then
        UpDirection = 1
    Else
        UpDirection = 0
    End If
    MatchCase = cbxCase.Value


    FindIt
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Text control handlers.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub txtToFind_Change()
    FirstTime = True
    If ("" <> txtToFind.Text) Then
        btnFindNext.Enabled = True
    Else
        btnFindNext.Enabled = False
    End If
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The actual find function!
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub FindIt()
    Dim intStart As Integer
    Dim intPos As Integer
    Dim strFindString As String
    Dim strSourceString As String
    Dim strMsg As String
    Dim intResponse As Integer
    Dim intOffset As Integer

    ' Set offset variable based on cursor position.
    If (CurrPos = EditCtl.SelStart) Then
        intOffset = 1
    Else
        intOffset = 0
    End If

    ' Read the public variable for start position.
    If (True = FirstTime) Then
        intOffset = 0
    End If

    ' Assign a value to the start value.
    intStart = EditCtl.SelStart + intOffset

    ' If not case sensitive, convert the string to upper case
    If (1 = MatchCase) Then
        strFindString = FindString
        strSourceString = EditCtl.Text
    Else
        strFindString = UCase(FindString)
        strSourceString = UCase(EditCtl.Text)
    End If

    ' Search for the string.
    If (0 = UpDirection) Then
        intPos = InStr(intStart + 1, strSourceString, strFindString, vbTextCompare)
    Else
        For intPos = intStart - 1 To 0 Step -1
            If (0 = intPos) Then
                Exit For
            End If
            If (strFindString = Mid(strSourceString, _
                                     intPos, _
                                     Len(strFindString))) Then
                Exit For
            End If
        Next
    End If

    ' If the string is found...
    If (intPos) Then
        EditCtl.SelStart = intPos - 1
        EditCtl.SelLength = Len(strFindString)
    Else
        strMsg = "Cannot find " & Chr(34) & FindString & Chr(34)
        intResponse = MsgBox(strMsg, 0, App.Title)
    End If

    CurrPos = EditCtl.SelStart
    FirstTime = False
End Sub

