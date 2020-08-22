#include "mpc-0.9.0/mpc.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
int number_of_nodes(mpc_ast_t* tree) {
    if(tree->children_num == 0) { return 1; }
    if(tree->children_num >= 1) {
        int total = 1;
        for (int i = 0; i < tree->children_num; i++)
        {
            total += number_of_nodes(tree->children[i]);
        }
        return total;
    }
    return 0;
}

int max_branch_children(mpc_ast_t* tree) {
    if(tree->children_num == 0) { return 0; }
    if(tree->children_num >= 1) {
        int max = 0;
        for (int i = 0; i < tree->children_num; i++)
        {
            max = MAX(max_branch_children(tree->children[i]), max);
        }
        return 1+max;
    }
    return 0;
}

int number_of_branches(mpc_ast_t* tree) {
    if(tree->children_num == 0) { return 0; }
    if(tree->children_num >= 1) {
        int total = tree->children_num;
        for (int i = 0; i < tree->children_num; i++)
        {
            total += number_of_branches(tree->children[i]);
        }
        return total;
    }
    return 0;
}

void debug_tree(mpc_ast_t* a) {
    printf("Tag: %s\n", a->tag);
    printf("Contents: %s\n", a->contents);
    printf("Number of children: %i\n", a->children_num);
    mpc_ast_t* c0 = a->children[0];
    printf("First Child Tag: %s\n", c0->tag);
    printf("First Child Contents: %s\n", c0->contents);
    printf("First Child Number of children: %i\n",
    c0->children_num);
    printf("number of tree children %i\n", number_of_nodes(a));
    printf("number of branches: %i\n", number_of_branches(a));
}