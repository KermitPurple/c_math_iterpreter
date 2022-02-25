#ifndef TOKEN_H
#define TOKEN_H

#include<stdbool.h>

typedef enum{
    L_PAREN,
    R_PAREN,
    INT,
    ADD,
    SUB,
    MUL,
    DIV,
    END,
}TokenType;

typedef struct{
    TokenType type;
    int num;
}Token;

typedef struct{
    char* string;
    Token* current;
    Token* next;
    bool error;
}TokenIter;

TokenIter* token_iter_new(char* string);
bool iterate(TokenIter* iter);
bool is_add_operator(TokenType);
bool is_mul_operator(TokenType);
bool is_operator(TokenType);
void print_token(Token*);

#endif // TOKEN_H
