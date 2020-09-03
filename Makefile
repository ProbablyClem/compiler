parser: 
	cc -o ./build/roo -g ./src/expr.c ./src/main.c ./src/scan.c ./src/tree.c ./src/gen.c ./src/cg.c ./src/stmt.c ./src/misc.c ./src/sym.c ./src/decl.c ./src/types.c

clean:
	rm -f parser *.o vgcore*

run:
	make --no-print-directory
	./build/roo ./tests/input.rs
	llc ./build/out.ll -o ./build/out.o -filetype=obj -relocation-model=pic
	gcc ./build/out.o
	chmod +x ./build/a.out
	rm -f ./build/*.o
	./build/a.out

build:
	make --no-print-directory
	./build/roo input.rs
