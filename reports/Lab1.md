# Intro to formal languages. Regular grammars. Finite Automata
### Course: Formal Languages & Finite Automata
### Author: **Kalamaghin Arteom (FAF-211)**


## Objectives

**1.** Understand what a language is and what it needs to have in order to be considered a formal one.

**2.** Provide the initial setup for the evolving project that we shall work on during this semester - to do the following:

        a. Create a local && remote repository of a VCS hosting service;
        b. Choose a programming language (one that supports all the main paradigms);
        c. Create a separate folder where we shall be keeping the report.

**3.** According to the variant number, get the grammar definition and do the following tasks:

        a. Implement a type/class for the grammar;
        b. Add a function that would generate 5 valid strings from the language expressed by the given grammar;
        c. Implement some functionality that would convert and object of type Grammar to one of type Finite Automaton;
        d. For the Finite Automaton, add a method that checks if an input string can be obtained via the state transition from it.


## Theoretical Notes

In **automata theory**, a **formal language** is a set of strings of symbols drawn from a finite alphabet. A formal language can be specified either by a set of rules (such as regular expressions or a context-free grammar) that generates the language, or by a formal machine that accepts (recognizes) the language. 

So the usual components of a language are:

* **The alphabet**: Set of valid characters;
* **The vocabulary**: Set of valid words;
* **The grammar**: Set of rules/constraints over the lang.

Various configurations of these components can produce languages appropriate for various use cases. So a language described in this manner will be able to generate some set of words.

_**String (or sometimes a word)** - is a finite sequence of symbols chosen from an alphabet. For example, 010101010 is a string chosen from the binary alphabet, as is the string 0000 or 1111._

**Automata theory** is the study of abstract computational devices (abstract state machine). An **automaton** is an abstract model of a digital computer. As such, every automaton includes some essential features. It has a mechanism for reading input. It will be assumed that the input is a string over a given alphabet. The input mechanism can read the input string from left to right, one symbol at a time and it can be detected the end of the string. The automaton can produce the output of some form and has a control unit, which can be in any one of a finite number of internal states, and which can change state in some defined manner based on transition functions.

A **finite-state machine** (FSM) or **finite-state automaton** (FSA, plural: automata), finite automaton, or simply a state machine, is a mathematical model of computation. It is an abstract machine that can be in exactly one of a finite number of states at any given time. This is a very useful tool in circuit design, protocol verification, patterns finding and **lexical analysis**, **natural language parsing**.

In this lab, an automaton will be used **to check words against some grammar** described in described in the mentioned above manner.

## Impelementation description

I started by creating the Grammar class, which will store the configuration of our language.

```cpp
class Grammar {
    public:
        list<string> Vn, Vt;
        list<Rule> P;

        Grammar(list<string> Vn_val, list<string> Vt_val, list<Rule> P_val) {
            Vn = Vn_val; Vt = Vt_val; P = P_val;
        };

        void printRules() {
            list<Rule>::iterator r;

            for(r = P.begin(); r != P.end(); ++r) {
                r->printRule();
            }
        }

        string generateWord();
};
```

The implementation of this class required me to introduce another class to store the rules.

```cpp
class Rule {
    private:
        string left;
        string right;

    public:
        Rule(string record) {
            left.clear(); right.clear();

            for(int i = 0; i < record.length(); i++) {
                if(record[i] == '>') {
                    left = left + record.substr(0, i-2);
                    right = right + record.substr(i+2, record.length()-i);
                }
            }
        };

        void printRule() {
            cout << left << " -> " << right << '\n';
        }

        string getLeft() { return left; };
        string getRight() { return right; };
};
```

When this class is initialized, one line is read from the **configuration file** into which the rules are written in the form familiar to humans. 

    S -> aP
    S -> bQ
    P -> bP
    ...

Then a simple parsing and recording of the relevant information in the fields of the object is carried out.

Below you can see the implementation of the method that generates some word from the set described by the language.

```cpp
string Grammar::generateWord() {
    list<Rule> possibilities;
    list<Rule>::iterator r;

    list<string>::iterator c;

    string generatedStr = "S";
    string tmpStr;

    int i, term, rn;

    while(1) {
        term = 0;

        for(i = 0; i < generatedStr.length(); i++) {
            c = find(Vn.begin(), Vn.end(), generatedStr.substr(i, 1));
            if(c != Vn.end()) { term = 1; }

            if(term) { break; }
        }

        if(term) {
            possibilities.clear();
            tmpStr.clear();

            for(r = P.begin(); r != P.end(); ++r) {
                if(!strcmp(r->getLeft().c_str(), c->c_str())) { 
                    possibilities.push_back(*r);
                }    
            }

            for(int j = 0; j < rand() % (possibilities.size() + 1); j++) {
                possibilities.pop_front();
            }

            tmpStr += generatedStr.substr(0, i);
            tmpStr += possibilities.front().getRight();
            tmpStr += generatedStr.substr(i+1, generatedStr.length()-i);

            generatedStr = tmpStr;
        } else {
            break;
        }
    }

    return generatedStr;
};
```

