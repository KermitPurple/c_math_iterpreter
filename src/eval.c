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

static Result expression(TokenIter* iter);

static Result shortest_expression(TokenIter* iter){
    Result r;
    int num;
    switch(iter->current->type){
        case INT:
            num = iter->current->num;
            iterate(iter);
            SUCCEED(num);
        case SUB:
            iterate(iter);
            r = shortest_expression(iter);
            CHECK(r);
            SUCCEED(-r.value);
        case L_PAREN:
            iterate(iter);
            r = expression(iter);
            if(iter->current->type != R_PAREN){
                FAIL;
            }
            iterate(iter);
            return r;
        default: FAIL;
    }
}

static Result partial_expression(TokenIter* iter, int a){
    Result r;
    BinaryOp op = get_operator(iter->current->type);
    if(op == NULL){
        FAIL;
    }
    if(is_add_operator(iter->current->type)){
        iterate(iter);
        r = expression(iter);
        CHECK(r);
        SUCCEED(op(a, r.value));
    }else{  // mul op
        iterate(iter);
        r = shortest_expression(iter);
        CHECK(r);
        int mul_res = op(a, r.value);
        if(iter->next->type == END || iter->next->type == R_PAREN){
            SUCCEED(mul_res);
        }else{
            r = partial_expression(iter, mul_res);
        }
        return r;
    }
}

static Result expression(TokenIter* iter){
    if(iter->error){
        FAIL;
    }
    Result r = shortest_expression(iter);
    CHECK(r);
    if(iter->current->type != END && iter->current->type != R_PAREN){
        r = partial_expression(iter, r.value);
    }
    return r;
}

Result eval(char* string){
    TokenIter* iter = token_iter_new(string);
    Result result = expression(iter);
    free(iter);
    return result;
}
