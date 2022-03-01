#ifndef TOKEN_H
#define TOKEN_H

#include<stdbool.h>

typedef enum{
    L_PAREN_TOKEN,
    R_PAREN_TOKEN,
    INT_TOKEN,
    ADD_TOKEN,
    SUB_TOKEN,
    MUL_TOKEN,
    DIV_TOKEN,
    END_TOKEN,
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
int get_precedence(TokenType type);

#endif // TOKEN_H
