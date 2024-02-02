#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include"DataInputValidation.cpp"
#include"CustomerInfo.cpp"
#include"CollateralDAO.cpp"
#include"hfuser_login_struct.h"
#include"hfuser_login.h"
using namespace std;

class Collateral : public CollateralDAO {
private:
	CustomerInfo cust[100];
	DataInputValidation dv;
	int search_key(CustomerInfo* cust, int count, string key) {
		for (int i = 0; i < count; i++) {
			if (cust[i].getCustomerId() + cust[i].getGroupLd() == key) {
				return i;
			}
		}
		return -1;
	}
	int search_Unikey_ID(CustomerInfo* cust, int count, string key) {
		for (int i = 0; i < count; i++) {
			if (cust[i].getCustomerId() == key) {
				return i;
			}
		}
		return -1;
	}
public:
	void header() {
		//line_border(138);
		cout << '|';
		cout << "Customer_ID" << '|';
		cout << "Group_LD" << '|';
		cout << "Customer_Name" << '|';
		cout << "Deposit_Date" << '|';
		cout << "Collateral_Type" << '|';
		cout << "Collateral_Number" << '|';
		cout << "Collateral_Address" << '|';
		cout << "Collateral_Currency" << '|';
		cout << "Collateral_Value" << '|';
		cout << endl;
		//line_border(138);
	}

	void write_file(CustomerInfo* cust, int count) {
		ofstream ofile;
		ofile.open("dataCollateral.dat", ios::out | ios::binary);
		if (ofile.is_open()) {
			for (int i = 0; i < count; i++) {
				ofile.write(reinterpret_cast<char*>(&cust[i]), sizeof(cust[i]));
			}
			ofile.close();
			cout << "written successfully." << endl;
		}
		else {
			cout << "unable to open file." << endl;
		}
	}

	void read_file(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		CustomerInfo ci;
		ifstream ifile;
		ifile.open("dataCollateral.dat", ios::binary);
		if (ifile.fail()) {
			cout << "Error: open file" << endl;
		}
		else {
			while (ifile.read(reinterpret_cast<char*>(&ci), sizeof(ci))) {
				cust[count] = ci;
				count++;
			}
			ifile.close();
		}
		main_menu(cust, count, user, count_user);
	}

