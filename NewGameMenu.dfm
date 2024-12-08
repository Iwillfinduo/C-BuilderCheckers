object Form2: TForm2
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'New Game'
  ClientHeight = 322
  ClientWidth = 418
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 40
    Top = 48
    Width = 336
    Height = 38
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1088#1077#1078#1080#1084' '#1080#1075#1088#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -33
    Font.Name = 'Helvetica'
    Font.Style = []
    ParentFont = False
  end
  object ComboBox1: TComboBox
    Left = 40
    Top = 136
    Width = 336
    Height = 32
    Style = csDropDownList
    BiDiMode = bdLeftToRight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Helvetica Light'
    Font.Style = []
    ItemHeight = 24
    ItemIndex = 0
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 0
    Text = #1048#1075#1088#1072' '#1073#1077#1079' '#1090#1072#1081#1084#1077#1088#1072
    Items.Strings = (
      #1048#1075#1088#1072' '#1073#1077#1079' '#1090#1072#1081#1084#1077#1088#1072
      #1041#1083#1080#1094' (5 '#1084#1080#1085#1091#1090')'
      #1041#1099#1089#1090#1088#1099#1077' '#1096#1072#1096#1082#1080' (14 '#1084#1080#1085#1091#1090')'
      #1050#1083#1072#1089#1089#1080#1095#1077#1089#1082#1080#1077' (45 '#1084#1080#1085#1091#1090')')
  end
  object BitBtn1: TBitBtn
    Left = 136
    Top = 240
    Width = 121
    Height = 33
    Caption = #1053#1086#1074#1072#1103' '#1080#1075#1088#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Helvetica Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = BitBtn1Click
  end
end
