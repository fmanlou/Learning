#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "tcp/tcp.h"
#include "log/log.h"

int
tcp_init(tcp_t *tcp, const conf_t *conf)
{
	struct addrinfo hint;
	int errcode;
	char addrstr[100];

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags |= AI_ADDRCONFIG;
	hint.ai_protocol = 0;

	errcode = getaddrinfo(conf->host, "80", &hint, &(tcp->ailist));
	if(errcode != 0)
	{
		loge("Unable to connect to server %s(%s)\n", conf->host, gai_strerror(errcode));
		return -1;
	}
}

int
tcp_connect(tcp_t *tcp)
{
	struct addrinfo *aip;

	for(aip = tcp->ailist; aip != NULL; aip = aip->ai_next)
	{
			tcp->sockfd = socket(aip->ai_family, aip->ai_socktype, aip->ai_protocol);
			if(0 == connect(tcp->sockfd, aip->ai_addr, aip->ai_addrlen))
			{
					logd("tcp connected\n");
					return 0;
			}
	}
	return -1;
}

void
tcp_disconnect(tcp_t *tcp)
{
	close(tcp->sockfd);
	logd("tcp disconnected\n");
}

void
tcp_free(tcp_t *tcp)
{
	freeaddrinfo(tcp->ailist);
}
