#include "channels.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/channels.h>

#include "utils.h"

static CHANNEL_REC * create(SERVER_REC *server,
                            const char *name,
                            const char *visible_name,
                            int automatic) {
	debug();
	return g_new0(CHANNEL_REC, 1);
}

void channels_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->channel_create = create;
}
