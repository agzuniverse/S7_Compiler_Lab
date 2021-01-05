%%
\/\*(.*\n)*.*\*\/ ;
\/\/.*\n ;
[\t\n ]+ ;
. printf("%c", yytext[0]);
%%
int yywrap(){}

int main()
{
    yylex();
}