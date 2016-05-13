#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAXHASHVALUE 99791

/*-------------DataCount--------------*/
struct _DataNoCount
{
    int a;
    int b;
};
typedef struct _DataNoCount DataNoCount;
DataNoCount EmptyDataNoCount = {0, 0};
struct ListNoCountNode
{
    struct ListNoCountNode* next;
    struct ListNoCountNode* prev;
    DataNoCount value;
};
int cmpDataNoCountA(const void* first, const void* second)
{
    DataNoCount a = *(DataNoCount*)first;
    DataNoCount b = *(DataNoCount*)second;
    return a.a - b.a;
}
int cmpDataNoCountB(const void* first, const void* second)
{
    DataNoCount a = *(DataNoCount*)first;
    DataNoCount b = *(DataNoCount*)second;
    return a.b - b.b;
}
int cmpDataNoCount(const void* first, const void* second)
{
    DataNoCount a = *(DataNoCount*)first;
    DataNoCount b = *(DataNoCount*)second;
    return (a.a == b.a && a.b == b.b) ? 0 : -1;
}
int HashNoCountA(DataNoCount dat)
{
    return abs(dat.a) % MAXHASHVALUE;
}
int HashNoCountB(DataNoCount dat)
{
    return abs(dat.b) % MAXHASHVALUE;
}
/*-------------------------------*/
struct ListNoCountNode* ListNoCountCreate(DataNoCount val)
{
    struct ListNoCountNode* NewNode = (struct ListNoCountNode*)malloc(sizeof(struct ListNoCountNode));
    NewNode->next = NewNode;
    NewNode->prev = NewNode;
    NewNode->value = val;
    return NewNode;
};
void ListNoCountAdd(struct ListNoCountNode* Node, DataNoCount val)
{
    struct ListNoCountNode* NewNode = ListNoCountCreate(val);
    struct ListNoCountNode* Next = Node->next;
    Node->next = NewNode;
    NewNode->prev = Node;
    Next->prev = NewNode;
    NewNode->next = Next;
}
void ListNoCountAddBefore(struct ListNoCountNode* Node, DataNoCount val)
{
    struct ListNoCountNode* NewNode = ListNoCountCreate(val);
    struct ListNoCountNode* Prev = Node->prev;
    NewNode->next = Node;
    Node->prev = NewNode;
    Prev->next = NewNode;
    NewNode->prev = Prev;
}
void ListNoCountRemove(struct ListNoCountNode* Node)
{
    Node->next->prev = Node->prev;
    Node->prev->next = Node->next;
    free(Node);
}
void ListNoCountDestroy(struct ListNoCountNode* Node)
{
    if(Node == NULL)
        return;

    struct ListNoCountNode* cur = Node->next;
    while(cur != Node)
    {
        cur = cur->next;
        free(cur->prev);
    }
    free(cur);
}
struct ListNoCountNode* ListNoCountSearchNext(struct ListNoCountNode* ListNoCount, struct ListNoCountNode* StartNode, DataNoCount dat, int (*cmpDataNoCount)(const void*, const void*))
{
    struct ListNoCountNode* CurrentNode = StartNode;
    while(CurrentNode != ListNoCount)
    {
        if(cmpDataNoCount( (const void*)(&(CurrentNode->value)), (const void*)(&dat)) == 0)
            return CurrentNode;
        else
            CurrentNode = CurrentNode->next;
    }
    return NULL;
}
int ListNoCountCount(struct ListNoCountNode* ListNoCount, DataNoCount dat, int (*cmpDataNoCount)(const void*, const void*))
{
    int Result = 0;
    struct ListNoCountNode* CurrentNode = ListNoCount->next;
    while(CurrentNode != NULL)
    {
        CurrentNode = ListNoCountSearchNext(ListNoCount, CurrentNode, dat, cmpDataNoCount);
        if(CurrentNode != NULL)
        {
            CurrentNode = CurrentNode->next;
            Result++;
        }
    }
    return Result;
}

