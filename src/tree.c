#include<stdlib.h>
#include<stdio.h>
#include"tree.h"

#define CHECK_NULL(x) if(x == NULL) return NULL

// forward declaration to use expression
static Node* expression(TokenIter* iter);

// return the shortest expression it can without breaking groupings like parentheses
static Node* shortest_expression(TokenIter* iter){
    int num;
    Node* node = NULL;
    switch(iter->current->type){
        case INT_TOKEN:
            node = malloc(sizeof(Node));
            node->type = INT_NODE;
            node->num = iter->current->num;
            iterate(iter);
            break;
        case SUB_TOKEN:
            node = malloc(sizeof(Node));
            node->type = NEG_NODE;
            iterate(iter);
            node->next = shortest_expression(iter);
            break;
        case L_PAREN_TOKEN:
            iterate(iter);
            node = expression(iter);
            if(iter->current->type != R_PAREN_TOKEN){
                return NULL;
            }
            iterate(iter);
            break;
        default: 
            break;
    }
    return node;
}

// get the operator and evaluate the second operand
static Node* partial_expression(TokenIter* iter, Node* left){
    CHECK_NULL(left);
    Node* node = malloc(sizeof(Node));
    CHECK_NULL(node);
    node->left = left;
    TokenType op = iter->current->type;
    switch(op){
        case ADD_TOKEN:
            node->type = ADD_NODE;
            break;
        case SUB_TOKEN:
            node->type = SUB_NODE;
            break;
        case MUL_TOKEN:
            node->type = MUL_NODE;
            break;
        case DIV_TOKEN:
            node->type = DIV_NODE;
            break;
        case END_TOKEN:
        case L_PAREN_TOKEN:
            free(node);
            return left;
        default:
            free(node);
            return NULL;
    }
    iterate(iter);
    if(is_operator(iter->next->type) && get_precedence(iter->next->type) > get_precedence(op)){
        node->right = expression(iter);
        CHECK_NULL(node->right);
    }else{
        node->right = shortest_expression(iter);
        CHECK_NULL(node->right);
        node = partial_expression(iter, node);
    }
    return node;
}

// get the longest expression possible
static Node* expression(TokenIter* iter){
    if(iter->error){
        return NULL;
    }
    Node* node = shortest_expression(iter);
    CHECK_NULL(node);
    return partial_expression(iter, node);
}

void print_node(Node* node){
    if(node == NULL){
        printf("NULL");
        return;
    }
    switch(node->type){
        case ADD_NODE:
            printf("<ADD ");
            print_node(node->left);
            printf(" ");
            print_node(node->right);
            printf(">");
            break;
        case SUB_NODE:
            printf("<SUB ");
            print_node(node->left);
            printf(" ");
            print_node(node->right);
            printf(">");
            break;
        case MUL_NODE:
            printf("<MUL ");
            print_node(node->left);
            printf(" ");
            print_node(node->right);
            printf(">");
            break;
        case DIV_NODE:
            printf("<DIV ");
            print_node(node->left);
            printf(" ");
            print_node(node->right);
            printf(">");
            break;
        case NEG_NODE:
            printf("<NEG ");
            print_node(node->next);
            printf(">");
            break;
        case INT_NODE:
            printf("%d", node->num);
            break;
    }
}

void free_node(Node* node){
    if(node == NULL){
        return;
    }
    switch(node->type){
        case ADD_NODE:
        case SUB_NODE:
        case MUL_NODE:
        case DIV_NODE:
            free_node(node->left);
            free_node(node->right);
            break;
        case NEG_NODE:
            free_node(node->next);
            break;
        default: break;
    }
    free(node);
}

Node* tree_from_string(char* string){
    TokenIter* iter = token_iter_new(string);
#ifdef DEBUG
    printf("TOKENS: ");
#endif // DEBUG
    Node* node = expression(iter);
#ifdef DEBUG
    printf("\nTREE: ");
    print_node(node);
    putchar('\n');
#endif // DEBUG
    free(iter);
    return node;
}
