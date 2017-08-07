#include "test_impl.h"

#include <irssi.h>

#include "discord.c"


void print_load_message(void) {
	//authorize();
	printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
						"Hello, World. xxx \"%s\"", MODULE_NAME);

}

void print_unload_message(void) {

    printtext(NULL, NULL, MSGLEVEL_CLIENTERROR,
              "Goodbye, Cruel World. ~signed \"%s\"", MODULE_NAME);

}

