using namespace std;


class Classifier {
    private:
        static bool type1Test(string, string);
        static bool type2Test(string);
        static bool type3Test(string, int*);

    public:
        int classify(string);
};

bool Classifier::type1Test(string left, string right) {
    if(left.length() <= right.length()) {
        return true;
    } else {
        return false;
    }
};

bool Classifier::type2Test(string left) {
    if(left.length() == 1) {
        return true;
    } else {
        return false;
    }
};

bool Classifier::type3Test(string right, int* al) {
    int numOfCaps = 0;

    for(int i = 0; i < right.length(); i++) {
        if(right[i] >= 'A' && right[i] <= 'Z') { numOfCaps++; } 
    }

    if(numOfCaps == 0) {
        return true;
    } else if(numOfCaps > 1) {
        return false;
    }

    if(right[0] >= 'A' && right[0] <= 'Z') {
        if(*al == 1) {
            return false;
        } else {
            *al = -1;
            return true;
        }
    } else if(right[right.length()-1] >= 'A' && right[right.length()-1] <= 'Z') {
        if(*al == -1) {
            return false;
        } else {
            *al = 1;
            return true;
        }
    } else {
        return false;
    }
};

int Classifier::classify(string source_name) {
    ifstream rules(source_name);
    string line;

    list<string> ruleset;
    list<string>::iterator rule_it;
    string rule, left_part, right_part;

    while(!rules.eof()) {
        getline(rules, line);
        ruleset.push_back(line);
    }

    int* res = (int*)malloc(ruleset.size()*sizeof(int));
    for(int i = 0; i < ruleset.size(); i++) { *(res+i) = 0; }

    int alignment = 0;

    int type = 999;

    for(rule_it = ruleset.begin(); rule_it != ruleset.end(); ++rule_it) {
        rule = *rule_it;
        
        for(int i = 0; i < rule.length(); i++) {
            if(rule[i] == '>') {
                left_part = rule.substr(0, i-2);
                right_part = rule.substr(i+2, rule.length()-i-2);

                break;
            }
        }

        if(Classifier::type1Test(left_part, right_part)) {
            *(res+distance(ruleset.begin(), rule_it)) = 1;
        } else {
            continue;
        }

        if(Classifier::type2Test(left_part)) {
            *(res+distance(ruleset.begin(), rule_it)) = 2;
        } else {
            continue;
        }

        if(Classifier::type3Test(right_part, &alignment)) {
            *(res+distance(ruleset.begin(), rule_it)) = 3;
        }
    }

    for(int i = 0; i < ruleset.size(); i++) {
        if(*(res+i) < type) {
            type = *(res+i);
        }
    }

    delete res;

    return type;
};
