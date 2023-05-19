#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include <iomanip>
#include <cstdio>
#include <bits/stdc++.h>
#include <vector>

using namespace std;
/*This code uses a language consisting of {a,b} to check whether the input 
string is a palindrome or not.

Potential accepted strings:
aaa
aaaa
aba
abba
*/
void entry(char str[], int size =10){
    int size = 0;
    while(str[size]!='$'){      //stop if entry is $
        cin>>str[size];
        size++;
    }
    for(int i=0; i<size; i++){
        cout<<str[i];
    }
}
void PrintStack(stack<char> s)
{
    if (s.empty())
        return;
 

    int x = s.top();
    s.pop();
    cout << x ;

    PrintStack(s);
    //don't lose your stack
    s.push(x);
}
bool EvenStack(stack<char> s){
    bool even= false;
    if(s.size()%2 ==0){
        return true;
    }
    else{
        return false;
    }
}
int main(){

    stack<char> input;
    char user_input[10];
    cout<<"Enter string of size and contents:"<<endl;
    entry(user_input);

    for(int i=0; i<strlen(user_input); i++){
        input.push(user_input[i]);
    }
    cout<<"Input stack contents:"<<endl;
    PrintStack(input);
    int size = input.size();
    cout<<"Size of stack is:"<< size;
    int midpoint = 0;
    if(EvenStack(input)){
        cout<<"Size is an even number, so use the second half of the input"<<endl;
        //check if current stack size after popping is midpoint = stack size/2
        midpoint = size/2;
    }
    else{
        cout<<"Size is an odd number, so use the middle of the input"<<endl;
        //check if current stack size after popping is midpoint == floor(stack size / 2)
        midpoint = floor(size/2);
    }
    stack <char> pushdownstack;
    pushdownstack.push('$');
    cout<<"Pushdown stack has been prepared with initial contents of: $"<<endl;
    //push language characters until midpoint
    //then check if input characters == pushdownstack characters, then pop
    //if pushdownstack size ==1 then "ACCEPT" since only null character remains, else "REJECT"
    while(input.size()!=0){         //Assume palindrome is accepted the first time and 
                                    //your grammar includes all terminal characters {a,b}
        pushdownstack.push(input.top());
        input.pop();
        if(EvenStack(input))    //even length of input, instead of comparing to midpoint
        {
            if(input.top() == pushdownstack.top()){
                input.pop();
                pushdownstack.pop();
            } 
        }
        else{                  //odd length of input
            input.pop();
        }
    }
    if(pushdownstack.size()==1){
        cout<<"ACCEPTED"<<endl;
    }
    else{
        cout<<"REJECTED"<<endl;
    }
}