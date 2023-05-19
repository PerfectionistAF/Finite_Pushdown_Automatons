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
/*This code uses a dfa to check whether or not the input string is accepted.
The criterion used here is 3 consecutive 0's followed by any number of 1's
Potential accepted strings:
0001
000
Potential rejected strings:
00010
//{0,       0,      0,      1,      -1}   0:transition  1:accepting  -1:dead 
//{index0, index1, index2, index3, index4}
*/
void entry(char str[], int size =100){
    int size = 0;
    while(str[size]!='$'){      //stop if entry is $
        cin>>str[size];
        size++;
    }
    for(int i=0; i<size; i++){
        cout<<str[i];
    }
}
void PrintStack(deque<char> s)
{
    if (s.empty())
        return;
 

    int x = s.front();
    s.pop_front();
    cout << x ;

    PrintStack(s);
    //don't lose your stack
    s.push_back(x);
}
int Forward(deque<char>s, int finalstate){
        if(s.front()==0 && finalstate==0){
            finalstate = 1;
            s.pop_front();//state0-->state1
        }
        else if(s.front()==0 && finalstate==1){
            finalstate = 2;
            s.pop_front();//state1-->state2
        }
        else if(s.front()==0 && finalstate==2){
            finalstate = 3;
            s.pop_front();//state2-->state3
        }
        else if(s.front()==1 && finalstate==3){//
            finalstate = 3;
            s.pop_front();//state3-->state3
        }
        else{
            finalstate;
        }
        return finalstate;
}
int Reject(deque<char>s, int finalstate){
        /*if(s.front()==1 && finalstate==1){
            finalstate = 4;

            s.pop_front();//state1-->state0
        }
        else if(s.front()==1 && finalstate==2){
            finalstate = 4;
            s.pop_front();//state2-->state1
        }*/
        if(s.front()==0 && finalstate==3){
            finalstate = 4;
            //state3-->state4(reject)
        }
        else{
            finalstate = 4;
            //state0-->state4(reject)
            //state1-->state4(reject)
            //state2-->state4(reject)
        }
        return finalstate;
}
int main(){
    deque<char> input;
    char user_input[100];
    cout<<"Enter string of size and contents:"<<endl;
    entry(user_input);

    for(int i=0; i<strlen(user_input); i++){
        input.push_back(user_input[i]);
    }
    cout<<"Input stack contents:"<<endl;
    PrintStack(input);
    int size = input.size();
    cout<<"Size of stack is:"<< size;

    int states[5]={0, 0, 0, 1, -1};
    cout<<"States:"<<endl;
    for(int i =0; i<5; i++){
        cout<<"state:"<<states[i]<<"____";
    }
    int finalstate = 0; //initialise final state with beginning index
    while(!input.empty()){
        finalstate=Forward(input, finalstate);
        finalstate=Reject(input, finalstate);
        
        if(finalstate==4)
            exit;
    }
    //check value in index of finalstate
    if(states[finalstate]==1){
        cout<<"ACCEPTED"<<endl;
    }
    else{
        cout<<"REJECTED"<<endl;
    }
}