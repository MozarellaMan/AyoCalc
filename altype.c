#include <stdio.h>
/* Create Enumeration of Possible alval Types */
enum { ALVAL_NUM, ALVAL_ERR };

/* Create Enumeration of Possible Error Types */
enum { ALERR_DIV_ZERO, ALERR_BAD_OP, ALERR_BAD_NUM };

typedef struct {
    int type;
    double num;
    int err;
} alval;

alval alval_num(double x){
    alval v;
    v.type = ALVAL_NUM;
    v.num = x;
    return v;
}


alval alval_err(int x){
    alval v;
    v.type = ALVAL_ERR;
    v.err = x;
    return v;
}

/* Print an "lval" */
void alval_print(alval v) {
    switch(v.type){

        /* In the case the type is a number print it */
        /* Then 'break' out of the switch. */
        case ALVAL_NUM: printf("%g", v.num); break;

        /* In the case the type is an error */
        case ALVAL_ERR:
            /* Check what type of error it is and print it */
            if (v.err == ALERR_DIV_ZERO)
            {
                printf("Error: You cannot divide by 0.");
            }
            if (v.err == ALERR_BAD_OP)
            {
                printf("Error: Invalid operator.");
            }
            if (v.err == ALERR_BAD_NUM)
            {
                printf("Error: Invalid number.");
            }
            
        break;
    }
}

/* Print an "alval" followed by a newline */
void alval_println(alval v) { alval_print(v); putchar('\n'); }