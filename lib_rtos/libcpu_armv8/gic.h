/*
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 */

#ifndef __GIC_H__
#define __GIC_H__

#define IRQ_TYPE_LEVEL 0
#define IRQ_TYPE_EDGE 1

int arm_gic_dist_init(rt_uint32_t index, rt_uint64_t dist_base, int irq_start);
int arm_gic_cpu_init(rt_uint32_t index, rt_uint64_t cpu_base);

void arm_gic_mask(rt_uint32_t index, int irq);
void arm_gic_umask(rt_uint32_t index, int irq);
void arm_gic_set_cpu(rt_uint32_t index, int irq, unsigned int cpumask);
void arm_gic_set_group(rt_uint32_t index, int vector, int group);

void arm_gic_config(rt_uint32_t index, int irq, int config);
int arm_gic_get_active_irq(rt_uint32_t index);
void arm_gic_ack(rt_uint32_t index, int irq);

void arm_gic_dump_type(rt_uint32_t index);

#endif

