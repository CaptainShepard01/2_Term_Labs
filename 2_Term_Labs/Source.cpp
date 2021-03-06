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

int Delete(User user);
int Update(User user);
int Read(User user);
int AnswersTyping(Question cur, int FK);
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

int leftrotate(unsigned int x, int c)
{
	return (x << c) | (x >> (32 - c));
}

int md5(char* p, int n) {
	int s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
	unsigned int k[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee , 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 , 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c , 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 , 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
	unsigned int a0 = 0x67452301;   //A
	unsigned int b0 = 0xefcdab89;   //B
	unsigned int c0 = 0x98badcfe;   //C
	unsigned int d0 = 0x10325476;   //D
	string ss;
	unsigned int** u = new unsigned int* [ceil((double)n / 64) + 1];
	for (int i = 0; i < ceil((double)n / 64) + 1; i++)
		u[i] = new unsigned int[16];
	int j, jui = ceil((double)n / 64);
	for (int i = 0; i < ceil((double)n / 64) + 1; i++)
		for (int j = 0; j < 16; j++)
			u[i][j] = 0;
	for (j = 0; j < ceil((double)n / 64 - 1); j++) {

		for (int i = 64 * j + 3; i < 64 * j + 64; i += 4) {
			int y = 0;
			for (int g = i + 4; g > i; g--) {

				y *= 256;
				y += p[g];
			}
			u[j][(i - 64 * j) / 4] = y;
			//cout << u[j][(i - 64 * j) / 4] << ' ';
		}
		//cout << endl;
	}
	int tick = 0, ttick = 0;

	for (int i = 64 * j + 3; i < 64 * j + 64; i += 4) {
		int y = 0;
		tick = 0;
		for (int g = i; g > i - 4; g--) {

			y *= 256;
			if (g >= n) {
				tick = g - i + 3;
			}
			else y += p[g];
		}
		if (tick > 0) {

			y *= pow(256, 4 - tick);
			u[j][(i - 64 * j) / 4] = y + pow(256, 3 - tick);
			//cout << u[j][(i - 64 * j) / 4] << ' ';
			ttick++;
			break;
		}
		//ttick++;
		u[j][(i - 64 * j) / 4] = y;
		//cout << u[j][(i - 64 * j) / 4] << ' ';
	}
	//cout << endl;


	if (ttick < 14) {
		u[j][14] = n / pow(2, 32);
		u[j][15] = n % ((int)pow(2, 32));
	}
	else {
		jui++;
		u[j + 1][14] = n / pow(2, 32);
		u[j + 2][15] = n % ((int)pow(2, 32));
	}

	/*for (int i = 0; i < 16; i++)
		cout << u[0][i] << ' ';
	cout << endl; system("pause");*/

	////
	int** uu = new int* [jui];
	int r;
	int A, B, C, D, f, g;
	for (int j = 0; j < jui; j++) {

		A = a0;
		B = b0;
		C = c0;
		D = d0;
		for (int i = 0; i < 64; i++) {
			if (i < 16) {
				f = (B & C) | (~B & D);
				g = i;
			}
			else if (i < 32) {
				f = (D & B) | ((~D) & C);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48) {
				f = (((~B & C) | (~C & B)) & ~D) | (~((~B & C) | (~C & B)) & D);
				g = (3 * i + 5) % 16;
			}
			else {
				f = (C & ~(B | ~D)) | (~C & (B | ~D));
				g = (7 * i) % 16;
			}
			f = f + A + k[i] + u[j][g];
			A = D;
			D = C;
			C = B;
			B = B + leftrotate(f, s[i]);
		}
		a0 = a0 + A;
		b0 = b0 + B;
		c0 = c0 + C;
		d0 = d0 + D;
	}
	//cout << endl << a0 << ' ' << b0 << ' ' << c0 << ' ' << d0 << endl;
	return a0 + b0 + c0 + d0;
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
		case 0: cin.clear(); while (cin.get() != '\n'); QuestionCreator(user);  return 0; break;
		case 1: Read(user); isRunning = 0; return 0; break;
		case 2: Update(user); isRunning = 0; return 0; break;
		case 3: Delete(user); system("pause"); isRunning = 0; return 0; break;
		case 4: system("cls"); isRunning = 0; return 0; break;
		}
	}
	return 0;
}

