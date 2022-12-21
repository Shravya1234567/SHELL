#include "headers.h"
#include "macros.h"
#include "ll.h"

void bubblesort()
{
    int swap_count = 0;
    data temp;
    data ptr = NULL;
    if (root == NULL)
    {
        return;
    }
    do
    {
        swap_count = 0;
        temp = root;
        while (temp->next != ptr)
        {
            if (strcasecmp(temp->procName, temp->next->procName) > 0)
            {
                char str[SIZE];
                char str1[SIZE];
                int d;
                strcpy(str1, temp->procName);
                strcpy(temp->procName, temp->next->procName);
                strcpy(temp->next->procName, str1);
                strcpy(str, temp->pName);
                strcpy(temp->pName, temp->next->pName);
                strcpy(temp->next->pName, str);
                d = temp->pid;
                temp->pid = temp->next->pid;
                temp->next->pid = d;
                d = temp->sno;
                temp->sno = temp->next->sno;
                temp->next->sno = d;
                swap_count = 1;
            }
            temp = temp->next;
        }
        ptr = temp;
    } while (swap_count);
}

void jobs()
{
    for (data currnode = root; currnode != NULL; currnode = currnode->next)
    {
        char pid[50];
        long int k = 0;
        char garbage[SIZE];
        char status;
        int p_id = currnode->pid;
        sprintf(pid, "%d", p_id);
        char path[SIZE];
        strcpy(path, "/proc/");
        strcat(path, pid);
        strcat(path, "/stat");
        FILE *fp1 = fopen(path, "r");
        if (fp1 == NULL)
        {
            perror("Error");
        }
        else
        {
            fscanf(fp1, "%ld", &k);
            fscanf(fp1, "%s", garbage);
            fscanf(fp1, " %c", &status);
            if (status == 'T')
            {
                printf("[%d] Stopped %s [%d]\n", currnode->sno, currnode->procName, currnode->pid);
            }
            else
            {
                printf("[%d] Running %s [%d]\n", currnode->sno, currnode->procName, currnode->pid);
            }
            fclose(fp1);
        }
    }
}

void jobs_r()
{
    for (data currnode = root; currnode != NULL; currnode = currnode->next)
    {
        char pid[50];
        long int k = 0;
        char garbage[SIZE];
        char status;
        int p_id = currnode->pid;
        sprintf(pid, "%d", p_id);
        char path[SIZE];
        strcpy(path, "/proc/");
        strcat(path, pid);
        strcat(path, "/stat");
        FILE *fp1 = fopen(path, "r");
        if (fp1 == NULL)
        {
            perror("Error");
        }
        else
        {
            fscanf(fp1, "%ld", &k);
            fscanf(fp1, "%s", garbage);
            fscanf(fp1, " %c", &status);
            if (status == 'T')
            {
                // printf("[%d] Stopped %s [%d]\n", currnode->sno, currnode->pName, currnode->pid);
            }
            else
            {
                printf("[%d] Running %s [%d]\n", currnode->sno, currnode->procName, currnode->pid);
            }
            fclose(fp1);
        }
    }
}

void jobs_s()
{
    for (data currnode = root; currnode != NULL; currnode = currnode->next)
    {
        char pid[50];
        long int k = 0;
        char garbage[SIZE];
        char status;
        int p_id = currnode->pid;
        sprintf(pid, "%d", p_id);
        char path[SIZE];
        strcpy(path, "/proc/");
        strcat(path, pid);
        strcat(path, "/stat");
        FILE *fp1 = fopen(path, "r");
        if (fp1 == NULL)
        {
            perror("Error");
        }
        else
        {
            fscanf(fp1, "%ld", &k);
            fscanf(fp1, "%s", garbage);
            fscanf(fp1, " %c", &status);
            if (status == 'T')
            {
                printf("[%d] Stopped %s [%d]\n", currnode->sno, currnode->procName, currnode->pid);
            }
            fclose(fp1);
        }
    }
}

void command_jobs(char **command, int n)
{
    bubblesort();
    if (n == 1)
    {
        jobs();
    }
    else if (n == 2 && strcmp(command[1], "-r") == 0)
    {
        jobs_r();
    }
    else if (n == 2 && strcmp(command[1], "-s") == 0)
    {
        jobs_s();
    }
    else
    {
        printf("\033[0;32m");
        printf("wrong command\n");
        printf("\033[0m");
    }
}