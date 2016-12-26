//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettings *Settings;
//---------------------------------------------------------------------------
__fastcall TSettings::TSettings(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSettings::FormCreate(TObject *Sender)
{
    usingGapsCh->Hint =
        "Запысывать файлы в свободные участки IMG-архива\n\n"
        "Позволяет экономить место на диске.\n\n"
        "Если эта опция выключена, все новые файлы и файлы, размер которых больше имеющихся, будут записываться в конец архива.\n\n"
        "Состояние архива после выполнения пересборки не зависит от этой опции.";

    shrinkFilesCh->Hint =
        "Уменьшать размер заменяемого файла, если новый файл меньше старого\n\n"
        "Если в архиве есть файл размером 8192 байт, и вы заменяете его файлом размером "
        "700 байт, то с данной опцией размер архивного файла будет уменьшен до 2048 байт.\n\n"
        "В любом случае в архив будет записано ровно 700 байт. Что будет находится (нули или мусор) "
        "в оставшихся 7492 или 1348 байтах зависит от следующей опции.\n\n"
        "* в IMG архиве сохраняется не размер файла, а количество блоков (2048 байт), необходимых "
        "для хранения файла, поэтому размер файла выравнивается по размеру блока в бОльшую сторону.";

    zeroAdditionCh->Hint =
        "Дополнять файлы нулями (рекомендуется!)\n\n"
        "При добавлении или замене размер нового файла выравнивается по размеру блока (2048 байт) "
        "в бОльшую сторону. Например, 3000 при выравнивании превратится в 4096.\n\n"
        "Если выключить данную опцию, то в архив будет записано только 3000 байтов, а оставшиеся 1096 байт могут "
        "содержать \"мусор\" - остатки от старых (удалённых или заменённых) файлов, это может привести к ошибкам.\n\n"
        "Включение данной опции гарантирует, что оставшиеся 1096 байт будут содержать нули.";

    writeZerosCh->Hint =
        "Заполнять нулями неиспользуемые участки IMG-архива\n\n"
        "Если вы добавляете файл большего размера чем был, то он будет записан "
        "в новое место архива, старое место можно заполнить нулями или оставить без изменений.\n\n"
        "Если новый файл меньше старого, и при этом выбрано уменьшение размера файла, "
        "то с данной опцией появившийся свободный участок также будет заполнен нулями.";

    overwriteNamesCh->Hint =
        "Перезаписывать имена заменяемых файлов\n\n"
        "Под имя файла отводится 24 байта, с этой опцией при замене файла будет записано имя файла, а оставшиеся байты заполнятся нулями.\n\n"
        "Если, например, имя файла занимало 10 байт, 11-й байт нулевой, а с 12-го по 24-й байты "
        "были ненулевые, то после перезаписи все байты кроме первых десяти будут содержать нули.";

    SaveWindowPositionCh->Hint =
        "Сохранять положение окна\n\n"
        "Если эта опция выключена, окно программы при каждом запуске будет появляться в центре экрана.";

    SaveWindowSizeCh->Hint =
        "Сохранять размеры окна\n\n"
        "Если эта опция выключена, при каждом запуске будут выставляться стандартные размеры окна.";
}
//---------------------------------------------------------------------------
void __fastcall TSettings::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    TWinControl *C = (TWinControl*)Sender;
    Label1->Caption = C->Hint;
}
//---------------------------------------------------------------------------
void __fastcall TSettings::ButtonDefClick(TObject *Sender)
{
    usingGapsCh->Checked        = true;
    shrinkFilesCh->Checked      = true;
    zeroAdditionCh->Checked     = true;
    writeZerosCh->Checked       = true;
    overwriteNamesCh->Checked   = true;
}
//---------------------------------------------------------------------------

void __fastcall TSettings::ButtonToolClick(TObject *Sender)
{
    usingGapsCh->Checked        = false;
    shrinkFilesCh->Checked      = false;
    zeroAdditionCh->Checked     = false;
    writeZerosCh->Checked       = false;
    overwriteNamesCh->Checked   = false;
}
//---------------------------------------------------------------------------

void __fastcall TSettings::ButtonCrazyClick(TObject *Sender)
{
    usingGapsCh->Checked        = false;
    shrinkFilesCh->Checked      = false;
    zeroAdditionCh->Checked     = true;
    writeZerosCh->Checked       = false;
    overwriteNamesCh->Checked   = true;
}
//---------------------------------------------------------------------------

void __fastcall TSettings::FormShow(TObject *Sender)
{
    usingGapsCh->Checked        = usingGaps;
    shrinkFilesCh->Checked      = shrinkFiles;
    zeroAdditionCh->Checked     = zeroAddition;
    writeZerosCh->Checked       = writeZeros;
    overwriteNamesCh->Checked   = overwriteNames;
    SaveWindowPositionCh->Checked   = SaveWindowPosition;
    SaveWindowSizeCh->Checked       = SaveWindowSize;
}
//---------------------------------------------------------------------------

void __fastcall TSettings::ButtonOKClick(TObject *Sender)
{            
    usingGaps = usingGapsCh->Checked;
    shrinkFiles = shrinkFilesCh->Checked;
    zeroAddition = zeroAdditionCh->Checked;
    writeZeros = writeZerosCh->Checked;
    overwriteNames = overwriteNamesCh->Checked;
    SaveWindowPosition = SaveWindowPositionCh->Checked;
    SaveWindowSize = SaveWindowSizeCh->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TSettings::ButtonIMGClick(TObject *Sender)
{
    WinExec(("cmd /c \"ftype GTA_ImgProFile="+ParamStr(0)+" \"%1\"\"").c_str(), SW_HIDE);
    WinExec("cmd /c \"assoc .img=GTA_ImgProFile\"", SW_HIDE);
}
//---------------------------------------------------------------------------

