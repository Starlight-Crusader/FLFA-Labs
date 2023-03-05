using namespace std;


class Transition {
    public:
        string source, character, target;

        Transition() { };

        Transition(string fun) {
            for(int i = 0; i < fun.length(); i++) {
                if(fun[i] == '(') {
                    source = Miscellaneous::readNextToken(fun.substr(i+1, fun.length()-i));
                } else if((fun[i] == ',') && (i != fun.length()-1)) {
                    character = Miscellaneous::readNextToken(fun.substr(i+1, fun.length()-i));
                } else if(fun[i] == '=') {
                    target = Miscellaneous::readNextToken(fun.substr(i+2, fun.length()-i-1));
                }
            }
        };
};


class Automaton {
    public:
        string *graph;
        list<string> Q, E, F;
        list<Transition> G;

        Automaton() { };
        
        Automaton(string source_name) {
            ifstream language(source_name);
            string line;

            getline(language, line);
            for(int i = 0; i < line.length()-1; i++) {
                if((line[i] == '{') || (line[i] == ',')) {
                    Q.push_back(Miscellaneous::readNextToken(line.substr(i+1, line.length()-i)));
                }
            }

            getline(language, line);
            for(int i = 0; i < line.length()-1; i++) {
                if((line[i] == '{') || (line[i] == ',')) {
                    E.push_back(Miscellaneous::readNextToken(line.substr(i+1, line.length()-i)));
                }
            }

            getline(language, line);
            for(int i = 0; i < line.length()-1; i++) {
                if((line[i] == '{') || (line[i] == ',')) {
                    F.push_back(Miscellaneous::readNextToken(line.substr(i+1, line.length()-i)));
                }
            }

            graph = new string[Q.size()*E.size()];

            while(!language.eof()) {
                getline(language, line);
                G.push_back(Transition(line));
            }

            list<Transition>::iterator t;
            list<string>::iterator q, e;
            int i1, i2;
            string target_state;

            for(q = Q.begin(); q != Q.end(); ++q) {
                for(e = E.begin(); e != E.end(); ++e) {
                    target_state.clear();

                    for(t = G.begin(); t != G.end(); ++t) {
                        if(t->source == *q && t->character == *e) {
                            if(target_state.length() > 0) {
                                target_state += '|';
                            }

                            target_state += t->target;
                        }
                    }

                    i1 = distance(Q.begin(), q);
                    i2 = distance(E.begin(), e);
                    
                    *(graph+i1*E.size()+i2) = target_state;
                }
            }

            for(int i = 0; i < Q.size(); i++) {
                for(int j = 0; j < E.size(); j++) {
                    if((graph+i*E.size()+j)->length() == 0) {
                        *(graph+i*E.size()+j) = '-';
                    } else {
                        *(graph+i*E.size()+j) = Miscellaneous::normalizeComposite(*(graph+i*E.size()+j));
                    }
                }
            }
        };

        void displayConfig();
};

void Automaton::displayConfig() {
    list<string>::iterator state, character;
    int i1, i2;

    cout << "Q = ";
    Miscellaneous::printList(Q);
    cout << "E = ";
    Miscellaneous::printList(E);
    cout << "F = ";
    Miscellaneous::printList(F);

    for(state = Q.begin(); state != Q.end(); ++state) {
        for(character = E.begin(); character != E.end(); ++character) {
            i1 = distance(Q.begin(), state); i2 = distance(E.begin(), character);

            if((graph+i1*E.size()+i2)->length() > 1) {
                cout << "d(" << *state << ',' << *character << ") = " << *(graph+i1*E.size()+i2) << '\n';
            }
        }
    }
};
