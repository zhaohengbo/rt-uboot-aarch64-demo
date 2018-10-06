/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */
#include <rtthread.h>
#include <rthw.h>

#include "armv8.h"

#include "gic.h"

extern struct rt_thread *rt_current_thread;
#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */
void rt_hw_show_register(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("Execption:\n");
    rt_kprintf("r00:0x%16.16llx r01:0x%16.16llx r02:0x%16.16llx r03:0x%16.16llx\n", regs->r0, regs->r1, regs->r2, regs->r3);
    rt_kprintf("r04:0x%16.16llx r05:0x%16.16llx r06:0x%16.16llx r07:0x%16.16llx\n", regs->r4, regs->r5, regs->r6, regs->r7);
	rt_kprintf("r08:0x%16.16llx r09:0x%16.16llx r10:0x%16.16llx r11:0x%16.16llx\n", regs->r8, regs->r9, regs->r10, regs->r11);
	rt_kprintf("r12:0x%16.16llx r13:0x%16.16llx r14:0x%16.16llx r15:0x%16.16llx\n", regs->r12, regs->r13, regs->r14, regs->r15);
	rt_kprintf("r16:0x%16.16llx r17:0x%16.16llx r18:0x%16.16llx r19:0x%16.16llx\n", regs->r16, regs->r17, regs->r18, regs->r19);
	rt_kprintf("r20:0x%16.16llx r21:0x%16.16llx r22:0x%16.16llx r23:0x%16.16llx\n", regs->r20, regs->r21, regs->r22, regs->r23);
    rt_kprintf("r24:0x%16.16llx r25:0x%16.16llx r26:0x%16.16llx r27:0x%16.16llx\n", regs->r24, regs->r25, regs->r26, regs->r27);
	rt_kprintf("r28:0x%16.16llx r29:0x%16.16llx r30:0x%16.16llx", regs->r28, regs->r29, regs->r30);
	rt_kprintf("spsr:0x%16.16llx", regs->spsr);
	rt_kprintf("return pc:0x%16.16llx", regs->pc);
}

/**
 * When comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_error(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("error exception:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

#define GIC_ACK_INTID_MASK              0x000003ff

void rt_hw_trap_irq(void)
{
    void *param;
    unsigned long ir;
    unsigned long fullir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    fullir = arm_gic_get_active_irq(0);
    ir = fullir & GIC_ACK_INTID_MASK;

    if (ir == 1023)
    {
        /* Spurious interrupt */
        return;
    }

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
#ifdef RT_USING_INTERRUPT_INFO
    isr_table[ir].counter++;
#endif
    if (isr_func)
    {
        /* Interrupt for myself. */
        param = isr_table[ir].param;
        /* turn to interrupt service routine */
        isr_func(ir, param);
    }

    /* end of interrupt */
    arm_gic_ack(0, fullir);
}

void rt_hw_trap_fiq(void)
{
    void *param;
    unsigned long ir;
    unsigned long fullir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    fullir = arm_gic_get_active_irq(0);
    ir = fullir & GIC_ACK_INTID_MASK;

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
    param = isr_table[ir].param;

    /* turn to interrupt service routine */
    isr_func(ir, param);

    /* end of interrupt */
    arm_gic_ack(0, fullir);
}

