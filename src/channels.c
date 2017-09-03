#include "channels.h"
#include "core.h"

#include <stdbool.h>

#include <irssi/src/common.h>
#include <irssi/src/core/signals.h>
#include <irssi/src/core/chat-protocols.h>

#include <irssi/src/core/channels.h>
#include <irssi/src/core/servers.h>

#include "utils.h"

#include "servers.h"
#include <jansson.h>
#include "discord.h"

enum week{
	GUILD_TEXT,
	DM,
	GUILD_VOICE,
	GROUP_DM,
	GUILD_CATEGORY
};

static CHANNEL_REC * create(DISCORD_SERVER_REC *server,
                            const char *name,
                            const char *visible_name,
                            int automatic) {
	debug();
	CHANNEL_REC *rec = g_new0(CHANNEL_REC, 1);

	json_t *root = discord_get_channel_info(server->tok, name);
	printf("%s", json_dumps(root, 0));
	byte chan_type = json_integer_value(json_object_get(root, "type"));

	if ( chan_type == DM ) {
		//name = "test";
		visible_name = json_string_value(json_object_get(json_array_get(json_object_get(root, "recipients"), 0), "username")); // TODO: clean up
	} else {
		printf("group chat");
	}

	channel_init(rec, (SERVER_REC *) server, name, visible_name, automatic);
	return rec;
}

static void join(DISCORD_SERVER_REC *server, const char *data, int automatic) {
	debug();
	create(server, data, NULL, automatic);
}

static bool is_channel(SERVER_REC *server, const char *data) {
	debug();
	return true;
}

#include "servers.h"

#include "discord.h"

static void send_message(DISCORD_SERVER_REC *server, const char *target, const char *msg, int target_type) {
	debug();
	discord_send_message(server->tok, target, msg);
}

static void sig_connected(SERVER_REC *server) {
	/*
	 * Is there a reason to assign these functions when connected and not on
	 * init?
	 */
	server->channels_join = (void (*)(SERVER_REC *, const char *, int)) join;
	server->ischannel = (int (*)(SERVER_REC *, const char *)) is_channel;
	server->send_message = (void (*)(SERVER_REC *, string, string, int))send_message;
}

void channels_protocol_init(CHAT_PROTOCOL_REC *rec) {
	rec->channel_create = (CHANNEL_REC *(*)(SERVER_REC *, const char *, const char *, int)) create;
	signal_add("server connected", (SIGNAL_FUNC) sig_connected); // TODO: move signals out of protocol init
}

