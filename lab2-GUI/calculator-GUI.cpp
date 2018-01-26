#include<iostream>
#include"Graph.h"
#include"GUI.h"
#include"Point.h"
#include"Simple_window.h"
#include"std_lib_facilities.h"
#include"Window.h"
#include<sstream>

stringstream input;
stringstream in;
string copyToIn;
char c;
const char number = '8';
const char quit = '=';
const char print = ';';
double Memory;//用于实现MR功能的全局变量；
class wrong {};//用于抛出的错误

struct calculator :Window
{
public:
	calculator(Point xy, int w, int h, const string&title);
private:
	Button one;
	Button two;
	Button three;
	Button four;
	Button five;
	Button six;
	Button seven;
	Button eight;
	Button nine;
	Button zero;
	Button plu;
	Button min;
	Button div;
	Button mul;
	Button mod;
	Button left;
	Button right;
	Button fac;
	Button print;
	Button dec;
	Button M;
	Button R;
	Button equ;
	Button C;
	Button x;
	Button pri;
	Out_box output;
	Out_box PutResult;
	string result;
	static void cb(Address, Address);
	void cb();
	static void equal(Address,Address);
	void equal();
	static void allClear(Address, Address);
	void allClear();
	static void printTheFct(Address, Address);
	void printTheFct();
	void cal();
};

calculator::calculator(Point xy, int w, int h, const string&title)
	:Window(xy, w, h, "calculator"),
	one(Point(0, 250), 50, 50, "1", cb),
	two(Point(50, 250), 50, 50, "2", cb),
	three(Point(100, 250), 50, 50, "3", cb),
	four(Point(0, 200), 50, 50, "4", cb),
	five(Point(50, 200), 50, 50, "5", cb),
	six(Point(100, 200), 50, 50, "6", cb),
	seven(Point(0, 150), 50, 50, "7", cb),
	eight(Point(50, 150), 50, 50, "8", cb),
	nine(Point(100, 150), 50, 50, "9", cb),
	zero(Point(50, 300), 50, 50, "0", cb),
	plu(Point(150, 250), 50, 50, "+", cb),
	min(Point(150, 200), 50, 50, "-", cb),
	div(Point(150, 100), 50, 50, "/", cb),
	mul(Point(150, 150), 50, 50, "*", cb),
	mod(Point(50, 100), 50, 50, "%", cb),
	left(Point(0, 300), 50, 50, "(", cb),
	right(Point(100, 300), 50, 50, ")", cb),
	fac(Point(100, 100), 50, 50, "!", cb),
	print(Point(150, 300), 50, 50, ";", cb),
	dec(Point(0, 100), 50, 50, ".", cb),
	M(Point(0, 350), 50, 50, "M", cb),
	R(Point(50, 350), 50, 50, "R", cb),
	equ(Point(150, 350), 50, 50, "=", equal),
	output(Point(0, 0), 200, 50, "input"),
	PutResult(Point(0, 50), 200, 50, "result"),
	C(Point(100, 350), 50, 50, "C", allClear),
	x(Point(0,400),100,50,"x",cb),
	pri(Point(100,400),100,50,"print",printTheFct)
{
	attach(one);
	attach(two);
	attach(three);
	attach(four);
	attach(five);
	attach(six);
	attach(seven);
	attach(eight);
	attach(nine);
	attach(zero);
	attach(plu);
	attach(min);
	attach(div);
	attach(mul);
	attach(mod);
	attach(left);
	attach(right);
	attach(fac);
	attach(print);
	attach(dec);
	attach(M);
	attach(R);
	attach(equ);
	attach(output);
	attach(PutResult);
	attach(C);
	attach(pri);
	attach(x);
}

double MRPIC(double x = 0);
void clean_up_mess();
void calculator::cb(Address pv, Address pw) //回调函数
{
	 c = *reference_to<calculator>(pv).label();
	 reference_to<calculator>(pw).cb();

}

void calculator::cb()  //将label上的字符插入流中
{
	input << c;
	output.put(input.str());
}

void calculator::equal(Address pv, Address pw)  //'='的回调函数
{
	c = *reference_to<calculator>(pv).label();
	reference_to<calculator>(pw).equal();
}

void calculator::equal()  //计算表达式的值并将结果打印到输出框
{
	input << c;
	copyToIn = input.str();
	cal();
	input.str("");
}

void calculator::allClear(Address pv, Address pw)  //'C'的回调函数
{
	reference_to<calculator>(pw).allClear();
}

void calculator::allClear()  //清空输入框
{
	input.str("");
	output.put(input.str());
}

void calculator::printTheFct(Address pv, Address pw)  //'print'的回调函数
{
	reference_to<calculator>(pw).printTheFct();
}

