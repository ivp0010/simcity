
CC = g++
CFLAGS = -Wall -Wextra -g

TARGET = simcity

OBJS = main.o cell.o residential.o commercial.o industrial.o simManager.o manager.o resManager.o indManager.o comManager.o graph.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.cpp splitter.h simManager.h
	$(CC) $(CFLAGS) -c main.cpp

cell.o: cell.cpp cell.h
	$(CC) $(CFLAGS) -c cell.cpp

residential.o: residential.cpp residential.h cell.h
	$(CC) $(CFLAGS) -c residential.cpp

industrial.o: industrial.cpp industrial.h cell.h
	$(CC) $(CFLAGS) -c industrial.cpp

commercial.o: commercial.cpp commercial.h cell.h
	$(CC) $(CFLAGS) -c commercial.cpp

simManager.o: simManager.cpp simManager.h residential.h industrial.h commercial.h manager.h comManager.h indManager.h resManager.h graph.h cell.h cell.h
	$(CC) $(CFLAGS) -c simManager.cpp

graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) -c graph.cpp

manager.o: manager.cpp manager.h cell.h
	$(CC) $(CFLAGS) -c manager.cpp

resManager.o: resManager.cpp resManager.h residential.h manager.h
	$(CC) $(CFLAGS) -c resManager.cpp

indManager.o: indManager.cpp indManager.h manager.h industrial.h
	$(CC) $(CFLAGS) -c indManager.cpp

comManager.o: comManager.cpp comManager.h commercial.h manager.h
	$(CC) $(CFLAGS) -c comManager.cpp


.PHONY: clean
clean:
	rm -f *.o $(TARGET)
