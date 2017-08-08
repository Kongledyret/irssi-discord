#include "servers.h"

#include "irssi.h"
#include "impl.h"
#include <servers-setup.h>
#include <net-nonblock.h>
#include <servers.h>

#include <unistd.h>

#include "discord.h"

SERVER_REC *test_server_init_connect(SERVER_CONNECT_REC *conn) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "test_server_init_connect");

	if (strlen(conn->address) == 0) {
		string gateway = get_gateway();
		printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
		          "full gateway string: %s", gateway);
		char proto_len = strstr(gateway, "//") - gateway;
		conn->address = strdup((string) (proto_len + gateway + 2));
		if (proto_len == 4) {
			conn->port = 443;
		} else if (proto_len == 3) {
			conn->port = 3;
		}

		printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
		          "addr: %s:%d", conn->address, conn->port);
	}

	SERVER_REC *server = g_new0(SERVER_REC, 1);

	server->chat_type=PROTOCOL;

	server->connrec = conn;
	server_connect_ref(SERVER_CONNECT(conn));

	server_connect_init((SERVER_REC *) server);

	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          conn->address);

	return (SERVER_REC *) server;
}

void test(struct _GIOChannel *huh, void *ptr) {
	sleep(4);
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "loop");
}

static void channels_join(SERVER_REC *server, const char *channel, int automatic) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "switching to channel: %s", channel);
}


void test_server_connect(SERVER_REC *server) {
	//void *data = NULL;
	//net_connect_nonblock("gateway.discord.gg", 443, &((IPADDR){2, {{{2}}}}), test, data);
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "test_server_connect");
	server->channels_join = channels_join;
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "server is connected: %d", server->connected);
	server->connected = 1;
	server_start_connect(server); // TODO: handle return
	return;
}
