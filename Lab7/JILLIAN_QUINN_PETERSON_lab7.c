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

int main()
{
    char *text = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    int *lock = mmap(NULL, 12, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    lock[1] = 0;
    lock[2] = 0;
    lock[0] = 0;

        if(fork() == 0)
        {
            int i = 0;
            while(1)
            {
                lock[1] = 1;
                lock[2] = 0;
                while (lock[0] == 1 && lock[2] == 0);
                    if (i%2 == 0)
                    {
                        strcpy(text, "This is the peterson process wow pretty cool pretty fun very nice wow");
                    } 
                    else
                    {
                        strcpy(text, "Hi! THis is a random extra process because I did not know if I would have time to write Eisenberg");
                    }  
                lock[1] = 0;
                i++;
                
            }
            return 0;
        }
        else
        {
            while (1)
            {
                lock[0] = 1;
                lock[2] = 1;
                while (lock[1] == 1 && lock[2] == 1);
                    char partext[1000];
                    strcpy(partext, text);
                    printf("%s", partext);
                    printf("\n");
                lock[2] = 0;
                lock[0] = 0;

            }
            
        }

    
    
    
    return 0;
}