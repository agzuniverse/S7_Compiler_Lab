%{
    #include<stdio.h>
    int valid=1;
    int yylex();
    int yyerror();
%}

%token letter digit
%start line

%%

line: letter remaining
remaining: letter remaining
        |  digit remaining
        |
        ;
%%

int yyerror(){
    printf("Invalid variable\n");
    valid=0;
    return 0;
}

int main()
{
    printf("Enter variable to check if it is valid\n");
    yyparse();
    if(valid) printf("Valid.\n");
}