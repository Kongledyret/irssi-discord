#include "servers-setup.h"
#include "core.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/servers-setup.h>

#include "utils.h"

static DISCORD_SERVER_SETUP_REC *create(void) {
	debug();
	return g_new0(DISCORD_SERVER_SETUP_REC, 1);
}

void servers_setup_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->create_server_setup = (SERVER_SETUP_REC *(*)(void)) create;
}

#include <irssi/src/lib-config/iconfig.h>

static void read_config(DISCORD_SERVER_SETUP_REC *proto, CONFIG_NODE *node) {
	debug();
	proto->tok = config_node_get_str(node, "token", NULL);
}

#include "servers.h"

void fill_conn(DISCORD_SERVER_CONNECT_REC *conn, DISCORD_SERVER_SETUP_REC *sserver) {
	debug();
	//if (sserver->tok != NULL && conn->tok == NULL) 
	// ^^^ XXX This breaks stuff and I dont want to debug XXX ^^^
	conn->tok = g_strdup(sserver->tok);
}

#include <irssi/src/core/signals.h>

void servers_setup_signals_init(void) {
	signal_add("server setup read", (SIGNAL_FUNC) read_config);
	signal_add("server setup fill server", (SIGNAL_FUNC) fill_conn);
}
