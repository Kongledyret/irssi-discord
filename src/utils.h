#include <irssi/src/common.h>
#include <irssi/src/core/levels.h>
#include <irssi/src/fe-common/core/printtext.h>
#define printf(...) printtext(NULL, NULL, MSGLEVEL_CLIENTERROR, __VA_ARGS__)
#define debug() printf("======%s:%d %s======", __FILE__, __LINE__, __func__)
