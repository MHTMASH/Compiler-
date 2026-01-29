#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> productions;
map<char, set<char>> FIRST, FOLLOW;
set<char> nonTerminals, terminals;
char startSymbol;

// Function to get FIRST set of a symbol
set<char> computeFirst(char symbol) {
    if (FIRST.find(symbol) != FIRST.end())
        return FIRST[symbol];

    set<char> firstSet;
    if (!isupper(symbol)) { // Terminal
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
                if (temp.find('@') == temp.end())
                    break;
                else
                    firstSet.erase('@');
            }
        }
    }
    FIRST[symbol] = firstSet;
    return firstSet;
}

// Function to compute FOLLOW sets
void computeFollow(char symbol) {
    if (FOLLOW.find(symbol) != FOLLOW.end())
        return;

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
                            if (lhs != symbol)
                                computeFollow(lhs);
                            FOLLOW[symbol].insert(FOLLOW[lhs].begin(), FOLLOW[lhs].end());
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
        string rhs = prod.substr(2); // Skip '='
        stringstream ss(rhs);
        string token;
        vector<string> alternatives;

        // Split alternatives by '|'
        string current;
        for (char c : rhs) {
            if (c == '|') {
                alternatives.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        if (!current.empty())
            alternatives.push_back(current);

        for (string alt : alternatives) {
            productions[lhs].push_back(alt);
            for (char c : alt)
                if (!isupper(c) && c != '@')
                    terminals.insert(c);
        }
    }

    // Compute FIRST sets
    for (char nt : nonTerminals)
        computeFirst(nt);

    // Compute FOLLOW sets
    for (char nt : nonTerminals)
        computeFollow(nt);

    // Display FIRST sets
    cout << "\nFIRST sets:\n";
    for (char nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (char c : FIRST[nt])
            cout << c << " ";
        cout << "}\n";
    }

    // Display FOLLOW sets
    cout << "\nFOLLOW sets:\n";
    for (char nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (char c : FOLLOW[nt])
            cout << c << " ";
        cout << "}\n";
    }

    return 0;
}
