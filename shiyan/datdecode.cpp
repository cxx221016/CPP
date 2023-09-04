#include<fstream>
#include<sstream>
#include<iostream>
#include<unordered_map>
#include<string>

namespace std {
template<>
class hash<pair<unsigned char,unsigned char>> 
{
public:
    size_t operator()(const pair<unsigned char,unsigned char> &p) const {
        return hash<int>()(p.first)^hash<int>()(p.second);
    }
};
};

using head = std::pair<unsigned char, unsigned char>;

static std::unordered_map<head,std::string> fileheadmap
{
    {head{0x42,0x4D},"bmp"},
    {head{0x47,0x49},"gif"},
    {head{0x89,0x50},"png"},
    {head{0xFF,0xD8},"jpg"},
    {head{0x49,0x49},"tif"},
    {head{0x00,0x00},"ico"}
};

std::pair<std::string,std::string> getinfo(const std::string& filepath)
{
    std::cout<<filepath<<std::endl;
    auto idx=filepath.find_last_of('.');
    if(idx==std::string::npos)
    {
        return {filepath,""};
    }
    else
    {
        std::cout<<filepath.substr(0,idx)<<" "<<filepath.substr(idx+1)<<std::endl;
        return {filepath.substr(0,idx),filepath.substr(idx+1)};
    }
}

std::pair<unsigned char,std::string> getfiletype(const head& h)
{
    for(auto& [k,v]:fileheadmap)
    {
        //std::cout<<(int)(k.first^h.first)<<" "<<(int)(k.second^h.second)<<std::endl;
        if((k.first^h.first)==(k.second^h.second)) 
        {
            //std::cout<<(int)(k.first^h.first)<<" "<<(int)(k.second^h.second)<<std::endl;
            return {(k.first^h.first),v};
        }
    }
    return {0,""};
}


bool parse(const std::string& filepath)
{
    //std::ifstream fin(filepath,std::ios::binary|std::ios::in);
    auto info=getinfo(filepath);
    if(info.second=="")
    {
        std::cout<<"not a dat file"<<std::endl;
        return false;
    }
    if(info.second!="dat")
    {
        std::cout<<"not a dat file"<<std::endl;
        return false;
    }
    std::ifstream fin(filepath,std::ios::binary);
    if(!fin)
    {
        std::cout<<"file not found"<<std::endl;
        return false;
    }
    int length=fin.seekg(0,std::ios::end).tellg();
    fin.seekg(0,std::ios::beg);
    unsigned char* buffer=new unsigned char[length];
    fin.read((char*)buffer,length);
    fin.close();
    //std::cout<<length<<std::endl; 
    auto filetype=getfiletype({buffer[0],buffer[1]});
    if(filetype.second=="")
    {
        std::cout<<"unknown file type"<<std::endl;
        return false;
    }
    unsigned char key=filetype.first;
    for(int i=0;i<length;++i)
    {
        buffer[i]^=key;
    }
    std::ofstream fout(info.first+"."+filetype.second,std::ios::binary);
    fout.write((char*)buffer,length);
    fout.close();
    delete[] buffer;
    return true;

}

int main()
{
    std::string filepath;
    while(true)
    {
        std::cout<<"input filename:";
        std::cin>>filepath;
        if(filepath=="exit") break;
        if(parse(filepath)) std::cout<<"success"<<std::endl;
        else std::cout<<"failed"<<std::endl;
    }
    return 0;
}
