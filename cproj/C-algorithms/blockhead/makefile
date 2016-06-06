compiler = gcc-6
options = -c -O3 -Wall -Werror
linker = gcc-6

all: main.o libdatabase.a computerNext.o
	$(linker) main.o computerNext.o libdatabase.a -o main

#-------------------------------------------------------------
libdatabase.a: database.o b-tree.o
	ar cr libdatabase.a database.o b-tree.o
	
database.o: database.c database.h b-tree.h b-tree.c
	$(compiler) $(options) database.c -o database.o
	
b-tree.o: b-tree.c b-tree.h
	$(compiler) $(options) b-tree.c -o b-tree.o
	
#-------------------------------------------------------------
# liballocator.a: memoryController.o
# 	ar cr liballocator.a memoryController.o

# memoryController.o: memoryController.c memoryController.h
# 	$(compiler) $(options) memoryController.c -o memoryController.o
	
#-------------------------------------------------------------

computerNext.o: computerNext.c computerNext.h
	$(compiler) $(options) computerNext.c -o computerNext.o

main.o: main.c
	$(compiler) $(options) main.c -o main.o
#-------------------------------------------------------------

clean: 
	rm *.o
	rm *.a