﻿#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct searching {
	string date_list, course_list, course_name_list;
}searchs[280];

int month_june[17] = { 15,16,17,18,19,22,23,24,25,26,29,30 };
int month_july[23] = { 1,2,3,6,7,8,9,10,13,14,15,16,17,20,21,22,23,24,27,28,29,30,31 };
int month_august[21] = { 3,4,5,6,7,10,11,12,13,14,17,18,19,20,21,24,25,26,27,28,31 };
int month_september[14] = { 1,2,3,4,7,8,9,10,11,14,15,16,17,18 };
int date_count = 0, course_count = 0, course_name_count = 0;

int selection, temp_num_students, temp_slots, counting, time_year, time_month, time_day, time_date, error_num, error_return, result;
string compare_acc, compare_timeslots, compare_course, compare_name, compare_num_students, compare_time;
string temp_acc, temp_course, temp_name, temp_timeslots, temp_time, current_time, temp;
bool bootup = true, replace = false;

string updateAccount[4], updateTimeslot[4], updateCourse[4], updateName[4], updateTime[4], account;
int updateNum[4] = { 0 }, numberUpdate, line = 0, update_num = 0;

void menu();
void search();
void update();
void update2();
void cancel();
void checking();
void checking2();
void booking();
void error();        // It is used to revert the program from error.
void loading();		 // It is used for decoration.
void current_date();


ofstream outfile;
ifstream infile;

int main() { 
	current_date();
	error_return = 0;
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
	cout << "========================================================================================================================\n"
		<< "                                                  * The Booking System *" << endl
		<< "========================================================================================================================\n"
		<< "1. New booking.                                            | 2. Search booking. \n"
		<< "3. Update booking.                                         | 4. Cancel booking. \n"
		<< "5. Exit.                                                   | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< "                                                           | \n"
		<< " Booking list for today                                    | \n"
		<< " ---------+-------------+----------------------------------------------------------------+--------------+---------------\n"
		<< "  Account | Course Code |  Course Name                                                   | Student Num. | Time Slots" << endl
		<< " ---------+-------------+----------------------------------------------------------------+--------------+---------------\n";
	infile.open("booking.txt");
	while (getline(infile, temp_acc)) {
		getline(infile,temp_timeslots);
		infile >> temp_course;
		infile.ignore(1);
		getline(infile, temp_name);
		infile >> temp_num_students >> temp_time;
		infile.ignore(100, '\n');
		if (temp_time == current_time) {
			cout << "  " << setw(8) << left << temp_acc << "| " << setw(12) << left << temp_course << "| "
				<< setw(63) << left << temp_name << "| " << setw(13) << left << temp_num_students << "| " << temp_timeslots << endl
				<< " ---------+-------------+----------------------------------------------------------------+--------------+---------------\n";
			counting++;
		}
	}
	infile.close();
	
	cout << "\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A\x1b[A";
	for (int j = 0; j < counting; j++) {
		cout << "\x1b[A\x1b[A";
	}
	counting = 0;
	cout << "\rSelection: ";
	cin >> selection;
	
	error_num = 5;
	error();

	if (selection == 1) { // booking
		menu();
	}
	else if (selection == 2) {
		system("cls");
		search();
	}
	else if (selection == 3) {
		system("cls");
		update();
	}
	else if (selection == 4) { // Cancel booking
		system("cls");
		cancel();
	}
	else {
		exit(0);
	}

return 0;
}

