/*
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 */

#include <common.h>
#include <rtthread.h>
#include "armv8.h"

DECLARE_GLOBAL_DATA_PTR;

extern rt_uint64_t rt_hw_get_current_el(void);

#define INITIAL_SPSR_EL3 (PSTATE_EL3 | SP_EL0)
#define INITIAL_SPSR_EL2 (PSTATE_EL2 | SP_EL0)
#define INITIAL_SPSR_EL1 (PSTATE_EL1 | SP_EL0)

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry 
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
	rt_uint8_t *stack_addr, void *texit)
{
	rt_uint64_t *stk;
	rt_uint64_t current_el;
	
	stk 	 = (rt_uint64_t*)stack_addr;
	
	*(--stk) = ( rt_uint64_t ) gd;			/* R1 */
	*(--stk) = ( rt_uint64_t ) parameter; 	/* R0 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R3 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R2 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R5 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R4 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R7 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R6 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R9 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R8 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R11 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R10 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R13 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R12 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R15 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R14 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R17 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R16 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R19 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R18 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R21 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R20 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R23 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R22 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R25 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R24 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R27 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R26 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R29 */
	*(--stk) = ( rt_uint64_t ) gd;			/* R28 */
	*(--stk) = ( rt_uint64_t ) 0;			/* XZR - has no effect, used so there are an even number of registers. */
	*(--stk) = ( rt_uint64_t ) texit;		/* R30 - procedure call link register. */
	
	current_el = rt_hw_get_current_el();
	
	if(current_el == 3)
	{
		*(--stk) = INITIAL_SPSR_EL3;
	}
	else if(current_el == 2)
	{
		*(--stk) = INITIAL_SPSR_EL2;
	}
	else
	{
		*(--stk) = INITIAL_SPSR_EL1;
	}

	*(--stk) = ( rt_uint64_t ) tentry; 		/* Exception return address. */

	/* return task's current stack address */
	return (rt_uint8_t *)stk;
}

/*@}*/
