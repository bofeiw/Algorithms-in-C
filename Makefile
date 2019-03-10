all:
	make test

test:
	make clean
	gcc test.c sort.c -o test
	./test
	make clean

clean:
	rm -f *.o test *.out


