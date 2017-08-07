#include "irssi.h"
#include "queries.h"

#include <queries.h>

QUERY_REC *test_query_create(const char *server_tag, const char *nick, int automatic) {
	QUERY_REC *rec = g_new0(QUERY_REC, 1);
	rec->chat_type = PROTOCOL;
	rec->name = g_strdup(nick);
	rec->server_tag = g_strdup(server_tag);
	query_init(rec, automatic);
	return rec;
}
