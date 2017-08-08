#include "irssi.h"
#include "chatnets.h"
#include <chatnets.h>

static CHATNET_REC *create_chatnet(void) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
						"test_create_chatnet");
	return g_malloc0(sizeof(CHATNET_REC));
}


void protocol_init_chatnet(CHAT_PROTOCOL_REC *rec) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
						"test_init_chatnet");
	rec->create_chatnet = create_chatnet;
}

