#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  char send[100];
  char receive[100];

  int clients[100];
  int i = 0;
  
  while(1){
    from_client = server_handshake( &to_client );
    if(from_client != clients[i]){
      clients[i] = from_client;
      i++;
    }

    //Receiving Information
    while(read(from_client, receive, sizeof(receive)) > 0){
      receive[strlen(receive)] = '\0';
      printf("recieved info : %s\n", receive);
    
      //Sends Changed Information
      write(to_client, send, sizeof(send));
    }
    printf("error %d\n", errno);
  }
  return 0;
}
