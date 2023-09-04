#include<string>
#include<sstream>
#include<iostream>
#include<cassert>

template <class T0, class T1, class T2, class T3, class T4>
std::string FormatString (const std::string &msg, int paraSize, const T0 &t0, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
{
    if (paraSize > 5)
        paraSize = 5;
    const char PREFEX = '$';
    std::stringstream ss;
    for (std::string::size_type i = 0; i < msg.size (); ++i)
    {
        if (msg[i] != PREFEX) // not '$'
        {
            ss << msg[i];
        }
        else if (i == msg.size () - 1) // '$' is the end of msg
        {
            ss << PREFEX;
        }
        else // is '$'
        {
            i++;
            char c = msg[i]; // get next character
            int index = c - '0';
            if (c == PREFEX) // next character is '$'
            {
                ss << PREFEX;
            }
            else if (index < 0 || index >= paraSize) // next character is not valid para ('0' - '5')
            {
                ss << PREFEX << c;
            }
            else // valid para "$0", "$1", ...
            {
                switch (index)
                {
                case 0:
                    ss << t0;
                    break;
                case 1:
                    ss << t1;
                    break;
                case 2:
                    ss << t2;
                    break;
                case 3:
                    ss << t3;
                    break;
                case 4:
                    ss << t4;
                    break;
                default:
                    assert (false);
                    break;
                }
            }
        }
    }
    return ss.str ();
}
template <class T0, class T1, class T2, class T3>
std::string FormatString (const std::string &msg, const T0 &t0, const T1 &t1, const T2 &t2, const T3 &t3)
{
    return FormatString (msg, 4, t0, t1, t2, t3, 0);
}
template <class T0, class T1, class T2>
std::string FormatString (const std::string &msg, const T0 &t0, const T1 &t1, const T2 &t2)
{
    return FormatString (msg, 3, t0, t1, t2, 0, 0);
}
template <class T0, class T1>
std::string FormatString (const std::string &msg, const T0 &t0, const T1 &t1)
{
    return FormatString (msg, 2, t0, t1, 0, 0, 0);
}
template <class T0>
std::string FormatString (const std::string &msg, const T0 &t0)
{
    return FormatString (msg, 1, t0, 0, 0, 0, 0);
}
std::string FormatString (const std::string &msg)
{
    return FormatString (msg, 0, 0, 0, 0, 0, 0);
}

void FormatString_test ()
{
    std::cout << FormatString ("$hahaha$", 1, 2) << std::endl;
    std::cout << FormatString ("haha $0 sss", 3) << std::endl;
    std::cout << FormatString ("haha $0 sss $1 ddd $3$5", 3) << std::endl;
    std::cout << FormatString ("haha $$0 s$ss $1 ddd $3$5", 3, "dddd") << std::endl;
    std::cout << FormatString ("haha $$$0 sss $1 ddd $3$5", 'a', "dddddd", 3, 0.3333) << std::endl;
}

int main()
{
    FormatString_test ();
    system("pause");
    return 0;
}