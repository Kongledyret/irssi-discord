#include "chatnets.h"
#include "core.h"

#include <irssi/src/common.h>
#include <irssi/src/core/core.h>
#include <irssi/src/core/chat-protocols.h>

#include "irssi/src/core/chatnets.h"

#include "utils.h"

static DISCORD_CHATNET_REC *create(void) {
	debug();
	return g_new0(DISCORD_CHATNET_REC, 1);
}

void chatnets_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->chatnet = MODULE_NAME;
	rec->create_chatnet = (CHATNET_REC *(*)(void))create;
}

#include <irssi/src/lib-config/iconfig.h>

static void read_config(DISCORD_CHATNET_REC *rec, CONFIG_NODE *node) {
	debug();
	rec->email = config_node_get_str(node, "email", NULL);
}

#include <irssi/src/core/signals.h>

void chatnets_signals_init(void) {
	signal_add("chatnet read", (SIGNAL_FUNC) read_config);
}
