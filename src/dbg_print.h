/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

	 
#ifndef __DBG_PRINT_H_
#define __DBG_PRINT_H_


#include <stdio.h>
#include <stdlib.h>

#include "xil_types.h"
#include "xil_printf.h"



/**************************** Type Definitions *******************************/



/************************** Constant Definitions *****************************/



/***************** Macros (Inline Functions) Definitions *********************/


//#define	dbg_print_enable


/* debug print function */
#define print_var(xxx) 						xil_printf( "%s = %d\r\n", #xxx, xxx )
#define print_var_non_zero(xxx) 			{	if (0 != xxx ) xil_printf( "%s = %d\r\n", #xxx, xxx ); }
#define print_info_var(info, xxx) 			xil_printf( info" %s = %d\r\n", #xxx, xxx )
#define print_info_var_non_zero(info, xxx) 	{	if (0 != xxx ) xil_printf( info" %s = %d\r\n", #xxx, xxx ); }
#define print_var_hex(xxx) 					xil_printf( "%s = 0x%08x\r\n", #xxx, xxx )
#define print_var_hex_non_zero(xxx) 		{	if (0 != xxx ) xil_printf( "%s = 0x%08x\r\n", #xxx, xxx ); }
#define print_info_var_hex(info, xxx) 		xil_printf( info" %s = 0x%08x\r\n", #xxx, xxx )
#define print_info_var_hex_non_zero(info, xxx) 		{	if (0 != xxx ) xil_printf( info" %s = 0x%08x\r\n", #xxx, xxx ); }

#define print_var_location(xxx) 			xil_printf( "Address of variable:%s is 0x%08x\r\n", #xxx, &xxx )

#define print_pointer_hex_4(pointer) 		{	xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[0]), (pointer)[0], (pointer)[1], (pointer)[2], (pointer)[3] ); }

#define print_pointer_hex_8(pointer) 		{	xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[0]), (pointer)[0], (pointer)[1], (pointer)[2], (pointer)[3] ); \
												xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[4]), (pointer)[4], (pointer)[5], (pointer)[6], (pointer)[7] );}

#define print_pointer_hex_8a(pointer) 		{	xil_printf( "0x%08x:  %08x  %08x  %08x  %08x  %08x  %08x  %08x  %08x\r\n", \
						&((pointer)[0]), (pointer)[0], (pointer)[1], (pointer)[2], (pointer)[3], \
						(pointer)[4], (pointer)[5], (pointer)[6], (pointer)[7] ); }

#define print_pointer_hex_16(pointer) 		{	xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[0]), (pointer)[0], (pointer)[1], (pointer)[2], (pointer)[3] ); \
												xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[4]), (pointer)[4], (pointer)[5], (pointer)[6], (pointer)[7] ); \
											xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[8]), (pointer)[8], (pointer)[9], (pointer)[10], (pointer)[11] ); \
												xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[12]), (pointer)[12], (pointer)[13], (pointer)[14], (pointer)[15] );}


#define print_var_old(xxx) 					xil_printf( "Old %s = %d\r\n", #xxx, xxx )
#define print_var_old_hex(xxx) 				xil_printf( "Old %s = 0x%08x\r\n", #xxx, xxx )
#define print_var_old_hex_non_zero(xxx) 	{	if (0 != xxx ) xil_printf( "Old %s = 0x%08x\r\n", #xxx, xxx ); }
#define print_var_new(xxx) 					xil_printf( "New %s = %d\r\n", #xxx, xxx )
#define print_var_new_hex(xxx) 				xil_printf( "New %s = 0x%08x\r\n", #xxx, xxx )
#define print_var_new_hex_non_zero(xxx) 	{	if (0 != xxx ) xil_printf( "New %s = 0x%08x\r\n", #xxx, xxx ); }

#define dbg_print_func_begin 						xil_printf( "\r\n%s : begin.\r\n", __func__ )

#ifdef	dbg_print_enable

#define dbg_print(format,args...) 				xil_printf(format, ##args)

