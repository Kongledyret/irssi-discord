#include "queries.h"
#include "core.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/queries.h>

#include "utils.h"

QUERY_REC * create(const char *server_tag,
                   const char *data,
                   int automatic) {
	debug();
	return g_new0(QUERY_REC, 1);
}
void queries_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->query_create = create;
}

