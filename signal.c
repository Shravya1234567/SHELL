#include "headers.h"
#include "macros.h"

void ctrl_c(int sig)
{
    if (child != -1)
    {
        kill(child, SIGINT);
    }
    printf("\n");
    char currdir[SIZE];
    char sys_name[SIZE];
    gethostname(sys_name, SIZE);
    if (getcwd(currdir, SIZE) == NULL)
    {
        perror("ERROR IN CHECKING CURRENT DIRECTORY");
        exit(1);
    }
    else
    {
        char *relpath = strstr(currdir, Home);
        if (relpath != NULL)
        {
            relpath = relpath + strlen(Home);
            printf("\033[0;33m");
            printf("<%s@%s:~%s>", username, sys_name, relpath);
            printf("\033[0m");
        }
        else
        {
            printf("\033[0;33m");
            printf("<%s@%s:%s>", username, sys_name, currdir);
            printf("\033[0m");
        }
    }
    fflush(stdout);
    return;
}

void ctrl_z(int sig)
{
    char currdir[SIZE];
    char sys_name[SIZE];
    gethostname(sys_name, SIZE);
    printf("\n");
    if (getcwd(currdir, SIZE) == NULL)
    {
        perror("ERROR IN CHECKING CURRENT DIRECTORY");
        exit(1);
    }
    else
    {
        char *relpath = strstr(currdir, Home);
        if (relpath != NULL)
        {
            relpath = relpath + strlen(Home);
            printf("\033[0;33m");
            printf("<%s@%s:~%s>", username, sys_name, relpath);
            printf("\033[0m");
        }
        else
        {
            printf("\033[0;33m");
            printf("<%s@%s:%s>", username, sys_name, currdir);
            printf("\033[0m");
        }
    }
    fflush(stdout);
    return;
}
