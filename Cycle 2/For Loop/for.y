%{
    #include<stdio.h>
    int yyerror();
    int yylex();
    int valid = 1;
%}

%token FOR ID NUM BIOP UNOP

%%

start: FOR '(' loop_expr ';' loop_expr ';' loop_expr ')' body
      ;

body: stmt
    | '{' stmt_list '}'
    ;

stmt_list: stmt_list stmt
        |
        ;

stmt: loop_expr ';'
    ;

loop_expr: compound_expr
          |
          ;

compound_expr: compound_expr ',' expr
              | expr
              ;

expr: ID BIOP expr
    | ID UNOP
    | UNOP ID
    | ID
    | NUM
    ;

%%

int yyerror()
{
    printf("This is invalid!\n");
    valid = 0;
    return 0;
}

int main()
{
    yyparse();
    if(valid)
        printf("The loop is valid\n");
}