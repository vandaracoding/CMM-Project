#pragma once
#include<string>
#include"Customerinfo.cpp"
using namespace std;

struct userinfo;
void welcome_user_menu();
void line_border(int length);
void user_header();
void view_active_user(userinfo user[], int count, string mark);
void write_file_user(userinfo user[], int count);
void read_file_user(userinfo user[], int count_user, CustomerInfo cust[], int count);
bool isComplexPasword(const string& password);
void GetPassword(userinfo user[], int count, string& NewPassword);
int search_key_user(userinfo user[], int count, string key);
void search_user(userinfo user[], int count_user, CustomerInfo cust[], int count);
void update(userinfo user[], int count_user, CustomerInfo cust[], int count);
void sort_user(userinfo user[], int count_user, CustomerInfo cust[], int count);
void delete_(userinfo user[], int count_user, CustomerInfo cust[], int count);
void adm_menu(userinfo user[], int count_user, CustomerInfo cust[], int count);
void profile_menu(userinfo user[], int count_user, string UserProfile, CustomerInfo cust[], int count);
void log_in(userinfo user[], int count_user, CustomerInfo cust[], int count);
void register_(userinfo user[], int& count_user, CustomerInfo cust[], int count);
void main_menu_user(userinfo user[], int count_user, CustomerInfo cust[], int count);
//------validate field
bool search_key_userid(userinfo user[], int count, string key);
string get_userid(userinfo user[], int count);
bool validate_username(string name);
string get_username();
bool validate_gender(char gender);
char get_gender();
bool validate_bookingdate(string date);
string get_bookingdate();
bool validate_profile(string gender);
string get_profile();