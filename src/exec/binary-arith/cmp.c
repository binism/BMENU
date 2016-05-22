#include "exec/helper.h"

#define DATA_BYTE 1
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmp-template.h"
#undef DATA_BYTE


extern char suffix;


make_helper(CMP_i2ra_v) {
   return (suffix == 'l'?CMP_i2ra_l(eip):CMP_i2ra_w(eip));
}


make_helper(CMP_i2rm_v) {
   return (suffix == 'l'?CMP_i2rm_l(eip):CMP_i2rm_w(eip));
}

make_helper(CMP_ib2rm_v) {
   return (suffix == 'l'?CMP_ib2rm_l(eip):CMP_ib2rm_w(eip));
}

make_helper(CMP_r2rm_v) {
   return (suffix == 'l'?CMP_r2rm_l(eip):CMP_r2rm_w(eip));
}

make_helper(CMP_rm2r_v) {
   return (suffix == 'l'?CMP_rm2r_l(eip):CMP_rm2r_w(eip));
}
