using namespace std;


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

string Grammar::generateWord() {
    // unsigned int second = 1000000;

    list<Rule> possibilities;
    list<Rule>::iterator r;

    list<string>::iterator c;

    string generatedStr = "S";
    string tmpStr;

    int i, term;

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

            for(int j = 0; j < rand() % possibilities.size() + 1; j++) {
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
