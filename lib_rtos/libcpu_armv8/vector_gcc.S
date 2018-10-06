/*
 * File      : vector_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-05     Bernard      the first version
 */
.text

.globl system_vectors
.globl vector_error
.globl vector_irq
.globl vector_fiq

system_vectors:
.align 11
    .set    VBAR, system_vectors
    .org    VBAR
    .org (VBAR + 0x00 + 0)
    B vector_error      // 			Synchronous
    .org (VBAR + 0x80 + 0)
    B vector_irq        //          IRQ/vIRQ
    .org (VBAR + 0x100 + 0)
    B vector_fiq        //          FIQ/vFIQ
    .org (VBAR + 0x180 + 0)
    B vector_error      //          Error/vError
    .org (VBAR + 0x200 + 0)
    B vector_error      // 			Synchronous
    .org (VBAR + 0x280 + 0)
    B vector_error  	// 			IRQ/vIRQ
    .org (VBAR + 0x300 + 0)
    B vector_error      //          FIQ/vFIQ
    .org (VBAR + 0x380 + 0)
    B vector_error
	.org (VBAR + 0x400 + 0)
    B vector_error
    .org (VBAR + 0x480 + 0)
    B vector_error
    .org (VBAR + 0x500 + 0)
    B vector_error
    .org (VBAR + 0x580 + 0)
    B vector_error
	.org (VBAR + 0x600 + 0)
    B vector_error
    .org (VBAR + 0x680 + 0)
    B vector_error
    .org (VBAR + 0x700 + 0)
    B vector_error
    .org (VBAR + 0x780 + 0)
    B vector_error
    .org (VBAR + 0x800 + 0)
    B vector_error
	