/*-------------------------------*/
struct HashMapNoCount
{
    int MaxHashValue;
    struct ListNoCountNode** Map;
    int (*HashFunction)(DataNoCount);
};
struct HashMapNoCount* HashMapNoCountCreate(int MaxHashValue, int (*HashFunction)(DataNoCount))
{
    struct HashMapNoCount* NewHashMapNoCount = (struct HashMapNoCount*)malloc(sizeof(struct HashMapNoCount));
    NewHashMapNoCount->MaxHashValue = MaxHashValue;
    NewHashMapNoCount->HashFunction = HashFunction;
    NewHashMapNoCount->Map = (struct ListNoCountNode**)malloc(sizeof(struct ListNoCountNode*) * MaxHashValue);
    int i;
    for(i = 0; i < MaxHashValue; i++)
        (NewHashMapNoCount->Map)[i] = ListNoCountCreate(EmptyDataNoCount);
    return NewHashMapNoCount;
}
void HashMapNoCountAdd(struct HashMapNoCount* HashMapNoCount, DataNoCount dat)
{
    int datHash = (HashMapNoCount->HashFunction)(dat);
    if(datHash >= HashMapNoCount->MaxHashValue)
        datHash %= HashMapNoCount->MaxHashValue;

    ListNoCountAdd( (HashMapNoCount->Map)[datHash], dat);
}
int HashMapNoCountCount(struct HashMapNoCount* HashMapNoCount, DataNoCount dat, int (*cmpDataNoCount)(const void*, const void*))
{
    int datHash = (HashMapNoCount->HashFunction)(dat);
    if(datHash >= HashMapNoCount->MaxHashValue)
        datHash %= HashMapNoCount->MaxHashValue;
    return ListNoCountCount( (HashMapNoCount->Map)[datHash], dat, cmpDataNoCount);
}
DataNoCount* HashMapNoCountDeleteOne(struct HashMapNoCount* HashMapNoCount, DataNoCount dat, int (*cmpDataNoCount)(const void*, const void*))
{
    int datHash = (HashMapNoCount->HashFunction)(dat);
    if(datHash >= HashMapNoCount->MaxHashValue)
        datHash %= HashMapNoCount->MaxHashValue;
    struct ListNoCountNode* ResultNode = ListNoCountSearchNext( (HashMapNoCount->Map)[datHash], (HashMapNoCount->Map)[datHash]->next, dat, cmpDataNoCount);

    if(ResultNode == NULL)
        return NULL;

    DataNoCount* resDataNoCount = (DataNoCount*)malloc(sizeof(DataNoCount));
    *resDataNoCount = ResultNode->value;
    ListNoCountRemove(ResultNode);
    return resDataNoCount;
}
int HashMapNoCountDeleteAll(struct HashMapNoCount* HashMapNoCount, DataNoCount dat, int (*cmpDataNoCount)(const void*, const void*))
{
    int datHash = (HashMapNoCount->HashFunction)(dat);
    if(datHash >= HashMapNoCount->MaxHashValue)
        datHash %= HashMapNoCount->MaxHashValue;
    int Deleted = 0;
    while(HashMapNoCountDeleteOne(HashMapNoCount, dat, cmpDataNoCount) != NULL)
        Deleted++;
    return Deleted;
}
void HashMapNoCountDestroy(struct HashMapNoCount* HashMapNoCount)
{
    int CurListNoCount;
    for(CurListNoCount = 0; CurListNoCount < HashMapNoCount->MaxHashValue; CurListNoCount++)
        ListNoCountDestroy(HashMapNoCount->Map[CurListNoCount]);
    free(HashMapNoCount);
}

