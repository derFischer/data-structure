#include<iostream>
#include<string>
using namespace std;

const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = ">";
const string result = "="; 
double Memory;//����ʵ��MR���ܵ�ȫ�ֱ�����
class wrong {};//�����׳��Ĵ���
class Token {
public:
	char kind;
	double value;
	Token(char ch)
		:kind(ch), value(0) {}
	Token(char ch, double val)
		:kind(ch), value(val) {}
};

class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream() :full(false), buffer(0) {}

void Token_stream::putback(Token t)//��t�Ż�����
{
	if (full) throw wrong();
	buffer = t;
	full = true;
}

Token Token_stream::get()//���������еõ��ַ������ض�Ӧ��token
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch) {
	case quit:
	case print:
	case'(':
	case')':
	case'+':
	case'-':
	case'*':
	case'/':
	case'%':
	case'!':
	case'M':
	case'R':
		return Token(ch);
	case'.':
	case'0':case'1':case'2':case'3':case'4':
	case'5':case'6':case'7':case'8':case'9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		cout << "error\n";
		throw wrong();
	}
}
void Token_stream::ignore(char c)//�����ַ�ֱ��";"
{
	if (full&&c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;
	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

Token_stream ts;

double expression();
double unit();
double primary()//primary:һ��������/(expression)/R
{

	Token t = ts.get();
	switch (t.kind) {
	case'(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
		{
			cout << "error\n";
			throw wrong();
		}
		return d;
	}
	case number:
		return t.value;
	case 'R':
		return Memory;
	case '+':
		return unit();
	case'-':
		return -unit();//�����Ŵ���
	default:
		cout << "error\n";
		throw wrong();
	}
}

double unit()//unit:һ��primary/primary!  
{
	double left = primary();
	Token t = ts.get();
	switch (t.kind) {
	case'!':
	{   double result = 1;
	int num = int(left);
	if (num != left || left < 0)
	{
		cout << "error\n";
		throw wrong();
	}
	else
	{
		if (num == 0) return 1;
		else
		{
			for (int i = 1; i <= num; ++i) result *= i;
			return result;
		}
	}
	}
	default:
		ts.putback(t);
		return left;
	}
}

double term()//term:һ��unit/unit�ĳ˳�ģ����
{
	double left = unit();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case'*':
			left *= unit();
			t = ts.get();
			break;
		case'/':
		{
			double d = unit();
			if (d == 0)
			{
				cout << "error\n";
				throw wrong();
			}
			left /= d;
			t = ts.get();
			break;
		}
		case'%':
		{
			double d = unit();
			int i1 = int(left);
			if (i1 != left) 
			{
				cout << "error\n";
				throw wrong();
			}
			int i2 = int(d);
			if (i2 != d) 
			{
				cout << "error\n";
				throw wrong();      //�ж�ģ������������Ƿ�Ϊ����
			}
			if (i2 == 0) 
			{
				cout << "error\n";
				throw wrong();
			}
			left = i1 % i2;
			t = ts.get();
			break;
		}
		case'R':
		{
			cout << "error\n";
			throw wrong();
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression() //expression:term+-term
{
	double left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind)
		{
		case'+':
			left += term();
			t = ts.get();
			break;
		case'-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double MR()//MR�����еĴ洢����,M��һ��expression��
{
	double left = expression();
	Token t = ts.get();
	if (t.kind == 'M')
	{
		Memory = left;
		return left;
	}
	else
	{
		ts.putback(t);
		return left;
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
	while (cin) {
		try
		{
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print) t = ts.get();
			if (t.kind == quit) return;
			ts.putback(t);
			cout << "=" << MR() << endl;
		}
		catch (wrong) {
			clean_up_mess();
		}
	}
}


int main()
{
	try {
		calculate();
		cout << "��������˳�:";
		char a;
		cin >> a;
		return 0;
		}
	catch (runtime_error)
	{
		cerr << "error\n" << endl;
		char a;
		cin >> a;
		return 1;
	}

	catch (...)
	{
		cerr << "exception\n";
		char a;
		cin >> a;
		return 2;
	}
}