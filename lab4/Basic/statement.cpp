/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include <cctype>
#include "exp.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

using namespace std;

/* Implementation of the Statement class */


bool isD(string &obj)
{
	if (!isdigit(obj[0]))
	{
		if (obj[0] != '-') return false;
	}
	for (int i = 1; i < obj.size(); ++i)
		if (!isdigit(obj[i])) return false;
	return true;
}

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

Rem::Rem(string st = "")
{
	statement = st;
}

void Rem::ex(EvalState &st, int &l)
{
	return;
}

Input::Input(string stmt)
{
	TokenScanner scanner;
	scanner.setInput(stmt);
	scanner.ignoreWhitespace();
	statement = parseExp(scanner);
}

void Input::ex(EvalState &st, int &l)
{
	if (statement->getType() != IDENTIFIER) error("SYNTAX ERROR");
	else
	{
		cout << " ? ";
		string n = statement->toString();
		string value;
		getline(cin, value);
		while (! isD(value))
		{
			cout << "INVALID NUMBER" << endl;
			cout << " ? ";
			getline(cin, value);
		}
		int v = stoi(value);
		st.setValue(n, v);
		return;
	}
}
Let::Let(string stmt)
{
	TokenScanner scanner;
	scanner.setInput(stmt);
	scanner.ignoreWhitespace();
	statement = parseExp(scanner);
}

void Let::ex(EvalState &st, int &l)
{
	statement->eval(st);
	return;
}

Print::Print(string stmt)
{
	TokenScanner scanner;
	scanner.setInput(stmt);
	scanner.ignoreWhitespace();
	statement = parseExp(scanner);
}

void Print::ex(EvalState &st, int &l)
{
	cout << statement->eval(st) << endl;
	return;
}

If::If(string stmt)
{
	TokenScanner scanner;
	int pos1;
	int pos2;
	op = ' ';
	if (stmt.find('<') != string::npos)
	{
		op = '<';
		pos1 = stmt.find('<');
	}
	if (stmt.find('>') != string::npos)
	{
		op = '>';
		pos1 = stmt.find('>');
	}
	if (stmt.find('=') != string::npos)
	{
		op = '=';
		pos1 = stmt.find('=');
	}
	if (op == ' ') error("SYNTAX ERROR");

	if (stmt.find("THEN") != string::npos)
	{
		pos2 = stmt.find("THEN");
	}
	else error("SYNTAX ERROR");
	string str1 = stmt.substr(0, pos1);
	scanner.setInput(str1);
	scanner.ignoreWhitespace();
	con1 = parseExp(scanner);
	string str2 = stmt.substr(pos1 + 1, pos2 - pos1 - 1);
	scanner.setInput(str2);
	scanner.ignoreWhitespace();
	con2 = parseExp(scanner);
	string str3 = stmt.substr(pos2 + 4);
	scanner.setInput(str3);
	scanner.ignoreWhitespace();
	result = parseExp(scanner);
}

void If::ex(EvalState &st, int &l)
{
	if (op == '>' && con1->eval(st) > con2->eval(st)) l = result->eval(st);
	if (op == '=' && con1->eval(st) == con2->eval(st)) l = result->eval(st);
	if (op == '<' && con1->eval(st) < con2->eval(st)) l = result->eval(st);
	return;
}

Goto::Goto(string stmt)
{
	TokenScanner scanner;
	scanner.setInput(stmt);
	scanner.ignoreWhitespace();
	statement = parseExp(scanner);
}

void Goto::ex(EvalState &st, int &l)
{
	l = statement->eval(st);
	return;
}

End::End()
{

}

void End::ex(EvalState &st, int &l)
{
	l = -1;
	return;
}