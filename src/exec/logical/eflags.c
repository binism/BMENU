#include "eflags.h"
#include "cpu/modrm.h"
#include "exec/helper.h"

void and_eflags_change(int a,int b,int MSB) {
      int temp = a & b;
	cpu.EFLAGS.SF = MSB;
	int i=0,sum=0;
      for(; i<8; i++)
      { int tmp = temp & 0x1;
	   sum = sum + tmp;
	   temp=temp>>1;
	 }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
	if ( (a & b) == 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    cpu.EFLAGS.CF=0;
    cpu.EFLAGS.OF=0;
}



void or_eflags_change(int a,int b,int MSB) {
      int temp = a | b;
	cpu.EFLAGS.SF = MSB;
	int i=0,sum=0;
      for(; i<8; i++)
      { int tmp = temp & 0x1;
	   sum = sum + tmp;
	   temp=temp>>1;
	 }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
	if ( (a | b) == 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    cpu.EFLAGS.CF=0;
    cpu.EFLAGS.OF=0;
}



void xor_eflags_change(int a,int b,int MSB) {
      int temp = a ^ b;
	cpu.EFLAGS.SF = MSB;
	int i=0,sum=0;
      for(; i<8; i++)
      { int tmp = temp & 0x1;
	   sum = sum + tmp;
	   temp=temp>>1;
	 }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
	if ( (a ^ b) == 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    cpu.EFLAGS.CF=0;
    cpu.EFLAGS.OF=0;
}
