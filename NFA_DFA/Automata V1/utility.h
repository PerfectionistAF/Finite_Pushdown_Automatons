#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <set>


using namespace std;


struct FA
{
    string start;
    vector<string> epsilonStart;                                       // start state
    vector<vector<string>> accept;                      // set of accepting states
    vector<string> lang;                                // set of input symbols
    vector<vector<string>> states;                      // set of states
    map<pair<vector<string>, string>, vector<string>> transition_table; // transition function; mapping state x lang => state
    map<string, vector<string>> epsilonClosure;                 // only used if FA is an epsilon-NFA
};

void printDFA(FA, bool);
FA convertNFAToDFA(FA);
FA convertEpsilonNFAToDFA(FA);

#endif // UTILITY_H_INCLUDED
