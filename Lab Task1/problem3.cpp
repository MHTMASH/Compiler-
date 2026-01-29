#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Regex: [a-zA-Z_][a-zA-Z0-9_]*
int isValidIdentifier(char *str) {
    if (str[0] == '\0') return 0;
    
    // Must start with letter or underscore
    if (!isalpha(str[0]) && str[0] != '_')
        return 0;
    
    // Rest can be letters, digits, or underscore
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_')
            return 0;
    }
    return 1;
}

int main() {
    char line[200];
    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);
    
    char word[50];
    int j = 0;
    
    printf("Valid identifiers: ");
    for (int i = 0; line[i] != '\0'; i++) {
        if (isalnum(line[i]) || line[i] == '_') {
            word[j++] = line[i];
        } else {
            if (j > 0) {
                word[j] = '\0';
                if (isValidIdentifier(word))
                    printf("%s ", word);
                j = 0;
            }
        }
    }
    
    printf("\n");
    printf("Invalid identifiers: ");
    
    // Reset to find invalid
    j = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (isalnum(line[i]) || line[i] == '_') {
            word[j++] = line[i];
        } else {
            if (j > 0) {
                word[j] = '\0';
                if (!isValidIdentifier(word))
                    printf("%s ", word);
                j = 0;
            }
        }
    }
    
    printf("\n");
    return 0;
}