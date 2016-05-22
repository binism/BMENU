#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"


make_helper(concat(PUSH_r_,SUFFIX)) {
  cpu.esp=cpu.esp-DATA_BYTE;
  int reg_code = instr_fetch(eip,1) & 0x7;
  swaddr_t addr;
  addr = cpu.esp;
  MEM_W(addr,REG(reg_code));
  print_asm("push" str(SUFFIX) " %%%s",REG_NAME(reg_code));
  return 1;
}




#include "exec/template-end.h"