void menu(){
	error_return = 1; temp = "0000";
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
	stringstream s(temp);
	s >> selection;
	error_num = 9999;
	error();

	temp_time = temp + "2020";
	temp.insert(2, " ");
	checking();

	cout << "\nPlease fill in the following details " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "Course code                        : ";
	cin >> temp_course;
	cin.ignore(99, '\n');
	cout << "Couse name                         : ";
	getline(cin, temp_name);
	cout << "Number of students (range: 1 - 500): ";
	cin >> selection;

	error_num = 500;
	error();
	temp_num_students = selection;

	cout << "\n           2.  2 p.m. - 4 p.m. \x1b[A \rTime slots 1. 11 a.m. - 1 p.m.     : ";
	cin >> selection;
	cout << endl << endl;
	error_num = 2;
	error();
	temp_slots = selection;

	if (temp_num_students > 250) { // Number of students exceed 250
		cout << "ZOOM A account is selected as the number of students exceed 250" << endl;
		loading();
		if (temp_slots == 1) {      // Time slot 11 a.m. - 1 p.m.
			temp_acc = "Zoom A";
			temp_timeslots = "Slot 11am-1pm";
			checking2();
		}
		else {                      // Time slot 2 p.m. - 4 p.m.
			temp_acc = "Zoom A";
			temp_timeslots = "Slot 2pm-4pm";
			checking2();
		}
	}
	else {							// Number of students do not exceed 250
		cout << "ZOOM B account can be used if the number of students is not excceeded 250. \n\nPlease select a ZOOM account" << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
			<< "1. ZOOM A   2. ZOOM B \nSelection: ";
		cin >> selection;

		error();

		if (selection == 1) {		// ZOOM A is selected
			if (temp_slots == 1) {
				temp_acc = "Zoom A";
				temp_timeslots = "Slot 11am-1pm";
				checking2();
			}
			else {
				temp_acc = "Zoom A";
				temp_timeslots = "Slot 2pm-4pm";
				checking2();
			}
		}
		else {						// ZOOM B is selected
			if (temp_slots == 1) {
				temp_acc = "Zoom B";
				temp_timeslots = "Slot 11am-1pm";
				checking2();
			}
			else {
				temp_acc = "Zoom B";
				temp_timeslots = "Slot 2pm-4pm";
				checking2();
			}
		}
	}
}

void search() {
	error_return = 2;
	string print_timeslots, print_acc;
	int decision, i = 0;
	bool exist_date, exist_course, exist_course_name, printing;

	infile.open("booking.txt");
	while (getline(infile, temp_acc)) {
		exist_date = false; exist_course = false; exist_course_name = false;
		getline(infile, temp_timeslots);
		infile >> temp_course;
		infile.ignore(1);
		getline(infile, temp_name);
		infile >> temp_num_students >> temp_time;
		infile.ignore(100, '\n');

		for (i = 0; i < 280; i++) {
			if (searchs[i].date_list == temp_time) {
				exist_date = true;
			}
			if (searchs[i].course_list == temp_course) {
				exist_course = true;
			}
			if (searchs[i].course_name_list == temp_name) {
				exist_course_name = true;
			}
		}
		if (!exist_date) {
			searchs[date_count].date_list = temp_time;
			date_count++;
		}
		if (!exist_course) {
			searchs[course_count].course_list = temp_course;
			course_count++;
		}
		if (!exist_course_name) {
			searchs[course_name_count].course_name_list = temp_name;
			course_name_count++;
		}

	}
	infile.close();
	cout << "=================================================================================================================================\n"
		<< "                                                      * The Booking System *" << endl
		<< "=================================================================================================================================\n"
		<< "1. Show all. \n"
		<< "2. Search by date. \n"
		<< "3. Search by course code. \n"
		<< "4. Search by course name. \n"
		<< "5. Search by time slots. \n"
		<< "6. Search by ZOOM account. \n"
		<< "7. Return. \n\n"
		<< "Selection: ";
	cin >> selection;

	error_num = 7;
	error();

	switch (selection) {
	case 1:
		decision = 1;
		break;
	case 2: {
		decision = 2;
		cout << "\nThese are the date that have bookings recorded." << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		for (i = 0; i < date_count; i++) {
			cout << i + 1 << ". " << searchs[i].date_list << endl;
		}
		cout << "\nWhich one do you want to check?\nSelection: ";
		cin >> selection;
		break;
	}
	case 3: {
		decision = 3;
		cout << "\nThese are the course code that have recorded." << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		for (i = 0; i < course_count; i++) {
			cout << i + 1 << ". " << searchs[i].course_list << endl;
		}
		cout << "\nWhich one do you want to check?\nSelection: ";
		cin >> selection;
		break;
	}
	case 4: {
		decision = 4;
		cout << "\nThese are the course name that have recorded." << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		for (i = 0; i < course_name_count; i++) {
			cout << i + 1 << ". " << searchs[i].course_name_list << endl;
		}
		cout << "\nWhich one do you want to check?\nSelection: ";
		cin >> selection;
		break;
	}
	case 5: {
		decision = 5;
		cout << "\nThese are the time slots that have recorded." << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
			<< "1. 11 a.m. - 1 p.m.\n2. 2 p.m. - 4 p.m.\n";
		cout << "\nWhich one do you want to check?\nSelection: ";
		cin >> selection;
		if (selection == 1) {
			print_timeslots = "Slot 11am-1pm";
		}
		else {
			print_timeslots = "Slot 2pm-4pm";
		}
		i = 2;
		break;
	}
	case 6: {
		decision = 6;
		cout << "\nThese are the ZOOM accounts that have recorded." << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
			<< "1. ZOOM A\n2. ZOOM B\n";
		cout << "\nWhich one do you want to check?\nSelection: ";
		cin >> selection;
		if (selection == 1) {
			print_acc = "Zoom A";
		}
		else {
			print_acc = "Zoom B";
		}
		i = 2;
		break;
	}
	case 7: {
		system("cls");
		main();
	}
	}
	error_num = i;
	error();

	selection -= 1;
	system("cls");

	cout << "=================================================================================================================================\n"
		<< "                                                      * The Booking System *" << endl
		<< "=================================================================================================================================\n"
		<< "---------+---------+-------------+----------------------------------------------------------------+--------------+---------------\n"
		<< " Date    | Account | Course Code | Course Name                                                    | student Num. | Time Slots" << endl
		<< "---------+---------+-------------+----------------------------------------------------------------+--------------+----------------\n";

	infile.open("booking.txt");
	while (getline(infile, temp_acc)) {
		printing = false;
		getline(infile, temp_timeslots);
		infile >> temp_course;
		infile.ignore(1);
		getline(infile, temp_name);
		infile >> temp_num_students >> temp_time;
		infile.ignore(100, '\n');

		switch (decision) {
		case 1:
			printing = true;
			break;
		case 2:
			if (searchs[selection].date_list == temp_time) {
				printing = true;
			}
			break;
		case 3:
			if (searchs[selection].course_list == temp_course) {
				printing = true;
			}
			break;
		case 4:
			if (searchs[selection].course_name_list == temp_name) {
				printing = true;
			}
			break;
		case 5:
			if (print_timeslots == temp_timeslots) {
				printing = true;
			}
			break;
		case 6:
			if (print_acc == temp_acc) {
				printing = true;
			}
			break;
		}
		if (printing) {
			cout << setw(9) << left << temp_time << "| " << setw(8) << left << temp_acc << "| " << setw(12) << left << temp_course << "| "
				<< setw(63) << left << temp_name << "| " << setw(13) << left << temp_num_students << "| " << temp_timeslots << endl
				<< "---------+---------+-------------+----------------------------------------------------------------+--------------+---------------\n";
		}
	}
	infile.close();
	system("pause");
	system("cls");
	main();
}