This is a very simple **string processing**, since we are dealing with the **Regular Grammar**. In practice, all we do is look for a _large letter_ in the string corresponding to a **non-terminal character** and replace it **using concatenation** according to a randomly chosen rule, where this non-terminal symbol is on the left side of the rule.

Next, an automaton was implemented.

```cpp
class FiniteAutomaton {
    public:
        list<string> Vn, Vt;
        string *transitions;

        FiniteAutomaton(Grammar g) {
            Vn.clear(); Vt.clear();

            list<string>::iterator s, s1, s2;
            list<Rule>::iterator r;

            for(s = g.Vn.begin(); s != g.Vn.end(); ++s) { Vn.push_back(*s); }
            for(s = g.Vt.begin(); s != g.Vt.end(); ++s) { Vt.push_back(*s); }

            string parseSpace;
            list<string> tokens;

            int i, j;
            int check;

            transitions = new string[Vn.size()*Vt.size()];

            for(i = 0; i < Vt.size(); i++) {
                for(j = 0; j < Vn.size(); j++) {
                    *(transitions+i*Vn.size()+j) = "";
                }
            }

            for(r = g.P.begin(); r != g.P.end(); ++r) {
                tokens.clear();
                tokens.push_back(r->getLeft());

                parseSpace = r->getRight();
                check = 0;

                for(i = 0; i < parseSpace.length(); i++) {
                    s1 = find(Vn.begin(), Vn.end(), parseSpace.substr(i, 1));

                    if(s1 != Vn.end()) {
                        if(i == 0) {
                            tokens.push_back(parseSpace.substr(i+1, parseSpace.length()-1));    
                        } else {
                            tokens.push_back(parseSpace.substr(0, i));
                        }

                        tokens.push_back(parseSpace.substr(i, 1));

                        check = 1;
                    }
                }

                if(!check) {
                    tokens.push_back(parseSpace);
                    tokens.push_back("+");
                }

                s1 = find(Vn.begin(), Vn.end(), tokens.front());
                tokens.pop_front();

                s2 = find(Vt.begin(), Vt.end(), tokens.front());
                tokens.pop_front();

                i = distance(Vn.begin(), s1); j = distance(Vt.begin(), s2);

                *(transitions+i*Vt.size()+j) = tokens.front();
            }

            for(i = 0; i < Vn.size(); i++) {
                for(j = 0; j < Vt.size(); j++) {
                    if((transitions+i*Vt.size()+j)->length() == 0) {
                        *(transitions+i*Vt.size()+j) = '-';
                    }
                }
            }
        };

        void displayConfiguration();
        int checkWord(string);
        void deallocateMemory();
};
```

It start from **transcribing the rules in some sort of a graph represented by a 2D array** - transitions between the states.

```cpp
int FiniteAutomaton::checkWord(string word) {
    string currentState = "S";
    list<string>::iterator s1, s2;
    int i, j;

    for(int k = 0; k < word.length(); k++) {
        s1 = find(Vn.begin(), Vn.end(), currentState);
        s2 = find(Vt.begin(), Vt.end(), word.substr(k, 1));

        if(s2 != Vt.end()) {
            i = distance(Vn.begin(), s1); j = distance(Vt.begin(), s2);
            currentState = *(transitions+i*Vt.size()+j);
        } else {
            return 0;
        }
    }

    if(currentState == "+") {
        return 1;
    } else {
        return 0;
    }
};
```

When checking a word, the automaton iterates through the characters and changes its state according to the map obtained from the rules. If it does end in the final state (indicated as '+' for the program) - the word matches the grammar, does not end - does not matches.

## Results and conclusions

Here are some results for a particular set of rules:
```
RULESET: 
S -> aP
S -> bQ
P -> bP
P -> cP
P -> dQ
P -> e
Q -> eQ
Q -> fQ
Q -> a

GENERATED WORDS: 
bffffa
ba
bfefa
bfeea
bffffeffa

AUTOMATA CONFIGURATION: 
    a b c d e f 
-----------------
S | P Q - - - - 
P | - P P Q + - 
Q | + - - - Q Q 

SYNTAX CHECKS: 
WORD - bffffffa | ANSWER: 1
WORD - blfffffa | ANSWER: 0
```

Regular grammar and final state machines are indeed powerful tools for information conveying and lexical analysis. During this lab, I was able to both gain a stronger grasp on these concepts in particular, and formal languages in general, and develop my technical skills.

## References

1. _Programming Language Syntax_ - Michael L. Scott, in Programming Language Pragmatics (Third Edition), 2009;
2. https://en.wikipedia.org/wiki/Finite-state_machine;
3. _Formal Languages and Finite Automata_ [Guide for practical lessons] - UTM