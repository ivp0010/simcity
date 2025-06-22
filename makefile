
CC = g++
CFLAGS = -Wall -Wextra -g

TARGET = simcity

OBJS = main.o cell.o residential.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.cpp splitter.h
	$(CC) $(CFLAGS) -c main.cpp

cell.o: cell.cpp cell.h
	$(CC) $(CFLAGS) -c cell.cpp

residential.o: residential.cpp residential.h cell.h
	$(CC) $(CFLAGS) -c residential.cpp

industrial.o: industrial.cpp industrial.h cell.h
	$(CC) $(CFLAGS) -c industrial.cpp

commercial.o: commercial.cpp commercial.h cell.h
	$(CC) $(CFLAGS) -c commercial.cpp

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
