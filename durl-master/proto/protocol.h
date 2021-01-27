#ifndef PROTOCOL_H
#define APP_LAYER_PROTOCOL_H

#define PROTO_INSECURE		(0<<0)
#define PROTO_SECURE		(1<<0)
#define PROTO_PROTO_FTP		(0<<1)
#define PROTO_PROTO_HTTP	(1<<1)

#define MAX_STRING		((size_t)1024)

#define PROTO_FTP		(PROTO_PROTO_FTP|PROTO_INSECURE)
#define PROTO_FTP_PORT	21

#define PROTO_FTPS		(PROTO_PROTO_FTP|PROTO_SECURE)
#define PROTO_FTPS_PORT 990

#define PROTO_HTTP		(PROTO_PROTO_HTTP|PROTO_INSECURE)
#define	PROTO_HTTP_PORT 80

#define PROTO_HTTPS		(PROTO_PROTO_HTTP|PROTO_SECURE)
#define PROTO_HTTPS_PORT 443

#define PROTO_DEFAULT			PROTO_HTTP
#define PROTO_DEFAULT_PORT		PROTO_HTTP_PORT

typedef struct {
	void *ptr;
	int type;

	int (*init)(void *ptr);
	int (*connect)(void *ptr);
	int (*request)(void *ptr);
	int (*response)(void *ptr, char *buf, int size);
	void (*disconnect)(void *ptr);
	int (*deinit)(void *ptr);
} app_layer_proto_t;
typedef app_layer_proto_t proto_t;

int protocol_init(proto_t *proto);

#endif
