﻿#define _CRT_SECURE_NO_WARNINGS_
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

enum Role { client, admin };

struct User
{
	int id;
	char login[20];
	int password;
	Role role;
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

int menu_admin();
int menu_client();
int Registration();
int Authorization();
int Authentication(User user);
//int global_user_id = 0;
int menu_start();

int main()
{
	bool isRunning = true;
	while (isRunning)
	{
		int answer = 0;
		setlocale(LC_ALL, "Russian");
		answer = menu_start();
		switch (answer)
		{
		case 0:Authorization(); break;
		case 1:Registration(); break;
		case 2: system("cls"); cout << "Goodbye\n__________________"; isRunning = false;
		}

	}
}

int Authentication(User user)
{
	if (user.role == admin)
	{
		bool isRunning = true;
		while (isRunning)
		{
			system("cls");
			cout << "Hello, admin!\n";
			cout << "Choose the option:\n";
			cout << "__________________\n";
			int tmp = menu_admin();
			switch (tmp)
			{
			case 0: cout << "Ok\n"; isRunning = 0; return 0; break;
			case 1: cout << "Ok\n"; isRunning = 0; return 0; break;
			case 2: cout << "Ok\n"; isRunning = 0; return 0; break;
			case 3: cout << "Ok\n"; isRunning = 0; return 0; break;
			case 4: system("cls"); isRunning = 0; return 0; break;
			}
		}
	}
	if (user.role == client)
	{
		bool isRunning = true;
		while (isRunning)
		{
			system("cls");
			cout << "Hello, client!\n";
			cout << "Choose the option:\n";
			cout << "__________________\n";
			int tmp = menu_client();
			switch (tmp)
			{
			case 0: cout << "Let's go!\n"; system("pause");
			case 1: system("cls"); isRunning = 0; return 0;
			}
		}
	}
	return 0;
}

int Registration()
{
	User iteruser;
	int cnt = 0;
	ifstream f1("users.dat", ios::binary);
	while (!f1.eof()) {
		f1.read((char*)&iteruser, sizeof(User));
		cnt++;
	}
	bool isFirst = 0;
	cnt > 0 ? isFirst = 0 : isFirst = 1;
	f1.close();
	User cur;
	//cur.id = curid;
	if (isFirst)cur.id = 1;
	else cur.id = cnt++;
	cout << "\n\n" << cur.id << "\n\n";
	cout << "Enter login: ";
	cin.getline(cur.login, 19);
	cout << "Enter password: ";
	char password[20];
	cin.getline(password, 19);
	//cout << strlen(password);
	cout << "Choose your role:\n";
	cout << "1 ---> client\n2 ---> admin\n";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1: cur.role = client; break;
	case 2: cur.role = admin; break;
	}
	cur.password = md5(password, strlen(password));
	ofstream f("users.dat", ios::app, ios::binary);
	f.write((char*)&cur, sizeof(User));
	f.close();
	//curid++;
	//cout << "\n\n" << curid << "\n\n";
	return 0;
}

int Authorization()
{
	User iteruser;
	cout << "Enter login: ";
	char login[20];
	cin.getline(login, 19);
	cout << "Enter password: ";
	char strpassword[20];
	cin.getline(strpassword, 19);
	int passwordmd5;
	passwordmd5 = md5(strpassword, strlen(strpassword));
	ifstream f("users.dat", ios::binary);

	bool isAuthorised = false;

	while (!f.eof()) {
		f.read((char*)&iteruser, sizeof(User));
		if (strcmp(iteruser.login, login) == 0) {
			if (iteruser.password == passwordmd5) {
				Authentication(iteruser);
				isAuthorised = true;
				break;
			}
			else {
				cout << "Wrong password!\n";
				system("pause");
				cout << "_________________\n";
				cout << "Enter password again: ";
				cin.getline(strpassword, 19);
				passwordmd5 = md5(strpassword, strlen(strpassword));			
			}
		}
	}
	if (!isAuthorised)
	{
		cout << "Wrong login!\n";
		system("pause");
	}
	f.close();
	system("cls");

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

int menu_admin()
{
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "Hello, admin!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";

		key = (key + 5) % 5;
		if (key == 0) cout << "-> Create" << endl;
		else  cout << "   Create" << endl;
		if (key == 1) cout << "-> Read" << endl;
		else  cout << "   Read" << endl;
		if (key == 2) cout << "-> Update" << endl;
		else  cout << "   Update" << endl;
		if (key == 3) cout << "-> Delete" << endl;
		else  cout << "   Delete" << endl;
		if (key == 4) cout << "-> Exit" << endl;
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

int menu_client()
{
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "Hello, client!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";
		key = (key + 2) % 2;
		if (key == 0) cout << "-> Tests" << endl;
		else  cout << "   Tests" << endl;
		if (key == 1) cout << "-> Exit" << endl;
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