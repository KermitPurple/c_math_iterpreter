#include<stdlib.h>
#include"eval.h"

#define FAIL return (Result){false, 0}
#define SUCCEED(x) return (Result){true, x}
#define CHECK(x) if(!x.success) FAIL

typedef int (*BinaryOp)(int, int);

static int add(int a, int b){
    return a + b;
}

static int sub(int a, int b){
    return a - b;
}

static int mul(int a, int b){
    return a * b;
}

static int _div(int a, int b){
    return a / b;
}

static BinaryOp get_operator(TokenType type){
    switch(type){
        case ADD: return &add;
        case SUB: return &sub;
        case MUL: return &mul;
        case DIV: return &_div;
        default: return NULL;
    }
}

static Result expression(TokenIter* iter){
    if(iter->error){
        FAIL;
    }
    Result result;
    int a;
    switch(iter->current->type){
        case SUB:
            iterate(iter);
            result = expression(iter);
            CHECK(result);
            SUCCEED(-result.value);
        case L_PAREN:
            iterate(iter);
            result = expression(iter);
            if(iter->next->type != R_PAREN){
                FAIL;
            }
            iterate(iter);
            return result;
        case INT:
            a = iter->current->num;
            if(is_operator(iter->next->type)){
                iterate(iter);
                BinaryOp op = get_operator(iter->current->type);
                if(op == NULL){
                    FAIL;
                }
                iterate(iter);
                result = expression(iter);
                CHECK(result);
                SUCCEED(op(a, result.value));
            }else if(iter->next->type != END){
                FAIL;
            }
            SUCCEED(a);
        default:
            FAIL;
    }
}

Result eval(char* string){
    TokenIter* iter = token_iter_new(string);
    Result result = expression(iter);
    free(iter);
    return result;
}
