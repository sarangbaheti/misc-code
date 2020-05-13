VERSION 5.00
Begin VB.UserControl MenuCtl 
   ClientHeight    =   180
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   252
   Picture         =   "vbmenu.ctx":0000
   PropertyPages   =   "vbmenu.ctx":0136
   ScaleHeight     =   180
   ScaleWidth      =   252
   Begin VB.Menu mnuPopup 
      Caption         =   "Popup"
      Begin VB.Menu mnuPopupItem 
         Caption         =   ""
         Index           =   1
      End
   End
End
Attribute VB_Name = "MenuCtl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Event Click(ItemNumber As Integer)

Private Sub mnuPopupItem_Click(Index As Integer)
RaiseEvent Click(Index)
End Sub

Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
PopupMenu mnuPopup
End Sub
Public Property Get MenuItem(ItemNumber As Integer) As String
MenuItem = mnuPopupItem(ItemNumber).Caption
End Property

Public Property Let MenuItem(ItemNumber As Integer, Caption As String)
If ItemNumber <> 1 Then
    Load mnuPopupItem(ItemNumber)
End If
mnuPopupItem(ItemNumber).Caption = Caption
End Property
