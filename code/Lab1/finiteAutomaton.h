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

void FiniteAutomaton::displayConfiguration() {
    list<string>::iterator s1, s2;

    cout << "    ";
    for(s1 = Vt.begin(); s1 != Vt.end(); ++s1) {
        cout << *s1 << ' ';
    }

    cout << '\n' << "---";
    for(int i = 0; i < Vt.size()+1; i++) {
        cout << "--";
    }

    for(int i = 0; i < Vn.size(); i++) {
        s2 = Vn.begin(); advance(s2, i);
        cout << '\n' << *s2 << " | ";

        for(int j = 0; j < Vt.size(); j++) {
            cout << *(transitions+i*Vt.size()+j) << ' ';
        }
    }

    cout << '\n';
};

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

void FiniteAutomaton::deallocateMemory() {
    delete transitions;
};
