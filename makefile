CC = gcc
CFLAGS = -g -Wall -std=c11 -D_XOPEN_SOURCE=700

RM = rm -rf

all: clean serv client

clean:
	-$(RM) serv client

serv:
	$(CC) -o serv serv.c -lrt $(CFLAGS)

client:
	$(CC) -o client client.c -lrt $(CFLAGS)