#define dbg_print_var(xxx) 						xil_printf( "%s : %s = %d\r\n", __func__, #xxx, xxx )
#define dbg_print_var_non_zero(xxx) 			{	if (0 != xxx ) xil_printf( "%s : %s = %d\r\n", __func__, #xxx, xxx ); }
#define dbg_print_var_hex(xxx) 					xil_printf( "%s : %s = 0x%08x\r\n", __func__, #xxx, xxx )
#define dbg_print_var_hex_non_zero(xxx) 		{	if (0 != xxx ) xil_printf( "%s : %s = 0x%08x\r\n", __func__, #xxx, xxx ); }

#define dbg_print_info_var(info, xxx) 			xil_printf( " %s :"info" : %s = %d\r\n", __func__, #xxx, xxx )
#define dbg_print_info_var_non_zero(info, xxx) 	{	if (0 != xxx ) xil_printf( info" %s : %s = %d\r\n", __func__, #xxx, xxx ); }
#define dbg_print_info_var_hex(info, xxx) 		xil_printf( " %s :"info"%s = 0x%08x\r\n", __func__, #xxx, xxx )
#define dbg_print_info_var_hex_non_zero(info, xxx) 		{	if (0 != xxx ) xil_printf( " %s :"info" %s = 0x%08x\r\n", __func__, #xxx, xxx ); }


#define dbg_print_pointer_hex_4(pointer) 		{	xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[0]), (pointer)[0], (pointer)[1], (pointer)[2], (pointer)[3] ); }

#define dbg_print_pointer_hex_8(pointer) 		{	xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[0]), (pointer)[0], (pointer)[1], (pointer)[2], (pointer)[3] ); \
												xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[4]), (pointer)[4], (pointer)[5], (pointer)[6], (pointer)[7] );}

#define dbg_print_pointer_hex_16(pointer) 		{	xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[0]), (pointer)[0], (pointer)[1], (pointer)[2], (pointer)[3] ); \
												xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[4]), (pointer)[4], (pointer)[5], (pointer)[6], (pointer)[7] ); \
											xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[8]), (pointer)[8], (pointer)[9], (pointer)[10], (pointer)[11] ); \
												xil_printf( "0x%08x:  %08x  %08x  %08x  %08x \r\n", \
						&((pointer)[12]), (pointer)[12], (pointer)[13], (pointer)[14], (pointer)[15] );}


#define dbg_print_var_old(xxx) 					xil_printf( "%s : Old %s = %d\r\n", __func__, #xxx, xxx )
#define dbg_print_var_old_hex(xxx) 				xil_printf( "%s : Old %s = 0x%08x\r\n", __func__, #xxx, xxx )
#define dbg_print_var_old_hex_non_zero(xxx) 	{	if (0 != xxx ) xil_printf( "%s : Old %s = 0x%08x\r\n", __func__, #xxx, xxx ); }

#define dbg_print_var_new(xxx) 					xil_printf( "%s : New %s = %d\r\n", __func__, #xxx, xxx )
#define dbg_print_var_new_hex(xxx) 				xil_printf( "%s : New %s = 0x%08x\r\n", __func__, #xxx, xxx )
#define dbg_print_var_new_hex_non_zero(xxx) 	{	if (0 != xxx ) xil_printf( "%s : New %s = 0x%08x\r\n", __func__, #xxx, xxx ); }

#else     	/* dbg_print_enable  */

#define dbg_print(format,args...)

#define dbg_print_var(xxx)
#define dbg_print_var_non_zero(xxx)
#define dbg_print_var_hex(xxx)
#define dbg_print_var_hex_non_zero(xxx)

#define dbg_print_info_var(info, xxx)
#define dbg_print_info_var_non_zero(info, xxx)
#define dbg_print_info_var_hex(info, xxx)
#define dbg_print_info_var_hex_non_zero(info, xxx)


#define dbg_print_pointer_hex_4(pointer) 		
#define dbg_print_pointer_hex_8(pointer) 	
#define dbg_print_pointer_hex_16(pointer) 		


#define dbg_print_var_old(xxx)
#define dbg_print_var_old_hex(xxx)
#define dbg_print_var_old_hex_non_zero(xxx)

#define dbg_print_var_new(xxx)
#define dbg_print_var_new_hex(xxx)
#define dbg_print_var_new_hex_non_zero(xxx)

#endif		/* dbg_print_enable  */


/************************** Variable Definitions *****************************/



/************************** Function Prototypes ******************************/




#endif /* __DBG_PRINT_H_  */

