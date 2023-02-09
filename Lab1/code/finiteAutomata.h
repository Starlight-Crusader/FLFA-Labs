class FiniteAutomata {
    private:
        list<string> terminalStates;

        list<string> transitionMapSource;
        list<string> transitionMapFlag;
        list<string> transitionMapTarget;

    public:
        FiniteAutomata(Grammar g) {
            transitionMapSource.clear();
            transitionMapFlag.clear();
            transitionMapTarget.clear();

            list<Rule>::iterator r;
            list<string>::iterator s1, s2, s3;
            string parseSpace;
            string tempStr;

            int check;
            int c;

            for(r = g.P.begin(); r != g.P.end(); ++r) {
                parseSpace = r->getLeft() + " -> " + r->getRight();

                for(int i = 0; i < parseSpace.length(); i++) {
                    if(parseSpace[i] == '>') {
                        transitionMapSource.push_back(parseSpace.substr(0, i-2));
                        parseSpace = parseSpace.substr(i+2, parseSpace.length());

                        break;
                    } else {
                        continue;
                    }
                }

                check = 0;

                for(int i  = 0; i < parseSpace.length(); i++) {
                    s1 = find(g.Vn.begin(), g.Vn.end(), parseSpace.substr(i, 1));

                    if(s1 != g.Vn.end()) {
                        transitionMapTarget.push_back(parseSpace.substr(i, 1));
                        transitionMapFlag.push_back(parseSpace.substr(0, i));

                        check = 1;
                    }
                }

                if(!check) {
                    tempStr = "-";
                    transitionMapTarget.push_back(tempStr);
                    transitionMapFlag.push_back(parseSpace);
                }
            }

            for(int i = 0; i < transitionMapSource.size(); i++) {
                s1 = transitionMapSource.begin();
                s2 = transitionMapTarget.begin();

                std::advance(s1, i); std::advance(s2, i);

                if(*s2 == "-") {
                    s3 = find(terminalStates.begin(), terminalStates.end(), *s1);

                    if(s3 == terminalStates.end()) {
                        terminalStates.push_back(*s1);
                    } else {
                        continue;
                    }
                }        
            }
        };

        void displayConfiguration();
        int checkWord(string);
};

void FiniteAutomata::displayConfiguration() {
    list<string>::iterator s1, s2, s3;

    for(int i = 0; i < transitionMapSource.size(); i++) {
        s1 = transitionMapSource.begin();
        s2 = transitionMapFlag.begin();
        s3 = transitionMapTarget.begin();

        std::advance(s1, i); std::advance(s2, i); std::advance(s3, i);

        cout << "delta(" << *s1 << ", " << *s2 << ") = " << *s3 << '\n';
    }

    cout << '\n' << "TERMINAL STATES: ";
    for(s1 = terminalStates.begin(); s1 != terminalStates.end(); ++s1) {
        cout << *s1 << ' ';
    }

    cout << '\n';
};

int FiniteAutomata::checkWord(string word) {
    string currentState = "S";
    list<string>::iterator s1, s2, s3;

    int tm;

    for(int i = 0; i < word.length(); i++) {
        tm = 0;

        for(int j = 0; j < transitionMapSource.size(); j++) {
            s1 = transitionMapSource.begin();
            s2 = transitionMapFlag.begin();
            s3 = transitionMapTarget.begin();

            std::advance(s1, j); std::advance(s2, j); std::advance(s3, j);
        
            if(*s1 == currentState && *s2 == word.substr(i, 1)) {
                if(*s3 != "-") {
                    currentState = *s3;
                }

                tm = 1;
                break;
            }
        }

        if(!tm) {
            return -1;
        }
    }

    s1 = find(terminalStates.begin(), terminalStates.end(), currentState);

    if(s1 != terminalStates.end()) {
        return 1;
    } else {
        return 0;
    }
};
