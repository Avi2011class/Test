CC = g++
CP = -c -O3 -Wall -Werror -fopenmp -march=corei5
HEADERS = headers/
OBJ = obj/
LIBS = -lgomp

Release: $(OBJ)main.o $(OBJ)libcrypt2.a
	$(CC) $(OBJ)main.o $(OBJ)libcrypt2.a $(LIBS) -o codeblocks-and-crypto

Build: $(OBJ)main.o $(OBJ)libcrypt2.a
	$(CC) $(OBJ)main.o $(OBJ)libcrypt2.a $(LIBS) -o codeblocks-and-crypto

$(OBJ)converter.o: $(HEADERS)converter.cpp $(HEADERS)converter.h
	$(CC) $(CP) $(HEADERS)converter.cpp -o $(OBJ)converter.o

$(OBJ)encoder.o: $(HEADERS)encoder.cpp $(HEADERS)encoder.h $(HEADERS)converter.h $(HEADERS)keys.h $(HEADERS)simple_math.h $(HEADERS)scanner.h $(HEADERS)writer.h
	$(CC) $(CP) $(HEADERS)encoder.cpp -o $(OBJ)encoder.o

$(OBJ)keys.o: $(HEADERS)keys.cpp $(HEADERS)keys.h $(HEADERS)simple_math.h
	$(CC) $(CP) $(HEADERS)keys.cpp -o $(OBJ)keys.o

$(OBJ)scanner.o: $(HEADERS)scanner.cpp $(HEADERS)scanner.h
	$(CC) $(CP) $(HEADERS)scanner.cpp -o $(OBJ)scanner.o

$(OBJ)simple_math.o: $(HEADERS)simple_math.cpp $(HEADERS)simple_math.h
	$(CC) $(CP) $(HEADERS)simple_math.cpp -o $(OBJ)simple_math.o

$(OBJ)writer.o: $(HEADERS)writer.cpp $(HEADERS)writer.h
	$(CC) $(CP) $(HEADERS)writer.cpp -o $(OBJ)writer.o

$(OBJ)main.o: main.cpp $(HEADERS)encoder.h $(HEADERS)converter.h $(HEADERS)keys.h $(HEADERS)simple_math.h $(HEADERS)scanner.h $(HEADERS)writer.h $(HEADERS)keys.h
	$(CC) $(CP) main.cpp -o $(OBJ)main.o

$(OBJ)libcrypt2.a: $(OBJ)converter.o $(OBJ)encoder.o $(OBJ)keys.o $(OBJ)scanner.o $(OBJ)simple_math.o $(OBJ)writer.o
	ar cr $(OBJ)libcrypt2.a $(OBJ)converter.o $(OBJ)encoder.o $(OBJ)keys.o $(OBJ)scanner.o $(OBJ)simple_math.o $(OBJ)writer.o

cleanRelease:
	rm -rf $(HEADERS)*.d $(OBJ)*.d
	rm -rf $(HEADERS)*.o $(OBJ)*.o



