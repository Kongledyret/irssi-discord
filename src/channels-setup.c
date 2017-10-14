#include "channels-setup.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/channels-setup.h>

#include "utils.h"

static CHANNEL_SETUP_REC * create(void) {
	debug();
	return g_new0(CHANNEL_SETUP_REC, 1);
}

void channels_setup_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->create_channel_setup = create;
}
