CC = gcc 
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o generic_vector.o associative_array.o Evil_Hangman.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o

generic_vector.o: generic_vector.h generic_vector.c my_string.o
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o

associative_array.o: associative_array.h associative_array.c my_string.o generic_vector.o
	$(CC) $(CFLAGS) -c associative_array.c -o associative_array.o

Evil_Hangman.o: Evil_Hangman.h Evil_Hangman.c my_string.o generic_vector.o
	$(CC) $(CFLAGS) -c Evil_Hangman.c -o Evil_Hangman.o 

unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o

unit_test.o: unit_test.c unit_test.h my_string.o
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o

test_def.o: test_def.c unit_test.h my_string.o
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o

clean:
	rm $(OBJECTS)
