#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo("server_name", 0644);//WKP
  
  char private_pipe[100];
  int pipe = open("server_name", O_RDONLY);//Waiting for private pipe
  read(pipe, private_pipe, sizeof(char*));
  remove("server_name");

  *to_client = open(private_pipe, O_WRONLY);//Sends to client file descriptor
  write(*to_client, "sending signal", sizeof(char*));

  char from_client[100];
  read(pipe, from_client, sizeof(char*));//Receives from client file descriptor
  
  printf("user %s connected\n", private_pipe);

  return pipe;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  //char pipe_name[100];
  //printf("Insert name\n");
  //scanf("%[^\n]s",pipe_name);
  char * pipe_name = "owowo";
  
  mkfifo(pipe_name, 0644);//Private Pipe

  *to_server = open("server_name", O_WRONLY);//Sends private pipe name
  write(*to_server, pipe_name, sizeof(char*));

  char from_server[100];
  int pipe = open(pipe_name, O_RDONLY);//Recieves from server file descriptor 
  read(pipe, from_server, sizeof(char*));

  write(*to_server, "sending signal", sizeof(char*));

  remove(pipe_name);

  printf("connected to server\n");

  return pipe;
}
