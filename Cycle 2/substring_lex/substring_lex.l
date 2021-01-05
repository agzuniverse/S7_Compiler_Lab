%%
.*aswi.*\n ;
. printf("%s", yytext);
%%
int yywrap(){}

int main()
{
    yylex();
}