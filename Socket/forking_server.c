#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main() {

  // int listen_socket = server_setup();
  int f;
  int i = 0;
  int listen_socket[100];
  for (; i<100; i++)
    listen_socket[i] = server_setup();
  int client_socket;

  while (1) {

    client_socket = server_connect(listen_socket);
    i++;
    
    f = fork();
    if (f == 0)
      subserver(client_socket);
    else
      close(client_socket);
  }

  return 0;
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
