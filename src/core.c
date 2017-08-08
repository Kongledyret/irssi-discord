
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

#include "core.h"
#include "irssi.h"

#include "impl.h"


#include "servers.h"
#include "channels.h"
#include "queries.h"


#include <chatnets.h>
static CHATNET_REC *create_chatnet(void) {
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
	          "create_chatnet");
	return g_malloc0(sizeof(CHATNET_REC));
}


void test_init() {
	CHAT_PROTOCOL_REC *rec;
	rec = g_new0(CHAT_PROTOCOL_REC, 1);
	rec->name = PROTOCOL_NAME;
	rec->fullname = "Discord wrapper";
	rec->chatnet = "test";

	rec->case_insensitive = FALSE;

	rec->create_chatnet = create_chatnet;

	protocol_init_servers(rec);
	protocol_init_channels(rec);
	rec->query_create = (QUERY_REC *(*) (const char *, const char *, int)) test_query_create;

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
