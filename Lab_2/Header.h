#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "List.h"

using namespace std;

void ListCreator(int n, NodeList*& Kantor);

void Adder(NodeList& nodelist, Rational current);
void Add(NodeList& nodelist);

void Delete(NodeList& nodelist, int key);

Node* Find(NodeList nodelist, int key);

int Summ(NodeList nodelist);

