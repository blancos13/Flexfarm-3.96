object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'FlexFarm Server'
  ClientHeight = 355
  ClientWidth = 523
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 19
  object ListView1: TListView
    Left = 8
    Top = 8
    Width = 321
    Height = 345
    Columns = <
      item
        AutoSize = True
        Caption = 'username'
      end
      item
        AutoSize = True
        Caption = 'password'
      end>
    MultiSelect = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object Edit1: TEdit
    Left = 335
    Top = 8
    Width = 173
    Height = 27
    TabOrder = 1
    TextHint = 'Username'
  end
  object Edit2: TEdit
    Left = 335
    Top = 35
    Width = 173
    Height = 27
    PasswordChar = '*'
    TabOrder = 2
    TextHint = 'Password'
  end
  object Button1: TButton
    Left = 335
    Top = 68
    Width = 75
    Height = 25
    Caption = 'Add'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 416
    Top = 68
    Width = 92
    Height = 25
    Caption = 'Remove'
    TabOrder = 4
    OnClick = Button2Click
  end
  object IdTCPServer1: TIdTCPServer
    Active = True
    Bindings = <>
    DefaultPort = 1337
    OnExecute = IdTCPServer1Execute
    Left = 424
    Top = 304
  end
end
