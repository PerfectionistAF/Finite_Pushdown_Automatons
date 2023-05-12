#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include <iomanip>
#include <cstdio>
#include <bits/stdc++.h>
#define MAX 128
//#define epsilon string s(1, 'E')
using namespace std;

string largest_string[MAX];
const string epsilon = "-E-";

void data_entry(string s[], int size = 1) {
  string stop = "$";
    for(int i = 0; i < size; i++){
        cin>>s[i];

          if(s[i] == stop){
          break;
          }

    }
    /*if(strlen(s)>size){
        cout<<"Entered more than required size, please re-enter:"<<endl;
        data_entry(s, size);
    }*/
    cout << endl;
}

void data_display(string s[], int size = 1) {
    for(int i = 0; i < size; i++){
        cout<<s[i]<<" ";
    }
    cout << endl;
}
 
int string_length(string s)  
{  
    int length = 0;  
    for (int i = 0; s[i] != '\0'; i++)  
    {  
        length++;  
          
    }  
    return length;     
}  
    
void split_string (string s, char seperator)  
{  
    int currentindex = 0, i = 0;  
    int startindex = 0, endindex = 0;  
    while (i <= string_length(s))  
    {  
        if (s[i] == seperator || i == string_length(s))  
        {  
            endindex = i;  
            string substring = "";  
            substring.append(s, startindex, endindex - startindex);  
            largest_string[currentindex] = substring;  
            currentindex += 1;  
            startindex = endindex + 1;  
        }  
        i++;  
        }     
} 

int term_count(string s, int size = 1){
    int count = 0;
    split_string(s,' ');
    for(int i = 0; i<string_length(s); i++){
        if(s[i]>='a' && s[i]<='z'){
                count++;
            }
    }
    return count;
}

bool is_term(char s){
    bool is_term = false;
        if(s>='a' && s<='z'){
            is_term = true;
        }
    return is_term;
}

class NewState{
    private:
    string name;
    bool accepting = false;
    string readpoppush ;
    public:
    void set_name() {
    string stop = "$";
    cout<<"Write name of state, end with $"<<endl;
    string s;
    getline(cin, s);
    name = s;
    if(s == stop){
      exit;
    }
    cout << endl;
    }

    string get_name() {
    //cout<<s<<endl;
        return this->name;
    }

    void set_accepting(string s, bool accept = false){
        accepting = accept;
    }

    bool get_accepting(){
        return this->accepting;
    }

    void set_readpoppush(string s){
        string stop = "$";
        //getline(cin, s);
        readpoppush = s;
        if(s == stop){
            exit;
        }
        //cout << endl;   
    }

    string get_readpoppush(){
        return this->readpoppush;
    }

    void display(){
        cout<<"name: "<<this->name<<" transition:-> "<<this->readpoppush<<" accepting: "<<this->accepting<<endl;
    }
};

