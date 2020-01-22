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
int Registration(int& curid);
int Authorization();
int Authentication(User user);
int global_user_id = 1;
int menu_start();
int menu_registration();
int menu_authorization();
int main()
{
	setlocale(LC_ALL, "Russian");
	int answer = menu_start();
	switch (answer)
	{
	case 0://int answer_authoriz = menu_authorization(); 
		Authorization(); break;
	case 1:/*int answer_reg = menu_registration();*/
		Registration(global_user_id); break;
	case 2: system("cls"); cout << "Goodbye\n"; return 0;
	}
	return 0;
}

int Authentication(User user)
{
	if (user.role == admin)
	{
		system("cls");
		cout << "Hello, admin!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";
		int tmp = menu_admin();
		switch (tmp)
		{
		case 0: cout << "Ok\n"; break;
		case 1: cout << "Ok\n"; break;
		case 2: cout << "Ok\n"; break;
		case 3: cout << "Ok\n"; break;
		case 4: system("cls"); main();
		}
	}
	if (user.role == client)
	{
		int tmp = menu_client();
		switch (tmp)
		{
		case 0: cout << "Let's go!\n";
		case 1: system("cls"); main();
		}
	}
	return 0;
}

int Registration(int &curid)
{
	User cur;
	cur.id = curid;
	cout << "Enter login: ";
	cin.getline(cur.login, 20);
	cout << "Enter password: ";
	char password[20];
	cin.getline(password, 20);
	cout << "Choose your role:\n";
	cout << "1 ---> client\n2 ---> admin\n";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1: cur.role = client; break;
	case 2: cur.role = admin; break;
	}
	cur.password = 1125;
	ofstream f("users.dat", ios::app);
	f.write((char*)&cur, sizeof(User));
	f.close();
	curid++;
	main();
	return 0;
}

int Authorization()
{
	User iteruser;
	cout << "Enter login: ";
	char login[20];
	cin.ignore(1);
	cin.getline(login, 20);
	cout << "Enter password: ";
	char strpassword[20];
	cin.getline(strpassword, 20);
	int passwordmd5;
	passwordmd5 = 1125;
	ifstream f("users.dat");
	while (!f.eof()) {
		f.read((char*)&iteruser, sizeof(User));
		if (strcmp(iteruser.login,login)==0) {
			if (iteruser.password == passwordmd5) {
				Authentication(iteruser);
			}
		}
		else {
			cout << "Wrong user!\n";
			system("pause");
			system("cls");
			main();
		}
	}
	f.close();
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
		cout << "Hello, admin!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";
		system("cls");
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
		cout << "Hello, client!\n";
		cout << "Choose the option:\n";
		cout << "__________________\n";
		system("cls");
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