#pragma once
#include <iostream>
#include<iomanip>
#include<string>
#include "DataInputValidation.cpp"
#include "BadInputException.cpp"
using namespace std;

class CustomerInfo {
private:
    string customer_id;
    string group_ld;
    string customer_name;
    string deposit_date;
    string coll_type;
    string coll_number;
    string coll_address;
    string coll_currency;
    double coll_value;
    string withdrawal_date;
    string remark;
    double covert_coll_value;
    DataInputValidation val;

public:
    CustomerInfo() :customer_id("Unknown"), group_ld("Unknown"), customer_name("Unknown"),
        deposit_date("Unknown"), coll_type("Unknown"), coll_number("Unknown"), coll_address("Unknown"),
        coll_currency("Unknown"), withdrawal_date("Unknown"), remark("Unknown"){}
    CustomerInfo(string customer_id, string group_ld, string customer_name, string deposit_date, string coll_type,
        string coll_number, string coll_address, string coll_currency, double coll_value, string withdrawal_date,
        string remark, double covert_coll_value) {
        setCustomerId(customer_id);
        setGroupLd(group_ld);
        setCustomerName(customer_name);
        setDepositDate(deposit_date);
        setCollType(coll_type);
        setCollNo(coll_number);
        setCollAddr(coll_address);
        setCollCCY(coll_currency);
        setCollValue(coll_value);
        setWithdDate(withdrawal_date);
        setRemark(remark);
        setConvCollValue(covert_coll_value);
    }
    void setCustomerId(const string customer_id) {
        if (!customer_id.empty()) {
            this->customer_id = customer_id;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getCustomerId() const {
        return this->customer_id;
    }
    void setGroupLd(const string group_ld) {
        if (!group_ld.empty()) {
            this->group_ld = group_ld;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getGroupLd() const {
        return this->group_ld;
    }
    void setCustomerName(const string customer_name) {
        if (!customer_name.empty()) {
            this->customer_name = customer_name;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getCustomerName() const {
        return this->customer_name;
    }
    void setDepositDate(const string deposit_date) {
        if (!deposit_date.empty()) {
            this->deposit_date = deposit_date;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getDepositDate() const {
        return this->deposit_date;
    }
    void setCollType(const string coll_type) {
        if (!coll_type.empty()) {
            this->coll_type = coll_type;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getCollType() const {
        return this->coll_type;
    }
    void setCollNo(const string coll_number) {
        if (!coll_number.empty()) {
            this->coll_number = coll_number;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getCollNo() const {
        return this->coll_number;
    }
    void setCollAddr(const string coll_address) {
        if (!coll_address.empty()) {
            this->coll_address = coll_address;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getCollAddr() const {
        return this->coll_address;
    }
    void setCollCCY(const string coll_currency) {
        if (!coll_currency.empty()) {
            this->coll_currency = coll_currency;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getCollCCY() const {
        return this->coll_currency;
    }
    void setCollValue(const double coll_value) {
        if (coll_value > 0) {
            this->coll_value = coll_value;
        }
        else
        {
            throw BadInputException();
        }
    }
    double getCollValue() const {
        return this->coll_value;
    }
    void setWithdDate(const string withdrawal_date) {
        if (!withdrawal_date.empty()) {
            this->withdrawal_date = withdrawal_date;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getWithdDate() const {
        return this->withdrawal_date;
    }
    void setRemark(const string remark) {
        if (!remark.empty()) {
            this->remark = remark;
        }
        else
        {
            throw BadInputException();
        }
    }
    string getRemark() const {
        return this->remark;
    }
    
    void setConvCollValue(const double covert_coll_value) {
        if ((covert_coll_value > 0)) {
            this->covert_coll_value = covert_coll_value;
        }
        else
        {
            throw BadInputException();
        }
    }
    double getConvCollValue() const {
        return this->covert_coll_value;
    }

    /*virtual void output() {
        cout << setw(8) <<getGroupLd()<<setw(10)<< getCustomerName() << setw(16) << getDepositDate() << setw(13) << getCollValue();
    }*/

    virtual void input() {
        string customer_id;
        string group_ld;
        string customer_name;
        string deposit_date;
        string coll_type;
        string coll_number;
        string coll_address;
        string coll_currency;
        double coll_value;
        
        customer_id = val.input_id();
        setCustomerId(customer_id);
        group_ld = val.input_ld();
        setGroupLd(group_ld);
        customer_name = val.input_name();
        setCustomerName(customer_name);
        deposit_date = val.input_date();
        setDepositDate(deposit_date);
        coll_type = val.input_coltype();
        setCollType(coll_type);
        coll_number = val.input_colno();
        setCollNo(coll_number);
        coll_address = val.input_address();
        setCollAddr(coll_address);
        coll_currency = val.input_ccy();
        setCollCCY(coll_currency);
        coll_value = val.input_colvalue();
        setCollValue(coll_value);
    }
    //virtual void view_active(CustomerInfo cust[], int* count) {
    //    //header();
    //    for (int i = 0; i < *count; i++) {
    //        if (cust[i].getWithdDate() == "" && cust[i].getRemark() != "delete") {
    //            cout << '|';
    //            cout << cust[i].getCustomerId() << setw(11 - cust[i].getCustomerId().length() + 1) << '|';
    //            cout << cust[i].getGroupLd() << setw(8 - cust[i].getGroupLd().length() + 1) << '|';
    //            cout << cust[i].getCustomerName() << setw(13 - cust[i].getCustomerName().length() + 1) << '|';
    //            cout << cust[i].getDepositDate() << setw(12 - cust[i].getDepositDate().length() + 1) << '|';
    //            cout << cust[i].getCollType() << setw(15 - cust[i].getCollType().length() + 1) << '|';
    //            cout << cust[i].getCollNo() << setw(17 - cust[i].getCollNo().length() + 1) << '|';
    //            cout << cust[i].getCollAddr() << setw(18 - cust[i].getCollAddr().length() + 1) << '|';
    //            cout << cust[i].getCollCCY() << setw(19 - cust[i].getCollCCY().length() + 1) << '|';
    //            cout << setprecision(2) << fixed << cust[i].getCollValue() << setw(20 - to_string(cust[i].getCollValue()).length() + 1) << '|';
    //            cout << endl;
    //        }
    //    }
    //    cout << endl;
    //}
};