/*int Adm_Creator(User user, bool& isRunning)
{
	int t = menu_create_adm();
	switch (t)
	{
	case 0: QuestionCreator(user); isRunning = 0; break;
	case 1: AnswerCreator(user); isRunning = 0; break;
	}
	return 0;
}*/

int Client(User user)
{
	bool isRunning = true;
	while (isRunning)
	{
		system("cls");
		int tmp = menu_client();
		switch (tmp)
		{
		case 0:
		{cout << "Hello, client!\n";
		cout << "Glad that you have chosen my quiz, " << user.login << " :)\n\n"; system("pause"); Quiz(user); isRunning = 0; break; }
		case 1: system("cls"); isRunning = 0; return 0;
		}
	}
	return 0;
}

int Registration()
{
	cin.clear(); while (cin.get() != '\n');
	User iteruser;
	int cnt = 0;
	ifstream f1("users.dat", ios::binary);

	while (f1.read((char*)&iteruser, sizeof(User))) {
		cnt++;
	}
	f1.close();
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
		f1.close();
	}

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
	FILE* file = fopen("users.dat", "ab");
	fwrite(&cur, sizeof(User), 1, file);
	fclose(file);
	/*ofstream f("users.dat", ios::app, ios::binary);
	f.write((char*)& cur, sizeof(User));
	f.close();*/
	return 0;
}

int Authorization()
{
	User iteruser;
	int cnt = 0;
	ifstream f1("users.dat", ios::binary);

	while (f1.read((char*)&iteruser, sizeof(User))) {
		cnt++;
	}
	f1.close();
	if (cnt > 0) {
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
	else {
		cout << "There are no Users, registrate first!\n";
		system("pause");
		system("cls");
		return 0;
	}
}

/*int menu_create_adm()
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
}*/

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
	while (qsttmp.read((char*)&tmp, sizeof(Question))) {
		cnt++;
	}
	qsttmp.close();

	FILE* file = fopen("questions.dat", "ab");
	//ofstream qst("questions.dat", ios::app, ios::binary);

	cnt++;
	Question cur;
	cur.PK_Q = cnt;
	int FK = cur.PK_Q;

	cur.IsDelete = 0;
	system("cls");

	cout << "PK = " << cur.PK_Q << '\n';

	cout << "Enter question: ";
	cin.clear();
	//while (cin.get() != '\n');

	cin.getline(cur.description, 99);


	fwrite(&cur, sizeof(Question), 1, file);
	//qst.write((char*)& cur, sizeof(Question));

	cout << "________\nDone!\n";

	//qst.close();
	fclose(file);

	system("pause");
	system("cls");
	cout << "Let's create some answers!\n______________________\n";
	system("pause");



	AnswersTyping(cur, FK);

	Admin(user);
	return 0;
}

int AnswersTyping(Question cur, int FK)
{
	Answer tmpans;
	ifstream ans("answers.dat", ios::binary);
	int cnt = 0;
	while (ans.read((char*)&tmpans, sizeof(Answer))) {
		cnt++;
	}
	bool isFirst = 1;
	if (cnt > 0)isFirst = 0;
	ans.close();

	system("cls");
	Answer answer[3];
	cout << cur.description << "\n__________________\n";
	//ofstream answ("answers.dat", ios::app, ios::binary);
	FILE* file = fopen("answers.dat", "ab");
	int tmpint = 0;

	cnt++;
	cout << "1-st answer: ";
	cin.clear();
	//while (cin.get() != '\n')continue;
	cin.getline(answer[0].description, 99);
	answer[0].PK_A = cnt;
	answer[0].FK_Q = FK;
	cout << "Is it correct?\n";
	cout << "1 ---> Yes\n2 ---> No\n";
	cin >> tmpint;
	switch (tmpint)
	{
	case 1: answer[0].IsCorrect = 1; break;
	case 2: answer[0].IsCorrect = 0; break;
	}
	answer[0].IsDelete = 0;
	fwrite(&answer[0], sizeof(Answer), 1, file);
	//answ.write((char*)&answer[0], sizeof(Answer));
	tmpint = 0;

	cnt++;

	cout << "2-nd answer: ";
	//cin.clear();
	while (cin.get() != '\n')continue;
	cin.getline(answer[1].description, 99);
	answer[1].PK_A = cnt;
	answer[1].FK_Q = FK;
	cout << "Is it correct?\n";
	cout << "1 ---> Yes\n2 ---> No\n";
	cin >> tmpint;
	switch (tmpint)
	{
	case 1: answer[1].IsCorrect = 1; break;
	case 2: answer[1].IsCorrect = 0; break;
	}
	answer[1].IsDelete = 0;
	fwrite(&answer[1], sizeof(Answer), 1, file);
	//answ.write((char*)&answer[1], sizeof(Answer));
	tmpint = 0;

	cnt++;

	cout << "3-rd answer: ";
	//cin.clear();
	while (cin.get() != '\n')continue;
	cin.getline(answer[2].description, 99);
	answer[2].PK_A = cnt;
	answer[2].FK_Q = FK;
	cout << "Is it correct?\n";
	cout << "1 ---> Yes\n2 ---> No\n";
	cin >> tmpint;
	switch (tmpint)
	{
	case 1: answer[2].IsCorrect = 1; break;
	case 2: answer[2].IsCorrect = 0; break;
	}
	answer[2].IsDelete = 0;
	fwrite(&answer[2], sizeof(Answer), 1, file);
	//answ.write((char*)&answer[2], sizeof(Answer));
	tmpint = 0;
	fclose(file);
	//answ.close();
	return 0;
}

