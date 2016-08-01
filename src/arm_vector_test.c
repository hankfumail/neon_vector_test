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

#include "platform.h"

#include <time.h>
#include "xparameters.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "dbg_print.h"
#include "func_measure_time.h"
#include "Sys_reg_report.h"

#include "arm_math.h"

#include "arm_cmplx_vector_dot_prod_data.h"
#include "arm_cmplx_vector_dot_prod.h"
#include "arm_cmplx_mult_cmplx_f32_dot.h"
#include "arm_cmplx_mult_cmplx_f32_dot2.h"
#include "arm_cmplx_mult_cmplx_f32_dot2a.h"
#include "arm_cmplx_mult_cmplx_f32_dot3.h"
#include "arm_cmplx_mult_cmplx_f32_dot3a.h"
#include "arm_cmplx_mult_cmplx_f32_dot3b.h"
#include "arm_cmplx_mult_cmplx_f32_dot3c.h"
#include "arm_cmplx_mult_cmplx_f32_dot4.h"
#include "arm_cmplx_mult_cmplx_f32_dot5.h"
#include "arm_cmplx_mult_cmplx_f32_dot5a.h"
#include "arm_cmplx_mult_cmplx_f32_dot5b.h"
#include "arm_cmplx_mult_cmplx_f32_dot5c.h"


#include "neon_asm_dot_prod.h"



/**************************** Type Definitions *******************************/



/************************** Constant Definitions *****************************/



/***************** Macros (Inline Functions) Definitions *********************/









/************************** Variable Definitions *****************************/



/************************** Function Prototypes ******************************/


/*
 * Samsung: CPU 1GHz, DDR3 667MHz: vector dot product, 498 *498 1700 cycle --> 1000 cycles
 *
 */

// It is not stable when CPU works at 1GHz, DDR3 works at 667MHz for ZC706 SN 1303-0832
// L1 & L2 cache are enabled by default.

/*
CPU frequency: 1000000000Hz=1000MHz.
Global Timer frequency: 500000000Hz=500MHz.
Address of variable:gf_array_src_a is 0x0011FEE8
Address of variable:gf_array_src_a[0] is 0x0011FEE8
Address of variable:gf_array_src_b is 0x00123EE8
Address of variable:gf_array_src_b[0] is 0x00123EE8

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 3261266 cycles, 6522 us, 0 second
 */

/*

CPU frequency: 1000000000Hz=1000MHz.
Global Timer frequency: 500000000Hz=500MHz.
Address of variable:gf_array_src_a is 0x0011FEE8
Address of variable:gf_array_src_a[0] is 0x0011FEE8
Address of variable:gf_array_src_b is 0x00123EE8
Address of variable:gf_array_src_b[0] is 0x00123EE8

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 3261263 cycles, 6522 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833463 cycles, 13666 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

*/

/*
CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x0011FEE8
Address of variable:gf_array_src_a[0] is 0x0011FEE8
Address of variable:gf_array_src_b is 0x00123EE8
Address of variable:gf_array_src_b[0] is 0x00123EE8

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 3261304 cycles, 9783 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833515 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

*/


/*
CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_a[0] is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_array_src_b[0] is 0x00005000

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 3261257 cycles, 9783 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833448 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

*/


/*
Data is stored in OCM. Function is stored in DDR3.

CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_a[0] is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_array_src_b[0] is 0x00005000

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 3261304 cycles, 9783 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833445 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000


*/

/*
CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_a[0] is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_array_src_b[0] is 0x00005000

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 3261251 cycles, 9783 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833436 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

*/

/*

CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_sum_dsp_concept is 0x00009000
Address of variable:gf_sum_dsp_concept2 is 0x00009008

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x00101D00
Test number:1000, test parameter:498=0x000001f2
It lasts 3261732 cycles, 9785 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833368 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot2 at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 6842713 cycles, 20528 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

*/

