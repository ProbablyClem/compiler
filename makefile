CC=gcc
CFLAGS=-W -Wall -ansi -Wextra
EXEC=main


all: $(EXEC)

main: main.o

$(EXEC):
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