int Quiz(User user)
{
	int points = 0;
	int a = 0;
	system("cls");
	Question tmpqst;
	ifstream quest("questions.dat", ios::binary);
	int cnt = 0;
	while (quest.read((char*)&tmpqst, sizeof(Question))) {
		cnt++;
	}
	quest.close();

	Question* mas = new Question[cnt];
	ifstream qsttmp("questions.dat", ios::binary);
	for (int i = 0; i < cnt; ++i) {
		qsttmp.read((char*)&mas[i], sizeof(Question));
	}
	qsttmp.close();

	ifstream answ("answers.dat", ios::binary);
	Answer ans[3];
	for (int i = 0; i < cnt; ++i) {

		system("cls");
		cout << mas[i].PK_Q << ") ";
		cout << mas[i].description << endl << endl;
		for (int j = 0; j < 3; ++j) {
			answ.read((char*)&ans[j], sizeof(Answer));
		}
		for (int j = 0; j < 3; ++j) {
			cout << j + 1 << ") ";
			cout << ans[j].description << endl;
		}
		cout << "Your answer: ";
		cin >> a;
		if (ans[a - 1].IsCorrect == 1) {
			points++;
		}
	}
	answ.close();
	system("cls");
	system("pause");
	cout << "Congratulations, " << user.login << "! " << "Your points: " << points << " of " << cnt << " \n";
	system("pause");
	ofstream ud("userdata.dat", ios::app, ios::binary);
	ud << user.login << ": " << points << " ";
	delete[] mas;

	ud.close();
	Client(user);
	return 0;
}

int Read(User user)
{
	Question qst;
	ifstream quest("questions.dat", ios::binary);
	int cnt = 0;
	while (quest.read((char*)&qst, sizeof(Question))) {
		cnt++;
	}
	quest.close();

	system("cls");
	cout << "There are all questions, answers to them and information if they are correct or not: \n";
	cout << "____________________________________________________________________________________\n";
	Question tmpqst;
	Answer tmpansw;
	//ifstream q("questions.dat", ios::binary);
	//ifstream a("answers.dat", ios::binary);
	FILE* file = fopen("answers.dat", "rb");
	FILE* file1 = fopen("questions.dat", "rb");

	for (int j = 0; j < cnt; ++j) {

		//q.read((char*)&tmpqst, sizeof(Question));
		fread(&tmpqst, sizeof(Question), 1, file1);
		cout << tmpqst.PK_Q << ") " << tmpqst.description << " " << tmpqst.IsDelete << endl << endl;

		for (int i = 0; i < 3; ++i) {
			//a.read((char*)&tmpansw, sizeof(Answer));
			fread(&tmpansw, sizeof(Answer), 1, file);

			cout << tmpansw.PK_A << ") " << tmpansw.description << " " << tmpansw.IsCorrect << " " << tmpansw.IsDelete << endl << endl;
		}
		cout << "///////////////////////\n";
	}

	system("pause");
	//q.close();
	fclose(file);
	fclose(file1);
	//a.close();
	Admin(user);
	return 0;
}

