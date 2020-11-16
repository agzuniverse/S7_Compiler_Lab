#include <stdio.h>
#include <string.h>

int n;
char prods[50][50];
// Using the rows of this array as a hashtable to store calculated firsts
char firsts[26][50];
// Using this array to check if the first of a non-termial has been calculated or not
int is_first_done[26];

char follows[26][50];
int is_follow_done[26];

// Only capital letter alphabets are considered non terminals
int isTerminal(char c)
{
    if (c < 65 || c > 90)
        return 1;
    return 0;
}

void first(char nonterm)
{
    int index = 0;
    char curr_firsts[50];
    for (int i = 0; i < n; i++)
    {
        if (prods[i][0] == nonterm)
        {

            // curr_prod_index is an index to the string of the form "A=BC"
            // Its defined as 2 so it starts at the location of B.
            int curr_prod_index = 2;

            // Loop only repeats if the flag remains 0.
            int flag = 0;
            while (prods[i][curr_prod_index] != '\0' && flag == 0)
            {
                // Flag is set to 1 initially.
                flag = 1;
                // If a terminal is found, add it to the firsts and stop the loop
                if (isTerminal(prods[i][curr_prod_index]))
                {
                    curr_firsts[index] = prods[i][2];
                    index++;
                    break;
                }

                // If a non terminal whose first has not been calculated yet, recursively call to calculate it
                // This does not cause infinite loop if the grammer is not left recursive.
                if (!is_first_done[prods[i][curr_prod_index] - 65])
                    first(prods[i][curr_prod_index]);

                // Copy the first of the non-terminal in the production to the first of the current non terminal
                int in = 0;
                while (firsts[prods[i][curr_prod_index] - 65][in] != '\0')
                {
                    curr_firsts[index] = firsts[prods[i][curr_prod_index] - 65][in];
                    // If the first of the non terminal in the production has epsilon, the next symbol has to be
                    // also considered, so the flag is set to 0 for the loop to run again
                    if (firsts[prods[i][curr_prod_index] - 65][in] == 'e')
                    {
                        curr_prod_index++;
                        flag = 0;
                    }
                    index++;
                    in++;
                }
            }
        }
    }

    // Copy the calculated first to the final array of firsts
    curr_firsts[index] = '\0';
    index++;
    strcpy(firsts[nonterm - 65], curr_firsts);
    is_first_done[nonterm - 65] = 1;
}

void follow(char nonterm)
{
    int index = 0;
    char curr_follows[50];
    // Starting symbol's follow always contains $
    if (nonterm == prods[0][0])
    {
        curr_follows[index] = '$';
        index++;
    }
    // Check RHS of all productions for the current nontermial
    for (int j = 0; j < n; j++)
    {
        int k = 2;
        int include_lhs_flag;
        while (prods[j][k] != '\0')
        {
            include_lhs_flag = 0;
            if (prods[j][k] == nonterm)
            {
                if (prods[j][k + 1] != '\0')
                {
                    // If the symbol to the right is a terminal
                    if (isTerminal(prods[j][k + 1]))
                    {
                        curr_follows[index] = prods[j][k + 1];
                        index++;
                        break;
                    }
                    // If the symbol to the right is a non-terminal
                    // Add everything in it's first to the current nonterminal's follow
                    int in = 0;
                    while (firsts[prods[j][k + 1] - 65][in] != '\0')
                    {
                        // Epsilon cannot be in follow
                        if (firsts[prods[j][k + 1] - 65][in] == 'e')
                        {
                            // If epsilon is found, follow of the LHS has to be added to this nonterminal's follow
                            include_lhs_flag = 1;
                            in++;
                            continue;
                        }

                        // Don't add symbols to follow if it's already there
                        int temp_flag = 0;
                        for (int z = 0; z < index; z++)
                            if (firsts[prods[j][k + 1] - 65][in] == curr_follows[z])
                            {
                                temp_flag = 1;
                                in++;
                                break;
                            }
                        if (temp_flag)
                            continue;

                        curr_follows[index] = firsts[prods[j][k + 1] - 65][in];
                        index++;
                        in++;
                    }
                }
                // If there is nothing to the right or if the first of the symbol to the right had an epsilon in it's first,
                // add the follow of the LHS to this nonterminal's follow
                if (prods[j][k + 1] == '\0' || include_lhs_flag == 1)
                {
                    // Prevent infinite loop when the same symbol is on both LHS and RHS
                    if (prods[j][0] != nonterm)
                    {
                        if (!is_follow_done[prods[j][0] - 65])
                            follow(prods[j][0]);
                        int x = 0;
                        while (follows[prods[j][0] - 65][x] != '\0')
                        {
                            // Don't add symbols to follow if it's already there
                            int temp_flag = 0;
                            for (int z = 0; z < index; z++)
                                if (follows[prods[j][0] - 65][x] == curr_follows[z])
                                {
                                    temp_flag = 1;
                                    x++;
                                    break;
                                }
                            if (temp_flag)
                                continue;
                            curr_follows[index] = follows[prods[j][0] - 65][x];
                            index++;
                            x++;
                        }
                    }
                }
            }
            k++;
        }
    }

    curr_follows[index] = '\0';
    index++;
    strcpy(follows[nonterm - 65], curr_follows);
    is_follow_done[nonterm - 65] = 1;
}

int main()
{
    // Take inputs
    printf("Enter the number of productions\n");
    scanf("%d", &n);
    printf("Enter productions in the format A=CD+\n\
Each production should be in a different line.\n\
Capital letters denote non-terminals, everything else is terminals.\n\
e is treated as epsilon.\n");
    for (int i = 0; i < n; i++)
        scanf("%s", prods[i]);

    // Calculate firsts

    // Initially no production's first has been calculated
    for (int i = 0; i < 26; i++)
        is_first_done[i] = 0;

    // Calculate firsts for all productions
    for (int i = 0; i < n; i++)
        if (is_first_done[prods[i][0] - 65] == 0)
            first(prods[i][0]);

    // Calculate follows for all productions
    for (int i = 0; i < n; i++)
        if (is_follow_done[prods[i][0] - 65] == 0)
            follow(prods[i][0]);

    printf("Firsts:\n");
    for (int i = 0; i < 26; i++)
        if (is_first_done[i])
            printf("%c : %s\n", i + 65, firsts[i]);

    printf("Follows:\n");
    for (int i = 0; i < 26; i++)
        if (is_follow_done[i])
            printf("%c : %s\n", i + 65, follows[i]);
}