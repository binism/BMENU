#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_r2rm_b, add_r2rm_v, add_rm2r_b, add_rm2r_v, 
/* 0x04 */	add_i2ra_b, add_i2ra_v, inv, inv, 
/* 0x08 */	or_r2rm_b, or_r2rm_v, or_rm2r_b, or_rm2r_v, 
/* 0x0c */	or_i2rm_b, or_i2rm_v, inv, dbopcode, 
/* 0x10 */	adc_r2rm_b, adc_r2rm_v, adc_rm2r_b, adc_rm2r_v, 
/* 0x14 */	adc_i2rm_b, adc_i2rm_v, inv, inv, 
/* 0x18 */	sbb_r2rm_b, sbb_r2rm_v, sbb_rm2r_b, sbb_rm2r_v, 
/* 0x1c */	sbb_i2ra_b, sbb_i2ra_v, inv, inv, 
/* 0x20 */	and_r2rm_b, and_r2rm_v, and_rm2r_b, and_rm2r_v, 
/* 0x24 */	and_i2ra_b, and_i2ra_v, inv, inv,
/* 0x28 */	sub_r2rm_b, sub_r2rm_v, sub_rm2r_b, sub_rm2r_v, 
/* 0x2c */	sub_i2ra_b, sub_i2ra_v, inv, inv, 
/* 0x30 */	xor_r2rm_b, xor_r2rm_v, xor_rm2r_b, xor_rm2r_v, 
/* 0x34 */	xor_i2ra_b, xor_i2ra_v, inv, inv,
/* 0x38 */	CMP_r2rm_b, CMP_r2rm_v, CMP_rm2r_b, CMP_rm2r_v, 
/* 0x3c */ CMP_i2ra_b, CMP_i2ra_v, inv, inv, 
/* 0x40 */	inc_r_v, inv, inv, inv, 
/* 0x44 */	inv, inv, inv, inv,
/* 0x48 */	dec_r_v, inv, inv, inv, 
/* 0x4c */	inv, inv, inv, inv, 
/* 0x50 */	PUSH_r_v, PUSH_r_v, PUSH_r_v, PUSH_r_v,//push r32/16 
/* 0x54 */	PUSH_r_v, PUSH_r_v, PUSH_r_v, PUSH_r_v,
/* 0x58 */	pop_r_v, pop_r_v, pop_r_v, pop_r_v, 
/* 0x5c */	pop_r_v, pop_r_v, pop_r_v, pop_r_v, 
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	inv, imul_i2rm2r_v, inv, imul_ib2rm2r_v, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	JCC_O_b, JCC_NO_b, JCC_B_b, JCC_AorE_b,
/* 0x74 */	JCC_EorZ_b, JCC_NE_b, JCC_BorE_b, JCC_A_b,
/* 0x78 */	JCC_S_b, JCC_NS_b, JCC_P_b, JCC_NP_b, 
/* 0x7c */	JCC_L_b, JCC_GorE_b, JCC_LorE_b, JCC_G_b, 
/* 0x80 */	opdefine80, opdefine81, nemu_trap, opdefine83, 
/* 0x84 */	test_r2rm_b, test_r2rm_v, xchg_r2rm_b, xchg_r2rm_v, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, lea_m2r_v, inv, opdefine8f, 
/* 0x90 */	xchg_r2ra_v, xchg_r2ra_v, xchg_r2ra_v, xchg_r2ra_v,
/* 0x94 */	xchg_r2ra_v, xchg_r2ra_v, xchg_r2ra_v, xchg_r2ra_v,
/* 0x98 */	inv, cwd_v, inv, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	movs_b, movs_v, inv, inv,
/* 0xa8 */	test_i2ra_b, test_i2ra_v, inv, inv,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	opdefinec0, opdefinec1, ret_iw_l, ret_ss_v,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave_r_v, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	opdefined0, opdefined1, opdefined2, opdefined3,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, JCC_CXZ_b,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	CALL_rel_v, JMP_rel_v, inv, JMP_rel_b,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, opdefinef6, opdefinef7,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	cld, std, opdefinefe, opdefineff
};

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
