#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include "error.h"
#include "WebSocketClient.h"
#include "debug.h"

extern ws_handshake_t default_hs;
int g_sockfd;
char g_txBuffer[1024];
char g_rxBuffer[1024];

int main(int argc, char *argv[])
{
    int portno, ret;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    g_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (g_sockfd < 0) {
        error("when opening socket");
    }
	printf("Connect\n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    TRACE("Connect to address: %s", inet_ntoa(serv_addr.sin_addr));

	ret = connect(g_sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if (ret < 0){
        error("in connect");
    }
    
    TRACE("Sends Handshake");
    WSClient_SendHandshake(&default_hs);

    return 0;
}