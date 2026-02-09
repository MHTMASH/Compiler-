#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *str) {    
    const char *keywords[] = {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum"
    };    
    
    int n = 11;
    
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char line[200];
    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);
    
    char word[50];
    int j = 0;
    
    printf("Keywords found: ");
    
    for (int i = 0; line[i] != '\0'; i++) {
        if (isalpha(line[i]) || line[i] == '_') {
            word[j++] = line[i];
        } else {
            if (j > 0) {
                word[j] = '\0';
                if (isKeyword(word)) {
                    printf("%s ", word);
                }
                j = 0;
            }
        }
    }
    
    printf("\n");
    return 0;
}