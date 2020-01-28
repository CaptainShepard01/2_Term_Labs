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

struct Question
{
	//int id;
	int PK_Q;
	char description[100] = {};
	bool IsDelete = 0;    //сэкономить время
};

struct Answer
{
	//int id;
	int PK_A;
	int FK_Q;
	char description[100] = {};
	bool IsCorrect = 0;
	bool IsDelete = 0;
};

int AnswersTyping(Answer& answer, int qstnmb, bool isFirst, int cnt, Question curquest);
int Admin(User user);
int Client(User user);
int Adm_Creator(User user, bool& isRunning);
int Quiz(User user);
int menu_admin();
int menu_client();
int menu_create_adm();
int Registration();
int Authorization();
int Authentication(User user);
//int global_user_id = 0;
int menu_start();
int QuestionCreator(User user);
int AnswerCreator(User user);

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
		Admin(user);
	}
	if (user.role == client)
	{
		Client(user);
	}
	return 0;
}

int Admin(User user)
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
		case 0: Adm_Creator(user, isRunning); isRunning = 0; return 0; break;
		case 1: cout << "Read\n"; system("pause"); isRunning = 0; return 0; break;
		case 2: cout << "Update\n"; system("pause"); isRunning = 0; return 0; break;
		case 3: cout << "Delete\n"; system("pause"); isRunning = 0; return 0; break;
		case 4: system("cls"); isRunning = 0; return 0; break;
		}
	}
	return 0;
}

int Adm_Creator(User user, bool& isRunning)
{
	int t = menu_create_adm();
	switch (t)
	{
	case 0: QuestionCreator(user); isRunning = 0; break;
	case 1: AnswerCreator(user); isRunning = 0; break;
	}
	return 0;
}

int Client(User user)
{
	bool isRunning = true;
	while (isRunning)
	{
		system("cls");
		int tmp = menu_client();
		switch (tmp)
		{
		case 0: cout << "Let's go!\n"; system("pause");
			system("cls");
			cout << "Hello, client!\n";
			cout << "Glad that you have chosen my quiz, " << user.login << " :)\n\n"; system("pause"); Quiz(user); isRunning = 0; break;
		case 1: system("cls"); isRunning = 0; return 0;
		}
	}
	return 0;
}

