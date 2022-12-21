#include "headers.h"
#include "macros.h"

void command_cd(char **command, int n)
{
    if (n == 2 && (strcmp(command[1], ".") == 0))
    {
        // continue
    }
    else if (n == 2 && (strcmp(command[1], "..") == 0))
    {
        char curdir[SIZE];
        char prevdir[SIZE];
        getcwd(curdir, SIZE);
        char k = '/';
        char *ptr = strrchr(curdir, k);
        int p = strlen(curdir);
        if (ptr)
        {
            int q = strlen(ptr);
            q = p - q;
            for (int i = 0; i <= q; i++)
            {
                prevdir[i] = curdir[i];
            }
            prevdir[q + 1] = '\0';
        }
        chdir(prevdir);
    }
    else if (n == 2 && (strcmp(command[1], "-") == 0))
    {
        chdir(previousdir);
        char *relpath = strstr(previousdir, Home);
        if (relpath)
        {
            relpath = relpath + strlen(Home);
            char Str[SIZE] = "/home/";
            strcat(Str, username);
            strcat(Str, relpath);
            printf("%s\n", Str);
        }
        else
        {
            printf("%s\n", previousdir);
        }
    }
    else if (n == 1 || (n == 2 && (strcmp(command[1], "~") == 0)))
    {
        chdir(Home);
    }
    else
    {
        if (chdir(command[1]) == 0)
        {
            // continue
        }
        else if (command[1][0] == '~')
        {
            char temp[SIZE];
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = command[1][i + 1];
            }
            temp[len - 1] = '\0';
            char Str[SIZE] = "/home/";
            strcat(Str, username);
            strcat(Str, temp);
            if (chdir(Str) != 0)
            {
                perror("Something went wrong");
            }
        }
        else if (command[1][0] == '.' && command[1][1] == '.')
        {
            char curdir[SIZE];
            char prevdir[SIZE];
            getcwd(curdir, SIZE);
            char k = '/';
            char *ptr = strrchr(curdir, k);
            int p = strlen(curdir);
            if (ptr)
            {
                int q = strlen(ptr);
                q = p - q;
                for (int i = 0; i <= q; i++)
                {
                    prevdir[i] = curdir[i];
                }
                prevdir[q + 1] = '\0';
            }
            char temp[SIZE];
            int len = strlen(command[1]);
            for (int i = 0; i < len - 2; i++)
            {
                temp[i] = command[1][i + 2];
            }
            temp[len - 2] = '\0';
    
            strcat(prevdir, temp);
            if (chdir(prevdir) != 0)
            {
                perror("\033[0;31mSomething went wrong\033[0m");
            }
        }
        else if (command[1][0] == '.')
        {
            char temp[SIZE];
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = command[1][i + 1];
            }
            temp[len - 1] = '\0';
            char Str[SIZE];
            getcwd(Str, SIZE);
            strcat(Str, temp);
            if (chdir(Str) != 0)
            {
                perror("\033[0;31mSomething went wrong\033[0m");
            }
        }
        else
        {
            perror("\033[0;31mSomething went wrong\033[0m");
        }
    }
}