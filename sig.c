#include "headers.h"
#include "macros.h"
#include "ll.h"

void command_sig(char **command, int n)
{
    int flag = 0;
    if (n == 3)
    {
        int i = atoi(command[1]);
        int signum = atoi(command[2]);
        data currnode;
        for (currnode = root; currnode != NULL; currnode = currnode->next)
        {
            if (currnode->sno == i)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("No job with given pid\n");
        }
        else
        {
            if (kill(currnode->pid, signum) < 0)
            {
                perror("Invalid signal");
                return;
            }
        }
    }
    else
    {
        perror("Invalid signal:");
        return;
    }
}