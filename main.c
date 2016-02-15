#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "error.h"
#include "WebSocketClient.h"


int g_sockfd;
char g_txBuffer[1024];
char g_rxBuffer[1024];

int main(int argc, char *argv[])
{
    int portno, n;
	ws_handshake_t default_hs = {0};

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
        error("ERROR opening socket");
    }
	printf("Connect\n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    printf("Connect %p %x\n", g_sockfd,serv_addr.sin_addr.s_addr);
//    if (connect(g_sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
//        error("ERROR connecting");
//    }
    
    printf("Sends Handshake\n");
	
	//Host: server.example.com
//Upgrade: websocket
//Connection: Upgrade
//Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==
//Sec-WebSocket-Protocol: chat, superchat
//Sec-WebSocket-Version: 13
//Origin: http://example.com
	
	default_hs.elems[0].attr_name = "Host";
	default_hs.elems[0].attr_val = "server.example.com";
	
	default_hs.elems[1].attr_name = "Upgrade";
	default_hs.elems[1].attr_val = "websocket";
	
	default_hs.elems[2].attr_name = "Connection";
	default_hs.elems[2].attr_val = "Upgrade";
	
	default_hs.elems[3].attr_name = "Sec-WebSocket-Key";
	default_hs.elems[3].attr_val = "x3JJHMbDL1EzLkh9GBhXDw==";
	
	default_hs.elems[4].attr_name = "Sec-WebSocket-Protocol";
	default_hs.elems[4].attr_val = "chat, superchat";
	
	default_hs.elems[5].attr_name = "Sec-WebSocket-Version";
	default_hs.elems[5].attr_val = "13";
	
	default_hs.elems[6].attr_name = "Origin";
	default_hs.elems[6].attr_val = "http://example.com";
	
    WSClient_SendHandshake(&default_hs);
	
    return 0;
}