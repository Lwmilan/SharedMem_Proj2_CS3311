all:
	gcc -g -Wall  main.c -o main
	gcc -g -Wall qsort.c -o qsort
	gcc -g -Wall merge.c -o merge




# #Makefile for simple C program
# CC = gcc

# # compiler flags:
# #  -g    adds debugging information to the executable file
# #  -Wall turns on most, but not all, compiler warnings
# CFLAGS  = -g -Wall

# # the build target executable:
# TARGET = qsort merge main

# all: $(TARGET)

# $(TARGET): $(TARGET).c
# 	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
#  
# clean:
# 	$(RM) $(TARGET)
