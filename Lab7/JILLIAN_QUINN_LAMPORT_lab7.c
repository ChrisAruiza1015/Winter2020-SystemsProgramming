#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <string.h>

int max(int i, int j)
{
    if (i > j)
    {
        return i;
    }
    else
    {
        return j;
    }
    
}
int main()
{
    char *text = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    int *entering = mmap(NULL, 12, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    int *number = mmap(NULL, 12, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    entering[0] = 0;
    entering[1] = 0;
    number[0] = 0;
    number[1] = 0;
    if (fork() == 0)
    {
        int i = 0;
        while(1)
        {
            entering[0] = 1;
            number[0] = 1 + max(number[0], number[1]);
            entering[0] = 0;
            while(entering[1]);
            while(number[1] != 0 && number[1] < number[0]);
            if (i%2 == 0)
            {
                strcpy(text, "I am doing laundry right now and it is taking a very long time !! This is a long sentence");
            } 
            else
            {
                strcpy(text, "Hey what's up Christian! I don't want to work on homework right now");
            }  
            i++;
        }
    }
    else
    {
        while(1)
        {
            entering[1] = 1;
            number[1] = 1 + max(number[0], number[1]);
            entering[1] = 0;
            while(entering[0]);
            while(number[0] != 0 && number[0] < number[1]);
            char partext[1000];
            strcpy(partext, text);
            printf("%s", partext);
            printf("\n");
        }  
    }
    return 0;   
}
    