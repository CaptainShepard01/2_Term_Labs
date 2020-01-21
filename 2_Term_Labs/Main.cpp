#define CRT_NO_SECURE_WARNINGS_
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <conio.h>
#include "Header.h"

using namespace std;

struct User
{
	int id;
	char login[20];
	char password[20];
	enum role { client, admin };
};

struct Questions
{
	int id;
	int PK_Q;
	char description[100];
	bool IsDelete = 0;    //сэкономить время
};

struct Answers
{
	int id;
	int PK_A;
	int FK_Q;
	char description[100];
	bool IsCorrect = 0;
	bool IsDelete = 0;
};


int Authentication()
{

	return 0;
}

int Authorization()
{

	return 0;
}

int Registration()
{

	return 0;
}

int menu();
int main()
{
	setlocale(LC_ALL, "Russian");
	int answer = menu();
	switch (answer)
	{
	case 0:; break;
		system("pause");
		return 0;
	}
	return 0;
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 1) % 1;
		if (key == 0) cout << "-> Palindrom (Task_1)" << endl;
		else  cout << "   Palindrom (Task_1)" << endl;
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
