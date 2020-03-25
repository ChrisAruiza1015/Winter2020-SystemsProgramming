#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

struct listelement
{
    struct listelement *next, *prev;
    char text[1000];
    int data;
};
struct listelement *head = NULL;

int main()
{
    //int a[10000000];
    struct listelement *n;
    int i;
    int *a = malloc(sizeof(int) * 10000000);
    a[0] = 0;
    printf("!!!\n");
    i = sizeof(int);
    printf("%d\n", i);
    printf("%ld\n", sizeof(*a));
    printf("%d", (&a[0] == a));
    n = (struct listelement*)malloc(sizeof(struct listelement));
    (*n).data = 9;
    free(n);
    
    return 0;

}