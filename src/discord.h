#include "core.h"

typedef const char *string;

typedef const char chID[19];
typedef string token;

#define BASE_API "https://discordapp.com/api/v" DISCORD_VERSION
void discord_send_message(token tok, chID target, string msg);

#include <jansson.h>
json_t *discord_get_channel_info(token tok, chID channel);
json_t *discord_get_guild_info(token tok, chID channel);
json_t *discord_get_message_history(token tok, chID channel);
