 
//
// This is example code from Chapter 7.7 "Recovering from errors" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#include<set>
#include<unordered_set>
#include "std_lib_facilities.h"
class Quit{};
class COUT_OUT_EXPR{};
class COUT_ALL_NAME{};

map<string,multiset<string>> mp;


istringstream is;
ostringstream os;
/*
    Simple calculator

    Revision history:

        Revised by Bjarne Stroustrup May 2007
        Revised by Bjarne Stroustrup August 2006
        Revised by Bjarne Stroustrup August 2004
        Originally written by Bjarne Stroustrup
            (bs@cs.tamu.edu) Spring 2004.

    This program implements a basic expression calculator.
    Input from is; output to cout.

    The grammar for input is:

    Statement:
        Expression
        Print
        Quit

    Print:
        ;

    Quit:
        q

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal


        Input comes from is through the Token_stream called ts.
*/

//------------------------------------------------------------------------------

const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
//const string prompt = "> ";
const string result = "="; // used to indicate that what follows is a result

//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from is
    Token_stream(const Token_stream&)=default;
    Token_stream& operator=(const Token_stream&)=default;
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c);      // discard tokens up to an including a c
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{

}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get() // read characters from is and compose a Token
{
    if (full) {         // check if we already have a Token ready
        full=false;
        return buffer;
    }

    char ch;
    is >> ch;          // note that >> skips whitespace (space, newline, tab, etc.)
    switch (ch) {
    case quit:
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
        return Token(ch); // let each character represent itself
    case '.':             // a floating-point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':    // numeric literal
    {
        is.putback(ch);// put digit back into the input stream
        double val;
        is >> val;     // read a floating-point number
        return Token(number,val);
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
    // c represents the kind of a Token
{
    // first look in buffer:
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now seach input:
    char ch = 0;
    while (is>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    double left;
    Token t = ts.get();
    switch (t.kind) {
    case '(':           // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            left=d;
            Token next=ts.get();
            if(next.kind=='!')
            {
                if(left==(int)left&&left>=0)
                {
                    int res=1;
                    while(left>0)
                    {
                        res*=left;
                        left--;
                    }
                    return res;
                }
                else error("!: invalid factorial");
            }
            else
            {
                ts.putback(next);
                return left;
            }
            return left;
        }
    case number:
        {
            left=t.value;
            Token next=ts.get();
            if(next.kind=='!')
            {
                if(left==(int)left&&left>=0)
                {
                    int res=1;
                    while(left>0)
                    {
                        res*=left;
                        left--;
                    }
                    return res;
                }
                else error("!: invalid factorial");
            }
            else
            {
                ts.putback(next);
                return left;
            }
            return left;
        }   // return the number's value
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get(); // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(term());
                if (i2 == 0) error("%: divide by zero");
                left = i1%i2;
                t = ts.get();
                break;
            }
        case '!':
            {
                if(left==(int)left&&left>=0)
                {
                    int res=1;
                    while(left>0)
                    {
                        res*=left;
                        left--;
                    }
                    left=res;
                }
                else error("!: invalid factorial");
                t=ts.get();
                break;
            }
        default:
            ts.putback(t);        // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

pair<string,string> calculate()
{
    string cur=is.str();
    int begin=cur.find('[');
    int end=cur.rfind(']');
    int clone=end;
    if(begin==-1||end==-1||(begin==end))
    {
        return {"",""};
    }
    begin++;end--;
    while(begin<cur.size()&&cur[begin]==' ') begin++;
    while(end>=0&&cur[end]==' ') end--;
    string name=cur.substr(begin,end-begin+1);
    clone++;
    while(clone<cur.size()&&cur[clone]==' ') clone++;
    string to_cal=cur.substr(clone);
    while(to_cal.back()==' '||to_cal.back()==';')
    {
        to_cal.pop_back();
    }
    is.clear();
    is.str(to_cal+";");
    ts=Token_stream();
    while (is)
    try 
    {
        Token t = ts.get();
        while (t.kind == print) t=ts.get();    // first discard all "prints"
        if (t.kind == print) return {"",""};        // quit
        ts.putback(t);
        os<<to_cal<< result << expression() ;
        mp[name].insert(os.str());
        return {name,os.str()};
    }
    catch (exception& e) {
        //cout << e.what() << endl;        // write error message
        clean_up_mess();
        mp[name].clear();
        return {name,""};
    }
    catch (Quit& q)
    {
        //mp[name].insert(os.str());
        return {name,os.str()};
    }
}

//------------------------------------------------------------------------------

int main()
try 
{
    vector<string> init;
    char ch;
    string exp_str;
    string query;
    getline(cin,exp_str);
    getline(cin,query);
    auto qindex=exp_str.find('q');
    auto findex=exp_str.rfind(';');
    for(int i=findex+1;i<exp_str.size();++i)
    {
        int begin=i+1,end=i+1;
        while(begin<exp_str.size()&&exp_str[begin]!='[') ++begin;
        while(end<exp_str.size()&&exp_str[end]!=']') ++end;
        if(begin==exp_str.size()||end==exp_str.size()||begin>end) break;
        ++begin;
        --end;
        while(begin<exp_str.size()&&exp_str[begin]==' ') ++begin;
        while(end>=0&&exp_str[end]==' ') --end;
        mp[exp_str.substr(begin,end-begin+1)].clear();
    }
    if(qindex==-1)
    {
        exp_str.push_back('q');
    }
    istringstream s_in(exp_str);
    string str;
    while((ch=s_in.get())!='q')
    {
        str.push_back(ch);
        if(ch==';') init.push_back(str),str.clear();
    }
    unordered_multiset<string> seen;
    string last;
    for(auto& exp:init)
    {
        is.clear();
        is.str(exp);
        auto pr=calculate();
        os.str("");
        if(last=="")
        {
            if(pr.first.size()>0)
            {
                last=pr.first;
                seen.insert(pr.second);
            }
        }
        else if(!last.empty())
        {
            if(pr.first.size()>0)
            {
                if(seen.size()>1)
                {
                    for(auto& EP:seen)
                    {
                        mp[last].erase(EP);
                    }
                    //if(mp[last].size()==0) mp.erase(last);
                }
                seen.clear();
            }
            else if(pr.first.size()==0)
            {
                seen.insert(pr.second);
            }
        }
    }
    if(seen.size()>=2)
    {
        for(auto& EP:seen)
        {
            mp[last].erase(EP);
        }
        //if(mp[last].size()==0) mp.erase(last);
    }


    int size=query.size();
    if(query.empty()) throw COUT_OUT_EXPR{};
    int i=0,j=size-1;
    while(i<size&&query[i]==' ') ++i;
    while(j>=0&&query[j]==' ') --j;
    query=query.substr(i,j-i+1);


    if(!mp.count(query))
    {
        cout<<"["<<query<<"]";
        system("pause");
        return 4;
    }
    cout<<"["<<query<<"]";
    for(auto& str:mp[query])
    {
        cout<<'\n'<<str;
    }

    /*
    for(auto& [name,expr]:mp)
    {
        cout<<"["<<name<<"]"<<'\n';
        for(auto& exp:expr)
        {
            cout<<exp<<'\n';
        }
        cout<<endl;
    }*/


    system("pause");    // cope with Windows console mode
    return 0;
}
catch (COUT_OUT_EXPR& OUT)
{
    bool flag=false;
    for(auto& [name,expr]:mp)
    {
        if(flag) cout<<'\n';
        cout<<"["<<name<<"]";
        for(auto& exp:expr)
        {
            cout<<'\n'<<exp;
        }
        if(!flag) flag=true;
    }
    system("pause");
    return 3;
}
catch (COUT_ALL_NAME& A)
{
    /*
    bool flag=false;
    for(auto& [name,_]:mp)
    {
        if(flag) cout<<'\n';
        cout<<"["<<name<<"]";
        if(!flag) flag=true;
    }*/
    system("pause");
    return 4;
}
catch (runtime_error& e) {
    //cout << e.what() << endl;
    system("pause");
    return 1;
}
catch (...) {
    //cout << "exception \n";
    system("pause");
    return 2;
}

//------------------------------------------------------------------------------