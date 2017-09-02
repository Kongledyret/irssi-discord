#include "servers.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/servers.h>

#include "utils.h"

static SERVER_CONNECT_REC *create(void) {
	return g_new0(SERVER_CONNECT_REC, 1);
}

static SERVER_REC *init(SERVER_CONNECT_REC *connrec) {
	return g_new0(SERVER_REC, 1);
}
static void connect(SERVER_REC *server) {
	return;
}

static void destroy(SERVER_CONNECT_REC *conn) {
	return;
}

void servers_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->create_server_connect = create;
	rec->server_init_connect = init;
	rec->server_connect = connect;
	rec->destroy_server_connect = destroy;
}
