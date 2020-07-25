#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int month_june[17] = { 15,16,17,18,19,22,23,24,25,26,29,30 }, month_july[23] = { 1,2,3,6,7,8,9,10,13,14,15,16,17,20,21,22,23,24,27,28,29,30,31 };
int month_august[21] = { 3,4,5,6,7,10,11,12,13,14,17,18,19,20,21,24,25,26,27,28,31 }, month_september[14] = { 1,2,3,4,7,8,9,10,11,14,15,16,17,18 };

void loading();		 // It is used for decoration.
void error();        // It is used to revert the program from error.
void booking();
void calender();
void checking();

ofstream outfile;
ifstream infile;

int selection, temp_num_students, temp_slots, counting;
string temp_acc, temp_course, temp_name, temp_timeslots, temp_time, temp, check , current_time;
bool bootup = true, looping = true;
int time_year, time_month, time_day, time_date;

int main() { 
	calender();
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
	// Main menu
	cout << "=======================================================================================================================\n"
		<< "                                                 * The Booking System *" << endl
		<< "=======================================================================================================================\n"
		<< "1. New booking.                                            | \n"
		<< "2. Cancel booking.                                         | \n"
		<< "3. Exit.                                                   | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< " Booking list for today                                    | \n"
		<< " ---------+---------------+--------------------------------------------------+----------------------+------------------\n"
		<< " Account  |  Course Code  |  Course Name                                     |  Number of Students  |  Time Slots" << endl
		<< " ---------+---------------+--------------------------------------------------+----------------------+------------------\n";
	infile.open("booking.txt");
	while (getline(infile, temp_acc)) {
		getline(infile,temp_timeslots);
		infile >> temp_course;
		infile.ignore(1);
		getline(infile, temp_name);
		infile >> temp_num_students;
		infile >> temp_time;
		infile.ignore(100, '\n');
		if (temp_time == current_time) {
			cout << " " << setw(9) << left << temp_acc << "| " << setw(14) << left << temp_course << "| "
				<< setw(49) << left << temp_name << "| " << setw(21) << left << temp_num_students << "| " << temp_timeslots << endl
				<< " ---------+---------------+--------------------------------------------------+----------------------+------------------\n";
			counting++;
		}
	}
	infile.close();
	
	cout << "\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A";
	for (int j = 0; j < counting; j++) {
		cout << "\x1b[A\x1b[A";
	}
	counting = 0;
	cout << "\rSelection: ";
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
			<< "The booking is only available for June semester ( 15 June 2020 --> 20 September 2020)                                  \n"
			<< "        |             June              |                                       |             July              |      \n"
			<< "        | Mon | Tues | Wed | Thur | Fri |                                       | Mon | Tues | Wed | Thur | Fri |      \n"
			<< "        |     |      |     |      |     |                                       |     |      |  1  |   2  |  3  |      \n"
			<< "        |     |      |     |      |     |                                       |  6  |   7  |  8  |   9  | 10  |      \n"
			<< "        | 15  |  16  | 17  |  18  | 19  |                                       | 13  |  14  | 15  |  16  | 17  |      \n"
			<< "        | 22  |  23  | 24  |  25  | 26  |                                       | 20  |  21  | 22  |  23  | 24  |      \n"
			<< "        | 29  |  30  |     |      |     |                                       | 27  |  28  | 29  |  30  | 31  |      \n"
			<< "        |            August             |                                       |           September           |      \n"
			<< "        | Mon | Tues | Wed | Thur | Fri |                                       | Mon | Tues | Wed | Thur | Fri |      \n"
			<< "        |  3  |   4  |  5  |   6  |  7  |                                       |     |   1  |  2  |   3  |  4  |      \n"
			<< "        | 10  |  11  | 12  |  13  | 14  |                                       |  7  |   8  |  9  |  10  | 11  |      \n"
			<< "        | 17  |  18  | 19  |  20  | 21  |                                       | 14  |  15  | 16  |  17  | 18  |      \n"
			<< "        | 24  |  25  | 26  |  27  | 28  |                                       |     |      |     |      |     |      \n"
			<< "        | 31  |      |     |      |     |                                       |     |      |     |      |     |      \n"
			<< "Choose which day to book for a time slots (Format: DDMM, example: 1506)." << endl
			<< "Selection: ";
		cin >> temp;
		temp_time = temp + "2020";
		temp.length();
		temp.insert(2, " ");
		checking();
 		cout << "=======================================================================================================================\n"
			<< "                                                 * The Booking System *" << endl
			<< "=======================================================================================================================\n"
			<< "Please fill in the following details " << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
			<< "Course code                    : ";
		cin >> temp_course;
		cin.ignore(99, '\n');
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
				temp_acc = "Zoom A";
				temp_timeslots = "Slot 11am-1pm";
				booking();
			}
			else {                      // Time slot 2 p.m. - 4 p.m.
				temp_acc = "Zoom A";
				temp_timeslots = "Slot 2pm-4pm";
				booking();
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
					temp_acc = "Zoom A";
					temp_timeslots = "Slot 11am-1pm";
					booking();
				}
				else {
					temp_acc = "Zoom A";
					temp_timeslots = "Slot 2pm-4pm";
					booking();
				}
			}
			else {						// ZOOM B is selected
				if (temp_slots == 1) {
					temp_acc = "Zoom B";
					temp_timeslots = "Slot 11am-1pm";
					booking();
				}
				else {
					temp_acc = "Zoom B";
					temp_timeslots = "Slot 2pm-4pm";
					booking();
				}
			}
		}
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

		infile.open("booking.txt");
		while (getline(infile, temp_acc)) {
			getline(infile, temp_timeslots);
			infile >> temp_course;
			infile.ignore(1);
			getline(infile, temp_name);
			infile >> temp_num_students;
			infile >> temp_time;
			infile.ignore(100, '\n');
			if (temp_time == current_time) {
				cout << " " << setw(9) << left << temp_acc << "| " << setw(14) << left << temp_course << "| "
					<< setw(49) << left << temp_name << "| " << setw(21) << left << temp_num_students << "| " << temp_timeslots << endl
					<< "----------+---------------+--------------------------------------------------+----------------------+------------------\n";
			}
			counting++;
		}
		infile.close();
		cout << "Selection: ";
		cin >> selection;

		if (cin.fail() or (selection != 1 && selection != 2 && selection != 3 && selection != 4) or (!isspace(cin.peek()))) {
			cout << "Please type between 1 and 4" << endl;
			error();
		}
		cout << endl << "Are you sure? \n1. Yes   2. No \nSelection: ";
		cin >> selection;

		if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
			cout << "Please type between 1 and 2" << endl;
			error();
		}
			
		cout << "\nThe booking is cancelled" << endl;
		system("pause");
		system("cls");
	}
	else {
		exit(0);
	}

