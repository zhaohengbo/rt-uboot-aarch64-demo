#ifndef __CPU_PORT_H__
#define __CPU_PORT_H__

void rt_hw_set_elx_env(void);
void rt_hw_set_current_vbar(rt_uint64_t addr);
rt_uint64_t rt_hw_get_current_el(void);

#endif
