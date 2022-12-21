#include "headers.h"
#include "macros.h"

int Compare(const void *a, const void *b)
{
    return strcasecmp(*(const char **)a, *(const char **)b);
}

void ls(int choice)
{
    char *filnames[SIZE];
    struct dirent *d;
    char *directory;
    DIR *dr;
    if (choice == 1)
    {
        dr = opendir(".");
    }
    if (choice == 2)
    {
        dr = opendir("..");
    }
    if (choice == 3)
    {
        dr = opendir(Home);
    }
    if (dr != NULL)
    {
        int i = 0;
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            if (d->d_name[0] != '.')
            {
                // printf("%s\n", d->d_name);
                filnames[i] = d->d_name;
                i++;
            }
        }
        closedir(dr);
        // for (int j = 0; j < i; j++)
        //     printf("%s \n",filnames[j]);
        qsort(filnames, i, sizeof(const char *), Compare);
        char curdir[SIZE];
        char *temp = getcwd(curdir, SIZE);
        char path[1000];
        char prevdir[SIZE];
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
        strcat(temp, "/");
        for (int j = 0; j < i; j++)
        {
            if (choice == 1)
            {
                strcpy(path, temp);
            }
            if (choice == 2)
            {
                strcpy(path, prevdir);
                strcat(path, "/");
            }
            else if (choice == 3)
            {
                strcpy(path, Home);
                strcat(path, "/");
            }
            strcat(path, filnames[j]);
            struct stat f = {0};
            if (stat(path, &f) == 0)
            {
                if (S_ISDIR(f.st_mode) )
                {
                    printf("\033[0;34m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else if ((f.st_mode & S_IXUSR))
                {
                    printf("\033[0;32m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", filnames[j]);
                }
            }
        }
    }
    else
    {
        perror("\033[0;31mError\033[0m");
    }
}

void ls_l(int choice, char *directory)
{
    char *filnames[SIZE];
    struct dirent *d;
    DIR *dr;
    if (strcmp(directory, "~") == 0)
    {
        dr = opendir(Home);
    }
    else
        dr = opendir(directory);
    int choic = 0;
    if (strcmp(directory, ".") == 0)
    {
        choic = 1;
    }
    else if (strcmp(directory, "..") == 0)
    {
        choic = 2;
    }
    else if (strcmp(directory, "~") == 0)
    {
        choic = 3;
    }
    char curdir[SIZE];
    long long total = 0;
    if (dr != NULL)
    {
        int i = 0;
        while ((d = readdir(dr)) != NULL)
        {
            char *temp = getcwd(curdir, 1000);
            char path[SIZE];
            char path1[SIZE];
            char prevdir[SIZE];
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
            strcat(temp, "/");
            if (choic == 1)
            {
                strcpy(path, temp);
            }
            else if (choic == 2)
            {
                strcpy(path, prevdir);
                strcat(path, "/");
            }
            else if (choic == 3)
            {
                strcpy(path, Home);
                strcat(path, "/");
            }
            else
            {
                strcpy(path, temp);
                strcat(path, directory);
                strcpy(path1, directory);
                strcat(path, "/");
                strcat(path1, "/");
            }
            strcat(path, d->d_name);
            strcat(path1, d->d_name);
            // printf("%s\n", path);
            filnames[i] = d->d_name;
            i++;
            struct stat kappa = {0};
            if ((choice == 1) || (d->d_name[0] != '.'))
            {
                if (stat(path, &kappa) == 0 || stat(path1, &kappa) == 0)
                    total += kappa.st_blocks;
                else
                {
                    perror("\033[0;31mError\033[0m");
                }
            }
        }
        printf("total %lld\n", total / 2);
        qsort(filnames, i, sizeof(const char *), Compare);
        char curdir[SIZE];
        char *temp = getcwd(curdir, SIZE);
        char path[1000];
        char path1[1000];
        char prevdir[SIZE];
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
        strcat(temp, "/");
        for (int j = 0; j < i; j++)
        {
            if (choic == 1)
            {
                strcpy(path, temp);
            }
            else if (choic == 2)
            {
                strcpy(path, prevdir);
                strcat(path, "/");
            }
            else if (choic == 3)
            {
                strcpy(path, Home);
                strcat(path, "/");
            }
            else
            {
                strcpy(path, temp);
                strcat(path, directory);
                strcpy(path1, directory);
                strcat(path, "/");
                strcat(path1, "/");
            }
            strcat(path, filnames[j]);
            strcat(path1, filnames[j]);
            if ((choice == 1) || (filnames[j][0] != '.'))
            {
                struct stat f = {0};
                if (stat(path, &f) == 0 || stat(path1, &f) == 0)
                {
                    if (S_ISDIR(f.st_mode))
                    {
                        printf("d");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IRUSR)
                    {
                        printf("r");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IWUSR)
                    {
                        printf("w");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IXUSR)
                    {
                        printf("x");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IRGRP)
                    {
                        printf("r");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IWGRP)
                    {
                        printf("w");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IXGRP)
                    {
                        printf("x");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IROTH)
                    {
                        printf("r");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IWOTH)
                    {
                        printf("w");
                    }
                    else
                    {
                        printf("-");
                    }
                    if (f.st_mode & S_IXOTH)
                    {
                        printf("x");
                    }
                    else
                    {
                        printf("-");
                    }
                    printf("\t");
                    printf("%ld ", f.st_nlink);
                    struct passwd *pw = getpwuid(f.st_uid);
                    struct group *gr = getgrgid(f.st_gid);
                    if (pw != 0)
                    {
                        printf("%s\t", pw->pw_name);
                    }
                    if (gr != 0)
                    {
                        printf("%s\t", gr->gr_name);
                    }
                    printf("%ld\t", f.st_size);
                    char mtime[80];
                    time_t t = f.st_mtime;
                    struct tm lt;
                    localtime_r(&t, &lt);
                    strftime(mtime, sizeof mtime, "%b %d %Y %H:%M", &lt);
                    printf("%s ", mtime);
                    // printf("%s\n",filnames[j]);
                    if (S_ISDIR(f.st_mode))
                    {
                        printf("\033[0;34m");
                        printf("%s\n", filnames[j]);
                        printf("\033[0m");
                    }
                    else if ((f.st_mode & S_IXUSR) )
                    {
                        printf("\033[0;32m");
                        printf("%s\n", filnames[j]);
                        printf("\033[0m");
                    }
                    else
                    {
                        printf("%s\n", filnames[j]);
                    }
                }
                else
                {
                    perror("\033[0;31mError\033[0m");
                }
            }
        }
        closedir(dr);
    }
    else
    {
        char curdir[SIZE];
        char *temp = getcwd(curdir, SIZE);
        char path[1000];
        strcat(temp, "/");
        strcpy(path, temp);
        strcat(path, directory);
        struct stat f = {0};
        if (stat(path, &f) == 0)
        {
            if (S_ISDIR(f.st_mode))
            {
                printf("d");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IRUSR)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IWUSR)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IXUSR)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IRGRP)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IWGRP)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IXGRP)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IROTH)
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IWOTH)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (f.st_mode & S_IXOTH)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }
            printf("\t");
            printf("%ld ", f.st_nlink);
            struct passwd *pw = getpwuid(f.st_uid);
            struct group *gr = getgrgid(f.st_gid);
            if (pw != 0)
            {
                printf("%s\t", pw->pw_name);
            }
            if (gr != 0)
            {
                printf("%s\t", gr->gr_name);
            }
            printf("%ld\t", f.st_size);
            char mtime[80];
            time_t t = f.st_mtime;
            struct tm lt;
            localtime_r(&t, &lt);
            strftime(mtime, sizeof mtime, "%b %d %Y %H:%M", &lt);
            printf("%s ", mtime);
            // printf("%s\n",filnames[j]);

            printf("%s\n", directory);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
    }
}

