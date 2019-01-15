#include "networking.h"
#include <curses.h>


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



  WINDOW *topwin;
  WINDOW *botwin;

  /*  Initialize ncurses  */

  
  if ( (topwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  
  
  if ( (botwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  

  topwin = newwin(18,40,0,0);
  refresh();
  

  //fds[0] is stdin, fds[1] is stdout
  if(fork() == 0){
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    while(1){
      read(server_socket, buffer, sizeof(buffer));
      wprintw(topwin, "%s\n", buffer);
      //wprintw(topwin, "are you okay??");
      //wrefresh(topwin);
      wrefresh(topwin);
    }
  }
  //when not reading from socket?
  else{
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    while (1) {
      // mvaddstr(13, 33, "Hello, world!");

      //printw("LALALLA");
      botwin = newwin(2,40,20,0);
      refresh();
      wmove(botwin,20,0);

      wprintw(botwin, "Your message:");
      wrefresh(botwin);
      wgetstr(botwin, buffer);
      // wscanw(botwin,"%s", buffer);
      wrefresh(botwin);
   /*  Clean up after ourselves  */
   
      //*strchr(buffer, '\n') = 0;


      //adds name to text
      strcpy(text,name);
      strcat(text,buffer);

      wrefresh(botwin);
      
      write(server_socket, text, sizeof(text));
      //wprintw(botwin,"writing : %s\n", buffer);

      delwin(botwin);

      //refresh();
    }
   
  }

  delwin(topwin);
  delwin(botwin);
  endwin();
  return 0;

}
