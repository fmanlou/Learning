#include <string.h>
#include <sys/socket.h>

#include "http/http.h"
#include "tcp/tcp.h"

static void http_build_request(http_t *http, conf_t *conf);

int
http_send(http_t *http, tcp_t *tcp, conf_t *conf)
{
	char str[MAX_STRING * 4];
	request_t *req = &(http->req);

	http_build_request(http, conf);
	memset(str, 0, sizeof(str));
	sprintf(str, "%s %s %s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", \
			req->method, req->url, req->version, \
			req->host, req->agent, req->accept, \
			req->lang, req->range, req->connection, \
			req->encode);
	printf("%s\n", str);

	return send(tcp->sockfd, str, strlen(str), 0);
}

int
http_recv(http_t *http, tcp_t *tcp)
{
	char buf[1024];
	int ret;

	memset(buf, 0, sizeof(buf));
	printf("Download file\n");
	while(1)
	{
		ret = recv(tcp->sockfd, buf, sizeof(buf), 0);
		printf("%d\n", ret);
		if(ret <= 0)
			break;
		printf("%s", buf);
	}
	printf("\n");
	return 0;
}

static
void
http_build_request(http_t *http, conf_t *conf)
{
	sprintf(http->req.method, "GET");		
	sprintf(http->req.url, "%s/%s", conf->dir, conf->file);		
	sprintf(http->req.version, "HTTP/1.1");		
	sprintf(http->req.host, "HOST: %s", conf->host);		
	sprintf(http->req.agent, "User-Agent: %s", "durl/1.0");		
	sprintf(http->req.accept, "Accept %s", \
			"text/html,application/xhtml+xml,application/xml;" \
			"q=0.9,image/avif,image/webp,image/apng,*/*;" \
			"q=0.8,application/signed-exchange;v=b3;q=0.9");		
	sprintf(http->req.lang, "Accept-Language: %s", "zh-CN,zh;q=0.9,en;q=0.8");		
	sprintf(http->req.range, "RANGE: bytes=%d-", 100);		
	sprintf(http->req.connection, "Connection: %s", "keep-alive");
	sprintf(http->req.encode, "Accept-Encoding %s", "gzip, deflate, br");		
}
