#include <iostream>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include <list>
#include <iterator>
#include <bits/stdc++.h>
#include <fstream>
#include <unistd.h>

#include "miscellaneous.h"
#include "automaton.h"
#include "converter.h"

using namespace std;


int main() {
    string source = "language.txt";
    /*
    Automaton nfa(source);
    cout << "NFA:" << '\n';
    nfa.displayConfig();
    cout << '\n';

    Automaton dfa;
    dfa = Converter::nfaTOdfa(nfa);
    cout << "DFA:" << '\n';
    dfa.displayConfig();
    cout <<'\n';
    */

    cout << "THE NFA TO RG ANS : " << '\n';
    Converter::autToRG(source);

    return 0;
};