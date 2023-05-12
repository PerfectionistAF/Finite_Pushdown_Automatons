#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <exception>

using namespace std;

class isNotRestricted : public exception {
private:
    string mssg;
    string str;
public:
    isNotRestricted(map<string, vector<string>> Grammar) {
        mssg = "Grammar has length greater than 1 on the left side ";
        for (auto& keys : Grammar) {
            if (keys.first.length() > 1) {
                str = str + keys.first + " ";
            }
        }
    }
    virtual const char* what() const throw() {
        string string_ = mssg + str;
        return string_.c_str();
    }
};

class isNotRightLinear : public exception {
private:
    string mssg1;
    string val;
    string mssg2;
public:
    isNotRightLinear(string _val) : val(_val) {
        mssg1 = "Grammar is not Right Linear - all the variables on right side of the rule should be states \n";
        mssg2 = "Check out rule ";
    }
    virtual const char* what() const throw() {
        string string_ = mssg1 + mssg2 + val;
        return string_.c_str();
    }
};

class isNotLeftLinear : public exception {
private:
    string mssg1;
    string val;
    string mssg2;
public:
    isNotLeftLinear(string _val) : val(_val) {
        mssg1 = "Grammar is not Left Linear - all the variables on left side of the rule should be states \n";
        mssg2 = "Check out rule ";
    }
    virtual const char* what() const throw() {
        string string_ = mssg1 + mssg2 + val;
        return string_.c_str();
    }
};

class IllegalProductionException : public exception {
private:
    string message;
public:
    IllegalProductionException(const string& msg) : message(msg) {}
    //Call try and catch to use the custom exception--->in Grammer_Input.cpp
    string what(){
        return message;
    }
};

