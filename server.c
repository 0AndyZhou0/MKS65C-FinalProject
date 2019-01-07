#include "pipe_networking.h"


int main() {
  int to_client;
  int from_client;

  char send[100];
  char receive[100];

  int clients[100];
  int i = 0;
  
  while(1){
    from_client = server_handshake(&clients[i]);
    i++;

    if(fork() == 0){
      //Receiving Information
      while(read(from_client, receive, sizeof(receive)) > 0){
	receive[strlen(receive)] = '\0';
	printf("recieved info : %s\n", receive);

	strcpy(send, receive);
      
	//Sends Changed Information
	for(int x = 0;x < i;x++){
	  write(clients[x], send, sizeof(send));
	}
	//write(to_client, send, sizeof(send));
      }
    }
  }
  return 0;
}
