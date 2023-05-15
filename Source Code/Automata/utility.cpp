#include "utility.h"
#include <QDebug>
#define EPSILON "#"
#define DEAD "$"

#define endl '\n'


bool find(vector<vector<string>> s1, vector<string> s2)
{
    string a;
    for (auto i : s2)
        a += i;
    sort(a.begin(), a.end());

    for (auto i : s1)
    {
        string b;
        for (auto j : i)
        {
            b += j;
        }
        sort(b.begin(), b.end());
        if (a == b)
            return true;
    }
    return false;
}

void unique(vector<string> &s)
{
    set<string> distinct(s.begin(), s.end());
    s.assign(distinct.begin(), distinct.end());
}

void unique2D(vector<vector<string>> &s)
{
    set<vector<string>> distinct(s.begin(), s.end());
    s.assign(distinct.begin(), distinct.end());
}

void setAcceptingStates(FA nfa, FA &dfa)
{
    vector<vector<string>> accepted;
    accepted.assign(nfa.accept.begin(), nfa.accept.end());
    for (auto &i : dfa.states)
    {
        for (auto j : i)
        {
            for (auto k : accepted)
            {
                for (auto m : k)
                {
                    if (j.find(m) != std::string::npos)
                    {
                        dfa.accept.push_back(i);
                        break;
                    }
                }
            }
        }
    }
}

void printDFA(FA dfa, bool isNFA)
{

    // print Start State
    if (isNFA)
        qDebug() << "Start: " << dfa.start << endl;
    else
    {
        qDebug() << "Start: ";
        for (auto s : dfa.epsilonStart)
            qDebug() << s << " ";
        qDebug() << endl;
    }

    // print accepted states
    qDebug() << "Accepted States: ";
    for (auto i : dfa.accept)
    {
        qDebug() << "[";
        for (auto j : i)
            qDebug() << j << ",";
        qDebug() << "\b], ";
    }
    // print input symbols
    qDebug() << "\nLang: ";
    for (int i = 0; i < dfa.lang.size(); i++)
        qDebug() << dfa.lang[i] << " ";
    qDebug() << endl;

    // print states
    qDebug() << "States: ";
    for (auto i : dfa.states)
    {
        qDebug() << "[";
        for (auto j : i)
            qDebug() << j << ",";
        qDebug() << "\b], ";
    }
    qDebug() << "\b\b" << endl;

    // print transition table
    qDebug() << "Transition table:" << endl;
    for (auto pair : dfa.transition_table)
    {
        qDebug() << "[";
        for (auto src : pair.first.first)
            qDebug() << src << ", ";
        qDebug() << "], ";
        qDebug() << pair.first.second
             << " -> "
             << "[";
        for (auto dest : pair.second)
            qDebug() << dest << ", ";
        qDebug() << "]" << endl;
    }
    // print epsilon closure
    if (!isNFA)
    {
        qDebug() << "Epsilon Closure:" << endl;
        for (auto pair : dfa.epsilonClosure)
        {
            qDebug() << pair.first
                 << " -> ";
            for (auto val : pair.second)
                qDebug() << val
                     << " ";
            qDebug() << endl;
        }
    }
}

FA convertNFAToDFA(FA nfa)
{
    FA dfa;
    dfa.start.assign(nfa.start.begin(), nfa.start.end());
    dfa.lang.assign(nfa.lang.begin(), nfa.lang.end());

    vector<string> start{nfa.start};
    dfa.states.push_back(start);

    queue<vector<string>> newStates;
    newStates.push(start);
    while (!newStates.empty())
    {
        vector<string> curState;
        for (auto i : newStates.front())
            curState.push_back(i);
        int stateLen = curState.size();
        int langLen = nfa.lang.size();
        vector<string> newState;
        for (int i = 0; i < langLen; ++i)
        {

            newState.clear();
            for (int j = 0; j < stateLen; ++j)
            {
                vector<string> state{curState[j]};
                if (nfa.transition_table.find({state, nfa.lang[i]}) != nfa.transition_table.end())
                {
                    for (auto i : nfa.transition_table[{state, nfa.lang[i]}])
                        newState.push_back(i);
                }
            }

            if (newState.empty())
                newState.push_back(DEAD);

            unique(newState);
            dfa.transition_table[{curState, nfa.lang[i]}] = newState;
            bool isFound = find(dfa.states, newState);
            if (!isFound)
            {
                newStates.push(newState);
                dfa.states.push_back(newState);
            }
        }
        newStates.pop();
    }
    setAcceptingStates(nfa, dfa);

    // Dummy state for initial node
    vector<string> emptyFrom;
    emptyFrom.push_back("&");
    string emptyOn = "&";
    dfa.transition_table[{{emptyFrom},emptyOn}].push_back(dfa.start);
    dfa.states.push_back(emptyFrom);
    return dfa;
}

