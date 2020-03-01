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

void Adder(NodeList& nodelist, Rational current);

void ListCreator(int n, NodeList*& Kantor)
{
	int str = 0;
	int stlb = 0, stlbincr = 1;
	bool s = 0;
	int tmp_str = 0;
	Rational current;
	int current_element = 1;
	for (current_element; current_element <= n;) {
		current.number = current_element;
		current.numerator = stlb;
		current.denominator = str;
		tmp_str = str;
		current.s = s;
		current.stlb = stlb;
		current.str = str;
		current.tmp_str = tmp_str;
		current.stlbincr = stlbincr;

		Kantor->addLast(current);
		while (tmp_str != 0 && current_element < n)
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
			current.s = s;
			current.stlb = stlb;
			current.str = str;
			current.tmp_str = tmp_str;
			current.stlbincr = stlbincr;
			current.number = current_element;
			current.numerator = stlb;
			current.denominator = tmp_str;
			Kantor->addLast(current);
		}
		str++;
		current_element++;
		stlb = 0;
		s = 0;
		stlbincr = 1;
	}
	Kantor->Print();
	system("pause");
}

void Add(NodeList& nodelist)
{
	int nmb = nodelist.tail->info.number + 1;
	bool tmp_s = 0;
	int stolbik = 0, tmp_tmp_str = 0;
	int tmp_stlbincr = 1;
	Rational current;
	if (nodelist.tail->info.tmp_str != 0)
	{
		tmp_tmp_str = nodelist.tail->info.tmp_str - 1;
		switch (nodelist.tail->info.s) {
		case 0: {
			stolbik = nodelist.tail->info.stlb - nodelist.tail->info.stlbincr;
			tmp_stlbincr = nodelist.tail->info.stlbincr + 1;
			tmp_s = 1;
			break;
		}
		case 1: {
			stolbik = nodelist.tail->info.stlb + nodelist.tail->info.stlbincr;
			tmp_stlbincr = nodelist.tail->info.stlbincr + 1;
			tmp_s = 0;
			break;
		}
		}
		current.s = tmp_s;
		current.stlb = stolbik;
		current.str = nodelist.tail->info.str;
		current.tmp_str = tmp_tmp_str;
		current.stlbincr = tmp_stlbincr;
		current.number = nmb;
		current.numerator = stolbik;
		current.denominator = tmp_tmp_str;
	}
	else if (nodelist.tail->info.tmp_str == 0) {
		current.str = nodelist.tail->info.str + 1;
		current.tmp_str = current.str;
		current.stlb = 0;
		current.stlbincr = 1;
		current.number = nmb;
		current.numerator = stolbik;
		current.denominator = current.str;
		current.s = 0;
	}
	Adder(nodelist, current);
	nodelist.Print();
	system("pause");
}

void Adder(NodeList& nodelist, Rational current) {
	nodelist.addLast(current);
}

void Delete(NodeList& nodelist, int key) {
	nodelist.remove(key);
	system("cls");
	cout << "Updated List:\n";
	nodelist.Print();
	system("pause");
};

Node* Find(NodeList nodelist, int key) {
	return nodelist.find(key);
};

int Summ(NodeList nodelist) {
	int sum = 0;

	return sum;
};

