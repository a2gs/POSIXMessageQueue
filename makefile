all: clean serv client

clean:
	-rm serv client

serv:
	cc -o serv serv.c -Wall -lrt -std=c11

client:
	cc -o client client.c -Wall -lrt -std=c11
