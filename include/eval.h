#ifndef EVAL_H
#define EVAL_H value

#include"token.h"

typedef struct{
    bool success;
    int value;
}Result;

Result eval(char* string);

#endif // EVAL_H
