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

  int lfd = 0,cfd = 0;
  int ret = 0;
  char buf[BUFSIZ];
  
  struct sockaddr_in server_addr,client_addr;
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  lfd = socket(AF_INET,SOCK_STREAM,0);
  if(lfd == -1){
    printf("socket error!\n");
  }
   
  bind(lfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
  
  listen(lfd,128);
  
  socklen_t client_addr_len = sizeof(client_addr);

  cfd = accept(lfd,(struct sockaddr *)&client_addr,&client_addr_len);
  if(cfd == -1){
    printf("socket error!\n");
  }
  
  char client_ip[64];

  printf("client ip:%s port:%d\n",
          inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,client_ip,sizeof(client_ip)),
          ntohs(client_addr.sin_port));

  int counter = 5;
  int i;

  while(--counter != 0){
    ret = read(cfd,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,ret);
    for(i=0;i<ret;i++){
      buf[i] = toupper(buf[i]);
    }
    write(cfd,buf,ret);
  }

  close(lfd);
  close(cfd);

  return 0;
}

