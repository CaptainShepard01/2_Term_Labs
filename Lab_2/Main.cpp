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
	int n = 0, key = 0;
	cout << "How many elements?\n";
	cin >> n;
	system("pause");
	system("cls");
	NodeList* Kantor = new NodeList;
	cout << "List:\n";
	ListCreator(n, Kantor);
	bool isRunning = true;
	while (isRunning)
	{
		int answer = 0;
		setlocale(LC_ALL, "Russian");
		answer = menu();
		switch (answer)
		{
		case 0: Kantor->Print(); system("pause"); break;
		case 1: {
			Kantor->Print();
			cout << "\nEnter number of target element: ";
			cin.clear();
			cin >> key;
			system("cls");
			Find(*Kantor, key); break; 
		}
		case 2: {
			Kantor->Print();
			cout << "\nEnter number of target element: ";
			cin.clear();
			cin >> key;
			system("cls");
			Delete(*Kantor, key); break;
		}
		case 3:Summ(*Kantor); break;
		case 4:Add(*Kantor); break;
		case 5:isRunning = false; return 0;
		}

	}
	delete Kantor;
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 6) % 6;
		if (key == 0) cout << "-> Show List" << endl;
		else  cout << "   Show List" << endl;
		if (key == 1) cout << "-> Find element with a number" << endl;
		else  cout << "   Find element with a number" << endl;
		if (key == 2) cout << "-> Delete element with a number" << endl;
		else  cout << "   Delete element with a number" << endl;
		if (key == 3) cout << "-> Show summ of list's elements" << endl;
		else  cout << "   Show summ of list's elements" << endl;
		if (key == 4) cout << "-> Add element" << endl;
		else  cout << "   Add element" << endl;
		if (key == 5) cout << "-> Exit" << endl;
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
