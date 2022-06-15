CC = g++
CFLAGS = -Wall -O3 --std=c++11
LIB = libs

	
main.exe : main.o $(LIB)/random.o $(LIB)/lib.o 
	$(CC) $(LIB)/random.o $(LIB)/lib.o main.o -o main.exe
	
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
	
random.o : $(LIB)/random.cpp $(LIB)/random.h
	$(CC) -c $(LIB)/random.cpp -o $(LIB)/random.o $(CFLAGS)
	
lib.o : $(LIB)/lib.cpp $(LIB)/lib.h
	$(CC) -c $(LIB)/lib.cpp -o $(LIB)/lib.o $(CFLAGS)

libd.o : $(LIB)/libd.cpp $(LIB)/libd.h
	$(CC) -c $(LIB)/libd.cpp -o $(LIB)/libd.o $(CFLAGS)
	
clean :
	rm *.o main.exe seed.out
