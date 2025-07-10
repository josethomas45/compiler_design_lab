#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
        "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };
    int i, flag = 0;
    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}

int main() {
    char ch, buffer[100], operators[] = "+-*/%=<>!&|^";
    FILE *fp;
    int i, j = 0;

    fp = fopen("inp.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        
        if (strchr(operators, ch)) {
            
            char next_char = fgetc(fp);
            if ((ch == '=' && (next_char == '=' || next_char == '+')) ||
                (ch == '!' && next_char == '=') ||
                (ch == '+' && next_char == '=') ||
                (ch == '-' && next_char == '=') ||
                (ch == '&' && next_char == '=') ||
                (ch == '|' && next_char == '=')) {
                printf("%c%c is operator\n", ch, next_char);
                continue;
            }
            ungetc(next_char, fp);  
            printf("%c is operator\n", ch);
            continue;
        }

        
        if (isalnum(ch) || ch == '_') {
            buffer[j++] = ch;
        } else if ((ch == ' ' || ch == '\n' || ch == '\t') && (j != 0)) {
            buffer[j] = '\0';  
            j = 0;
            if (isKeyword(buffer)) {
                printf("%s is keyword\n", buffer);
            } else {
                printf("%s is an identifier\n", buffer);
            }
        }
    }

    
    if (j != 0) {
        buffer[j] = '\0';
        if (isKeyword(buffer)) {
            printf("%s is keyword\n", buffer);
        } else {
            printf("%s is an identifier\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}
