object AboutBox: TAboutBox
  Left = 1026
  Top = 154
  BorderStyle = bsToolWindow
  Caption = 'IMG Pro v1.4 - About'
  ClientHeight = 233
  ClientWidth = 329
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Label3: TLabel
    Left = 16
    Top = 160
    Width = 299
    Height = 16
    Caption = 'Copyright (C) 2007-2016 LOD (Usov Alexey)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 104
    Top = 13
    Width = 120
    Height = 24
    Caption = 'IMG Pro v1.4'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object MemoLinks: TMemo
    Left = 32
    Top = 48
    Width = 265
    Height = 97
    BorderStyle = bsNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clHotLight
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    Lines.Strings = (
      'Author: LOD (Usov Alexey)'
      'E-Mail: imgpro@rambler.ru'
      'http://github.com/imgpro'
      'http://vk.com/id58933402'
      'http://vk.com/public24609835')
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    OnKeyDown = MemoLinksKeyDown
  end
  object ButtonOK: TButton
    Left = 120
    Top = 192
    Width = 89
    Height = 25
    Cancel = True
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
end
