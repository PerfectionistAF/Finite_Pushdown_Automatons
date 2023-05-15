
#ifndef PDA_H
#define PDA_H

#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>


using namespace std;

struct PDA
{
    string start;
    vector<string> states;
    vector<string> terminals;
    vector<string> nonTerminals;
    map<string, vector<string>> productionRules;
    map<pair<vector<string>, vector<string>>, vector<string>> transitionTable;
};

void convertCFGToPDA(PDA&);
void printPDA(PDA);

#endif // PDA_H
