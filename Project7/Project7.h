#ifndef PROJECT7_H
#define PROJECT7_H

#include "String.h"
#include "Parse.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int operate(String op, int arg1, int arg2);
bool isBinaryOperator(String op);
bool isUnaryOperator(String op);
int parse(vector<String>& expr);
void checkForComment();
bool isCommand(String token);
void processText();
int continueReading();
void processSet();
void processVar();
void printVector(vector<String> v);
void processOutput();
void parseFile();
extern void run();

#endif