/*-------------DATA--------------*/
struct _Data
{
    int a;
    int b;
    int c;
};
typedef struct _Data Data;
Data EmptyData = {0, 0, 0};
struct ListNode
{
    struct ListNode* next;
    struct ListNode* prev;
    Data value;
};
int cmpDataA(const void* first, const void* second)
{
    Data a = *(Data*)first;
    Data b = *(Data*)second;
    return a.a - b.a;
}
int cmpDataB(const void* first, const void* second)
{
    Data a = *(Data*)first;
    Data b = *(Data*)second;
    return a.b - b.b;
}
int cmpData(const void* first, const void* second)
{
    Data a = *(Data*)first;
    Data b = *(Data*)second;
    return (a.a == b.a && a.b == b.b) ? 0 : -1;
}
int HashA(Data dat)
{
    return abs(dat.a) % MAXHASHVALUE;
}
int HashB(Data dat)
{
    return abs(dat.b) % MAXHASHVALUE;
}
/*-------------------------------*/
struct ListNode* ListCreate(Data val)
{
    struct ListNode* NewNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    NewNode->next = NewNode;
    NewNode->prev = NewNode;
    NewNode->value = val;
    return NewNode;
};
void ListAdd(struct ListNode* Node, Data val)
{
    struct ListNode* NewNode = ListCreate(val);
    struct ListNode* Next = Node->next;
    Node->next = NewNode;
    NewNode->prev = Node;
    Next->prev = NewNode;
    NewNode->next = Next;
}
void ListAddBefore(struct ListNode* Node, Data val)
{
    struct ListNode* NewNode = ListCreate(val);
    struct ListNode* Prev = Node->prev;
    NewNode->next = Node;
    Node->prev = NewNode;
    Prev->next = NewNode;
    NewNode->prev = Prev;
}
void ListRemove(struct ListNode* Node)
{
    Node->next->prev = Node->prev;
    Node->prev->next = Node->next;
    free(Node);
}
void ListDestroy(struct ListNode* Node)
{
    if(Node == NULL)
        return;

    struct ListNode* cur = Node->next;
    while(cur != Node)
    {
        cur = cur->next;
        free(cur->prev);
    }
    free(cur);
}
struct ListNode* ListSearchNext(struct ListNode* List, struct ListNode* StartNode, Data dat, int (*cmpData)(const void*, const void*))
{
    struct ListNode* CurrentNode = StartNode;
    while(CurrentNode != List)
    {
        if(cmpData( (const void*)(&(CurrentNode->value)), (const void*)(&dat)) == 0)
            return CurrentNode;
        else
            CurrentNode = CurrentNode->next;
    }
    return NULL;
}
int ListCount(struct ListNode* List, Data dat, int (*cmpData)(const void*, const void*))
{
    int Result = 0;
    struct ListNode* CurrentNode = List->next;
    while(CurrentNode != NULL)
    {
        CurrentNode = ListSearchNext(List, CurrentNode, dat, cmpData);
        if(CurrentNode != NULL)
        {
            Result += (CurrentNode->value).c;
            CurrentNode = CurrentNode->next;

        }
    }
    return Result;
}

