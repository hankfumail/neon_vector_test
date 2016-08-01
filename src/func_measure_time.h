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

/*
 * helloworld.c: simple test application
 */

	 
#ifndef __FUNC_MEASURE_TIME_H_
#define __FUNC_MEASURE_TIME_H_


#include <stdio.h>
#include <stdlib.h>

#include "platform.h"

#include "xparameters.h"
#include "xtime_l.h"




/**************************** Type Definitions *******************************/

typedef void (*test_func1_pointer_strct)( void );
typedef void (*test_func2_pointer_strct)( unsigned int );


/************************** Constant Definitions *****************************/



/***************** Macros (Inline Functions) Definitions *********************/


#define print_measure_func(xxx) 	{xil_printf( "Begin to measure time for function:%s at 0x%08x\r\n", #xxx, xxx );}






/************************** Variable Definitions *****************************/




/************************** Function Prototypes ******************************/


void global_timer_test( void );

void func1_time_measure( test_func1_pointer_strct  func_ptr, 
					unsigned int ui_test_num );

void func2_time_measure( test_func2_pointer_strct  func_ptr, 
					unsigned int ui_test_param, unsigned int ui_test_num );


#endif /* __FUNC_MEASURE_TIME_H_  */

