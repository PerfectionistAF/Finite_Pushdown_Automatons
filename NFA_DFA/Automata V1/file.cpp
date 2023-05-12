#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main() {
    set<string> s1;
    s1.insert("ab");
    s1.insert("ba");
    s1.insert("aabbaa");
    s1.insert("aaaabb");
    s1.insert("a");
    s1.insert("b");
    s1.insert("c");

    set<string> s2;
    s2.insert("a");
    s2.insert("b");
    s2.insert("c");


    set<string>::iterator itr;
    itr = std::find(s1.begin(), s1.end(), "d");
    if(itr != s1.end()) cout << "found";
    else cout << "not found";
}
