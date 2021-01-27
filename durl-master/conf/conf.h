#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <stdio.h>
#include <stdint.h>

#define MAX_STRING 4096

typedef struct {
	char output_filename[MAX_STRING];
	char dir[MAX_STRING];
	char file[MAX_STRING];
	char host[MAX_STRING];
	char proto[MAX_STRING];
	int port;
	uint16_t num_connections;
	int save_state_interval;
	int verbose;
	int insecure;
	int connection_timeout;
	int reconnect_delay;
	//sa_family_t ai_family;
	unsigned long long max_speed;
} conf_t;

int configure_init(conf_t *conf, const char *url);

#endif
