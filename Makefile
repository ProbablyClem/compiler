parser: expr.c main.c scan.c tree.c gen.c cg.c stmt.c misc.c sym.c decl.c types.c
	cc -o roo -g expr.c main.c scan.c tree.c gen.c cg.c stmt.c misc.c sym.c decl.c types.c

clean:
	rm -f parser *.o vgcore*

run:
	make --no-print-directory
	./roo input.rs
	llc out.ll -o out.o -filetype=obj -relocation-model=pic
	gcc out.o
	chmod +x a.out
	rm -f *.o
	./a.out

build:
	make --no-print-directory
	./roo input
