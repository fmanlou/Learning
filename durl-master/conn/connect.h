#ifndef CONNECT_H
#define CONNECT_H

#include <stdio.h>
#include "protocol.h"
#include "configure.h"

typedef struct {
	proto_t proto;
} conn_t;

int connection_init(conn_t *conn, conf_t *conf);
int make_connect(conn_t *conn);
int fetch_response(conn_t *conn, char *buf, int size);
void connection_deinit(conn_t *conn);


#endif
