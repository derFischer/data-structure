
/*
学号：515015910005
姓名：丁丁
附加功能：1.word ladder的开头与结尾可以不是词典内的单词
2.支持不同长度开头结尾
*/

#include<iostream>
#include<stack>
#include<queue>
#include<fstream>
#include<string>
#include<set>
using namespace std;

class sameWord {};
class invalidInput {};
class wrongDic {};
set<string> ini;

class wordLadder
{
private:
	string start;                                                  //word ladder的起点
	string end;                                                    //word ladder的终点
	queue<stack<string>> ladder;                                   //储存partial ladder的queue
	set<string> d = ini;                                           //ini的一份拷贝，用于处理
public:
	wordLadder(string, string);                                     //构造函数
	wordLadder(const wordLadder&) = delete;
	void printLadder(stack<string>&);                              //达到终点时，打印当前处理栈
	void dispose();                                                //处理start直到end
	bool ifInDic(string);                                          //判断一个字符是否在d中
};

wordLadder::wordLadder(string st, string en)                        //传入start与end，构造word ladder
{
	stack<string> tmp;
	tmp.push(st);
	ladder.push(tmp);
	start = st;
	end = en;
}

void wordLadder::printLadder(stack<string>&obj)                    //传入一个stack<string>并按格式输出
{
	while (obj.size()>1)
	{
		string tmp;
		tmp = obj.top();
		obj.pop();
		cout << tmp << "->";
	}
	cout << obj.top() << '\n';
	obj.pop();
}

void wordLadder::dispose()                                         //对当前的word ladder进行处理
{
	if (!ifInDic(end)) d.insert(end);                              //若end不在d内，将end插入d
	if (start == end) throw sameWord();                            //start不应与end相同
	cout << "A ladder from " << end << " back to " << start << " :";
	while (!ladder.empty())
	{
		string w = ladder.front().top();                           //读取ladder顶层栈的顶层字符串
		for (int i = 0; i < w.size(); ++i)                         //依次替换w中的各个字母
		{
			for (char c = 'a'; c <= 'z'; ++c)
			{
				string t = w;
				t[i] = c;
				if (ifInDic(t))
				{
					if (t == end)
					{
						ladder.front().push(t);
						printLadder(ladder.front());
						return;
					}
					stack<string> tmp = ladder.front();
					tmp.push(t);
					ladder.push(tmp);
					d.erase(t);                                    //若t在字典中，加入新栈，同时在字典中删去t
				}
			}
		}

		for (int i = 0; i <= w.size(); ++i)                        //在w中依次插入字母
		{
			for (char c = 'a'; c <= 'z'; ++c)
			{
				string t = w;
				t.insert(i, 1, c);
				if (ifInDic(t))
				{
					if (t == end)
					{
						ladder.front().push(t);
						printLadder(ladder.front());
						return;
					}
					stack<string> tmp = ladder.front();
					tmp.push(t);
					ladder.push(tmp);
					d.erase(t);                                    //若t在字典中，加入新栈，同时在字典中删去t
				}
			}
		}

		for (int i = 0; i <= w.size() - 1; ++i)                    //在w中依次减去字母
		{
			string t = w;
			t = t.erase(i, 1);
			if (ifInDic(t))
			{
				if (t == end)
				{
					ladder.front().push(t);
					printLadder(ladder.front());
					return;
				}
				stack<string> tmp = ladder.front();
				tmp.push(t);
				ladder.push(tmp);
				d.erase(t);                                        //若t在字典中，加入新栈，同时在字典中删去t
			}
		}
		ladder.pop();
	}
	cout << "No word ladder found.\n";                             //ladder为空，则没有找到，退出。
	return;
}

bool wordLadder::ifInDic(string word)                              //判断word是否在d中
{
	return !(d.find(word) == d.end());
}

void init(string n)                                                //判断文件是否存在。若存在，将内容读入ini
{
	ifstream fl(n);
	if (!fl) throw wrongDic();
	string t;
	while (!fl.eof())
	{
		getline(fl, t);
		ini.insert(t);
	}
}

void testss(string obj)                                            //判断所输入内容是否均为字母               
{
	for (int i = 0; i < obj.size(); ++i)
		if ((obj[i]<'a' || obj[i]>'z') && (obj[i]<'A' || obj[i]>'Z')) throw invalidInput();
}

void tolower(string &a)                                            //将字符转为小写字母
{
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] > 'z' || a[i] < 'a') a[i] = a[i] - 'Z' + 'z';
	}
}

int main()
{
	while (true)
	{
		try
		{
			string name;
			cout << "Dictionary file name?";
			getline(cin, name, '\n');
			init(name);
			while (true)
			{
				try
				{
					string st;
					string en;
					cout << "Word #1 (or Enter to quit): ";
					getline(cin, st, '\n');
					if (st.size() == 0)
					{
						cout << "Have a nice day.";
						cin.get();
						return 0;
					}
					cout << "Word #2 (or Enter to quit): ";
					getline(cin, en, '\n');
					if (en.size() == 0)
					{
						cout << "Have a nice day.";
						cin.get();
						return 0;
					}
					testss(st);
					testss(en);
					tolower(st);
					tolower(en);
					wordLadder wl(st, en);
					wl.dispose();
				}
				catch (sameWord)
				{
					cout << "The two words must be different.\n";
				}
				catch (invalidInput)
				{
					cout << "Please enter a word.\n";
				}

			}
		}
		catch (wrongDic)
		{
			cout << "Unable to open that file.Try again.\n";
		}
	}
	return 0;
}