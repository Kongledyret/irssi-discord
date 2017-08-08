#include "irssi.h"

//CHANNEL_REC *test_channel_create(SERVER_REC *server, const char *name, const char *visible_name, int automatic);
void channels_join(SERVER_REC *server, const char *channel, int automatic);
void protocol_init_channels(CHAT_PROTOCOL_REC *rec);
