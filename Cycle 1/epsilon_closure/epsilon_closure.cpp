#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class NFA
{
    int noOfStates;
    unordered_set<char> states;
    int noOfSymbols;
    unordered_set<char> symbols;
    int noOfTransitions;
    unordered_map<char, vector<pair<char, char>>> transitions;
    char initialState;
    char finalState;
    unordered_map<char, vector<char>> e_closures;

    void printStates()
    {
        cout << "The states are:\n";
        for (auto it : states)
            cout << it << " ";
        cout << endl;
    }

    void printClosures()
    {
        cout << "The e-closures are:\n";
        for (auto v : e_closures)
        {
            cout << v.first << ": ";
            for (auto i : v.second)
                cout << i << " ";
            cout << endl;
        }
    }

public:
    NFA(int nst, int nsy, int ntr) : noOfStates{nst}, noOfSymbols{nsy}, noOfTransitions{ntr}
    {
        // Epsilon is valid symbol for all NFA
        symbols.insert('e');

        // Input all the required data to finish constructing the NFA
        inputStates();
        inputSymbols();
        inputTransitions();
    }

    void inputSymbols()
    {
        cout << "Enter symbols. Each symbols must be represented with a single character\nEpsilon is already considered and should not be entered here\n";
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

        cout << "Enter final state\n";
        while (true)
        {
            cin >> curr;
            if (states.find(curr) == states.end())
                cout << "That state is not in the set of states\n";
            else
            {
                finalState = curr;
                break;
            }
        }
    }

    void inputTransitions()
    {
        cout << "Enter transitions in the format \"<start state> <symbol> <end state>\"\n\"e\" is taken as epsilon\n";
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

    vector<char> findClosuresRecursive(char state, unordered_map<char, bool> &visited)
    {
        vector<char> ans;
        // Return blank vector if this state is already visited
        if (visited[state])
            return ans;
        visited[state] = true;
        for (auto it : transitions[state])
        {
            if (it.first == 'e')
            {
                vector<char> temp = findClosuresRecursive(it.second, visited);
                ans.insert(ans.end(), temp.begin(), temp.end());
            }
        }
        // Every state is in it's own e-closure
        ans.push_back(state);
        e_closures[state] = ans;
        return ans;
    }

    void findClosures()
    {
        unordered_map<char, bool> visited;
        findClosuresRecursive(initialState, visited);
        printClosures();
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

    z.findClosures();
}