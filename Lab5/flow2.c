#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <stdint.h>


/*
       O
      /\
    O    O
    /\   /\
   5 4   3 O
           /\
           2 1

*/

int main()
{
    int a;
    if (fork() == 0)
    {
        if (fork() == 0)
        {   
            if (fork() == 0)
            {
                printf("1");
                return 0;
            }
            else
            {
                wait(&a);
                printf("2");
            }
            return 0;
        }
        else
        {
            wait(&a);
            printf("3");
        }
        return 0;
    }
    else
    {
        wait(&a);
        if (fork() == 0)
        {
            printf("4");
            return 0;
        }
        else
        {
            wait(&a);
            printf("5\n");
        }
    }
    return 0;
}