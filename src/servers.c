#include "servers.h"
#include "core.h"

#include <irssi/common.h>
#include <irssi/core/signals.h>
#include <irssi/core/chat-protocols.h>

#include <irssi/core/servers.h>

#include "utils.h"

#include "channels.h"

static DISCORD_SERVER_CONNECT_REC *create(void) {
	debug();
	return g_new0(DISCORD_SERVER_CONNECT_REC, 1);
}

static DISCORD_SERVER_REC *init(DISCORD_SERVER_CONNECT_REC *connrec) {
	debug();
	DISCORD_SERVER_REC *server = g_new0(DISCORD_SERVER_REC, 1);
	server->chat_type = PROTOCOL;
	server->connrec = connrec;

	server->tok = g_strdup(connrec->tok);

	connrec->address = g_strdup("gateway.discord.gg");
	connrec->port = 443; // TODO: make this default a better way

	server_connect_ref(SERVER_CONNECT(connrec));
	server_connect_init((SERVER_REC *) server);
	return server;
}

static void sig_connected(DISCORD_SERVER_REC *server) {
	debug();
	server->connected = true; // XXX \\ Why do I have to do this tho
}

static void connect(DISCORD_SERVER_REC *server) {
	debug();
	server_start_connect((SERVER_REC *) server);
	printf("token: %s", server->tok);
	return;
}

static void destroy(SERVER_CONNECT_REC *conn) {
	debug();
	return;
}

void servers_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->create_server_connect = (SERVER_CONNECT_REC *(*)(void)) create;
	rec->server_init_connect = (SERVER_REC *(*)(SERVER_CONNECT_REC *)) init;
	rec->server_connect = (void (*)(SERVER_REC *)) connect;
	rec->destroy_server_connect = destroy;

	signal_add_first("server connected", (SIGNAL_FUNC) sig_connected);
}
