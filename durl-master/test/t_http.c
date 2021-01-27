#include <string.h>
#include "http/http.h"
#include "log/log.h"
#include "tcp/tcp.h"
#include "conf/conf.h"

int main(int argc, char **argv)
{
	http_t http;
	tcp_t tcp;
	conf_t conf;
	int ret;
	if(argc != 2)
	{
		fprintf(stderr, "Usage:\n" \
				"./http url\n" \
				"./http http://ftp.sjtu.edu.cn/" \
				"sites/ftp.kernel.org/pub/linux/kernel/v2.6/ChangeLog-2.6.0\n"
		);
		return 0;
	}

	memset(&http, 0, sizeof(http));
	memset(&tcp, 0, sizeof(tcp));
	memset(&conf, 0, sizeof(conf));

	configure_init(&conf, argv[1]);
	tcp_init(&tcp, &conf);

	logi("tcp init\n");
	if(-1 == tcp_connect(&tcp))
		loge("tcp connect failed\n");
	else
		logi("tcp connect succeed\n");

	ret = http_send(&http, &tcp, &conf);
	logi("send %d\n", ret);
	ret = http_recv(&http, &tcp);
	logi("recv %d\n", ret);
	tcp_disconnect(&tcp);
	tcp_free(&tcp);
}
