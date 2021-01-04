#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class DFA;

class NFA
{
    int noOfStates;
    unordered_set<char> states;
    int noOfSymbols;
    unordered_set<char> symbols;
    int noOfTransitions;
    unordered_map<char, vector<pair<char, char>>> transitions;
    char initialState;
    unordered_set<char> finalStates;

    friend DFA;

    void printStates()
    {
        cout << "The states are:\n";
        for (auto it : states)
            cout << it << " ";
        cout << endl;
    }

public:
    NFA(int nst, int nsy, int ntr) : noOfStates{nst}, noOfSymbols{nsy}, noOfTransitions{ntr}
    {
        // Input all the required data to finish constructing the NFA
        inputStates();
        inputSymbols();
        inputTransitions();
    }

    void inputSymbols()
    {
        cout << "Enter symbols. Each symbols must be represented with a single character\nEpsilon transitions are not allowed.";
        char curr;
        for (int i = 0; i < noOfSymbols; i++)
        {
            cin >> curr;
            symbols.insert(curr);
        }
    }

    void inputStates()
    {
        cout << "Enter states. Each state must be represented with a single character\n";
        char curr;
        for (int i = 0; i < noOfStates; i++)
        {
            cin >> curr;
            states.insert(curr);
        }
        printStates();

        cout << "Enter initial state\n";
        while (true)
        {
            cin >> curr;
            if (states.find(curr) == states.end())
                cout << "That state is not in the set of states\n";
            else
            {
                initialState = curr;
                break;
            }
        }

        cout << "Enter no. final states\n";
        int fs;
        cin >> fs;
        cout << "Enter final states\n";
        int i = 0;
        while (i < fs)
        {
            cin >> curr;
            if (states.find(curr) == states.end())
                cout << "That state is not in the set of states\n";
            else
            {
                finalStates.insert(curr);
                i++;
            }
        }
    }

    void inputTransitions()
    {
        cout << "Enter transitions in the format \"<start state> <symbol> <end state>\n";
        char from, s, to;
        int i = 0;
        while (i < noOfTransitions)
        {
            cin >> from >> s >> to;
            if (states.find(from) == states.end() || states.find(to) == states.end())
            {
                cout << "Invalid state\n";
                continue;
            }
            else if (symbols.find(s) == symbols.end())
            {
                cout << "Invalid symbol\n";
                continue;
            }
            else
            {
                transitions[from].push_back(make_pair(s, to));
                i++;
            }
        }
    }
};

class DFA
{
    // When converting from NFA to DFA, states in the NFA such as `a` and `b` can get
    // combined into a single state `a,b` in the DFA. A map is used to represent states
    // in the DFA as "a,b" -> [a,b]. The vector of states is present to avoid having
    // to perform string manipulation and conversion when looping through all the states
    // that got combined into a single state in the DFA.
    unordered_map<string, vector<char>> states;
    unordered_set<char> symbols;
    unordered_map<string, vector<pair<char, string>>> transitions;
    string initialState;
    unordered_set<string> finalStates;

    void printDFA()
    {
        cout << "The DFA:\n\n";
        cout << "States:\n";
        for (auto it : states)
        {
            cout << it.first << ", ";
        }
        cout << "\n\nSymbols:\n";
        for (auto it : symbols)
        {
            cout << it << ", ";
        }
        cout << "\n\nTransitions:\n";
        for (auto it : transitions)
        {
            for (auto e : it.second)
            {
                cout << it.first << " -> " << e.first << " -> " << e.second << endl;
            }
        }
    }

public:
    DFA(NFA z)
    {
        symbols = z.symbols;
        constructStates(z);
    }
    void constructStates(NFA z)
    {
        string initial(1, z.initialState);
        vector<char> v{z.initialState};
        states[initial] = v;
        queue<pair<string, vector<char>>> q;
        q.push(make_pair(initial, v));
        while (!q.empty())
        {
            pair<string, vector<char>> curr_dfa_state = q.front();
            q.pop();
            // Map from symbol to all states that can be reached from current state with that symbol
            unordered_map<char, vector<char>> temp;
            for (auto curr_state : curr_dfa_state.second)
                for (auto it : z.transitions[curr_state])
                    temp[it.first].push_back(it.second);
            for (auto it : temp)
            {
                string s;
                for (auto e : it.second)
                    s += e;
                transitions[curr_dfa_state.first].push_back(make_pair(it.first, s));
                // If the new state s has not been previously discovered, add to queue
                if (states.find(s) == states.end())
                {
                    states[s] = it.second;
                    q.push(make_pair(s, it.second));
                }
            }
        }
        printDFA();
    }
};

int main()
{
    int states, symbols, transitions;
    cout << "Enter number of states\n";
    cin >> states;
    cout << "Enter number of input symbols\n";
    cin >> symbols;
    cout << "Enter number of transitions\n";
    cin >> transitions;
    NFA z{states, symbols, transitions};
    DFA d{z};
}