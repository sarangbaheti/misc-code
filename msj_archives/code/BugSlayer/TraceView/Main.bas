Attribute VB_Name = "MainMod"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' John Robbins
' Microsoft Systems Journal, December 1997 - Bugslayer Column!
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

' The one instance of the main form.
Public fMainForm As frmMain

' Start me up.
Sub Main()

    Set fMainForm = New frmMain

    Load fMainForm

    fMainForm.Show

End Sub
