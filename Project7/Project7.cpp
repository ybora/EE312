#include "String.h"
#include "Parse.h"
#include <iostream>
#include <vector>
#include <map>

String var = String("var");
String set = String("set");
String text = String("text");
String output = String("output");
String doToken = String("do");
String od = String("od");
String ifToken = String("if");
String fi = String("fi");

using namespace std;

map<String, int> variables;

void printVector(vector<String> x) {
	for (int k = 0; k < x.size(); k++) {
		cout << x[k].c_str() << " ";
	}
	cout << endl;
}

int operate(String op, int arg1, int arg2) {
	if (op == "+") { return arg1 + arg2; }
	else if (op == "-") { return arg1 - arg2; }
	else if (op == "*") { return arg1 * arg2; }
	else if (op == "/") { return arg1 / arg2; }
	else if (op == "%") { return arg1 % arg2; }
	else if (op == "&&") { if (arg1 == 0 || arg2 == 0) return 0; return 1; }
	else if (op == "||") { if (arg1 != 0 || arg2 != 0) return 1; return 0; }
	else if (op == "<") { return arg1 < arg2; }
	else if (op == ">") { return arg1 > arg2; }
	else if (op == "<=") { return arg1 <= arg2; }
	else if (op == ">=") { return arg1 >= arg2; }
	else if (op == "==") { return arg1 == arg2; }
	else if (op == "!=") { return arg1 != arg2; }
	exit(1);
}

bool isBinaryOperator(String op) {
	if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
		return true;
	if (op == "&&" || op == "||")
		return true;
	if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=")
		return true;
	return false;
}

bool isUnaryOperator(String op) {
	if (op == "!" || op == "~") {
		return true;
	}
	return false;
}

int parse(vector<String>& expr) {
	// This method destroys the expr being passed in!
	String first = String(expr[0]); // get first token in string
	expr.erase(expr.begin()); // remove it
	
	if (variables.count(first)) {
		return variables[first];
	}

	if (isUnaryOperator(first)) {
		// Recursively get next operand
		int temp = parse(expr);

		if (first == String("~")) {
			return -temp;
		}
		else {
			return temp == 0 ? 1 : 0;
		}
	}

	if (!isBinaryOperator(first)) {
		return String::stoi(first);
	}

	// else parse the two operands recursively
	int arg1 = parse(expr);
	int arg2 = parse(expr);

	return operate(first, arg1, arg2);
}

void checkForComment() {
	if (String(next_token()) == String("//")) {
		skip_line();
		read_next_token();
	}
}

bool isCommand(String token) {
	return (token == var || token == set || token == output || token == text || token == doToken);
}

void processText() {
	// read and output the next thing
	read_next_token();
	cout << next_token();
	checkForComment();

	// keep going
	read_next_token();
	checkForComment();
}

void processText(vector<String>& statements, int& start) {
	start++;
	cout << statements[start].c_str();

	start++;
}

int continueReading() {
	vector<String> expression;
	read_next_token();
	while (!isCommand(next_token()) && next_token_type != END) {
		if (String(next_token()) == String("//")) {
			skip_line();
		}
		expression.push_back(next_token());
		read_next_token();
	}

	int result = parse(expression);
	return result;
}

int continueReading(vector<String>& statements, int& start) {
	vector<String> expression;
	start++;
	while (start < statements.size() && !isCommand(statements[start])) {
		expression.push_back(statements[start]);
		start++;
	}
	int result = parse(expression);
	return result;
}

void processSet() {
	read_next_token();
	String varName = String(next_token());
	int result = continueReading();

	if (!variables.count(varName)) {
		cout << "variable " << varName.c_str() << " not declared" << endl;
	}

	variables[varName] = result;
}

void processSet(vector<String>& statements, int& start) {
	start++;
	String varName = String(statements[start]);
	int result = continueReading(statements, start);

	variables[varName] = result;
}

void processVar() {
	read_next_token();
	String varName = String(next_token());
	int result = continueReading();

	if (variables.count(varName)) {
		cout << "variable " << varName.c_str() << " incorrectly re-initialized" << endl;
	}

	variables[varName] = result;
}

void processVar(vector<String> statements, int& start) {
	start++;
	String varName = String(statements[start]);
	int result = continueReading(statements, start);

	variables[varName] = result;
}

void processOutput() {
	int result = continueReading();
	cout << result;
}

void processOutput(vector<String> statements, int& start) {
	int result = continueReading(statements, start);
	cout << result;
}

void doDo(vector<String>& tokens) {
	for (int k = 0; k < tokens.size();) {
		if (tokens[k] == var) {
			processVar(tokens, k);
		}
		else if (tokens[k] == set) {
			processSet(tokens, k);
		} 
		else if (tokens[k] == text) {
			processText(tokens, k);
		}
		else if (tokens[k] == output) {
			processOutput(tokens, k);
		}
	}
}

void processDo() {
	vector<String> expression;
	read_next_token();
	while (!isCommand(next_token())) {
		checkForComment();
		expression.push_back(next_token());
		read_next_token();
	}

	vector<String> copy = expression;
	vector<String> mainCopy = expression;
	printVector(expression);
	int result = parse(expression);

	vector<String> tokens;
	if (result) {
		while (String(next_token()) != od) {
			checkForComment();
			if (String(next_token()) == doToken) {
				printVector(tokens);
				doDo(tokens);
				processDo();
			}
			tokens.push_back(next_token());
			read_next_token();
		}
	}

	while (parse(copy)) {
		doDo(tokens);
		copy = mainCopy;
	}
}

void processIf() {

}

void parseFile() {
	read_next_token();
	checkForComment();
	while (next_token_type != END) {
		checkForComment();
		if (next_token_type == NAME) {
			String currentToken = String(next_token());
			if (currentToken == var) {
				processVar();
			} 
			else if (currentToken == set) {
				processSet();
			}
			else if (currentToken == text) {
				processText();
			}
			else if (currentToken == output) {
				processOutput();
			}
			else if (currentToken == doToken) {
				processDo();
			}
			else if (currentToken == ifToken) {
				processIf();
			}
			else if (currentToken == od) {
				read_next_token();
			}
			else if (currentToken == fi) {
				read_next_token();
			}
		}
	}
}

void run() {
	parseFile();
}