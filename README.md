# MKS65C-FinalProject
Final Project for Systems

Multiple Client Chat Program
Andy Zhou, Calvin Aw

Broad description of project:
Multiple clients can connect to a server and they can chat with one another.

Required libraries: 
<stdio.h>  
<stdlib.h>  
<unistd.h>  
<sys/types.h>  
<sys/socket.h>  
<netinet/in.h>  
<arpa/inet.h>  
<netdb.h>  
<string.h>  
<errno.h>  


Instructions on how to use project:
1. make  
2. ./server  
3. ./client  
   ./client <port>  

Commands:  
!connect <roomnum>  
	 Connects to the specified room  
!shout <message>  
	Shouts to everyone regardless of room  
!setname <name>  
	 Changes your name  

To exit,
1. Ctrl + C on client
   Please exit on clients first or memory leaks will appear at your doorsteps to haunt you
2. Ctrl + C on server
