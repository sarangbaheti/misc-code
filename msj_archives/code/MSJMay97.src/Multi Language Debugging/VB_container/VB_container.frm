VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form VB_container_ 
   Caption         =   "VB_container"
   ClientHeight    =   5340
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7245
   LinkTopic       =   "Form1"
   ScaleHeight     =   5340
   ScaleWidth      =   7245
   StartUpPosition =   3  'Windows Default
   Begin ComctlLib.ProgressBar ProgressBar1 
      Align           =   2  'Align Bottom
      Height          =   240
      Left            =   0
      TabIndex        =   22
      Top             =   5100
      Width           =   7245
      _ExtentX        =   12779
      _ExtentY        =   423
      _Version        =   327680
      Appearance      =   1
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   4215
      Left            =   120
      TabIndex        =   10
      Top             =   240
      Width           =   7095
      _ExtentX        =   12515
      _ExtentY        =   7435
      _Version        =   327680
      TabHeight       =   520
      TabCaption(0)   =   "Purchase"
      TabPicture(0)   =   "VB_container.frx":0000
      Tab(0).ControlCount=   9
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Purchase_Price_label"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "Purchase_Shares_label"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "Purchase_Stock_label"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "Purchase_Account_label"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "Purchase_Price"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "Purchase_Shares"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "Purchase_Stock"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "Purchase_Account"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).Control(8)=   "Purchase"
      Tab(0).Control(8).Enabled=   0   'False
      TabCaption(1)   =   "Sell"
      TabPicture(1)   =   "VB_container.frx":001C
      Tab(1).ControlCount=   9
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Sell"
      Tab(1).Control(0).Enabled=   -1  'True
      Tab(1).Control(1)=   "Sell_Account"
      Tab(1).Control(1).Enabled=   -1  'True
      Tab(1).Control(2)=   "Sell_Stock"
      Tab(1).Control(2).Enabled=   -1  'True
      Tab(1).Control(3)=   "Sell_Shares"
      Tab(1).Control(3).Enabled=   -1  'True
      Tab(1).Control(4)=   "Sell_Price"
      Tab(1).Control(4).Enabled=   -1  'True
      Tab(1).Control(5)=   "Sell_Account_label"
      Tab(1).Control(5).Enabled=   0   'False
      Tab(1).Control(6)=   "Sell_Stock_label"
      Tab(1).Control(6).Enabled=   0   'False
      Tab(1).Control(7)=   "Sell_Shares_label"
      Tab(1).Control(7).Enabled=   0   'False
      Tab(1).Control(8)=   "Sell_Price_label"
      Tab(1).Control(8).Enabled=   0   'False
      TabCaption(2)   =   "Commission"
      TabPicture(2)   =   "VB_container.frx":0038
      Tab(2).ControlCount=   3
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "Commission"
      Tab(2).Control(0).Enabled=   -1  'True
      Tab(2).Control(1)=   "Get_Commission"
      Tab(2).Control(1).Enabled=   -1  'True
      Tab(2).Control(2)=   "Commission_label"
      Tab(2).Control(2).Enabled=   0   'False
      Begin VB.TextBox Commission 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   -72600
         TabIndex        =   20
         Top             =   720
         Width           =   3015
      End
      Begin VB.CommandButton Get_Commission 
         Caption         =   "Get Commission"
         Height          =   495
         Left            =   -72600
         TabIndex        =   19
         Top             =   3120
         Width           =   1815
      End
      Begin VB.CommandButton Sell 
         Caption         =   "Sell"
         Height          =   495
         Left            =   -72600
         TabIndex        =   9
         Top             =   3120
         Width           =   1815
      End
      Begin VB.TextBox Sell_Account 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   -72600
         TabIndex        =   5
         Top             =   720
         Width           =   3015
      End
      Begin VB.TextBox Sell_Stock 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   -72600
         TabIndex        =   6
         Top             =   1200
         Width           =   3015
      End
      Begin VB.TextBox Sell_Shares 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   -72600
         TabIndex        =   7
         Top             =   1680
         Width           =   3015
      End
      Begin VB.TextBox Sell_Price 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   -72600
         TabIndex        =   8
         Top             =   2160
         Width           =   3015
      End
      Begin VB.CommandButton Purchase 
         Caption         =   "Purchase"
         Height          =   495
         Left            =   2400
         TabIndex        =   4
         Top             =   3120
         Width           =   1815
      End
      Begin VB.TextBox Purchase_Account 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   2400
         TabIndex        =   0
         Top             =   720
         Width           =   3015
      End
      Begin VB.TextBox Purchase_Stock 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   2400
         TabIndex        =   1
         Top             =   1200
         Width           =   3015
      End
      Begin VB.TextBox Purchase_Shares 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   2400
         TabIndex        =   2
         Top             =   1680
         Width           =   3015
      End
      Begin VB.TextBox Purchase_Price 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   2400
         TabIndex        =   3
         Top             =   2160
         Width           =   3015
      End
      Begin VB.Label Commission_label 
         Caption         =   "Commission"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -74760
         TabIndex        =   21
         Top             =   720
         Width           =   2055
      End
      Begin VB.Label Sell_Account_label 
         Caption         =   "Account Number"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -74760
         TabIndex        =   18
         Top             =   720
         Width           =   2055
      End
      Begin VB.Label Sell_Stock_label 
         Caption         =   "Stock"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -74760
         TabIndex        =   17
         Top             =   1200
         Width           =   2055
      End
      Begin VB.Label Sell_Shares_label 
         Caption         =   "Shares"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -74760
         TabIndex        =   16
         Top             =   1680
         Width           =   2055
      End
      Begin VB.Label Sell_Price_label 
         Caption         =   "Price"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -74760
         TabIndex        =   15
         Top             =   2160
         Width           =   2055
      End
      Begin VB.Label Purchase_Account_label 
         Caption         =   "Account Number"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   14
         Top             =   720
         Width           =   2055
      End
      Begin VB.Label Purchase_Stock_label 
         Caption         =   "Stock"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   1200
         Width           =   2055
      End
      Begin VB.Label Purchase_Shares_label 
         Caption         =   "Shares"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   12
         Top             =   1680
         Width           =   2055
      End
      Begin VB.Label Purchase_Price_label 
         Caption         =   "Price"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   2160
         Width           =   2055
      End
   End
