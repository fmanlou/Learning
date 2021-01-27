#include "log.h"

int main()
{
	log_set_quiet(1);
	loge("hello world\n");
	log_set_quiet(0);
	logt("hello world\n");
	logd("hello world\n");
	logi("hello world\n");
	loge("hello world\n");
	logf("hello world\n");
	log_set_level(LOG_INFO);
	logt("hello world\n");
	logd("hello world\n");
	logi("hello world\n");
	loge("hello world\n");
	logf("hello world\n");
}