int main(){
    string grammar[MAX];
    string LHS[MAX];
    string RHS[MAX];
    int LHS_size=0;
    int RHS_size=0;
    string stop = "$";

    cout<<"LHS of your production rules of size?:";
    cin>>LHS_size;
    cout<<endl;
    data_entry(LHS, LHS_size);
    cout<<"_______________________________"<<endl;
    data_display(LHS, LHS_size);
    
    cout<<"RHS of your production rules of size?:";
    cin>>RHS_size;
    cout<<endl;
    data_entry(RHS, RHS_size);
    cout<<"_______________________________"<<endl;
    data_display(RHS, RHS_size);

    cout<<"Your grammar rules, one rule at a time:"<<endl;
    int i =0;
    int j=0;
    //one rule at a time
    while(i<LHS_size && j<RHS_size){
        grammar[i] = LHS[i] +"->"+ RHS[j];
        cout<<grammar[i]<<endl;
        i++;
        j++;
    }
    //write_grammar("grammar.txt");
    //Grammar grammar = read_grammar("grammar.txt");
    //write_test_cases(grammar);
    //string ass1 [MAX]= grammar.nonterminals; 
    
    cout<<"_______________________________"<<endl;
    //Mandatory states
    NewState states[4];
    cout<<"Mandatory states:"<<endl;
    states[0].set_name();
    for(int ptr=0; ptr<4; ptr++){
            cout<<"state: "<<ptr<<endl;
            states[ptr].set_name();
    }
    cout<<"_______________________________"<<endl;
    string str;
    str.append(epsilon);
    str.append(epsilon);
    str.append("$");
    states[0].set_readpoppush(str);
    states[1].set_readpoppush(epsilon + epsilon +LHS[0]);
    states[2].set_readpoppush(epsilon +"$"+ epsilon);
    states[3].set_accepting(states[3].get_name(), true);
    for(int ptr=0; ptr<4; ptr++){
            states[ptr].display();
    }
    cout<<endl;
    cout<<endl;
    for(int ptr=0; ptr<4; ptr++){
        for(int ptr2=ptr; ptr2<ptr+1; ptr2++){
            cout<<" -->"<<states[ptr].get_name()<<" -- "<<states[ptr].get_readpoppush();
        }
    }
    cout<<endl;
    cout<<"_______________________________"<<endl;
    //Produced states from qloop
    cout<<"Qloop States:"<<endl;
    cout<<"Separate RHS strings, then declare conditions of terminals, nonterminals and single states"<<endl;
    NewState qloop[MAX/2];
    int count = 0;
    int z = 0;
    int length = RHS[count].length();
    char RHS_new[length+1];
    char RHS_reverse[length+1];
    while(count<RHS_size){
        length = RHS[count].length();
        char RHS_new[length+1];
        char RHS_reverse[length+1];
        //RHS_new[length+1];
        strcpy(RHS_new, RHS[count].c_str());
        //RHS_reverse = new char[length+1];
        cout <<RHS[count]<< " separated into:"<<endl;
        for(int i = 0; i<length; i++){
            cout<<RHS_new[i]<<"--";
        }
        cout<<endl;
        cout<<"_______________________________"<<endl;
        cout<<endl;
        cout<<RHS[count]<< " reversed into:"<<endl;
        for(int i =0, j = length-1; i<length, j>=0; i++, j--){
            RHS_reverse[i] = RHS_new[j];
            cout<<RHS_reverse[i]<<"--";
        }
        cout<<endl;
        cout<<"_______________________________"<<endl;
        cout<<endl;
        cout<<"Qloop States:"<<endl;
        bool flag = false;
        if(RHS[count].length()==1){
            flag = true;
            cout<<"Production rule with a string of one character only detected"<<endl;
            //if (flag){
                string getter;
                qloop[z].set_name();
                getter = epsilon + LHS[count] +"-"+ RHS[count];
                qloop[z].set_readpoppush(getter);
                cout<<"Number of turns:"<<z<<endl;
                cout<<endl;
                cout<<"QLOOP----------------->";
                qloop[z].display();
                z++;
              //  }
        }
        
        else{
            cout<<"Production rule with a string of several characters detected"<<endl;
            
            for(int a=0; a<strlen(RHS_reverse); a++){
                string getter;
                
                if(is_term(RHS_reverse[a])){
                    //cout<<"If string contains terminal values:"<<endl;
                    qloop[a].set_name();
                    std::string s2(1, RHS_reverse[a]);
                    getter = s2 +"-"+ s2 + epsilon;
                    qloop[a].set_readpoppush(getter);
                    cout<<"Number of turns:"<<z<<endl;
                    cout<<endl;
                    cout<<"QLOOP----------------->";
                    qloop[a].display();
                    z++;
                }
                for(int b=a+1; b<strlen(RHS_reverse); b++){
                    if(!(is_term(RHS_reverse[b]))&&is_term(RHS_reverse[a]) ||
                    !(is_term(RHS_reverse[a]))&&is_term(RHS_reverse[b]) ||
                    !(is_term(RHS_reverse[a]))&&!(is_term(RHS_reverse[b])) ||
                    !(is_term(RHS_reverse[b]))&&!(is_term(RHS_reverse[a]))){
                        
                        //cout<<"If string contains both terminal and nonterminal values:"<<endl;
                        qloop[a].set_name();
                        if(a==0){
                            //std::string s1(1, LHS[i]);
                            std::string s2(1, RHS_reverse[a]);
                            getter = epsilon + LHS[count]+"-"+ s2;
                            qloop[a].set_readpoppush(getter);
                            cout<<"Number of turns:"<<z<<endl;
                            cout<<endl;
                            cout<<"QLOOP----------------->";
                            qloop[a].display();
                            z++;
                        }
                        else{
                            std::string s2(1, RHS_reverse[i]);
                            getter=epsilon + epsilon + RHS_reverse[a];
                            qloop[a].set_readpoppush(getter);
                            cout<<"Number of turns:"<<z<<endl;
                            cout<<endl;
                            cout<<"QLOOP----------------->";
                            qloop[a].display();
                            z++;
                        } 
                    }  
                }
                
            }
        }
        cout<<endl;
        cout<<"_______________________________"<<endl;
        cout<<endl;
        count++;
    }

}//end
    