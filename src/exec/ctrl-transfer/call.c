#include "exec/helper.h"

#define DATA_BYTE 1
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "call-template.h"
#undef DATA_BYTE


extern char suffix;

make_helper(CALL_rel_v) {
   return (suffix == 'l' ? CALL_rel_l(eip):CALL_rel_w(eip));
}
