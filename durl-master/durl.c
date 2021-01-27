#include "durl.h"

int
durl_init(durl_t *durl, const char *url)
{
	conf_t *conf;	
	conn_t *conn;

	conf = calloc(1, sizeof(conf_t));
	if(conf == NULL)
		return -1;
	conn = calloc(1, sizeof(conn_t));
	if(conf == NULL)
		return -1;
	durl->conf = conf;
	durl->conn = conn;

	if(0 != configure_init(conf, url))
		return -1;
	conn->conf = conf;
	connection_init(conn);
}

int
durl_fetch_file(durl_t *durl)
{
	durl->conn->make_request();

}
