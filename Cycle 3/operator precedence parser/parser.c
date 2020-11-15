#include <stdio.h>

int getindex(char c)
{
    switch (c)
    {
    case 'i':
        return 0;
    case '+':
        return 1;
    case '*':
        return 2;
    case '$':
        return 3;
    }
}

int main()
{
    char table[][4] =
        //         i    +    *    $
        /* i */ {{' ', '>', '>', '>'},
        /* + */ { '<', '>', '<', '>'},
        /* * */ { '<', '>', '>', '>'},
        /* $ */ { '<', '<', '<', ' '}};
    char inp[100];
    printf("Enter input\n");
    scanf("%s", inp);

    char stack[100];
    int top = 0, curr = 0;
    if (inp[0] == '$')
    {
        stack[top] = '$';
        curr++;
    }
    else
        printf("Rejected.\n");
    while (inp[curr] != '\0')
    {
        // 2 identifiers one after the other is not acceptable.
        if (stack[top] == 'i' && inp[curr] == 'i')
            break;
        while (table[getindex(stack[top])][getindex(inp[curr])] == '>')
            top--;
        top++;
        stack[top] = inp[curr];
        curr++;
    }
    if (top == 1 && stack[0] == '$' && stack[1] == '$')
        printf("Accepted.\n");
    else
        printf("Rejected.\n");
}