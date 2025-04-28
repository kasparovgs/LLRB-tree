TARGET = lab
CC = gcc
FLAGS = -g

ifeq ($(lib-type), s)
	LIB_EXTENSION = .a
	COMP = 
else
	LIB_EXTENSION = .so
	COMP = -Wl,-rpath,.
endif

LIBRARY = lib$(TARGET)$(LIB_EXTENSION)

$(TARGET) : $(LIBRARY) main.o dial.o log.o
	$(CC) main.o dial.o log.o -L. -l$(TARGET) -o $(TARGET) $(COMP) $(FLAGS)

$(LIBRARY) : llrbtree.o
ifeq ($(lib-type), s)
	ar rcs $(LIBRARY) llrbtree.o
else
	$(CC) -shared -o $(LIBRARY) llrbtree.o
endif

llrbtree.o : llrbtree.c

ifeq ($(lib-type), s)
	$(CC) -c llrbtree.c -o llrbtree.o
else
	$(CC) -c -fPIC llrbtree.c -o llrbtree.o
endif

main.o : main.c

ifeq ($(lib-type), s)
	$(CC) -c main.c -o main.o
else
	$(CC) -c -fPIC main.c -o main.o
endif

dial.o : dial.c

ifeq ($(lib-type), s)
	$(CC) -c dial.c -o dial.o
else
	$(CC) -c -fPIC dial.c -o dial.o
endif

log.o : log.c

ifeq ($(lib-type), s)
	$(CC) -c log.c -o log.o
else
	$(CC) -c -fPIC log.c -o log.o
endif

clean :
	rm $(TARGET) $(LIBRARY) *.o