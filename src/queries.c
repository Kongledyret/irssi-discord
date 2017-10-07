#include "queries.h"
#include "core.h"

#include <irssi/src/common.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/queries.h>

#include "utils.h"

#include "discord.h"
#include <jansson.h>

#include <irssi/src/fe-common/core/module-formats.h>

static DISCORD_QUERY_REC *create(const char *server_tag,
                                 const char *nick,
                                 int automatic) {
	debug();
	printf("server tag is %s", server_tag);
	DISCORD_QUERY_REC *rec = g_new0(DISCORD_QUERY_REC, 1);
	rec->chat_type = PROTOCOL;
	rec->server_tag = g_strdup(server_tag);
	rec->name = g_strdup(nick);

	query_init((QUERY_REC *) rec, automatic);
	/*
	 *
	 *printformat_module("fe-common/core", server, target,
>-  MSGLEVEL_PUBLIC | MSGLEVEL_NOHILIGHT |
>-  MSGLEVEL_NO_ACT,
>-  TXT_OWN_MSG_CHANNEL,
>-  server->nick, optarget, msg, nickmode);
*/
	//TEXT_DEST_REC dest;
	//format_create_dest_tag(&dest, NULL, server_tag, rec->visible_name, MSGLEVEL_ALL | MSGLEVEL_NEVER | MSGLEVEL_LASTLOG, rec->window);
	//printformat_module_dest("fe-common/core", &dest, 
	/* TODO: use own fe-common module where I can specify the time. see
	 * https://github.com/cdidier/irssi-xmpp/blob/e7a5528d097bd732fa0933dd9639e56c6bfb85de/src/fe-common/fe-xmpp-messages.c#L123
	 * */

	json_t *root = discord_get_message_history(rec->server->tok, rec->name);
	printf("%d", json_array_size(root));
	//json_array_foreach(root, index, message) { // I want to use foreach but I
	//have to reverse it
	for (size_t index = json_array_size(root) - 1; index < -1LL; index--) {
		json_t *message = json_array_get(root, index);
		const char *username = json_string_value(json_object_get(json_object_get(message, "author"), "username"));
		printformat_module_window("fe-common/core", rec->window, MSGLEVEL_MSGS,
			TXT_MSG_PRIVATE_QUERY, username, "", json_string_value(json_object_get(message, "content")));
	}
	//printformat_module_window("fe-common/core", rec->window, MSGLEVEL_ALL,
		//TXT_PUBMSG_CHANNEL, "msirabella", "optarget", "text", "nickmode");
	
	return rec;
}

static void sig_created(DISCORD_QUERY_REC *query, int automatic) {
	debug();

	json_t *root = discord_get_channel_info(query->server->tok, query->name); /*Dont move this to  creation, small bugs*/
	query->visible_name = g_strdup(json_string_value(json_object_get(json_array_get(json_object_get(root, "recipients"), 0), "username")));
}
*/

void queries_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->query_create = (QUERY_REC *(*)(const char *, const char *, int)) create;
}

#include <irssi/src/core/signals.h>

/*
void queries_signals_init(void) {
	signal_add("query created", (SIGNAL_FUNC) sig_created);
}
*/

