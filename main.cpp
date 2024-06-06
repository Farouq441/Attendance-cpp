// C++ Program to implement student Attendence Management 
// System 
#include <cstdlib> 
#include <cstring> 
#include <ctime> 
#include <fstream> 
#include <iostream> 
#include <string> 

using namespace std; 

// Function prototypes 
void mainmenu(); 
void adminLogin(); 
void studentlogin(); 
void adminMenu(); 
void creatAdminAccount(); 
void createStudentFile(); 
void initilizeAdminIdPass(); 
void insertionsort(); 
int isfileexist(string); 
void markAttendence(); 
void attendenceStatus(string); 
void attendencelist(); 

// Class to handle admin actions 
class admin { 
	string username, password, rPassword; 

public: 
	void checkPasswordMatch() 
	{ 
		int passwordMatchStatus 
			= password.compare(rPassword); 
		if (passwordMatchStatus != 0) { 
			cout << "\n\t\tPasswords are not matching. "
					"Re-enter the password\n"; 
			getUserNameAndPasswordOfAdmin(); 
		} 
	} 

	// implementing password constrains 
	int passwordformat() 
	{ 
		int digf = 0, numf = 0, splf = 0, i = 0, 
			len = password.size(); 

		if (password.size() < 8) { 
			printf("\n\t\t\tPassword is too short\n"); 
			return 0; 
		} 
		if (password.size() > 20) { 
			printf("\n\t\t\tPassword is too long"); 
			return 0; 
		} 

		for (i = 0; i < len; i++) { 
			if (password[i] >= 'A' && password[i] <= 'Z') { 
				numf = 1; 
			} 
			if (password[i] == '@' || password[i] == '&'
				|| password[i] == '_' || password[i] == '*'
				|| password[i] == '(' || password[i] == ')'
				|| password[i] == '#' || password[i] == '$'
				|| password[i] == '^' || password[i] == '.'
				|| password[i] == ',') { 
				splf = 1; 
			} 
			if (isdigit(password[i]) == 0) 
				digf = 1; 
		} 
		if (numf && splf && digf) { 
			return 1; 
		} 
		else { 
			printf("\nPassword should contain at least one "
				"uppercase letter, one digit, and one "
				"special character ('@', '#', '$', '^', "
				"'&', '*', '(', ')', '.', ',')"); 
			return 0; 
		} 
	} 

	void getUserNameAndPasswordOfAdmin() 
	{ 
		cout << "\n\t\t\tEnter username: "; 
		cin >> username; 
		cout << "\n\t\t\tEnter password: "; 
		cin >> password; 
		while (!passwordformat()) { 
			cout << "\n\t\t\tEnter password: "; 
			cin >> password; 
		} 
		cout << "\n\t\t\tRe-enter password: "; 
		cin >> rPassword; 
		cout << endl; 
		checkPasswordMatch(); 
	} 

	string returnAdminUsername() { return username; } 

	string returnAdminPassword() { return password; } 
}; 

// Class to handle student actions 
class student { 
	// variable to store name and university serial number 
	string usn, name; 

public: 
	void readStudentData() 
	{ 
		cout << "\n\t\t\tEnter the name: "; 
		cin >> name; 
		cout << "\n\t\t\tEnter the username: "; 
		cin >> usn; 
	} 

	string getUsn() { return usn; } 

	string getName() { return name; } 
}; 

// creating a file with admin credentials 
void createAdminAccount() 
{ 
	admin a; 
	a.getUserNameAndPasswordOfAdmin(); 
	string username, password; 
	username = a.returnAdminUsername(); 
	password = a.returnAdminPassword(); 
	fstream f; 
	f.open("AdminAccount.txt", ios::app); 
	f << username << "\t" << password << "\n"; 
	f.close(); 
	cout << "\n\t\t\tAccount created successfully\n"; 
} 

// function to initialize the admin file if it does not 
// exists 
void initilizeAdminIdPass() 
{ 
	fstream f; 
	int fileStatus = isfileexist("AdminAccount.txt"); 
	if (fileStatus) { 
		f.open("AdminAccount.txt", ios::out); 
		f << "admin\tadmin\n"; 
		f.close(); 
	} 
} 

