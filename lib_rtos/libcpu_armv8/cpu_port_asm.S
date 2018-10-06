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
.globl rt_hw_get_current_el
rt_hw_get_current_el:
	MRS		X0, CurrentEL
	CMP		X0, 0xc
	B.EQ	3f
	CMP		X0, 0x8
	B.EQ	2f
	CMP		X0, 0x4
	B.EQ	1f
	
	LDR		X0, =0
	B		0f
3:
	LDR		X0, =3
	B		0f
2:
	LDR		X0, =2
	B		0f
1:
	LDR		X0, =1
	B		0f
0:
	RET
.globl rt_hw_set_current_vbar
rt_hw_set_current_vbar:
	MRS		X1, CurrentEL
	CMP		X1, 0xc
	B.EQ	3f
	CMP		X1, 0x8
	B.EQ	2f
	CMP		X1, 0x4
	B.EQ	1f
	B		0f
3:
	MSR		VBAR_EL3,X0
	B		0f
2:
	MSR		VBAR_EL2,X0
	B		0f
1:
	MSR		VBAR_EL1,X0
	B		0f
0:
	RET
.globl rt_hw_set_elx_env
rt_hw_set_elx_env:
	MRS		X1, CurrentEL
	CMP		X1, 0xc
	B.EQ	3f
	CMP		X1, 0x8
	B.EQ	2f
	CMP		X1, 0x4
	B.EQ	1f
	B		0f
3:
	MRS		X0, SCR_EL3
	ORR		X0, X0, #0xF			/* SCR_EL3.NS|IRQ|FIQ|EA */
	MSR		SCR_EL3, X0
	B		0f
2:
	MRS	X0, HCR_EL2
	ORR	X0, X0, #0x38
	MSR	HCR_EL2, X0
	B		0f
1:
	B		0f
0:
	RET