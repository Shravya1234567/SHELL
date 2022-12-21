#include "headers.h"
#include "macros.h"

void command_pwd(char **command, int n)
{
    char curdir[SIZE];
    getcwd(curdir, SIZE);
    printf("%s\n", curdir);
}