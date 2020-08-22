#include "mpc-0.9.0/mpc.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#ifdef _WIN64
#include <string.h>
static char buffer[2048];
/* fake readline */
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}
void add_history(char* unused){}
#else 
#include <editline/readline.h>
#include <editline/history.h>
#endif

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

int eval_op(long x, char* op, long y){
    if(strcmp(op, "+") == 0){ return x + y;}
    if(strcmp(op, "-") == 0){ return x - y;}
    if(strcmp(op, "*") == 0){ return x * y;}
    if(strcmp(op, "/") == 0){ return x / y;}
    if(strcmp(op, "%") == 0){ return x % y;}
    return 0;
}

long eval(mpc_ast_t* tree) {

    /* if tagged as number, return directly */

    if(strstr(tree->tag, "number")){
        return atoi(tree->contents);
    }

    /* the operator is always the second child */

    char* op = tree->children[1]->contents;

    /* store child  */

    long x = eval(tree->children[2]);

    /* Iterate through remaining children and combine */
    int i = 3;
    while (strstr(tree->children[i]->tag, "expr"))
    {
        x = eval_op(x, op, eval(tree->children[i]));
        i++;
    }
    
    return x;
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


int main(int argc, char const *argv[]) {
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Ayolisp  = mpc_new("ayolisp");

    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+(\\.[0-9]*)?/;                  \
      operator : '+' | '-' | '*' | '/' | '%' ;            \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      ayolisp    : /^/ <operator> <expr>+ /$/ ;           \
    ",
    Number, Operator, Expr, Ayolisp);

    puts("\nAyolisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to exit \nWhat will you lisp today? \n");

    while (1)
    {
        char* input = readline("ayolisp> ");

        add_history(input);

        mpc_result_t r;

        if(mpc_parse("<stdin>", input, Ayolisp, &r)){
            long result = eval(r.output);
            mpc_ast_t* a = r.output;
            printf("%li\n", result);
            printf("max branch children %i\n", max_branch_children(a));
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }
    
    mpc_cleanup(4, Number, Operator, Expr, Ayolisp);
    return 0;
}
