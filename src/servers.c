#include <stdbool.h>

#include "servers.h"

#include "irssi.h"
#include "impl.h"
#include <servers.h>
#include <net-nonblock.h>
#include <servers.h>

#include <unistd.h>

#include "discord.h"

static SERVER_CONNECT_REC *create_server_connect(void) {
	return g_malloc0(sizeof(SERVER_CONNECT_REC));
}

static SERVER_REC *test_server_init_connect(SERVER_CONNECT_REC *conn) {
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

static void send_message(SERVER_REC *server, string target, string msg, int target_type) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "target: %s", target);

	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "msg: %s", msg);

	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "target type: %d", target_type);

	discord_send_message(strtoll(target, (char **)(target + strlen(target)), 10), strdup(msg));
}
static bool ischannel(SERVER_REC *server, const char *data) {
	return TRUE;
}

//TODO: signal for "server setup read" to add tokens and/or oath

#include "channels.h"
static void test_server_connect(SERVER_REC *server) {
	//void *data = NULL;
	//net_connect_nonblock("gateway.discord.gg", 443, &((IPADDR){2, {{{2}}}}), test, data);
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "test_server_connect");

	server->channels_join = channels_join;
	server->ischannel = (int (*)(SERVER_REC *, const char *)) ischannel;
	server->send_message=send_message;

	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "server is connected: %d", server->connected);
	server->connected = 1;
	server_start_connect(server); // TODO: handle return
	return;
}

static SERVER_SETUP_REC *create_server_setup(void) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "server_setup");
	return g_malloc0(sizeof(SERVER_SETUP_REC));
}

static void destroy_server_connect(SERVER_CONNECT_REC *conn) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "test_server_destroy");
}


void protocol_init_servers(CHAT_PROTOCOL_REC *rec) {
	rec->server_init_connect = test_server_init_connect;
	rec->server_connect = test_server_connect;
	rec->create_server_connect = create_server_connect;
	rec->create_server_setup = create_server_setup;
	rec->destroy_server_connect = destroy_server_connect;
}
