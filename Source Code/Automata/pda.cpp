#include "pda.h"
#include "graph.h"
#include <QDebug>

#define EPSILON "#"
#define DOLLAR "$"
#define endl '\n'

void uniques(vector<string> &str)
{
    set<string> distinct(str.begin(), str.end());
    str.assign(distinct.begin(), distinct.end());
}

bool isNonTerminal(string symbol, PDA pda)
{
    vector<string>::iterator it;
    it = find(pda.nonTerminals.begin(), pda.nonTerminals.end(), symbol);
    return it != pda.nonTerminals.end();
}

void pushMandatoryStates(PDA &pda)
{

    pda.transitionTable.insert({{{"q0"}, {EPSILON, EPSILON, DOLLAR}}, {"q1"}});
    pda.transitionTable.insert({{{"q1"}, {EPSILON, EPSILON, pda.start}}, {"qloop"}});
    pda.transitionTable.insert({{{"qloop"}, {EPSILON, DOLLAR, EPSILON}}, {"qAccept"}});
    pda.states.push_back("q0");
    pda.states.push_back("q1");
    pda.states.push_back("qloop");
    pda.states.push_back("qAccept");
}

void convertCFGToPDA(PDA &pda)
{
    pushMandatoryStates(pda);

    // Handling terminals
    for (auto terminal : pda.terminals)
    {
        vector<string> trans = {terminal, terminal, EPSILON};
        pda.transitionTable[{{"qloop"}, trans}].push_back({"qloop"});
    }

    int stateNum = 2;

    // Handling non-terminals
    for (auto nonTerminal : pda.nonTerminals)
    {
        string prevState = "qloop";
        string curState = "q" + to_string(stateNum++);
        vector<string> trans = {EPSILON,nonTerminal,EPSILON};
        pda.transitionTable[{{prevState},trans}].push_back(curState);
        for (auto production : pda.productionRules[nonTerminal])
        {
            string innerPrevState = curState;
            string innerCurState = "q" + to_string(stateNum++);
            string reversedRule = string(production.rbegin(), production.rend());
            int len = reversedRule.size();
            for (int i = 0; i < len - 1; i++)
            {
                if(i==0) pda.states.push_back(curState);
                string symbol;
                symbol += reversedRule[i];
                vector<string> trans = {EPSILON, EPSILON, symbol};
                pda.transitionTable[{{innerPrevState},trans}].push_back(innerCurState);
                innerPrevState = innerCurState;
                pda.states.push_back(innerCurState);
                innerCurState = "q" + to_string(stateNum++);

                if(i == len - 2) stateNum--;
            }
            string symbol;
            symbol += reversedRule[len - 1];
            vector<string> trans = {EPSILON, EPSILON, symbol};
            pda.transitionTable[{{innerPrevState},trans}].push_back({"qloop"});
        }
    }

    uniques(pda.states);

}

void printPDA(PDA pda)
{
    for (auto pair : pda.transitionTable)
    {
        for(auto s: pair.first.first)
            qDebug() << s;
        qDebug() << ", {"
             << pair.first.second[0]
             << ", "
             << pair.first.second[1]
             << ", "
             << pair.first.second[2]
             << "} -> "
             << "[";
        for(auto state: pair.second)
            qDebug() << state << ",";
        qDebug() << "]";
        qDebug() << endl;
    }
    qDebug() << "STATES" << endl;
    for(auto state: pda.states)
        qDebug() << state << " ";


    qDebug() << "Production Rules" << endl;
    for(auto rule: pda.productionRules)
    {
        qDebug() << rule.first << " ->";
        for(auto production: rule.second)
            qDebug() << production << " ";
    }

}

