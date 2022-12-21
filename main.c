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
#include "pipe.h"
#include "jobs.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"
#include "signal.h"

int cpid = 0;
int child = -1;
int main()
{
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);
    root = NULL;
    tail = NULL;
    int s = 1;
    int histcount = 0;
    char sys_name[SIZE];
    char currdir[SIZE];
    char delimiter1[] = ";", delimiter2[] = "' ','\t'";
    struct passwd *p = getpwuid(getuid());
    strcpy(username, p->pw_name);
    gethostname(sys_name, SIZE);
    getcwd(Home, SIZE);
    int count = 0;
    char temp[SIZE];
    char path[SIZE];
    strcpy(path, Home);
    strcat(path, "/history.txt");
    FILE *fp1 = fopen(path, "a+");
    fclose(fp1);
    fp1 = fopen(path, "r");
    while ((fscanf(fp1, "%[^\n]%*c", temp) != EOF))
    {
        strcpy(histarray[count], temp);
        // printf("%s\n", temp);
        count++;
    }
    histcount = count;
    fclose(fp1);
    char cmnd[SIZE];
    while (1)
    {
        isredir = 0;
        int status;
        pid_t pid;
        while ((pid = (waitpid(-1, &status, WNOHANG))) > 0)
        {
            int sno;
            char pro[SIZE];
            data prevnode = NULL;
            for (data currnode = root; currnode != NULL; currnode = currnode->next)
            {
                if (currnode->pid == pid)
                {
                    sno = currnode->sno;
                    strcpy(pro, currnode->pName);

                    s--;
                    if (prevnode == NULL)
                    {
                        root = currnode->next;
                        free(currnode);
                    }
                    else if (currnode->next == NULL)
                    {
                        prevnode->next = NULL;
                        free(currnode);
                    }
                    else
                    {
                        prevnode->next = currnode->next;
                        free(currnode);
                    }

                    break;
                }
                prevnode = currnode;
            }
            for (data currnode = root; currnode != NULL; currnode = currnode->next)
            {
                if (currnode->sno > sno)
                {
                    currnode->sno = currnode->sno - 1;
                }
            }
            if (WIFEXITED(status))
            {
                fprintf(stderr, "\033[0;31m");
                fprintf(stderr, "%s with pid %d exited normally\n", pro, pid);
                fprintf(stderr, "\033[0m");
            }
            else
            {
                fprintf(stderr, "\033[0;31m");
                fprintf(stderr, "%s with pid %d exited abnormally\n", pro, pid);
                fprintf(stderr, "\033[0m");
            }
        }
        strcpy(previousdir, currdir);
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
        char inputstr[INPUTSIZE], *commands[COMMANDSIZE];
        // scanf("%[^\n]s",inputstr);
        if(scanf("%[^\n]%*c", inputstr)==EOF)
        {
            printf("\n");
            exit(0);
        }
        ADD_HISTORY(inputstr, &histcount);
        int i = 0, j = 0;
        char *temp = strtok(inputstr, delimiter1);
        for (i = 0; temp != NULL; i++)
        {
            commands[i] = temp;
            temp = strtok(NULL, delimiter1);
        }
        for (int k = 0; k < i; k++)
        {
            int flag1 = 0, flag2 = 0;
            for (int s = 0; s < strlen(commands[k]); s++)
            {
                if (commands[k][s] == '|')
                {
                    pipe_command(commands[k]);
                    flag2 = 1;
                    break;
                }
            }
            if (flag2 == 1)
            {
                break;
            }
            for (int s = 0; s < strlen(commands[k]); s++)
            {
                if (commands[k][s] == '>' || commands[k][s] == '<')
                {
                    redirection(commands[k]);
                    flag1 = 1;
                    isredir = 1;
                    break;
                }
            }
            if (flag1 == 1)
            {
                break;
            }
            j = 0;
            char temp3[SIZE];
            strcpy(temp3, commands[k]);
            char *temp1 = strtok(commands[k], delimiter2);
            char *command[20];
            for (j = 0; temp1 != NULL; j++)
            {
                command[j] = temp1;
                temp1 = strtok(NULL, delimiter2);
            }
            if (strcmp(command[0], "cd") == 0)
            {
                command_cd(command, j);
            }
            else if (strcmp(command[0], "echo") == 0)
            {
                command_echo(command, j);
            }
            else if (strcmp(command[0], "pwd") == 0)
            {
                command_pwd(command, j);
            }
            else if (strcmp(command[0], "ls") == 0)
            {
                command_ls(command, j);
            }
            else if (strcmp(command[0], "history") == 0)
            {
                command_history(command, j);
            }
            else if (strcmp(command[0], "pinfo") == 0)
            {
                command_pinfo(command, j);
            }
            else if (strcmp(command[0], "discover") == 0)
            {
                command_discover(command, j);
            }
            else if (strcmp(command[0], "jobs") == 0)
            {
                command_jobs(command, j);
            }
            else if (strcmp(command[0], "sig") == 0)
            {
                command_sig(command, j);
            }
            else if (strcmp(command[0], "fg") == 0)
            {
                command_fg(command, j, &s);
            }
            else if (strcmp(command[0], "bg") == 0)
            {
                command_bg(command, j);
            }
            else if (strcmp(command[0], "exit") == 0)
            {
                exit(0);
            }
            else
            {
                fg(j, temp3, &s);
            }
        }
    }
    return 0;
}
