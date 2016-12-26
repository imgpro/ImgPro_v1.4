// IMG Pro v1.4
// Coded by LOD (Usov Alexey)
// mail: imgpro@rambler.ru
// http://github.com/imgpro
// http://vk.com/id58933402
// http://vk.com/public24609835
// Copyright (C) 2007-2016 LOD (Usov Alexey)

//---------------------------------------------------------------------------

#define NO_WIN32_LEAN_AND_MEAN
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "browse_folder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
const char PRG_NAME[] = "IMG Pro";  
const char INI_FILE[] = "imgpro14.ini";
bool ButtonsEnabled = true;
String ExtractPath;    
int sortby = 0;
TRect bounds(0,0,0,0);
extern bool usingGaps       = true;
extern bool shrinkFiles     = true;
extern bool zeroAddition    = true;
extern bool writeZeros      = true;
extern bool overwriteNames  = true;
extern bool SaveWindowPosition  = true;
extern bool SaveWindowSize      = true;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

__int64 GetFileSize(LPCTSTR lpFileName){
    _WIN32_FILE_ATTRIBUTE_DATA FileInformation;
    GetFileAttributesEx(lpFileName,GetFileExInfoStandard,&FileInformation);
    return (__int64)FileInformation.nFileSizeHigh<<32 | FileInformation.nFileSizeLow;
}

bool IsGtaFile(const String &FileName){
    String s = ExtractFileExt(FileName).LowerCase();
    if(s == ".dff")return true;
    if(s == ".txd")return true;
    if(s == ".col")return true;
    if(s == ".ipl")return true;
    if(s == ".ifp")return true;
    if(s == ".scm")return true;
    if(s == ".cut")return true;
    if(s == ".dat")return true;
    if(s == ".rrr")return true;
    if(s == ".anm")return true;
    return false;
}

bool TForm1::AddToList(const String &FileName)
{
    if(!FileExists(FileName) && DirectoryExists(FileName)){
        ExtractPath = FileName;
        return true;
    }
    if(ExtractFileExt(FileName).LowerCase()==".img"){
        ImgPathE->Text = FileName;
        return true;
    }
    if(!IsGtaFile(FileName)){
        String s = FileName + "\n\nне является файлом GTA\nдобавить его в список?";
        int r = MessageBox(Handle, s.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONQUESTION|MB_YESNOCANCEL);
        if(r == IDNO) return true;
        if(r == IDCANCEL) return false;
    }

    TListItem *Item = FilesLV->Items->Add();
    Item->Caption = ExtractFileName(FileName);

    String s;
    int size = GetFileSize(FileName.c_str());
    Item->ImageIndex = size;
    if(size<1024) s = String(size); else s = String((size+1023)/1024) + " kb";
    Item->SubItems->Add(s);
    Item->Data = (void*)size;

    Item->SubItems->Add(ExtractFileExt(FileName).SubString(2,MAX_PATH).UpperCase());
    Item->SubItems->Add(ExtractFilePath(FileName));
    return true;
}

void __fastcall TForm1::ButtonAddClick(TObject *Sender)
{
    if(!AddOD->Execute()) return;
    for(int i=0; (i<AddOD->Files->Count) && AddToList(AddOD->Files->Strings[i]); i++);  //short-circuit evaluation
}
//---------------------------------------------------------------------------

void TForm1::WmDropFiles(TWMDropFiles& Message)
{
	HDROP drop_handle=(HDROP)Message.Drop;
	char fname[MAX_PATH];
	int filenum=DragQueryFile(drop_handle,-1,NULL,NULL);
	for(int i=0;i<filenum;i++)
	{
		DragQueryFile(drop_handle,i,fname,MAX_PATH);
		if(!AddToList(fname)) break;
	}
	DragFinish(drop_handle);
}

