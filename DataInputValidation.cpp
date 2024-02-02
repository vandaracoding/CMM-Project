#pragma once
#include<iostream>
using namespace std;

class DataInputValidation {
private:
    bool validate_ld(string ld) {
        if (ld.length() != 7) {
            return false;
        }
        return true;
    }
    bool validate_name(string name) {
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
    bool validate_ccy(string ccy) {
        if (ccy == "usd" || ccy == "khr" || ccy == "thb") {
            return true;
        }
        return false;
    }
    bool validate_date(string date) {
        if (date.length() == 6) {
            return true;
        }
        return false;
    }
    bool validate_coltype(string coltype) {
        if (coltype == "hard" || coltype == "soft") {
            return true;
        }
        return false;
    }
    bool validate_address(string address) {
        if (address.length() == 3 || address.length() == 4) {
            return true;
        }
        return false;
    }
    bool validate_colvalue(double colvalue) {
        if (colvalue >= 0) {
            return true;
        }
        return false;
    }
public:
    string input_id() {
        string id;
        cout << "        Customer ID: ";
        cin >> id;
        return id;
    }
    string input_ld() {
        string ld;
        while (true) {
            cout << "           Group LD: ";
            cin >> ld;
            if (!validate_ld(ld)) {
                cout << "error: invalid ld " << endl;
            }
            else {
                return ld;
            }
        }
    }
    string input_name() {
        string name;
        while (true) {
            cout << "      Customer Name: ";
            cin >> name;
            if (!validate_name(name)) {
                cout << "error: invalid name " << endl;
            }
            else {
                return name;
            }
        }
    }
    string input_ccy() {
        string ccy;
        while (true) {
            cout << "Collateral Currency: ";
            cin >> ccy;
            if (!validate_ccy(ccy)) {
                cout << "error: invalid currency " << endl;
            }
            else {
                return ccy;
            }
        }
    }
    string input_date() {
        string date;
        while (true) {
            cout << "               Date: ";
            cin >> date;
            if (!validate_date(date)) {
                cout << "error: invalid date " << endl;
            }
            else {
                return date;
            }
        }
    }
    string input_coltype() {
        string coltype;
        while (true) {
            cout << "    Collateral Type: ";
            cin >> coltype;
            if (!validate_coltype(coltype)) {
                cout << "error: invalid collateral type " << endl;
            }
            else {
                return coltype;
            }
        }
    }
    string input_colno() {
        string colno;
        cout << "  Collateral Number: ";
        cin >> colno;
        return colno;
    }
    string input_address() {
        string address;
        while (true) {
            cout << " Collateral Address: ";
            cin >> address;
            if (!validate_address(address)) {
                cout << "error: invalid address " << endl;
            }
            else {
                return address;
            }
        }
    }
    double input_colvalue() {
        double colvalue;
        while (true) {
            cout << "   Collateral Value: ";
            cin >> colvalue;
            if (cin.fail()) {
                cout << "error: this field allow to input only value " << endl;
            }
            else if (!validate_colvalue(colvalue)) {
                cout << "error: unable to use minus sign " << endl;
            }
            else {
                return colvalue;
            }
        }
    }
};