void buildEpsilonClosure(FA &epsilonNFA)
{
    for (auto states : epsilonNFA.states)
    {
        string s;
        s += states[0];
        if (epsilonNFA.transition_table.find({states, EPSILON}) == epsilonNFA.transition_table.end())
        {
            epsilonNFA.epsilonClosure[s].push_back(s);
            continue;
        }

        queue<vector<string>> epsilonClosure;
        epsilonClosure.push(states);
        vector<string> newTransitions;
        for (auto s : states)
            newTransitions.push_back(s);
        while (!epsilonClosure.empty())
        {
            for (auto st : epsilonClosure.front())
            {
                vector<string> cl;
                cl.push_back(st);
                if (epsilonNFA.transition_table.find({cl, EPSILON}) != epsilonNFA.transition_table.end())
                {
                    epsilonClosure.push(epsilonNFA.transition_table[{cl, EPSILON}]);
                    for (auto s : epsilonNFA.transition_table[{cl, EPSILON}])
                        newTransitions.push_back(s);
                }
            }

            epsilonClosure.pop();
        }

        unique(newTransitions);
        epsilonNFA.epsilonClosure[s].assign(newTransitions.begin(),newTransitions.end());
    }
}

FA convertEpsilonNFAToDFA(FA epsilonNFA)
{
    FA dfa;
    dfa.lang.assign(epsilonNFA.lang.begin(), epsilonNFA.lang.end());

    buildEpsilonClosure(epsilonNFA);
    dfa.epsilonClosure = epsilonNFA.epsilonClosure;

    vector<string> start{epsilonNFA.epsilonClosure[epsilonNFA.start]};
    dfa.epsilonStart.assign(start.begin(), start.end());
    dfa.states.push_back(start);

    queue<vector<string>> newStates;
    newStates.push(start);

    while (!newStates.empty())
    {
        vector<string> curState;
        for (auto i : newStates.front())
            curState.push_back(i);
        int stateLen = curState.size();
        int langLen = epsilonNFA.lang.size();
        vector<string> newState;
        for (int i = 0; i < langLen; ++i)
        {
            newState.clear();
            for (int j = 0; j < stateLen; ++j)
            {
                vector<string> state{curState[j]};
                if (epsilonNFA.transition_table.find({state, epsilonNFA.lang[i]}) != epsilonNFA.transition_table.end())
                {
                    for (auto it : epsilonNFA.transition_table[{state, epsilonNFA.lang[i]}])
                        newState.push_back(it);
                    queue<string> epsilonClosure;
                    for (auto it : newState)
                        epsilonClosure.push(it);
                    while (!epsilonClosure.empty())
                    {
                        for(auto k: dfa.epsilonClosure[epsilonClosure.front()])
                            newState.push_back(k);
                        epsilonClosure.pop();
                    }
                }
            }

            if (newState.empty())
                newState.push_back(DEAD);

            unique(newState);
            dfa.transition_table[{curState, epsilonNFA.lang[i]}] = newState;
            bool isFound = find(dfa.states, newState);
            if (!isFound)
            {
                newStates.push(newState);
                dfa.states.push_back(newState);
            }
        }
        newStates.pop();
    }
    setAcceptingStates(epsilonNFA, dfa);
    // Dummy state for initial node
    vector<string> emptyFrom;
    emptyFrom.push_back("&");
    string emptyOn = "&";
    dfa.transition_table[{{emptyFrom},emptyOn}].push_back(dfa.start);
    dfa.states.push_back(emptyFrom);


    return dfa;
}
