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


int menu_start();
int menu_registration();
int menu_authorization();
int main()
{
	setlocale(LC_ALL, "Russian");
	int answer = menu_start();
	switch (answer)
	{
	case 0:int answer_authoriz = menu_authorization(); 
		Authorization(); break;
	case 1:int answer_reg = menu_registration();
		Registration(); break;
	case 2: system("cls"); cout << "Goodbye"; system("pause"); return 0;
		system("pause");
		return 0;
	}
	return 0;
}

int Authentication()
{
	 
	return 0;
}

int Registration()
{
	User cur;
	cur.id = 1;
	cout << "Enter login: ";
	cin.getline(cur.login, 20);
	cout << "Enter password: ";
	cin.getline(cur.password, 20);
	cout << "Choose your role:\n ";
	cout << "1 ---> client\n2 ---> admin\n";
	
	return 0;
}

int Authorization()
{

	return 0;
}

int menu_start() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0) cout << "-> I'd like to sign in" << endl;
		else  cout << "   I'd like to sign in" << endl;
		if (key == 1) cout << "-> I'm new user, let me create a new account" << endl;
		else  cout << "   I'm new user, let me create a new account" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
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

int menu_registration() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0) cout << "-> Enter login" << endl;
		else  cout << "   Enter login" << endl;
		if (key == 1) cout << "-> Enter password" << endl;
		else  cout << "   Enter password" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
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

int menu_authorization() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0) cout << "-> Enter login" << endl;
		else  cout << "   Enter login" << endl;
		if (key == 1) cout << "-> Enter password" << endl;
		else  cout << "   Enter password" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
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