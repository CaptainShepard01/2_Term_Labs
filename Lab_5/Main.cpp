#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "List.h"
#include "Tree.h"
#include "Element.h"
#include "Dictionary.h"
using namespace std;

bool CompareStrByAlph(char str1[64], char str2[64])
{
	for (int i = 0; i < 64; i++)
	{
		if (strlen(str1) == i || strlen(str2) == i)
			if (strlen(str1) < strlen(str2))
				return true;
			else
				return false;

		if (str1[i] < str2[i])
			return true;
		else if (str1[i] != str2[i])
			return false;
	}

	return false;
}

bool CompareStr(char str1[64], char str2[64])
{
	for (int i = 0; str1[i] > 0 && str2[i] > 0; i++)
	{
		if (str1[i] != str2[i])
			return false;

		if (str1[i + 1] < 0 && str2[i + 1] > 0 || str2[i + 1] < 0 && str1[i + 1] > 0)
			return false;
	}

	return true;
}


int menu();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int answer = 0;
	Tree dict;
	bool isRunning = true;
	while (isRunning)
	{
		answer = menu();
		switch (answer)
		{
		case 0:Add(dict); break;
		case 1:Read(dict); break;
		case 2:Print(dict); break;
		case 3:NewDict(dict); break;
		case 4:isRunning = 0; break;
		}
	}
	return 0;
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 5) % 5;
		if (key == 0) cout << "-> Create dictionary" << endl;
		else  cout << "   Create dictionary" << endl;
		if (key == 1) cout << "-> Read" << endl;
		else  cout << "   Read" << endl;
		if (key == 2) cout << "-> Print dictionary" << endl;
		else  cout << "   Print dictionary" << endl;
		if (key == 3) cout << "-> Print old and new dictionaries" << endl;
		else  cout << "   Print old and new dictionaries" << endl;
		if (key == 4) cout << "-> Exit." << endl;
		else cout << "   Exit." << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}