void ls_a(char *directory)
{
    char *filnames[SIZE];
    struct dirent *d;
    DIR *dr;
    if (strcmp(directory, "~") == 0)
    {
        dr = opendir(Home);
    }
    else
        dr = opendir(directory);
    int choice = 0;
    if (strcmp(directory, ".") == 0)
    {
        choice = 1;
    }
    else if (strcmp(directory, "..") == 0)
    {
        choice = 2;
    }
    else if (strcmp(directory, "~") == 0)
    {
        choice = 3;
    }
    if (dr != NULL)
    {
        int i = 0;
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            filnames[i] = d->d_name;
            i++;
        }
        closedir(dr);
        // for (int j = 0; j < i; j++)
        //     printf("%s \n",filnames[j]);
        qsort(filnames, i, sizeof(const char *), Compare);
        char curdir[SIZE];
        char *temp = getcwd(curdir, SIZE);
        char path[1000];
        char path1[1000];
        char prevdir[SIZE];
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
        strcat(temp, "/");
        for (int j = 0; j < i; j++)
        {
            if (choice == 1)
            {
                strcpy(path, temp);
            }
            else if (choice == 2)
            {
                strcpy(path, prevdir);
                strcat(path, "/");
            }
            else if (choice == 3)
            {
                strcpy(path, Home);
                strcat(path, "/");
            }
            else
            {
                strcpy(path, temp);
                strcat(path, directory);
                strcat(path, "/");
                strcpy(path1, directory);
                strcat(path1, "/");
            }
            strcat(path, filnames[j]);
            strcat(path1, filnames[j]);
            struct stat f = {0};
            struct stat f1 = {0};
            if (stat(path, &f) == 0)
            {
                if (S_ISDIR(f.st_mode))
                {
                    printf("\033[0;34m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else if (f.st_mode & S_IXUSR)
                {
                    printf("\033[0;32m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", filnames[j]);
                }
            }
            else if (stat(path1, &f1) == 0)
            {
                if (S_ISDIR(f1.st_mode) )
                {
                    printf("\033[0;34m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else if ((f1.st_mode & S_IXUSR) )
                {
                    printf("\033[0;32m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", filnames[j]);
                }
            }
        }
    }
    else
    {
        char curdir[SIZE];
        char *temp = getcwd(curdir, SIZE);
        char path[1000];
        strcat(temp, "/");
        strcpy(path, temp);
        strcat(path, directory);
        struct stat f = {0};
        if (stat(path, &f) == 0)
        {
            printf("%s\n", directory);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
    }
}

void ls_dir(char *directory)
{
    char *filnames[SIZE];
    struct dirent *d;
    DIR *dr;
    dr = opendir(directory);
    if (dr != NULL)
    {
        int i = 0;
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            if (d->d_name[0] != '.')
            {
                // printf("%s\n", d->d_name);
                filnames[i] = d->d_name;
                i++;
            }
        }
        closedir(dr);
        // for (int j = 0; j < i; j++)
        //     printf("%s \n",filnames[j]);
        qsort(filnames, i, sizeof(const char *), Compare);
        char curdir[SIZE];
        char *temp = getcwd(curdir, SIZE);
        char path[1000];
        char path1[1000];
        strcat(temp, "/");
        for (int j = 0; j < i; j++)
        {
            strcpy(path, temp);
            strcpy(path1, directory);
            strcat(path, directory);
            strcat(path, "/");
            strcat(path1, "/");
            strcat(path, filnames[j]);
            strcat(path1, filnames[j]);
            struct stat f = {0};
            struct stat f1 = {0};
            int flag = 0;
            if (stat(path1, &f1) == 0)
                flag = 1;
            if (flag == 0 && stat(path, &f) == 0)
            {
                if (S_ISDIR(f.st_mode) )
                {
                    printf("\033[0;34m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else if ((f.st_mode & S_IXUSR))
                {
                    printf("\033[0;32m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", filnames[j]);
                }
            }
            else if (flag == 1)
            {
                if (S_ISDIR(f1.st_mode))
                {
                    printf("\033[0;34m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else if ((f1.st_mode & S_IXUSR))
                {
                    printf("\033[0;32m");
                    printf("%s\n", filnames[j]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", filnames[j]);
                }
            }
        }
    }
    else
    {
        char curdir[SIZE];
        char *temp = getcwd(curdir, SIZE);
        char path[1000];
        strcat(temp, "/");
        strcpy(path, temp);
        strcat(path, directory);
        struct stat f = {0};
        if (stat(path, &f) == 0)
        {
            printf("%s\n", directory);
        }
        else
        {
            // perror("\033[0;31m");
            perror("\033[0;31mError\033[0m");
            // perror("\033[0m");
        }
    }
}

void command_ls(char **command, int n)
{
    if ((n == 3 && strcmp(command[1], "-a") == 0 && strcmp(command[2], "-l") == 0) || (n == 3 && strcmp(command[2], "-a") == 0 && strcmp(command[1], "-l") == 0) || (n == 2 && ((strcmp(command[1], "-la") == 0) || (strcmp(command[1], "-al") == 0))))
    {
        ls_l(1, ".");
    }
    else if (n >= 3)
    {
        int flag1 = 0, flag2 = 0;
        for (int i = 1; i < n; i++)
        {
            if (strcmp(command[i], "-l") == 0)
            {
                flag1 = 1;
            }
            if (strcmp(command[i], "-a") == 0)
            {
                flag2 = 1;
            }
            if ((strcmp(command[i], "-la") == 0) || (strcmp(command[i], "-al") == 0))
            {
                flag1 = 1;
                flag2 = 1;
            }
        }

        for (int i = 1; i < n; i++)
        {
            if (strcmp(command[i], ".") == 0)
            {
                // printf(". :\n");
                if (flag1 == 1 && flag2 == 1)
                {
                    ls_l(1, ".");
                }
                else if (flag1 == 1)
                {
                    ls_l(0, ".");
                }
                else if (flag2 == 1)
                {
                    ls_a(".");
                }
                else
                {
                    ls(1);
                }
            }
            else if (strcmp(command[i], "..") == 0)
            {
                // printf(".. :\n");
                if (flag1 == 1 && flag2 == 1)
                {
                    ls_l(1, "..");
                }
                else if (flag1 == 1)
                {
                    ls_l(0, "..");
                }
                else if (flag2 == 1)
                {
                    ls_a("..");
                }
                else
                {
                    ls(2);
                }
            }
            else if (strcmp(command[i], "~") == 0)
            {
                // printf("%s :\n", Home);
                if (flag1 == 1 && flag2 == 1)
                {
                    ls_l(1, "~");
                }
                else if (flag1 == 1)
                {
                    ls_l(0, "~");
                }
                else if (flag2 == 1)
                {
                    ls_a("~");
                }
                else
                {
                    ls(3);
                }
            }
            else if ((strcmp(command[i], "-la") != 0) && (strcmp(command[i], "-al") != 0) && (strcmp(command[i], "-l") != 0) && (strcmp(command[i], "-a") != 0))
            {
                // printf("%s :\n", command[i]);
                if (flag1 == 1 && flag2 == 1)
                {
                    ls_l(1, command[i]);
                }
                else if (flag1 == 1)
                {
                    ls_l(0, command[i]);
                }
                else if (flag2 == 1)
                {
                    ls_a(command[i]);
                }
                else
                {
                    ls_dir(command[i]);
                }
            }
        }
    }
    else if (n == 1 || (n == 2 && strcmp(command[1], ".") == 0))
    {
        ls(1);
    }
    else if ((n == 2 && (strcmp(command[1], "-l") == 0)))
    {
        ls_l(0, ".");
    }
    else if ((n == 2 && (strcmp(command[1], "-a") == 0)))
    {
        ls_a(".");
    }
    else if ((n == 2 && strcmp(command[1], "..") == 0))
    {
        ls(2);
    }
    else if ((n == 2 && strcmp(command[1], "~") == 0))
    {
        ls(3);
    }
    else if ((n == 2))
    {
        ls_dir(command[1]);
    }
}