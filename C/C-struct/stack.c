#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Stack_Node
{
    Data Val;
    int Height;
    struct Stack_Node* Next;
};

/*////////////////////////////////////////////////////////////////////////////////////*/
struct Stack_Node*     Stack_Push    (struct Stack_Node* st, Data data);
Data                   Stack_Top     (struct Stack_Node* st);
struct Stack_Node*     Stack_Pop     (struct Stack_Node* st);
int                    Stack_Size    (struct Stack_Node* st);
void                   Stack_Print   (struct Stack_Node* st);

/*////////////////////////////////////////////////////////////////////////////////////*/

struct Stack_Node* Stack_Push(struct Stack_Node* st, Data dat)
{
    struct Stack_Node* New_Node = (struct Stack_Node*)malloc(sizeof(struct Stack_Node));
    New_Node->Val = dat;
    if(st != NULL)
    {
        New_Node->Next = st;
        New_Node->Height = st->Height + 1;
    }
    else
    {
        New_Node->Next = NULL;
        New_Node->Height = 1;
    }
    return New_Node;

}

Data Stack_Top (struct Stack_Node* st)
{
    if(st != NULL)
        return st->Val;
    else
        return -1;
}

struct Stack_Node* Stack_Pop(struct Stack_Node* st)
{
    if(st != NULL)
    {
        struct Stack_Node* st_second = st->Next;
        free(st);
        return st_second;
    }
    else return NULL;

};

int Stack_Size(struct Stack_Node* st)
{
    if(st != NULL)
        return st->Height;
    else
        return 0;
}

void Stack_Print(struct Stack_Node* st)
{
    if(st == NULL)
        printf("Empty stack\n");
    else
    {
        while(st != NULL)
        {
            printf("%d ", st->Val);
            st = st->Next;
        }
        printf("\n");
    }
}
/*////////////////////////////////////////////////////////////////////////////////////*/

int main(void)
{
    struct Stack_Node* s = 0;
    Stack_Print(s);
    s = Stack_Push(s, 2);
    s = Stack_Push(s, 3);
    s = Stack_Push(s, 4);
    Stack_Print(s);
    printf("%d %d\n", Stack_Top(s), Stack_Size(s));
    s = Stack_Pop(s);
    Stack_Print(s);
    printf("%d %d\n", Stack_Top(s), Stack_Size(s));
    s = Stack_Pop(s);
    Stack_Print(s);
    printf("%d %d\n", Stack_Top(s), Stack_Size(s));
    s = Stack_Pop(s);
    Stack_Print(s);
    printf("%d %d\n", Stack_Top(s), Stack_Size(s));
    s = Stack_Pop(s);
    return 0;
}
