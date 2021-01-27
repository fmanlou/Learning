#include <string.h>
#include "conf/conf.h"
#include "log/log.h"

int main(int argc, char **argv)
{
	conf_t conf;
	if(argc != 2)
	{
		fprintf(stderr, "Usage:\n" \
				"./conf url\n" \
				"./conf http://ftp.sjtu.edu.cn/" \
				"sites/ftp.kernel.org/pub/linux/kernel/v2.6/ChangeLog-2.6.0\n"
		);
		return 0;
	}
	memset(&conf, 0, sizeof(conf_t));
	configure_init(&conf, argv[1]);
	logi("port: %d\n", conf.port);
	logi("host: %s\n", conf.host);
	logi("dir: %s\n", conf.dir);
	logi("file: %s\n", conf.file);
}
