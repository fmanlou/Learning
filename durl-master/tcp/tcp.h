#ifndef TCP_H
#define TCP_H

#include "conf/conf.h"

#ifdef HAVE_SSL
#include <openssl/ssl.h>
#endif

typedef struct {
	int sockfd;
	struct addrinfo *ailist;
#ifdef HAVE_SSL
	SSL *ssl;
#endif
} tcp_t;

int tcp_init(tcp_t *tcp, const conf_t *conf);
int tcp_connect(tcp_t *tcp);
void tcp_disconnect(tcp_t *tcp);
void tcp_free(tcp_t *tcp);

#endif
