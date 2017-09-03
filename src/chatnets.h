//#include "irssi.h"

#ifndef CHATNET_GLOCK
#define CHATNET_GLOCK

void protocol_init_chatnet(CHAT_PROTOCOL_REC *rec);

struct _DISCORD_CHATNET_REC {
	#include <irssi/src/core/chatnet-rec.h>
	const char *email;
};
typedef struct _DISCORD_CHATNET_REC DISCORD_CHATNET_REC;
#endif
