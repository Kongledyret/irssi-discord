#include "irssi.h"
#include "channels.h"

#include <channels-setup.h>
#include <channels.h>

static CHANNEL_SETUP_REC *create_channel_setup(void) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "setup_channel");
	return g_malloc0(sizeof(CHANNEL_SETUP_REC));
}

static CHANNEL_REC *channel_create(SERVER_REC *server, const char *name, const char *visible_name, int automatic) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "create_channel");
	CHANNEL_REC *rec = g_new0(CHANNEL_REC, 1);
	channel_init((CHANNEL_REC *) rec, (SERVER_REC *) server, name, visible_name, automatic);
	return rec;
}

void channels_join(SERVER_REC *server, const char *channel, int automatic) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "switching to channel: %s", channel);
	channel_create(server, channel, NULL, automatic);
}

void protocol_init_channels(CHAT_PROTOCOL_REC *rec) {
	rec->create_channel_setup = create_channel_setup;
	rec->channel_create = (CHANNEL_REC *(*) (SERVER_REC *, const char *, const char *, int)) channel_create;
}
