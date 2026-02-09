#include <stdio.h>
#include <string.h>
#include <ctype.h>

int keywordCount = 0, identifierCount = 0, constantCount = 0;
int operatorCount = 0, symbolCount = 0, stringCount = 0, invalidCount = 0;

int isKeyword(char *str) {
    const char *keywords[] = {"int", "float", "char", "double", "if", "else", 
                        "while", "for", "return", "void", "main", "printf", "scanf"};
    int n = 13;
    
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == '%' || ch == '=' || ch == '<' || ch == '>');
}

int isSpecialSymbol(char ch) {
    return (ch == '(' || ch == ')' || ch == '{' || ch == '}' || 
            ch == '[' || ch == ']' || ch == ';' || ch == ',' || ch == '.');
}

int isNumber(char *str) {
    int dotCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            dotCount++;
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    return (dotCount <= 1);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }
    
    char line[500];
    
    while (fgets(line, sizeof(line), file)) {
        int i = 0;
        int len = strlen(line);
        
        while (i < len) {
            // Skip whitespace
            if (isspace(line[i])) {
                i++;
                continue;
            }
            
            // Check for string literals
            if (line[i] == '"') {
                int start = i;
                i++;
                while (i < len && line[i] != '"') {
                    i++;
                }
                if (i < len) {
                    i++; // Include closing quote
                    char str[100];
                    strncpy(str, &line[start], i - start);
                    str[i - start] = '\0';
                    printf("<%s, string_literal>\n", str);
                    stringCount++;
                }
                continue;
            }
            
            // Check for identifiers or keywords
            if (isalpha(line[i]) || line[i] == '_') {
                char word[50];
                int j = 0;
                while (i < len && (isalnum(line[i]) || line[i] == '_')) {
                    word[j++] = line[i++];
                }
                word[j] = '\0';
                
                if (isKeyword(word)) {
                    printf("<%s, keyword>\n", word);
                    keywordCount++;
                } else {
                    printf("<%s, identifier>\n", word);
                    identifierCount++;
                }
                continue;
            }
            
            // Check for numbers
            if (isdigit(line[i])) {
                char num[50];
                int j = 0;
                while (i < len && (isdigit(line[i]) || line[i] == '.')) {
                    num[j++] = line[i++];
                }
                num[j] = '\0';
                printf("<%s, constant>\n", num);
                constantCount++;
                continue;
            }
            
            // Check for operators
            if (isOperator(line[i])) {
                printf("<%c, operator>\n", line[i]);
                operatorCount++;
                i++;
                continue;
            }
            
            // Check for special symbols
            if (isSpecialSymbol(line[i])) {
                printf("<%c, special_symbol>\n", line[i]);
                symbolCount++;
                i++;
                continue;
            }
            
            i++;
        }
        printf("\n");
    }
    
    printf("Token Counts:\n");
    printf("Keywords: %d\n", keywordCount);
    printf("Identifiers: %d\n", identifierCount);
    printf("Constants: %d\n", constantCount);
    printf("Operators: %d\n", operatorCount);
    printf("Special symbols: %d\n", symbolCount);
    printf("String literals: %d\n", stringCount);
    printf("Invalid tokens: %d\n", invalidCount);
    
    fclose(file);
    return 0;
}