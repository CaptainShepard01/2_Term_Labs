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

int menu();

int main()
{
	int n = 0;
	cout << "How many elements?\n";
	cin >> n;
	NodeList* Kantor = new NodeList;
	ListCreator(n, Kantor);
	delete Kantor;
	return 0;
	/*bool isRunning = true;
	while (isRunning)
	{
		int answer = 0;
		setlocale(LC_ALL, "Russian");
		answer = menu();
		switch (answer)
		{
		case 0:Find(); break;
		case 1:Delete(); break;
		case 2:Summ(); break;
		case 3:Add(); break;
		case 4:isRunning = false; return 0;
		}

	}*/
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 5) % 5;
		if (key == 0) cout << "-> Find element with a number" << endl;
		else  cout << "   Find element with a number" << endl;
		if (key == 1) cout << "-> Delete element with a number" << endl;
		else  cout << "   Delete element with a number" << endl;
		if (key == 2) cout << "-> Show summ of list's elements" << endl;
		else  cout << "   Show summ of list's elements" << endl;
		if (key == 3) cout << "-> Add element" << endl;
		else  cout << "   Add element" << endl;
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
