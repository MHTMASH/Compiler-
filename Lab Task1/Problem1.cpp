#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    int chars = 0, words = 0, lines = 0;
    int inWord = 0;
    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        chars++;
        
        if (ch == '\n') {
            lines++;
        }
        
        if (isspace(ch)) {
            inWord = 0;
        } else {
            if (inWord == 0) {
                words++;
                inWord = 1;
            }
        }
    }
    
    fclose(file);
    
    printf("Total characters: %d\n", chars);
    printf("Total words: %d\n", words);
    printf("Total lines: %d\n", lines);
    
    return 0;
}