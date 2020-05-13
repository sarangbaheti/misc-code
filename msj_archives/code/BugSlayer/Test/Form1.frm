VERSION 5.00
Begin VB.Form Form1
   Caption         =   "Form1"
   ClientHeight    =   3555
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3555
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkShowTrace
      Caption         =   "Act as viewer app"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   3000
      Width           =   2055
   End
   Begin VB.CommandButton btnNull
      Caption         =   "NULL"
      Height          =   495
      Left            =   2640
      TabIndex        =   8
      Top             =   1800
      Width           =   1935
   End
   Begin VB.CommandButton btnEmpty
      Caption         =   "Empty"
      Height          =   495
      Left            =   2640
      TabIndex        =   7
      Top             =   1200
      Width           =   1935
   End
   Begin VB.Frame Frame1
      Caption         =   "Boolean Properties"
      Height          =   2535
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   2055
      Begin VB.CheckBox chkShowTraceAsODS
         Caption         =   "ShowTraceAsODS"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   2160
         Width           =   1815
      End
      Begin VB.CheckBox chkShowTimeStamps
         Caption         =   "ShowTimeStamps"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   1710
         Width           =   1815
      End
      Begin VB.CheckBox chkShowPID
         Caption         =   "ShowPID"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   1260
         Width           =   1815
      End
      Begin VB.CheckBox chkShowItem
         Caption         =   "ShowItemNumber"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   810
         Width           =   1815
      End
      Begin VB.CheckBox chkAddCRLF
         Caption         =   "AddCRLF"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   1815
      End
   End
   Begin VB.CommandButton btnTrace
      Caption         =   "Do Trace String"
      Height          =   735
      Left            =   2640
      TabIndex        =   6
      Top             =   360
      Width           =   1935
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' John Robbins
' Microsoft Systems Journal, December 1997 - Bugslayer Column!
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Private WithEvents trc As Trace
Attribute trc.VB_VarHelpID = -1
Private iMod As Long


 Private Sub Form_Load()

    Set trc = New Trace

    iMod = 0

    If (True = trc.AddCRLF) Then
        chkAddCRLF.Value = 1
    End If
    If (True = trc.ShowItemNumber) Then
        chkShowItem.Value = 1
    End If
    If (True = trc.ShowPID) Then
        chkShowPID.Value = 1
    End If
    If (True = trc.ShowTimeStamps) Then
        chkShowTimeStamps.Value = 1
    End If
    If (True = trc.ShowTraceAsODS) Then
        chkShowTraceAsODS.Value = 1
    End If

    ' At the start, act as a viewer application.
    chkShowTrace.Value = 1

End Sub

Private Sub chkAddCRLF_Click()
    If (1 = chkAddCRLF.Value) Then
        trc.AddCRLF = True
    Else
        trc.AddCRLF = False
    End If
End Sub

Private Sub chkShowItem_Click()
    If (1 = chkShowItem.Value) Then
        trc.ShowItemNumber = True
    Else
        trc.ShowItemNumber = False
    End If
End Sub

Private Sub chkShowPID_Click()
    If (1 = chkShowPID.Value) Then
        trc.ShowPID = True
    Else
        trc.ShowPID = False
    End If
End Sub

Private Sub chkShowTimeStamps_Click()
    If (1 = chkShowTimeStamps.Value) Then
        trc.ShowTimeStamps = True
    Else
        trc.ShowTimeStamps = False
    End If
End Sub

Private Sub chkShowTraceAsODS_Click()
    If (1 = chkShowTraceAsODS.Value) Then
        trc.ShowTraceAsODS = True
    Else
        trc.ShowTraceAsODS = False
    End If
End Sub


Private Sub btnTrace_Click()
    Dim str As String

    iMod = iMod + 1
    If (3 = iMod) Then
        iMod = 0
    End If
    Select Case iMod
        Case 0
            str = "String number 0!"
        Case 1
            str = "Hey!  I'm string 1"
        Case 2
            str = "Pleased to meetcha, I'm string 2"
    End Select
    str = str + vbCrLf

    trc.Trace str
End Sub


Private Sub trc_TraceEvent(ByVal bstrText As String)
    If (1 = chkShowTrace.Value) Then
        MsgBox (bstrText)
    End If
End Sub

Private Sub btnEmpty_Click()
    On Error GoTo btnEmpty_Error
    trc.Trace ""
btnEmpty_Error:
    MsgBox (Err.Description)
End Sub

Private Sub btnNull_Click()
    On Error GoTo btnNull_Error
    trc.Trace vbNullString
btnNull_Error:
    MsgBox (Err.Description)
End Sub

