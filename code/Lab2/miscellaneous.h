using namespace std;


class Miscellaneous {
    public:
        static string readNextToken(string);
        static void printList(list<string>);
        static string normalizeComposite(string);
};

string Miscellaneous::readNextToken(string part) {
    for(int i = 0; i < part.length(); i++) {
        if(!((part[i] >= 'a' && part[i] <= 'z') || (part[i] >= '0' && part[i] <= '9'))) {
            return part.substr(0, i);
        }
    }

    return "?!";
};

void Miscellaneous::printList(list<string> l) {
    list<string>::iterator s;

    cout << "{ ";
    for(s = l.begin(); s != l.end(); ++s) {
        cout << *s << ", ";
    }
    
    cout << "EOL }" << '\n';
};

string Miscellaneous::normalizeComposite(string comp_state) {
    list<string> states; states.clear();
    string sorted;
    string state;

    int start;
    comp_state += '<';

    for(int i = 0; i < comp_state.length(); i++) {
        if(i == 0 || comp_state[i] == '|') {
            if(i == 0) { start = 0; } 
            else { start = 1; }

            state = Miscellaneous::readNextToken(comp_state.substr(i+start, comp_state.length()-i));

            if(find(states.begin(), states.end(), state) == states.end()) {
                states.push_back(state);
            }
        }
    }

    states.sort();

    sorted += states.front(); states.pop_front();
    while(states.size() > 0) {
        sorted += '|'; sorted += states.front(); states.pop_front();
    }
            
    return sorted;
};
