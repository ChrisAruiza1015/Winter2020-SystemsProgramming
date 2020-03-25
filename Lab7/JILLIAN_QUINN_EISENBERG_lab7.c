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

int main() {

    char *text = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    int *flags = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    int *turn = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    turn[0] = 0;
    flags[1] = 0;
    flags[0] = 0;

    if (fork() == 0)
    {
        int i = 0;
        while(1)
        {
            flags[0] = 1;
            int index = turn[0];
            while (index != 0)
            {
                if (flags[index] != 0)
                {
                    index = turn[0];
                }
                else
                {
                    index = (index + 1) %2;
                }
                
            }
            flags[0] = 2;
            index = 0;
            while ((index < 2) && (index == 0 || (flags[index] != 2)))
            {
                index += 1;
            }
            while ((index < 2) && (turn[0] != 0 || flags[turn[0]] == 0))
            {
                //printf("%d\n", index);
            }
            
            //turn[0] = 0;
            if (i%2 == 0)
            {
                strcpy(text, "Yay I think this processes works and I hope it is actually Eiseberg!!!");
            } 
            else
            {
                strcpy(text, "Hi thank you so much for the lab 7 extension! About to start the project 4 now !");
            }

            index = (turn[0] + 1) %2;
            while (flags[index] == 0)
            {
                index = (index + 1) %2;
            }
            turn[0] = index;
            flags[0] = 0;


            i++;

        }


    return 0;
    }
    else
    {
        int i = 0;
        while(1)
        {
            flags[1] = 1;
            int index = turn[0];
            while (index != 1)
            {
                //printf("%d", index);
                if (flags[index] != 0)
                {
                    index = turn[0];
                }
                else
                {
                    index = (index + 1) % 2;
                }
                
            }
            flags[1] = 2;
            index = 0;
            while ((index < 2) && (index == 1 || flags[index] != 2))
            {
                index += 1;
            }
            while ((index < 2) && (turn[0] != 1 || (flags[turn[0]] == 0)));
            //turn[0] = 1;
            char partext[1000];
            strcpy(partext, text);
            printf("%s", partext);
            printf("\n");

            index = (turn[0] + 1) %2;
            while (flags[index] == 0)
            {
                index = (index + 1) %2;
            }
            turn[0] = index;
            flags[1] = 0;


            i++;

        }
        





    }
    


}