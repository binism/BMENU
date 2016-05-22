#include "exec/helper.h"

#define DATA_BYTE 1
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jmp-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;


make_helper(JMP_rel_v) {
  return (suffix=='l'? JMP_rel_l(eip) : JMP_rel_w(eip));
}


make_helper(JMP_rm_v) {
	return (suffix=='l'?JMP_rm_l(eip) : JMP_rm_w(eip));
}
