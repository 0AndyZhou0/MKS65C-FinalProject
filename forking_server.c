#include "networking.h"

//void process(char *s);
void subserver(int from_client, int *from_clients,int i);

int main() {

  int listen_socket = server_setup();
  int f;
  int i = 0;
  printf("--------------------\n");
  //int listen_socket[10];
  //for (; i<10; i++)
  //listen_socket[i] = server_setup();
  i = 0;
  //int client_socket;
  int client_socket[10];
  printf("--------------------\n");

  while (1) {
    client_socket[i] = server_connect(listen_socket);
    if(i < 10){
      i++;
      printf("%d\n",i);
    }

    //f = fork();
    for(int x = 0;x < i;x++){
      if (fork() == 0){
      
	subserver(client_socket[x], client_socket, i);
      }
    }
    //else{
      //for(int x = 0;x < i;x++){
	//close(client_socket[x]);
	//}
    //}
  }

  return 0;
}

void subserver(int client_socket, int *client_sockets, int i) {
  char buffer[BUFFER_SIZE];
  
  while (read(client_socket, buffer, sizeof(buffer))) {
    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    //process(buffer);
    for(int x = 0;x < i;x++){
      printf("x : %d\n",x);
      write(client_sockets[x], buffer, sizeof(buffer));
    }
  }//end read loop
  close(client_socket);
  exit(0);
}

/*
void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
*/
