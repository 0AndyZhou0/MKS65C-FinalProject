all: client server

client: client.o pipe_networking.o
	gcc -o client client.o pipe_networking.o

server: server.o pipe_networking.o
	gcc -o server server.o pipe_networking.o

client.o: client.c pipe_networking.h
	gcc -c client.c

basic_server.o: server.c pipe_networking.h
	gcc -c server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
