#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <fstream>
#include <conio.h>
#include "Structures.h"
using namespace std;

Node* ExpressionTree(char* c, Stack*& stack);
char* getString();
char* stringCorrector(char* src);
double eval(Node* root);
bool isSin(char f, char s, char t);
bool isCos(char f, char s, char t);
bool variableToFloat(char* v, double& ins, Tree*& tree);

