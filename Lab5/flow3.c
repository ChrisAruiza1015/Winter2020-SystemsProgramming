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
   1 2   3 4
    

*/

int main()
{
    int g;
    if (fork() == 0)
    {
        if (fork() == 0) 
        {
            printf("1\n");
            return 0;
        }
        else
        {
           wait(&g);
           printf("2\n");   
        }
        return 0;
    }
    else
    {
        wait(&g);
        if (fork() == 0)
        {
            printf("3\n");
            return 0;
        }
        else
        {
            wait(&g);
            printf("4\n");
        }
    }
    return 0;
}