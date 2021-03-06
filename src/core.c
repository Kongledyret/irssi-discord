#include "core.h"
#include <irssi/src/common.h>
#include <irssi/src/core/modules.h>

#include "utils.h"

#include "protocol.h"
#include "signals.h"

void NAMESPACE(init)() {
	debug();
	protocol_init();
	signals_init();
	module_register(MODULE_NAME, "core");
}
void NAMESPACE(deinit)() {
	debug();
}
#ifdef IRSSI_ABI_VERSION
void NAMESPACE(abicheck)(int *version)
{
	*version = IRSSI_ABI_VERSION;
}
#endif
