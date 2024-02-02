#pragma once
#include <iostream>
#include "CustomerInfo.cpp"
#include"hfuser_login_struct.h"
using namespace std;

class CollateralDAO {
public:
	virtual void header() = 0;
	virtual void write_file(CustomerInfo* cust, int count) = 0;
	virtual void read_file(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void summ_rpt_ccy(CustomerInfo* cust, int count) = 0;
	virtual double conv_ccy_to_usd(double coll_value, string ccy) = 0;
	virtual void summ_rpt_vcoll(CustomerInfo* cust, int count) = 0;
	//virtual void view_active(CustomerInfo* cust, int count) = 0;
	virtual void select_view_active(CustomerInfo* cust, int count, string key) = 0;
	virtual void view_withdraw(CustomerInfo* cust, int count) = 0;
	virtual void search(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void delete_collateral(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void update_info(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void withdrawal(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual bool search_key_id(CustomerInfo* cust, int count, string key) = 0;
	virtual string get_id(CustomerInfo* cust, int count) = 0;
	virtual void deposit(CustomerInfo* cust, int& count, userinfo user[], int count_user) = 0;
	virtual void submenu_file(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void submenu_view(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void submenu_report(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void submenu_about(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;
	virtual void welcome_program_menu() = 0;
	virtual void main_menu(CustomerInfo* cust, int count, userinfo user[], int count_user) = 0;


};