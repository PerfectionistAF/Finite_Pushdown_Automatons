#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <Grammer_Exeptions.cpp>


using namespace std;

class Grammar {
public:
    int num_nonterminals = 0;
    int num_terminals = 0;
    int linear = 0; // will be -1 for left linear, 1 for right linear, and 2 for regular

    string startvariable = "S";
    vector<string> nonterminals;
    vector<string> terminals;
    map<string, vector<string>> dict_grammar;

    void set_numOfnonterm() {
        num_nonterminals = (int)nonterminals.size();
    }

    void set_numOfterm() {
        num_terminals = (int)terminals.size();
    }
    /*This code block is iterating over a map named dict_grammar 
    and constructing a string message that represents the entire grammar in the correct format.

    The map dict_grammar is a container that stores a set of production rules 
    for each non-terminal state in the grammar. 
    The keys in the map represent the non-terminal states, 
    and the values represent the set of production rules associated with that state.

    The loop iterates over each entry in the map and constructs a string rule_str 
    that represents the production rules for each state. 
    The rule_str string is constructed by iterating over each rule for the current state 
    and concatenating them with the delimiter |. 
    The substr(3) function call is used to remove the first delimiter (which is unnecessary).

    Finally, the loop constructs a message string by concatenating the non-terminal state, 
    the arrow symbol ->, and the rule_str. 
    The message string is returned, which represents the entire grammar in the correct format.*/
    string display() {
        string message = "Grammar is as follows \n";
        for (auto it = dict_grammar.begin(); it != dict_grammar.end(); ++it) {
            string rule_str = "";
            auto const& state = it->first;
            auto const& rules = it->second;
            for (auto const& rule : rules) {
                rule_str += " | " + rule;
            }
            rule_str = rule_str.substr(3);
            message += state + " -> " + rule_str + "\n";
        }
        return message;
    }

};

/*These are helper function******************************/
void write_test_cases(Grammar grammar) {
    ofstream file("test_cases2.txt");
    if(file.is_open()) {
        for(int i = 0; i < grammar.terminals.size(); i++) {
            file << grammar.terminals[i] << "\n";
        }
    }
    file.close();
}

vector<string> split(string str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

string join(vector<string> strings, string delim) {
    stringstream ss;
    for (int i = 0; i < strings.size(); i++) {
        if (i > 0) {
            ss << delim;
        }
        ss << strings[i];
    }
    return ss.str();
}
/*****************************************************/

Grammar read_grammar(string filename) {
    ifstream file1(filename);
    string line;
    Grammar grammar;

    //standard library function that is used to read a string or a line from an input stream
    // the first two lines of the file are expected to contain the list of states 
    // and the list of terminals respectively, separated by commas. 
    //Therefore, these two lines are read separately using getline 
    //and then split into individual strings using the split function.
    
    getline(file1, line);
    grammar.nonterminals = split(line, ',');

    getline(file1, line);
    grammar.terminals = split(line, ',');

    grammar.set_numOfnonterm();
    grammar.set_numOfterm();

    for (int i = 0; i < grammar.num_nonterminals; i++) {
        getline(file1, line);
        string rule = line;
        for (char letter : rule) {
            if (letter == '-' || letter == '>' || letter == '|' || letter == '$') {
                continue;
            }
            else if (find(grammar.nonterminals.begin(), grammar.nonterminals.end(), string(1, letter)) == grammar.nonterminals.end() &&
                find(grammar.terminals.begin(), grammar.terminals.end(), string(1, letter)) == grammar.terminals.end()) {
                string message = "Illegal production rule: " + rule + "\n";
                message += "Invalid symbol: " + string(1, letter) + "\n";
                try{
                    throw IllegalProductionException(message);
                }
                catch (IllegalProductionException(message)){
                    cout<<message.what();
                }

            }
        }
        string lhs = rule.substr(0, rule.find("-"));
        string rhs = rule.substr(rule.find(">") + 1);
        grammar.dict_grammar[lhs] = split(rhs, '|');
    }

    return grammar;
}

void write_grammar(string filename) {
    ofstream file1(filename);
    string data1, data2, data3;

    cout << "Context Free Grammar \nEnter non-terminal symbols: ";
    getline(cin, data1);

    cout << "Enter terminal symbols: \n";
    getline(cin, data2);

    cout << "Enter production rules (empty line to finish):\n";
    vector<string> productions;
    while (getline(cin, data3) && !data3.empty()) {
        productions.push_back(data3);
    }
    data3 = join(productions, "\n");

    file1 << data1 << "\n";
    file1 << data2 << "\n";
    file1 << data3;

    file1.close();
}
/*int main() {
    write_grammar("grammar.txt");
    Grammar grammar = read_grammar("grammar.txt");
    write_test_cases(grammar);
    return 0;
}*/
