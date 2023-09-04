#include "std_lib_facilities.h"
class MySolution
{
public:
    bool isvalid(const string& str)
    {
        int l=0;
        for(int i=0;i<str.size();++i)
        {
            char ch=str[i];
            if(ch=='1') l++;
            else 
            {
                if(l==0) return false;
                else l--;

                if(l==0&&i!=str.size()-1) return false;
            }
        }
        return l==0;
    }

    vector<string> split(string&& str)
    {
        int n=str.size();
        int left=0,right=0;
        int cur=0;
        vector<string> res;
        while(right<n)
        {
            if(str[right]=='1') cur++;
            else
            {
                if(cur>0) cur--;
                else error(str);
            }
            if(cur==0)
            {
                res.push_back(str.substr(left,right-left+1));
                left=right+1;
            }
            ++right;
        }
        sort(res.begin(),res.end(),[](const auto& a,const auto& b)
        {
            return a.size()<=b.size();
        });
        return res;
    }

    bool isomorphic(const string& s,const string& t)
    {
        if(s[0]!='1'||s.back()!='0'||s.size()%2) error(s);
        if(t[0]!='1'||t.back()!='0'||t.size()%2) error(t);
        if(s==t) return true;
        if(s.size()!=t.size()) return false;
        if(s.size()==2) return false;
        //string tmp({s.begin()+1,s.end()-1});
        vector<string> sp=split({s.begin()+1,s.end()-1});
        vector<string> tp=split({t.begin()+1,t.end()-1});
        if(sp.size()!=tp.size()) return false;
        for(int i=0;i<sp.size();++i)
        {
            if(!isomorphic(sp[i],tp[i])) return false;
        }
        return true;
    }

    string my_isomorphic(const string& s,const string& t)
    {
        try
        {
            return to_string(isomorphic(s,t));
        }
        catch(const std::exception& e)
        {
            //std::cerr << e.what() << '\n';
            return e.what();
        }
        
    }
};