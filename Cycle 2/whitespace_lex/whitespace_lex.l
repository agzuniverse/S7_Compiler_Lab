%%
\/\*(.*\n)*.*\*\/ ;
\/\/.*\n ;
[\t\n ]+ ;
. return 1;
%%
int yywrap(){}

int main()
{
    yylex();
}