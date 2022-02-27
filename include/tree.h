#ifndef TREE_H
#define TREE_H

#include"token.h"

typedef enum{
    ADD_NODE,
    SUB_NODE,
    MUL_NODE,
    DIV_NODE,
    NEG_NODE,
    INT_NODE,
}NodeType;

typedef struct Node{
    NodeType type;
    union{
        // Used in case of binary op node
        // i.e. add sub mul div
        struct{ 
            struct Node* left;
            struct Node* right;
        };
        // used in neg node
        struct Node* next;
        // used in int node
        int num;
    };
}Node;

void print_node(Node* node);
Node* tree_from_string(char* string);

#endif // TREE_H

