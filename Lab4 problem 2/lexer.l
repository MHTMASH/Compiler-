%{
#include "parser.tab.h"
%}

%%

"if"        { return IF; }
"else"      { return ELSE; }

[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }
[0-9]+                  { return NUM; }

"<"         { return LT; }

[=+*/\-;(){}]   { return yytext[0]; }

[ \t\n]+    ;   /* ignore whitespace */

.           { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
