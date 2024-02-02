#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include"Collateral.cpp"
#include"CustomerInfo.cpp"
using namespace std;

void line_border(int length) {
	cout << ' ';
	for (int i = 1; i < length; i++) {
		cout << '-';
	}
	cout << endl;
}

void user_header() {
	line_border(60);
	cout << '|';
	cout << "User_ID" << '|';
	cout << "User_Name" << '|';
	cout << "Gender" << '|';
	cout << "Position" << '|';
	cout << "Booking_Date" << '|';
	cout << "User_Profile" << '|';
	cout << endl;
	line_border(60);
}

void view_active_user(userinfo user[], int count_user, string mark) {
	user_header();
	for (int i = 0; i < count_user; i++) {
		if (user[i].status_flag == 'y') {
			if (mark == "") {
				cout << '|';
				cout << user[i].user_id << setw(7 - user[i].user_id.length() + 1) << '|';
				cout << user[i].user_name << setw(9 - user[i].user_name.length() + 1) << '|';
				cout << user[i].gender << setw(6) << '|';
				cout << user[i].position << setw(8 - user[i].position.length() + 1) << '|';
				cout << user[i].booking_date << setw(12 - user[i].booking_date.length() + 1) << '|';
				cout << user[i].user_profile << setw(12 - user[i].user_profile.length() + 1) << '|';
				cout << endl;
			}
			else if (mark == user[i].user_id) {
				cout << '|';
				cout << user[i].user_id << setw(7 - user[i].user_id.length() + 1) << '|';
				cout << user[i].user_name << setw(9 - user[i].user_name.length() + 1) << '|';
				cout << user[i].gender << setw(6) << '|';
				cout << user[i].position << setw(8 - user[i].position.length() + 1) << '|';
				cout << user[i].booking_date << setw(12 - user[i].booking_date.length() + 1) << '|';
				cout << user[i].user_profile << setw(12 - user[i].user_profile.length() + 1) << '|';
				cout << endl;
			}

		}
	}
	cout << endl;
}


bool search_key_userid(userinfo user[], int count_user, string key) {
	for (int i = 0; i < count_user; i++) {
		if (key == user[i].user_id || stoi(key) <= 0 || key.length() != 4) {
			return true;
			break;
		}
	}
	return false;
}

string get_userid(userinfo user[], int count_user) {
	string id;
	while (true) {
		cout << "     User ID: ";
		cin >> id;
		if (id.length() != 4) {
			cout << "error: user id is unable to be over or lower 4 digits." << endl;
		}
		else if (stoi(id) <= 0) {
			cout << "error: unable to use minus sign" << endl;
		}
		else if (search_key_userid(user, count_user, id)) {
			cout << "error: duplicated id in list." << endl;
		}
		else {
			return id;
		}
	}
}

bool validate_username(string name) {
	if (name.length() <= 3) {
		return false;
	}
	for (int i = 0; i < name.length(); i++) {
		if (!(name[i] >= 65 && name[i] <= 122)) {
			return false;
		}
	}
	return true;
}

string get_username() {
	string name;
	while (true) {
		cout << "   User Name: ";
		cin >> name;
		if (!validate_username(name)) {
			cout << "error: invalid name " << endl;
		}
		else {
			return name;
		}
	}
}

bool validate_gender(char gender) {
	if (gender == 'm' || gender == 'f') {
		return true;
	}
	return false;
}

char get_gender() {
	char gender;
	while (true) {
		cout << "      Gender: ";
		cin >> gender;
		if (!validate_gender(gender)) {
			cout << "error: invalid gender " << endl;
		}
		else {
			return gender;
		}
	}
}

bool validate_bookingdate(string date) {
	if (date.length() == 6) {
		return true;
	}
	return false;
}

string get_bookingdate() {
	string date;
	while (true) {
		cout << "Booking Date: ";
		cin >> date;
		if (!validate_bookingdate(date)) {
			cout << "error: invalid date " << endl;
		}
		else {
			return date;
		}
	}
}

bool validate_profile(string gender) {
	if (gender == "ipt" || gender == "adm") {
		return true;
	}
	return false;
}