void update() {
	error_return = 3;

	cout << "====================================================================================================================================\n"
		<< "                                                       * The Booking System *" << endl
		<< "====================================================================================================================================\n"
		<< "Which day of booking you want to update?(Format: DDMM, example: 1506)." << endl
		<< "Date: ";
	cin >> temp;
	stringstream s(temp);
	s >> selection;
	error_num = 9999;
	error();

	temp_time = temp + "2020";
	temp.insert(2, " ");
	checking();

	cout << "------------+---------+-------------+----------------------------------------------------------------+--------------+---------------\n"
		<< "   Date     | Account | Course Code | Course Name                                                    | student Num. | Time Slots" << endl
		<< "------------+---------+-------------+----------------------------------------------------------------+--------------+----------------\n";
	infile.open("booking.txt");
	while (getline(infile, account)) {
		updateAccount[line] = account;
		getline(infile, account);
		updateTimeslot[line] = account;
		infile >> account;
		updateCourse[line] = account;
		infile.ignore(1);
		getline(infile, account);
		updateName[line] = account;
		infile >> numberUpdate;
		updateNum[line] = numberUpdate;
		infile >> account;
		updateTime[line] = account;
		infile.ignore(100, '\n');
		if (temp_time == updateTime[line]) {
			cout << line + 1 << ". " << setw(9) << left << updateTime[line] << "| " << setw(8) << left << updateAccount[line] << "| " << setw(12) << left
				<< updateCourse[line] << "| " << setw(63) << left << updateName[line] << "| " << setw(13) << left << updateNum[line] << "| " << updateTimeslot[line] << endl
				<< "------------+---------+-------------+----------------------------------------------------------------+--------------+---------------\n";
			line++;
		}
	}
	infile.close();

	cout << "which one do you want to update?\nSelection: ";
	cin >> selection;
	update_num = selection - 1;
	error_num = line;
	error();

	line = 0;
	outfile.open("temp.txt", ios::app);
	infile.open("booking.txt");
	while (getline(infile, temp_acc)) {
		getline(infile, temp_timeslots);
		infile >> temp_course;
		infile.ignore(1);
		getline(infile, temp_name);
		infile >> temp_num_students >> temp_time;
		infile.ignore(100, '\n');
		if (updateAccount[update_num] != temp_acc || updateTimeslot[update_num] != temp_timeslots || updateTime[update_num] != temp_time) {
			outfile << temp_acc << endl << temp_timeslots << endl << temp_course << " " << temp_name << endl << temp_num_students << endl << temp_time << endl;
		}
	}
	infile.close();
	outfile.close();
	remove("booking.txt");
	result = rename("temp.txt", "booking.txt");
	remove("temp.txt");

	system("cls");
	update2();
}

