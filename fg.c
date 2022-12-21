#include "headers.h"
#include "macros.h"
#include "ll.h"

void command_fg(char **command, int n, int *s)
{
    int flag = 0;
    int jobnum;
    if (n == 2)
    {
        int status;
        int i = atoi(command[1]);
        data currnode;
        data prevnode = NULL;
        for (currnode = root; currnode != NULL; currnode = currnode->next)
        {
            if (currnode->sno == i)
            {
                jobnum = currnode->sno;
                flag = 1;
                break;
            }
            prevnode = currnode;
        }
        if (flag == 0)
        {
            printf("No job with given job num\n");
        }
        else
        {
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, currnode->pid);
            if (kill(currnode->pid, SIGCONT) < 0)
            {
                perror("Error");
            }
            waitpid(currnode->pid, &status, WUNTRACED);
            if (WIFSTOPPED(status))
            {
                kill(currnode->pid, SIGSTOP);
            }
            else
            {
                *s = *s - 1;
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
                for (data currnode1 = root; currnode1 != NULL; currnode1 = currnode1->next)
                {
                    if (currnode1->sno > jobnum)
                    {
                        currnode1->sno = currnode1->sno - 1;
                    }
                }
            }
            tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
            signal(SIGTTIN, SIG_DFL); 
            signal(SIGTTOU, SIG_DFL); 
        }
    }
    else
    {
        perror("Invalid command");
        return;
    }
}