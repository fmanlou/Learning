#include <string.h>
#include "lib/compat-bsd.h"
#include "conf/url.h"
#include "log/log.h"

void url_fetch_proto(conf_t *conf, const char *url);
void url_fetch_port(conf_t *conf, const char *url);
void url_fetch_hostname(conf_t *conf, const char *url);
void url_fetch_dir(conf_t *conf, const char *url);
void url_fetch_file(conf_t *conf, const char *url);

void
url_parse(conf_t *conf, const char *url)
{
	url_fetch_proto(conf, url);
	url_fetch_port(conf, url);	
	url_fetch_hostname(conf, url);
	url_fetch_dir(conf, url);
	url_fetch_file(conf, url);
}

void
url_fetch_proto(conf_t *conf, const char *url)
{
	char *index;
	
	index = strstr(url, "://");
	if(index == NULL)
		return;

	strlcpy(conf->proto, url, index -url);
	/*
	if(index == NULL)
	{
		conf->proto =  PROTO_DEFAULT;
		return 0;
	}
	printf("proto len: %d\n", proto_strlen);
	if(strncmp(url, "http", proto_strlen) == 0) 
		conf->proto = PROTO_HTTP;	
	else if(strncmp(url, "https", proto_strlen) == 0) 
		conf->proto = PROTO_HTTPS;
	else if(strncmp(url, "ftp", proto_strlen) == 0) 
		conf->proto = PROTO_FTP;
	else if(strncmp(url, "ftps", proto_strlen) == 0) 
		conf->proto = PROTO_FTPS;
	else
	{
		loge("Unsupprted protocol\n");
		return -1;
	}
	*/
}

void
url_fetch_port(conf_t *conf, const char *url)
{
	/*
	switch(conf->proto)
	{
		case PROTO_FTP:
			conf->port = PROTO_FTP_PORT;
			break;
		case PROTO_FTPS:
			conf->port = PROTO_FTPS_PORT;
			break;
		case PROTO_HTTP:
			conf->port = PROTO_HTTP_PORT;
			break;
		case PROTO_HTTPS:
			conf->port = PROTO_HTTPS_PORT;
			break;
	}
	*/

	char *index;
	index = strstr(url, "://");
	if(index != NULL)
		url = index + 3;
	
	index = strchr(url, ':');
	if(index != NULL)
		sscanf(index + 1, "%i", &conf->port);
}

void
url_fetch_hostname(conf_t *conf, const char *url)
{
	char *index;
	index = strstr(url, "://");
	if(index != NULL)
		url = index + 3;

	/* IPv6 */
	if(*url == '[')
	{
		strlcpy(conf->host, url + 1, sizeof(conf->host));
		index = strchr(conf->host, ']');
		if(index != NULL)
			*(index + 1) = 0;
	}
	/* IPv4 */
	else
	{
		strlcpy(conf->host, url, sizeof(conf->host));
		/* remove file path */
		index = strchr(conf->host, '/');
		if(index != NULL)
			*index = 0;
		/* remove port */
		index = strchr(conf->host, ':');
		if(index != NULL)
			*index = 0;
	}
}

void
url_fetch_dir(conf_t *conf, const char *url)
{
	char *index;
	/* skip protocol:// */
	index = strstr(url, "://");
	if(index != NULL)
		url = index + 3;

	/* skip hostname */
	index = strchr(url, '/');
	if(index == NULL)
	{
		strcpy(conf->dir, "/");
		return;
	}
	else
		snprintf(conf->dir, MAX_STRING, "/%s", index + 1);

	/* remove url paramters */
	index = strchr(conf->dir, '?');
	if(index != NULL)
		*index = 0;

	/* remove file name */
	index = strrchr(conf->dir, '/');
	if(index != NULL)
		*index = 0;
}

void
url_fetch_file(conf_t *conf, const char *url)
{
	char *index;
	/* skip protocol:// */
	index = strstr(url, "://");
	if(index != NULL)
		url = index + 3;

	/* skip hostname */
	index = strchr(url, '/');
	if(index == NULL)
	{
		strcpy(conf->file, "/");
		return;
	}
	else
		snprintf(conf->file, MAX_STRING, "/%s", index + 1);

	/* remove url paramters */
	index = strchr(conf->file, '?');
	if(index != NULL)
		index = 0;

	/* remove dir */
	index = strrchr(conf->file, '/');
	if(index != NULL)
		strlcpy(conf->file, index + 1, sizeof(conf->file));
}

void 
url_fetch_username(conf_t *conf, const char *url)
{
	
}

void
url_fetch_passwd(conf_t *conf, const char *url)
{

}
