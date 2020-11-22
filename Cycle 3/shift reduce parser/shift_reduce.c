#include <stdio.h>
#include <string.h>

/*
Grammar:
S -> S+S
S -> S-S
S -> (S)
S -> i
*/

char inp[100];
int len;
char stack[100];
int top = 0;

void print_details(int ind, char *action)
{
    printf("$");
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);
    printf("\t\t");
    for (int i = ind; i < len; i++)
        printf("%c", inp[i]);
    printf("$\t\t%s\n", action);
}

void check_for_reduce(int i)
{
    int flag = 1;
    // Keep trying to reduce until no more reduction actions are possible
    while (flag)
    {
        flag = 0;
        // S -> S+S
        if (stack[top - 2] == 'S' && stack[top - 1] == '+' && stack[top] == 'S')
        {
            // i+1 to not print the character that got shifted in the previous action
            print_details(i + 1, "REDUCE");
            stack[top - 2] = 'S';
            top = top - 2;
            flag = 1;
        }
        // S -> S-S
        else if (stack[top - 2] == 'S' && stack[top - 1] == '-' && stack[top] == 'S')
        {
            print_details(i + 1, "REDUCE");
            stack[top - 2] = 'S';
            top = top - 2;
            flag = 1;
        }
        // S -> (S)
        else if (stack[top - 2] == '(' && stack[top - 1] == 'S' && stack[top] == ')')
        {
            print_details(i + 1, "REDUCE");
            stack[top - 2] = 'S';
            top = top - 2;
            flag = 1;
        }
        // S -> i
        else if (stack[top] == 'i')
        {
            print_details(i + 1, "REDUCE");
            stack[top] = 'S';
            flag = 1;
        }
    }
}

int main()
{
    printf("Enter input:\n");
    scanf("%s", inp);
    len = strlen(inp);

    // Print headings
    printf("Stack\t\tInput\t\tAction\n");

    for (int i = 0; i < len; i++)
    {
        print_details(i, "SHIFT");
        stack[top] = inp[i];
        check_for_reduce(i);
        top++;
    }
    // remove the last top++
    top--;

    if (top == 0 && stack[0] == 'S')
        printf("Accepted.\n");
    else
        printf("Rejected.\n");
}