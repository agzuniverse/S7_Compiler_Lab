/*
Sample Input:
void main()
{
   int a, b, c;
   c = a + b;
}
*/
#include <iostream>
#include <fstream>

using namespace std;

string keywords[] = {"auto", "break", "case", "char", "const", "continue", "default",
                     "do", "double", "else", "enum", "extern", "float", "for", "goto",
                     "if", "int", "long", "register", "return", "short", "signed",
                     "sizeof", "static", "struct", "switch", "typedef", "union",
                     "unsigned", "void", "volatile", "while"};
int number_of_keywords = 32;
char operators[] = {'+', '-', '*', '/', '%', '='};

bool isOperator(char c)
{
    int len = sizeof(operators) / sizeof(operators[0]);
    for (int i = 0; i < len; i++)
    {
        if (c == operators[i])
            return true;
    }
    return false;
}

bool isKeyword(string s)
{
    for (int i = 0; i < number_of_keywords; i++)
    {
        if (s == keywords[i])
            return true;
    }
    return false;
}

int main()
{
    ifstream inp("input.cpp");
    char c;
    string temp = "";
    while (inp.get(c))
    {
        if (isOperator(c))
            cout << c << " is an operator\n";
        else if (isalnum(c))
            temp.push_back(c);
        else if (c == ' ' || c == '\n' || c == '\t')
        {
            if (temp.length() > 0)
            {
                if (isKeyword(temp))
                    cout << temp << " is a keyword\n";
                else
                    cout << temp << " is a identifier\n";
                temp = "";
            }
        }
    }
}