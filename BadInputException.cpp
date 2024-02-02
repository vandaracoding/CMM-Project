#pragma once
#include<iostream>
using namespace std;

class BadInputException : public exception {
    const char* what() const throw() {
        return "Error: bad input";
    }
};