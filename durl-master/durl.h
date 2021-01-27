#ifndef DURL_H
#define DURL_H

#include "configure.h"

typedef struct {
	conn_t *conn;
	conf_t *conf;
} durl_t;

int durl_init(durl_t *durl, const char *url);
int durl_fetch_file(durl_t *durl);
int durl_deinit(durl_t *durl);

#endif
