static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData){
    TCHAR szPath[_MAX_PATH];
    switch (uMsg) {
        case BFFM_INITIALIZED:
            if (lpData) SendMessage(hWnd,BFFM_SETSELECTION,TRUE,lpData);
            break;
        case BFFM_SELCHANGED:
            SHGetPathFromIDList(LPITEMIDLIST(lParam),szPath);
            SendMessage(hWnd, BFFM_SETSTATUSTEXT, NULL, LPARAM(szPath));
            break;
    }
    return 0;
}

bool SelectFolder(String &Path, String Title="", HWND hWndOwner=NULL, bool NewStyle=false)
{
    LPMALLOC pMalloc;
    if (SHGetMalloc(&pMalloc) != NOERROR) return false;

    BROWSEINFO bi;
    ZeroMemory(&bi,sizeof bi);
    bi.ulFlags   = BIF_RETURNONLYFSDIRS;
    if(NewStyle) bi.ulFlags |= BIF_NEWDIALOGSTYLE;

    // дескриптор окна-владельца диалога
    bi.hwndOwner = hWndOwner;

    // добавление заголовка к диалогу
    bi.lpszTitle = Title.c_str();

    // отображение текущего каталога
    bi.lpfn      = BrowseCallbackProc;
    bi.ulFlags  |= BIF_STATUSTEXT;
    
    // установка каталога по умолчанию
    char buffer[MAX_PATH];
    strncpy(buffer,Path.c_str(),MAX_PATH);
    bi.lParam    = LPARAM(buffer);

    bool result = false;
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL) {
        if (SHGetPathFromIDList(pidl,buffer)){
            result = true;
            Path = buffer;
        }
        pMalloc->Free(pidl);
    }
    pMalloc->Release();
    
    return result;
}