void update2() {
	bool cancel = false;
	replace = true;
	error_return = 4;
	cout << "=================================================================================================================================\n"
		<< "                                                      * The Booking System *" << endl
		<< "=================================================================================================================================\n"
		<< "You want to update\n"
		<< "1. Time Slot                           2. Course Name \n"
		<< "3. Zoom Account                        4. Number of Students \n"
		<< "5. Cancel update \n"
		<< "Selection: ";
	cin >> selection;

	error_num = 5;
	error();
	

	switch (selection) {
		case 1: {
			system("cls");
			cout << "=================================================================================================================================\n"
				<< "                                                      * The Booking System *" << endl
				<< "=================================================================================================================================\n"
				<< "1. 11 am - 1 pm						2. 2 pm - 4pm \n"
				<< "Selection: ";
			cin >> selection;

			error_num = 2;
			error();

			temp_acc = updateAccount[update_num];
			temp_course = updateCourse[update_num];
			temp_name = updateName[update_num];
			temp_num_students = updateNum[update_num];
			temp_time = updateTime[update_num];

			if (selection == 1) {
				temp_timeslots = "Slot 11am-1pm";
			}
			else {
				temp_timeslots = "Slot 2pm-4pm";
			}
			checking2();
			break;
		}
		case 2: {
			system("cls");
			cout << "=================================================================================================================================\n"
				<< "                                                      * The Booking System *" << endl
				<< "=================================================================================================================================\n"
				<< "\nPlease fill in the new details " << endl
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
				<< "Course code         : ";
			cin >> temp_course;
			cin.ignore(99, '\n');
			cout << "Course name         : ";
			getline(cin, temp_name);

			temp_acc = updateAccount[update_num];
			temp_timeslots = updateTimeslot[update_num];
			temp_num_students = updateNum[update_num];
			temp_time = updateTime[update_num];
			break;
		}
		case 3: {
			system("cls");
			cout << "=================================================================================================================================\n"
				<< "                                                      * The Booking System *" << endl
				<< "=================================================================================================================================\n"
				<< "Please select the Zoom account that you want to update to\n"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
				<< "1.Zoom A                          2.Zoom B\n"
				<< "Selection :";
			cin >> selection;

			error_num = 2;
			error();

			while (selection == 2 && updateNum[update_num] > 250) {
				cout << "Zoom B is limited to 250 students per session" << endl
					<< "Please select the Zoom account that you want to update to" << endl
					<< "Selection :";
				cin >> selection;

				error();
			}

			if (selection == 1) {
				temp_acc = "Zoom A";
			}
			else if (selection == 2) {
				temp_acc = "Zoom B";
			}
			temp_timeslots = updateTimeslot[update_num];
			temp_course = updateCourse[update_num];
			temp_name = updateName[update_num];
			temp_num_students = updateNum[update_num];
			temp_time = updateTime[update_num];

			checking2();
			break;
		}
		case 4: {
			system("cls");
			cout << "=================================================================================================================================\n"
				<< "                                                      * The Booking System *" << endl
				<< "=================================================================================================================================\n"
				<< "Please key in the number of students that you want to update to: ";
			cin >> selection;
			
			error_num = 500;
			error();

			while (updateAccount[update_num] == "Zoom B" && selection > 250) {
				cout << "\nZoom B is limited to 250 students per session" << endl;
				cout << "Please key in the number of students that you want to update to: ";
				cin >> selection;

				error();
			}
			temp_num_students = selection;
			temp_acc = updateAccount[update_num];
			temp_timeslots = updateTimeslot[update_num];
			temp_course = updateCourse[update_num];
			temp_name = updateName[update_num];
			temp_time = updateTime[update_num];
			break;
		}
		case 5: {
			temp_acc = updateAccount[update_num];
			temp_timeslots = updateTimeslot[update_num];
			temp_course = updateCourse[update_num];
			temp_name = updateName[update_num];
			temp_num_students = updateNum[update_num];
			temp_time = updateTime[update_num];
			cancel = true;
		}
	}
	outfile.open("booking.txt", ios::app);
	outfile << temp_acc << endl << temp_timeslots << endl << temp_course << " " << temp_name << endl << temp_num_students << endl << temp_time << endl;
	if (cancel) {
		cout << "\nthe update is cancelled." << endl;
		cancel = false;
	}
	else {
		cout << "\nThe booking is successfully updated." << endl;
	}
	outfile.close();
	system("pause");
	system("cls");
	main();
}

