
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

#include "servers-setup.h"

#include "protocol.h"
#include "servers.h"
#include "channels.h"
#include "queries.h"
#include "chatnets.h"

void test_init() {
	CHAT_PROTOCOL_REC *rec;
	rec = g_new0(CHAT_PROTOCOL_REC, 1);
	rec->name = PROTOCOL_NAME;
	rec->fullname = "Discord wrapper";
	rec->chatnet = "discord";

	rec->case_insensitive = FALSE;

	protocol_setup_servers(rec);
	protocol_init();
	protocol_init_servers(rec);
	protocol_init_chatnet(rec);
	protocol_init_channels(rec);
	rec->query_create = (QUERY_REC *(*) (const char *, const char *, int)) test_query_create;

	chat_protocol_register(rec);
	g_free(rec);

	print_load_message();
	module_register(MODULE_NAME, "core");
	//reload_config = 1;
	//signal_emit("reload", 0);
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
