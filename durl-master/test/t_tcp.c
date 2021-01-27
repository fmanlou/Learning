#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#include "tcp/tcp.h"
#include "log/log.h"
#include "lib/compat-bsd.h"

int main(int argc, char **argv)
{
	char buf[1024];
	tcp_t tcp;
	conf_t conf;

	if(argc != 3)
	{
		fprintf(stderr, "Usage:\n" \
				"./tcp host port\n" \
				"./conf www.baidu.com 80\n"
		);
		return 0;
	}

	memset(buf, 0, sizeof(buf));
	strlcpy(conf.host, argv[1], sizeof(conf.host));
	sscanf(argv[2], "%d", &conf.port);

	tcp_init(&tcp, &conf);
	if(-1 == tcp_connect(&tcp))
		logi("tcp connect failed\n");
	else
		logi("tcp connect succeed\n");

	if(send(tcp.sockfd, "test", 4, 0) <= 0)
		logi("tcp send failed\n");
	else
		logi("tcp send succeed\n");
	if(0 >= recv(tcp.sockfd, buf, sizeof(buf), 0))
		logi("tcp recv failed\n");
	else
		logi("tcp recv succeed\n");
	logi("HTTP response:\n%s\n", buf);
	tcp_disconnect(&tcp);
	tcp_free(&tcp);
}
