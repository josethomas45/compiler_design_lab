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
    while ((ch = fgetc(fp)) != '\n' && ch != EOF);
}

void skipMultiLineComment(FILE *fp) {
    char ch, nextCh;
    ch = fgetc(fp);
    while ((ch != '*' || (nextCh = fgetc(fp)) != '/') && ch != EOF) {
        ch = nextCh;
    }
}

int main() {
    char ch, buffer[100], operators[] = "+-*/%=<>!&|^";
    char tokens[] = "();{}[],[]";
    FILE *fp;
    int i, j = 0;
    fp = fopen("inp.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        
        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                skipSingleLineComment(fp);
                continue;
            } else if (next == '*') {
                skipMultiLineComment(fp);
                continue;
            } else {
                ungetc(next, fp);
            }
        }

    
        for (i = 0; operators[i] != '\0'; ++i) {
            if (ch == operators[i]) {
                printf("%c is operator\n", ch);
                break;
            }
        }

        
        for (i = 0; tokens[i] != '\0'; ++i) {
            if (ch == tokens[i]) {
                printf("%c is a token\n", ch);
                break;
            }
        }

        
        if (isalnum(ch) || ch == '_') {
            buffer[j++] = ch;
        } else if ((ch == ' ' || ch == '\n' || ch == '\t') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            if (isKeyword(buffer))
                printf("%s is keyword\n", buffer);
            else
                printf("%s is an identifier\n", buffer);
        }
    }

    
    if (j != 0) {
        buffer[j] = '\0';
        if (isKeyword(buffer))
            printf("%s is keyword\n", buffer);
        else
            printf("%s is an identifier\n", buffer);
    }

    fclose(fp);
    return 0;
}
