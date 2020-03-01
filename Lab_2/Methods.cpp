#define _USE_CRT_NO_SECURE_WARNINGS
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "Header.h"
#include "List.h"

using namespace std;

void ListCreator(int n, NodeList *&Kantor)
{
	int str = 0;
	int stlb = 0, stlbincr = 1;
	bool s = 0;
	int tmp = 0;
	int tmp_str = 0;
	Rational current;
	int current_element = 1;
	for (current_element; current_element <= n;) {
		current.number = current_element;
		current.numerator = stlb;
		current.denominator = str;
		tmp_str = str;
		Kantor->addLast(current);
		while (tmp_str != 0)
		{
			current_element++;
			tmp_str--;
			switch (s) {
			case 0: {
				stlb = stlb - stlbincr;
				stlbincr++;
				s = 1;
				break;
			}
			case 1: {
				stlb = stlb + stlbincr;
				stlbincr++;
				s = 0;
				break;
			}
			}
			current.number = current_element;
			current.numerator = stlb;
			current.denominator = tmp_str;
			Kantor->addLast(current);
		}
		str++;
		current_element++;
	}
	Kantor->Print();
}

void Add(NodeList nodelist)
{
     nodelist.tail;
}

void Delete() {};

void Find() {};

void Summ() {};

