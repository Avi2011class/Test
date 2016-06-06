#ifndef COMPUTERNEXT_H_INCLUDED
#define COMPUTERNEXT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "database.h"

int computerNext (char* field, int height, int width,
				struct StringDatabase* base, char* result, int *location, char* inserted);
/*
Предпочтительный ход компа
field - локализорованное поле
height, width - его параметры
base - база словаря
result - адрес записи найденного слова
location - адрес возврата координаты вставленной буквы
inserted - адрес возврата вставленного символа

функция возвращает длину найденного слова
*/

void DFSstart (char* field, char* visited,
			int iStart, int jStart, int height, int width,
			struct StringDatabase* base, char* 	DFSpath, char* result, uint8_t isFill,
			int* location, int bufLocation, char* inserted, char bufInserted);
#endif // COMPUTERNEXT_H_INCLUDED
