CC = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
CC_OPTS = -O0 -g $(WARNINGS)
LINKER = g++

PQUEUE = analyze_pqueue
PQUEUE_OBJS = main.o

all: $(PQUEUE)

$(PQUEUE): $(PQUEUE_OBJS)
	$(LINKER) -o $(PQUEUE) $(PQUEUE_OBJS)

main.o: main.cpp priority_queue.h priority_queue.cpp
	$(CC) $(CC_OPTS) -c main.cpp

clean:
	-rm -rf *.o $(PQUEUE)

tidy:
	-rm -rf doc
