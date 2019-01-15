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


  

  //fds[0] is stdin, fds[1] is stdout
  if(fork() == 0){
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    while(1){
      read(server_socket, buffer, sizeof(buffer));
      printf("%s\n", buffer);
      //wprintw(topwin, "are you okay??");
      //wrefresh(topwin);
      //wrefresh(topwin);
    }
  }
  //when not reading from socket?
  else{
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    while (1) {
      // mvaddstr(13, 33, "Hello, world!");

       fgets(buffer, sizeof(buffer), stdin);	
       *strchr(buffer, '\n') = 0;	      //printw("LALALLA");
   /*  Clean up after ourselves  */

       //*strchr(buffer, '\n') = 0;



       //adds name to text	     
      strcpy(text,name);	      
      strcat(text,buffer);	    


      write(server_socket, text, sizeof(text));	     
      printf("writing : %s\n", buffer);
      //printw("LALALLA");
     
      //refresh();
    }
   
  }



}
