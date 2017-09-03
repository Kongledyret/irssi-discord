#include "irssi.h"
#include <servers-setup.h>
#ifndef SERVER_GLOCK
#define SERVER_GLOCK

void protocol_init_servers(CHAT_PROTOCOL_REC *rec);

struct _DISCORD_SERVER_CONNECT_REC {
	#include <irssi/src/core/server-connect-rec.h>
	unsigned int heartbeat_interval;
	const char *token;
	const char *email;
};

typedef struct _DISCORD_SERVER_CONNECT_REC DISCORD_SERVER_CONNECT_REC;
#define STRUCT_SERVER_CONNECT_REC DISCORD_SERVER_CONNECT_REC
struct _DISCORD_SERVER_REC {
	#include <irssi/src/core/server-rec.h>
};

typedef struct _DISCORD_SERVER_REC DISCORD_SERVER_REC;
#endif
