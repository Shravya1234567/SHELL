#include "headers.h"
#include "macros.h"

void command_pinfo(char **command, int n)
{
    long int k = 0;
    int memory = 0;
    char pid[50];
    int p_id = getpid();
    char garbage[SIZE];
    char status;
    int p;
    char buffer[SIZE];
    int pgrp = -1;
    int tpgid = -1;
    if (n == 1)
    {
        sprintf(pid, "%d", p_id);
    }
    else
    {
        strcpy(pid, command[1]);
    }
    char path[SIZE];
    strcpy(path, "/proc/");
    strcat(path, pid);
    strcat(path, "/stat");
    FILE *fp1 = fopen(path, "r");

    if (fp1 == NULL)
    {
        perror("error");
    }
    else
    {
        fscanf(fp1,
               "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s "
               "%*s %*s %*s %*s %*s %d",
               &p, &status, &pgrp, &tpgid, &memory);
        printf("pid : %s\n", pid);
        printf("process status : %c", status);
        if(pgrp == tpgid)
        {
            printf("+\n");
        }
        else
        {
            printf("\n");
        }
        fclose(fp1);
        // char path1[SIZE];
        // strcpy(path1, "/proc/");
        // strcat(path1, pid);
        // strcat(path1, "/statm");
        // FILE *fp2 = fopen(path1, "r");
        // fscanf(fp2, "%ld", &memory);
        printf("memory : %d\n", memory);
        //fclose(fp2);
        char path2[SIZE];
        strcpy(path2, "/proc/");
        strcat(path2, pid);
        strcat(path2, "/exe");
        readlink(path2, buffer, SIZE);
        //printf("%s\n", buffer);
        int len = strlen(Home);
        char *relpath = strstr(buffer, Home);
        if (relpath != NULL)
        {
            relpath = relpath + len;
            char temp[SIZE];
            strcpy(temp, "~");
            strcat(temp, relpath);
            printf("executable path : %s\n", temp);
        }
        else
        {
            printf("executable path : %s\n", buffer);
        }
    }
}