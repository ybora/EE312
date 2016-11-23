#ifndef PROJECT7_H
#define PROJECT7_H

#include "String.h"
#include "Parse.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
 * [NAME] operate
 * [Brief] performs a mathematical operation on the given operands
 * [Returns] int: the result of the operation
 * [IN] String op: the operator
 * [IN] int arg1: the first argument
 * [IN] int arg2: the second argument
 *
 * [Summary] Performs a mathematical operation on the two given arguments based on the 
 *  provided arguments
 */
int operate(String op, int arg1, int arg2);

/*
 * [NAME] isBinaryOperator
 * [Brief] checks if a given string constitutes as a binary operator
 * [Returns] bool: whether or not the given operator is a binary operator
 * [IN] String op: the operator
 *
 * [Summary] Checks if the given string is a binary operator
 */
bool isBinaryOperator(String op);

/*
 * [NAME] isUnaryOperator
 * [Brief] checks if a given string constitutes as a unary operator
 * [Returns] bool: whether or not the given operator is a unary operator
 * [IN] String op: the operator
 *
 * [Summary] Checks if the given string is a unary operator
 */
bool isUnaryOperator(String op);

/*
 * [NAME] parse
 * [Brief] parses a mathematical expression and gives its result
 * [Returns] int: the result of the mathematical expression
 * [IN] vector<String> expr: a vector consisting the mathematical expression
 *
 * [Summary] recursively parses an expression in polish notation and returns
 * its result
 */
int parse(vector<String>& expr);

/*
 * [NAME] checkForComment
 * [Brief] checks the current token is a comment
 * [Returns] void
 * [IN] void
 *
 * [Summary] Checks if the current token being read in is a comment and skips a line
 *  in the file if it is
 */
void checkForComment();

/*
 * [NAME] isCommand
 * [Brief] checks if a given token constitutes a valid blip command
 * [Returns] bool: whether or not the given operator is a valid blip command
 * [IN] String token: the string to check 
 *
 * [Summary] Checks if the given token is a blip command
 */
bool isCommand(String token);

/*
 * [NAME] processText
 * [Brief] processes the text command in blip
 * [Returns] void
 * [IN] void
 *
 * [Summary] Reads in the next token and outputs it to the screen
 *  Then checks for a comment
 */
void processText();

/*
 * [NAME] continueReading
 * [Brief] continues reading the expression from the file
 * [Returns] int: the result of the parsed expression
 * [IN] void
 *
 * [Summary] Continues reading the current line till the end of the file or till the next 
 *  command, then calls parse to compute the result of the expression and then returns it.
 *  Used as a helper function for processOutput, processSet, and processVar.
 */
int continueReading();

/*
 * [NAME] processSet
 * [Brief] processes the set command in blip
 * [Returns] void
 * [IN] void
 *
 * [Summary] Processes the set command by using continueReading and then storing the result 
 *  into a variable in the map. Different from var because the set command is supposed to re-
 *  initialize the variable.
 */
void processSet();

/*
 * [NAME] processVar
 * [Brief] processes the var command in blip
 * [Returns] void
 * [IN] void
 *
 * [Summary] Processes the var command by using continueReading and then storing the result 
 *  into a variable in the map. Different from set because the var command is supposed to first
 *  initialize the variable.
 */
void processVar();

/*
 * [NAME] processOutput
 * [Brief] processes the output command in blip
 * [Returns] void
 * [IN] void
 *
 * [Summary] Processes the output command by using continueReading and then outputting
 *  the result to the console 
 */
void processOutput();

/*
 * [NAME] parseFile
 * [Brief] parses the given input file
 * [Returns] void
 * [IN] void
 *
 * [Summary] Parses the input file and calls one of the four process functions based on the 
 *  input. Reads until the end of the file.
 */
void parseFile();

/*
 * [NAME] run
 * [Brief] runs the program in the main
 * [Returns] void
 * [IN] void
 *
 * [Summary] Wrapper function for parseFile to be run in the main
 */
void run();

#endif