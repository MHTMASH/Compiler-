#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("input2.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }
    
    char line[200];
    int lineNum = 1;
    
    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        
        // Check for string literals
        if (line[0] == '"') {
            int closed = 0;
            for (int i = 1; i < len; i++) {
                if (line[i] == '"') {
                    closed = 1;
                    break;
                }
            }
            if (closed) {
                printf("Line %d: Valid string literal\n", lineNum);
            } else {
                printf("Line %d: Error - Unterminated string\n", lineNum);
            }
        }
        // Check for character constants
        else if (line[0] == '\'') {
            if (line[1] == '\'') {
                printf("Line %d: Error - Empty character constant\n", lineNum);
            } else if (line[2] == '\'') {
                printf("Line %d: Valid character constant\n", lineNum);
            } else if (line[1] != '\'' && line[2] != '\'') {
                int closed = 0;
                for (int i = 1; i < len; i++) {
                    if (line[i] == '\'') {
                        closed = 1;
                        if (i > 2) {
                            printf("Line %d: Error - Multiple characters\n", lineNum);
                        } else {
                            printf("Line %d: Error - Unterminated character\n", lineNum);
                        }
                        break;
                    }
                }
                if (!closed) {
                    printf("Line %d: Error - Unterminated character\n", lineNum);
                }
            }
        }
        
        lineNum++;
    }
    
    fclose(file);
    return 0;
}