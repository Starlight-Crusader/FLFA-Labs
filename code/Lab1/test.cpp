#include <iostream>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include <list>
#include <iterator>
#include <bits/stdc++.h>
#include <fstream>
#include <unistd.h>

#include "grammar.h"
#include "finiteAutomaton.h"

using namespace std;


int main() {
    srand(time(0));
    system("clear");
    
    list<string> Vn = {"S", "P", "Q"};
    list<string> Vt = {"a", "b", "c", "d", "e", "f"};
    list<Rule> P;

    ifstream rules("rules.txt");
    string line;

    string genWord;
    list<string> genWords;
    list<string>::iterator w;

    while(!rules.eof()) {
        getline(rules, line);
        P.push_back(Rule(line));
    }

    Grammar gramm(Vn, Vt, P);

    cout << "RULESET: " << '\n';
    gramm.printRules();

    for(int i = 0; i < 5; i++) {
        genWord = gramm.generateWord();

        w = find(genWords.begin(), genWords.end(), genWord);
        if(w == genWords.end()) { 
            genWords.push_back(genWord); 
        } else {
            i--;
        }
    }

    cout << '\n' << "GENERATED WORDS: " << '\n';

    for(w = genWords.begin(); w != genWords.end(); ++w) {
        cout << *w << '\n';
    }

    

    FiniteAutomaton fa(gramm);

    cout << '\n' << "AUTOMATA CONFIGURATION: " << '\n';
    fa.displayConfiguration();


    cout << '\n' << "SYNTAX CHECKS: " << '\n';
    cout << "WORD - bffffffa | ANSWER: ";
    cout << fa.checkWord("bffffffa") << '\n';

    cout << "WORD - blfffffa | ANSWER: ";
    cout << fa.checkWord("blfffffa") << '\n';

    // fa.deallocateMemory();
    return 0;
};
