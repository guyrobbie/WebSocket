#ifndef _WSClient_H_
#define _WSClient_H_

#define MAX_ELEMS           20
#define HANDSHAKE_HEADER    "GET /chat HTTP/1.1\r\n"

typedef struct _ws_hs_element_t{
    char *attr_name;
    char *attr_val;
}ws_hs_element_t;

typedef struct _ws_handshake_t{
    ws_hs_element_t elems[MAX_ELEMS];
}ws_handshake_t;

char* WSClient_SendHandshake(ws_handshake_t *hsList);

#endif /* #ifndef _WSClient_H_ */