return 0;
}

void booking() {
	if (temp_slots == 7) {  // The time slot is occupied.
		cout << "\nThis time slot has been taken. " << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			<< "\nDo you want to update it or cancel the booking? \n1. Update   2. Leave the old booking \nSelection: ";
		cin >> selection;

		if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
			cout << "Please type between 1 and 2" << endl;
			error();
		}

		if (selection == 1) {				// The data is overwrited

			cout << "\nThis time slot is successfully updated." << endl;
		}
		else {								// The booking is cancelled
			cout << "\nThis booking is cancelled." << endl;
		}
	}
	else {
		cout << "\nThis time slot is empty. Do you want to book it? \n1. Yes   2. No \nSelection: ";
		cin >> selection;

		if (cin.fail() or (selection != 1 && selection != 2) or (!isspace(cin.peek()))) {
			cout << "Please type between 1 and 2" << endl;
			error();
		}

		if (selection == 1) {				// The data is written
			outfile.open("booking.txt", ios::app);
			outfile << temp_acc << endl << temp_timeslots << endl << temp_course << " " << temp_name << endl << temp_num_students << endl << temp_time << endl;
			cout << "\nThis time slot is successfully booked." << endl;
			outfile.close();
		}
		else {								// The booking is cancelled
			cout << "\nThis booking is cancelled." << endl;
		}
		system("pause");
		system("cls");
		main();
	}
}

void error() {
	cin.clear();
	cin.ignore(256, '\n');
	system("pause");
	system("cls");
	main();
}

void loading() {
	for (int i = 0; i <= 4000; i++) {
		cout << "Loading . . . " << i / 40 << "%" << '\r';
	}
	cout << endl;
}

