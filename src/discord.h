#include "core.h"

typedef const char *string;

typedef const char channel_ID[19];
typedef string token;

#define BASE_API "https://discordapp.com/api/v" DISCORD_VERSION
void discord_send_message(token tok, channel_ID target, string msg);
