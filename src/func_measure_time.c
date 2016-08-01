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

#include <stdio.h>
#include <stdlib.h>
#include <sleep.h>

#include "platform.h"

#include "xparameters.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "dbg_print.h"


#include "func_measure_time.h"


/**************************** Type Definitions *******************************/



/************************** Constant Definitions *****************************/



/***************** Macros (Inline Functions) Definitions *********************/




/************************** Variable Definitions *****************************/




/************************** Function Prototypes ******************************/




void global_timer_test( void )
{
	u32 u32Loop;
	XTime tBegin, tCur;
	XTime tLastCycles;
	u64 tLastUS;
	u64 tPrevUS;
	u64 tLastSecond;

	xil_printf("Global Timer standalone driver test.\n\r" );
	xil_printf("CPU frequency: %dHz=%dMHz.\n\r", 
				XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ, XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ/1000000 );
	xil_printf("Global Timer frequency: %dHz=%dMHz.\n\r", 
				COUNTS_PER_SECOND, COUNTS_PER_SECOND/1000000 );

	XTime_GetTime(&tBegin);
	tPrevUS = 0;
	for ( u32Loop=0; u32Loop<1000000000; u32Loop++ )
	{
		//for ( u32InnerLoop=0; u32InnerLoop<DDR_TEST_WORD; u32InnerLoop++ )
		{
		}
		XTime_GetTime(&tCur);
		tLastCycles = ( tCur - tBegin );
		tLastUS = ( tLastCycles*1000000 ) / COUNTS_PER_SECOND;
		tLastSecond = tLastUS/1000000;
		if( tLastUS>(tPrevUS+1000000) )
		{
			printf("It lasts %llu cycles, %llu us, %llu second\n\r", tLastCycles, tLastUS, tLastSecond );
			tPrevUS = tLastUS;
		}
	}

	xil_printf("\n\r");

}



void func1_time_measure
( 
	test_func1_pointer_strct  func_ptr, 
	unsigned int ui_test_num 
)
{
	u32 u32Loop;
	XTime tBegin, tEnd;
	XTime tLastCycles;
	u64 tLastUS;
	u64 tLastSecond;

	XTime_GetTime(&tBegin);
	for ( u32Loop=0; u32Loop<ui_test_num; u32Loop++ )
	{
		func_ptr( );
	}
	XTime_GetTime(&tEnd);
	tLastCycles = ( tEnd - tBegin );
	tLastUS = ( tLastCycles*1000000 )/COUNTS_PER_SECOND;
	tLastSecond = tLastUS/1000000;
	printf("It lasts %llu cycles, %llu us = %llu second\n\r", tLastCycles, tLastUS, tLastSecond );
	//xil_printf("\n\r");

}



void func2_time_measure
( 
	test_func2_pointer_strct  func_ptr, 
	unsigned int ui_test_param, 
	unsigned int ui_test_num 
)
{
	u32 u32Loop;
	XTime tBegin, tEnd;
	XTime tLastCycles;
	u64 tLastUS;
	u64 tLastSecond;

	printf( "Test number:%d, test parameter:%d=0x%08x\r\n", 
		ui_test_num, ui_test_param, ui_test_param );
	usleep(10000);

	XTime_GetTime(&tBegin);
	for ( u32Loop=0; u32Loop<ui_test_num; u32Loop++ )
	{
		func_ptr(ui_test_param);
	}
	XTime_GetTime(&tEnd);
	tLastCycles = ( tEnd - tBegin );
	tLastUS = ( tLastCycles*1000000 )/COUNTS_PER_SECOND;
	tLastSecond = tLastUS/1000000;
	printf("It lasts %llu cycles, %llu us, %llu second\n\r", tLastCycles, tLastUS, tLastSecond );
	//xil_printf("\n\r");

}