void __fastcall TForm1::FormShow(TObject *Sender)
{
    DragAcceptFiles(Handle,true);    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonDeleteClick(TObject *Sender)
{
    FilesLV->DeleteSelected();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonAboutClick(TObject *Sender)
{
    //MessageBox(0,"Эту прогу сделал LOD    E-mail: imgpro@rambler.ru","About",0);
    //imgpro@rambler.ru
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChBxTopClick(TObject *Sender)
{
    FormStyle = ChBxTop->Checked ? fsStayOnTop : fsNormal;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonBrowseImgFileClick(TObject *Sender)
{                                   
    ImgOD->InitialDir = ExtractFilePath(ImgPathE->Text);
    if(ImgOD->Execute()) ImgPathE->Text = ImgOD->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FilesLVColumnClick(TObject *Sender,
      TListColumn *Column)
{
    sortby = Column->Index;
    FilesLV->AlphaSort();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FilesLVCompare(TObject *Sender, TListItem *Item1,
      TListItem *Item2, int Data, int &Compare)
{
    String A = sortby ? Item1->SubItems->Strings[sortby-1] : Item1->Caption;
    String B = sortby ? Item2->SubItems->Strings[sortby-1] : Item2->Caption;
    if(sortby == 1) Compare = Sign((int)Item1->Data - (int)Item2->Data);
    else Compare = stricmp(A.c_str(),B.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FilesLVKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==VK_DELETE) ButtonDelete->Click();
    if(Key==VK_INSERT) ButtonAdd->Click();
    if(Shift==TShiftState()<<ssCtrl && Key=='A') FilesLV->SelectAll();
}
//---------------------------------------------------------------------------

void TForm1::EnableButtons(bool Enabled){
    ButtonsEnabled = Enabled;
    ButtonExtract->Enabled  = ButtonsEnabled && FilesLV->Items->Count>0;
    ButtonReplace->Enabled  = ButtonsEnabled && FilesLV->Items->Count>0;
    ButtonAdd->Enabled      = ButtonsEnabled;
    ButtonDelete->Enabled   = ButtonsEnabled;
    ButtonRebuild->Enabled  = ButtonsEnabled;
    ButtonSettings->Enabled = ButtonsEnabled;
}

void __fastcall TForm1::FilesLVChanging(TObject *Sender, TListItem *Item,
      TItemChange Change, bool &AllowChange)
{
    EnableButtons(ButtonsEnabled);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    TStringList *List = new TStringList;  
    List->Values["usingGaps"]       = (int)usingGaps;
    List->Values["shrinkFiles"]     = (int)shrinkFiles;
    List->Values["zeroAddition"]    = (int)zeroAddition;
    List->Values["writeZeros"]      = (int)writeZeros;
    List->Values["overwriteNames"]  = (int)overwriteNames;
    List->Values["ImgPath"] = ImgPathE->Text;
    List->Values["AddPath"] = AddOD->FileName=="" ? AddOD->InitialDir : ExtractFilePath(AddOD->FileName);
    List->Values["ExtPath"] = ExtractPath;
    List->Values["TopMost"] = (int)ChBxTop->Checked;
    List->Values["Color"]   = Color;
    if(bounds.Width()>0){
        if(SaveWindowPosition){
            List->Values["Left"]    = bounds.Left;
            List->Values["Top"]     = bounds.Top;
        }
        if(SaveWindowSize){ 
            List->Values["Width"]   = bounds.Width();
            List->Values["Height"]  = bounds.Height();
        }
    }
    List->Values["WindowState"]         = WindowState;
    List->Values["SaveWindowPosition"]  = (int)SaveWindowPosition;
    List->Values["SaveWindowSize"]      = (int)SaveWindowSize;
    try{ List->SaveToFile(ExtractFilePath(Application->ExeName)+INI_FILE); }
    catch (Exception &exception){ Application->ShowException(&exception); }
    delete List;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    if(FileExists(ExtractFilePath(Application->ExeName)+INI_FILE)){
        TStringList *List = new TStringList;
        List->LoadFromFile(ExtractFilePath(Application->ExeName)+INI_FILE);
        usingGaps       = StrToIntDef(List->Values["usingGaps"],        usingGaps);
        shrinkFiles     = StrToIntDef(List->Values["shrinkFiles"],      shrinkFiles);
        zeroAddition    = StrToIntDef(List->Values["zeroAddition"],     zeroAddition);
        writeZeros      = StrToIntDef(List->Values["writeZeros"],       writeZeros);
        overwriteNames  = StrToIntDef(List->Values["overwriteNames"],   overwriteNames);
        ImgPathE->Text      = List->Values["ImgPath"];
        AddOD->InitialDir   = List->Values["AddPath"];
        ExtractPath         = List->Values["ExtPath"];
        ChBxTop->Checked    = List->Values["TopMost"].Trim() == "1";
        Color               = (TColor)StrToIntDef(List->Values["Color"],Color);
        SaveWindowPosition  = StrToIntDef(List->Values["SaveWindowPosition"],   SaveWindowPosition);
        SaveWindowSize      = StrToIntDef(List->Values["SaveWindowSize"],       SaveWindowSize);
        if(SaveWindowPosition){
            Position    = poDesigned;
            Left        = StrToIntDef(List->Values["Left"],     Left);
            Top         = StrToIntDef(List->Values["Top"],      Top);
        }
        if(SaveWindowSize){
            Width       = StrToIntDef(List->Values["Width"],    Width);
            Height      = StrToIntDef(List->Values["Height"],   Height);
        }
        WindowState = (TWindowState)StrToIntDef(List->Values["WindowState"],WindowState);
        delete List;
    }
    if(ExtractFileExt(ParamStr(1)).UpperCase() == ".IMG") ImgPathE->Text = ParamStr(1);
}
//---------------------------------------------------------------------------

String AnsiLastError(){
    char* cstr;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR)&cstr, 0, NULL);
    String res = cstr;
    LocalFree(cstr);
    return res;
}
String LastErrorMsg(){ return String().sprintf("Error %d: ", GetLastError()) + AnsiLastError(); }

bool TForm1::OpenImgArchive(ImgFile &Img, String FileName, bool write){
    if(!Img.open(FileName.c_str(),write)){
        String msg;
        msg.sprintf("Не удалось открыть IMG архив\n%s\n\nОшибка при работе с файлом\n%s\n%s", FileName.c_str(), Img.lastname.c_str(), LastErrorMsg().c_str());
        MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONERROR);
        return false;
    }
    Img.usingGaps = usingGaps;
    Img.shrinkFiles = shrinkFiles;
    Img.zeroAddition = zeroAddition;
    Img.writeZeros = writeZeros;
    Img.overwriteNames = overwriteNames;
    return true;
}

void TForm1::Extract(){
    if(!SelectFolder(ExtractPath,"Выберите папку для извлечения файлов",Handle)) return;
    ImgFile Img;
    if(!OpenImgArchive(Img,ImgPathE->Text)) return;
    int count=0;
    ProgressBar1->Position = 0;
    ProgressBar1->Max = FilesLV->Items->Count;
    for(int i=0; i<FilesLV->Items->Count; i++){
        ProgressBar1->Position = i;
        String src = FilesLV->Items->Item[i]->Caption;
        ImgItem* rec = Img.fileByName(src.c_str());
        if(!rec) continue;
        String dest = IncludeTrailingBackslash(ExtractPath) + String(rec->getName().c_str());
        if(FileExists(dest)){
            _WIN32_FILE_ATTRIBUTE_DATA finf;
            SYSTEMTIME st;
            ZeroMemory(&finf,sizeof finf);
            GetFileAttributesEx(dest.c_str(),GetFileExInfoStandard,&finf);
            FileTimeToSystemTime(&finf.ftLastWriteTime,&st);
            String date,msg;
            date.sprintf("%02d.%02d.%02d  %02d:%02d:%02d",st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);
            msg.sprintf("\"%s\" уже существует.\n\nЗаменить имеющийся файл\nразмер: %db\nдата изменения: %s\n\nИзвлекаемым файлом?\nразмер: %db",
                dest.c_str(), finf.nFileSizeLow, date.c_str(), rec->size());
            int res = MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONQUESTION|MB_YESNOCANCEL);
            if(res == IDNO) continue;
            if(res != IDYES) break;
        }
        while(true){
            if(Img.extract(rec,dest.c_str())){
                count++;
                break;
            }
            Img.clearStreams();
            String msg;
            msg.sprintf("Не удалось сохранить файл\n%s\n\nОшибка при работе с файлом\n%s\n%s", dest.c_str(), Img.lastname.c_str(), LastErrorMsg().c_str());
            int res = MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONWARNING|MB_CANCELTRYCONTINUE);
            if(res == IDTRYAGAIN) continue;
            if(res == IDCONTINUE) break;
            return;
        }
    }
    ProgressBar1->Position = ProgressBar1->Max;
    MessageBox(Handle, String().sprintf("Извлечено: %d",count).c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONINFORMATION);
}

void __fastcall TForm1::ButtonExtractClick(TObject *Sender)
{
    EnableButtons(false);
    Extract();
    EnableButtons(true);
}
//---------------------------------------------------------------------------

void TForm1::FilesLVToStrings(TStrings *Strings){
    TListItems *Items = FilesLV->Items;
    for(int i=0; i < Items->Count; i++){
        TListItem *Item = Items->Item[i];
        String Path = Item->SubItems->Strings[2]+Item->Caption;
        Strings->AddObject(Path,Item);
    }
}

void TForm1::Replace(TStringList *Files){
    if(MessageBox(Handle, "Заменить?", PRG_NAME, MB_TASKMODAL|MB_ICONQUESTION|MB_YESNO)!=IDYES) return;
    ImgFile Img;
    if(!OpenImgArchive(Img,ImgPathE->Text,true)) return;
    int replaced=0, added=0;
    ProgressBar1->Max = Files->Count;
    ProgressBar1->Position = 0;
    for(int i=0; i<Files->Count; i++){
        ProgressBar1->Position = i;
        String src = Files->Strings[i];
        String dest = ExtractFileName(src);
        ImgItem *rec = Img.fileByName(dest.c_str());
        while(true){
            if( Img.import(dest.c_str(), src.c_str()) ){
                (rec ? replaced : added)++;
                ((TListItem*)Files->Objects[i])->Delete();
                Application->ProcessMessages();
                break;
            }
            Img.clearStreams();
            String msg;
            msg.sprintf("Не удалось добавить/заменить\n%s\n\nОшибка при работе с файлом\n%s\n%s", src.c_str(), Img.lastname.c_str(), LastErrorMsg().c_str());
            int r = MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONWARNING|MB_CANCELTRYCONTINUE);
            if(r == IDTRYAGAIN) continue;
            if(r == IDCONTINUE) break;
            return;
        }
    }
    ProgressBar1->Position = ProgressBar1->Max;
    String msg = String().sprintf("Завершено\n\nЗаменено: %d\nДобавлено: %d", replaced, added);
    MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONASTERISK);
}

