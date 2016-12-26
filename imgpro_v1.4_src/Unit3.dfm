object Settings: TSettings
  Left = 1235
  Top = 238
  AutoScroll = False
  Caption = 'IMG Pro v1.4 - Settings'
  ClientHeight = 412
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnMouseMove = FormMouseMove
  OnShow = FormShow
  DesignSize = (
    624
    412)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 224
    Width = 576
    Height = 161
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    WordWrap = True
  end
  object usingGapsCh: TCheckBox
    Left = 24
    Top = 16
    Width = 297
    Height = 17
    Caption = #1047#1072#1087#1099#1089#1099#1074#1072#1090#1100' '#1092#1072#1081#1083#1099' '#1074' '#1089#1074#1086#1073#1086#1076#1085#1099#1077' '#1091#1095#1072#1089#1090#1082#1080' IMG-'#1072#1088#1093#1080#1074#1072
    ParentShowHint = False
    ShowHint = False
    TabOrder = 0
    OnMouseMove = FormMouseMove
  end
  object writeZerosCh: TCheckBox
    Left = 24
    Top = 88
    Width = 313
    Height = 17
    Caption = #1047#1072#1087#1086#1083#1085#1103#1090#1100' '#1085#1091#1083#1103#1084#1080' '#1085#1077#1080#1089#1087#1086#1083#1100#1079#1091#1077#1084#1099#1077' '#1091#1095#1072#1089#1090#1082#1080' IMG-'#1072#1088#1093#1080#1074#1072
    ParentShowHint = False
    ShowHint = False
    TabOrder = 3
    OnMouseMove = FormMouseMove
  end
  object overwriteNamesCh: TCheckBox
    Left = 24
    Top = 112
    Width = 257
    Height = 17
    Caption = #1055#1077#1088#1077#1079#1072#1087#1080#1089#1099#1074#1072#1090#1100' '#1080#1084#1077#1085#1072' '#1079#1072#1084#1077#1085#1103#1077#1084#1099#1093' '#1092#1072#1081#1083#1086#1074
    ParentShowHint = False
    ShowHint = False
    TabOrder = 4
    OnMouseMove = FormMouseMove
  end
  object shrinkFilesCh: TCheckBox
    Left = 24
    Top = 40
    Width = 417
    Height = 17
    Caption = 
      #1059#1084#1077#1085#1100#1096#1072#1090#1100' '#1088#1072#1079#1084#1077#1088' '#1079#1072#1084#1077#1085#1103#1077#1084#1086#1075#1086' '#1092#1072#1081#1083#1072', '#1077#1089#1083#1080' '#1085#1086#1074#1099#1081' '#1092#1072#1081#1083' '#1084#1077#1085#1100#1096#1077' '#1089#1090#1072#1088#1086 +
      #1075#1086
    ParentShowHint = False
    ShowHint = False
    TabOrder = 1
    OnMouseMove = FormMouseMove
  end
  object SaveWindowPositionCh: TCheckBox
    Left = 24
    Top = 168
    Width = 169
    Height = 17
    Caption = #1057#1086#1093#1088#1072#1085#1103#1090#1100' '#1087#1086#1083#1086#1078#1077#1085#1080#1077' '#1086#1082#1085#1072
    ParentShowHint = False
    ShowHint = False
    TabOrder = 8
    OnMouseMove = FormMouseMove
  end
  object ButtonOK: TButton
    Left = 232
    Top = 376
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 11
    OnClick = ButtonOKClick
  end
  object ButtonCancel: TButton
    Left = 320
    Top = 376
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 12
  end
  object ButtonDef: TButton
    Left = 24
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Default'
    TabOrder = 5
    OnClick = ButtonDefClick
  end
  object ButtonTool: TButton
    Left = 120
    Top = 136
    Width = 129
    Height = 25
    Caption = 'like IMG Tools v2.0'
    TabOrder = 6
    OnClick = ButtonToolClick
  end
  object ButtonCrazy: TButton
    Left = 272
    Top = 136
    Width = 201
    Height = 25
    Caption = 'like GTA: SA Crazy IMG Editor v1.0'
    TabOrder = 7
    OnClick = ButtonCrazyClick
  end
  object zeroAdditionCh: TCheckBox
    Left = 24
    Top = 64
    Width = 249
    Height = 17
    Caption = #1044#1086#1087#1086#1083#1085#1103#1090#1100' '#1092#1072#1081#1083#1099' '#1085#1091#1083#1103#1084#1080' ('#1088#1077#1082#1086#1084#1077#1085#1076#1091#1077#1090#1089#1103'!)'
    TabOrder = 2
    OnMouseMove = FormMouseMove
  end
  object SaveWindowSizeCh: TCheckBox
    Left = 24
    Top = 192
    Width = 153
    Height = 17
    Caption = #1057#1086#1093#1088#1072#1085#1103#1090#1100' '#1088#1072#1079#1084#1077#1088#1099' '#1086#1082#1085#1072
    TabOrder = 9
    OnMouseMove = FormMouseMove
  end
  object ButtonIMG: TButton
    Left = 208
    Top = 176
    Width = 225
    Height = 25
    Caption = #1040#1089#1089#1086#1094#1080#1080#1088#1086#1074#1072#1090#1100' '#1089' IMG '#1092#1072#1081#1083#1072#1084#1080
    TabOrder = 10
    OnClick = ButtonIMGClick
  end
end
