OBJS	= global.o main.o
SOURCE	= global.c main.c
HEADER	= global.h
OUT	= scrutin
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

global.o: global.c
	$(CC) $(FLAGS) global.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 


clean:
	rm -f $(OBJS) $(OUT)