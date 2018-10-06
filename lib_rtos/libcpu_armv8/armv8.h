#ifndef __ARMV8_H__
#define __ARMV8_H__

/* the exception stack without VFP registers */
struct rt_hw_exp_stack
{
	unsigned long long pc;
	unsigned long long spsr;
	unsigned long long r30;
	unsigned long long rz;
	unsigned long long r28;
	unsigned long long r29;
	unsigned long long r26;
	unsigned long long r27;
	unsigned long long r24;
	unsigned long long r25;
	unsigned long long r22;
	unsigned long long r23;
	unsigned long long r20;
	unsigned long long r21;
	unsigned long long r18;	
	unsigned long long r19;
	unsigned long long r16;
	unsigned long long r17;
	unsigned long long r14;
	unsigned long long r15;
	unsigned long long r12;
	unsigned long long r13;
	unsigned long long r10;
	unsigned long long r11;
	unsigned long long r8;
	unsigned long long r9;
	unsigned long long r6;
	unsigned long long r7;
	unsigned long long r4;
	unsigned long long r5;
	unsigned long long r2;
	unsigned long long r3;
	unsigned long long r0;
	unsigned long long r1;
};

#define SP_ELx						( ( unsigned long long ) 0x01 )
#define SP_EL0						( ( unsigned long long ) 0x00 )
#define PSTATE_EL1					( ( unsigned long long ) 0x04 )
#define PSTATE_EL2					( ( unsigned long long ) 0x08 )
#define PSTATE_EL3					( ( unsigned long long ) 0x0c )

#define __REG64(x)  (*((volatile unsigned long long *)(x)))
#define __REG32(x)  (*((volatile unsigned int *)(x)))
#define __REG16(x)  (*((volatile unsigned short *)(x)))

#endif
