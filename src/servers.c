#include <stdbool.h>

#include "servers.h"

#include "irssi.h"
#include "impl.h"
#include <servers.h>
#include <net-nonblock.h>
#include <servers.h>

#include <unistd.h>

#include "discord.h"

#define IS_NOT_EMPTY(val) (val != NULL && *val != '\0')
static SERVER_REC *discord_server_init_connect(SERVER_CONNECT_REC *conn) {
	DISCORD_SERVER_CONNECT_REC *dconn = (DISCORD_SERVER_CONNECT_REC *) conn;
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
						"token: %s", dconn->token);
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "test_server_init_connect");

	if (strlen(dconn->address) == 0) {
		string gateway = get_gateway();
		printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
		          "full gateway string: %s", gateway);
		char proto_len = strstr(gateway, "//") - gateway;
		dconn->address = strdup((string) (proto_len + gateway + 2));
		if (proto_len == 4) {
			dconn->port = 443;
		} else if (proto_len == 3) {
			dconn->port = 3;
		}

		printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
		          "addr: %s:%d", dconn->address, dconn->port);
	}

	DISCORD_SERVER_REC *server = g_new0(DISCORD_SERVER_REC, 1);

	//strncpy(server->token, token, 59);
	//server->token = IS_NOT_EMPTY(token) ? g_strdup(token) : NULL;


	server->chat_type = PROTOCOL;

	server->connrec = dconn;
	server_connect_ref(SERVER_CONNECT(conn));

	server_connect_init((SERVER_REC *) server);

	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          conn->address);

	return (SERVER_REC *) server;
}

static SERVER_CONNECT_REC *create_server_connect(void) {
	return g_malloc0(sizeof(SERVER_CONNECT_REC));
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


	string msg2 = strdup(msg);
	discord_send_message(strtoll(target, (char **)(target + strlen(target)), 10), strdup(msg2));
}

static bool ischannel(SERVER_REC *server, const char *data) {
	return TRUE;
}

//TODO: signal for "server setup read" to add tokens and/or oath

#define printf(...) printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, __VA_ARGS__)

#include "channels.h"
static void test_server_connect(SERVER_REC *server) {
	//void *data = NULL;
	//net_connect_nonblock("gateway.discord.gg", 443, &((IPADDR){2, {{{2}}}}), test, data);
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "test_server_connect");

	server->channels_join = channels_join;
	server->ischannel = (int (*)(SERVER_REC *, const char *)) ischannel;
	server->send_message=send_message;

	//server->connected = 1;
	int z = server_start_connect(server); // TODO: handle return
	printf("ret: %d", z);
	return;
}

static void destroy_server_connect(SERVER_CONNECT_REC *conn) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "test_server_destroy");
}


void protocol_init_servers(CHAT_PROTOCOL_REC *rec) {
	rec->server_init_connect = discord_server_init_connect;
	rec->server_connect = test_server_connect;
	rec->create_server_connect = create_server_connect;
	rec->destroy_server_connect = destroy_server_connect;
}
