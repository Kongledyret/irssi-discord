typedef unsigned long long group_ID;
typedef int user_ID;

typedef const char *string;
string get_gateway(void);
int authorize(void);
void discord_send_message(group_ID id, string message);
