parser: expr.c interp.c main.c scan.c tree.c gen.c cg.c
	cc -o roo -g expr.c interp.c main.c scan.c tree.c gen.c cg.c

clean:
	rm -f parser *.o