string get_profile() {
	string profile;
	while (true) {
		cout << "User Profile: ";
		cin >> profile;
		if (!validate_profile(profile)) {
			cout << "error: invalid profile " << endl;
		}
		else {
			return profile;
		}
	}
}

void write_file_user(userinfo user[], int count_user) {
	ofstream ofile;
	ofile.open("dataUser.dat", ios::out | ios::binary);
	if (ofile.is_open()) {
		for (int i = 0; i < count_user; i++) {
			ofile.write(reinterpret_cast<char*>(&user[i]), sizeof(user[i]));
		}
		ofile.close();
		cout << "written successfully." << endl;
	}
	else {
		cout << "unable to open file." << endl;
	}
}

void read_file_user(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	userinfo ui;
	ifstream ifile;
	ifile.open("dataUser.dat", ios::binary);
	if (ifile.fail()) {
		cout << "Error: open file" << endl;
	}
	else {
		while (ifile.read(reinterpret_cast<char*>(&ui), sizeof(ui))) {
			user[count_user] = ui;
			count_user++;
		}
		ifile.close();
	}
	welcome_user_menu();
	main_menu_user(user, count_user, cust, count);
}

bool isComplexPasword(const string& password) {
	bool isLowerCase = false;
	bool isUpperCase = false;
	bool isDigit = false;
	bool isSpecialChar = false;

	if (password.length() < 8) {
		return false;
	}
	for (char c : password) {
		if (isupper(c)) {
			isUpperCase = true;
		}
		else if (islower(c)) {
			isLowerCase = true;
		}
		else if (isdigit(c)) {
			isDigit = true;
		}
		else if (ispunct(c)) {
			isSpecialChar = true;
		}
	}
	return isUpperCase && isLowerCase && isDigit && isSpecialChar;
}

void GetPassword(userinfo user[], int count_user, string& NewPassword) {
	string ConfirmNewPassword;
	do {
		cout << "----------------------------------------------------------------" << endl;
		cout << "Password should be changed (8 digits character with complexity)." << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << "        New Password: ";
		cin >> NewPassword;
		if (!isComplexPasword(NewPassword)) {
			cout << "password shoud be complexible criteria. try again." << endl;
		}
	} while (!isComplexPasword(NewPassword));

	do {
		cout << "Comfirm New Password: ";
		cin >> ConfirmNewPassword;
		if (NewPassword != ConfirmNewPassword) {
			cout << "password confirmation is not correct. try again.";
		}
	} while (NewPassword != ConfirmNewPassword);
	cout << "password has been changed successfully: " << NewPassword << endl;
}

int search_key_user(userinfo user[], int count_user, string key) {
	for (int i = 0; i < count_user; i++) {
		if (user[i].user_id == key) {
			return i;
		}
	}
	return -1;
}

void search_user(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	string user_id;
	char answer_key;
	cout << "     User ID: "; cin >> user_id;
	string key = user_id;
	int found = search_key_user(user, count_user, user_id);
	if (found != -1) {
		view_active_user(user, count_user, user[found].user_id);
	}
	else {
		cout << "Not found" << endl;
		search_user(user, count_user, cust, count);
	}
	cout << "Do you want to search more (y/n)?: "; cin >> answer_key;
	if (answer_key == 'y') {
		search_user(user, count_user, cust, count);
	}
	else {
		adm_menu(user, count_user, cust, count);
	}
}

void update(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	string user_id;
	string key_update;
	char answer_key;
	int field_key;
	cout << "   User ID: "; cin >> user_id;
	int found = search_key_user(user, count_user, user_id);
	if (found != -1) {
		cout << "--------------------------------" << endl;
		cout << "1. Position" << endl;
		cout << "2. User Profile" << endl;
		cout << "3. Password" << endl;
		cout << "--------------------------------" << endl;
		cout << "Pls choose each fields to update: "; cin >> field_key;
		if (field_key == 1) {
			cout << "    Position: "; cin >> key_update;
			user[found].position = key_update;
		}
		else if (field_key == 2) {
			cout << "User Profile: "; cin >> key_update;
			user[found].user_profile = key_update;
		}
		else if (field_key == 3) {
			string oldPassword;
			do {
				cout << "        Old Password: ";
				cin >> oldPassword;
				if (user[found].password != oldPassword) {
					cout << "password is not correct. try again." << endl;
				}
			} while (user[found].password != oldPassword);
			GetPassword(user, count_user, key_update);
			user[found].password = key_update;
			cout << "Do you want to update more (y/n)?: "; cin >> answer_key;
			if (answer_key == 'y') {
				update(user, count_user, cust, count);
			}
			else {
				adm_menu(user, count_user, cust, count);
			}
		}
		else {
			cout << "Invalid field.";
		}
		view_active_user(user, count_user, "");
		cout << "Do you want to update more (y/n)?: "; cin >> answer_key;
		if (answer_key == 'y') {
			update(user, count_user, cust, count);
		}
		else {
			adm_menu(user, count_user, cust, count);
		}
	}
}

