#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i = 0;
char input[100];

void E();
void T();
void X();
void match(char c);
void error();

int main() {
    printf("Enter string to parse: ");
    scanf("%s", input);

    printf("\nParsing string: %s\n", input);

    E();

    if (input[i] == '$') {
        printf("String Accepted\n");
    } else {
        error();
    }

    return 0;
}

void E() {
    printf("E = TX\n");
    T();
    X();
}

void T() {
    if (input[i] == 'i') {
        printf("T = i\n");
        match('i');
    } else {
        error();
    }
}

void X() {
    if (input[i] == '+') {
        printf("X = +TX\n");
        match('+');
        T();
        X();
    } else {
        printf("X = @\n");   // epsilon
    }
}

void match(char c) {
    if (input[i] == c) {
        printf("Match %c\n", c);
        i++;
    } else {
        error();
    }
}

void error() {
    printf("String Rejected\n");
    exit(0);
}
