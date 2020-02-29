#pragma once
#define CRT_NO_SECURE_WARNINGS_
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
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

using namespace std;

int leftrotate(unsigned int x, int c);
int md5(char* p, int n);

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
	int PK_Q = 0;
	char description[100] = {};
	bool IsDelete = 0;    //сэкономить время
};

struct Answer
{
	//int id;
	int PK_A = 0;
	int FK_Q = 0;
	char description[100] = {};
	bool IsCorrect = 0;
	bool IsDelete = 0;
};

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