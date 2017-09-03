#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

void queries_protocol_init(CHAT_PROTOCOL_REC *rec);

void queries_signals_init(void);

#include "servers.h"

#define STRUCT_SERVER_REC DISCORD_SERVER_REC
typedef struct {
	#include <irssi/src/core/query-rec.h>
} DISCORD_QUERY_REC;

