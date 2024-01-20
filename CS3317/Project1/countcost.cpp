#include <iostream>
#include <string>
#include <vector>
using namespace std;
int gapcost = 3;
int mismatchcost = 5;
int main()
{
    // vector<string> strs
    // {
    //     "--IWTJBGTJGJTWGBJTPKHAXHAGJJSJJPPJAPJHJHJHJHJHJHJHJHJPK-STJJUWXHGPHGALKLPJTPJPGVXPLBJHH-JPKWPPDJSG",
    //     "--IWTJBGTJGJTWGBJTPKHAXHAGJJXJJKPJTPJHJHJHJHJHJHJHJHJHK-UTJJUWXHGHHGALKLPJTPJPGVX-PLBJHH----------",
    //     "WPIWTJBGTJGJTHGBJOXKHTXHAGJJXJJPPJTP--JHJHJHJHJHJHJHJPKUAJJUWXHG-HHGALKLPJTPJPGVXPLBJHH-JPK-------",
    // };
    // vector<string> strs{
    //     "IPZ-JJLMLTKJU-LOSTKTJOGLKJO-BLTXGKTPLUWWKOMOYJBG-A-LJUKLGLOSVHWBPGWSLUKO-BSOPLOOKUKSARPPJ",
    //     "IPZJJ-PLLTTO-ULOSTPLOOGLWJJBLL--XWKWTLUWW-KOMOYJBZAYUKLWLJ-SZHGBPKJULJ-KUBHJJOJOHGKTKWA-T",
    //     "IPMJJLLLTH-O-ULOSTMA-JIGLKJPVL-LXGKTPLTWWKOMOYJBZPYU-KLILOSZHGBPGWXLZK--JBSWJLPJUUMHKTRAP",
    // };
    // vector<string> strs{
    //     "IPZJJPL*LTHUULOSTXTJOGLKJGBLLMMPJPLUWGKOMOYJBZA*YUKOFLOSZHGBPH*XPLXKJBXKJLAUUOJHW*TWWPQ*",
    //     "IPMJJ*LLLTHOULOSTMAJIGLKJPVLLXGKTPLTWWKOMOYJBZP*YUKLILOSZHGBPGWXLZKJBSWJLPJUU*MHK*TRAP**",
    //     "IPZJJ*LMLTKJULOSTKTJOGLKJOBLTXGKTPLUWWKOMOYJBGALJUKLGLOSVHWBPGWS*LUKOBSOPLOOKU***KSARPPJ",
    // };
    // vector<string> strs{
    //     "IPZJJLMLTKJ-ULOSTKTJOGLKJOBLTXGKTP--LUWWKOMOYJBGALJUKLGLOSVHWBPGWSLUKOBSOP-LOOKUKS-----ARPPJ",
    //     "IPZJJ-LGLTTOULOSTKTJOGLKJKBPL-MJKHL-LXWWKOMOYJBJALOLPLWLOSSHWBP-WPPLOKXBJH-LOJLO-GWT-WGA---S",
    //     "IPZJJPL-LTTOULOSTPLOOGLWJJBLL-XWKWT-LUWWKOMOYJBZA-YUKLWLJSZHGBPKJ-ULJKUB-HJJOJ-OHGKTKW-A---T",
    // };
    vector<string> strs{
        "IWT---JBGTJGJTWGBJ-TPKHAXHAGJJSJJPPJAPJHJHJHJHJH-JH-JHJHJPKSTJ--JUWXHGPHGALKLPJ-TPJPGVXPLBJHHJPKWPPDJSG",
        "IWT---JBGTJGJTWGBJ-TPKHAXHAGJJXJJKPJTPJHJHJHJHJH-JH-JHJHJHKUTJ--JUWXHGHHGALKLPJ-TPJPGVXPLBJHH----------",
        "-WTXHHJ-JTJ-HT-NTJHT-JH--H------J--JT-JH-HJH-HJHOJHPJH-HJHHNTJHHJ---H--H------JHT---------JHHJ-HW---JPH",
    };
    for(auto& str:strs){
        for(auto& c:str){
            if(c=='*'){
                c='-';
            }
        }
    }
    int cost = 0;
    for (int i = 0; i < strs.size(); ++i)
    {
        for (int j = i + 1; j < strs.size(); ++j)
        {
            for (int k = 0; k < strs[0].size(); ++k)
            {
                if (strs[i][k] == '-' && strs[j][k] == '-')
                {
                    continue;
                }
                else if (strs[i][k] == '-' || strs[j][k] == '-')
                {
                    cost += gapcost;
                }
                else if (strs[i][k] != strs[j][k])
                {
                    cost += mismatchcost;
                }
            }
        }
    }
    cout<<cost<<endl;
    for(auto& str:strs){
        cout<<str<<endl;
    }
    system("pause");
    return 0;
}