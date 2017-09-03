typedef const char *string;

typedef const char channel_ID[19];
typedef string token;

void discord_send_message(token tok, channel_ID target, string msg);
