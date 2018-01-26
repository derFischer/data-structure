
/*
学号：515015910005
姓名：丁丁
附加功能：以一个句首为开头并以一个句尾做结尾（如果在用户所给的单词数下没有达到句尾时，继续生成直到句尾）
          （若所给文档中没有句首/句尾，则段首/段尾显示...）
*/

#include<iostream>
#include<sstream>
#include<map>
#include<vector>
#include<queue>
#include<fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

int randomNum(int size);
class NG {};
class NL {};
class nL {};
class wrongText {};
class inputWrong {};

//N--Ngram的参数，n--所要生成段的单词数
class randomWriter
{
private:
	int N;
	map<queue<string>, vector<string>> mmap;
	queue<string> words;
	vector<queue<string>> Upper;                                         //Upper用于存放以大写字母开头的queue
	vector<queue<string>> all;                                           //all用于存放所有queue
	string name;
	int num;
	bool sig = false;                                                    //sig用于判断文件中是否含有句尾
public:
	randomWriter(int, int, string);                                      //传入N，n以及文件名构造randomWriter
	randomWriter(const randomWriter&) = delete;
	void mapp();                                                         //生成map
	void print();                                                        //打印
	void dispose();                                                      //处理
	void ifS(string);                                                    //判断此字符串是否为句尾
};

randomWriter::randomWriter(int n, int number, string nm)                 //传入N，n以及文件名构造
{
	N = n;
	num = number;
	name = nm;
}

void randomWriter::mapp()                                                //读文件并生成对应的map
{
	ifstream file(name);
	string tmp;
	int i = 1;
	while (i++ < N)                                                      //读入前N-1个单词并存入queue中
	{
		file >> tmp;
		ifS(tmp);                                                        //读入一个单词并判断是否为句尾
		words.push(tmp);
	}
	vector<string> st;
	mmap[words] = st;
	if (words.front()[0] <= 'Z'&& words.front()[0] >= 'A')  Upper.push_back(words);
	                                                                     //若words以一个大写字母开头，压入Upper
	while (file >> tmp)
	{
		ifS(tmp);                                                        //读入一个单词并判断是否为句尾
		if (mmap.find(words) != mmap.end())
		{
			mmap[words].push_back(tmp);                                  //queue在map中，将queue后的单词加入向量
		}
		else
		{
			vector<string> vv;                                           //queue不在map中，新建一组queue-vector
			vv.push_back(tmp);
			mmap[words] = vv;
		}
		words.pop();                                                     //pop去queue的第一个单词并加入新单词
		words.push(tmp);
		all.push_back(words);
		if (words.front()[0] <= 'Z'&& words.front()[0] >= 'A') Upper.push_back(words);
		                                                                 //若words以一个大写字母开头，压入Upper
	}

	ifstream in(name);                                                   //已读到文件末尾，循环读到文件头
	int pos = 1;
	while (pos++ < N)
	{
		in >> tmp;
		if (mmap.find(words) != mmap.end())
		{
			mmap[words].push_back(tmp);                                  
		}
		else
		{
			vector<string> vv;
			vv.push_back(tmp);
			mmap[words] = vv;
		}
		words.pop();                                                    
		words.push(tmp);
		all.push_back(words);
		if (words.front()[0] <= 'Z'&& words.front()[0] >= 'A')  Upper.push_back(words);
	}
}

