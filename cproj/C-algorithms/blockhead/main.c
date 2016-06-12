#include <stdio.h>
#include <stdlib.h>
//#include "memoryController.h"
//#include "database.h"
#include "computerNext.h"

#define SIZE 10
int main (void)
{
	srand(time(0));
	struct StringDatabase* D = databaseInit();
	FILE* databaseFile = fopen ("base.txt", "r");

	databaseRead(D, databaseFile);
	//BTreePrintTree(D->root, 0, stdout);
	fclose (databaseFile);

	//return;
	// databasePrint(D, stdout);
	// printf ("%d\n", databaseFindPrefix(D, ""));

	char array[SIZE * SIZE] = {};
	array[0] = 'b';
	array[1] = 'a';
	array[2] = 's';
	array[3] = 'i';
	array[4] = 's';
	//array[9] = 's';
	//array[7] = 'd';

	char result[SIZE * SIZE] = {};
	databaseRemove(D, "basis");
	#define PRINT_FIELD(field) \
	{\
		int i, j;\
		for (i = 0; i < SIZE; i++)\
			{ \
				for ( j = 0; j < SIZE; j++) \
					printf("%c  ", array[SIZE * i + j] ? array[SIZE * i + j] : '-');\
				printf ("\n");\
			}\
	}
	PRINT_FIELD(array);

	int k;
	for (k = 0; k < SIZE * SIZE; k++)
	{
		int location = 0;
		char inserted = 0;
		computerNext (array, SIZE, SIZE, D, result, &location, &inserted);
		printf ("result = %s, location = (%d, %d), inserted = %c\n",
				result, location / SIZE + 1, location % SIZE + 1, inserted);
		if (inserted == 0)
        	break;
        databaseRemove(D, result);
        memset(result, 0, SIZE * SIZE);
        array[location] = inserted;
        PRINT_FIELD(array);

	}




//*/


	databaseDestroy(D);

}
