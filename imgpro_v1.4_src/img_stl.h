// IMG Pro v1.4
// Coded by LOD (Usov Alexey)
// mail: imgpro@rambler.ru
// http://github.com/imgpro
// http://vk.com/id58933402
// http://vk.com/public24609835
// Copyright (C) 2007-2016 LOD (Usov Alexey)

#include "dff_utils.h"
#include <windows.h>

struct ImgItem;
struct ImgFile;

typedef void (*ImgCallbackFun)();

const DWORD FCC_VER2 = 0x32524556;
const DWORD imgBlockSize = 2048;
inline DWORD imgBlocks(DWORD bytes){ return (bytes+imgBlockSize-1)/imgBlockSize; }
inline DWORD imgBytes(DWORD blocks){ return blocks*imgBlockSize; }
inline DWORD imgAlign(DWORD size_pos){ return imgBlocks(size_pos)*imgBlockSize; }

//string("ab\0\0",4) != string("ab\0\0")
//string("ab\0\0",4).size() = 4
//string("ab\0\0").size() = 2
//string( string("ab\0\0",4) ) = 4
//string( string("ab\0\0",4).c_str() ) = 2
//inline string imgKey(const string &name){ return tolower(name.c_str()); }
inline string imgKey(const string &name){ return tolower(name.c_str()).substr(0,24); }

struct ImgItem{
    DWORD offsetB;
    DWORD sizeB;
    char name[24];
    DWORD nextB() const { return offsetB + sizeB; }
    DWORD offset() const { return imgBytes(offsetB); }
    DWORD size() const { return imgBytes(sizeB); }
    void setOffset(DWORD _offset){ offsetB = imgBlocks(_offset); }
    void setSize(DWORD _size){ sizeB = imgBlocks(_size); }
    void setName(const string &_name){ ZeroMemory(name,24); _name.copy(name,24); }
    string getName() const { return string(name,24).c_str(); } //without c_str() getName().size()=24
    string getKey() const { return imgKey(getName()); }
    void go(fstream &fimg) const {
        fimg.seekg(offset());
        fimg.seekp(offset());
    }
    bool read(fstream &fimg, vector<char> &buffer) const {
        fimg.seekg(offset());
        return readVector(fimg,buffer,size());
    }
    bool write(fstream &fimg, const vector<char> &buffer, bool zeroAddition) const {
        fimg.seekp(offset());
        if(!writeVector(fimg,buffer)) return false;
        if(zeroAddition){
            vector<char> zero(size() - buffer.size());
            return writeVector(fimg,zero);
        }else{
            fimg.seekp(imgBytes(nextB()));
            return fileExtend(fimg);
        }
    }
    bool writeZero(fstream &fimg) const {
        fimg.seekp(offset());
        vector<char> zero(size());
        return writeVector(fimg,zero);
    }
    //bool operator < (const ImgItem &b) const { return offsetB < b.offsetB; }
    bool operator < (const ImgItem &b) const { return offsetB==b.offsetB ? sizeB<b.sizeB : offsetB<b.offsetB; }
    bool operator == (const ImgItem &b) const {
        //return offsetB==b.offsetB && sizeB==b.sizeB && getName()==b.getName();
        return !memcmp(this, &b, sizeof b);
    }
    bool operator != (const ImgItem &b) const { return !(*this==b); }
    string str() const {
        char buf[64];
        sprintf(buf, "(0x%X, %d, %.24s)", imgBytes(offsetB), imgBytes(sizeB), name);
        return string(buf);
    }
};

