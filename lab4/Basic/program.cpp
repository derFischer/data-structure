/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
#include <limits.h>
using namespace std;
#define MAX INT_MAX

Program::Program()
{
}

Program::~Program()
{
	for (map<int, Statement*>::iterator i = statements.begin(); i != statements.end(); ++i)
	{
		delete i->second;
   }
	statements.clear();
	lines.clear();
}

void Program::clear()
{
	lines.clear();
	for (map<int, Statement*>::iterator i = statements.begin(); i != statements.end(); ++i)
	{
		delete i->second;
	}
	statements.clear();
	return;
}

void Program::addSourceLine(int lineNumber, string line) 
{
	lines[lineNumber] = line;
	return;
}

void Program::removeSourceLine(int lineNumber)
{
	lines.erase(lineNumber);
	statements.erase(lineNumber);
	return;
}

string Program::getSourceLine(int lineNumber) 
{
	if (lines.count(lineNumber) == 0) return"";
    return lines[lineNumber];    
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) 
{
	statements[lineNumber] = stmt;
	return;
}

Statement *Program::getParsedStatement(int lineNumber)
{
    return statements[lineNumber]; 
}

int Program::getFirstLineNumber() 
{
	if (lines.empty()) return -1;
	int i = MAX;
	for (map<int, string>::iterator j = lines.begin(); j != lines.end(); ++j)
		if (i > j->first) i = j->first;
	return i;
}

int Program::getNextLineNumber(int lineNumber)
{
	int i = MAX;
	for (map<int, string>::iterator j = lines.begin(); j != lines.end(); ++j)
	{
		if (j->first > lineNumber && i > j->first) i = j->first;
	}
	if (i == MAX) return -1;
    return i;
}
