#include "headers.h"
#include "macros.h"

void command_echo(char **command, int n)
{
    for (int i = 1; i < n; i++)
    {
        printf("%s ", command[i]);
    }
    printf("\n");
}