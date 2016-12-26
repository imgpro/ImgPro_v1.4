object Form1: TForm1
  Left = 389
  Top = 138
  AutoScroll = False
  Caption = 'IMG Pro v1.4'
  ClientHeight = 412
  ClientWidth = 624
  Color = clActiveBorder
  Constraints.MinHeight = 400
  Constraints.MinWidth = 200
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  OnShow = FormShow
  DesignSize = (
    624
    412)
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonAdd: TButton
    Left = 536
    Top = 32
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Addd...'
    TabOrder = 1
    OnClick = ButtonAddClick
  end
  object FilesLV: TListView
    Left = 0
    Top = 0
    Width = 521
    Height = 345
    Anchors = [akLeft, akTop, akRight, akBottom]
    Columns = <
      item
        Caption = 'File Name'
        Width = 128
      end
      item
        Caption = 'Size'
        Width = 60
      end
      item
        Caption = 'Type'
        Width = 40
      end
      item
        AutoSize = True
        Caption = 'Path'
      end>
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    HideSelection = False
    MultiSelect = True
    ReadOnly = True
    ParentFont = False
    TabOrder = 0
    ViewStyle = vsReport
    OnChanging = FilesLVChanging
    OnColumnClick = FilesLVColumnClick
    OnCompare = FilesLVCompare
    OnKeyDown = FilesLVKeyDown
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 352
    Width = 609
    Height = 52
    Anchors = [akLeft, akRight, akBottom]
    Caption = '*.IMG file'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    DesignSize = (
      609
      52)
    object ImgPathE: TEdit
      Left = 8
      Top = 18
      Width = 497
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object ButtonBrowseImgFile: TButton
      Left = 520
      Top = 17
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Browse...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = ButtonBrowseImgFileClick
    end
  end
  object ButtonDelete: TButton
    Left = 536
    Top = 72
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Delete'
    TabOrder = 2
    OnClick = ButtonDeleteClick
  end
  object ButtonAbout: TButton
    Left = 613
    Top = 0
    Width = 11
    Height = 17
    Hint = 'About'
    Anchors = [akTop, akRight]
    Caption = '?'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 10
    OnClick = ButtonAboutClick
  end
  object ButtonExtract: TButton
    Left = 536
    Top = 168
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Extract...'
    Enabled = False
    TabOrder = 3
    OnClick = ButtonExtractClick
  end
  object ProgressBar1: TProgressBar
    Left = 531
    Top = 248
    Width = 83
    Height = 9
    Anchors = [akTop, akRight]
    Min = 0
    Max = 1
    Step = 1
    TabOrder = 5
  end
  object ButtonReplace: TButton
    Left = 536
    Top = 208
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Replace'
    Enabled = False
    TabOrder = 4
    OnClick = ButtonReplaceClick
  end
  object ChBxTop: TCheckBox
    Left = 536
    Top = 0
    Width = 58
    Height = 17
    Hint = 'Always-On-Top'
    Anchors = [akTop, akRight]
    Caption = 'On Top'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 8
    OnClick = ChBxTopClick
  end
  object ButtonRebuild: TButton
    Left = 536
    Top = 272
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Rebuild'
    TabOrder = 6
    OnClick = ButtonRebuildClick
  end
  object ButtonSettings: TButton
    Left = 600
    Top = 0
    Width = 13
    Height = 17
    Hint = 'Settings'
    Anchors = [akTop, akRight]
    Caption = '*'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 9
    OnClick = ButtonSettingsClick
  end
  object AddOD: TOpenDialog
    Filter = 
      'GTA Car Files(*.dff;*.txd;*.ifp)|*.dff;*.txd;*.ifp|GTA Textures(' +
      '*.txd)|*.txd|All GTA Files(*.dff;*.txd;*.col;*.ipl;*.ifp;*.scm;*' +
      '.cut;*.dat;*.rrr;*.anm)|*.dff;*.txd;*.col;*.ipl;*.ifp;*.scm;*.cu' +
      't;*.dat;*.rrr;*.anm|All Files(*.*)|*.*'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 424
    Top = 288
  end
  object ImgOD: TOpenDialog
    Filter = 'GTA IMG Arhive (*.img)|*.img'
    Left = 392
    Top = 288
  end
end
