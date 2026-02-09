%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token IF ELSE
%token ID NUM
%token LT

%left '+' '-'
%left '*' '/'
%left LT

%%

program
    : stmt_list            { printf("Parsing successful\n"); }
    ;

stmt_list
    : stmt_list stmt
    | stmt
    ;

stmt
    : assignment
    | if_stmt
    ;

assignment
    : ID '=' expr ';'
    ;

if_stmt
    : IF '(' expr ')' block
    | IF '(' expr ')' block ELSE block
    ;

block
    : '{' stmt_list '}'
    ;

expr
    : expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr LT expr
    | ID
    | NUM
    ;

%%

void yyerror(const char *s) {
    printf("Syntax error\n");
}

int main() {
    return yyparse();
}
