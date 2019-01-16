#include "networking.h"
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 

//void process(char *s);
//void subserver(int from_client, int *from_clients,int i);

int main() {

  int listen_socket = server_setup();
  int f;
  int client_socket[100];
  int client_num[100];
  char* client_names[100];
  int clients = listen_socket;
  for(int x = 0;x < 100;x++){
    client_socket[x] = 0;
    client_num[x] = 0;
    client_names[x] = 0;
  }

  fd_set readfds;
  
  int temp;
  char buffer[BUFFER_SIZE];
  
  while (1) {
    FD_ZERO(&readfds);
    FD_SET(listen_socket,&readfds);
    for(int i = 0;i < 100;i++){
      if(client_socket[i] > 0){
	FD_SET(client_socket[i], &readfds);
	if(client_socket[i] > clients){
	  clients = client_socket[i];
	}
      }
    }
     
    select(clients + 1, &readfds, NULL, NULL, NULL);
    
    if(FD_ISSET(listen_socket, &readfds)){
      if(temp = server_connect(listen_socket)){
	for(int x = 0;x < 100 && client_socket[x] != temp;x++){
	  if(client_socket[x] == 0){
	    client_socket[x] = temp;//Add to list of clients
	    client_names[x] = malloc(sizeof(char*));
	    break;
	  }
	}
      }
    }

    for(int i = 0;client_socket[i];i++){
      if(FD_ISSET(client_socket[i], &readfds)){
	//printf("client[%d]\n",i);
	if(read(client_socket[i], buffer, sizeof(buffer)) > 0){
	  printf("Received: [%s]\n", buffer);

	  //Checks for commands
	  if(buffer[0] == '!'){
	    
	    //Connecting to another room
	    if(strncmp(buffer, "!connect ", 9) == 0){
	      //Setting room num
	      int num = atoi(&buffer[9]);
	      if(num != 0){
		client_num[i] = num;
	      }
	      //Telling room someone has joined

	      char message[100] = "";
	      strcat(message, client_names[i]);
	      strcat(message, " has joined the server");
	      for(int x = 0;x < 100;x++){
		if(client_socket[x] && client_num[x] == client_num[i]){
		  write(client_socket[x], message, sizeof(message));
		}
	      }
	    }
	    
	    //Shouting to every server
	    else if(strncmp(buffer, "!shout ", 7) == 0){
	      //Adding name and shout symbol
	      char message[100] = "";
	      strcat(message, client_names[i]);
	      strcat(message, "(shout) : ");
	      strcat(message, buffer);
	      
	      for(int x = 0;x < 100;x++){
		if(client_socket[x]){
		  write(client_socket[x], message, sizeof(message));
		}
	      }
	    }
	    
	    //Setting a name
	    else if(strncmp(buffer, "!setname ", 9) == 0){
	      strcpy(client_names[i], &buffer[9]);
	    }
	    
	  }else{
	    //Writes message to all clients with the correct tag

	    //Adds name to message
	      char message[100] = "";
	      strcat(message, client_names[i]);
	      strcat(message, " : ");
	      strcat(message, buffer);
	      if(strncasecmp(buffer, "owo", 3) == 0){
		strcat(message, "\nOwOnator : What's this?");
	      }
	    for(int x = 0;x < 100;x++){
	      if(client_socket[x] && client_num[i] == client_num[x]){
	        write(client_socket[x], message, sizeof(message));
	      }
	    }
	  }
	}else{
	  //Removes client from list if he/she leaves
	  close(client_socket[i]);
	  client_socket[i] = 0;
	  client_num[i] = 0;
	  free(client_names[i]);
	}
      }
    }
  }

  return 0;
}

/*
void subserver(int client_socket, int *client_sockets, int i) {
  char buffer[BUFFER_SIZE];
  
  while (read(client_socket, buffer, sizeof(buffer))) {
    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    //process(buffer);
    for(int x = 0;x < i;x++){
      //printf("x : %d\n",x);
      write(client_sockets[x], buffer, sizeof(buffer));
    }
  }
  close(client_socket);
  exit(0);
}
*/

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
