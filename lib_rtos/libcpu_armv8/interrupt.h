/*
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define INT_IRQ     0x00
#define INT_FIQ     0x01

void rt_hw_interrupt_control(int vector, int priority, int route);

void rt_hw_interrupt_config(int vector,int config);

void rt_hw_interrupt_init(void);

#endif
