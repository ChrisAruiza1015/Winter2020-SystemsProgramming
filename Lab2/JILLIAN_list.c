#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

struct listelement
{
    struct listelement *next, *prev;
    char text[1000];
};
struct listelement *head = NULL;

void pushString()
{
    struct listelement *n;
    n = (struct listelement*)malloc(sizeof(struct listelement));
    printf("\nEnter an element to add to the list: ");
    scanf("%s", n -> text);
    if (head == 0)
    {
        head = n;
        n -> next = n -> prev = 0;
        return;
    }
    struct listelement *p = head;
    for(;p -> next!=0; p = p -> next);
    p -> next = n;
    n -> prev = p;
    n -> next = 0;
}
int printList()
{
    printf("\nThe current list is: \n");
    for (struct listelement *p = head; p!=0; p = p-> next)
    {
        printf("%s\n", (p->text));
    
    }
    return 0;
}

int endProgram()
{
    struct listelement *p = head;
    if (head == 0)
    {
        free(head);
        free(p);
        printf("\nProgram Ended\n");
        return 0;
    }
    else{
        while (head -> next != 0) {
            p = head;
            head = head -> next;
            free(p);
        }
            
    }
    free(head);
    printf("\nProgram Ended\n");
    return 0;
}
void deleteItem()
{
    int i;
    printf("\nEnter the index of the item to remove: ");
    scanf("%d", &i);
    struct listelement *p = head;
    int count = 1;
    if (head == 0) 
    {
        printf("\nThere are no elements in the list\n");
        //return *p;
    }
    else{
    while (count != i)
    {
        if (p -> next == 0)
        {
            printf("\nThere are not that many items in the list\n");
            return;
        }
        else
        {
            p = p -> next;
            count++;
        }
    }
    if (head -> next == 0)
    {
        head = 0;
        free(p);
    }
    else if (p == head)
    {
        head = head -> next;
        free(p);
        head -> prev = 0;
    }
    else
    {
        {
            p -> prev -> next = p -> next;
            if (p -> next != NULL)
                p -> next -> prev = p -> prev;
            free(p);
        }
    }
    }
}
int main() 
{
    bool running = true;
    int num;
    
    while (running)
    {
        printf("\nSelect: \n1 push string\n2 print list\n");
        printf("3 delete item\n4 end program\n");
        scanf("%d", &num);
        if (num == 1)
        {
            pushString();
        }
        else if (num == 2)
        {
            printList();
        }
        else if (num == 3)
        {
            deleteItem();
        }
        else if (num == 4)
        {
            endProgram();
            running = false;
        }
        else
        {
            printf("\nInvalid number. Try again: \n");
        }
        
    }
    return 0;
}