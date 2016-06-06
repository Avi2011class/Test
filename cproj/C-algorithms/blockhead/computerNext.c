#include "computerNext.h"
// #define DEBUG
int computerNext (char* field, int height, int width, struct StringDatabase* base, char* result, int* location, char* inserted)
{
	unsigned int i0, j0;
	char* visited = (char*) calloc (height * width + 1, sizeof (char));
	//struct MemoryAllocator* T = initMemoryAllocator( 5 );

	char* DFSpath = (char*) calloc (height * width + 2, sizeof (char));
	for (i0 = 0; i0 < height; i0++)
		for (j0 = 0; j0 < width; j0++)
		{
			visited [i0 * height + j0] = 1;
			DFSstart (field, visited, i0, j0, height, width, base, DFSpath, result, 0, location, 0, inserted, 0);
			memset (visited, 0, height * width + 1);
		}
	free (visited);

	return 0;
}

void DFSstart (char* field, char* visited, int iStart, int jStart, int height, int width,
			struct StringDatabase* base, char* DFSpath, char* result, uint8_t isFill,
			int* location, int bufLocation, char* inserted, char bufInserted)
{
#ifdef DEBUG
	int counter = 0;
	for (counter = 0; counter < strlen (DFSpath); counter++)
		printf ("  ");
	printf ("DFS into (%d, %d), DFSpath = %s, result = %s, isFill = %hhu\n",
			iStart, jStart, DFSpath, result, isFill);
#endif // DEBUG

	if (isFill && field[iStart * width + jStart] == 0)
		return;

	if (field[iStart * width + jStart] != 0)
	{

		if (databaseFindPrefix(base, (char*) DFSpath) == 0)
			return;

		visited[ iStart * width + jStart ] = 1;
		int lenDFSpath = strlen (DFSpath);
		DFSpath[lenDFSpath] = field[iStart * width + jStart];
		if (isFill)
		{
			if (databaseFindString(base, DFSpath) && lenDFSpath + 1 > strlen (result))
			{
				result = strcpy(result, DFSpath);
				*location = bufLocation;
				*inserted = bufInserted;
			}
			else if (databaseFindString(base, DFSpath) &&
						lenDFSpath + 1 == strlen (result) &&
						rand() % 2 == 0)
			{
				result = strcpy(result, DFSpath);
				*location = bufLocation;
				*inserted = bufInserted;
			}
		}

#define GO_NEXT \
        if (iNext > -1 && iNext < height && jNext > -1 && jNext < width && \
			visited[iNext * width + jNext] == 0) \
				DFSstart(field, visited, iNext, jNext, height, \
							width, base, DFSpath, result, isFill, \
							location, bufLocation, inserted, bufInserted);

		int iNext;
		int jNext;

		iNext = iStart;
		jNext = jStart;
		iNext--;
		GO_NEXT;

		iNext = iStart;
		jNext = jStart;
		jNext--;
		GO_NEXT;

		iNext = iStart;
		jNext = jStart;
		iNext++;
		GO_NEXT;

		iNext = iStart;
		jNext = jStart;
		jNext++;
		GO_NEXT;
#undef GO_NEXT

		DFSpath[lenDFSpath] = 0;
		visited[ iStart * width + jStart ] = 0;
	}

	if (field[iStart * width + jStart] == 0 && isFill == 0)
	{
		if (databaseFindPrefix(base, DFSpath) == 0)
				return;
		unsigned char symbol;
		for (symbol = 'a'; symbol <= 'z'; symbol++)
		{
			field[iStart * width + jStart] = symbol;

			visited[ iStart * width + jStart ] = 1;
			int lenDFSpath = strlen (DFSpath);
			DFSpath[lenDFSpath] = field[iStart * width + jStart];

			if (databaseFindString(base, DFSpath) && lenDFSpath + 1 > strlen (result))
			{
				result = strcpy(result, DFSpath);
				*location = iStart * width + jStart;
				*inserted = symbol;
			}
			else if (databaseFindString(base, DFSpath) &&
						lenDFSpath + 1 == strlen (result) &&
						rand() % 2 == 0)
			{
				result = strcpy(result, DFSpath);
				*location = iStart * width + jStart;
				*inserted = symbol;
			}
			#define GO_NEXT \
			if (iNext > -1 && iNext < height && jNext > -1 && jNext < width && \
				visited[iNext * width + jNext] == 0) \
					DFSstart(field, visited, iNext, jNext, height, \
								width, base, DFSpath, result, 1,\
								location, iStart * width + jStart, inserted, symbol);

			int iNext;
			int jNext;

			iNext = iStart;
			jNext = jStart;
			iNext--;
			GO_NEXT;

			iNext = iStart;
			jNext = jStart;
			jNext--;
			GO_NEXT;

			iNext = iStart;
			jNext = jStart;
			iNext++;
			GO_NEXT;

			iNext = iStart;
			jNext = jStart;
			jNext++;
			GO_NEXT;
			#undef GO_NEXT

			DFSpath[lenDFSpath] = 0;
			visited[ iStart * width + jStart ] = 0;
			field[iStart * width + jStart] = 0;
		}
	}

}