End
Attribute VB_Name = "VB_container_"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private CPP_component As CPP_COMPONENTLib.CStock

Private Sub Purchase_Click()
       
    Dim account As Long
    Dim stock As String
    Dim shares As Long
    Dim price As Double
    Dim message

    account = CLng(Purchase_Account.Text)
    stock = CStr(Purchase_Stock.Text)
    shares = CLng(Purchase_Shares.Text)
    price = CDbl(Purchase_Price.Text)
    
    ProgressBar1.Value = 20
    
    ' Call C++ component's IStock::Buy interface
    ' implemented by CStock::Buy
    CPP_component.Buy account, stock, shares, price
    
    ProgressBar1.Value = 60
    ProgressBar1.Value = 100
    message = MsgBox("Purchase Complete", vbExclamation, "Stock Transactions")
    ProgressBar1.Value = 0

End Sub

Private Sub Sell_Click()
    
    Dim account As Long
    Dim stock As String
    Dim shares As Long
    Dim price As Double
    Dim message
    
    account = CLng(Sell_Account.Text)
    stock = CStr(Sell_Stock.Text)
    shares = CLng(Sell_Shares.Text)
    price = CDbl(Sell_Price.Text)
    
    ProgressBar1.Value = 20
    ' Call C++ component's IStock::Sell interface
    ' implemented by CStock::Sell
    CPP_component.Sell account, stock, shares, price
    
    ProgressBar1.Value = 60
    ProgressBar1.Value = 100
    message = MsgBox("Sale Complete", vbExclamation, "Stock Transactions")
    ProgressBar1.Value = 0

End Sub

Private Sub Get_Commission_Click()
    ' Call C++ component's IStock::Commission interface
    ' implemented by CStock::get_Commission
   Commission = CPP_component.Commission
End Sub

Private Sub Form_Load()
    ' Call C++ component's CStock constructor.
    Set CPP_component = New CPP_COMPONENTLib.CStock
End Sub

Private Sub SSTab1_DblClick()

End Sub
