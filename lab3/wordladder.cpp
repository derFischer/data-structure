
/*
ѧ�ţ�515015910005
����������
���ӹ��ܣ�1.word ladder�Ŀ�ͷ���β���Բ��Ǵʵ��ڵĵ���
2.֧�ֲ�ͬ���ȿ�ͷ��β
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
	string start;                                                  //word ladder�����
	string end;                                                    //word ladder���յ�
	queue<stack<string>> ladder;                                   //����partial ladder��queue
	set<string> d = ini;                                           //ini��һ�ݿ��������ڴ���
public:
	wordLadder(string, string);                                     //���캯��
	wordLadder(const wordLadder&) = delete;
	void printLadder(stack<string>&);                              //�ﵽ�յ�ʱ����ӡ��ǰ����ջ
	void dispose();                                                //����startֱ��end
	bool ifInDic(string);                                          //�ж�һ���ַ��Ƿ���d��
};

wordLadder::wordLadder(string st, string en)                        //����start��end������word ladder
{
	stack<string> tmp;
	tmp.push(st);
	ladder.push(tmp);
	start = st;
	end = en;
}

void wordLadder::printLadder(stack<string>&obj)                    //����һ��stack<string>������ʽ���
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

void wordLadder::dispose()                                         //�Ե�ǰ��word ladder���д���
{
	if (!ifInDic(end)) d.insert(end);                              //��end����d�ڣ���end����d
	if (start == end) throw sameWord();                            //start��Ӧ��end��ͬ
	cout << "A ladder from " << end << " back to " << start << " :";
	while (!ladder.empty())
	{
		string w = ladder.front().top();                           //��ȡladder����ջ�Ķ����ַ���
		for (int i = 0; i < w.size(); ++i)                         //�����滻w�еĸ�����ĸ
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
					d.erase(t);                                    //��t���ֵ��У�������ջ��ͬʱ���ֵ���ɾȥt
				}
			}
		}

		for (int i = 0; i <= w.size(); ++i)                        //��w�����β�����ĸ
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
					d.erase(t);                                    //��t���ֵ��У�������ջ��ͬʱ���ֵ���ɾȥt
				}
			}
		}

		for (int i = 0; i <= w.size() - 1; ++i)                    //��w�����μ�ȥ��ĸ
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
				d.erase(t);                                        //��t���ֵ��У�������ջ��ͬʱ���ֵ���ɾȥt
			}
		}
		ladder.pop();
	}
	cout << "No word ladder found.\n";                             //ladderΪ�գ���û���ҵ����˳���
	return;
}

bool wordLadder::ifInDic(string word)                              //�ж�word�Ƿ���d��
{
	return !(d.find(word) == d.end());
}

void init(string n)                                                //�ж��ļ��Ƿ���ڡ������ڣ������ݶ���ini
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

void testss(string obj)                                            //�ж������������Ƿ��Ϊ��ĸ               
{
	for (int i = 0; i < obj.size(); ++i)
		if ((obj[i]<'a' || obj[i]>'z') && (obj[i]<'A' || obj[i]>'Z')) throw invalidInput();
}

void tolower(string &a)                                            //���ַ�תΪСд��ĸ
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