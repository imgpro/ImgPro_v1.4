//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "img_stl.h"
#include <Math.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TButton *ButtonAdd;
    TButton *ButtonDelete;
    TButton *ButtonExtract;
    TButton *ButtonReplace;
    TProgressBar *ProgressBar1;
    TListView *FilesLV;
    TGroupBox *GroupBox1;
    TEdit *ImgPathE;
    TButton *ButtonBrowseImgFile;
    TCheckBox *ChBxTop;
    TButton *ButtonAbout;
    TOpenDialog *AddOD;
    TOpenDialog *ImgOD;
    TButton *ButtonRebuild;
    TButton *ButtonSettings;
    void __fastcall ButtonAddClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonDeleteClick(TObject *Sender);
    void __fastcall ButtonAboutClick(TObject *Sender);
    void __fastcall ChBxTopClick(TObject *Sender);
    void __fastcall ButtonBrowseImgFileClick(TObject *Sender);
    void __fastcall FilesLVColumnClick(TObject *Sender,
          TListColumn *Column);
    void __fastcall FilesLVCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);
    void __fastcall FilesLVKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FilesLVChanging(TObject *Sender, TListItem *Item,
          TItemChange Change, bool &AllowChange);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ButtonExtractClick(TObject *Sender);
    void __fastcall ButtonReplaceClick(TObject *Sender);
    void __fastcall ButtonRebuildClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall ButtonSettingsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    bool AddToList(const String &FileName);
    void WmDropFiles(TWMDropFiles& Message);
    void WmMoving(TMessage &Message);
    BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(WM_DROPFILES,TWMDropFiles,WmDropFiles)
    MESSAGE_HANDLER(WM_MOVING, TMessage, WmMoving);
	END_MESSAGE_MAP(TForm);
    void EnableButtons(bool Enabled);
    bool OpenImgArchive(ImgFile &Img, String FileName, bool write=false);
    void Extract();
    void FilesLVToStrings(TStrings *Strings);
    void Replace(TStringList *Files);
    void Rebuild();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern bool usingGaps;
extern bool shrinkFiles;
extern bool zeroAddition;
extern bool writeZeros;
extern bool overwriteNames;
extern bool SaveWindowPosition;
extern bool SaveWindowSize;
//---------------------------------------------------------------------------
#endif

