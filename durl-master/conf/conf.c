#include "conf.h"
#include "url.h"

int
configure_init(conf_t *conf, const char *url)
{
	if(0 != url_parse(conf, url))
		return -1;
	conf->num_connections = 4;
	conf->insecure = 0;
	conf->max_speed = 0;
	//conf->ai_family = AF_UNSPEC;
	conf->verbose = 1;
	conf->connection_timeout = 45;
	conf->reconnect_delay = 20;
	return 0;
}
