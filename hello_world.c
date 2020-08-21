#include <stdio.h>

static char input[2048];

int main(int argc, char const *argv[])
{
    puts("Ayolisp Version 0.0.0.0.1");
    puts("Press Ctrl+c to exit \n");

    while (1)
    {
        fputs("ayolisp> ", stdout);

        fgets(input, 2048, stdin);

        printf("No you're a %s", input);
    }
    
    return 0;
}
