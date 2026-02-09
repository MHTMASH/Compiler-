#include <stdio.h>
#include <string.h>

int main() {
    char line[200];
    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);
    
    printf("Assignment operators: ");
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '=' && line[i+1] != '=')
            printf("= ");
    }
    
    printf("\nArithmetic operators: ");
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '+' || line[i] == '-' || line[i] == '*' || 
            line[i] == '/' || line[i] == '%')
            printf("%c ", line[i]);
    }
    
    printf("\nRelational operators: ");
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '>' && line[i+1] == '=') {
            printf(">= ");
            i++;
        } else if (line[i] == '<' && line[i+1] == '=') {
            printf("<= ");
            i++;
        } else if (line[i] == '=' && line[i+1] == '=') {
            printf("== ");
            i++;
        } else if (line[i] == '!' && line[i+1] == '=') {
            printf("!= ");
            i++;
        } else if (line[i] == '>') {
            printf("> ");
        } else if (line[i] == '<') {
            printf("< ");
        }
    }
    
    printf("\nLogical operators: ");
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '&' && line[i+1] == '&') {
            printf("&& ");
            i++;
        } else if (line[i] == '|' && line[i+1] == '|') {
            printf("|| ");
            i++;
        } else if (line[i] == '!') {
            printf("! ");
        }
    }
    
    printf("\n");
    return 0;
}