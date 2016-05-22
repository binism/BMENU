#include "exec/helper.h"
#include "all-instr.h"
#define DATA_BYTE 1
#include "opdefine-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "opdefine-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "opdefine-template.h"
#undef DATA_BYTE
typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun second_opcode_table [256] = {
/* 0x00 */	inv, inv, inv, inv, 
/* 0x04 */	inv, inv, inv, inv, 
/* 0x08 */	inv, inv, inv, inv, 
/* 0x0c */	inv, inv, inv, inv, 
/* 0x10 */	inv, inv, inv, inv, 
/* 0x14 */	inv, inv, inv, inv, 
/* 0x18 */	inv, inv, inv, inv, 
/* 0x1c */	inv, inv, inv, inv, 
/* 0x20 */	inv, inv, inv, inv, 
/* 0x24 */	inv, inv, inv, inv,
/* 0x28 */	inv, inv, inv, inv, 
/* 0x2c */	inv, inv, inv, inv, 
/* 0x30 */	inv, inv, inv, inv, 
/* 0x34 */	inv, inv, inv, inv,
/* 0x38 */	inv, inv, inv, inv, 
/* 0x3c */	inv, inv, inv, inv, 
/* 0x40 */	inv, inv, inv, inv, 
/* 0x44 */	inv, inv, inv, inv,
/* 0x48 */	inv, inv, inv, inv, 
/* 0x4c */	inv, inv, inv, inv, 
/* 0x50 */	inv, inv, inv, inv, 
/* 0x54 */	inv, inv, inv, inv,
/* 0x58 */	inv, inv, inv, inv, 
/* 0x5c */	inv, inv, inv, inv, 
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	inv, inv, inv, inv, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	inv, inv, inv, inv,
/* 0x74 */	inv, inv, inv, inv,
/* 0x78 */	inv, inv, inv, inv, 
/* 0x7c */	inv, inv, inv, inv, 
/* 0x80 */	JCC_O_v, JCC_NO_v, JCC_B_v, JCC_AorE_v, 
/* 0x84 */	JCC_EorZ_v, JCC_NE_v, JCC_BorE_v, JCC_A_v, 
/* 0x88 */	JCC_S_v, JCC_NS_v, JCC_P_v, JCC_NP_v,
/* 0x8c */	JCC_L_v, JCC_GorE_v, JCC_LorE_v, JCC_G_v, 
/* 0x90 */	set_o_b, set_no_b, set_b_b, set_ae_b,
/* 0x94 */	set_e_b, set_ne_b, set_na_b, set_a_b,
/* 0x98 */	set_s_b, set_ns_b, set_pe_b, set_po_b, 
/* 0x9c */	set_l_b, set_ge_b, set_le_b, set_g_b, 
/* 0xa0 */	inv, inv, inv, inv,
/* 0xa4 */	inv, inv, inv, inv,
/* 0xa8 */	inv, inv, inv, inv,
/* 0xac */	inv, inv, inv, imul_rm2r_v,
/* 0xb0 */	inv, inv, inv, inv,
/* 0xb4 */	inv, inv, movzx_rmb2r_v, movzx_rmw2r_l,
/* 0xb8 */	inv, inv, inv, inv, 
/* 0xbc */	inv, inv, movsx_rmb2r_v, movsx_rmw2r_l, 
/* 0xc0 */	inv, inv, inv, inv,
/* 0xc4 */	inv, inv, inv, inv,
/* 0xc8 */	inv, inv, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	inv, inv, inv, inv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	inv, inv, inv, inv,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, inv, inv,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	inv, inv, inv, inv
 };