void cancel() {
	error_return = 5;
	string deleteAccount[4], deleteTimeslot[4], deleteCourse[4], deleteName[4], deleteNum[4], deleteTime[4];
	int delete_num;
	cout << "====================================================================================================================================\n"
		<< "                                                       * The Booking System *" << endl
		<< "====================================================================================================================================\n"
		<< "Which day of booking you want to delete?(Format: DDMM, example: 1506)." << endl
		<< "Date: ";
	cin >> temp;
	stringstream s(temp);
	s >> selection;
	error_num = 9999;
	error();

	temp_time = temp + "2020";
	temp.insert(2, " ");
	checking();

	cout << "------------+---------+-------------+----------------------------------------------------------------+--------------+---------------\n"
		<< "   Date     | Account | Course Code | Course Name                                                    | student Num. | Time Slots" << endl
		<< "------------+---------+-------------+----------------------------------------------------------------+--------------+----------------\n";
	infile.open("booking.txt");
	while (getline(infile, account)) {
		deleteAccount[line] = account;
		getline(infile, account);
		deleteTimeslot[line] = account;
		infile >> account;
		deleteCourse[line] = account;
		infile.ignore(1);
		getline(infile, account);
		deleteName[line] = account;
		infile >> account;
		deleteNum[line] = account;
		infile >> account;
		deleteTime[line] = account;
		infile.ignore(100, '\n');
		if (temp_time == deleteTime[line]) {
			cout << line + 1 << ". " << setw(9) << left << deleteTime[line] << "| " << setw(8) << left << deleteAccount[line] << "| " << setw(12) << left
				<< deleteCourse[line] << "| " << setw(63) << left << deleteName[line] << "| " << setw(13) << left << deleteNum[line] << "| " << deleteTimeslot[line] << endl
				<< "------------+---------+-------------+----------------------------------------------------------------+--------------+---------------\n";
			line++;
		}
	}
	infile.close();

	cout << "Which one do you want to cancel?\nSelection: ";
	cin >> selection;
	delete_num = selection - 1;
	error_num = line;
	error();

	line = 0;
	cout << "\nAre you sure?\n1. Yes   2. No\nSelection: ";
	cin >> selection;
	error_num = 2;
	error();

	outfile.open("temp.txt", ios::app);
	infile.open("booking.txt");
	while (getline(infile, temp_acc)) {
		getline(infile, temp_timeslots);
		infile >> temp_course;
		infile.ignore(1);
		getline(infile, temp_name);
		infile >> temp_num_students >> temp_time;
		infile.ignore(100, '\n');
		if (deleteAccount[delete_num] != temp_acc || deleteTimeslot[delete_num] != temp_timeslots || deleteTime[delete_num] != temp_time) {
			outfile << temp_acc << endl << temp_timeslots << endl << temp_course << " " << temp_name << endl << temp_num_students << endl << temp_time << endl;
		}
	}

	infile.close();
	outfile.close();
	remove("booking.txt");
	result = rename("temp.txt", "booking.txt");
	remove("temp.txt");
	cout << "\nThe booking was deleted" << endl;
	system("pause");
	system("cls");
	main();
}