void calculator::printTheFct()  //添加坐标和函数图像
{
	try
	{
		input << '=';
		copyToIn = input.str();
		Simple_window win(Point(200, 200), 600, 400, "Function graghing");
		Function s(MRPIC, -10, 11, Point(300, 200), 400, 30, 30);
		Axis x(Axis::x, Point(20, 200), 560, 560/30, "one notch=1");
		Axis y(Axis::y, Point(300, 380), 360, 360/30, "one notch=1");
		win.attach(s);
		win.attach(x);
		win.attach(y);
		win.wait_for_button();
		input.str("");
		output.put("");
		PutResult.put("");
	}
	catch (wrong)
	{
		clean_up_mess();
		PutResult.put("error;");
		output.put("");
		input.str("");
		input.clear();
		in.str("");
		in.clear();
		return;
	}
}

class Token 
{
public:
	char kind;
	double value;
	Token(char ch)
		:kind(ch), value(0) {}
	Token(char ch, double val)
		:kind(ch), value(val) {}
};

class Token_stream 
{
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

void Token_stream::putback(Token t)//将t放回流中
{
	if (full) throw wrong();
	buffer = t;
	full = true;
}

Token Token_stream::get()//从输入流中得到字符并返回对应的token
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	in >> ch;
	switch (ch) 
	{
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
	case'x':
		return Token(ch);
	case'.':
	case'0':case'1':case'2':case'3':case'4':
	case'5':case'6':case'7':case'8':case'9':
	{
		in.putback(ch);
		double val;
		in >> val;
		return Token(number, val);
	}

	default:
		throw wrong();
	}
}
void Token_stream::ignore(char c)//忽略字符直到";"
{
	if (full&&c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;
	char ch = 0;
	while (in >> ch)
		if (ch == c) return;
}

Token_stream ts;

double expression(double x=0);
double unit(double x=0);
double primary(double x=0)//primary:一个浮点数/(expression)/R
{

	Token t = ts.get();
	switch (t.kind) 
	{
	case'(':
	{
		double d = expression(x);
		t = ts.get();
		if (t.kind != ')')
		{
			throw wrong();
		}
		return d;
	}
	case number:
		return t.value;
	case 'x':
		return x;
	case 'R':
		return Memory;
	case '+':
		return unit(x);
	case'-':
		return -unit(x);//正负号处理
	default:
		ts.putback(t);
		throw wrong();
	}
}

double unit(double x)//unit:一个primary/primary!  
{
	double left = primary(x);
	Token t = ts.get();
	switch (t.kind) 
	{
	case'!':
	{   
		double result = 1;
	    int num = int(left);
	if (num != left || left < 0)
	{
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
	case'x':
		throw wrong();
	default:
		ts.putback(t);
		return left;
	}
}

double term(double x=0)//term:一个unit/unit的乘除模运算
{
	double left = unit(x);
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case'*':
			left *= unit(x);
			t = ts.get();
			break;
		case'/':
		{
			double d = unit(x);
			if (d == 0)
			{
				throw wrong();
			}
			left /= d;
			t = ts.get();
			break;
		}
		case'%':
		{
			double d = unit(x);
			int i1 = int(left);
			if (i1 != left)
			{
				throw wrong();
			}
			int i2 = int(d);
			if (i2 != d)
			{
				throw wrong();      //判断模运算的两个数是否为整数
			}
			if (i2 == 0)
			{
				throw wrong();
			}
			left = i1 % i2;
			t = ts.get();
			break;
		}
		case'R':
		{
			throw wrong();
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression(double x) //expression:term+-term
{
	double left = term(x);
	Token t = ts.get();
	while (true) 
	{
		switch (t.kind)
		{
		case'+':
			left += term(x);
			t = ts.get();
			break;
		case'-':
			left -= term(x);
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double MR(double x=0)//MR功能中的存储部分,M在一个expression后
{
	double left = expression(x);
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

double MRPIC(double x)  //用于计算函数自变量对应因变量值的函数
{
	in << copyToIn;
	double left = expression(x);
	Token t = ts.get();
	if (t.kind == 'M')
	{
		Memory = left;
		in.str("");
		in.clear();
		return left;
	}
	if (t.kind == '=')
	{
		in.str("");
		return left;
	}
	else
	{
		ts.putback(t);
		in.str("");
		in.clear();
		return left;
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

void calculator::cal()  //计算表达式的值
{
	string result;
	in << copyToIn;
	while (in) 
	{
		try
		{
			Token t = ts.get();
			while (t.kind == ';') t = ts.get();
			if (t.kind == quit) break;
			ts.putback(t);
			double R = MR();
			string tmp;
			stringstream ss;
			ss << R;
			ss >> tmp;
			result += tmp + ";";
		}
		catch (wrong) 
		{
			clean_up_mess();
			result += "error;";
		}
	}
	PutResult.put(result);
	in.clear();
	input.clear();
	in.str("");
}


int main()
{
		calculator cal(Point(300, 300), 200, 450, "calculator");
		return gui_main();
}