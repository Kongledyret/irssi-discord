#include "servers.h"

#include "irssi.h"
#include "impl.h"
#include <servers-setup.h>
#include <servers.h>

SERVER_REC *test_server_init_connect(SERVER_CONNECT_REC *conn) {
	SERVER_REC *server = g_new0(SERVER_REC, 1);

	server->chat_type=PROTOCOL;

	server->connrec = conn;
	server_connect_ref(SERVER_CONNECT(conn));

	server_connect_init((SERVER_REC *) server);

	return (SERVER_REC *) server;
}

void test_server_connect(SERVER_REC *server) {
	return;
}
