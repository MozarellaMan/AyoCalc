#include "mpc-0.9.0/mpc.h"
#include "altype.c"
#include "util.c"
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

alval eval_op(alval x, char* op, alval y) {

      /* If either value is an error return it */
    if (x.type == ALVAL_ERR) { return x; }
    if (y.type == ALVAL_ERR) { return y; }

    /* Otherwise do maths on the number values */
    if(strcmp(op, "+") == 0){ return alval_num(x.num + y.num);}
    if(strcmp(op, "-") == 0){ return alval_num(x.num - y.num);;}
    if(strcmp(op, "*") == 0){ return alval_num(x.num * y.num);}
    if(strcmp(op, "^") == 0){ return alval_num(pow(x.num,  y.num));}
    if(strcmp(op, "max") == 0){ return alval_num(fmax(x.num, y.num));}
    if(strcmp(op, "min") == 0){ return alval_num(fmax(x.num, y.num));}


     /* division by zero handling */
    if(strcmp(op, "/") == 0) { 
        return y.num == 0.0
            ? alval_err(ALERR_DIV_ZERO) 
            : alval_num(x.num / y.num);
    }
    if(strcmp(op, "%") == 0){ 
        return y.num == 0.0 
            ? alval_err(ALERR_DIV_ZERO)
            : alval_num(fmod(x.num, y.num));
    }

    return alval_err(ALERR_BAD_OP);
}

alval eval_op_single(char* op, alval x){
    if (x.type == ALVAL_ERR) { return x; }
    if(strcmp(op, "-") == 0){ return alval_num(x.num * -1);}
    return x;
}

alval eval(mpc_ast_t* tree) {

    /* if tagged as number, return directly */
    if(strstr(tree->tag, "number")){
        /* Check if there is some error in conversion */
        errno = 0;
        double x = strtod(tree->contents, NULL);
        return errno != ERANGE ? alval_num(x) : alval_err(ALERR_BAD_NUM);
    }
    /* the operator is always the second child */
    char* op = tree->children[1]->contents;
    /* store child  */
    alval x = eval(tree->children[2]);
    /* Iterate through remaining children and combine */
    int i = 3;
    if(strstr(tree->children[i]->tag, "expr")) {
        while (strstr(tree->children[i]->tag, "expr")) {
            x = eval_op(x, op, eval(tree->children[i]));
            i++;
        }
    }  else {
        return eval_op_single(op,x);
    }

    return x;
}

int main(int argc, char const *argv[]) {
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Ayocalc  = mpc_new("ayolisp");

    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                                   \
      number   : /-?[0-9]+(\\.[0-9]*)?/;                                \
      operator : '+' | '-' | '*' | '/' | '%' | '^' | \"max\" | \"min\" | \"avg\"; \
      expr     : <number> | '(' <operator> <expr>+ ')' ;                \
      ayolisp    : /^/ <operator> <expr>+ /$/ ;                         \
    ",
    Number, Operator, Expr, Ayocalc);

    puts("\nAyoCalc Version 0.1");
    puts("Press Ctrl+C to exit \nWhat will you calculate today? \n");
    while (1)
    {
        char* input = readline("ayocalc> ");
        add_history(input);
        mpc_result_t r;

        if(mpc_parse("<stdin>", input, Ayocalc, &r)){
            alval result = eval(r.output);
            alval_println(result);
            mpc_ast_t* a = r.output;
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }
    
    mpc_cleanup(4, Number, Operator, Expr, Ayocalc);
    return 0;
}