	void summ_rpt_ccy(CustomerInfo* cust, int count) {
		int n_coll_usd = 0, n_coll_khr = 0, n_coll_thb = 0;
		double v_coll_usd = 0, v_coll_khr = 0, v_coll_thb = 0;
		for (int i = 0; i < count; i++) {
			if (cust[i].getWithdDate() == "" && cust[i].getRemark() == "") {
				if (cust[i].getCollCCY() == "usd") {
					n_coll_usd++;
					v_coll_usd += cust[i].getConvCollValue();
				}
				else if (cust[i].getCollCCY() == "khr") {
					n_coll_khr++;
					v_coll_khr += conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY());
				}
				else if (cust[i].getCollCCY() == "thb") {
					n_coll_thb++;
					v_coll_thb += conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY());
				}
			}
		}
		cout << "all amount in this report has been converted to usd based on exchange(usd = 4000, thb = 100)" << endl;
		//line_border(55);
		cout << '|' << "Currency_Type" << '|';
		cout << "Number_Of_Collateral" << '|';
		cout << "Value_Of_Collateral" << '|' << endl;
		//line_border(55);
		cout << '|' << "USD" << setw(11) << '|';
		cout << n_coll_usd << setw(20 - to_string(n_coll_usd).length() + 1) << "|";
		cout << fixed << setprecision(2) << v_coll_usd << setw(23 - to_string(v_coll_usd).length() + 1) << "|" << endl;
		cout << '|' << "KHR" << setw(11) << '|';
		cout << n_coll_khr << setw(20 - to_string(n_coll_khr).length() + 1) << "|";
		cout << fixed << setprecision(2) << v_coll_khr << setw(23 - to_string(v_coll_khr).length() + 1) << "|" << endl;
		cout << '|' << "THB" << setw(11) << '|';
		cout << n_coll_thb << setw(20 - to_string(n_coll_thb).length() + 1) << "|";
		cout << fixed << setprecision(2) << v_coll_thb << setw(23 - to_string(v_coll_thb).length() + 1) << "|" << endl;
		//line_border(55);
	}

	double conv_ccy_to_usd(double coll_value, string ccy) {
		double result_convert;
		if (ccy == "khr") {
			result_convert = coll_value / 4000;
		}
		else if (ccy == "thb") {
			result_convert = ((coll_value * 100) / 4000);
		}
		else {
			result_convert = coll_value;
		}
		return result_convert;
	}

	void summ_rpt_vcoll(CustomerInfo* cust, int count) {
		int n_coll_1 = 0, n_coll_2 = 0, n_coll_3 = 0, n_coll_4 = 0;
		double v_coll_1 = 0, v_coll_2 = 0, v_coll_3 = 0, v_coll_4 = 0;
		for (int i = 0; i < count; i++) {
			if (conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY()) > 0) {
				if (conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY()) <= 10000) {
					n_coll_1++;
					v_coll_1 += conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY());
				}
				else if (conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY()) > 10000 && conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY()) <= 50000) {
					n_coll_2++;
					v_coll_2 += conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY());
				}
				else if (conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY()) > 50000 && conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY()) <= 100000) {
					n_coll_3++;
					v_coll_3 += conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY());
				}
				else if (conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY()) > 100000) {
					n_coll_4++;
					v_coll_4 += conv_ccy_to_usd(cust[i].getConvCollValue(), cust[i].getCollCCY());
				}
			}
		}
		cout << "all amount in this report has been converted to usd based on exchange(usd = 4000, thb = 100)" << endl;
		//line_border(64);
		cout << '|' << "Collateral_Value_Class" << '|';
		cout << "Number_Of_Collateral" << '|';
		cout << "Value_Of_Collateral" << '|' << endl;
		//line_border(64);
		cout << '|' << ">=10,000" << setw(15) << '|';
		cout << n_coll_1 << setw(20 - to_string(n_coll_1).length() + 1) << "|";
		cout << fixed << setprecision(2) << v_coll_1 << setw(23 - to_string(v_coll_1).length() + 1) << "|" << endl;
		cout << '|' << ">10,000 to <=50,000" << setw(4) << '|';
		cout << n_coll_2 << setw(20 - to_string(n_coll_2).length() + 1) << "|";
		cout << fixed << setprecision(2) << v_coll_2 << setw(23 - to_string(v_coll_2).length() + 1) << "|" << endl;
		cout << '|' << ">50,000 to <=100,000" << setw(3) << '|';
		cout << n_coll_3 << setw(20 - to_string(n_coll_3).length() + 1) << "|";
		cout << fixed << setprecision(2) << v_coll_3 << setw(23 - to_string(v_coll_3).length() + 1) << '|' << endl;
		cout << '|' << ">100,000" << setw(15) << '|';
		cout << n_coll_4 << setw(20 - to_string(n_coll_4).length() + 1) << "|";
		cout << fixed << setprecision(2) << v_coll_4 << setw(23 - to_string(v_coll_4).length() + 1) << "|" << endl;
		//line_border(64);
	}

	void view_active(CustomerInfo* cust, int &count) {
		header();
		for (int i = 0; i < count; i++) {
			if (cust[i].getWithdDate() == "" && cust[i].getRemark() != "delete") {
				cout << '|';
				cout << cust[i].getCustomerId() << setw(11 - cust[i].getCustomerId().length() + 1) << '|';
				cout << cust[i].getGroupLd() << setw(8 - cust[i].getGroupLd().length() + 1) << '|';
				cout << cust[i].getCustomerName() << setw(13 - cust[i].getCustomerName().length() + 1) << '|';
				cout << cust[i].getDepositDate() << setw(12 - cust[i].getDepositDate().length() + 1) << '|';
				cout << cust[i].getCollType() << setw(15 - cust[i].getCollType().length() + 1) << '|';
				cout << cust[i].getCollNo() << setw(17 - cust[i].getCollNo().length() + 1) << '|';
				cout << cust[i].getCollAddr() << setw(18 - cust[i].getCollAddr().length() + 1) << '|';
				cout << cust[i].getCollCCY() << setw(19 - cust[i].getCollCCY().length() + 1) << '|';
				cout << setprecision(2) << fixed << cust[i].getCollValue() << setw(20 - to_string(cust[i].getCollValue()).length() + 1) << '|';
				cout << endl;
			}
		}
		cout << endl;
	}

	void select_view_active(CustomerInfo* cust, int count, string key) {
		header();
		for (int i = 0; i < count; i++) {
			if (cust[i].getWithdDate() == "" && cust[i].getRemark() != "delete" && (cust[i].getCustomerId() + cust[i].getGroupLd()) == key) {
				cout << '|';
				cout << cust[i].getCustomerId() << setw(11 - cust[i].getCustomerId().length() + 1) << '|';
				cout << cust[i].getGroupLd() << setw(8 - cust[i].getGroupLd().length() + 1) << '|';
				cout << cust[i].getCustomerName() << setw(13 - cust[i].getCustomerName().length() + 1) << '|';
				cout << cust[i].getDepositDate() << setw(12 - cust[i].getDepositDate().length() + 1) << '|';
				cout << cust[i].getCollType() << setw(15 - cust[i].getCollType().length() + 1) << '|';
				cout << cust[i].getCollNo() << setw(17 - cust[i].getCollNo().length() + 1) << '|';
				cout << cust[i].getCollAddr() << setw(18 - cust[i].getCollAddr().length() + 1) << '|';
				cout << cust[i].getCollCCY() << setw(19 - cust[i].getCollCCY().length() + 1) << '|';
				cout << cust[i].getCollValue() << setw(20 - to_string(cust[i].getCollValue()).length() + 1) << '|';
				cout << endl;
			}
		}
		cout << endl;
	}

	void view_withdraw(CustomerInfo* cust, int count) {
		header();
		for (int i = 0; i < count; i++) {
			if (cust[i].getWithdDate() != "" && cust[i].getRemark() != "delete") {
				cout << '|';
				cout << cust[i].getCustomerId() << setw(11 - cust[i].getCustomerId().length() + 1) << '|';
				cout << cust[i].getGroupLd() << setw(8 - cust[i].getGroupLd().length() + 1) << '|';
				cout << cust[i].getCustomerName() << setw(13 - cust[i].getCustomerName().length() + 1) << '|';
				cout << cust[i].getDepositDate() << setw(12 - cust[i].getDepositDate().length() + 1) << '|';
				cout << cust[i].getCollType() << setw(15 - cust[i].getCollType().length() + 1) << '|';
				cout << cust[i].getCollNo() << setw(17 - cust[i].getCollNo().length() + 1) << '|';
				cout << cust[i].getCollAddr() << setw(18 - cust[i].getCollAddr().length() + 1) << '|';
				cout << cust[i].getCollCCY() << setw(19 - cust[i].getCollCCY().length() + 1) << '|';
				cout << cust[i].getCollValue() << setw(20 - to_string(cust[i].getCollValue()).length() + 1) << '|';
				cout << endl;
			}
		}
		cout << endl;
	}
	void search(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		string customer_id, group_id;
		char answer_key;
		do {
			cout << "        Customer ID: ";
			cin >> customer_id;
			if (search_Unikey_ID(cust, count, customer_id) == -1) {
				cout << "Not found" << endl;
			}
		} while (search_Unikey_ID(cust, count, customer_id) == -1);
		group_id = dv.input_ld();
		string key = customer_id + group_id;
		int found = search_key(cust, count, key);
		if (found != -1) {
			select_view_active(cust, count, key);
		}
		else {
			cout << "Not found" << endl;
		}
		cout << "Do you want to search more (y/n)?: "; cin >> answer_key;
		if (answer_key == 'y') {
			search(cust, count, user, count_user);
		}
		else {
			submenu_view(cust, count, user, count_user);
		}
	}
	void delete_collateral(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		string customer_id, group_id;
		char answer_key;
		char clarify_ans;
		do {
			cout << "        Customer ID: ";
			cin >> customer_id;
			if (search_Unikey_ID(cust, count, customer_id) == -1) {
				cout << "Not found" << endl;
			}
		} while (search_Unikey_ID(cust, count, customer_id) == -1);
		group_id = dv.input_ld();
		string key = customer_id + group_id;
		int found = search_key(cust, count, key);
		if (found != -1) {
			cout << "are you clear to delete this customer: " << cust[found].getCustomerName() << " (y/n)?: "; cin >> clarify_ans;
			if (clarify_ans == 'y') {
				cust[found].getRemark() = "delete";
				cout << "Successfully." << endl;
			}
			else {
				submenu_file(cust, count, user, count_user);
			}
		}
		else {
			cout << "Not found" << endl;
		}
		view_active(cust, count);
		cout << "Do you want to delete more (y/n)?: "; cin >> answer_key;
		if (answer_key == 'y') {
			delete_collateral(cust, count, user, count_user);
		}
		else {
			submenu_file(cust, count, user, count_user);
		}
	}
	void update_info(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		string customer_id, group_id, key_update;
		char answer_key;
		int field_key;
		do {
			cout << "        Customer ID: ";
			cin >> customer_id;
			if (search_Unikey_ID(cust, count, customer_id) == -1) {
				cout << "Not found" << endl;
			}
		} while (search_Unikey_ID(cust, count, customer_id) == -1);
		group_id = dv.input_ld();
		string key = customer_id + group_id;
		int found = search_key(cust, count, key);
		if (found != -1) {
			cout << "----------------------------------" << endl;
			cout << "1. Customer Name" << endl;
			cout << "2. Deposit Date" << endl;
			cout << "3. Collateral Type" << endl;
			cout << "4. Collateral Number" << endl;
			cout << "5. Collateral Address" << endl;
			cout << "6. Collateral Currency" << endl;
			cout << "7. Collateral Value" << endl;
			cout << "----------------------------------" << endl;
			cout << "Which fields do you want to update: "; cin >> field_key;
			if (field_key == 1) {
				cout << "Customer Name: "; cin >> key_update;
				cust[found].setCustomerName(key_update);
			}
			else if (field_key == 2) {
				cout << "Deposit Date: "; cin >> key_update;
				cust[found].setDepositDate(key_update);
			}
			else if (field_key == 3) {
				cout << "Collateral Type: "; cin >> key_update;
				cust[found].setCollType(key_update);
			}
			else if (field_key == 4) {
				cout << "Collateral Number: "; cin >> key_update;
				cust[found].setCollNo(key_update);
			}
			else if (field_key == 5) {
				cout << "Collateral Address: "; cin >> key_update;
				cust[found].setCollAddr(key_update);
			}
			else if (field_key == 6) {
				cout << "Collateral Currency: "; cin >> key_update;
				cust[found].setCollCCY(key_update);
			}
			else if (field_key == 7) {
				cout << "Collateral Value: "; cin >> key_update;
				cust[found].setCollValue(stof(key_update));
			}
			else {
				cout << "Invalid field.";
			}
			view_active(cust, count);
			cout << "Do you want to update more (y/n)?: "; cin >> answer_key;
			if (answer_key == 'y') {
				update_info(cust, count, user, count_user);
			}
			else {
				submenu_file(cust, count, user, count_user);
			}
		}
	}
	void withdrawal(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		string customer_id, group_id, withdrawal_date;
		char answer_key;
		char clarify_ans;
		do {
			cout << "        Customer ID: ";
			cin >> customer_id;
			if (search_Unikey_ID(cust, count, customer_id) == -1) {
				cout << "Not found" << endl;
			}
		} while (search_Unikey_ID(cust, count, customer_id) == -1);
		group_id = dv.input_ld();
		withdrawal_date = dv.input_date();
		string key = customer_id + group_id;
		int found = search_key(cust, count, key);
		if (found != -1) {
			cout << "are you clear to withdraw this customer: " << cust[found].getCustomerName() << " (y/n)?: "; cin >> clarify_ans;
			if (clarify_ans == 'y') {
				cust[found].getWithdDate() = withdrawal_date;
				cout << "Successfully." << endl;
			}
			else {
				submenu_file(cust, count, user, count_user);
			}
		}
		else {
			cout << "Not found" << endl;
		}
		view_active(cust, count);
		cout << "Do you want to withdraw more (y/n)?: "; cin >> answer_key;
		if (answer_key == 'y') {
			withdrawal(cust, count, user, count_user);
		}
		else {
			submenu_file(cust, count, user, count_user);
		}
	}
	bool search_key_id(CustomerInfo* cust, int count, string key) {
		for (int i = 0; i < count; i++) {
			if (key == cust[i].getCustomerId() || stoi(key) <= 0 || key.length() != 6) {
				return true;
				break;
			}
		}
		return false;
	}
	string get_id(CustomerInfo* cust, int count) {
		string id;
		while (true) {
			cout << "        Customer ID: ";
			cin >> id;
			if (id.length() != 6) {
				cout << "error: user id is unable to be over or lower 6 digits." << endl;
			}
			else if (stoi(id) <= 0) {
				cout << "error: unable to use minus sign " << endl;
			}
			else if (search_key_id(cust, count, id)) {
				cout << "error: duplicated id in list." << endl;
			}
			else {
				return id;
			}
		}
	}
	void deposit(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		char answer_key;
		cout << "-----------------------------" << endl;
		cout << "           Customer ID(6 digits):" << endl;
		cout << "               Group LD(ldxxxxx):" << endl;
		cout << "         Customer Name(no space):" << endl;
		cout << "              Value Date(ddmmyy):" << endl;
		cout << "      Collateral Type(hard|soft):" << endl;
		cout << "               Collateral Number:" << endl;
		cout << "  Collateral Address(3|4 digits):" << endl;
		cout << "Collateral Currency(khr,usd,thb):" << endl;
		cout << "         Collateral Value(value):" << endl;
		cout << "-----------------------------" << endl;
		cout << "Pls enter data by each fields" << endl;
		cout << "-----------------------------" << endl;
		cust[count].input();
		cout << "Successfully." << endl;
		count++;
		//cust[count-1].covert_coll_value = conv_ccy_to_usd(cust[count-1].coll_value, cust[count-1].coll_currency);
		view_active(cust, count);
		cout << "Do you want to add more (y/n)?: "; cin >> answer_key;
		if (answer_key == 'y') {
			deposit(cust, count, user, count_user);
		}
		else {
			submenu_file(cust, count, user, count_user);
		}
	}
	void submenu_file(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		int menu = 0;;
		cout << "-------------------------" << endl;
		cout << "1. Deposit" << endl;
		cout << "2. Withdraw" << endl;
		cout << "3. Update" << endl;
		cout << "4. Delete" << endl;
		cout << "5. Save" << endl;
		cout << "6. Log Off" << endl;
		cout << "7. Main Menu" << endl;
		cout << "-------------------------" << endl;
		cout << "Pls choose sub menu (1-7): ";
		cin >> menu;
		switch (menu) {
		case 1:
			deposit(cust, count, user, count_user);
			break;
		case 2:
			withdrawal(cust, count, user, count_user);
			break;
		case 3:
			update_info(cust, count, user, count_user);
			break;
		case 4:
			delete_collateral(cust, count, user, count_user);
			break;
		case 5:
			write_file(cust, count);
			submenu_file(cust, count, user, count_user);
			break;
		case 6:
			log_in(user, count_user, cust, count);
			break;
		case 7:
			main_menu(cust, count, user, count_user);
			break;
		default:
			cout << "Invalid menu";
			break;
		}
	}
	void submenu_view(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		int menu = 0;
		cout << "-------------------------" << endl;
		cout << "1. Search" << endl;
		cout << "2. View" << endl;
		cout << "3. Main Menu" << endl;
		cout << "-------------------------" << endl;
		cout << "Pls choose sub menu (1-3): ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			search(cust, count, user, count_user);
			break;
		case 2:
			view_active(cust, count);
			submenu_view(cust, count, user, count_user);
			break;
		case 3:
			main_menu(cust, count, user, count_user);
			break;
		default:
			cout << "Invalid menu";
			break;
		}
	}
	void submenu_report(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		int menu = 0;
		char answer_key;
		cout << "-----------------------------" << endl;
		cout << "1. List of active collateral" << endl;
		cout << "2. List of withdrawal collateral" << endl;
		cout << "3. Summary report by currency" << endl;
		cout << "4. Summary report by collateral value" << endl;
		cout << "-----------------------------" << endl;
		cout << "Pls choose above report (1-4): ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			view_active(cust, count);
			break;
		case 2:
			view_withdraw(cust, count);
			break;
		case 3:
			summ_rpt_ccy(cust, count);
			break;
		case 4:
			summ_rpt_vcoll(cust, count);
			break;
		default:
			cout << "Invalid menu";
			break;
		}
		cout << "Do you want to report more (y/n)?: "; cin >> answer_key;
		if (answer_key == 'y') {
			submenu_report(cust, count, user, count_user);
		}
		else {
			main_menu(cust, count, user, count_user);
		}
	}
	void submenu_about(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		int menu = 0;
		cout << " +++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "+      STEP IT ACADEMY CAMBODIA         +" << endl;
		cout << "+    Collateral Management System       +" << endl;
		cout << "+ Copyright @2023         Version 1.1.1 +" << endl;
		cout << "+      Produced by: Hak Vandara         +" << endl;
		cout << " +++++++++++++++++++++++++++++++++++++++" << endl;
		main_menu(cust, count, user, count_user);
	}
	void welcome_program_menu() {
		string text = "--------Wellcome To Program Menu--------";
		int screenWidth = 100;
		int padding = (screenWidth - text.length()) / 2;
		cout << setw(padding + text.length()) << text << endl;
	}
	void main_menu(CustomerInfo* cust, int count, userinfo user[], int count_user) {
		int menu = 0;
		cout << "---------------------" << endl;
		cout << "1. File" << endl;
		cout << "2. View" << endl;
		cout << "3. Report" << endl;
		cout << "4. About" << endl;
		cout << "5. Exit" << endl;
		cout << "---------------------" << endl;
		cout << "Pls choose menu (1-5): ";
		cin >> menu;
		switch (menu) {
		case 1:
			submenu_file(cust, count, user, count_user);
			break;
		case 2:
			submenu_view(cust, count, user, count_user);
			break;
		case 3:
			submenu_report(cust, count, user, count_user);
			break;
		case 4:
			submenu_about(cust, count, user, count_user);
			break;
		case 5:
			write_file(cust, count);
			exit(0);
		default:
			cout << "Invalid menu";
			break;
		}
	}
};