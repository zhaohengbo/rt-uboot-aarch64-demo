/*
 *  linux/drivers/clocksource/arm_arch_timer.c
 *
 *  Copyright (C) 2011 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <common.h>

#include <rthw.h>
#include <rtthread.h>

#include <asm/io.h>

#include "cpu_port.h"

#include "gic.h"
#include "armv8.h"
#include "interrupt.h"

#define CPU_CP_GET(val, reg) __asm__ __volatile__ ("mrs %0, " #reg : "=r" (val) : : "memory")
#define CPU_CP_SET(val, reg) __asm__ __volatile__ ("msr " #reg ",%0"  : : "r" (val) : "memory")

#define CPU_CLK_TMR_FREQ 100000000UL

#define CNT_EL0 30
#define CNT_EL1 29
#define CNT_EL2 26

#define SOC_IRQ_TIMER_LEVEL IRQ_TYPE_LEVEL

static rt_uint64_t TmrStepSize;

void soc_timer_isr_handler(void)
{
	rt_uint64_t current_el;
	
	current_el = rt_hw_get_current_el();
	
	if(current_el == 3)
	{
		CPU_CP_SET(TmrStepSize, CNTPS_TVAL_EL1);
	}
	else if(current_el == 2)
	{
		CPU_CP_SET(TmrStepSize, CNTHP_TVAL_EL2);
	}
	else
	{
		CPU_CP_SET(TmrStepSize, CNTP_TVAL_EL0);
	}
}

void soc_timer_init(void)
{
	rt_uint64_t current_el;
	
	TmrStepSize = CPU_CLK_TMR_FREQ / RT_TICK_PER_SECOND;
	
	current_el = rt_hw_get_current_el();
	
	if(current_el == 3)
	{
		CPU_CP_SET(TmrStepSize, CNTPS_TVAL_EL1);
    	CPU_CP_SET(0x1, CNTPS_CTL_EL1);
	}
	else if(current_el == 2)
	{
		CPU_CP_SET(TmrStepSize, CNTHP_TVAL_EL2);
		CPU_CP_SET(0x1, CNTHP_CTL_EL2);
	}
	else
	{
		CPU_CP_SET(TmrStepSize, CNTP_TVAL_EL0);
    	CPU_CP_SET(0x1, CNTP_CTL_EL0);
	}
}

extern void rt_hw_timer_isr(int vector, void *param);

void soc_timer_isr_install(void)
{
	rt_uint64_t current_el;
	
	current_el = rt_hw_get_current_el();
	
	if(current_el == 3)
	{
		rt_hw_interrupt_install(CNT_EL1, rt_hw_timer_isr, RT_NULL, "tick");
		rt_hw_interrupt_mask(CNT_EL1);
		rt_hw_interrupt_config(CNT_EL1,SOC_IRQ_TIMER_LEVEL);
    	rt_hw_interrupt_umask(CNT_EL1);
	}
	else if(current_el == 2)
	{
		rt_hw_interrupt_install(CNT_EL2, rt_hw_timer_isr, RT_NULL, "tick");
		rt_hw_interrupt_mask(CNT_EL2);
		rt_hw_interrupt_config(CNT_EL2,SOC_IRQ_TIMER_LEVEL);
    	rt_hw_interrupt_umask(CNT_EL2);
	}
	else
	{
		rt_hw_interrupt_install(CNT_EL0, rt_hw_timer_isr, RT_NULL, "tick");
		rt_hw_interrupt_mask(CNT_EL0);
		rt_hw_interrupt_config(CNT_EL0,SOC_IRQ_TIMER_LEVEL);
		rt_hw_interrupt_umask(CNT_EL0);
	}
}