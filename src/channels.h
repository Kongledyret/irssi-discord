#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <stdbool.h>

void channels_protocol_init(CHAT_PROTOCOL_REC *rec);

void join(SERVER_REC *server, const char *data, int automatic);
bool is_channel(SERVER_REC *server, const char *data);
void send_message(SERVER_REC *server, const char *target, const char *msg, int target_type);
