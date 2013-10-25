CFLAGS=-W -Wall -Wextra -Werror
LDFLAGS=-L/usr/lib/libfcgi.so -lfcgi -L/usr/lib/postgresql/8.3/lib/ -lpq -lcrypto
CPPFLAGS=-I/usr/include/postgresql/

all: prog.fcgi

prog.fcgi: crypto.o sql.o page.o dir.o main.o
	gcc $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm *.o

clearall:
	rm *.o
	rm prog.fcgi
