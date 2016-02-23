#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
/*---------------------------------------------------------------------
Структура, реализующая ассоциативынй массив на основе хеш-таблиц
---------------------------------------------------------------------*/
typedef int key_type;
typedef int data_type;
/*---------------------------------------------------------------------*/
struct hash_pair
{
    key_type key;
    data_type data;
};
struct hash_table
{
    uint16_t (*hash_function)(key_type key);
    int* allocated;
    int* used;
    struct hash_pair** table;
    int allocation_step;
};

/*---------------------------------------------------------------------*/
uint16_t hash_FAQ6(key_type key); /*Хеш-функция*/
struct hash_table* hash_table_create(int allocation_step, uint16_t (*hash_function)(key_type key));
        /*Создание хеш-таблицы. allocation_step - шаг выделения памяти (рекомендовано 5 - 100),
        hash_function - указатель на используемую функцию хеширования */
void hash_table_set(struct hash_table* This, key_type key, data_type data);
        /*установка значения*/
data_type hash_table_get(struct hash_table* This, key_type key);
        /*возврат значения, в случае невозможности выполнить поиск возвращается нулевая последовательность байт*/
void hash_table_destroy(struct hash_table* This);
        /*уничтожение хеш-таблицы*/
void hash_table_print(struct hash_table* This);
        /*печать целочисленного массива*/
/*---------------------------------------------------------------------*/
uint16_t hash_FAQ6(key_type key)
{
    uint16_t result_hash = 0;
    char *str = (char*)&key;
    size_t i;
    for(i = 0; i < sizeof(key); i++)
    {
        result_hash += (unsigned char)str[i];
        result_hash += result_hash << 10;
        result_hash ^= result_hash >> 6;
    }
    result_hash += result_hash << 3;
    result_hash ^= result_hash >> 11;
    result_hash += result_hash << 15;
    return result_hash;
}
struct hash_table* hash_table_create(int allocation_step, uint16_t (*hash_function)(key_type key))
{

    size_t i, j;
    struct hash_table* new_hash_table = (struct hash_table*)calloc(sizeof(struct hash_table), 1);

    new_hash_table->allocation_step = allocation_step;
    new_hash_table->hash_function = hash_function;

    new_hash_table->allocated = (int*)calloc(sizeof(int), UINT16_MAX);
    for(i = 0; i < UINT16_MAX; i++)
        new_hash_table->allocated[i] = allocation_step;

    new_hash_table->used = (int*)calloc(sizeof(int), UINT16_MAX);

    new_hash_table->table = (struct hash_pair**)malloc(sizeof(struct hash_pair*) * UINT16_MAX);
    for(i = 0; i < UINT16_MAX; i++)
        new_hash_table->table[i] = (struct hash_pair*)calloc(sizeof(struct hash_pair), allocation_step);
    return new_hash_table;
};
void hash_table_set(struct hash_table* This, key_type key, data_type data)
{
    uint16_t key_hash = (This->hash_function)(key);
    uint8_t founded = 0;
    size_t i;
    for(i = 0; i < This->used[key_hash]; i++)
        if(This->table[key_hash][i].key == key)
        {
            This->table[key_hash][i].data = data;
            founded = 1;
            break;
        }
    if(!founded)
        if(This->used[key_hash] < This->allocated[key_hash])
        {
            This->table[key_hash][This->used[key_hash]].key = key;
            This->table[key_hash][This->used[key_hash]].data = data;
            This->used[key_hash]++;
        }
        else
        {
            This->table[key_hash] = (struct hash_pair*)realloc((void*)This->table[key_hash], This->allocated[key_hash] + This->allocation_step);
            This->allocated[key_hash] += 5;
            This->table[key_hash][This->used[key_hash]].key = key;
            This->table[key_hash][This->used[key_hash]].data = data;
            This->used[key_hash]++;
        }
}
data_type hash_table_get(struct hash_table* This, key_type key)
{
    uint16_t key_hash = (This->hash_function)(key);
    size_t i;

    for(i = 0; i < This->used[key_hash]; i++)
        if(This->table[key_hash][i].key == key)
            return This->table[key_hash][i].data;

    data_type result;
    memset((void*)&result, 0, sizeof(data_type));
    return result;
}
void hash_table_destroy(struct hash_table* This)
{
    size_t i;
    for(i = 0; i < UINT16_MAX; i++)
        free(This->table[i]);
    free(This->table);
    free(This->used);
    free(This->allocated);
    free(This);
}
void hash_table_print(struct hash_table* This)
{
    printf("hash_table:\n");
    size_t i, j;
    for(i = 0; i < UINT16_MAX; i++)
        if(This->used[i] > 0)
        {
            printf("   %d: ", (int)i);
            for(j = 0; j < This->used[i]; j++)
                printf("(%d, %d) ", This->table[i][j].key, This->table[i][j].data);
            printf("\n");
        }
    printf("\n\n");
}
/*---------------------------------------------------------------------*/
int main(void)
{
    struct hash_table* T = hash_table_create(4, hash_FAQ6);
    hash_table_print(T);
    hash_table_set(T, 4, 76);
    hash_table_set(T, 5, 75);
    hash_table_set(T, 6, 72);
    hash_table_print(T);
    hash_table_set(T, 4, 7);
    hash_table_set(T, 40, 126);
    hash_table_print(T);

    hash_table_destroy(T);
    return 0;
}




