/*

CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_a[0] is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_array_src_b[0] is 0x00005000
Address of variable:gf_sum_dsp_concept is 0x00009000
Address of variable:gf_sum_dsp_concept2 is 0x00009008
Address of variable:gf_sum_dsp_concept3 is 0x00009010
Address of variable:gf_sum_dsp_concept4 is 0x00009018

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x00102018
Test number:1000, test parameter:498=0x000001f2
It lasts 3261683 cycles, 9785 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833380 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot2 at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 6842678 cycles, 20528 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Float complex vecter dot production test is completed.

CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_a[0] is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_array_src_b[0] is 0x00005000
Address of variable:gf_sum_dsp_concept is 0x00009000
Address of variable:gf_sum_dsp_concept2 is 0x00009008
Address of variable:gf_sum_dsp_concept3 is 0x00009010
Address of variable:gf_sum_dsp_concept4 is 0x00009018

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x00102018
Test number:1000, test parameter:498=0x000001f2
It lasts 3261765 cycles, 9785 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833370 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot2 at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 6842710 cycles, 20528 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot3 at 0x00101D00
Test number:1000, test parameter:498=0x000001f2
It lasts 2094098 cycles, 6282 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot4 at 0x00101E74
Test number:1000, test parameter:498=0x000001f2
It lasts 3260813 cycles, 9782 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:0.000000, imaginary part:0.000000

Float complex vecter dot production test is completed.

CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_a[0] is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_array_src_b[0] is 0x00005000
Address of variable:gf_sum_dsp_concept is 0x00009000
Address of variable:gf_sum_dsp_concept2 is 0x00009008
Address of variable:gf_sum_dsp_concept3 is 0x00009010
Address of variable:gf_sum_dsp_concept4 is 0x00009018

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x00102018
Test number:1000, test parameter:498=0x000001f2
It lasts 3261696 cycles, 9785 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833343 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot2 at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 6842687 cycles, 20528 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot3 at 0x00101D00
Test number:1000, test parameter:498=0x000001f2
It lasts 2094107 cycles, 6282 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:0.000000, imaginary part:0.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot4 at 0x00101E74
Test number:1000, test parameter:498=0x000001f2
It lasts 3260732 cycles, 9782 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:0.000000, imaginary part:0.000000

Float complex vecter dot production test is completed.

CPU frequency: 666666687Hz=666MHz.
Global Timer frequency: 333333343Hz=333MHz.
Address of variable:gf_array_src_a is 0x00001000
Address of variable:gf_array_src_a[0] is 0x00001000
Address of variable:gf_array_src_b is 0x00005000
Address of variable:gf_array_src_b[0] is 0x00005000
Address of variable:gf_sum_dsp_concept is 0x00009000
Address of variable:gf_sum_dsp_concept2 is 0x00009008
Address of variable:gf_sum_dsp_concept3 is 0x00009010
Address of variable:gf_sum_dsp_concept4 is 0x00009018

Begin to measure time for function:sp_cmplx_vector_dot_mul at 0x00102018
Test number:1000, test parameter:498=0x000001f2
It lasts 3261723 cycles, 9785 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept at 0x001017AC
Test number:1000, test parameter:498=0x000001f2
It lasts 6833439 cycles, 20500 us, 0 second
sp_cmplx_vector_dot_mul result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot2 at 0x001017CC
Test number:1000, test parameter:498=0x000001f2
It lasts 6842727 cycles, 20528 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229066229547008.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot3 at 0x00101D00
Test number:1000, test parameter:498=0x000001f2
It lasts 2094125 cycles, 6282 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Begin to measure time for function:arm_cmplx_mult_cmplx_f32_dot4 at 0x00101E74
Test number:1000, test parameter:498=0x000001f2
It lasts 3260794 cycles, 9782 us, 0 second
arm_cmplx_mult_cmplx_f32_dot2 result: real part:26648846142537728.000000, imaginary part:1172229203668500480.000000

Float complex vecter dot production test is completed.



*/

/*
-mcpu=cortex-a9 -Wall -O3  -g -c -mfloat-abi=softfp -mfpu=neon -ftree-vectorize -ffast-math -mvectorize-with-neon-quad
-mcpu=cortex-a9 -Wall -O3  -c -mfloat-abi=softfp -mfpu=neon -ftree-vectorize -ffast-math -mvectorize-with-neon-quad
*/

