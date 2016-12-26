// IMG Pro v1.4
// Coded by LOD (Usov Alexey)
// mail: imgpro@rambler.ru
// http://github.com/imgpro
// http://vk.com/id58933402
// http://vk.com/public24609835
// Copyright (C) 2007-2016 LOD (Usov Alexey)

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::MemoLinksKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==VK_ESCAPE) ButtonOK->Click();
    if(Key=='A' && Shift==TShiftState()<<ssCtrl) MemoLinks->SelectAll();
}
//---------------------------------------------------------------------------

