#include <iostream>
#include"hfuser_login.h"
#include"hfuser_login_struct.h"
#include"Collateral.cpp"
using namespace std;

int main()
{
	const int size = 100;
	userinfo user[size];
	CustomerInfo* cust = new CustomerInfo[size];
	int count = 0;
	int count_user = 0;
	read_file_user(user, count_user, cust, count);
    return 0;
}