// function to help in admin in logging in 
void adminLogin() 
{ 
	initilizeAdminIdPass(); 
	int success_flag = 0; 
	cout << "\n\n------------------------ ADMIN LOGIN "
			"------------------------\n"; 
	string username, fUsername, fPassword; 
	string password; 
	cout << "\n\t\t\tEnter username : "; 
	cin >> username; 
	cout << "\n\t\t\tEnter password : "; 
	cin >> password; 
	fstream f; 
	f.open("AdminAccount.txt", ios::in); 
	while (f) { 
		f >> fUsername >> fPassword; 
		if (username.compare(fUsername) == 0 
			&& password.compare(fPassword) == 0) { 
			cout << "\n\t\t\tLogin successful!!!\n"; 
			success_flag = 1; 
			adminMenu(); 
			f.close(); 
			break; 
		} 
	} 

	// if login is failed. 
	if (success_flag == 0) { 
		f.close(); 
		cout << "\n\t\tError! Invalid Credentials. Please "
				"Try Again\n"; 
	} 
} 

// function for admin dashboard 
void adminMenu() 
{ 
	int choice; 
	for (;;) { 
		cout << "\n ------------------------ ADMIN MENU "
				"------------------------\n"; 
		cout << "\n\t\t\t1.Mark attendance\n\t\t\t2.Add "
				"students\n\t\t\t3.Create new admin "
				"account\n\t\t\t4.Student attendance "
				"list\n\t\t\t5.Main "
				"menu\n\t\t\t0.Exit\n\n\t\t\tEnter your "
				"choice..."; 
		cin >> choice; 
		switch (choice) { 
		case 0: 
			exit(0); 
		case 1: { 
			markAttendence(); 
			break; 
		} 
		case 2: { 
			createStudentFile(); 
			break; 
		} 
		case 3: { 
			createAdminAccount(); 

			break; 
		} 
		case 4: { 
			attendencelist(); 
			break; 
		} 
		case 5: { 
			mainmenu(); 
			break; 
		} 
		} 
	} 
} 

// creating a file to store student data 
void createStudentFile() 
{ 
	student s; 
	int year, month, day, pa; 
	s.readStudentData(); 
	string usn, name; 
	usn = s.getUsn(); 
	name = s.getName(); 
	string filename = usn + ".txt"; 
	time_t now = time(0); 
	tm* ltm = localtime(&now); 
	year = ltm->tm_year + 1900; 
	month = ltm->tm_mon + 1; 
	day = ltm->tm_mday; 
	pa = 2; 
	if (!isfileexist(filename)) { 
		cout << "\n\t\t\tStudent already enrolled\n"; 
	} 
	else { 
		fstream seperatef, commonf, usnf; 
		seperatef.open(filename, ios::out); 
		seperatef << usn << "\t" << name << "\t" << pa 
				<< "\t" << day << "\t" << month << "\t"
				<< year << "\n"; 
		commonf.open("studentlist.txt", ios::app); 
		commonf << usn << "\t" << name << "\n"; 
		usnf.open("UsnFile.txt", ios::app); 
		usnf << usn << "\n"; 
		commonf.close(); 
		usnf.close(); 
		seperatef.close(); 
		cout << "\n\t\tStudent successfully added to the "
				"list\n"; 
	} 
	insertionsort(); 
} 

// function to mark attendence with date 
void markAttendence() 
{ 
	string filename, usn, name; 
	int pa, day, month, year; 
	time_t now = time(0); 
	tm* ltm = localtime(&now); 
	year = ltm->tm_year + 1900; 
	month = ltm->tm_mon + 1; 
	day = ltm->tm_mday; 
	cout << "\n\t\t\tEnter 1 for present and 0 for "
			"absent\n\n"; 
	fstream sfile, usnfile; 
	sfile.open("studentlist.txt", ios::in); 

	while (sfile >> usn >> name) { 
		filename = usn + ".txt"; 
		usnfile.open(filename, ios::app); 
		cout << "\t\tUniversity Number: " << usn 
			<< "\tName: " << name << "\t"; 
		cin >> pa; 
		usnfile << usn << "\t" << name << "\t" << pa << "\t"
				<< day << "\t" << month << "\t" << year 
				<< "\n"; 
		usnfile.close(); 
	} 

	cout << "\n\t\t\tAll attendance marked\n"; 
	sfile.close(); 
} 

// utility function to check whether the file with the given 
// name exists 
int isfileexist(string filename) 
{ 
	fstream f; 
	f.open(filename, ios::in); 
	if (f) { 
		f.close(); 
		return 0; 
	} 
	f.close(); 
	return 1; 
} 

// insertion sort implementation 
void insertionSortRecursive(string arr[], int n) 
{ 
	if (n <= 1) 
		return; 

	insertionSortRecursive(arr, n - 1); 
	string last = arr[n - 1]; 
	int j = n - 2; 

	while (j >= 0 && arr[j] > last) { 
		arr[j + 1] = arr[j]; 
		j--; 
	} 
	arr[j + 1] = last; 
} 

