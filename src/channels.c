#include "irssi.h"
#include "channels.h"

#include <channels-setup.h>
#include <channels.h>

CHANNEL_REC *test_channel_create(SERVER_REC *server, const char *name, const char *visible_name, int automatic) {
	CHANNEL_REC *rec = g_new0(CHANNEL_REC, 1);
	channel_init((CHANNEL_REC *) rec, (SERVER_REC *) server, name, visible_name, automatic);
	return rec;
}