void checking() {
	int i = 1, j , day = 0, month = 0;
	bool correct = false;
	string check = "";

	stringstream check_value;
	check_value << temp;
	while (check_value >> check) {			// convert string into int
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
	if (!correct) {
		cout << "\nPlease choose the date between Monday and Friday." << endl;
		system("pause");
		system("cls");
		if (error_return == 5) {
			cancel();
		}
		else if (error_return == 3) {
			update();
		}
		else {
			menu();
		}
	}
}

void checking2() {
	bool conflict = false;
	
	infile.open("booking.txt");
	while (getline(infile, compare_acc)) {
		getline(infile, compare_timeslots);
		infile >> compare_course;
		infile.ignore(1);
		getline(infile, compare_name);
		infile >> compare_num_students >> compare_time;
		infile.ignore(100, '\n');
		if (temp_time == compare_time && temp_acc == compare_acc && temp_timeslots == compare_timeslots) {
			conflict = true;
			break;
		}
	}
	infile.close();

	if (conflict) {
		system("cls");
		cout << "========================================================================================================================\n"
			<< "                                                  * The Booking System *" << endl
			<< "========================================================================================================================\n"
			<< "The booking is taken." << endl
			<< "---------+-------------+----------------------------------------------------------------+--------------+----------------\n"
			<< " Account | Course Code |  Course Name                                                   | Student Num. | Time Slots" << endl
			<< "---------+-------------+----------------------------------------------------------------+--------------+----------------\n"
			<< " " << setw(8) << left << compare_acc << "| " << setw(12) << left << compare_course << "| "
			<< setw(63) << left << compare_name << "| " << setw(13) << left << compare_num_students << "| " << compare_timeslots << endl
			<< "---------+-------------+----------------------------------------------------------------+--------------+---------------\n"
			<< "\nDo you want to replace this booking?\n1. Yes   2. No \nSelection: ";
		cin >> selection;

		error();

		if (selection == 1) {				// The data is overwrited
			booking();
		}
		else {								// The booking is cancelled
			cout << "\nReturning to the main page." << endl;
			system("pause");
			system("cls");
			main();
		}
	}
	else {
		if (replace) {
			cout << "\nThis time slot is empty. Update it into this time slots? \n1. Yes    2. No \nSelection: ";
		}
		else {
			cout << "\nThis time slot is empty. Do you want to book it? \n1. Yes   2. No \nSelection: ";
		}
		cin >> selection;

		error();

		if (selection == 1) {				// The data is overwrited
			booking();
		}
		else {								// The booking is cancelled
			cout << "\nReturning to the main page." << endl;
			system("pause");
			system("cls");
			main();
		}
	}
}

void booking() {
	if (replace) {
		outfile.open("temp.txt", ios::app);
		infile.open("booking.txt");
		while (getline(infile, compare_acc)) {
			getline(infile, compare_timeslots);
			infile >> compare_course;
			infile.ignore(1);
			getline(infile, compare_name);
			infile >> compare_num_students >> compare_time;
			infile.ignore(100, '\n');
			if (temp_acc != compare_acc || temp_timeslots != compare_timeslots || temp_time != compare_time) {
				outfile << compare_acc << endl << compare_timeslots << endl << compare_course << " " << compare_name << endl << compare_num_students << endl << compare_time << endl;
			}
		}

		infile.close();
		outfile.close();
		remove("booking.txt");
		result = rename("temp.txt", "booking.txt");
		remove("temp.txt");
	}

	outfile.open("booking.txt", ios::app);
	outfile << temp_acc << endl << temp_timeslots << endl << temp_course << " " << temp_name << endl << temp_num_students << endl << temp_time << endl;
	if (replace) {
		cout << "\nThis booking has been updated." << endl;
		replace = false;
	}
	else {
		cout << "\nThis time slot is successfully booked." << endl;
	}
	outfile.close();
	system("pause");
	system("cls");
	main();
}

void error() {
	bool detect = false;
	if (error_num == 9999) {
		if (temp.length() != 4) {
			cout << "\nPlease type according to the date format." << endl;
			detect = true;
		}
	}
	else if (selection > error_num) {
		cout << "\nPlease type between 1 and " << error_num << "." << endl;
		detect = true;
	}
	else if (cin.fail() || (cin.peek() != '\n')) {
		cout << "\nOnly numbers are allowed." << endl;
		detect = true;
	}
	
	if (detect) {
		system("pause");
		system("cls");
		cin.clear();
		cin.ignore(50, '\n');
		switch (error_return) {
			case 0:
				main();
			case 1:
				menu();
			case 2:
				search();
			case 3:
				update();
			case 4:
				update2();
			case 5:
				cancel();
		}
	}
	return;
}

void loading() {
	for (int i = 0; i <= 4000; i++) {
		cout << "Loading . . . " << i / 40 << "%" << '\r';
	}
	cout << endl;
}

void current_date() {
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
}