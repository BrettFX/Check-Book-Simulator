/*
 * Main.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: Brett Allen
 *
 *  This program simulates a working bank account system. The program can: save the account balance,
 *  save the number of transactions performed on the account, allow deposits to be made to the account,
 *  allow withdrawals to be taken form the account, calculate interest for the period,
 *  report the current account balance at any time, and report the current number of transactions
 *  at any time.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "Account.h"

using namespace std;

void sys(string);
void displayMenu();
void makeDeposit(Account &);
void withdraw(Account &);
void clearScreen();

const char *PATH1 = ".\\Files\\Current_Balance.txt";
const char *PATH2 = ".\\Files\\Beginning_Balance.txt";

int main()
{
	ifstream inFile;
	ofstream outFile;
	inFile.open(PATH2); //Beginning balance
	outFile.open(PATH1); //Current balance
	string input = "";
	double newInput;

	inFile >> input;
	stringstream convert(input);

	inFile.close();

	if ( !(convert >> newInput) )
	    newInput = 0.0;

	//Creating instance of Account object
	Account savings(0.045, newInput);

	char choice[50]; //Potential memory ramification (implement try catch)

	cout << fixed << showpoint << setprecision(2);

	do
	{
		//clearScreen();
		//Display menu
		displayMenu();
		cin >> choice;

		//Validate choice
		while(toupper(choice[0]) < 'A' || toupper(choice[0]) > 'G')
		{
			//clearScreen();
			cout << "Please make a choice in the range A - G: ";
			displayMenu();
			cin >> choice;
		}

		//Process selection
		switch(choice[0])
		{
		case 'a':
		case 'A':
			cout << "The current balance is $";
			cout << savings.getBalance() << endl;
			break;
		case 'b':
		case 'B':
			cout << "There have been ";
			cout << savings.getTransactions() << " transactions.\n";
			break;
		case 'c':
		case 'C':
			cout << "Interest earned for this period: $";
			cout << savings.getInterest() << endl;
			break;
		case 'd':
		case 'D':
			makeDeposit(savings);
			break;
		case 'e':
		case 'E':
			withdraw(savings);
			break;
		case 'f':
		case 'F':
			savings.calcInterest();
			cout << "Interest added.\n";
		}

	}while(toupper(choice[0]) != 'G');

	//Modularize this

	outFile.clear();
	outFile << savings.getBalance();

	outFile.close();

	inFile.open(PATH1); //Current balance
	outFile.open(PATH2); //Beginning balance

	inFile >> input;

	//Write the value of input to beginning balance
	outFile << input;

	inFile.close();
	outFile.close();

	sys("pause");
	return 0;
}

void sys(string command)
{
	if(command == "pause")
	{
		cout << "Press enter to continue . . .";
		cin.get();
		cin.get();
	}
}

void displayMenu()
{
	cout << "\n\t\tMENU\n";
	cout << "-----------------------------------------\n";
	cout << "A) Display account balance\n";
	cout << "B) Display number of transactions\n";
	cout << "C) Display interest earned for this period\n";
	cout << "D) Make deposit\n";
	cout << "E) Make withdrawal\n";
	cout << "F) Add interest for this period\n";
	cout << "G) Exit\n\n";
	cout << ">>> ";
}

void makeDeposit(Account &acct)
{
	double dollars;

	cout << "Enter the amount of the deposit: ";
	cin >> dollars;
	cin.ignore();
	acct.makeDeposit(dollars);
}

void withdraw(Account &acct)
{
	double dollars;

	cout << "Enter the amount of the withdrawal: ";
	cin >> dollars;
	cin.ignore();
	if(!acct.withdraw(dollars))
	{
		cout << "ERROR: Withdrawal amount too large.\n\n";
	}
}

void clearScreen()
{
	HANDLE                     hStdOut;
	  CONSOLE_SCREEN_BUFFER_INFO csbi;
	  DWORD                      count;
	  DWORD                      cellCount;
	  COORD                      homeCoords = { 0, 0 };

	  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	  if (hStdOut == INVALID_HANDLE_VALUE) return;

	  /* Get the number of cells in the current buffer */
	  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	  /* Fill the entire buffer with spaces */
	  if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	  /* Fill the entire buffer with the current colors and attributes */
	  if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	  /* Move the cursor home */
	  SetConsoleCursorPosition( hStdOut, homeCoords );
}

