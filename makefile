forking: client fserver

select: sclient sserver

sserver: select_server.o networking.o
	gcc -o server select_server.o networking.o

fserver: forking_server.o networking.o
	gcc -o server forking_server.o networking.o

sclient: select_client.o networking.o
	gcc -o client select_client.o networking.o

client: client.o networking.o
	gcc -o client client.o networking.o

select_client.o: select_client.c networking.h
	gcc -c select_client.c

client.o: client.c networking.h
	gcc -c client.c

select_server.o: select_server.c networking.h
	gcc -c select_server.c

forking_server.o: forking_server.c networking.h
	gcc -c forking_server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
