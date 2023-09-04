#ifndef BOOKMARKBUILDER_H
#define BOOKMARKBUILDER_H

#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<unordered_map>
#include<memory>
#include<ctime>
#include"base64.hpp"
#define DEFAULT_ICON

using namespace std;
static const std::string defaultfoldername = "BookMarkFolder";
static size_t default_indent_size = 4;

class BookMarkBuilder;

class ILogger
{
    public:
        virtual ~ILogger(){}
        virtual void Log(const std::string& msg)=0 ;
};



struct BookMarkUrl
{
    std::string url;
    std::string name;
    std::string add_date;
    std::string icon;
    inline static const std::string defaulticon="data:image/png;base64,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";

    BookMarkUrl(std::string url, std::string name="", std::string add_date="", std::string icon=""):url(url),name(name),add_date(add_date),icon(icon){
        if(this->name.empty()){
            this->name =reduceurl(this->url);
        }
        if(this->add_date.empty()){
            this->add_date =time2timestamp();
        }
        #ifdef DEFAULT_ICON
        if(this->icon.empty()){
            this->icon = defaulticon;
        }
        #endif
    }
    std::string str(size_t indent=0) const;
};

class BookMarkFolder
{
    friend class BookMarkBuilder;
    public:
        BookMarkFolder(std::string name="", std::string add_date="", std::string last_modified="",bool isroot=false):name(name),add_date(add_date),last_modified(last_modified),isroot(isroot){
            if(this->name.empty()){
                this->name = defaultfoldername;
            }
            if(this->add_date.empty()){
                this->add_date =time2timestamp();
            }
            if(this->last_modified.empty()){
                this->last_modified =time2timestamp();
            }
        }
        ~BookMarkFolder(){}
        std::string str(size_t indent) const;
        //std::shared_ptr<BookMarkFolder> operator[](const std::string& name);
    private:
        std::string name;
        std::string add_date;
        std::string last_modified;
        bool isroot;
        std::unordered_map<std::string, std::shared_ptr<BookMarkFolder>> m_folder_children;
        std::unordered_map<std::string, std::shared_ptr<BookMarkUrl>> m_url_children;
};

class BookMarkBuilder:public std::enable_shared_from_this<BookMarkBuilder>,public ILogger
{
    public:
        BookMarkBuilder(const std::string& name="", const std::string& add_date="", const std::string& last_modified=""):m_root(new BookMarkFolder(name, add_date, last_modified,true)){}
        BookMarkBuilder(std::shared_ptr<BookMarkFolder> root):m_root(root){}
        virtual ~BookMarkBuilder(){}
        std::shared_ptr<BookMarkBuilder> AddFolder(const std::string& name="", const std::string& add_date="", const std::string& last_modified="");
        std::shared_ptr<BookMarkBuilder> operator[](const std::string& name);
        std::shared_ptr<BookMarkBuilder> SubFolder(const std::string& name);
        std::shared_ptr<BookMarkBuilder> AddUrl(const std::string& url, const std::string& name="", const std::string& add_date="", const std::string& icon="");
        std::string str(size_t indent=0) const;
        virtual void Log(const std::string& msg)
        {
            std::cout<<msg<<std::endl;
        }
        bool SaveToFile(const std::string& path)
        {
            std::string result=this->str();
            ofstream out(path);
            if(!out.is_open()) return false;
            out<<result;
            out.close();
            return true;
        }
    private:
        std::shared_ptr<BookMarkFolder> m_root;

};

std::string BookMarkUrl::str(size_t indent) const{
    std::string str;
    str.append(indent, ' ');
    str += "<DT><A HREF=\"";
    str += url;
    str += "\" ADD_DATE=\"";
    str += add_date;
    str += "\" ICON=\"";
    str += icon;
    str += "\">";
    str += name;
    str += "</A>\n";
    return str;
}

std::string BookMarkFolder::str(size_t indent) const{
    std::string str;
    if(isroot) 
    {
        str+="<!DOCTYPE NETSCAPE-Bookmark-file-1>\n";
        str += "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\">\n";
        str += "<TITLE>Bookmarks</TITLE>\n";
        str += "<H1>Bookmarks</H1>\n";
        str += "<DL><p>\n ";
    }
    str.append(indent, ' ');
    str += "<DT><H3 ADD_DATE=\"";
    str += add_date;
    str += "\" LAST_MODIFIED=\"";
    str += last_modified;
    if(isroot){
        str += "\" PERSONAL_TOOLBAR_FOLDER=\"true";
    }
    str += "\">";
    str += name;
    str += "</H3>\n";
    int allsize=m_folder_children.size()+m_url_children.size();
    if(allsize==0) return str;
    str.append(indent, ' ');
    str += "<DL><p>\n";
    for(auto& it : m_folder_children){
        str += it.second->str(indent+default_indent_size);
    }
    for(auto& it : m_url_children){
        str += it.second->str(indent+default_indent_size);
    }
    str.append(indent, ' ');
    str += "</DL><p>\n";
    if(isroot) str += "</DL><p>\n";
    return str;
}

std::shared_ptr<BookMarkBuilder> BookMarkBuilder::AddFolder(const std::string& name, const std::string& add_date, const std::string& last_modified)
{
    m_root->m_folder_children[name] = std::shared_ptr<BookMarkFolder>(new BookMarkFolder(name, add_date, last_modified));
    Log(this->m_root->name+" AddFolder "+name);
    return shared_from_this();
}

std::shared_ptr<BookMarkBuilder> BookMarkBuilder::operator[](const std::string& name)
{
    auto it = m_root->m_folder_children.find(name);
    if(it == m_root->m_folder_children.end()){
        std::shared_ptr<BookMarkFolder> folder(new BookMarkFolder(name));
        m_root->m_folder_children[name] = folder;
    } 
    Log(this->m_root->name+"->"+name);
    return std::make_shared<BookMarkBuilder>(m_root->m_folder_children[name]);
}

std::shared_ptr<BookMarkBuilder> BookMarkBuilder::SubFolder(const std::string& name)
{
    return operator[](name);
}

std::shared_ptr<BookMarkBuilder> BookMarkBuilder::AddUrl(const std::string& url, const std::string& name, const std::string& add_date, const std::string& icon)
{
    m_root->m_url_children[url] = std::shared_ptr<BookMarkUrl>(new BookMarkUrl(url, name, add_date, icon));
    Log(this->m_root->name+" AddUrl "+url);
    return shared_from_this();
}

std::string BookMarkBuilder::str(size_t indent) const
{
    return m_root->str(indent+2);
}

#endif // BOOKMARK_H


