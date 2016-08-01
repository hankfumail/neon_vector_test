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
 * arm_complex_vector_dot.c: simple test application
 */

#include <stdio.h>
#include <stdlib.h>

#include "platform.h"

#include <time.h>
#include "xparameters.h"
#include "xil_printf.h"

#include "arm_cmplx_vector_dot_prod_data.h"
#include "Arm_cmplx_math_test_data.h"

/**************************** Type Definitions *******************************/



/************************** Constant Definitions *****************************/
#define 	VECTOR_LENGTH		1024



/***************** Macros (Inline Functions) Definitions *********************/




/************************** Variable Definitions *****************************/



/************************** Function Prototypes ******************************/





/************************** Function Implementation ******************************/

#if 0

// System may be reseted if ".ocm_low.text" is used for sp_cmplx_vector_dot_mul
//void  __attribute__((section(".ocm_low.text"))) sp_cmplx_vector_dot_mul( unsigned int ui_vector_length );

#endif


/*

*/

void  sp_cmplx_vector_dot_mul( unsigned int ui_vector_length )
{
	int		j;
	float	*p_a;
	float	*p_b;
	float	a_real;
	float	a_img;
	float	b_real;
	float	b_img;
	float	sum_real=0;
	float	sum_img=0;

	ui_vector_length = ui_vector_length&0xfffffffe;
	//printf("ui_vector_length: %d\n\r", ui_vector_length);

	p_a = gf_array_src_a;
	p_b = gf_array_src_b;
    for( j=0; j<ui_vector_length; j++ )
    {
		//(a+bi)(c+di) = a*c-bd  +(ad+bc)i
		a_real = *p_a;
		p_a++;
		a_img = *p_a;
		p_a++;
		b_real = *p_b;
		p_b++;
		b_img = *p_b;
		p_b++;
    	sum_real += a_real*b_real-a_img*b_img;
    	sum_img += a_real*b_img+a_img*b_real;
    }

	gf_sum[0] = sum_real;
	gf_sum[1] = sum_img;

}







