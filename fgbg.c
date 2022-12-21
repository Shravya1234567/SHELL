#include "headers.h"
#include "macros.h"
#include "ll.h"

void fg(int n, char *input, int *s)
{
    char delimiter[] = "&", delimiter2[] = "' ','\t'";
    char *c1[SIZE];
    int i = 0, j = 0;
    char temp3[SIZE];
    strcpy(temp3, input);
    char *temp = strtok(input, delimiter);
    // printf("%s\n", input);
    for (i = 0; temp != NULL; i++)
    {
        c1[i] = temp;
        temp = strtok(NULL, delimiter);
    }
    for (int k = 0; k < i; k++)
    {
        j = 0;
        char copy[SIZE];
        strcpy(copy, c1[k]);
        char *temp1 = strtok(c1[k], delimiter2);
        char *c2[20];
        for (j = 0; temp1 != NULL; j++)
        {
            c2[j] = temp1;
            temp1 = strtok(NULL, delimiter2);
        }
        c2[j] = NULL;
        if (k != i - 1)
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
                    setpgid(0, 0);
                    if (execvp(c2[0], c2) == -1)
                    {
                        perror("\033[0;31mError\033[0m");
                    }
                }
                else if (p > 0)
                {
                    int status;
                    setpgid(p, 0);
                    fprintf(stderr, "[%d] %d\n", *s, p);
                    // printf("%d\n",p);
                    *s = *s + 1;
                    data temp;
                    temp = (data)malloc(sizeof(struct pData));
                    temp->pName = (char *)malloc(strlen(c2[0]) + 1);
                    temp->procName = (char *)malloc(strlen(copy) + 1);
                    strcpy(temp->pName, c2[0]);
                    strcpy(temp->procName, copy);
                    temp->pid = p;
                    temp->sno = *s - 1;
                    temp->next = NULL;
                    if (root == NULL)
                    {
                        root = temp;
                        tail = temp;
                    }
                    else
                    {
                        tail->next = temp;
                        tail = temp;
                    }
                    setpgid(getpid(), 0);
                    tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
                }
            }
        }
        if (k == i - 1)
        {
            int len = strlen(temp3);
            if (temp3[len - 1] == '&')
            {
                int cid;
                int p = fork();
                if (p < 0)
                {
                    perror("\033[0;31mError\033[0m");
                }
                else
                {
                    if (p == 0)
                    {
                        setpgid(0, 0);
                        cid = getpid();
                        if (execvp(c2[0], c2) == -1)
                        {
                            perror("\033[0;31mError\033[0m");
                        }
                    }
                    else if (p > 0)
                    {
                        int status;
                        setpgid(p, 0);
                        fprintf(stderr, "[%d] %d\n", *s, p);
                        // printf("%d\n", p);
                        *s = *s + 1;
                        data temp;
                        temp = (data)malloc(sizeof(struct pData));
                        temp->pName = (char *)malloc(strlen(c2[0]) + 1);
                        temp->procName = (char *)malloc(strlen(copy) + 1);
                        strcpy(temp->pName, c2[0]);
                        strcpy(temp->procName, copy);
                        temp->pid = p;
                        temp->sno = *s - 1;
                        temp->next = NULL;
                        if (root == NULL)
                        {
                            root = temp;
                            tail = temp;
                        }
                        else
                        {
                            tail->next = temp;
                            tail = temp;
                        }
                        setpgid(getpid(), 0);
                        tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
                    }
                }
            }
            else
            {
                int cid;
                int p = fork();
                time_t time1, time2;
                time1 = time(0);
                if (p < 0)
                {
                    perror("\033[0;31mError\033[0m");
                }
                else
                {
                    if (p == 0)
                    {
                        cid = getpid();
                        setpgid(0, 0);
                        if (execvp(c2[0], c2) == -1)
                        {
                            perror("\033[0;31mError\033[0m");
                        }
                    }
                    else if (p > 0)
                    {
                        // printf("%d\n", p);
                        // wait(NULL);
                        int status;
                        setpgid(p, 0);
                        signal(SIGTTIN, SIG_IGN);
                        signal(SIGTTOU, SIG_IGN);
                        tcsetpgrp(STDIN_FILENO, p);
                        child = p;
                        waitpid(p, &status, WUNTRACED);
                        if (WIFSTOPPED(status))
                        {
                            *s = *s + 1;
                            data temp;
                            temp = (data)malloc(sizeof(struct pData));
                            temp->pName = (char *)malloc(strlen(c2[0]) + 1);
                            temp->procName = (char *)malloc(strlen(copy) + 1);
                            strcpy(temp->pName, c2[0]);
                            strcpy(temp->procName, copy);
                            temp->pid = p;
                            temp->sno = *s - 1;
                            temp->next = NULL;
                            if (root == NULL)
                            {
                                root = temp;
                                tail = temp;
                            }
                            else
                            {
                                tail->next = temp;
                                tail = temp;
                            }
                            kill(p,SIGSTOP);
                        }
                        child = -1;
                        time2 = time(0);
                        if ((time2 - time1) >= 1)
                        {
                            fprintf(stderr, "\033[0;31m");
                            fprintf(stderr, "%s took %ld seconds to execute \n", c2[0], time2 - time1);
                            fprintf(stderr, "\033[0m");
                        }
                        tcsetpgrp(STDIN_FILENO,getpgid(getpid()));
                        signal(SIGTTIN, SIG_DFL);
                        signal(SIGTTOU,SIG_DFL);
                    }
                }
            }
        }
    }
}