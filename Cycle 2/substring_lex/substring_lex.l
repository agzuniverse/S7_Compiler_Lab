%%
.*aswi.*\n ;
. return 1;
%%
int yywrap(){}

int main()
{
    yylex();
}