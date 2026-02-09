#include <stdio.h>
#include <string.h>
#include <ctype.h>


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

int hasInvalidChar(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '@' || str[i] == '$' || str[i] == '#')
            return str[i];
    }
    return 0;
}

int main() {
    FILE *file = fopen("input3.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }
    
    char line[500];
    int lineNum = 1;
    
    while (fgets(line, sizeof(line), file)) {
        int i = 0;
        int len = strlen(line);
        
        while (i < len) {
            // skip whitespace
            if (isspace(line[i])) {
                i++;
                continue;
            }
            
            // string literals
            if (line[i] == '"') {
                int start = i;
                i++;
                int closed = 0;
                while (i < len) {
                    if (line[i] == '"') {
                        closed = 1;
                        i++;
                        break;
                    }
                    if (line[i] == '\n') break;
                    i++;
                }
                
                if (!closed) {
                    // unterminated string
                    char str[100];
                    int j = 0;
                    for (int k = start; k < i && line[k] != '\n'; k++) {
                        str[j++] = line[k];
                    }
                    str[j] = '\0';
                    printf("Error: Unterminated string literal %s\n", str);
                }
                continue;
            }
            
            // multi-line comments
            if (i < len - 1 && line[i] == '/' && line[i+1] == '*') {
                int start = i;
                i += 2;
                int closed = 0;
                
                while (i < len - 1) {
                    if (line[i] == '*' && line[i+1] == '/') {
                        closed = 1;
                        i += 2;
                        break;
                    }
                    i++;
                }
                
                if (!closed) {
                    printf("Error: Unterminated comment /*\n");
                }
                continue;
            }
            
            // identifiers
            if (isalpha(line[i]) || line[i] == '_' || isdigit(line[i])) {
                char word[50];
                int j = 0;
                int startPos = i;
                
                while (i < len && !isspace(line[i]) && line[i] != ';' && 
                       line[i] != ',' && line[i] != '=' && line[i] != '(' && 
                       line[i] != ')') {
                    word[j++] = line[i++];
                }
                word[j] = '\0';
                
                // starts with digit
                if (isdigit(word[0])) {
                    printf("Error: Invalid identifier '%s'\n", word);
                }
                // invalid characters
                else if (hasInvalidChar(word)) {
                    char invalidChar = hasInvalidChar(word);
                    printf("Error: Invalid character '%c' in identifier %s\n", 
                           invalidChar, word);
                }
                // valid identifier
                else if (!isValidIdentifier(word)) {
                    printf("Error: Invalid identifier '%s'\n", word);
                }
                
                continue;
            }
            
            i++;
        }
        
        lineNum++;
    }
    
    fclose(file);
    return 0;
}