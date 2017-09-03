#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

void servers_setup_protocol_init(CHAT_PROTOCOL_REC *rec);
void servers_setup_signals_init(void);

#include "discord.h"

typedef struct {
	#include <irssi/src/core/server-setup-rec.h>
	token tok;
} DISCORD_SERVER_SETUP_REC;
