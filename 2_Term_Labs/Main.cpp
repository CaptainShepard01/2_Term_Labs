#define _CRT_SECURE_NO_WARNINGS_
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
	char login[20] = {};
	int password;
	Role role;
};

struct Questions
{
	int id;
	int PK_Q;
	char description[100] = {};
	bool IsDelete = 0;    //сэкономить время
};

struct Answers
{
	int id;
	int PK_A;
	int FK_Q;
	char description[100] = {};
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
int QuestionCreator();

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
		case 2: system("cls"); cout << "Goodbye!\n__________________"; isRunning = false;
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

	while (f1.read((char*)&iteruser, sizeof(User))) {
		cnt++;
	}
	bool isFirst = 1;
	if (cnt > 0)isFirst = 0;
	User cur;
	if (isFirst)cur.id = 1;
	else cur.id = cnt + 1;
	bool isRepeated = 0;
	while (!isRepeated) {
		system("cls");
		cout << "\n" << "Id = " << cur.id << "\n\n";
		cout << "Enter login: ";
		//cout << isFirst << endl;
		cin.clear();
		while (cin.get() == '\n')continue;
		cin.getline(cur.login, 19);
		f1.close();
		f1.open("users.dat", ios::binary);
		if (isFirst == 1)isRepeated = 1;
		else {
			while (f1.read((char*)&iteruser, sizeof(User))) {
				if (strcmp(cur.login, iteruser.login) == 0) {
					cout << "Login is taken!\n";
					system("pause");
					isRepeated = 0;
					break;
				}
				isRepeated = 1;
			}
		}

	}
	f1.close();
	cout << "Enter password: ";
	char password[20];
	cin.getline(password, 19);
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
	return 0;
}

int Authorization()
{
	User iteruser;


	char strpassword[20] = {};
	bool isOk = 0;
	while (!isOk) {
		system("cls");
		ifstream f("users.dat", ios::binary);
		char login[20] = {};
		cout << "Enter login: ";
		cin.clear();
		while (cin.get() == '\n')continue;
		cin.getline(login, 19);
		while (f.read((char*)&iteruser, sizeof(User))) {
			if (strcmp(iteruser.login, login) == 0) {
				isOk = 1;
				break;
			}
		}
		f.close();
		if (isOk == 1) {
			int passwordmd5;
			do {
				system("cls");
				cout << "Current login: " << login << '\n';
				cout << "Enter password: ";
				cin.getline(strpassword, 19);
				passwordmd5 = md5(strpassword, strlen(strpassword));
			} while (iteruser.password != passwordmd5);
		}

	}

	system("cls");
	Authentication(iteruser);
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

int QuestionCreator()
{
	ofstream qst("questions.dat", ios::app, ios::binary);

	qst.close();
	return 0;
}