all: clean serv client

clean:
	-rm serv client

serv:
	cc -o serv serv.c -Wall -lrt

client:
	cc -o client client.c -Wall -lrt
