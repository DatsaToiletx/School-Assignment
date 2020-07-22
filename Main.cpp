#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// It is used to store data
struct records {
	string acc, course, name, slots;
	int num_students = 0, taken = 0;
} r[4];

void loading();		 // It is used for decoration.
void error();        // It is used to revert the program from error.

int selection, temp_num_students, temp_slots, slots_num, total, update, cancel;
string temp_course, temp_name;
bool bootup = true, looping = true;

int main() {
	while (looping == true) {
		if (bootup == true) {
			cout << " __          __  ______   __       _____   ______   __  __   ______   " << endl
				<< " \\ \\        / / |  ____| | |      /  ___| /  __  \\ |  \\/  | |  ____| " << endl
				<< "  \\ \\  /\\  / /  | |__    | |      | |     | |  | | | \\  / | | |__   " << endl
				<< "   \\ \\/  \\/ /   |  __|   | |      | |     | |  | | | |\\/| | |  __|  " << endl
				<< "    \\  /\\  /    | |____  | |____  | |___  | |__| | | |  | | | |____   " << endl
				<< "     \\/  \\/     |______| |______| \\_____| \\______/ |_|  |_| |______|" << endl
				<< endl;
			loading();
			cout << endl << "Welcome to the booking system." << endl;
			bootup = false;
			system("pause");
			system("cls");
		}

		r[0].acc = r[2].acc = "ZOOM A";                 // ************************************************
		r[1].acc = r[3].acc = "ZOOM B";					//         Record the time slots and the 
		r[0].slots = r[1].slots = "11 a.m. - 1 p.m.";	//      ZOOM account into the structure function
		r[2].slots = r[3].slots = " 2 p.m. - 4 p.m.";	// ************************************************
		// Main menu
		cout << "=======================================================================================================================\n"
			<< "                                                 * The Booking System *" << endl
			<< "=======================================================================================================================\n"
			<< "1. New booking.                                            | \n"
			<< "2. Cancel booking.                                         | --> Total no. of bookings done today : " << total << endl
			<< "3. Exit.                                                   | --> Total no. of bookings updated    : " << update << endl
			<< "                                                           | --> Total no. of bookings cancelled  : " << cancel << endl
			<< "                                                           | \n"
			<< "                                                           | \n"
			<< "                                                           | \n"
			<< " ---------+---------------+--------------------------------------------------+----------------------+------------------\n"
			<< " Account  |  Course Code  |  Course Name                                     |  Number of Students  |  Time Slots" << endl
			<< " ---------+---------------+--------------------------------------------------+----------------------+------------------\n";
		// Display the booking record.
		for (int i = 0; i < 4; i++) {
			cout << " " << setw(9) << left << r[i].acc << "| " << setw(14) << left << r[i].course << "| "
				<< setw(49) << left << r[i].name << "| " << setw(21) << left << r[i].num_students << "| " << r[i].slots << endl
				<< " ---------+---------------+--------------------------------------------------+----------------------+------------------\n";
		}
		cout << "\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A" // \x1b[A is used to move cursor up the lines.
			<< "\rSelection: ";
		cin >> selection;
		// Used to handle error.
		if (cin.fail() or (selection != 1 && selection != 2 && selection != 3) or (!isspace(cin.peek()))) {
			cout << "Please type between 1 and 3" << endl;
			error();
		}

		if (selection == 1) { // booking
			system("cls");
			cout << "=======================================================================================================================\n"
				<< "                                                 * The Booking System *" << endl
				<< "=======================================================================================================================\n"
				<< "Please fill in the following details " << endl
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
				<< "Course code                    : ";
			cin >> temp_course;
			cin.ignore(99 , '\n');
			cout << "Couse name                     : ";
			getline(cin, temp_name);
			cout << "Number of students             : ";
			cin >> temp_num_students;

			if (cin.fail() or (!isspace(cin.peek()))) {
				cout << "Only numbers are accepted." << endl;
				error();
			}
			cout << "\n           2.  2 p.m. - 4 p.m. \x1b[A \rTime slots 1. 11 a.m. - 1 p.m. : ";
			cin >> temp_slots;

			if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
				cout << "\nPlease type between 1 and 2" << endl;
				error();
			}
			cout << endl << endl;

			if (temp_num_students > 250) { // Number of students exceed 250
				cout << "ZOOM A account is selected as the number of students exceed 250" << endl;
				loading();
				if (temp_slots == 1) {      // Time slot 11 a.m. - 1 p.m.
					slots_num = 0;
				}
				else {                      // Time slot 2 p.m. - 4 p.m.
					slots_num = 2;
				}
			}
			else {							// Number of students do not exceed 250
				cout << "ZOOM B account can be used if the number of students is not excceeded 250. \nPlease select a ZOOM account" << endl
					<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
					<< "1. ZOOM A   2. ZOOM B \nSelection: ";
				cin >> selection;

				if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
					cout << "Please type between 1 and 2" << endl;
					error();
				}
				loading();

				if (selection == 1) {		// ZOOM A is selected
					if (temp_slots == 1) {
						slots_num = 0;
					}
					else {
						slots_num = 2;
					}
				}
				else {						// ZOOM B is selected
					if (temp_slots == 1) {
						slots_num = 1;
					}
					else {
						slots_num = 3;
					}
				}
			}

			if (r[slots_num].taken == 1) {  // The time slot is occupied.
				cout << "\nThis time slot has been taken. " << endl
					<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
					<< "\nDo you want to update it or cancel the booking? \n1. Update   2. Leave the old booking \nSelection: ";
				cin >> selection;

				if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
					cout << "Please type between 1 and 2" << endl;
					error();
				}

				if (selection == 1) {				// The data is overwrited
					r[slots_num].course = temp_course;
					r[slots_num].name = temp_name;
					r[slots_num].num_students = temp_num_students;
					total += 1;
					update += 1;
					cout << "\nThis time slot is successfully updated." << endl;
				}
				else {								// The booking is cancelled
					cout << "\nThis booking is cancelled." << endl;
				}
			}
			else {                  // The time slot is empty.
				cout << "\nThis time slot is empty. Do you want to book it? \n1. Yes   2. No \nSelection: ";
				cin >> selection;

				if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
					cout << "Please type between 1 and 2" << endl;
					error();
				}

				if (selection == 1) {				// The data is written
					r[slots_num].course = temp_course;
					r[slots_num].name = temp_name;
					r[slots_num].num_students = temp_num_students;
					r[slots_num].taken = 1;
					total += 1;
					cout << "\nThis time slot is successfully booked." << endl;
				}
				else {								// The booking is cancelled
					cout << "\nThis booking is cancelled." << endl;
				}
			}
			system("pause");
			system("cls");
		}

		else if (selection == 2) { // Cancel booking
			system("cls");
			cout << "=======================================================================================================================\n"
				<< "                                                 * The Booking System *" << endl
				<< "=======================================================================================================================\n"
				<< "Select which bookings to cancel" << endl
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
				<< "----------+---------------+--------------------------------------------------+----------------------+------------------\n"
				<< " Account  |  Course Code  |  Course Name                                     |  Number of Students  |  Time Slots" << endl
				<< "----------+---------------+--------------------------------------------------+----------------------+------------------\n";

			for (int i = 0; i < 4; i++) {
				cout << i + 1 << ". " << setw(7) << left << r[i].acc << "| " << setw(14) << left << r[i].course << "| "
					<< setw(49) << left << r[i].name << "| " << setw(21) << left << r[i].num_students << "| " << r[i].slots << endl
					<< "----------+---------------+--------------------------------------------------+----------------------+------------------\n";
			}
			cout << "Selection: ";
			cin >> selection;

			if (cin.fail() or (selection != 1 && selection != 2 && selection != 3 && selection != 4) or (!isspace(cin.peek()))) {
				cout << "Please type between 1 and 4" << endl;
				error();
			}
			slots_num = selection - 1;
			cout << endl << "Are you sure? \n1. Yes   2. No \nSelection: ";
			cin >> selection;

			if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
				cout << "Please type between 1 and 2" << endl;
				error();
			}
			r[slots_num].course.clear();
			r[slots_num].name.clear();
			r[slots_num].num_students = 0;
			r[slots_num].taken = 0;
			cancel += 1;
			cout << "\nThe booking is cancelled" << endl;
			system("pause");
			system("cls");
		}
		else {
			exit(0);
		}
	}
	return 0;
}

void error() {
	cin.clear();
	cin.ignore(256, '\n');
	system("pause");
	system("cls");
	main();
	return;
}

void loading() {
	for (int i = 0; i <= 4000; i++) {
		cout << "Loading . . . " << i / 40 << "%" << '\r';
	}
	cout << endl;
	return;
}