/*-------------------------------*/
struct HashMap
{
    int MaxHashValue;
    struct ListNode** Map;
    int (*HashFunction)(Data);
};
struct HashMap* HashMapCreate(int MaxHashValue, int (*HashFunction)(Data))
{
    struct HashMap* NewHashMap = (struct HashMap*)malloc(sizeof(struct HashMap));
    NewHashMap->MaxHashValue = MaxHashValue;
    NewHashMap->HashFunction = HashFunction;
    NewHashMap->Map = (struct ListNode**)malloc(sizeof(struct ListNode*) * MaxHashValue);
    int i;
    for(i = 0; i < MaxHashValue; i++)
        (NewHashMap->Map)[i] = ListCreate(EmptyData);
    return NewHashMap;
}
int HashMapCount(struct HashMap* HashMap, Data dat, int (*cmpData)(const void*, const void*))
{
    int datHash = (HashMap->HashFunction)(dat);
    if(datHash >= HashMap->MaxHashValue)
        datHash %= HashMap->MaxHashValue;
    return ListCount( (HashMap->Map)[datHash], dat, cmpData);
}
Data* HashMapDeleteOne(struct HashMap* HashMap, Data dat, int (*cmpData)(const void*, const void*))
{
    int datHash = (HashMap->HashFunction)(dat);
    if(datHash >= HashMap->MaxHashValue)
        datHash %= HashMap->MaxHashValue;
    struct ListNode* ResultNode = ListSearchNext( (HashMap->Map)[datHash], (HashMap->Map)[datHash]->next, dat, cmpData);

    if(ResultNode == NULL)
        return NULL;

    Data* resData = (Data*)malloc(sizeof(Data));
    *resData = ResultNode->value;
    ListRemove(ResultNode);
    return resData;
}
int HashMapDeleteAll(struct HashMap* HashMap, Data dat, int (*cmpData)(const void*, const void*))
{
    int datHash = (HashMap->HashFunction)(dat);
    if(datHash >= HashMap->MaxHashValue)
        datHash %= HashMap->MaxHashValue;
    int Deleted = 0;
    Data* DelDat = NULL;
    while(1)
    {
        DelDat = HashMapDeleteOne(HashMap, dat, cmpData);
        if(DelDat == NULL)
            break;
        else
            Deleted += DelDat->c;
    }

    return Deleted;
}
void HashMapAdd(struct HashMap* HashMap, Data dat)
{
    int datHash = (HashMap->HashFunction)(dat);
    if(datHash >= HashMap->MaxHashValue)
        datHash %= HashMap->MaxHashValue;
    dat.c = HashMapDeleteAll(HashMap, dat, cmpData) + 1;
    ListAdd( (HashMap->Map)[datHash], dat);
}
void HashMapDestroy(struct HashMap* HashMap)
{
    int CurList;
    for(CurList = 0; CurList < HashMap->MaxHashValue; CurList++)
        ListDestroy(HashMap->Map[CurList]);
    free(HashMap);
}
/*-------------------------------*/


void useCount(char* buffer, int N, int x1, int y1)
{
    struct HashMap* A = HashMapCreate(MAXHASHVALUE, HashA);
    struct HashMap* B = HashMapCreate(MAXHASHVALUE, HashB);
    int i, x, y;
    char mode;

            Data NewData;
            NewData.a = x1;
            NewData.b = y1;
            HashMapAdd(A, NewData);
            HashMapAdd(B, NewData);
            int count = HashMapCount(A, NewData, cmpData);
            printf("%d\n", count);



    for(i = 1; i < N; i++)
    {
        scanf("%s ", buffer);
        if(strcmp(buffer, "ADD\0") == 0)
        {
            scanf("%d %d", &x, &y);
            Data NewData;
            NewData.a = x;
            NewData.b = y;
            HashMapAdd(A, NewData);
            HashMapAdd(B, NewData);
            int count = HashMapCount(A, NewData, cmpData);
            printf("%d\n", count);
        }
        else if(strcmp(buffer, "DELETE\0") == 0)
        {
            scanf("%c", &mode);
            if(mode == 'A')
            {
                scanf("%d", &x);
                Data NewData;
                NewData.a = x;
                int count = HashMapCount(A, NewData, cmpDataA);
                printf("%d\n", count);
                while(1)
                {
                    Data* Del = HashMapDeleteOne(A, NewData, cmpDataA);
                    if(Del != NULL)
                    {
                        HashMapDeleteOne(B, *Del, cmpData);
                    }
                    else
                        break;
                }
            }
            if(mode == 'B')
            {
                scanf("%d", &y);
                Data NewData;
                NewData.b = y;
                int count = HashMapCount(B, NewData, cmpDataB);
                printf("%d\n", count);
                while(1)
                {
                    Data* Del = HashMapDeleteOne(B, NewData, cmpDataB);
                    if(Del != NULL)
                    {
                        HashMapDeleteOne(A, *Del, cmpData);
                    }
                    else
                        break;
                }
            }
        }
        else if(strcmp(buffer, "COUNT\0") == 0)
        {
            scanf("%c", &mode);
            if(mode == 'A')
            {
                scanf("%d", &x);
                Data NewData;
                NewData.a = x;
                int count = HashMapCount(A, NewData, cmpDataA);
                printf("%d\n", count);
            }
            if(mode == 'B')
            {
                scanf("%d", &y);
                Data NewData;
                NewData.b = y;
                int count = HashMapCount(B, NewData, cmpDataB);
                printf("%d\n", count);
            }
        }
        else
        {
            printf("ERR\n");
        }
    }
    HashMapDestroy(A);
    HashMapDestroy(B);
}



