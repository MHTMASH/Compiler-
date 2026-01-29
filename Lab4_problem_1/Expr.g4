grammar Expr;

expr
    : expr '+' term
    | expr '-' term
    | term
    ;

term
    : term '*' power
    | term '/' power
    | power
    ;

power
    : factor '^' power      // right associative
    | factor
    ;

factor
    : '(' expr ')'
    | ID
    | NUM
    ;

ID  : [a-zA-Z]+ ;
NUM : [0-9]+ ('.' [0-9]+)? ;

WS  : [ \t\r\n]+ -> skip ;