void __fastcall TForm1::ButtonReplaceClick(TObject *Sender)
{
    EnableButtons(false);  
    TStringList *Files = new TStringList;
    FilesLVToStrings(Files);
    Replace(Files);
    delete Files;
    EnableButtons(true);
}
//---------------------------------------------------------------------------

void incProgress(){
    Form1->ProgressBar1->Position++;
    Application->ProcessMessages();
}

void TForm1::Rebuild(){
    String ImgName = ImgPathE->Text;
    String DirName = ChangeFileExt(ImgName,".dir");
    String ImgNameT = ChangeFileExt(ImgName,".temp.img");
    String DirNameT = ChangeFileExt(ImgNameT,".dir");
    String msg = String().sprintf("Пересобрать архив\n\"%s\"?", ImgName.c_str());
    if(MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONQUESTION|MB_YESNO)!=IDYES) return;
    ImgFile Img;
    if(!OpenImgArchive(Img,ImgName)) return;
    ProgressBar1->Position = 0;
    ProgressBar1->Max = Img.files.size();
    int Time = GetTickCount();
    if(!Img.rebuild(ImgNameT.c_str(),incProgress)){  
        msg.sprintf("Не удалось создать архив\n%s\n\nОшибка при работе с файлом\n%s\n%s", ImgNameT.c_str(), Img.lastname.c_str(), LastErrorMsg().c_str());
        MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONERROR);
        return;
    }
    Img.close();
    Time = GetTickCount() - Time;
    if(!MoveFileEx(ImgNameT.c_str(), ImgName.c_str(), MOVEFILE_REPLACE_EXISTING)){
        msg.sprintf("Не удалось заменить\n\"%s\"\nфайлом\n\"%s\"\n\n%s", ImgName.c_str(), ImgNameT.c_str(), LastErrorMsg().c_str());
        MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONERROR);
        return;
    }
    if(Img.fcc!=FCC_VER2) if(!MoveFileEx(DirNameT.c_str(), DirName.c_str(), MOVEFILE_REPLACE_EXISTING)){
        msg.sprintf("Не удалось заменить\n\"%s\"\nфайлом\n\"%s\"\n\n%s", DirName.c_str(), DirNameT.c_str(), LastErrorMsg().c_str());
        MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONERROR);
        return;
    }
    msg.sprintf("Архив пересобран за %.3f сек.", Time/1000.0);
    MessageBox(Handle, msg.c_str(), PRG_NAME, MB_TASKMODAL|MB_ICONINFORMATION);
}

void __fastcall TForm1::ButtonRebuildClick(TObject *Sender)
{          
    EnableButtons(false);
    Rebuild(); 
    EnableButtons(true);  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == VK_F1) ButtonAbout->Click();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
    if(WindowState == wsNormal) bounds = BoundsRect;
}
//---------------------------------------------------------------------------

void TForm1::WmMoving(TMessage &Message){
    if(WindowState == wsNormal) bounds = BoundsRect;
}

void __fastcall TForm1::ButtonSettingsClick(TObject *Sender)
{
    Settings->ShowModal();    
}
//---------------------------------------------------------------------------

