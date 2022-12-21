#include "headers.h"
#include "macros.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "history.h"
#include "pinfo.h"
#include "discover.h"
#include "fgbg.h"
#include "ll.h"
#include "redirection.h"
#include "sig.h"
#include "jobs.h"

void exec_commands(char *str)
{
    char delimiter1[] = "' ','\t'";
    for (int s = 0; s < strlen(str); s++)
    {
        if (str[s] == '>' || str[s] == '<')
        {
            redirection(str);
            return;
        }
    }
    char *com[20];
    char *temp1 = strtok(str, delimiter1);
    int n;
    for (n = 0; temp1 != NULL; n++)
    {
        com[n] = temp1;
        temp1 = strtok(NULL, delimiter1);
    }
    com[n] = '\0';
    if (strcmp(com[0], "cd") == 0)
    {
        command_cd(com, n);
    }
    else if (strcmp(com[0], "echo") == 0)
    {
        command_echo(com, n);
    }
    else if (strcmp(com[0], "pwd") == 0)
    {
        command_pwd(com, n);
    }
    else if (strcmp(com[0], "ls") == 0)
    {
        command_ls(com, n);
    }
    else if (strcmp(com[0], "history") == 0)
    {
        command_history(com, n);
    }
    else if (strcmp(com[0], "pinfo") == 0)
    {
        command_pinfo(com, n);
    }
    else if (strcmp(com[0], "discover") == 0)
    {
        command_discover(com, n);
    }
    else if (strcmp(com[0], "jobs") == 0)
    {
        command_jobs(com, n);
    }
    else if (strcmp(com[0], "sig") == 0)
    {
        command_sig(com, n);
    }
    else if (strcmp(com[0], "exit") == 0)
    {
        exit(0);
    }
    else
    {
        int p = fork();
        if (p < 0)
        {
            perror("error");
        }
        else
        {
            if (p == 0)
            {
                if (execvp(com[0], com) == -1)
                {
                    perror("\033[0;31mError\033[0m");
                }
            }
            else if (p > 0)
            {
                wait(NULL);
            }
        }
    }
}

void pipe_command(char *command)
{
    int std_out = dup(1);
    if (std_out < 0)
    {
        perror("\033[0;31mError in dup\033[0m");
    }
    int std_in = dup(0);
    if (std_in < 0)
    {
        perror("\033[0;31mError in dup\033[0m");
    }
    char delimiter[] = "|";
    char inputstr[SIZE];
    strcpy(inputstr, command);
    char *temp = strtok(inputstr, delimiter);
    char *comm[SIZE];
    int i;
    for (i = 0; temp != NULL; i++)
    {
        comm[i] = temp;
        temp = strtok(NULL, delimiter);
    }
    comm[i] = '\0';
    int pipedes[i - 1][2];
    if (pipe(pipedes[0]) < 0)
    {
        perror("\033[0;31mError in pipe sys call\033[0m");
    }
    if (dup2(pipedes[0][1], 1) < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    exec_commands(comm[0]);
    if (close(pipedes[0][1]) < 0)
    {
        perror("\033[0;31mError in closing\033[0m");
    }
    int j;
    for (j = 1; j < i - 1; j++)
    {
        if (pipe(pipedes[j]) < 0)
        {
            perror("\033[0;31mError in pipe sys call\033[0m");
        }
        if (dup2(pipedes[j - 1][0], 0) < 0)
        {
            perror("\033[0;31mError in dup2\033[0m");
        }
        if (dup2(pipedes[j][1], 1) < 0)
        {
            perror("\033[0;31mError in dup2\033[0m");
        }
        exec_commands(comm[j]);
        if (close(pipedes[j - 1][0]) < 0)
        {
            perror("\033[0;31mError in closing\033[0m");
        }
        if (close(pipedes[j][1]) < 0)
        {
            perror("\033[0;31mError in closing\033[0m");
        }
    }
    if (dup2(pipedes[j - 1][0], 0) < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    if (dup2(std_out, 1) < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    exec_commands(comm[j]);
    if (dup2(std_in, 0) < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    if (close(pipedes[j - 1][0]) < 0)
    {
        perror("\033[0;31mError in closing\033[0m");
    }
    if (close(std_in) < 0)
    {
        perror("\033[0;31mError in closing\033[0m");
    }
    if (close(std_out) < 0)
    {
        perror("\033[0;31mError in closing\033[0m");
    }
}