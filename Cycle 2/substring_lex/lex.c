#include <stdio.h>

extern int yylex();
extern char *yytext;

int main()
{
    int ntoken;
    do
    {
        ntoken = yylex();
        printf("%s", yytext);
    } while (ntoken);
}