
/*
ѧ�ţ�515015910005
����������
���ӹ��ܣ���һ������Ϊ��ͷ����һ����β����β��������û������ĵ�������û�дﵽ��βʱ����������ֱ����β��
          ���������ĵ���û�о���/��β�������/��β��ʾ...��
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

//N--Ngram�Ĳ�����n--��Ҫ���ɶεĵ�����
class randomWriter
{
private:
	int N;
	map<queue<string>, vector<string>> mmap;
	queue<string> words;
	vector<queue<string>> Upper;                                         //Upper���ڴ���Դ�д��ĸ��ͷ��queue
	vector<queue<string>> all;                                           //all���ڴ������queue
	string name;
	int num;
	bool sig = false;                                                    //sig�����ж��ļ����Ƿ��о�β
public:
	randomWriter(int, int, string);                                      //����N��n�Լ��ļ�������randomWriter
	randomWriter(const randomWriter&) = delete;
	void mapp();                                                         //����map
	void print();                                                        //��ӡ
	void dispose();                                                      //����
	void ifS(string);                                                    //�жϴ��ַ����Ƿ�Ϊ��β
};

randomWriter::randomWriter(int n, int number, string nm)                 //����N��n�Լ��ļ�������
{
	N = n;
	num = number;
	name = nm;
}

void randomWriter::mapp()                                                //���ļ������ɶ�Ӧ��map
{
	ifstream file(name);
	string tmp;
	int i = 1;
	while (i++ < N)                                                      //����ǰN-1�����ʲ�����queue��
	{
		file >> tmp;
		ifS(tmp);                                                        //����һ�����ʲ��ж��Ƿ�Ϊ��β
		words.push(tmp);
	}
	vector<string> st;
	mmap[words] = st;
	if (words.front()[0] <= 'Z'&& words.front()[0] >= 'A')  Upper.push_back(words);
	                                                                     //��words��һ����д��ĸ��ͷ��ѹ��Upper
	while (file >> tmp)
	{
		ifS(tmp);                                                        //����һ�����ʲ��ж��Ƿ�Ϊ��β
		if (mmap.find(words) != mmap.end())
		{
			mmap[words].push_back(tmp);                                  //queue��map�У���queue��ĵ��ʼ�������
		}
		else
		{
			vector<string> vv;                                           //queue����map�У��½�һ��queue-vector
			vv.push_back(tmp);
			mmap[words] = vv;
		}
		words.pop();                                                     //popȥqueue�ĵ�һ�����ʲ������µ���
		words.push(tmp);
		all.push_back(words);
		if (words.front()[0] <= 'Z'&& words.front()[0] >= 'A') Upper.push_back(words);
		                                                                 //��words��һ����д��ĸ��ͷ��ѹ��Upper
	}

	ifstream in(name);                                                   //�Ѷ����ļ�ĩβ��ѭ�������ļ�ͷ
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

void randomWriter::print()                                               //��ӡ
{
	queue<string> tmp;
	queue<string> pr;
	if (!Upper.empty())                                                  //��Upper��Ϊ�գ����Upper�����ѡ��ͷ
	{
		int begin = randomNum(Upper.size());
		tmp = Upper[begin];
		pr = tmp;
	}
	else                                                                 //��UpperΪ�գ����all�����ѡ��ͷ
	{
		cout << "...";                                                   //û�о��ף��ԡ�...����ʼ
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

	string ne;                                                           //ne���������Ҫ��ӡ������
	for (int i = 0; i <= num - N; ++i)                                   //�����ӡ��ָ�������ĵ���
	{
		int next = randomNum(mmap[tmp].size());
		ne += mmap[tmp][next] + ' ';
		tmp.push(mmap[tmp][next]);
		tmp.pop();
	}
	if (!sig) cout << ne << "...\n";                                     //���ļ���û�о�β�����ӡ��...��������
	else                                                                 //���ļ����о�β
	{                                                                    //��ne�Ľ�β����.?!�����������
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

void randomWriter::dispose()                                             //�������������map���ӡ
{
	mapp();
	print();
}

void randomWriter::ifS(string obj)                                       //�ж�obj�Ƿ�Ϊ��β���Ƿ���.!?��β��
{
	if (obj[obj.size() - 1] == '.' || obj[obj.size() - 1] == '!' || obj[obj.size() - 1] == '?') sig = true;
}

void testNN(string NN)                                                   //�ж��������N/n�Ƿ�Ϊ����
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

void testt(string name)                                                  //�ж��ļ��Ƿ����
{
	ifstream t(name);
	if (!t) throw wrongText();
}

int length(string name)                                                  //�����ļ�����
{
	ifstream text(name);
	int w = 0;
	string word;
	while (text >> word) ++w;
	return w;
}

void test(string name, int N)                                            //�ж��������N�Ƿ����
{
	if (N > length(name)) throw NG();                                    //N��Ӧ�����ļ�������
	if (N < 2) throw NL();                                               //N��ӦС��2
}

void testn(int N, int n)                                                 //�ж��������n�Ƿ����
{
	if (n < N) throw nL();                                               //n��ӦС��N
}

int randomNum(int size)                                                  //���������
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