void randomWriter::print()                                               //打印
{
	queue<string> tmp;
	queue<string> pr;
	if (!Upper.empty())                                                  //若Upper不为空，则从Upper中随机选择开头
	{
		int begin = randomNum(Upper.size());
		tmp = Upper[begin];
		pr = tmp;
	}
	else                                                                 //若Upper为空，则从all中随机选择开头
	{
		cout << "...";                                                   //没有句首，以“...”开始
		int begin = randomNum(all.size());
		tmp = all[begin];
		pr = tmp;
	}
	string st;
	for (int j = 0; j < tmp.size(); ++j)
	{
		st = pr.front();
		cout << st << ' ';
		pr.pop();
	}

	string ne;                                                           //ne保存接下来要打印的内容
	for (int i = 0; i <= num - N; ++i)                                   //随机打印到指定个数的单词
	{
		int next = randomNum(mmap[tmp].size());
		ne += mmap[tmp][next] + ' ';
		tmp.push(mmap[tmp][next]);
		tmp.pop();
	}
	if (!sig) cout << ne << "...\n";                                     //若文件中没有句尾，则打印“...”，结束
	else                                                                 //若文件中有句尾
	{                                                                    //若ne的结尾并非.?!，则继续生成
		while (ne[ne.size() - 2] != '.'&&ne[ne.size() - 2] != '?'&&ne[ne.size() - 2] != '!')
		{
			int next = randomNum(mmap[tmp].size());
			ne += mmap[tmp][next] + ' ';
			tmp.push(mmap[tmp][next]);
			tmp.pop();
		}
		cout << ne << '\n';
	}
}

void randomWriter::dispose()                                             //处理包括：生成map与打印
{
	mapp();
	print();
}

void randomWriter::ifS(string obj)                                       //判断obj是否为句尾（是否以.!?结尾）
{
	if (obj[obj.size() - 1] == '.' || obj[obj.size() - 1] == '!' || obj[obj.size() - 1] == '?') sig = true;
}

void testNN(string NN)                                                   //判断所输入的N/n是否为整数
{
	stringstream ss;
	ss << NN;
	if ((ss.str()[0] > '9' || ss.str()[0] < '0') && ss.str()[0] != '-') throw inputWrong();
	int n;
	ss >> n;
	string t;
	ss >> t;
	if (t.size()) throw inputWrong();
}

void testt(string name)                                                  //判断文件是否存在
{
	ifstream t(name);
	if (!t) throw wrongText();
}

int length(string name)                                                  //返回文件长度
{
	ifstream text(name);
	int w = 0;
	string word;
	while (text >> word) ++w;
	return w;
}

void test(string name, int N)                                            //判断所输入的N是否合理
{
	if (N > length(name)) throw NG();                                    //N不应大于文件单词数
	if (N < 2) throw NL();                                               //N不应小于2
}

void testn(int N, int n)                                                 //判断所输入的n是否合理
{
	if (n < N) throw nL();                                               //n不应小于N
}

int randomNum(int size)                                                  //生成随机数
{
	return  (size - 1)*rand() / (RAND_MAX + 1);
}

int main()
{
	srand(int(time(NULL)));
	while (true)
	{
		try
		{
			int N, num;
			string NN, nn;
			string name;
			cout << "Input file name?";
			cin >> name;
			testt(name);
			while (true)
			{
				try
				{
					cout << "Value of N?";
					cin >> NN;
					testNN(NN);
					stringstream ss;
					ss << NN;
					ss >> N;
					test(name, N);
					while (true)
					{
						try
						{
							cout << "#of random words to generate(0 to quit)?";
							cin >> nn;
							testNN(nn);
							stringstream ss;
							ss << nn;
							ss >> num;
							if (num == 0)
							{
								cout << "Exiting.";
								return 0;
							}
							testn(N, num);
							randomWriter rw(N, num, name);
							rw.dispose();
						}
						catch (nL)
						{
							cout << "Must be at least " << N << " words.\n";
						}
						catch (inputWrong)
						{
							cout << "Illegal integer format.Try again.\n";
						}
					}
				}
				catch (inputWrong)
				{
					cout << "Illegal integer format.Try again.\n";
				}
				catch (NL)
				{
					cout << "N must be 2 or greater.\n";
				}
				catch (NG)
				{
					cout << "N shouldn't be greater than the number of the words in the text.\n";
				}
			}
		}
		catch (wrongText)
		{
			cout << "Unable to open that file.  Try again.\n";
		}
	}
	return 0;
}