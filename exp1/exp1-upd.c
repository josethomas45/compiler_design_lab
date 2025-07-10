#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
        "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", 
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", 
        "union", "unsigned", "void", "volatile", "while"
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

void skipSingleLineComment(FILE *fp) {
    char ch;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF);  // Skip until newline or EOF
}

void skipMultiLineComment(FILE *fp) {
    char ch, nextCh;
    ch = fgetc(fp);
    while ((ch != '*' || (nextCh = fgetc(fp)) != '/') && ch != EOF) {
        ch = nextCh;
    }
}

int main() {
    char ch, buffer[15], operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0;
    fp = fopen("inp.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Skip single-line comments
        if (ch == '/' && (ch = fgetc(fp)) == '/') {
            skipSingleLineComment(fp);
            continue;
        }

        // Skip multi-line comments
        if (ch == '/' && (ch = fgetc(fp)) == '*') {
            skipMultiLineComment(fp);
            continue;
        }

        // Check if the character is an operator
        for (i = 0; i < 6; ++i) {
            if (ch == operators[i]) {
                printf("%c is operator\n", ch);
            }
        }

        // Handle alphanumeric characters (identifiers or keywords)
        if (isalnum(ch)) {
            buffer[j++] = ch;
        } else if ((ch == ' ' || ch == '\n') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            if (isKeyword(buffer) == 1)
                printf("%s is keyword\n", buffer);
            else
                printf("%s is an identifier\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}