#include "queries.h"
#include "core.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/queries.h>

#include "utils.h"

#include "discord.h"
#include <jansson.h>

DISCORD_QUERY_REC *create(const char *server_tag,
                   const char *nick,
                   int automatic) {
	debug();
	DISCORD_QUERY_REC *rec = g_new0(DISCORD_QUERY_REC, 1);
	rec->chat_type = PROTOCOL;
	rec->server_tag = g_strdup(server_tag);
	rec->name = g_strdup(nick);

	query_init((QUERY_REC *) rec, automatic);
	return rec;
}

static void sig_created(DISCORD_QUERY_REC *query, int automatic) {
	debug();
	json_t *root = discord_get_channel_info(query->server->tok, query->name);
	query->visible_name = g_strdup(json_string_value(json_object_get(json_array_get(json_object_get(root, "recipients"), 0), "username")));
}

void queries_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->query_create = (QUERY_REC *(*)(const char *, const char *, int)) create;
}

#include <irssi/src/core/signals.h>

void queries_signals_init(void) {
	signal_add("query created", (SIGNAL_FUNC) sig_created);
}

