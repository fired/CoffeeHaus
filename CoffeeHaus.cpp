#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// Any global constants
string MENUITEMS[] = { "Coffee of the Day", "Espresso", "Caffe Americano", "Caffe Latte", "Caffe Mocha", "Cappuccino" };
double PRICES[] = { 0.75, 1.50, 1.75, 3.50, 4.00, 3.25 };
int totala[6];
double subtotal[1];

double const SALESTAX = 0.055;


// Function prototypes
void display_Menu();
void get_Choice(int& choice, int& amount, int totala[], bool& flag);
void transaction(int& choice, int& amount, double subtotal[]);
void show_Receipt(double subtotal[], int totala[]);
void print_Receipt(double subtotal[], int totala[]);


int main()
{
	for (int d = 0; d < 6; d++) {
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
	cout << endl;
	cout << "\t\t**Welcome to Coffee Shop!**\n";
	cout << "\t\t\t   *Menu*" << endl;
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
	int addt;

	while (!(choice >= 0 && choice < 7)) {
		cout << "Please select an option" << endl;
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
		cin >> amount;
		if (amount < 0) {
			cout << "Please enter a positive amount" << endl;
		}
		totala[choice - 1] = amount;
	}
}

void transaction(int& choice, int& amount, double subtotal[]) {
	double totali = 0;

	totali = amount * PRICES[choice - 1];
	subtotal[0] = subtotal[0] + totali;

	cout << endl;
	cout << "You ordered " << amount << " " << MENUITEMS[choice - 1] << endl;
	cout << "The total for these items is $" << totali << endl;
	cout << "Your subtotal so far is $" << subtotal[0] << "." << endl;
	cout << endl;
}

void show_Receipt(double subtotal[], int totala[]) {
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
	cout << "\t\tSubtotal:" << "           $" << subtotal[0] << endl;
	cout << "\t\tTax:" << "                $" << tax << endl;
	cout << "\t\tTotal:" << "              $" << subtotal[0] + tax << endl;
	cout << endl;
	cout << "\t\t\tHave a Blessed Day!" << endl;
}

void print_Receipt(double subtotal[], int totala[]) {
	ofstream fout;
	fout.open("Receipt1.txt");
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
	fout << "\t\tSubtotal:" << "           $" << subtotal[0] << endl;
	fout << "\t\tTax:" << "                $" << tax << endl;
	fout << "\t\tTotal:" << "              $" << subtotal[0] + tax << endl;
	fout << endl;
	fout << "\t\tHave a Blessed Day!" << endl;

	fout.close();
}