void sort_user(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	string sort_key;
	cout << "which sort key do you want (asc/desc)?: ";
	cin >> sort_key;
	for (int i = 0; i < count_user; i++) {
		for (int j = 0; j < count_user - i - 1; j++) {
			if (sort_key == "asc") {
				if (user[j].number > user[j + 1].number) {
					userinfo temp;
					temp = user[j];
					user[j] = user[j + 1];
					user[j + 1] = temp;
				}
			}
			else if (sort_key == "desc") {
				if (user[j].number < user[j + 1].number) {
					userinfo temp;
					temp = user[j];
					user[j] = user[j + 1];
					user[j + 1] = temp;
				}
			}
			else {
				cout << "invalid key sort. try again." << endl;
				sort_user(user, count_user, cust, count);
			}

		}
	}
	view_active_user(user, count_user, "");
	adm_menu(user, count_user, cust, count);
}

void delete_(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	string user_id, delete_date;
	char answer_key;
	char confirm_key;
	cout << "    User ID: "; cin >> user_id;
	cout << "Delete Date: "; cin >> delete_date;
	string key = user_id;
	int found = search_key_user(user, count_user, user_id);
	if (found != -1) {
		cout << "Are you sure to delete (y/n)?: ";
		cin >> confirm_key;
		if (confirm_key == 'y') {
			user[found].delete_date = delete_date;
			user[found].status_flag = 'n';
			cout << "delete is successfully." << endl;
		}
		else if (confirm_key == 'n') {
			cout << "delete is fail." << endl;
		}
		else {
			cout << "invalid confirmation key.";
		}
	}
	else {
		cout << "Not found" << endl;
		delete_(user, count_user, cust, count);
	}
	view_active_user(user, count_user, "");
	cout << "Do you want to delete more (y/n)?: "; cin >> answer_key;
	if (answer_key == 'y') {
		delete_(user, count_user, cust, count);
	}
	else {
		adm_menu(user, count_user, cust, count);
	}
}

void adm_menu(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	int menu = 0;
	cout << "-------------------------" << endl;
	cout << "1. Update" << endl;
	cout << "2. Delete" << endl;
	cout << "3. View" << endl;
	cout << "4. Search" << endl;
	cout << "5. Sort" << endl;
	cout << "6. Main Menu" << endl;
	cout << "-------------------------" << endl;
	cout << "Pls choose sub menu (1-6): ";
	cin >> menu;
	switch (menu) {
	case 1:
		update(user, count_user, cust, count);
		break;
	case 2:
		delete_(user, count_user, cust, count);
		break;
	case 3:
		view_active_user(user, count_user, "");
		adm_menu(user, count_user, cust, count);
		break;
	case 4:
		search_user(user, count_user, cust, count);
		break;
	case 5:
		sort_user(user, count_user, cust, count);
		break;
	case 6:
		main_menu_user(user, count_user, cust, count);
		break;
	default:
		cout << "Invalid menu";
		break;
	}
}

