#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isInteger(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int isFloat(char *str) {
    int dotCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            dotCount++;
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    return (dotCount == 1);
}

int main() {
    char line[200];
    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);
    
    char num[50];
    int j = 0;
    
    printf("Integer constants: ");
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i]) || line[i] == '.') {
            num[j++] = line[i];
        } else {
            if (j > 0) {
                num[j] = '\0';
                if (isInteger(num))
                    printf("%s ", num);
                j = 0;
            }
        }
    }
    
    printf("\n");
    printf("Floating-point constants: ");
    
    j = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i]) || line[i] == '.') {
            num[j++] = line[i];
        } else {
            if (j > 0) {
                num[j] = '\0';
                if (isFloat(num))
                    printf("%s ", num);
                j = 0;
            }
        }
    }
    
    printf("\n");
    return 0;
}