#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"token.h"

int main(){
    char* line = NULL;
    size_t capacity = 0;
    while(1){
        printf("calc> ");
        if(getline(&line, &capacity, stdin) == EOF){
            break;
        }
        if(strcmp(line, "quit\n") == 0 || strcmp(line, "q\n") == 0){
            break;
        }
        TokenIter* iter = token_iter_new(line);
        do{
            print_token(iter->current);
            putchar('\n');
        }while(iterate(iter));
        free(iter);
    }
    free(line);
    return 0;
}