int Delete(User user)
{
	Question tmpqst;
	ifstream quest("questions.dat", ios::binary);
	int cnt = 0;
	while (quest.read((char*)&tmpqst, sizeof(Question))) {
		cnt++;
	}
	quest.close();

	Question* mas = new Question[cnt];
	ifstream qsttmp("questions.dat", ios::binary);
	for (int i = 0; i < cnt; ++i) {
		qsttmp.read((char*)&mas[i], sizeof(Question));
	}
	qsttmp.close();

	ifstream answ("answers.dat", ios::binary);
	Answer* ans = new Answer[cnt * 3];
	for (int i = 0; i < cnt * 3; ++i) {
		answ.read((char*)&ans[i], sizeof(Answer));
	}
	answ.close();

	//Read(user);
	for (int j = 0; j < cnt; ++j) {

		cout << mas[j].PK_Q << ") " << mas[j].description << " " << mas[j].IsDelete << endl << endl;

		for (int i = 0; i < 3; ++i) {
			cout << ans[j * 3 + i].PK_A << ") " << ans[j * 3 + i].description << " " << ans[j * 3 + i].IsCorrect << " " << ans[j * 3 + i].IsDelete << endl << endl;
		}
		cout << "///////////////////////\n";
	}
	cout << "\n\nWhich would you like to delete?\n\n";
	int choose = 0;
	cin.clear();
	cin >> choose;
	mas[choose - 1].IsDelete = 1;
	for (int i = 0; i < 3; ++i) {
		ans[(choose - 1) * 3 + i].IsDelete = 1;
	}
	system("pause");
	FILE* qst = fopen("questions.dat", "wb");
	for (int i = 0; i < cnt; ++i) {
		fwrite(&mas[i], sizeof(Question), 1, qst);
	}
	fclose(qst);

	FILE* answer = fopen("answers.dat", "wb");
	for (int i = 0; i < cnt * 3; ++i) {
		fwrite(&ans[i], sizeof(Answer), 1, answer);
	}
	fclose(answer);

	cout << "\nDone!\nDo you want to delete one more?\n\n";
	cout << "1 --> Yes\n2 --> No\n\n";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:system("cls"); Delete(user); break;
	case 2:Admin(user); return 0;
	}

	return 0;
}

int Update(User user)
{
	Question tmpqst;
	ifstream quest("questions.dat", ios::binary);
	int cnt = 0;
	while (quest.read((char*)&tmpqst, sizeof(Question))) {
		cnt++;
	}
	quest.close();

	Question* mas = new Question[cnt];
	ifstream qsttmp("questions.dat", ios::binary);
	for (int i = 0; i < cnt; ++i) {
		qsttmp.read((char*)&mas[i], sizeof(Question));
	}
	qsttmp.close();

	ifstream answ("answers.dat", ios::binary);
	Answer* ans = new Answer[cnt * 3];
	for (int i = 0; i < cnt * 3; ++i) {
		answ.read((char*)&ans[i], sizeof(Answer));
	}
	answ.close();

	//Read(user);
	for (int j = 0; j < cnt; ++j) {

		cout << mas[j].PK_Q << ") " << mas[j].description << " " << mas[j].IsDelete << endl << endl;

		for (int i = 0; i < 3; ++i) {
			cout << ans[j * 3 + i].PK_A << ") " << ans[j * 3 + i].description << " " << ans[j * 3 + i].IsCorrect << " " << ans[j * 3 + i].IsDelete << endl << endl;
		}
		cout << "///////////////////////\n";
	}
	cout << "\n\nWhich would you like to restore?\n\n";
	int choose = 0;
	cin.clear();
	cin >> choose;
	mas[choose - 1].IsDelete = 0;
	for (int i = 0; i < 3; ++i) {
		ans[(choose - 1) * 3 + i].IsDelete = 0;
	}
	system("pause");
	FILE* qst = fopen("questions.dat", "wb");
	for (int i = 0; i < cnt; ++i) {
		fwrite(&mas[i], sizeof(Question), 1, qst);
	}
	fclose(qst);

	FILE* answer = fopen("answers.dat", "wb");
	for (int i = 0; i < cnt * 3; ++i) {
		fwrite(&ans[i], sizeof(Answer), 1, answer);
	}
	fclose(answer);

	cout << "\nDone!\nDo you want to delete one more?\n\n";
	cout << "1 --> Yes\n2 --> No\n\n";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:system("cls"); Delete(user); break;
	case 2:Admin(user); return 0;
	}

	return 0;
}