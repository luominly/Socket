#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>

int main(){
  
  int cfd = socket(AF_INET,SOCK_STREAM,0);
  if(cfd == -1){
    printf("sock init error\n");
  }
  
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = ntohs(8080);
  inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr.s_addr);

  int ret = connect(cfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
  if(ret == -1){
    printf("connect error\n");
  }

  int counter = 5;
  char buf[BUFSIZ];
  while(--counter != 0){
    write(cfd,"hello\n",6);
    ret = read(cfd,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,ret);
  }

  close(cfd);

  return 0;
}
