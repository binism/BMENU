#include "eflags.h"
#include "cpu/modrm.h"
#include "exec/helper.h"
 void add_eflags_change(int a,int b,int MSB_1,int  MSB_2,int MSB_3) {
	cpu.EFLAGS.SF=MSB_3;
	int temp = a + b;
	int i=0,sum=0;
    for(; i<8; i++)
     { int tmp =  temp  & 0x1;
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
    if(MSB_1==MSB_2&&MSB_1!=MSB_3)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
}

void cmp_eflags_change(int a,int b,int MSB_1,int MSB_2,int MSB_3) {
      int temp = b - a;
	cpu.EFLAGS.SF=MSB_3;
	int i=0,sum=0;
    for(; i<8; i++)
     { int tmp = temp &  0x1;
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
    if(MSB_1!=MSB_2&&MSB_1==MSB_3)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
	if(b<a)
		cpu.EFLAGS.CF=1;
	else
		cpu.EFLAGS.CF=0;
} 
void adc_eflags_change(int a,int b,int MSB_1,int MSB_2,int MSB_3) {
    int temp = b + a + cpu.EFLAGS.CF;
	cpu.EFLAGS.SF=MSB_3;
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
	if ( b + a + cpu.EFLAGS.CF== 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    if(MSB_1==MSB_2&&MSB_2!=MSB_3)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
}


void dec_eflags_change(int a,int MSB_1,int MSB_2) {
     int temp = a - 1;
    cpu.EFLAGS.SF=MSB_2;
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
       if( a-1==0)
            cpu.EFLAGS.ZF=1;
       else
            cpu.EFLAGS.ZF=0;
     if(0!=MSB_1&&0==MSB_2>>31)
		cpu.EFLAGS.OF=1;
     else 
		cpu.EFLAGS.OF=0;
     if(a<1)
		cpu.EFLAGS.CF=1;
      else
		cpu.EFLAGS.CF=0;
}


void inc_eflags_change(int  a,int MSB_1,int MSB_2) {
     int temp = a + 1;
   cpu.EFLAGS.SF=MSB_2;
	int i=0,sum=0;
    for(; i<8; i++)
     { int tmp = temp & 0x1 ;
	   sum = sum + tmp;
	   temp=temp>>1;
     }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
       if( a+1==0)
            cpu.EFLAGS.ZF=1;
       else
            cpu.EFLAGS.ZF=0;
     if(0==MSB_1&&0!=MSB_2)
		cpu.EFLAGS.OF=1;
     else 
		cpu.EFLAGS.OF=0;
     if(a<1)
		cpu.EFLAGS.CF=1;
      else
		cpu.EFLAGS.CF=0;
}


void sbb_eflags_change(int  a,int b,int MSB_1,int MSB_2,int MSB_3) {
    int temp = b - a - cpu.EFLAGS.CF;
	cpu.EFLAGS.SF=MSB_3;
	int i=0,sum=0;
    for(; i<8; i++)
     { int tmp = temp &  0x1;
	   sum = sum + tmp;
	   temp=temp>>1;
	 }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
	if ( b - a - cpu.EFLAGS.CF== 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    if(MSB_1!=MSB_2&&MSB_1==MSB_3)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
        if(b<(a+cpu.EFLAGS.CF))
		cpu.EFLAGS.CF=1;
	else
		cpu.EFLAGS.CF=0;
}

