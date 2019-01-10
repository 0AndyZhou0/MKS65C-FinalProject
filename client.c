#include "networking.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

<<<<<<< HEAD
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
      printf(">");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      printf("writing : %s\n", buffer);
      //read(server_socket, buffer, sizeof(buffer));
      //printf("%s\n", buffer);
    }
=======
  while (1) {
    printf(">");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));

    if (fork() == 0){
      read(server_socket, buffer, sizeof(buffer));

    }
    printf("%s\n", buffer);
>>>>>>> c12d3d2cfdb0cc1241ce47fd74c530d224aa59b9
  }
}
