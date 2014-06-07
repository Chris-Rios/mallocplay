CCFLAGS= -g
all: test test2 test3 test4 test5 test6 test7
test: test.o my_malloc.o
	gcc $(CCFLAGS) -o test test.o my_malloc.o
test.o: test.c my_malloc.h
	gcc -c test.c -lm
test2: test2.o my_malloc.o
	gcc $(CCFLAGS) -o test2 test2.o my_malloc.o
test2.o: test2.c my_malloc.h
	gcc -c test2.c -lm	
test3: test3.o my_malloc.o
	gcc $(CCFLAGS) -o test3 test3.o my_malloc.o
test3.o: test3.c my_malloc.h
	gcc -c test3.c -lm
test4: test4.o my_malloc.o
	gcc $(CCFLAGS) -o test4 test4.o my_malloc.o
test4.o: test4.c my_malloc.h
	gcc -c test4.c -lm
test5: test5.o my_malloc.o
	gcc $(CCFLAGS) -o test5 test5.o my_malloc.o
test5.o: test5.c my_malloc.h
	gcc -c test5.c -lm
test6: test6.o my_malloc.o
	gcc $(CCFLAGS) -o test6 test6.o my_malloc.o
test6.o: test6.c my_malloc.h
	gcc -c test6.c -lm	
test7: test7.o my_malloc.o
	gcc $(CCFLAGS) -o test7 test7.o my_malloc.o
test7.o: test7.c my_malloc.h
	gcc -c test7.c -lm	
	
my_malloc.o: my_malloc.c my_malloc.h
	gcc $(CCFLAGS) -c my_malloc.c -lm
clean:
	rm *.o test test2 test3 test4 test5 test6 test7
