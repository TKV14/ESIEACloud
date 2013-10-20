CFLAGS=-W -Wall -Wextra -Werror
LDFLAGS=-L/usr/lib/libfcgi.so -lfcgi

all: prog.fcgi

prog.fcgi: page.o dir.o main.o
	gcc $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm *.o

clearall:
	rm *.o
	rm prog.fcgi
