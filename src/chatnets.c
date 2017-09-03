#include "chatnets.h"
#include "core.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include "irssi/src/core/chatnets.h"

#include "utils.h"

static CHATNET_REC *create(void) {
	debug();
	return g_new0(CHATNET_REC, 1);
}

void chatnets_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->chatnet = MODULE_NAME;
	rec->create_chatnet = create;
}
