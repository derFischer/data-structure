/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */
   virtual void ex(EvalState &st, int &l) = 0;

};


class Rem: public Statement
{
public:
	Rem(string	stmt);
	void ex(EvalState &st, int &l);
private:
	string statement;
};

class Input:public Statement 
{
public:
	Input(string stmt);
	void ex(EvalState &st, int &l);
private:
	Expression *statement;
};

class Let:public Statement 
{
public:
	Let(string stmt);
	void ex(EvalState &st, int &l);
private:
	Expression *statement;
};

class Print:public Statement
{
public:
	Print(string stmt);
	void ex(EvalState &st, int &l);
private:
	Expression *statement;
};


class If:public Statement
{
public:
	If(string stmt);
	void ex(EvalState &st, int &l);
private:
	Expression *con1;
	Expression *con2;
	char op;
	Expression *result;
};

class Goto:public Statement 
{
public:
	Goto(string stmt);
	void ex(EvalState &st, int &l);
private:
	Expression *statement;
};

class End:public Statement
{
public:
	End();
	void ex(EvalState &st, int &l);
private:
	Expression *statement;
};

#endif
