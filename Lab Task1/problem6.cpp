#include <stdio.h>

int main() {
    char line[200];
    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);
    
    printf("Special symbols: ");
    
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '{' || line[i] == '}' || 
            line[i] == '(' || line[i] == ')' ||
            line[i] == ';' || line[i] == ',' ||
            line[i] == '[' || line[i] == ']' ||
            line[i] == '.') {
            printf("%c ", line[i]);
        }
    }
    
    printf("\n");
    return 0;
}