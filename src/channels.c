#include "channels.h"

#include <stdbool.h>

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/channels.h>

#include "utils.h"

static CHANNEL_REC * create(SERVER_REC *server,
                            const char *name,
                            const char *visible_name,
                            int automatic) {
	debug();
	CHANNEL_REC *rec = g_new0(CHANNEL_REC, 1);
	channel_init(rec, server, name, visible_name, automatic);
	return rec;
}

void channels_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->channel_create = create;
}

void join(SERVER_REC *server, const char *data, int automatic) {
	debug();
	create(server, data, NULL, automatic);
}

bool is_channel(SERVER_REC *server, const char *data) {
	debug();
	printf(data);
	return true;
}

void send_message(SERVER_REC *server, const char *target, const char *msg, int target_type) {
	debug();
}
