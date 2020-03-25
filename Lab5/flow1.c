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
   1 2   5 O
           /\
           3 4

*/

int flow()
{
    int a,b,c,d;
    if (fork() == 0)
    {
        if (fork() == 0)
        {
            printf("1 ");
            return 0;
        }
        else
        {
            wait(&a);
            printf("2 ");
        }
        return 0;
    }
    else
    {
        wait(&a);
        if (fork() == 0)
        {
            if (fork() == 0)
            {
                printf("3 ");
                return 0;
            }
            else
            {
                wait(&a);
                printf("4 "); 
            }
            return 0; 
        }
        else
        {
            wait(&a);
            printf("5 \n");
        }
    }
    return 0;
}

int main()
{
    int g;
    flow();
    return 0;
}