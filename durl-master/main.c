#include <stdio.h>
#include <stdlib.h>
#include "durl.h"

int main(int argc, char *argv[])
{
	durl_t *durl;
	durl = calloc(1, sizeof(durl_t));
	if(argc != 2)
	{
		fprintf(stderr, "Usage: axdl <url>\n");
		return 1;
	}
	durl_init(durl, argv[1]);
	durl_fetch_file(durl);
	durl_deinit(durl);
	return 0;
}