/*
	NEON optimization flag: softwre pending
	remove NEON optimization flag: softwre completed.
	NEON optimization flag: softwre completed

*/
int main()
{

    init_platform();
	
	xil_printf("CPU frequency: %dHz=%dMHz.\n\r", 
				XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ, XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ/1000000 );
	xil_printf("Global Timer frequency: %dHz=%dMHz.\n\r", 
				COUNTS_PER_SECOND, COUNTS_PER_SECOND/1000000 );

	/*
	L1 Instruction Cache enabled.
	L1 Data Cache enabled.
	*/
	system_control_register_report( );

	sp_cmplx_vector_init( );

	/*
		Begin to measure time for function:sp_cmplx_vector_dot_mul
		Test number:10000, test parameter:1024=0x00000400
		It lasts 66750908 cycles, 133501 us, 0 second

		Begin to measure time for function:sp_cmplx_vector_dot_mul_dsp_concept
		Test number:10000, test parameter:1024=0x00000400
		It lasts 139601313 cycles, 279202 us, 0 second
	*/
	print_measure_func( sp_cmplx_vector_dot_mul );
	func2_time_measure( sp_cmplx_vector_dot_mul, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum[0], gf_sum[1] );

	print_measure_func( sp_cmplx_vector_dot_mul_dsp_concept );
	func2_time_measure( sp_cmplx_vector_dot_mul_dsp_concept, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept[0], gf_sum_dsp_concept[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot2 );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot2, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept2[0], gf_sum_dsp_concept2[1] );

	print_measure_func( arm_cmplx_mult_cmplx_f32_dot2a );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot2a, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept2a[0], gf_sum_dsp_concept2a[1] );

	print_measure_func( arm_cmplx_mult_cmplx_f32_dot3 );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot3, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept3[0], gf_sum_dsp_concept3[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot3a );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot3a, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept3a[0], gf_sum_dsp_concept3a[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot3b );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot3b, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept3b[0], gf_sum_dsp_concept3b[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot3c );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot3c, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept3c[0], gf_sum_dsp_concept3c[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot4 );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot4, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept4[0], gf_sum_dsp_concept4[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot5 );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot5, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept5[0], gf_sum_dsp_concept5[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot5a );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot5a, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept5a[0], gf_sum_dsp_concept5a[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot5b );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot5b, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept5b[0], gf_sum_dsp_concept5b[1] );
	
	print_measure_func( arm_cmplx_mult_cmplx_f32_dot5c );
	func2_time_measure( arm_cmplx_mult_cmplx_f32_dot5c, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_dsp_concept5c[0], gf_sum_dsp_concept5c[1] );
	
	print_measure_func( asm_cmplx_dot_prod8 );
	func2_time_measure( asm_cmplx_dot_prod8, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_asm_cmplx_dot_8[0], gf_sum_asm_cmplx_dot_8[1] );
	
	print_measure_func( asm_cmplx_dot_prod8b );
	func2_time_measure( asm_cmplx_dot_prod8b, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_asm_cmplx_dot_8b[0], gf_sum_asm_cmplx_dot_8b[1] );
	
	print_measure_func( asm_cmplx_dot_prod16 );
	func2_time_measure( asm_cmplx_dot_prod16, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_asm_cmplx_dot_16[0], gf_sum_asm_cmplx_dot_16[1] );
	
	print_measure_func( asm_cmplx_dot_prod16a );
	func2_time_measure( asm_cmplx_dot_prod16a, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_asm_cmplx_dot_16a[0], gf_sum_asm_cmplx_dot_16a[1] );
	
	print_measure_func( asm_cmplx_dot_prod16b );
	func2_time_measure( asm_cmplx_dot_prod16b, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_asm_cmplx_dot_16b[0], gf_sum_asm_cmplx_dot_16b[1] );
	
	print_measure_func( asm_cmplx_dot_prod16c );
	func2_time_measure( asm_cmplx_dot_prod16c, 512, 1000);
	printf("Result: real part:%f, imaginary part:%f\n\r\n\r", 
				gf_sum_asm_cmplx_dot_16c[0], gf_sum_asm_cmplx_dot_16c[1] );
#if 1
#endif


	 print_measure_func( asm_dot_prod4 );
	 func2_time_measure( asm_dot_prod4, 128, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_4[0], gf_sum_asm_dot_4[1] );

	 print_measure_func( asm_dot_prod8 );
	 func2_time_measure( asm_dot_prod8, 128, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_8[0], gf_sum_asm_dot_8[1] );

	 print_measure_func( asm_dot_prod16 );
	 func2_time_measure( asm_dot_prod16, 128, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_16[0], gf_sum_asm_dot_16[1] );

	 print_measure_func( asm_dot_prod20 );
	 func2_time_measure( asm_dot_prod20, 128, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_20[0], gf_sum_asm_dot_20[1] );

	 print_measure_func( asm_dot_prod4 );
	 func2_time_measure( asm_dot_prod4, 2048, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_4[0], gf_sum_asm_dot_4[1] );

	 print_measure_func( asm_dot_prod8 );
	 func2_time_measure( asm_dot_prod8, 2048, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_8[0], gf_sum_asm_dot_8[1] );

	 print_measure_func( asm_dot_prod16 );
	 func2_time_measure( asm_dot_prod16, 2048, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_16[0], gf_sum_asm_dot_16[1] );

	 print_measure_func( asm_dot_prod20 );
	 func2_time_measure( asm_dot_prod20, 2048, 1000);
	 printf("Result: result 1:%f, result 2:%f\n\r\n\r", 
				 gf_sum_asm_dot_20[0], gf_sum_asm_dot_20[1] );


	 printf("Float complex vecter dot production test is completed.\n\r\n\r");

   	 cleanup_platform();

    return 0;
}
