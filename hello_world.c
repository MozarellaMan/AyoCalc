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
#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char const *argv[])
{
    puts("\nAyolisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to exit \nWhat will you lisp today? \n");

    while (1)
    {
        char* input = readline("ayolisp> ");

        add_history(input);

        printf("No you're a %s\n", input);

        free(input);
    }
    
    return 0;
}