int main(void)
{
    struct HashMapNoCount* A = HashMapNoCountCreate(MAXHASHVALUE, HashNoCountA);
    struct HashMapNoCount* B = HashMapNoCountCreate(MAXHASHVALUE, HashNoCountB);

    int N;
    scanf("%d\n", &N);
    int i;
    char* buffer = (char*)malloc(sizeof(char) * 100);
    char mode;
    int x, y;
    for(i = 0; i < N; i++)
    {


        scanf("%s ", buffer);



        if(strcmp(buffer, "ADD\0") == 0)
        {


            scanf("%d %d", &x, &y);

            if( i == 0 && x+y == 0)
            {
                useCount(buffer, N, x, y);
                free(buffer);
                HashMapNoCountDestroy(A);
                HashMapNoCountDestroy(B);
                return 0;
            }

            DataNoCount NewData;
            NewData.a = x;
            NewData.b = y;
            HashMapNoCountAdd(A, NewData);
            HashMapNoCountAdd(B, NewData);
            int count = HashMapNoCountCount(A, NewData, cmpData);
                printf("%d\n", count);
        }
        else if(strcmp(buffer, "DELETE\0") == 0)
        {
            scanf("%c", &mode);
            if(mode == 'A')
            {
                scanf("%d", &x);
                DataNoCount NewData;
                NewData.a = x;
                int count = HashMapNoCountCount(A, NewData, cmpDataA);
                printf("%d\n", count);
                while(1)
                {
                    DataNoCount* Del = HashMapNoCountDeleteOne(A, NewData, cmpDataA);
                    if(Del != NULL)
                    {
                        HashMapNoCountDeleteOne(B, *Del, cmpData);
                    }
                    else
                        break;
                }
            }
            if(mode == 'B')
            {
                scanf("%d", &y);
                DataNoCount NewData;
                NewData.b = y;
                int count = HashMapNoCountCount(B, NewData, cmpDataB);
                printf("%d\n", count);
                while(1)
                {
                    DataNoCount* Del = HashMapNoCountDeleteOne(B, NewData, cmpDataB);
                    if(Del != NULL)
                    {
                        HashMapNoCountDeleteOne(A, *Del, cmpData);
                    }
                    else
                        break;
                }
            }
        }
        else if(strcmp(buffer, "COUNT\0") == 0)
        {
            scanf("%c", &mode);
            if(mode == 'A')
            {
                scanf("%d", &x);
                DataNoCount NewData;
                NewData.a = x;
                int count = HashMapNoCountCount(A, NewData, cmpDataA);
                printf("%d\n", count);
            }
            if(mode == 'B')
            {
                scanf("%d", &y);
                DataNoCount NewData;
                NewData.b = y;
                int count = HashMapNoCountCount(B, NewData, cmpDataB);
                printf("%d\n", count);
            }
        }
        else
        {
            printf("ERR\n");
        }
    }
    free(buffer);
    HashMapNoCountDestroy(A);
    HashMapNoCountDestroy(B);
    return 0;
}
