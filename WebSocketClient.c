#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "error.h"
#include "WebSocketClient.h"


//Host: server.example.com
//Upgrade: websocket
//Connection: Upgrade
//Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==
//Sec-WebSocket-Protocol: chat, superchat
//Sec-WebSocket-Version: 13
//Origin: http://example.com

//ws_handshake_t default_hs = {
//    {"Host", NULL},
//    {"Upgrade", NULL},
//    {"Connection", NULL},
//    {"Sec-WebSocket-Key", NULL},
//    {"Sec-WebSocket-Protocol", NULL},
//    {"Sec-WebSocket-Version", NULL},
//    {"Origin", NULL},
//    };

extern int g_sockfd;
extern char g_txBuffer[1024];
extern char g_rxBuffer[1024];

char* WSClient_SendHandshake(ws_handshake_t *hsList)
{
    int idx;
	int buff_len = 0;
	int sent_len, read_len;
    
    buff_len = sprintf(g_txBuffer, HANDSHAKE_HEADER);
    for(idx = 0; idx < MAX_ELEMS; idx++){
        if(hsList->elems[idx].attr_val == NULL){
            continue;
        }
        buff_len += sprintf(g_txBuffer + buff_len, "%s: %s\r\n", hsList->elems[idx].attr_name, hsList->elems[idx].attr_val);
    }
    buff_len += sprintf(g_txBuffer + buff_len, "\r\n");
    
	for(idx = 0; idx < buff_len; idx++){
		printf("g_txBuffer[%d] = 0x%x",idx, g_txBuffer[idx]);
	}
    
    sent_len = write(g_sockfd,g_txBuffer, buff_len);
    if (sent_len < 0) {
        error("ERROR writing to socket");
    }
    
    read_len = read(g_sockfd,g_rxBuffer, sizeof(g_rxBuffer));
    if (read_len < 0) {
        error("ERROR reading from socket");
    }
	
    return g_rxBuffer;
}
    
    