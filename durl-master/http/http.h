#ifndef HTTP_H
#define HTTP_H

#include "tcp/tcp.h"

typedef struct {
	char method[10];
	char url[MAX_STRING];
	char version[10];
	char host[40];
	char agent[MAX_STRING];
	char accept[MAX_STRING];
	char lang[40];
	char range[40];
	char connection[20];
	char encode[40];
	char *body;
} request_t;

typedef struct {
	char version[10];
	int statuscode;
	char statusmes[10];
	char date[50];
	char server[40];
	char conttype[50];
	int contlen;
	char *body;
} response_t;

typedef struct {
	request_t req;
	response_t res;	
} http_t;

int http_send(http_t *http, tcp_t *tcp, conf_t *conf);
int http_recv(http_t *http, tcp_t *tcp);

#endif
