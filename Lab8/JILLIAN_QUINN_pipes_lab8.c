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

typedef char byte;
typedef struct mypipe
{
    byte* pipebuffer;
    int buffersize;
    int start_occupied;
    int end_occupied;
}mypipe;
//initializes (malloc) the pipe with a size of "size" and sets start and end.

void init_pipe(mypipe* pipe, int size)
{
    byte* space;
    space = malloc(size + sizeof(mypipe));
    pipe -> pipebuffer = space;
    pipe -> start_occupied = 0;
    pipe -> end_occupied = 0;
    pipe -> buffersize = size;
}
//writes "size" bytes from buffer into the pipe, returns size

int mywrite(mypipe *pipe, byte* buffer, int size)
{
    if (size > pipe -> buffersize)
    {
        return 0;
    }
    /* if ((pipe -> buffersize - (pipe-> end_occupied + size)) > (pipe->start_occupied) )
    {
        printf("\nNot Enough Space\n");
        return 0;
    } */
    int e = pipe ->end_occupied;
    for (int i = 0; i < size - 1; i++)
    {
        if (e > pipe -> buffersize)
        {
            e = 0;
        }
        pipe ->pipebuffer[e] = buffer[i];
        e++;
    }
    pipe -> end_occupied = e;
    return size;
}

//reads "size" bytes from pipe into buffer, returns how much it read (max size), 0 if pipe is emptyh
int myread(mypipe* pipe, byte* buffer, int size)
{
    if (pipe-> start_occupied == pipe-> end_occupied)
    {
        printf("\nPipe is Empty\n");
        fflush(0);
        return 0;
    }
    if ((pipe -> buffersize - (pipe-> start_occupied + size)) > (pipe->end_occupied) )
    {
        printf("\nNot Enough Space\n");
        return 0;
    }

    if (size > pipe -> buffersize)
    {
        return 0;
    }
    int s = pipe ->start_occupied;
    for (int i = 0; i < size - 1; i++)
    {
        if (s > (pipe -> buffersize))
        {
            s = 0;
        }
        buffer[i] = pipe ->pipebuffer[s];
        s++;
    }
    pipe -> start_occupied = s;
    return size;
}
int main()
{
    char text[100];
    mypipe pipeA;
    init_pipe(&pipeA, 32);  

    mywrite(&pipeA, "hello world", 12);
    mywrite(&pipeA, "it's a nice day", 16);

    myread(&pipeA, text, 12);
    printf("%s\n", text);
    fflush(0);

    myread(&pipeA, text, 16);
    printf("%s\n", text);
    fflush(0);

    mywrite(&pipeA, "and now we test the carryover", 30);
    myread(&pipeA, text, 30);
    printf("%s\n", text);
    fflush(0);
    

    return 0;
}