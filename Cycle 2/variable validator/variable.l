%{
    #include "y.tab.h"
%}

%%
[a-zA-Z]+ return letter;
[0-9]+ return digit;
. ;
\n return 0;
%%

int yywrap(void){}