#include "headers.h"
#include "macros.h"

int discover(char *directory)
{
    struct dirent *d;
    DIR *dr;
    char curdir[SIZE];
    getcwd(curdir, SIZE);
    dr = opendir(directory);
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            char path[SIZE];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, d->d_name);
            // printf("%s\n", path);
            struct stat kappa = {0};
            if (stat(path, &kappa) == 0)
            {
                if (S_ISREG(kappa.st_mode))
                {
                    int len = strlen(curdir);
                    char *relpath = strstr(path, curdir);
                    // printf("%s\n",curdir);
                    if (relpath != NULL)
                    {
                        relpath = relpath + len;
                        printf(".%s\n", relpath);
                    }
                    else
                    {
                        printf("%s\n", path);
                    }
                }
                else if (S_ISDIR(kappa.st_mode))
                {
                    int len = strlen(curdir);
                    char *relpath = strstr(path, curdir);
                    if (relpath != NULL)
                    {
                        relpath = relpath + len;
                        int len1 = strlen(relpath);
                        if (relpath[len1 - 1] != '.')
                        {
                            printf(".%s\n", relpath);
                            discover(path);
                        }
                    }
                    else
                    {
                        printf("%s\n", path);
                    }
                }
            }
            else
            {
                perror("\033[0;31mError\033[0m");
            }
        }
        closedir(dr);
        return 0;
    }
    else
    {
        // perror("error");
        return 1;
    }
}

void discover_f(char *directory)
{
    struct dirent *d;
    DIR *dr;
    char curdir[SIZE];
    getcwd(curdir, SIZE);
    dr = opendir(directory);
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            char path[SIZE];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, d->d_name);
            // printf("%s\n", path);
            struct stat kappa = {0};
            if (stat(path, &kappa) == 0)
            {
                if (S_ISREG(kappa.st_mode))
                {
                    int len = strlen(curdir);
                    char *relpath = strstr(path, curdir);
                    // printf("%s\n",curdir);
                    if (relpath != NULL)
                    {
                        relpath = relpath + len;
                        printf(".%s\n", relpath);
                    }
                    else
                    {
                        printf("%s\n", path);
                    }
                }
            }
            else
            {
                perror("\033[0;31mError\033[0m");
            }
        }
        closedir(dr);
    }
    else
    {
        perror("\033[0;31mError\033[0m");
    }
}

void discover_d(char *directory)
{
    struct dirent *d;
    DIR *dr;
    char curdir[SIZE];
    getcwd(curdir, SIZE);
    dr = opendir(directory);
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            char path[SIZE];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, d->d_name);
            // printf("%s\n", path);
            struct stat kappa = {0};
            if (stat(path, &kappa) == 0)
            {
                if (S_ISDIR(kappa.st_mode))
                {
                    int len = strlen(curdir);
                    char *relpath = strstr(path, curdir);
                    if (relpath != NULL)
                    {
                        relpath = relpath + len;
                        int len1 = strlen(relpath);
                        if (relpath[len1 - 1] != '.')
                        {
                            printf(".%s\n", relpath);
                            discover_d(path);
                        }
                    }
                    else
                    {
                        printf("%s\n", path);
                    }
                }
            }
            else
            {
                perror("\033[0;31mError\033[0m");
            }
        }
        closedir(dr);
    }
    else
    {
        perror("\033[0;31mError\033[0m");
    }
}

void discover_file(char *directory, char *file)
{
    struct dirent *d;
    DIR *dr;
    char curdir[SIZE];
    getcwd(curdir, SIZE);
    dr = opendir(directory);
    char temp[SIZE];
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            char path[SIZE];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, d->d_name);
            strcpy(temp, d->d_name);
            // printf("%s\n", path);
            struct stat kappa = {0};
            if (stat(path, &kappa) == 0)
            {
                if (S_ISREG(kappa.st_mode) && strcmp(temp, file) == 0)
                {
                    int len = strlen(curdir);
                    char *relpath = strstr(path, curdir);
                    // printf("%s\n",curdir);
                    if (relpath != NULL)
                    {
                        relpath = relpath + len;
                        printf(".%s\n", relpath);
                    }
                    else
                    {
                        printf("%s\n", path);
                    }
                }
                else if (S_ISDIR(kappa.st_mode))
                {
                    int len = strlen(curdir);
                    char *relpath = strstr(path, curdir);
                    if (relpath != NULL)
                    {
                        relpath = relpath + len;
                        int len1 = strlen(relpath);
                        if (relpath[len1 - 1] != '.')
                        {
                            discover_file(path, file);
                        }
                    }
                }
            }
            else
            {
                perror("\033[0;31mError\033[0m");
            }
        }
        closedir(dr);
    }
    else
    {
        perror("\033[0;31mError\033[0m");
    }
}

