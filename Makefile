CC = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
CC_OPTS = -O0 -g $(WARNINGS)
LINKER = g++

PQUEUE = test_pqueue
PQUEUE_OBJS = tester.o

all: $(PQUEUE)

$(PQUEUE): $(PQUEUE_OBJS)
	$(LINKER) -o $(PQUEUE) $(PQUEUE_OBJS)

tester.o: tester.cpp priority_queue.h priority_queue.cpp
	$(CC) $(CC_OPTS) -c tester.cpp

clean:
	-rm -rf *.o $(PQUEUE)

tidy:
	-rm -rf doc
