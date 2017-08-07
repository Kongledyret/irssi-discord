#include "irssi.h"
#include "chatnets.h"
#include <chatnets.h>

static CHATNET_REC *create_chatnet(void) {
	return g_malloc0(sizeof(CHATNET_REC));
}


void protocol_init_chatnet(CHAT_PROTOCOL_REC *rec) {
	rec->create_chatnet = create_chatnet;
}

