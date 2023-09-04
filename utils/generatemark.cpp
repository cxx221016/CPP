#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<random>
#include"BookMarks.hpp"
using namespace std;


int main(int argc,char* args[])
{
    std::string urlpath="D:\\Download\\myself.txt";
    std::shared_ptr<BookMarkBuilder> builder(new BookMarkBuilder("bookmark"));
    ifstream in(urlpath);
    std::vector<std::string> urls;
    std::string line;
    while(getline(in,line))
    {
        urls.push_back(line);
    }
    in.close();
    for(auto url:urls)
    {
        builder->AddUrl(url);
    }
    auto dir1=builder->SubFolder("dir1");
    dir1->AddUrl("www.baidu.com");
    dir1->AddUrl("www.sina.com");
    dir1->AddUrl("www.qq.com");
    dir1->AddUrl("www.163.com");
    auto dir11=dir1->SubFolder("dir11");
    dir11->AddUrl("www.163.com");
    dir11->AddUrl("www.163.com");
    auto dir2=builder->SubFolder("dir1")->SubFolder("dir2");
    dir2->AddUrl("www.google.com");
    dir2->AddUrl("www.bing.com");
    dir2->AddUrl("www.sogou.com");
    dir2->AddUrl("www.soso.com");
    dir2->AddUrl("www.yahoo.com");
    std::string dir3name="dir3";
    auto dir3=builder->SubFolder(dir3name);
    dir3->AddUrl("www.google.com");
    dir3->AddUrl("www.bing.com");
    auto main=builder->SubFolder("main");
    main->AddUrl("www.google.com");
    main->AddUrl("www.bing.com");
    auto country=builder->SubFolder("country");
    country->AddUrl("www.sjtu.edu.cn");
    country->AddUrl("www.tsinghua.edu.cn");
    country->AddUrl("www.pku.edu.cn");
    country->AddUrl("www.zju.edu.cn");

    
    // std::string result=builder->str();
    // std::string outpath="D:\\Download\\myself.html";
    // ofstream out(outpath);
    // out<<result;
    // out.close();
    if(!builder->SaveToFile("D:\\Download\\myself.html"))
    {
        std::cout<<"save failed"<<std::endl;
    }
    std::cout<<args[0]<<std::endl;
    std::cout<<argc<<std::endl;

    system("pause");
    return 0;
}