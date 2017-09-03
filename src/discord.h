typedef unsigned long long group_ID;
typedef int user_ID;
typedef const char *token;

typedef const char *string;
string get_gateway(void);
int authorize(void);

#define UOFF_T_LONG_LONG 1
#include <irssi/src/core/core.h>
#include <irssi/src/core/network.h>

void discord_send_message(group_ID id, string message);
#include <stdbool.h>
#include "servers.h"
bool discord_websocket_handshake(DISCORD_SERVER_REC *rec);

token email_login(const char *email, char *password);
