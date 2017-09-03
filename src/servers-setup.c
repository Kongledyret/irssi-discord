#include "servers-setup.h"
#include "core.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/servers-setup.h>

#include "utils.h"

static SERVER_SETUP_REC *create(void) {
	debug();
	return g_new0(SERVER_SETUP_REC, 1);
}

void servers_setup_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->create_server_setup = create;
}

#include <irssi/src/lib-config/iconfig.h>

static void read_config(SERVER_SETUP_REC *proto, CONFIG_NODE *node) {
	debug();
	printf(config_node_get_str(node, "token", NULL));
}

#include <irssi/src/core/signals.h>

void servers_setup_signals_init(void) {
	signal_add("server setup read", (SIGNAL_FUNC) read_config);
}
