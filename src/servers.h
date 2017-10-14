#ifndef SERVERS_GLOCK
#define SERVERS_GLOCK
#include <irssi/common.h>
#include <irssi/core/chat-protocols.h>

void servers_protocol_init(CHAT_PROTOCOL_REC *rec);

#include "discord.h"

typedef struct {
	#include <irssi/core/server-connect-rec.h>
	token tok;
} DISCORD_SERVER_CONNECT_REC;

#define STRUCT_SERVER_CONNECT_REC DISCORD_SERVER_CONNECT_REC
typedef struct {
	#include <irssi/core/server-rec.h>
	token tok;
} DISCORD_SERVER_REC;
#endif
