#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> productions;
map<char, set<char>> FIRST, FOLLOW;
set<char> nonTerminals, terminals;
char startSymbol;

// Compute FIRST set
set<char> computeFirst(char symbol) {
    if (FIRST.find(symbol) != FIRST.end()) return FIRST[symbol];

    set<char> firstSet;
    if (!isupper(symbol)) {
        firstSet.insert(symbol);
        return firstSet;
    }

    for (string prod : productions[symbol]) {
        if (prod == "@") {
            firstSet.insert('@');
        } else {
            for (char ch : prod) {
                set<char> temp = computeFirst(ch);
                firstSet.insert(temp.begin(), temp.end());
                if (temp.find('@') == temp.end()) break;
                else firstSet.erase('@');
            }
        }
    }
    FIRST[symbol] = firstSet;
    return firstSet;
}

// Compute FOLLOW set
void computeFollow(char symbol) {
    if (FOLLOW.find(symbol) != FOLLOW.end()) return;

    if (symbol == startSymbol)
        FOLLOW[symbol].insert('$');

    for (auto &p : productions) {
        char lhs = p.first;
        for (string rhs : p.second) {
            for (int i = 0; i < rhs.size(); i++) {
                if (rhs[i] == symbol) {
                    if (i + 1 < rhs.size()) {
                        set<char> firstNext = computeFirst(rhs[i + 1]);
                        if (firstNext.find('@') != firstNext.end()) {
                            firstNext.erase('@');
                            FOLLOW[symbol].insert(firstNext.begin(), firstNext.end());
                            if (lhs != symbol) {
                                computeFollow(lhs);
                                FOLLOW[symbol].insert(FOLLOW[lhs].begin(), FOLLOW[lhs].end());
                            }
                        } else {
                            FOLLOW[symbol].insert(firstNext.begin(), firstNext.end());
                        }
                    } else {
                        if (lhs != symbol) {
                            computeFollow(lhs);
                            FOLLOW[symbol].insert(FOLLOW[lhs].begin(), FOLLOW[lhs].end());
                        }
                    }
                }
            }
        }
    }
}

// Check LL(1) condition
bool isLL1() {
    for (char nt : nonTerminals) {
        vector<set<char>> prodFirsts;
        for (string rhs : productions[nt]) {
            set<char> s;
            if (rhs == "@") s.insert('@');
            else {
                for (char ch : rhs) {
                    set<char> temp = computeFirst(ch);
                    s.insert(temp.begin(), temp.end());
                    if (temp.find('@') == temp.end()) break;
                    else s.erase('@');
                }
            }
            prodFirsts.push_back(s);
        }

        // Check pairwise disjointness
        for (int i = 0; i < prodFirsts.size(); i++) {
            for (int j = i + 1; j < prodFirsts.size(); j++) {
                set<char> intersection;
                for (char c : prodFirsts[i])
                    if (prodFirsts[j].count(c)) intersection.insert(c);
                if (!intersection.empty()) return false; // Not disjoint
            }
        }

        // If epsilon in FIRST, check intersection with FOLLOW
        for (int i = 0; i < prodFirsts.size(); i++) {
            if (prodFirsts[i].count('@')) {
                set<char> intersection;
                for (char c : FOLLOW[nt])
                    if (prodFirsts[i].count(c)) intersection.insert(c);
                if (!intersection.empty()) return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    cout << "Number of productions: ";
    cin >> n;
    cin.ignore();

    cout << "Enter productions:\n";
    for (int i = 0; i < n; i++) {
        string prod;
        getline(cin, prod);
        char lhs = prod[0];
        if (i == 0) startSymbol = lhs;
        nonTerminals.insert(lhs);

        string rhs = prod.substr(2);
        stringstream ss(rhs);
        string token;
        vector<string> alternatives;

        string current;
        for (char c : rhs) {
            if (c == '|') {
                alternatives.push_back(current);
                current.clear();
            } else current += c;
        }
        if (!current.empty()) alternatives.push_back(current);

        for (string alt : alternatives) {
            productions[lhs].push_back(alt);
            for (char ch : alt)
                if (!isupper(ch) && ch != '@')
                    terminals.insert(ch);
        }
    }

    // Compute FIRST and FOLLOW sets
    for (char nt : nonTerminals) computeFirst(nt);
    for (char nt : nonTerminals) computeFollow(nt);

    // Optional: Display FIRST and FOLLOW
    cout << "\nFIRST sets:\n";
    for (char nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (char c : FIRST[nt]) cout << c << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (char nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (char c : FOLLOW[nt]) cout << c << " ";
        cout << "}\n";
    }

    // Check LL(1)
    if (isLL1())
        cout << "\nGrammar is LL(1)\n";
    else
        cout << "\nGrammar is NOT LL(1)\n";

    return 0;
}
