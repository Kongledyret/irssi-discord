#include "signals.h"

#include <irssi/src/core/signals.h>

#include "chatnets.h"
#include "servers-setup.h"
#include "queries.h"

void signals_init(void) {
	chatnets_signals_init();
	servers_setup_signals_init();
	queries_signals_init();
}

