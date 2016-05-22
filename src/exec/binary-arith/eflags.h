#ifndef __EFLAGS_H__
#define __EFLAGS_H__

#include "cpu/modrm.h"
#include "exec/helper.h"
void add_eflags_change(int a,int b,int MSN_1,int MSB_2,int MSB_3); /*{
     int temp = a + b;
	cpu.EFLAGS.SF=temp>>length;
	int i=0,sum=0;
    for(; i<8; i++)
     { int tmp =  temp & 0x1;
	   sum = sum + tmp;
	   temp=temp>>1;
      }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
	if ( a + b == 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    int temp1 = a + b;
    if(a>>length==b>>length&&a>>length!=temp1>>length)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
        long long temp2 = temp1;
        if(((temp2>>(length+1)&0x1)==1))
		cpu.EFLAGS.CF=1;
	else
		cpu.EFLAGS.CF=0;
}*/



void cmp_eflags_change(int a,int b,int MSB_1,int MSB_2,int MSB_3); /*{
      int temp = b - a;
	cpu.EFLAGS.SF=temp>>length;
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
	if ( b - a == 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    int temp1 = b - a;
    if(a>>length!=b>>length&&a>>length==temp1>>length)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
	if(b<a)
		cpu.EFLAGS.CF=1;
	else
		cpu.EFLAGS.CF=0;
}*/
void adc_eflags_change(int a,int b,int MSB_1,int MSB_2,int MSB_3);
void dec_eflags_change(int a,int MSB_1,int MSB_2);
void inc_eflags_change(int a,int MSB_1,int MSB_2);
void sbb_eflags_change(int a,int b,int MSB_1,int MSB_2,int MSB_3);

#endif
