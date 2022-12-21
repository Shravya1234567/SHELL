#include "headers.h"
#include "macros.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "history.h"
#include "pinfo.h"
#include "discover.h"
#include "fg.h"
#include "ll.h"
#include "jobs.h"
#include "sig.h"

void redirection(char *command)
{
    char delimiter[] = "' ','\t'";
    int f1 = 0, f2 = 0, f3 = 0;
    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '>' && command[i + 1] == '>')
        {
            f1 = 1;
        }
        else if (command[i] == '>')
        {
            f2 = 1;
        }
        else if (command[i] == '<')
        {
            f3 = 1;
        }
    }
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
    char *inputfile, *outputfile;
    char *out[2], *in[2];
    char *com[20];
    int j = 0;
    if (f2 == 1 && f3 == 0)
    {
        char temp[SIZE];
        strcpy(temp, command);
        out[0] = strtok(temp, ">");
        out[1] = strtok(NULL, ">");
        char *token = strtok(out[0], delimiter);
        for (j = 0; token != NULL; j++)
        {
            com[j] = token;
            token = strtok(NULL, delimiter);
        }
        com[j] = '\0';
        outputfile = strtok(out[1], delimiter);
    }
    else if (f3 == 1 && f2 == 0)
    {
        char temp[SIZE];
        strcpy(temp, command);
        in[0] = strtok(temp, "<");
        in[1] = strtok(NULL, "<");
        char *token = strtok(in[0], delimiter);
        for (j = 0; token != NULL; j++)
        {
            com[j] = token;
            token = strtok(NULL, delimiter);
        }
        inputfile = strtok(in[1], delimiter);
        com[j] = '\0';
    }
    else
    {
        char temp[SIZE];
        strcpy(temp, command);
        out[0] = strtok(temp, ">");
        out[1] = strtok(NULL, ">");
        in[0] = strtok(out[0], "<");
        in[1] = strtok(NULL, "<");
        char *token = strtok(in[0], delimiter);
        for (j = 0; token != NULL; j++)
        {
            com[j] = token;
            token = strtok(NULL, delimiter);
        }
        outputfile = strtok(out[1], delimiter);
        inputfile = strtok(in[1], delimiter);
        com[j] = '\0';
    }
    if (f3 == 1)
    {
        int fd_in = open(inputfile, O_RDONLY);
        if (fd_in < 0)
        {
            perror("\033[0;31mError opening input file\033[0m");
            return;
        }
        if (dup2(fd_in, 0) < 0)
        {
            perror("\033[0;31mError in dup2\033[0m");
        }
        if (close(fd_in) < 0)
        {
            perror("\033[0;31mError in closing input file\033[0m");
        }
    }
    if (f1 == 1)
    {
        int fd_out = open(outputfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_out < 0)
        {
            perror("\033[0;31mError opening outputfile\033[0m");
            return;
        }
        if (dup2(fd_out, 1) < 0)
        {
            perror("\033[0;31mError in dup2\033[0m");
        }
        if (close(fd_out) < 0)
        {
            perror("\033[0;31mError in closing output file\033[0m");
        }
    }
    else if (f1 == 0 && f2 == 1)
    {
        int fd_out = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0)
        {
            perror("\033[0;31mError opening outputfile\033[0m");
            return;
        }
        if (dup2(fd_out, 1) < 0)
        {
            perror("\033[0;31mError in dup2\033[0m");
        }
        if (close(fd_out) < 0)
        {
            perror("\033[0;31mError in closing output file\033[0m");
        }
    }
    if (strcmp(com[0], "cd") == 0)
    {
        command_cd(com, j);
    }
    else if (strcmp(com[0], "echo") == 0)
    {
        command_echo(com, j);
    }
    else if (strcmp(com[0], "pwd") == 0)
    {
        command_pwd(com, j);
    }
    else if (strcmp(com[0], "ls") == 0)
    {
        command_ls(com, j);
    }
    else if (strcmp(com[0], "history") == 0)
    {
        command_history(com, j);
    }
    else if (strcmp(com[0], "pinfo") == 0)
    {
        command_pinfo(com, j);
    }
    else if (strcmp(com[0], "discover") == 0)
    {
        command_discover(com, j);
    }
    else if (strcmp(com[0], "jobs") == 0)
    {
        command_jobs(com, j);
    }
    else if (strcmp(com[0], "sig") == 0)
    {
        command_sig(com, j);
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
            perror("\033[0;31mError\033[0m");
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
    if (dup2(std_in, 0) < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    if (dup2(std_out, 1) < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    if (close(std_in) < 0)
    {
        perror("\033[0;31mError in closing output file\033[0m");
    }
    if (close(std_out) < 0)
    {
        perror("\033[0;31mError in closing output file\033[0m");
    }
}