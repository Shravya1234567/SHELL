#include "headers.h"
#include "macros.h"
#include "ll.h"

void command_bg(char **command, int n)
{
    int flag = 0;
    if (n == 2)
    {
        int i = atoi(command[1]);
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
            printf("No job with given job num\n");
        }
        else
        {
            if(kill(currnode->pid,SIGCONT) < 0)
            {
                perror("Error");
            }
        }
    }
    else
    {
        perror("Invalid command");
        return;
    }
}