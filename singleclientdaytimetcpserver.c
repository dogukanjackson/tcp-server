/* gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
Doğukan ÇİFTÇİ 230201071 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
/*#define AF_INET
#define AF_INET6*/
const char APRESSMESSAGE[]="MY FIRST SERVER!\n";
int main(int argc, char *argv[]){
   int SimpleSocket=0;
   int SimplePort=0;
   int returnStatus=0;
   struct sockaddr_in SimpleServer;
   if(argc!=2){
      fprintf(stderr, "Usage: %s <port>\n", argv[0]);
      exit(1);   
   }
   SimpleSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if (SimpleSocket==-1){
      fprintf(stderr, "Could not create socket!\n");
      
      exit(1);
   }
   else{
   fprintf(stderr,"Socket created!\n");
   
   }
   SimplePort=atoi(argv[1]);
   bzero(&SimpleServer, sizeof(SimpleServer));
   SimpleServer.sin_family=AF_INET;
   SimpleServer.sin_addr.s_addr=htonl(INADDR_ANY);
   SimpleServer.sin_port= htons(SimplePort);
   returnStatus= bind(SimpleSocket, (struct sockaddr *)&SimpleServer,sizeof(SimpleServer));
   if (returnStatus==0){
       fprintf(stderr,"Bind completed!\n");
   }
   else{
   fprintf(stderr,"Could not bind to address!\n");
   close(SimpleSocket);
   exit(1);
   }
   returnStatus=listen(SimpleSocket,5);
   if (returnStatus==-1){
   fprintf(stderr,"Cannot listen on socket!\n");
   close(SimpleSocket);
   exit(1);
   }
   while(1){
      struct sockaddr_in ClientName ={0};
      int SimpleClient=0;
      int ClientNameLenght=sizeof(ClientName);
      SimpleClient= accept(SimpleSocket, (struct sockaddr *)&ClientName, &ClientNameLenght);
      printf("%cconnected");
      if (SimpleClient==-1){
         fprintf(stderr, "Cannot accept connections!\n");
         close(SimpleSocket);
         exit(1); 
         }
   time_t currenttime=time(NULL);
   char message[200];
   struct tm Tm=*localtime(&currenttime);
   snprintf(message,sizeof(message),"Connected\nIt is: %d-%d-%d Time is:%d: %d: %d\ndisconnected\n",Tm.tm_year+1900,Tm.tm_mon+1,Tm.tm_mday,Tm.tm_hour, Tm.tm_min,Tm.tm_sec);
   write (SimpleClient, message,strlen(message));
   close(SimpleClient);
   }
   close(SimpleSocket);

   	  int clientSocket=accept(SimpleSocket,NULL,NULL);

   return 0;
}