void calender() {
	time_t timer; timer = time(NULL);
	struct tm* ab; ab = localtime(&timer);
	time_year = (ab->tm_year) + 1900; time_month = (ab->tm_mon) + 1; time_day = (ab->tm_mday);
	if (time_month < 10 && time_day < 10) {
		current_time = "0" + to_string(time_day) + "0" + to_string(time_month) + to_string(time_year);
	}
	else if (time_month < 10) {
		current_time = to_string(time_day) + "0" + to_string(time_month) + to_string(time_year);
	}
	else if (time_day < 10) {
		current_time = "0" + to_string(time_day) + to_string(time_month) + to_string(time_year);
	}
	else {
		current_time = to_string(time_day) + to_string(time_month) + to_string(time_year);
	}
	/*struct tm start = { 0 };
	struct date {
		int june, july, august, september;
	}r[25];
	start.tm_year = 120; start.tm_mon = 5; start.tm_mday = 15; start.tm_wday = 1;
	int i = 0, display;
	bool loop = true;
	while (loop == true) {
		if (start.tm_wday == 7) {
			start.tm_wday = 0;
		}

		if (start.tm_mon == 5 && start.tm_mday == 31) {
			start.tm_mon++; start.tm_mday = 1; i = 0;
		}
		if (start.tm_mon == 6 && start.tm_mday == 32) {
			start.tm_mon++; start.tm_mday = 1; i = 0;
		}
		if (start.tm_mon == 7 && start.tm_mday == 32) {
			start.tm_mon++; start.tm_mday = 1; i = 0;
		}

		if (start.tm_mon == 8 && start.tm_mday == 21) {
			loop = false;
		}

		if (start.tm_mon == 5 && (start.tm_wday == 1 || start.tm_wday == 2 || start.tm_wday == 3 || start.tm_wday == 4 || start.tm_wday == 5)) {
			r[i].june = start.tm_mday;
			i++;
		}
		else if (start.tm_mon == 6 && (start.tm_wday == 1 || start.tm_wday == 2 || start.tm_wday == 3 || start.tm_wday == 4 || start.tm_wday == 5)) {
			r[i].july = start.tm_mday;
			i++;
		}
		else if (start.tm_mon == 7 && (start.tm_wday == 1 || start.tm_wday == 2 || start.tm_wday == 3 || start.tm_wday == 4 || start.tm_wday == 5)) {
			r[i].august = start.tm_mday;
			i++;
		}
		else {
			r[i].september = start.tm_mday;
		}
		start.tm_mday++; start.tm_wday++;
	}
	cout << "Choose what month you want to display." << endl;
	cin >> display;
	switch (display) {
	case 6:
		cout << "These are the days available for booking in June" << endl;
		for (i = 0; i < 12; i++) {
			cout << " | " << r[i].june;
			if ((i + 1) % 5 == 0) {
				cout << " | " << endl;
			}
		}
		break;
	case 7:
		cout << "these are the days available for booking in July" << endl;
		for (i = 0; i < 23; i++) {
			cout << " | " << r[i].july;
			if ((i + 1) % 5 == 0) {
				cout << " | " << endl;
			}
		}
		break;
	case 8:
		cout << "these are the days available for booking in August" << endl;
		for (i = 0; i < 21; i++) {
			cout << " | " << r[i].august;
			if ((i + 1) % 5 == 0) {
				cout << " | " << endl;
			}
		}
		break;
	case 9:
		cout << "these are the days available for booking in September" << endl;
		for (i = 0; i < 14; i++) {
			cout << " | " << r[i].september;
			if ((i + 1) % 5 == 0) {
				cout << " | " << endl;
			}
		}
		break;
	}*/
	return;
}

void checking() {
	int i = 1, j , day = 0, month = 0;
	bool correct = false;
	stringstream check_value;
	check_value << temp;
	check = "";
	while (check_value >> check) {
		switch (i) {
			case 1:
				stringstream(check) >> day;
				i++;
				break;
			case 2:
				stringstream(check) >> month;
				break;
		}
		check = "";
	}

	switch (month) {
		case 6:
			for (j = 0; j <= 16; j++) {
				if (day == month_june[j]) {
					correct = true;
				}
			}
			break;
		case 7:
			for (j = 0; j <= 22; j++) {
				if (day == month_july[j]) {
					correct = true;
				}
			}
			break;
		case 8:
			for (j = 0; j <= 20; j++) {
				if (day == month_august[j]) {
					correct = true;
				}
			}
			break;
		case 9:
			for (j = 0; j <= 13; j++) {
				if (day == month_september[j]) {
					correct = true;
				}
			}
			break;
	}

	if (correct == false) {
		cout << "Please choose the date between Monday and Friday." << endl;
		system("pause");
		system("cls");
		main();
	}
	system("cls");
	return;
}