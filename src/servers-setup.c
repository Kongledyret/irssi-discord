#include "servers-setup.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/servers-setup.h>

static SERVER_SETUP_REC *create(void) {
		return g_new0(SERVER_SETUP_REC, 1);
}

void servers_setup_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->create_server_setup = create;
}
