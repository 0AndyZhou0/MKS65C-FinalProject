#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo("ur_mum_gay", 0644);//WKP
  
  char private_pipe[100];
  int pipe = open("ur_mum_gay", O_RDONLY);//Waiting for private pipe
  read(pipe, private_pipe, sizeof(char*));
  remove("ur_mum_gay");

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
  mkfifo("no_u", 0644);//Private Pipe

  *to_server = open("ur_mum_gay", O_WRONLY);//Sends private pipe name
  write(*to_server, "no_u", sizeof(char*));

  char from_server[100];
  int pipe = open("no_u", O_RDONLY);//Recieves from server file descriptor 
  read(pipe, from_server, sizeof(char*));

  write(*to_server, "sending signal", sizeof(char*));

  remove("no_u");

  printf("connected to server\n");

  return pipe;
}
