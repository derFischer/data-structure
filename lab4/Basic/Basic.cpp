/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include <set>
#include "statement.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

set<string> gs = { "REM","INPUT","LET","PRINT","END","IF","THEN","GOTO","RUN","LIST","CLEAR","HELP","QUIT" };

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   while (true) 
   {
      try 
	  {
		 cin.clear();
		 cin.sync();
         processLine(getLine(), program, state);
      }
	  catch (ErrorException & ex)
	  {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   string st = scanner.nextToken();
   TokenType s = scanner.getTokenType(st);
   if (s == NUMBER)
   {
	   stringstream ss;
	   ss << st;
	   int ln;
	   ss >> ln;
	   scanner.ignoreWhitespace();
	   string next = scanner.nextToken();
	   if (next == "")
	   {
		   if (program.getSourceLine(ln) == "") return;
		   else
		   {
			   program.removeSourceLine(ln);
			   return;
		   }
	   }
	   if (gs.find(next) == gs.end()) error("SYNTAX ERROR");
	   else
	   {
		   string stmt1 = line.substr(st.size() + 1);
		   string stmt = line.substr(st.size() + next.size() + 1);
		   program.addSourceLine(ln, stmt1);
		   if (next == "REM")
		   {
			   Rem *stm = new Rem (stmt);
			   program.setParsedStatement(ln, stm);
			   return;
		   }
		   if (next == "INPUT")
		   {
			   Input *stm = new Input(stmt);
			   program.setParsedStatement(ln, stm);
			   return;
		   }
		   if (next == "LET")
		   {
			   Let *stm = new Let(stmt);
			   program.setParsedStatement(ln, stm);
			   return;
		   }
		   if (next == "PRINT")
		   {
			   Print *stm = new Print(stmt);
			   program.setParsedStatement(ln, stm);
			   return;
		   }
		   if (next == "END")
		   {
			   End *stm = new End();
			   program.setParsedStatement(ln, stm);
			   return;
		   }
		   if (next == "IF")
		   {
			   If *stm = new If(stmt);
			   program.setParsedStatement(ln, stm);
			   return;
		   }
		   if (next == "GOTO")
		   {
			   Goto *stm = new Goto(stmt);
			   program.setParsedStatement(ln, stm);
			   return;
		   }
		   error("SYNTAX ERROR");
	   }
   }

   if (s == WORD)
   {
	   string stmt = line.substr(st.size());
	   if (st == "RUN")
	   {
		   int ln = program.getFirstLineNumber();
		   while (ln != -1)
		   {
			   int tmp = ln;
			   Statement *exec = program.getParsedStatement(ln);
			   exec->ex(state, ln);
			   if (ln != tmp)
			   {
				   if (ln == -1) return;
				   if (program.getSourceLine(ln) == "") error("LINE NUMBER ERROR");
			   }
			   else
			   {
				   ln = program.getNextLineNumber(ln);
			   }
		   }
		   return;
	   }

	   if (st == "LIST")
	   {
		   int ln = program.getFirstLineNumber();
		   while (ln != -1)
		   {
			   cout << ln << ' ' << program.getSourceLine(ln) << '\n';
			   ln = program.getNextLineNumber(ln);
		   }
		   return;
	   }

	   if (st == "CLEAR")
	   {
		   program.clear();
		   state.clear();
		   return;
	   }

	   if (st == "HELP")
	   {
		   cout << "..." << '\n';
		   return;
	   }
	   
	   if (st == "QUIT")
	   {
		   exit(0);
	   }
	   
	   if (st == "PRINT")
	   {
		   int t = 0;
		   Print smt(stmt);
		   smt.ex(state, t);
		   return;
	   }
	   
	   if (st == "INPUT")
	   {
		   int t = 0;
		   Input smt(stmt);
		   smt.ex(state, t);
		   return;
	   }

	   if (st == "LET")
	   {
		   int t = 0;
		   Let smt(stmt);
		   smt.ex(state, t);
		   return;
	   } 
	   error("SYNTAX ERROR");
   }
}
