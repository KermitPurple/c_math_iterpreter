#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"
#include"eval.h"

int main(){
    char* line = NULL;
    size_t capacity = 0;
    while(1){
        printf("calc> ");
        if(
            getline(&line, &capacity, stdin) == EOF ||
            strcmp(line, "quit\n") == 0 ||
            strcmp(line, "q\n") == 0
        ){
            break;
        }
        line[strlen(line) - 1] = '\0'; // get rid of newline
        tree_from_string(line);
        putchar('\n');
        Result r = eval(line);
        if(r.success){
            printf("%s = %d\n", line, r.value);
        }else{
            printf("Invalid expression \"%s\"\n", line);
        }
    }
    free(line);
    return 0;
}
