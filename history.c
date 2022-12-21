#include "headers.h"
#include "macros.h"

void ADD_HISTORY(char *string, int *histcount)
{
    if (*histcount < 20)
    {
        if (strcmp(histarray[*histcount - 1], string) != 0)
        {
            strcpy(histarray[*histcount], string);
            *histcount = *histcount + 1;
        }
    }
    else
    {
        if (strcmp(histarray[*histcount - 1], string) != 0)
        {
            for (int i = 0; i < 19; i++)
            {
                strcpy(histarray[i], histarray[i + 1]);
            }
            strcpy(histarray[19], string);
            *histcount = 20;
        }
    }
    char path[SIZE];
    strcpy(path, Home);
    strcat(path, "/history.txt");
    FILE *f1 = fopen(path, "w");
    for (int i = 0; i < *histcount; i++)
    {
        char temp[SIZE];
        strcpy(temp, histarray[i]);
        fprintf(f1, "%s\n", temp);
    }
    fclose(f1);
}

void command_history(char **command, int n)
{
    if (n != 1)
    {
        printf("\033[0;31mInvalidcommand\033[0m\n");
    }
    else
    {
        int i = 0;
        char temp[SIZE];
        char path[SIZE];
        char display[20][SIZE];
        strcpy(path, Home);
        strcat(path, "/history.txt");
        FILE *fp1 = fopen(path, "r");
        while ((fscanf(fp1, "%[^\n]%*c", temp) != EOF))
        {
            strcpy(display[i], temp);
            i++;
        }
        if (i <= 10)
        {
            for (int j = 0; j < i; j++)
            {
                printf("%s\n", display[j]);
            }
        }
        else
        {
            for (int j = i - 10; j < i; j++)
            {
                printf("%s\n", display[j]);
            }
        }
        fclose(fp1);
    }
}