struct ImgFile{
    DWORD fcc;
    vector<ImgItem> files;
    map<string,ImgItem*> fileByKey;
    fstream fimg;
    fstream fdir;
    string imgname;
    string dirname;
    string lastname;
    int reserved;       
    bool usingGaps;
    bool shrinkFiles;
    bool zeroAddition;
    bool writeZeros;
    bool overwriteNames;
    void clear(){
        close(); clearStreams();
        files.clear(); fileByKey.clear();
        imgname.clear(); dirname.clear(); lastname.clear();
        fcc = 0; reserved = 0;
        usingGaps = shrinkFiles = zeroAddition = writeZeros = overwriteNames = true;
    }
    void close(){ fimg.close(); fdir.close(); }
    void clearStreams(){ fimg.clear(); fdir.clear(); }
    bool imgFalse(const string &_fname){
        lastname = _fname;
        return false;
    }
    bool imgFalse(const string &_fname, fstream& _f){
        lastname = _fname;
        if(_f.eof() && GetLastError()==0) ::SetLastError(ERROR_HANDLE_EOF);
        return false;
    }
    #define IMGFALSE imgFalse(imgname,fimg)
    #define DIRFALSE imgFalse(dirname,fdir)
    void rebuildSearch(){
        fileByKey.clear();
        stl_for(ifile,files,vector<ImgItem>) fileByKey[ifile->getKey()]=ifile;
    }
    ImgItem *fileByName(const string &name){ return fileByKey[imgKey(name)]; }
    void go(const string &name){ fileByName(name)->go(fimg); }
    bool open(const string &fname, bool write=false){
        clear();
        imgname = fname;
        fimg.open(imgname.c_str(), ios::binary|ios::in|(write?ios::out:0));
        if(!fimg) return IMGFALSE;
        fcc = readValue<DWORD>(fimg);   //possible viod file
        fimg.clear();
        if(FCC_VER2 == fcc){
            int fileCount = readValue<int>(fimg);
            fimg.clear();
            if(!readVector(fimg, files, fileCount)) return IMGFALSE;
        }else{
            dirname = imgname.substr(0,imgname.rfind(".")) + ".dir";
            fdir.open(dirname.c_str(), ios::binary|ios::in|(write?ios::out:0));
            if(!fdir) return DIRFALSE;
            int fileCount = filesize(fdir)/sizeof(ImgItem);
            if(!readVector(fdir, files, fileCount)) return DIRFALSE;
        }
        reserved = files.size();
        rebuildSearch();
        return true;
    }
    bool saveCount(int count){
        if(FCC_VER2 != fcc) return true;
        fimg.seekp(0);
        if(!writeValue(fimg,FCC_VER2)) return IMGFALSE;
        if(!writeValue(fimg,count)) return IMGFALSE;
        return true;
    }
    bool saveCount(){ return saveCount(files.size()); }
    bool save(){
        if(FCC_VER2 == fcc){
            if(!saveCount()) return false;
            if(!writeVector(fimg,files)) return IMGFALSE;
        }else{
            if(!writeVector(fdir,files)) return DIRFALSE;
        }
        return true;
    }
    bool saveRecord(const ImgItem &rec, int n){
        if(FCC_VER2 == fcc){
            fimg.seekp(8 + n*sizeof(ImgItem));
            if(!writeValue(fimg,rec)) return IMGFALSE;
        }else{
            fdir.seekp(n*sizeof(ImgItem));
            if(!writeValue(fdir,rec)) return DIRFALSE;
        }
        return true;
    }
    int recordIndex(const ImgItem *rec) const { return rec-files.begin(); }
    bool saveRecord(const ImgItem *rec){ return saveRecord(*rec, recordIndex(rec)); }
    DWORD findGapB(DWORD size, DWORD start) const {
        long long sizeB = imgBlocks(size);
        long long startB = imgBlocks(start);
        vector<ImgItem> sorted = files;
        stable_sort(sorted.begin(),sorted.end());
        stl_for(ifile,sorted,vector<ImgItem>){
            if((long long)ifile->offsetB - startB >= sizeB) return startB;  //signed long long!!!
            startB = max(ifile->nextB(),startB);
        }
        return startB;
    }
    DWORD metaSize(int fileCount) const { return (fileCount*sizeof(ImgItem)+8)*(FCC_VER2==fcc); }
    DWORD metaSize() const { return metaSize(reserved); }
    DWORD findSpaceB(DWORD size, DWORD start) const {
        if(usingGaps) return findGapB(size,start);
        const ImgItem *rec = max_element(files.begin(),files.end());
        return max(imgBlocks(start), rec?rec->nextB():0);
    }
    DWORD findSpaceB(DWORD size) const { return findSpaceB(size,metaSize()); }
    bool reserve(int n){
        if(n < reserved) return true;
        if(files.empty()){
            reserved = n;
            return true;
        }
        DWORD meta_size = metaSize(n);
        vector<char> buf;
        while(true){
            ImgItem *first = min_element(files.begin(),files.end());
            if(first->offset() >= meta_size) break;
            ImgItem item = *first, old = *first;
            if(!item.read(fimg,buf)) return IMGFALSE;
            item.offsetB = findSpaceB(item.size(),meta_size);
            if(!item.write(fimg,buf,zeroAddition)) return IMGFALSE;
            if(!saveRecord(item,recordIndex(first))) return false;
            *first = item;
            if(writeZeros) if(!old.writeZero(fimg)) return IMGFALSE;
        }
        reserved = n;
        return true;
    }
    bool import(const string &dest, const char *src){
        vector<char> buf;
        if(!readVector(src,buf)) return imgFalse(src);
        ImgItem *rec = fileByName(dest);
        if(!rec){
            if(!reserve(files.size()+1)) return false;
            ImgItem item;
            item.offsetB = findSpaceB(buf.size());
            item.sizeB = imgBlocks(buf.size());
            item.setName(dest);
            if(!item.write(fimg,buf,zeroAddition)) return IMGFALSE;
            if(!saveRecord(item,files.size())) return false;
            if(!saveCount(files.size()+1)) return false;
            files.push_back(item);
            fileByKey[item.getKey()] = &files.back();
        }else if(rec->size() < buf.size()){
            ImgItem item = *rec, old = *rec;
            item.offsetB = findSpaceB(buf.size());
            item.sizeB = imgBlocks(buf.size());
            if(overwriteNames) item.setName(dest);
            if(!item.write(fimg,buf,zeroAddition)) return IMGFALSE;
            if(!saveRecord(item,recordIndex(rec))) return false;
            *rec = item;
            if(writeZeros) if(!old.writeZero(fimg)) return IMGFALSE;
        }else{
            ImgItem item = *rec;
            if(!writeZeros) item.sizeB = shrinkFiles ? imgBlocks(buf.size()) : item.sizeB;
            if(!item.write(fimg,buf,zeroAddition)) return IMGFALSE;
            item.sizeB = shrinkFiles ? imgBlocks(buf.size()) : item.sizeB;
            if(overwriteNames) item.setName(dest);
            if(!saveRecord(item,recordIndex(rec))) return false;
            *rec = item;
        }
        return true;
    }
    bool newArchive(const string &fname, DWORD _fcc=FCC_VER2){
        clear();
        fcc = _fcc;
        imgname = fname;
        fimg.open(imgname.c_str(), ios::binary|ios::out);
        if(!fimg) return IMGFALSE;
        if(FCC_VER2 != fcc){
            dirname = imgname.substr(0,imgname.rfind(".")) + ".dir";
            fdir.open(dirname.c_str(), ios::binary|ios::out);
            if(!fdir) return DIRFALSE;
        }
        return save();
    }
    friend bool rebuild(const char *fname_new, ImgFile &Src, ImgCallbackFun func=NULL){
        ImgFile Dest;
        if(!Dest.newArchive(fname_new,Src.fcc)) return Src.imgFalse(Dest.lastname);
        if(!Dest.reserve(Src.files.size())) return Src.imgFalse(Dest.lastname);
        Dest.fimg.seekp(imgAlign(Dest.metaSize()));
        vector<char> buf;
        stl_for(ifile,Src.files,vector<ImgItem>){
            if(!ifile->read(Src.fimg,buf)) return Src.imgFalse(Src.imgname,Src.fimg);
            Dest.files.push_back(*ifile);
            ImgItem *rec = &Dest.files.back();
            rec->offsetB = imgBlocks(Dest.fimg.tellp());
            if(!rec->write(Dest.fimg,buf,Dest.zeroAddition)) return Src.imgFalse(Dest.imgname,Dest.fimg);
            if(func) func();
        }
        if(!Dest.save()) return Src.imgFalse(Dest.lastname);
        return true;
    }
    bool rebuild(const char *fname_new, ImgCallbackFun func=NULL){ return ::rebuild(fname_new, *this, func); }
    bool extract(const ImgItem *rec, const char *dest){
        vector<char> buf;
        if(!rec->read(fimg,buf)) return IMGFALSE;
        if(!writeVector(dest,buf)) return imgFalse(dest);
        return true;
    }
};

