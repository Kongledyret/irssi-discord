#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>
void chatnets_protocol_init(CHAT_PROTOCOL_REC *rec);
void chatnets_signals_init(void);

#include "discord.h"

typedef struct {
	#include <irssi/src/core/server-setup-rec.h>
	string email;
} DISCORD_CHATNET_REC;
