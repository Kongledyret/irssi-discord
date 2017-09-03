#define UOFF_T_LONG_LONG 1
#include <irssi/src/common.h>
#include <irssi/src/fe-common/core/printtext.h>
#include <irssi/src/core/levels.h>
#include <irssi/src/lib-config/iconfig.h>
#include <irssi/src/core/signals.h>
#include <irssi/src/core/chatnets.h>
#include <irssi/src/core/chat-protocols.h>

//#include "irssi.h"

#include "chatnets.h"
#include "protocol.h"

//#include <irssi/src/core/chatnets.h>

static CHATNET_REC *create_chatnet(void) {
	return g_malloc0(sizeof(DISCORD_CHATNET_REC));
}

static void sig_chatnet_read(DISCORD_CHATNET_REC *rec, CONFIG_NODE *node) {
	rec->email = config_node_get_str(node, "email", NULL); 
}


void protocol_init_chatnet(CHAT_PROTOCOL_REC *rec) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
						"test_init_chatnet");
	signal_add("chatnet read", (SIGNAL_FUNC) sig_chatnet_read);
	rec->create_chatnet = create_chatnet;
}

