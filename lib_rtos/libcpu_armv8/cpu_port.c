/*
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 */

#include <rthw.h>
#include <rtthread.h>

/**
 * @addtogroup ARM CPU
 */
/*@{*/

/** shutdown CPU */
void rt_hw_cpu_shutdown()
{
	rt_base_t level;
	rt_kprintf("shutdown...\n");

	level = rt_hw_interrupt_disable();
	while (1)
	{
		RT_ASSERT(0);
	}
}

/*@}*/
