#include <stdio.h>
#include <string.h>

int main() {
    char line[500];
    printf("Enter a line or comment: ");
    fgets(line, sizeof(line), stdin);
    
    int len = strlen(line);
    
    // Check for single-line comment
    for (int i = 0; i < len - 1; i++) {
        if (line[i] == '/' && line[i+1] == '/') {
            printf("Single-line comment detected\n");
            return 0;
        }
    }
    
    // Check for multi-line comment
    int start = -1, end = -1;
    for (int i = 0; i < len - 1; i++) {
        if (line[i] == '/' && line[i+1] == '*') {
            start = i;
            break;
        }
    }
    
    for (int i = len - 1; i > 0; i--) {
        if (line[i] == '/' && line[i-1] == '*') {
            end = i;
            break;
        }
    }
    
    if (start != -1 && end != -1) {
        printf("Multi-line comment detected\n");
    } else if (start != -1) {
        printf("Error: Unterminated multi-line comment\n");
    } else {
        printf("No comment detected\n");
    }
    
    return 0;
}