int Registration()
{
	User iteruser;
	int cnt = 0;
	ifstream f1("users.dat", ios::binary);

	while (f1.read((char*)& iteruser, sizeof(User))) {
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
		cin.clear();
		cin.getline(cur.login, 19);
		f1.close();
		f1.open("users.dat", ios::binary);
		if (isFirst == 1)isRepeated = 1;
		else {
			while (f1.read((char*)& iteruser, sizeof(User))) {
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
	f.write((char*)& cur, sizeof(User));
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
		//while (cin.get() == '\n')continue;
		cin.getline(login, 19);
		while (f.read((char*)& iteruser, sizeof(User))) {
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

int menu_create_adm()
{
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 2) % 2;
		if (key == 0) cout << "-> Create questions." << endl;
		else  cout << "   Create questions." << endl;
		if (key == 1) cout << "-> Create answers." << endl;
		else  cout << "   Create answers." << endl;
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

int QuestionCreator(User user)
{
	system("cls");
	Question tmp;
	ifstream qsttmp("questions.dat", ios::binary);
	int cnt = 0;
	while (qsttmp.read((char*)& tmp, sizeof(Question))) {
		cnt++;
	}
	qsttmp.close();


	ofstream qst("questions.dat", ios::app, ios::binary);
	cout << "Let's create some questions!\n______________________\n";

	bool isFirst = 1;
	if (cnt > 0)isFirst = 0;
	Question cur;
	if (isFirst)cur.PK_Q = 1;
	else cur.PK_Q = cnt + 1;

	cur.IsDelete = 0;

	cout << '\n';
	cout << "PK = " << cur.PK_Q << '\n';

	cout << "Enter question: ";
	cin.clear();
	cin.getline(cur.description, 99);
	qst.write((char*)& cur, sizeof(Question));
	cout << "________\nDone!\n";
	system("pause");
	qst.close();
	Admin(user);
	return 0;
}

int AnswerCreator(User user)
{
	system("cls");
	Question tmpqst;
	ifstream quest("questions.dat", ios::binary);
	int cnt = 1;   //?????????????????
	while (quest.read((char*)& tmpqst, sizeof(Answer))) {
		cnt++;
	}
	quest.close();

	bool isFirst = 1;
	if (cnt > 0)isFirst = 0;
	Question* mas = new Question[cnt];
	if (!isFirst) {
		ifstream qsttmp("questions.dat", ios::binary);
		for (int i = 0; i < cnt; ++i) {
			qsttmp.read((char*)& mas[i], sizeof(Question));
		}
		qsttmp.close();
		cout << "________________________\nQuestions: \n";
		for (int i = 0; i < cnt; ++i) {
			cout << mas[i].PK_Q << ") ";
			cout << mas[i].description << endl;
		}

	}
	else {
		cout << "____________________________________________________\nThere aren't any questions created yet, create them first!\n";
		QuestionCreator(user);
	}

	cout << "Let's create some answers!\n______________________\n";
	cout << "Which one is a chosen one?\n\n";
	Answer cur;
	int qstnmb = 0;
	cin >> qstnmb;

	Answer tmpans;
	ifstream ans("answers.dat", ios::binary);
	cnt = 1;
	while (ans.read((char*)& tmpans, sizeof(Answer))) {
		cnt++;
	}
	isFirst = 1;
	if (cnt > 0)isFirst = 0;
	ans.close();

	AnswersTyping(cur, qstnmb, isFirst, cnt, mas[qstnmb - 1]);

	delete[] mas;
	Admin(user);
	return 0;
}

int AnswersTyping(Answer& answer, int qstnmb, bool isFirst, int cnt, Question curquest)
{
	system("cls");
	cout << curquest.description << "\n__________________\n";
	ofstream answ("answers.dat", ios::app, ios::binary);
	int tmpint = 0;
	cout << "1-st answer: ";
	//cin.clear();
	while (cin.get() != '\n')continue;
	cin.getline(answer.description, 99);
	if (isFirst)answer.PK_A = 1;
	else answer.PK_A = cnt + 1;
	answer.FK_Q = qstnmb;
	cout << "Is it correct?\n";
	cout << "1 ---> Yes\n2 ---> No\n";
	cin >> tmpint;
	switch (tmpint)
	{
	case 1: answer.IsCorrect = 1; break;
	case 2: answer.IsCorrect = 0; break;
	}
	answer.IsDelete = 0;
	answ.write((char*)& answer, sizeof(Answer));

	cout << "_____________________\n2-nd answer: ";
	//cin.clear();
	while (cin.get() != '\n')continue;
	cin.getline(answer.description, 99);
	if (isFirst)answer.PK_A = 1;
	else answer.PK_A = cnt + 1;
	answer.FK_Q = qstnmb;
	cout << "Is it correct?\n";
	cout << "1 ---> Yes\n2 ---> No\n";
	cin >> tmpint;
	switch (tmpint)
	{
	case 1: answer.IsCorrect = 1; break;
	case 2: answer.IsCorrect = 0; break;
	}
	answer.IsDelete = 0;
	answ.write((char*)& answer, sizeof(Answer));
	tmpint = 0;

	cout << "_____________________\n3-rd answer: ";
	//cin.clear();
	while (cin.get() != '\n')continue;
	cin.getline(answer.description, 99);
	if (isFirst)answer.PK_A = 1;
	else answer.PK_A = cnt + 1;
	answer.FK_Q = qstnmb;
	cout << "Is it correct?\n";
	cout << "1 ---> Yes\n2 ---> No\n";
	cin >> tmpint;
	switch (tmpint)
	{
	case 1: answer.IsCorrect = 1; break;
	case 2: answer.IsCorrect = 0; break;
	}
	answer.IsDelete = 0;
	answ.write((char*)& answer, sizeof(Answer));
	tmpint = 0;

	answ.close();
	return 0;
}

int Quiz(User user)
{
	int points = 0;
	int a = 0;
	system("cls");
	Question tmpqst;
	ifstream quest("questions.dat", ios::binary);
	int cnt = 1;
	while (quest.read((char*)& tmpqst, sizeof(Question))) {
		cnt++;
	}
	quest.close();

	Question* mas = new Question[cnt];
	ifstream qsttmp("questions.dat", ios::binary);
	for (int i = 0; i < cnt; ++i) {
		qsttmp.read((char*)& mas[i], sizeof(Question));
	}
	qsttmp.close();

	ifstream answ("answers.dat", ios::binary);
	Answer* ans = new Answer[3 * cnt];
	for (int i = 0; i < 3*cnt; ++i) {
		answ.read((char*)& ans[i], sizeof(Answer));
	}
	for (int i = 0; i < cnt; ++i) {
		system("cls");
		cout << mas[i].PK_Q << ") ";
		cout << mas[i].description << endl << endl;
		for (int j = 0; j < 3; ++j) {
			cout << j + 1 << ") ";
			cout << ans[j + i * 3].description << endl;
		}
		cout << "Your answer: ";
		cin >> a;
		if (ans[(a - 1) + i * 3].IsCorrect == 1) {
			points++;
		}
	}
	answ.close();
	ofstream ud("userdata.dat", ios::app, ios::binary);
	ud << points;
	delete[] mas;
	delete[] ans;
	ud.close();
	Client(user);
	return 0;
}