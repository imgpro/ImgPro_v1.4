//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSettings : public TForm
{
__published:	// IDE-managed Components
    TCheckBox *usingGapsCh;
    TCheckBox *writeZerosCh;
    TCheckBox *overwriteNamesCh;
    TCheckBox *shrinkFilesCh;
    TCheckBox *SaveWindowPositionCh;
    TLabel *Label1;
    TButton *ButtonOK;
    TButton *ButtonCancel;
    TButton *ButtonDef;
    TButton *ButtonTool;
    TButton *ButtonCrazy;
    TCheckBox *zeroAdditionCh;
        TCheckBox *SaveWindowSizeCh;
    TButton *ButtonIMG;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall ButtonDefClick(TObject *Sender);
    void __fastcall ButtonToolClick(TObject *Sender);
    void __fastcall ButtonCrazyClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOKClick(TObject *Sender);
    void __fastcall ButtonIMGClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettings *Settings;
//---------------------------------------------------------------------------
#endif
