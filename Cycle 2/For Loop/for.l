%{
    #include "y.tab.h"
%}

%%

"for" return FOR;
"++"|"--" return UNOP;
=|<|>|<=|>=|!=|&&|"||"|[+-/*] return BIOP;
[0-9]+ return NUM;
[a-zA-Z_]+[a-zA-Z0-9_]* return ID;
[ \n\t] ;
. return *yytext;

%%

int yywrap(void){}