OBJS = werhauz.o stringManipulate.o list.o findFuncs.o setters.o utilities.o
SOURCE = werhauz.c stringManipulate.c list.c findFuncs.c setters.c utilities.c
HEADER = hashStructs.h stringManipulate.h list.h findFuncs.h setters.h utilities.h
OUT = werhauz
CC = gcc
FLAGS  = -g -c

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

werhauz.o: werhauz.c
	$(CC) $(FLAGS) werhauz.c

stringManipulate.o: stringManipulate.c
	$(CC) $(FLAGS) stringManipulate.c

list.o: list.c
	$(CC) $(FLAGS) list.c

findFuncs.o: findFuncs.c
	$(CC) $(FLAGS) findFuncs.c

setters.o: setters.c
	$(CC) $(FLAGS) setters.c

utilities.o: utilities.c
	$(CC) $(FLAGS) utilities.c

clean: 
	rm -f $(OBJS) $(OUT)
