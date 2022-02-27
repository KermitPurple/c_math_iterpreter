#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include"token.h"

typedef enum{
    GENERAL,
    NUMBER,
}ScanningState;

static const char* token_type_to_string(TokenType type){
    switch(type){
        case L_PAREN_TOKEN: return "L_PAREN";
        case R_PAREN_TOKEN: return "R_PAREN";
        case INT_TOKEN: return "INT";
        case ADD_TOKEN: return "ADD";
        case SUB_TOKEN: return "SUB";
        case MUL_TOKEN: return "MUL";
        case DIV_TOKEN: return "DIV";
        case END_TOKEN: return "END";
        default: return "";
    }
}

static Token* get_next(TokenIter* iter){
    Token* result = malloc(sizeof(Token));
    if(result == NULL){
        return NULL;
    }
    ScanningState state = GENERAL;
    int buffer_index = 0;
    char buffer[256] = "";
    char ch;
    while(1){
        ch = *iter->string++;
        switch(state){
            case GENERAL:
                if(isdigit(ch)){
                    buffer[buffer_index++] = ch;
                    state = NUMBER;
                    continue;
                }else if(isspace(ch)){
                    continue;
                }else if(ch == '('){
                    result->type = L_PAREN_TOKEN;
                    return result;
                }else if(ch == ')'){
                    result->type = R_PAREN_TOKEN;
                    return result;
                }else if(ch == '+'){
                    result->type = ADD_TOKEN;
                    return result;
                }else if(ch == '-'){
                    result->type = SUB_TOKEN;
                    return result;
                }else if(ch == '*'){
                    result->type = MUL_TOKEN;
                    return result;
                }else if(ch == '/'){
                    result->type = DIV_TOKEN;
                    return result;
                }else if(ch == '\0'){
                    result->type = END_TOKEN;
                    return result;
                }else{
                    iter->error = true;
                    return NULL;
                }
                break;
            case NUMBER:
                if(!isdigit(ch)){
                    iter->string--;
                    result->type = INT_TOKEN;
                    result->num = atoi(buffer);
                    return result;
                }else{
                    buffer[buffer_index++] = ch;
                }
                break;
        }
    }
}

bool iterate(TokenIter* iter){
    if(iter->error || iter->current->type == END_TOKEN){
        return false;
    }
    iter->current = iter->next;
    iter->next = get_next(iter);
    return true;
}

bool is_add_operator(TokenType type){
    switch(type){
        case ADD_TOKEN:
        case SUB_TOKEN:
            return true;
        default:
            return false;
    }
}

bool is_mul_operator(TokenType type){
    switch(type){
        case MUL_TOKEN:
        case DIV_TOKEN:
            return true;
        default:
            return false;
    }
}

bool is_operator(TokenType type){
    switch(type){
        case ADD_TOKEN:
        case SUB_TOKEN:
        case MUL_TOKEN:
        case DIV_TOKEN:
            return true;
        default:
            return false;
    }
}

TokenIter* token_iter_new(char* string){
    TokenIter* iter = malloc(sizeof(TokenIter)); 
    if(iter == NULL){
        return NULL;
    }
    iter->string = string;
    iter->error = false;
    iter->current = get_next(iter);
    iter->next = get_next(iter);
    return iter;
}

void print_token(Token* token){
    const char* type_string = token_type_to_string(token->type);
    switch(token->type){
        case INT_TOKEN:
            printf("<%s %d>", type_string, token->num);
            break;
        default:
            printf("<%s>", type_string);
    }
}