extern char suffix;
make_helper(opdefine80) {
  ModR_M m;
  m.val=instr_fetch(eip+1,1);
  switch (m.opcode)
  { case 0: return add_i2rm_b(eip); break;
	case 1: return or_i2rm_b(eip); break;
    case 2: return adc_i2rm_b(eip); break;
    case 3: return sbb_i2rm_b(eip); break;
	case 4: return and_i2rm_b(eip); break;
    case 5: return sub_i2rm_b(eip); break;
	case 6: return xor_i2rm_b(eip); break;
    case 7: return CMP_i2rm_b(eip); break;
    default : return 2; 
  } 
  /*if(m.opcode==5)
    return sub_i2rm_b;
  el se return 2;*/
}
make_helper(opdefine81) { 
   ModR_M m;
   m.val=instr_fetch(eip+1,1);
   switch (m.opcode)
   { case 0: return add_i2rm_v(eip); break;
	 case 1: return or_i2rm_v(eip); break;
     case 2: return adc_i2rm_v(eip); break;
     case 3: return sbb_i2rm_v(eip); break;
	 case 4: return and_i2rm_v(eip); break;
     case 5: return sub_i2rm_v(eip); break;
	 case 6: return xor_i2rm_v(eip); break;
     case 7: return CMP_i2rm_v(eip); break;
     default : return 2;
   } 
}
make_helper(opdefine83) { 
   ModR_M m;
   m.val=instr_fetch(eip+1,1);
   switch (m.opcode)
   { case 0: return add_ib2rm_v(eip); break;
	 case 1: return or_ib2rm_v(eip); break;
     case 2: return adc_ib2rm_v(eip); break;
     case 3: return sbb_ib2rm_v(eip); break;
	 case 4: return and_ib2rm_v(eip); break;
     case 5: return sub_ib2rm_v(eip); break;
	 case 6: return xor_ib2rm_v(eip); break;
     case 7: return CMP_ib2rm_v(eip); break;
     default : return 2;
     } 
   /*if(m.opcode==5)
      return sub_i2rm_v(eip);
   else if(m.opcode==7)
     return CMP_i2rm_v(eip);
    else return 2;*/ 
}   
make_helper(opdefine8f) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	switch (m.opcode)
	{ case 0: return pop_m_v(eip); break;
	  default : return 2; break;
	}
}


make_helper(opdefinec0) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
    switch(m.opcode)
	{  
      case 4: return sal_ib2rm_b(eip);
	  case 5: return shr_ib2rm_b(eip);
	  case 7: return sar_ib2rm_b(eip);
	  default : return 2;
	}
}

make_helper(opdefinec1) { 
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch(m.opcode)
	{   
      case 4: return sal_ib2rm_v(eip);
	  case 5: return shr_ib2rm_v(eip);
	  case 7: return sar_ib2rm_v(eip);
	  default : return 2;
	}
}

make_helper(opdefined0) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch(m.opcode)
	{ case 4: return sal_12rm_b(eip); 
      case 5: return shr_12rm_b(eip);
	  case 7: return sar_12rm_b(eip);
	  default : return 2;
 	}
} 


make_helper(opdefined1) { 
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch(m.opcode)
	{   
	  case 4: return sal_12rm_v(eip);
	  case 5: return shr_12rm_v(eip);
	  case 7: return sar_12rm_v(eip);

	  default : return 2;
	}
}


make_helper(opdefined2) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch(m.opcode)
	{ case 4: return sal_rc2rm_b(eip); 
	  case 5: return shr_rc2rm_b(eip);
	  case 7: return sar_rc2rm_b(eip);
	  default : return 2;
 	}
} 

make_helper(opdefined3) { 
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch(m.opcode)
	{ case 4: return sal_rc2rm_v(eip);
	  case 5: return shr_rc2rm_v(eip);	
      case 7: return sar_rc2rm_v(eip);
	  default : return 2;
	} 
}

make_helper(opdefinef6) {
   ModR_M m;
   m.val=instr_fetch(eip+1,1);
   switch(m.opcode)
   { case 0: return test_i2rm_b(eip); break;
     case 2: return not_rm_b(eip); break;
	 case 3: return neg_rm_b(eip); break;
     case 4: return mul_rm2ra_b(eip); break;
	 case 5: return imul_rm2ra_b(eip); break;
	 case 6: return div_rm2ra_b(eip); break;
     case 7: return idiv_rm2ra_b(eip); break;
     default : return 2;
   }
}

make_helper(opdefinef7) { 
   ModR_M m;
   m.val=instr_fetch(eip+1,1);
   switch(m.opcode)
   { case 0: return test_i2rm_v(eip); break;
	 case 2: return not_rm_v(eip); break;
	 case 3: return neg_rm_v(eip); break;
     case 4: return mul_rm2ra_v(eip); break;
	 case 5: return imul_rm2ra_v(eip); break;
	 case 6: return div_rm2ra_v(eip); break;
	 case 7: return idiv_rm2ra_v(eip); break;
     default : return 2;
    }
} 

make_helper(opdefinefe) {
   ModR_M m;
   m.val=instr_fetch(eip+1,1);
   switch(m.opcode)
   { case 0: return inc_rm_b(eip); break;
	 case 1: return dec_rm_b(eip); break;
	 default : return 2;
   }
}
make_helper(opdefineff) {
   ModR_M m;
   m.val=instr_fetch(eip+1,1);
   switch(m.opcode)
   { case 0: return inc_rm_v(eip); break;
     case 1: return dec_rm_v(eip); break;
     case 4: return JMP_rm_v(eip); break;   
     default : return 2;
   }
}

make_helper(dbopcode) {
   return second_opcode_table[ instr_fetch(eip + 1, 1) ](eip);
}
