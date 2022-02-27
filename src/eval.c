#include<stdlib.h>
#include"eval.h"
#include"tree.h"

// Fail in a function that returns a Result
#define FAIL return (Result){false, 0}
// Succeed in a function that returns a Result
#define SUCCEED(x) return (Result){true, x}
// Check if a result has !success and FAIL if it does
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

// div has a name collision
static int _div(int a, int b){
    return a / b;
}

static BinaryOp get_operator(NodeType type){
    switch(type){
        case ADD_NODE: return &add;
        case SUB_NODE: return &sub;
        case MUL_NODE: return &mul;
        case DIV_NODE: return &_div;
        default: return NULL;
    }
}

// evaluate a string in infix notation
Result eval(char* string){
    Node* node = tree_from_string(string);
    // TODO evaluate value
    free(node);
    SUCCEED(10);
}
