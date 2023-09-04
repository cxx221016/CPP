#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<string>
#include<sstream>
#include<unordered_map>
#include<iterator>
using namespace std;

namespace std {
template<>
class hash<pair<int,int>> 
{
public:
    size_t operator()(const pair<int,int> &p) const {
        return hash<int>()(p.first)^hash<int>()(p.second);
    }
};
};

struct Exit : runtime_error {
	Exit() : runtime_error("Exit") {}
};

// error() simply disguises throws:
inline void error(const string& s)
{
	throw runtime_error(s);
}

class pointset
{
private:
    vector<pair<int,int>> points;
public:
    pointset()
    {

    }

    static int dis(const pair<int,int>& a,const pair<int,int>& b)
    {
        return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
    }

    int _add(istringstream& is)
    {
        int size;
        if(is>>size)
        {
            int cnt=0;
            while(size--)
            {
                int x,y;
                if(is>>x>>y) points.emplace_back(x,y),cnt++;
                else 
                {
                    while(cnt--) points.pop_back();
                    error("invalid input");
                }
            }
            int check;
            if(is>>check)
            {
                while(cnt--) points.pop_back();
                error("invalid input");
            }
        }
        sort(points.begin(),points.end());
        points.erase(unique(points.begin(),points.end()),points.end());
        return points.size();
    }
    string _find(istringstream& is)
    {
        int x,y;
        if(is>>x>>y)
        {
            int check;
            if(is>>check) error("invalid input");
            pair<int,int> pr{x,y};
            auto it =find(points.begin(),points.end(),pr);
            if(it==points.end()) return "not find";
            else return "find";
        }
        else error("invalid input");
    }

    int _filter(istringstream&  is)
    {
        int x,y,d;
        if(is>>x>>y>>d)
        {
            int check;
            if(is>>check) error("invalid input");
            pair<int,int> pr{x,y};
            d=d*d;
            auto it=partition(points.begin(),points.end(),[&](auto&& p)
            {
                return dis(p,pr)<=d;
            });
            points.erase(it,points.end());
            return points.size();
        }
        else error("invalid input");
    }

    vector<pair<int,int>>&  _sort(istringstream& is)
    {
        int x,y;
        if(is>>x>>y)
        {
            int check;
            if(is>>check) error("invalid input");
            pair<int,int> pr{x,y};
            unordered_map<pair<int,int>,int> getdis;
            for(auto& p:points)
            {
                getdis[p]=dis(p,pr);
            }
            sort(points.begin(),points.end(),[&](const auto& a,const auto& b)
            {
                return getdis[a]==getdis[b]? a.first<b.first: getdis[a]<getdis[b];
            });
            return points;
        }
        else error("invalid input");
    }
};


int main()
{
    string str;
    ostringstream os;
    pointset pset;
    while(getline(cin,str))
    {
        try
        {
            istringstream is(str);
            string cmd;
            is>>cmd;
            if(cmd=="add")
            {
                os<<pset._add(is)<<'\n';
            }
            else if(cmd=="find")
            {
                os<<pset._find(is)<<'\n';
            }
            else if(cmd=="filter")
            {
                os<<pset._filter(is)<<'\n';
            }
            else if(cmd=="sort")
            {
                vector<pair<int,int>> points=pset._sort(is);
                if(points.empty())
                {
                    os<<'\n';
                    continue;
                }
                for(auto& point:points)
                {
                    os<<"("<<point.first<<", "<<point.second<<")";
                    if(point!=points.back())  os<<", ";
                    else os<<'\n';
                }
            }
            else error("invalid input");
        }
        catch(const std::exception& e)
        {
            os << e.what() << '\n';
        }
    }
    string output=os.str();
    output.pop_back();
    cout<<output;
    system("pause");
    return 0;
}