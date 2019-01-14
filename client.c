#include "networking.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  char name[100];
  printf("Insert name : ");
  fgets(name, sizeof(name), stdin);
  *strchr(name, '\n') = 0;
  strcat(name, " : ");

  char text[255];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
  
  //pipes
  int fds[2];
  pipe(fds);

  if(fork() == 0){
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    while(1){
      read(server_socket, buffer, sizeof(buffer));
      printf("%s\n", buffer);
    }
  }else{
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    while (1) {
      //printf(">");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;

      //adds name to text
      strcpy(text,name);
      strcat(text,buffer);
      
      write(server_socket, text, sizeof(text));
      printf("writing : %s\n", buffer);
    }
  }
}
