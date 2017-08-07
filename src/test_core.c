
/* Originally this code was part of the irssi-lua module
 * <https://github.com/ahf/irssi-lua> and copyright as below:
 *
 * Copyright (c) 2009 Alexander Færøy <ahf@irssi.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "test_core.h"
#include <irssi.h>

#include "servers-setup.h"

#include "test_impl.h"

#define PROTOCOL_NAME "TEST"

static CHATNET_REC *create_chatnet(void) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
						"Hello, World. xxx \"%s\"", MODULE_NAME);
	return g_new0(CHATNET_REC, 1);
}
static SERVER_SETUP_REC *create_server_setup(void) {
	// This one
	//
	return g_new0(SERVER_SETUP_REC, 1);
}
static SERVER_CONNECT_REC *create_server_connect(void) {
	SERVER_CONNECT_REC *conn;

	conn = g_new0(SERVER_CONNECT_REC, 1);
	return (SERVER_CONNECT_REC *)conn;
}

SERVER_REC *server_init_connect(SERVER_CONNECT_REC *connrec) {
	SERVER_REC *server;
	return server;
}
SERVER_REC *server_connect(SERVER_CONNECT_REC *conn) {
	SERVER_REC *server = NULL;
	return server;
}


/*
CHANNEL_SETUP_REC *create_channel_setup(void) {
}
SERVER_CONNECT_REC *create_init_connect(void) {
}
void *destroy_server_connect(SERVER_CONNECT_REC *conn) {
}
*/


void test_init() {
	CHAT_PROTOCOL_REC *rec;
	rec = g_new0(CHAT_PROTOCOL_REC, 1);
	rec->name = PROTOCOL_NAME;
	rec->fullname = "Discord wrapper for irc";
	rec->chatnet = "testnet";
	rec->case_insensitive = FALSE;

	rec->create_chatnet = create_chatnet;
	rec->create_server_setup = create_server_setup;
	rec->create_server_connect = create_server_connect;
	//rec->create_channel_setup
	//rec->destroy_server_connect
	rec->server_init_connect = server_init_connect;
	rec->server_connect = (void (*)(SERVER_REC *))server_connect;
	//rec->channel_create
	//rec->query_create
	//
	//

	chat_protocol_register(rec);
	g_free(rec);

	module_register(MODULE_NAME, "core");
	print_load_message();
}

void test_deinit() {
    print_unload_message();
}

#ifdef IRSSI_ABI_VERSION
/*
 *  * irssi abicheck()
 *   */
void test_abicheck(int *version)
{
		*version = IRSSI_ABI_VERSION;
}
#endif
