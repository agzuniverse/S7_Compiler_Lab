%{
    #include<stdio.h>
    int yylex();
    int yyerror();
%}

%token NUMBER
%left '+' '-' // This specifies associativity of these operators
%left '*' '/' // Lowest line has operators with highest precedence

%%

start: exp {printf("%d\n", $$);}
        ;
exp: exp '*' exp {$$ = $1 * $3;}
    |exp '/' exp {$$ = (float)$1 / $3;}
    |exp '+' exp {$$ = $1 + $3;}
    |exp '-' exp {$$ = $1 - $3;}
    |NUMBER {$$=$1;}
    ;

%%

int yyerror()
{
    printf("Invalid input\n");
    return 0;
}

int main()
{
    printf("Enter in the format <NUMBER><OP><NUMBER> where OP can be +, -, / or * \n");
    yyparse();
}