// soring usn file according to university serial number 
// number 
void insertionsort() 
{ 
	int i, j, n = 0; 
	string k; 
	string usnarray[150]; 
	fstream usnf; 
	usnf.open("UsnFile.txt"); 
	while (usnf >> usnarray[n++]) 
		; 
	usnf.close(); 
	insertionSortRecursive(usnarray, n); 
	usnf.open("UsnFile.txt"); 
	for (i = 0; i <= n; i++) { 
		usnf << usnarray[i] << "\n"; 
	} 
	usnf.close(); 
} 

// function to print attendence list 
void attendencelist() 
{ 
	string usn, name; 
	int totaldays = 0, p = 0, a = 0, flag = 0, pa, day, 
		month, year; 
	float per = 0.0; 
	fstream sepf, usnf; 
	usnf.open("UsnFile.txt", ios::in); 
	while (usnf >> usn) { 
		flag = 0; 
		p = 0; 
		a = 0; 
		per = 0; 
		totaldays = 0; 
		usn = usn + ".txt"; 
		sepf.open(usn, ios::in); 
		while (sepf >> usn >> name >> pa >> day >> month 
			>> year) { 
			if (flag == 0) { 
				cout << "\n\n\tUniversity Number:" << usn 
					<< "\t"
					<< "Name: " << name << endl; 
				flag = 1; 
				continue; 
			} 
			totaldays++; 
			if (pa == 1) 
				p++; 
			else
				a++; 
		} 
		sepf.close(); 
		per = ((float)p / totaldays) * 100; 
		cout << "\tPresent:" << p << "\tAbsent:" << a 
			<< "\tAttendance percentage:" << per << endl; 
	} 
	usnf.close(); 
} 

// function to check attendence status 
void attendenceStatus(string filename) 
{ 
	fstream f, usnfile; 
	string usn, name, usnfilename; 
	int pa, day, month, year, pcount, acount, 
		totaldays = 0, p = 0, a = 0, flag = 0; 
	float per = 0.0; 

	usnfile.open(filename, ios::in); 
	while (usnfile >> usn >> name >> pa >> day >> month 
		>> year) { 
		if (flag == 0) { 
			cout << "\n\tName:" << name 
				<< "\tUniversity Number:" << usn << endl; 
			flag = 1; 
			continue; 
		} 
		totaldays++; 
		if (pa == 1) { 
			p++; 
			cout << "\t" << day << "-" << month << "-"
				<< year << "\tPresent\n"; 
		} 
		else { 
			a++; 
			cout << "\t" << day << "-" << month << "-"
				<< year << "\tAbsent\n"; 
		} 
	} 
	usnfile.close(); 
	per = ((float)p / totaldays) * 100; 

	cout << "\n\n\tPresent:" << p << "\tAbsent:" << a 
		<< "\tAttendance percentage:" << per << endl 
		<< endl; 
} 

// student login page 
void studentlogin() 
{ 
	; 
	cout << "\n ------------------------ STUDENT MENU "
			"------------------------\n"; 
	string password, username, fUsername, fPassword; 
	int successf = 0; 
	cout << "\n\t\t\tEnter username : "; 
	cin >> username; 
	cout << "\n\t\t\tEnter password : "; 
	cin >> password; 
	string filename = password + ".txt"; 
	ifstream sflogin; 
	sflogin.open("studentlist.txt"); 
	while (sflogin >> fUsername) { 
		if (password.compare(fUsername) == 0 
			&& username.compare(fUsername) == 0) { 
			successf = 1; 
			attendenceStatus(filename); 
			sflogin.close(); 
			break; 
		} 
	} 
	if (successf == 0) { 
		sflogin.close(); 
		cout << "\n\t\t\t Error ! Invalid Credentials.."; 
	} 
	sflogin.close(); 
} 

// main menu 
void mainmenu() 
{ 
	int choice; 
	while (1) { 
		cout << "\n\n ------------------ Welcome to "
				"Attendence Management System "
				"------------------\n"; 
		cout << "\n\t\t\t1.Student login\n\t\t\t2.Admin "
				"login\n\t\t\t0.Exit\n\n\t\t\tEnter your "
				"choice... "; 
		cin >> choice; 
		switch (choice) { 
		case 0: 
			exit(0); 
		case 1: 
			studentlogin(); 
			break; 
		case 2: 
			adminLogin(); 
			break; 

		default: 
			cout << "Invalid Option! Pease Try Again.\n"; 
		} 
	} 
} 

// driver code 
int main() 
{ 
	mainmenu(); 
	return 0; 
}
