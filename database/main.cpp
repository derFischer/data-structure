#include "database.h"
#include<algorithm>
#include<ctime>
#include<random>
#include<set>
#include<regex>

//����int��ΧΪ[-2147483648, 2147483647]�������˷�Χ�ᱨ��Ϊ���жϹ��̣�����Χ��������[-100000000,1000000000]
bool isInterger(string &obj)
{
	if (obj.size() == 0)
	{
		return false;
	}
	if (obj.size() == 1)
	{
		if (!isdigit(obj[0]))
		{
			return false;
		}
		return true;
	}
	if (obj.size() > 10)
	{
		return false;
	}

	if (!isdigit(obj[0]))
	{
		if (!obj[0] == '-' || obj[0] == '+')
		{
			return false;
		}
	}
	if (obj.size() == 10)
	{
		if (obj[0] > 1)
		{
			return false;
		}
	}
	for (int i = 1; i < obj.size(); ++i)
	{
		if (!isdigit(obj[i]))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int databaseChoice;
	int choice;
	database db("");
	while (true)
	{
		cout << "��ѡ��\n"\
			"1.����һ�����ݿ⣻\n"\
			"2.��һ�����ݿ⣻\n"\
			"3.�˳���" << endl;
		string tmp;
		getline(cin, tmp);
		if (isInterger(tmp))
		{
			databaseChoice = stoi(tmp);
			if (databaseChoice >= 1 && databaseChoice <= 3)
			{
				break;
			}
			else
			{
				cout << "�޴�ѡ����������롣" << endl;
			}
		}
		else
		{
			cout << "�������룬���������롣" << endl;
		}
	}

	switch (databaseChoice)
	{
	case 1:
	{
		cout << "�����������ݿ�·�������ƣ�" << endl;
		string name;
		getline(cin, name);
		db.setPath(name);
		db.open(CREATE);
		db.close();
		db.open(READ_AND_WRITE);
		break;
	}
	case 2:
	{
		while (true)
		{
			try
			{
				cout << "���������ݿ�·�������ƣ�" << endl;
				string name;
				getline(cin, name);
				db.setPath(name);
				db.open(READ_AND_WRITE);
				break;
			}
			catch (wrongIndexFile)
			{
				cout << "���ݿⲻ���ڡ�" << endl;
			}
			catch (wrongDataFile)
			{
				cout << "���ݿⲻ���ڡ�" << endl;
			}
		}
		break;
	}
	case 3:
		exit(0);
		break;
	}
	while (true)
	{
		while (true)
		{
			cout << "��ѡ��\n"\
				"1.ͨ����ֵ�洢���ݣ�\n"\
				"2.ͨ����ֵ��ѯ���ݣ�\n"\
				"3.ͨ����ֵ�޸����ݣ�\n"\
				"4.ͨ����ֵɾ�����ݣ�\n"\
				"5.ͨ����ֵ�ָ���ɾ�����ݣ�\n"\
				"6.�˳���" << endl;
			string tmp;
			getline(cin, tmp);
			if (isInterger(tmp))
			{
				choice = stoi(tmp);
				if (databaseChoice >= 1 && databaseChoice <= 3)
				{
					break;
				}
				else
				{
					cout << "�޴�ѡ����������롣" << endl;
				}
			}
			else
			{
				cout << "�������룬���������롣" << endl;
			}
		}
		switch (choice)
		{
		case 1:
		{
			int key;
			string tmp;
			string value;
			while (true)
			{
				cout << "�������ֵ��";
				getline(cin, tmp);
				if (isInterger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "�������룬���������롣" << endl;
				}
			}
			cout << "���������ݣ�";
			getline(cin, value);
			if (db.store(key, value))
			{
				cout << "�洢�ɹ���" << endl;
			}
			else
			{
				cout << "�ü�ֵ�Ѵ��ڣ��洢ʧ�ܡ�" << endl;
			}
			break;
		}
		case 2:
		{
			int key;
			string tmp;
			string result;
			while (true)
			{
				cout << "�������ֵ��";
				getline(cin, tmp);
				if (isInterger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "�������룬���������롣" << endl;
				}
			}
			result = db.fetch(key);
			if (result != "false")
			{
				cout << "��ѯ�ɹ�������Ϊ��" << result << endl;
			}
			else
			{
				cout << "�ü�ֵ�����ڣ���ѯʧ�ܡ�" << endl;
			}
			break;
		}
		case 3:
		{
			int key;
			string tmp;
			string value;
			while (true)
			{
				cout << "�������ֵ��";
				getline(cin, tmp);
				if (isInterger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "�������룬���������룺" << endl;
				}
			}
			cout << "���������ݣ�";
			getline(cin, value);
			if (db.modify(key, value))
			{
				cout << "�޸ĳɹ���" << endl;
			}
			else
			{
				cout << "�ü�ֵ�����ڣ��޸�ʧ�ܡ�" << endl;
			}
			break;
		}
		case 4:
		{
			int key;
			string tmp;
			string result;
			while (true)
			{
				cout << "�������ֵ��";
				getline(cin, tmp);
				if (isInterger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "�������룬���������롣" << endl;
				}
			}
			if (db.remove(key))
			{
				cout << "ɾ���ɹ���" << endl;
			}
			else
			{
				cout << "�ü�ֵ�����ڣ�ɾ��ʧ�ܡ�" << endl;
			}
			break;
		}
		case 5:
		{
			int key;
			string tmp;
			while (true)
			{
				cout << "�������ֵ��";
				getline(cin, tmp);
				if (isInterger(tmp))
				{
					key = stoi(tmp);
					break;
				}
				else
				{
					cout << "�������룬���������롣" << endl;
				}
			}
			if (db.recovery(key))
			{
				cout << "�ָ��ɹ���" << endl;
			}
			else
			{
				cout << "�ָ�ʧ�ܡ�" << endl;
			}
			break;
		}
		case 6:
			exit(0);
			break;
		}
	}
}