void discover_file_f(char *directory, char *file)
{
    struct dirent *d;
    DIR *dr;
    char curdir[SIZE];
    getcwd(curdir, SIZE);
    dr = opendir(directory);
    char temp[SIZE];
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            char path[SIZE];
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, d->d_name);
            strcpy(temp, d->d_name);
            // printf("%s\n", path);
            struct stat kappa = {0};
            if (stat(path, &kappa) == 0)
            {
                if (S_ISREG(kappa.st_mode) && strcmp(temp, file) == 0)
                {
                    int len = strlen(curdir);
                    char *relpath = strstr(path, curdir);
                    // printf("%s\n",curdir);
                    if (relpath != NULL)
                    {
                        relpath = relpath + len;
                        printf(".%s\n", relpath);
                    }
                    else
                    {
                        printf("%s\n", path);
                    }
                }
            }
            else
            {
                perror("\033[0;31mError\033[0m");
            }
        }
        closedir(dr);
    }
    else
    {
        perror("\033[0;31mError\033[0m");
    }
}

void command_discover(char **command, int n)
{
    if (n == 1)
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        discover(curdir);
    }
    else if (n == 2 && (strcmp(command[1], "-d") == 0))
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        discover_d(curdir);
    }
    else if (n == 2 && (strcmp(command[1], "-f") == 0))
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        discover_f(curdir);
    }
    else if (n == 2)
    {
        if (strcmp(command[1], ".") == 0)
        {
            char curdir[SIZE];
            getcwd(curdir, SIZE);
            discover(curdir);
        }
        else if (strcmp(command[1], "..") == 0)
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
                for (int i = 0; i < q; i++)
                {
                    prevdir[i] = curdir[i];
                }
                prevdir[q] = '\0';
            }
            discover(prevdir);
        }
        else if (strcmp(command[1], "~") == 0)
        {
            discover(Home);
        }
        else
        {
            char curdir[SIZE];
            char temp[SIZE];
            getcwd(curdir, SIZE);
            strcpy(temp, command[1]);
            if (command[1][0] == '.')
            {
                int len = strlen(command[1]);
                for (int i = 0; i < len - 1; i++)
                {
                    temp[i] = temp[i + 1];
                }
                temp[len - 1] = '\0';
                strcat(curdir, temp);
                discover(curdir);
                // printf("%s\n", curdir);
            }
            else
            {
                if (discover(command[1]) == 1)
                {
                    char curdir[SIZE];
                    getcwd(curdir, SIZE);
                    char temp[SIZE];
                    int len = strlen(command[1]);
                    for (int i = 0, j = 1; i < len - 2, j < len - 1; i++, j++)
                    {
                        temp[i] = command[1][j];
                    }
                    temp[len - 2] = '\0';
                    discover_file(curdir, temp);
                }
            }
        }
    }
    else if ((n == 3) && ((strcmp(command[1], "-d") == 0)) && ((strcmp(command[2], "-f") == 0)))
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        discover(curdir);
    }
    else if ((n == 3) && ((strcmp(command[2], "-d") == 0)) && ((strcmp(command[1], "-f") == 0)))
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        discover(curdir);
    }
    else if ((n == 3) && ((strcmp(command[2], "-d") == 0) || (strcmp(command[2], "-f") == 0)))
    {
        char curdir[SIZE];
        char temp[SIZE];
        getcwd(curdir, SIZE);
        strcpy(temp, command[1]);
        if (command[1][0] = '.')
        {
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = temp[i + 1];
            }
            temp[len - 1] = '\0';
            strcat(curdir, temp);
            if ((strcmp(command[2], "-d") == 0))
            {
                discover_d(curdir);
            }
            else if ((strcmp(command[2], "-f") == 0))
            {
                discover_f(curdir);
            }
        }
        else
        {
            if ((strcmp(command[2], "-d") == 0))
            {
                discover_d(curdir);
            }
            else if ((strcmp(command[2], "-f") == 0))
            {
                discover_f(curdir);
            }
        }
    }
    else if ((n == 4) && (strcmp(command[2], "-d") == 0) && (strcmp(command[3], "-f") == 0))
    {
        char curdir[SIZE];
        char temp[SIZE];
        getcwd(curdir, SIZE);
        strcpy(temp, command[1]);
        if (command[1][0] == '.')
        {
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = temp[i + 1];
            }
            temp[len - 1] = '\0';
            strcat(curdir, temp);
            discover(curdir);
            // printf("%s\n", curdir);
        }
        else
        {
            discover(command[1]);
        }
    }
    else if ((n == 4) && (strcmp(command[2], "-f") == 0) && (strcmp(command[3], "-d") == 0))
    {
        char curdir[SIZE];
        char temp[SIZE];
        getcwd(curdir, SIZE);
        strcpy(temp, command[1]);
        if (command[1][0] == '.')
        {
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = temp[i + 1];
            }
            temp[len - 1] = '\0';
            strcat(curdir, temp);
            discover(curdir);
            // printf("%s\n", curdir);
        }
        else
        {
            discover(command[1]);
        }
    }
    else if ((n == 4) && (strcmp(command[1], "-f") == 0) && (strcmp(command[2], "-d") == 0))
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        char temp[SIZE];
        int len = strlen(command[3]);
        for (int i = 0, j = 1; i < len - 2, j < len - 1; i++, j++)
        {
            temp[i] = command[3][j];
        }
        temp[len - 2] = '\0';
        discover_file(curdir, temp);
    }
    else if ((n == 4) && (strcmp(command[1], "-d") == 0) && (strcmp(command[2], "-f") == 0))
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        char temp[SIZE];
        int len = strlen(command[3]);
        for (int i = 0, j = 1; i < len - 2, j < len - 1; i++, j++)
        {
            temp[i] = command[3][j];
        }
        temp[len - 2] = '\0';
        discover_file(curdir, temp);
    }
    else if ((n == 3) && strcmp(command[1], ".") == 0)
    {
        char curdir[SIZE];
        getcwd(curdir, SIZE);
        char temp[SIZE];
        int len = strlen(command[2]);
        for (int i = 0, j = 1; i < len - 2, j < len - 1; i++, j++)
        {
            temp[i] = command[2][j];
        }
        temp[len - 2] = '\0';
        discover_file(curdir, temp);
    }
    else if ((n == 3))
    {
        char curdir[SIZE];
        char temp[SIZE];
        char temp1[SIZE];
        int len1 = strlen(command[2]);
        for (int i = 0, j = 1; i < len1 - 2, j < len1 - 1; i++, j++)
        {
            temp1[i] = command[2][j];
        }
        temp1[len1 - 2] = '\0';
        getcwd(curdir, SIZE);
        strcpy(temp, command[1]);
        if (command[1][0] = '.')
        {
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = temp[i + 1];
            }
            temp[len - 1] = '\0';
            strcat(curdir, temp);
            discover_file(curdir, temp1);
            discover_file(curdir, temp);
            // printf("%s\n", curdir);
        }
        else
        {
            discover_file(command[1], temp1);
        }
    }
    else if ((n == 4) && strcmp(command[2], "-f") == 0)
    {
        char curdir[SIZE];
        char temp[SIZE];
        char temp1[SIZE];
        int len1 = strlen(command[3]);
        for (int i = 0, j = 1; i < len1 - 2, j < len1 - 1; i++, j++)
        {
            temp1[i] = command[3][j];
        }
        temp1[len1 - 2] = '\0';
        getcwd(curdir, SIZE);
        strcpy(temp, command[1]);
        if (command[1][0] = '.')
        {
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = temp[i + 1];
            }
            temp[len - 1] = '\0';
            strcat(curdir, temp);
            discover_file_f(curdir, temp1);
            // printf("%s\n", curdir);
        }
        else
        {
            discover_file(command[1], temp1);
        }
    }
    else if ((n == 5) && (strcmp(command[2], "-d") == 0) && (strcmp(command[3], "-f") == 0))
    {
        char curdir[SIZE];
        char temp[SIZE];
        char temp1[SIZE];
        int len1 = strlen(command[4]);
        for (int i = 0, j = 1; i < len1 - 2, j < len1 - 1; i++, j++)
        {
            temp1[i] = command[4][j];
        }
        temp1[len1 - 2] = '\0';
        getcwd(curdir, SIZE);
        strcpy(temp, command[1]);
        if (command[1][0] = '.')
        {
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = temp[i + 1];
            }
            temp[len - 1] = '\0';
            strcat(curdir, temp);
            discover_file(curdir, temp1);
            discover_file(curdir, temp);
            // printf("%s\n", curdir);
        }
        else
        {
            discover_file(command[1], temp1);
        }
    }
    else if ((n == 5) && (strcmp(command[2], "-f") == 0) && (strcmp(command[3], "-d") == 0))
    {
        char curdir[SIZE];
        char temp[SIZE];
        char temp1[SIZE];
        int len1 = strlen(command[4]);
        for (int i = 0, j = 1; i < len1 - 2, j < len1 - 1; i++, j++)
        {
            temp1[i] = command[4][j];
        }
        temp1[len1 - 2] = '\0';
        getcwd(curdir, SIZE);
        strcpy(temp, command[1]);
        if (command[1][0] = '.')
        {
            int len = strlen(command[1]);
            for (int i = 0; i < len - 1; i++)
            {
                temp[i] = temp[i + 1];
            }
            temp[len - 1] = '\0';
            strcat(curdir, temp);
            discover_file(curdir, temp1);
            discover_file(curdir, temp);
            // printf("%s\n", curdir);
        }
        else
        {
            discover_file(command[1], temp1);
        }
    }
}