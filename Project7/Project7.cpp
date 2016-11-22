#include "String.h"
#include "Parse.h"
#include <iostream>
#include <vector>
#include <map>

String var = String("var");
String set = String("set");
String text = String("text");
String output = String("output");

using namespace std;

map<String, int> variables;

// operate on the two operands
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

// operate on the two operands
// This is the primary method in this exercise.
// It is called recursively
int parse(vector<String>& expr) {
	// This method destroys the expr being passed in!
	String first = String(expr[0]); // get first token in string
	expr.erase(expr.begin()); // remove it
							  // base case; if first token is a number (not operator), return the number
	
	if (variables.count(first)) return variables[first];

	if (isUnaryOperator(first)) {
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
	return (token == var || token == set || token == output || token == text);
}

void processText() {
	read_next_token();
	cout << next_token();
	checkForComment();
	read_next_token();
	checkForComment();
}

int continueReading() {
	vector<String> expression;
	read_next_token();
	while (!isCommand(next_token())) {
		if (String(next_token()) == String("//")) {
			skip_line();
		}
		expression.push_back(next_token());
		read_next_token();
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

void processVar() {
	read_next_token();
	String varName = String(next_token());
	int result = continueReading();

	if (variables.count(varName)) {
		cout << "variable incorrectly re-initialized" << endl;
	}

	variables[varName] = result;
}

void printVector(vector<String> v) {
	for (int k = 0; k < v.size(); k++) {
		cout << v[k].c_str() << endl;
	}
}

void processOutput() {
	int result = continueReading();
	cout << result;
}

void parseFile() {
	read_next_token();
	checkForComment();
	while (next_token_type != END) {
		if (next_token_type == NAME) {
			String currentToken = String(next_token());
			if (currentToken == var) {
				processVar();
			} 
			if (currentToken == set) {
				processSet();
			}
			if (currentToken == text) {
				processText();
			}
			if (currentToken == output) {
				processOutput();
			}
		}
	}
}

void run() {
	parseFile();
}