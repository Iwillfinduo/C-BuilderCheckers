object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Main Menu'
  ClientHeight = 509
  ClientWidth = 321
  Color = clWindow
  Constraints.MaxHeight = 548
  Constraints.MaxWidth = 337
  Constraints.MinHeight = 548
  Constraints.MinWidth = 337
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -33
  Font.Name = 'Helvetica Light'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 40
  object Label1: TLabel
    Left = 80
    Top = 48
    Width = 167
    Height = 56
    Caption = #1064#1072#1096#1082#1080
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlack
    Font.Height = -47
    Font.Name = 'Helvetica Bold'
    Font.Style = []
    ParentFont = False
  end
  object Shape1: TShape
    Left = 96
    Top = 110
    Width = 65
    Height = 65
    Brush.Color = clBlack
  end
  object Shape2: TShape
    Left = 160
    Top = 110
    Width = 65
    Height = 65
  end
  object Shape3: TShape
    Left = 96
    Top = 110
    Width = 65
    Height = 65
    Brush.Style = bsClear
    Pen.Color = clWhite
    Shape = stCircle
  end
  object Shape4: TShape
    Left = 104
    Top = 122
    Width = 49
    Height = 43
    Pen.Color = clWhite
    Shape = stCircle
  end
  object NewGameBtn: TButton
    Left = 72
    Top = 184
    Width = 185
    Height = 49
    Caption = #1053#1086#1074#1072#1103' '#1080#1075#1088#1072
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Helvetica Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = NewGameBtnClick
  end
  object LoadBtn: TButton
    Left = 72
    Top = 247
    Width = 185
    Height = 49
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Helvetica Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = LoadBtnClick
  end
  object RulesBtn: TButton
    Left = 72
    Top = 312
    Width = 185
    Height = 49
    Caption = #1055#1088#1072#1074#1080#1083#1072
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Helvetica Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = RulesBtnClick
  end
  object AboutBtn: TButton
    Left = 72
    Top = 376
    Width = 185
    Height = 49
    Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Helvetica Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = AboutBtnClick
  end
  object ExitBtn: TButton
    Left = 72
    Top = 440
    Width = 185
    Height = 49
    Caption = #1042#1099#1093#1086#1076
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Helvetica Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = ExitBtnClick
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'check'
    Filter = 'Checkers Save file .check|*.check'
    Title = #1047#1072#1075#1088#1091#1079#1082#1072' '#1080#1075#1088#1099
    Left = 280
    Top = 320
  end
end