void profile_menu(userinfo user[], int count_user, string UserProfile, CustomerInfo cust[], int count) {
	Collateral c;
	if (UserProfile == "adm") {
		int menu = 0;
		cout << "---------------------" << endl;
		cout << "1. User Menu" << endl;
		cout << "2. Program Menu" << endl;
		cout << "3. Main Menu" << endl;
		cout << "---------------------" << endl;
		cout << "Pls choose menu (1-3): ";
		cin >> menu;
		switch (menu) {
		case 1:
			adm_menu(user, count_user, cust, count);
			break;
		case 2:
			c.welcome_program_menu();
			c.read_file(cust, count, user, count_user);
			break;
		case 3:
			main_menu_user(user, count_user, cust, count);
			break;
		default:
			cout << "Invalid menu";
			break;
		}
	}
	else if (UserProfile == "ipt") {
		c.welcome_program_menu();
		c.read_file(cust, count, user, count_user);
	}
}

void log_in(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	string key;
	string password;
	int index;
	cout << " User ID: ";
	cin >> key;
	if (search_key_user(user, count_user, key) != -1) {
		cout << "Password: ";
		cin >> password;
		index = search_key_user(user, count_user, key);
		if (user[index].log_time == 1 && user[index].password == password) {
			GetPassword(user, count_user, password);
			user[index].log_time = 2;
			user[index].password = password;
			main_menu_user(user, count_user, cust, count);
		}
		else if (user[index].log_time == 1 && user[index].password != password) {
			cout << "Temporary password is not correct. try again." << endl;
			log_in(user, count_user, cust, count);
		}
		else if (user[index].log_time == 2 && user[index].password != password) {
			cout << "Password is not correct. try again." << endl;
			log_in(user, count_user, cust, count);
		}
		else if (user[index].log_time == 2 && user[index].password == password) {
			profile_menu(user, count_user, user[index].user_profile, cust, count);
		}

	}
	else {
		cout << "User doesn't have in list. try again." << endl;
		log_in(user, count_user, cust, count);
	}

}

void register_(userinfo user[], int& count_user, CustomerInfo cust[], int count) {
	char answer_key;
	//--------------menu-------------------
	cout << "-----------------------" << endl;
	cout << "    User ID(4 digits):" << endl;
	cout << "  User Name(no space):" << endl;
	cout << "          Gender(m|f):" << endl;
	cout << "             Position:" << endl;
	cout << " Booking Date(ddmmyy):" << endl;
	cout << "User Profile(ipt|adm):" << endl;
	cout << "-----------------------------" << endl;
	cout << "Pls enter data by each fields" << endl;
	cout << "-----------------------------" << endl;
	//--------------input------------------
	user[count_user].user_id = get_userid(user, count_user);
	user[count_user].user_name = get_username();
	user[count_user].gender = get_gender();
	cout << "    Position: "; cin >> user[count_user].position;
	user[count_user].booking_date = get_bookingdate();
	user[count_user].user_profile = get_profile();
	user[count_user].number = count_user;
	user[count_user].status_flag = 'y';
	srand(time(0));
	int randomNumber = rand() + 10000;
	user[count_user].password = to_string(randomNumber);
	user[count_user].log_time = 1;
	cout << "Successfully." << endl;
	cout << "Temporary password: " << user[count_user].password << endl;
	count_user++;
	view_active_user(user, count_user, "");
	cout << "Do you want to register more (y/n)?: "; cin >> answer_key;
	if (answer_key == 'y') {
		register_(user, count_user, cust, count);
	}
	else {
		main_menu_user(user, count_user, cust, count);
	}
}

void welcome_user_menu() {
	string text = "--------Wellcome To User Menu--------";
	int screenWidth = 200;
	int padding = (screenWidth - text.length()) / 2;
	cout << setw(padding + text.length()) << text << endl;
}

void main_menu_user(userinfo user[], int count_user, CustomerInfo cust[], int count) {
	int menu = 0;
	cout << "---------------------" << endl;
	cout << "1. Register" << endl;
	cout << "2. Log In" << endl;
	cout << "3. Save" << endl;
	cout << "4. Exit" << endl;
	cout << "---------------------" << endl;
	cout << "Pls choose menu (1-4): ";
	cin >> menu;
	switch (menu) {
	case 1:
		register_(user, count_user, cust, count);
		break;
	case 2:
		log_in(user, count_user, cust, count);
		break;
	case 3:
		write_file_user(user, count_user);
		main_menu_user(user, count_user, cust, count);
		break;
	case 4:
		write_file_user(user, count_user);
		exit(0);
		break;
	default:
		cout << "Invalid menu";
		break;
	}
}