#include "protocol.h"
#include "http.h"
#include "ftp.h"

int
protocol_init(proto_t *proto, conf_t *conf)
{
	switch(proto->type)
	{
		case PROTO_HTTP:
			protocol_http_init(proto, conf);
		case PROTO_FTP:
			protocol_ftp_init(proto, conf);
		default:
			loge("Unsupported protocol\n");
	}
}

static
int
protocol_http_init(proto_t *proto)
{
	proto->ptr = (http_t *)calloc(1, sizeof(http_t));
	proto->init = http_init;
	proto->request = http_request;
	proto->response = http_response;
	proto->deinit = http_deinit;
	proto->init(proto->ptr);
}

static
int
protocol_ftp_init()
{
	proto->ptr = (http_t *)calloc(1, sizeof(http_t));
	proto->init = ftp_init;
	proto->connect = ftp_connect;
	proto->request = ftp_request;
	proto->disconnect = ftp_disconnect;
	proto->response = ftp_response;
	proto->deinit = ftp_deinit;
	proto->init(proto->ptr);
}
