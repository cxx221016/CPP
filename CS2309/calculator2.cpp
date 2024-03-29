/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

/*
    Simple calculator

    This program implements a basic expression calculator.
    Input from cin; output to cout.

    The grammar for input is:

    Statement:
        Expression
		Declaration
        Print
        Quit

    Print:
        ;

    Quit:
        quit

	Declaration:
		let Name = Expression
	Name:
		string

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
    Primary:
        Number
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal


        Input comes from cin through the Token_stream called ts.
*/
class Quit{};

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
    Token(char ch,string n):kind(ch),name(n),value(0){}
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case '!':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
        cin.unget();
	    double val;
	    cin >> val;
	    return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+= ch;
			cin.unget();
			if (s == "let") return Token(let);
			if (s == "quit") //return Token(name);
            {
                throw Quit {};
            }
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names{};

double get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	double left;
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
    	double d = expression();
	    t = ts.get();
	    if (t.kind != ')') error("'(' expected");
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
			ts.unget(next);
			return left;
		}
		return left;
	}
	case '-':
		return -primary();
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
			ts.unget(next);
			return left;
		}
	    return left;
	}
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{
    	   double d = primary();
		   if (d == 0) error("divide by zero");
		   left /= d;
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
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (true) 
    try 
    {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	calculate();
    //system("pause");
	return 0;
}
catch (Quit& q)
{
    //system("pause");
    return 0;
}
catch (exception& e) {
	cout << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
    //system("pause");
	return 1;
}
catch (...) {
	cout << "exception\n";
	char c;
	while (cin >> c && c != ';');
    //system("pause");
	return 2;
}