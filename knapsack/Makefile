# Compilador
CC := gcc
# Flags
CFLAGS := -g

#Objetivos
all : knapsacktest

libknapsack.o: libknapsack.c libknapsack.h
	@echo "   libknapsack:"
	$(CC) $(CFLAGS) -c libknapsack.c -o $@ -lm

knapsacktest: knapsacktest.c libknapsack.o
	@echo "  main:"
	$(CC) $(CFLAGS) libknapsack.o knapsacktest.c -o $@ -lm

clean :
	@echo "   Remove binaries..."
	rm -f *.o knapsacktest