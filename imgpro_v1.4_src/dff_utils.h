// IMG Pro v1.4
// Coded by LOD (Usov Alexey)
// mail: imgpro@rambler.ru
// http://github.com/imgpro
// http://vk.com/id58933402
// http://vk.com/public24609835
// Copyright (C) 2007-2016 LOD (Usov Alexey)

#ifndef DFF_UTILS
#define DFF_UTILS

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>
using namespace std;

//readVector, writeVector
template<typename T>
istream& readVector(istream &f, T &v, size_t n){
    v.resize(n);
    //f.read((char*)v.begin(), n*sizeof(T::value_type)); //slowly
    streamsize bytes = n*sizeof(T::value_type);
    streamsize readed = f.rdbuf()->sgetn((char*)v.begin(), bytes);
    if(bytes != readed) f.setstate(ios::eofbit|ios::failbit);
    return f;
}
template<typename T, typename TRaw>
void readVector(istream &f, T &v, size_t n, TRaw raw){
    v.resize(n);
    for(T::iterator it = v.begin(); it != v.end(); ++it){
        readValue(f, raw);
        *it = raw;
    }
}
template<typename T>
bool readVector(const char *fname, T &v){
    ifstream f(fname,ios::binary);
    if(!f) return false;
    size_t n = (filesize(f)+sizeof(T::value_type)-1)/sizeof(T::value_type);
    return readVector(f,v,n);
}
template<typename T>
ostream& writeVector(ostream &f, T &v){
    return f.write((char*)v.begin(), v.size()*sizeof(T::value_type));
}
template<typename T, typename TRaw>
void writeVector(ostream &f, T &v, TRaw raw){
    for(T::iterator it = v.begin(); it != v.end(); ++it){
        raw = *it;
        writeValue(f, raw);
    }
}
template<typename T>
bool writeVector(const char *fname, T &v){
    ofstream f(fname,ios::binary);
    if(!f) return false;
    return writeVector(f,v);
}

//loadVector, saveVector
template<typename T>
void loadVector(istream &f, T &v, size_t n){
    v.resize(n);
    for(T::iterator it = v.begin(); it != v.end(); ++it) it->load(f);
}
template<typename T>
void saveVector(ostream &f, T &v){
    for(T::iterator it = v.begin(); it != v.end(); ++it) it->save(f);
}

//readValue, viewValue, writeValue
template<typename T>
void readValue(istream &f, T &dest){
    f.read((char*)&dest, sizeof(T));
}
template<typename T>
T readValue(istream &f){
    T x = T();
    f.read((char*)&x, sizeof(T));
    return x;
}
template<typename T>
T viewValue(istream &f){
    T x = T();
    streampos pos = f.tellg();
    f.read((char*)&x, sizeof(T));
    f.seekg(pos);
    return x;
}
template<typename T>
ostream& writeValue(ostream &f, T x){
    return f.write((char*)&x, sizeof(x));
}

struct complex{
    float x,y;
    complex(){}
    complex(float _x, float _y){ x=_x; y=_y; }  
    friend float dot(const complex &a, const complex &b){ return a.x*b.x + a.y*b.y; }
    float abs2() const { return x*x + y*y; }
    float abs() const { return sqrt(abs2()); }
    float arg() const { return atan2(y,x); }
    friend complex operator * (float s, const complex &a){ return complex(s*a.x, s*a.y); }
    friend complex operator * (const complex &a, float s){ return complex(a.x*s, a.y*s); }
    friend complex operator / (float s, const complex &a){ return complex(s,0)/a; }
    friend complex operator / (const complex &a, float s){ return complex(a.x/s, a.y/s); }
    friend complex operator + (const complex &a, const complex &b){
        return complex(a.x+b.x, a.y+b.y);
    }
    friend complex operator - (const complex &a, const complex &b){
        return complex(a.x-b.x, a.y-b.y);
    }
    friend complex operator * (const complex &a, const complex &b){
        return complex(a.x*b.x - a.y*b.y, a.y*b.x + a.x*b.y);
    }
    friend complex operator / (const complex &a, const complex &b){
        return a*b.conj()/b.abs2();
    }
    complex conj() const { return complex(x,-y); }
    complex inv() const { return conj()/abs2(); }
    string str(){
        char buf[64];
        sprintf(buf, "[%.3f,%.3f]", x, y);
        return string(buf);
    }
};

struct vec{
    float x,y,z;
    vec(){}
    vec(float _x, float _y, float _z){ x=_x; y=_y; z=_z; }
    friend float dot(const vec &a, const vec &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
    float abs2() const { return x*x + y*y + z*z; }
    float abs() const { return sqrt(abs2()); }
    friend vec operator * (float s, const vec &v){ return vec(s*v.x, s*v.y, s*v.z); }
    friend vec operator * (const vec &v, float s){ return vec(v.x*s, v.y*s, v.z*s); }
    friend vec operator / (const vec &v, float s){ return vec(v.x/s, v.y/s, v.z/s); }
    friend vec operator + (const vec &a, const vec &b){ return vec(a.x+b.x, a.y+b.y, a.z+b.z); }
    friend vec operator - (const vec &a, const vec &b){ return vec(a.x-b.x, a.y-b.y, a.z-b.z); }
    friend vec cross(const vec &a, const vec &b){
        return vec(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
    }     
    string str(){
        char buf[64];
        sprintf(buf, "[%.3f,%.3f,%.3f]", x, y, z);
        return string(buf);
    }
};

template<typename T1, typename T2>
void setFlag(T1 &x, T2 flag, bool state){ x = state ? x|flag : x&~flag; }

inline string toupper(string s){
    transform(s.begin(), s.end(), s.begin(), toupper);
    return s;
}

inline string tolower(string s){
    transform(s.begin(), s.end(), s.begin(), tolower);
    return s;
}

inline streampos filesize(istream &f){
    streampos pos = f.tellg();
    f.seekg(0,ios::end);
    streampos res = f.tellg();
    f.seekg(pos);
    return res;
}

inline fstream& fileExtend(fstream &f){
    if(f.tellp() > filesize(f)){
        f.seekp(f.tellp()-1);
        writeValue<char>(f,0);
    }
    return f;
}

#define stl_for(Iter,Cont,TCont) for(TCont::iterator Iter=Cont.begin(); Iter!=Cont.end(); ++Iter)

#endif

