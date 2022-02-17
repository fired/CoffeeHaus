#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <string>
#include <fstream>
using namespace std;

// Any global constants
string MENUITEMS[] = { "Coffee of the Day", "Espresso", "Caffe Americano", "Caffe Latte", "Caffe Mocha", "Cappuccino" };
double PRICES[] = { 0.75, 1.50, 1.75, 3.50, 4.00, 3.25 };
int totala[6]; // track total amount of items bought per item
double subtotal[1]; // track subtotal

double const SALESTAX = 0.055; // for tax addition


// Function prototypes
void display_Menu();
void get_Choice(int& choice, int& amount, int totala[], bool& flag);
void transaction(int& choice, int& amount, double subtotal[]);
void show_Receipt(double subtotal[], int totala[]);
void print_Receipt(double subtotal[], int totala[]);


int main()
{
	for (int d = 0; d < 6; d++) { // fills the array with -1 to read later to see what was actually bought
		totala[d] = -1;
	}
	bool flag = false;
	while (!flag) {
		int choice = -1;
		int amount = -1;

		// Your program goes here!
		display_Menu();
		get_Choice(choice, amount, totala, flag);
		if (choice != 7) {
			transaction(choice, amount, subtotal);
		}

	}
	cout << "Thank you for ordering" << endl;
	show_Receipt(subtotal, totala);
	print_Receipt(subtotal, totala);

	return 0;
}

void display_Menu() {
	//***********************************************************
	// 
	// display_Menu prints all the options that are are in the 
	// coffee shop
	// 
	// Sent in: Nothing
	// Sent back: Nothing
	// 
	//***********************************************************
	cout << endl;
	cout << "\t\t**Welcome to Coffee Shop!**\n";
	cout << "\t\t\t       *Menu*" << endl;
	cout << endl;
	cout << "\t\t1. Coffee of the Day      $0.75" << endl;
	cout << "\t\t2. Espresso               $1.50" << endl;
	cout << "\t\t3. Caffe Americano        $1.75" << endl;
	cout << "\t\t4. Caffe Latte            $3.50" << endl;
	cout << "\t\t5. Caffe Mocha            $4.00" << endl;
	cout << "\t\t6. Cappucino              $3.25" << endl;
	cout << "\t\t7. Done Ordering" << endl;
}

void get_Choice(int& choice, int& amount, int totala[], bool& flag) {
	//***************************************************************
	// 
	// get_Choice asks the user to select an option and to select an 
	// amount of the option they want to get. Will also account for 
	// if the user wants to stop ordering. 
	// 
	// Sent in: choice, amount, totala[], flag
	// Sent back: changed array totala values, flag
	// 
	//***************************************************************
	int addt;

	while (!(choice >= 0 && choice < 7)) {
		cout << "Please select an option" << endl;
		cout << "\t";
		cin >> choice;
		if (choice == 7) {
			flag = true;
			break;
		}
		if (choice < 0 || choice > 7) {
			cout << "Pleaes enter a valid choice" << endl;
		}
	}
	while (!(amount > 0) && choice != 7) {
		cout << "Please select an amount" << endl;
		cout << "\t";
		cin >> amount;
		if (amount < 0) {
			cout << "Please enter a positive amount" << endl;
		}
		totala[choice - 1] = amount + totala[choice - 1];
	}
}

void transaction(int& choice, int& amount, double subtotal[]) {
	//*********************************************************
	//
	// transaction will take the choice and correlate it to price
	// to display what you ordered and amount, total for the items
	// bought, and subtotal so far. 
	// 
	// Sent in: choice, amount, subtotal[]
	// Sent back: changed array subtotal
	// 
	//*********************************************************
	double totali = 0;

	totali = amount * PRICES[choice - 1];
	subtotal[0] = subtotal[0] + totali;

	cout << endl;
	cout << "You ordered " << amount << " " << MENUITEMS[choice - 1] << endl;
	cout << "The total for these items is $" << fixed << setprecision(2) << totali << endl;
	cout << "Your subtotal so far is $" << fixed << setprecision(2) << subtotal[0] << "." << endl;
	cout << endl;
}

void show_Receipt(double subtotal[], int totala[]) {
	//**********************************************
	//
	// show_Receipt will show what you have ordered
	// in total at the end of your order.
	// 
	// Sent in: subtotal[], totala[]
	// Sent back: Nothing
	// 
	//**********************************************
	double tax = subtotal[0] * SALESTAX;
	cout << endl;
	cout << "\t*    *    *    *    *    *    *    *    *    *    *" << endl;
	cout << "\tThank you for your order at Coffee Shop!" << endl;
	cout << "\t*    *    *    *    *    *    *    *    *    *    *" << endl;
	cout << endl;
	for (int i = 0; i < 6; i++) {
		if (totala[i] >= 0) {
			double t = totala[i] * PRICES[i];
			cout << "\t" << totala[i] << "   " << MENUITEMS[i] << "   at   " << "$" << PRICES[i] << "   for" << "   $" << t << endl;
		}
	}
	cout << endl;
	cout << endl;
	cout << "\t\tSubtotal:" << "           $" << fixed << setprecision(2) << subtotal[0] << endl;
	cout << "\t\tTax:" << "                $" << fixed << setprecision(2) << tax << endl;
	cout << "\t\tTotal:" << "              $" << fixed << setprecision(2) << subtotal[0] + tax << endl;
	cout << endl;
	cout << "\t\t\tHave a Blessed Day!" << endl;
}

void print_Receipt(double subtotal[], int totala[]) {
	//***********************************************
	//
	// print_Receipt takes everything from show receipt
	// and puts it into a text file to be able to look
	// at it later. 
	// 
	// Sent in: subtotal[], totala[]
	// Sent back: Nothing
	// 
	//***********************************************
	ofstream fout;
	string endtxt = ".txt";
	string reciname;

	cout << endl;
	cout << "What is your first name and first name only?:\n";
	cin >> reciname;

	fout.open(reciname + endtxt);
	if (!fout.is_open()) {
		cout << "unable to open file" << endl;
		return;
	}

	double tax = subtotal[0] * SALESTAX;
	fout << "\t*    *    *    *    *    *    *    *    *    *    *" << endl;
	fout << "\tThank you for your order at Coffee Shop!" << endl;
	fout << "\t*    *    *    *    *    *    *    *    *    *    *" << endl;
	fout << endl;

	for (int i = 0; i < 6; i++) {
		if (totala[i] >= 0) {
			double t = totala[i] * PRICES[i];
			fout << "\t" << totala[i] << "   " << MENUITEMS[i] << "   at   " << "$" << PRICES[i] << "   for" << "   $" << t << endl;
		}
	}
	fout << endl;
	fout << endl;
	fout << "\t\tSubtotal:" << "           $" << fixed << setprecision(2) << subtotal[0] << endl;
	fout << "\t\tTax:" << "                $" << fixed << setprecision(2) << tax << endl;
	fout << "\t\tTotal:" << "              $" << fixed << setprecision(2) << subtotal[0] + tax << endl;
	fout << endl;
	fout << "\t\t\tHave a Blessed Day!" << endl;

	fout.close();
}