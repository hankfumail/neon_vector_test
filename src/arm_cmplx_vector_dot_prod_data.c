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
#include "dbg_print.h"
#include "mmu_table.h"

#include "arm_cmplx_vector_dot_prod_data.h"


/**************************** Type Definitions *******************************/



/************************** Constant Definitions *****************************/



/***************** Macros (Inline Functions) Definitions *********************/




/************************** Variable Definitions *****************************/

#if 0

float   __attribute__((section(".ocm_low.data"))) gf_array_src_a[VECTOR_MAX_LENGTH*2];
float   __attribute__((section(".ocm_low.data"))) gf_array_src_b[VECTOR_MAX_LENGTH*2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept2[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept2a[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept3[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept3a[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept3b[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept3c[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept4[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept5[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept5a[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept5b[2];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_dsp_concept5c[2];


float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_dot_4[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_dot_8[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_dot_8b[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_dot_16[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_dot_20[4];


float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_cmplx_dot_8[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_cmplx_dot_8b[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_cmplx_dot_16[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_cmplx_dot_16a[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_cmplx_dot_16b[4];
float 	__attribute__((section(".ocm_low.data"))) gf_sum_asm_cmplx_dot_16c[4];

#else

float   gf_array_src_a[VECTOR_MAX_LENGTH*2];
float   gf_array_src_b[VECTOR_MAX_LENGTH*2];
float 	gf_sum[2];
float 	gf_sum_dsp_concept[2];
float 	gf_sum_dsp_concept2[2];
float 	gf_sum_dsp_concept2a[2];
float 	gf_sum_dsp_concept3[2];
float 	gf_sum_dsp_concept3a[2];
float 	gf_sum_dsp_concept3b[2];
float 	gf_sum_dsp_concept3c[2];
float 	gf_sum_dsp_concept4[2];
float 	gf_sum_dsp_concept5[2];
float 	gf_sum_dsp_concept5a[2];
float 	gf_sum_dsp_concept5b[2];
float 	gf_sum_dsp_concept5c[2];


float 	gf_sum_asm_dot_4[4];
float 	gf_sum_asm_dot_8[4];
float 	gf_sum_asm_dot_8b[4];
float 	gf_sum_asm_dot_16[4];
float 	gf_sum_asm_dot_20[4];


float 	gf_sum_asm_cmplx_dot_8[4];
float 	gf_sum_asm_cmplx_dot_8b[4];
float 	gf_sum_asm_cmplx_dot_16[4];
float 	gf_sum_asm_cmplx_dot_16a[4];
float 	gf_sum_asm_cmplx_dot_16b[4];
float 	gf_sum_asm_cmplx_dot_16c[4];

#endif



/************************** Function Prototypes ******************************/











/************************** Function Implementation ******************************/



void  sp_cmplx_vector_init( void )
{
	int		i;
	unsigned int *pui_data;

	print_var_location( gf_array_src_a );
	print_var_location( gf_array_src_a[0] );
	print_var_location( gf_array_src_b );
	print_var_location( gf_array_src_b[0] );
	print_var_location( gf_sum_dsp_concept );
	print_var_location( gf_sum_dsp_concept2 );
	print_var_location( gf_sum_dsp_concept3 );
	print_var_location( gf_sum_dsp_concept3a );
	print_var_location( gf_sum_dsp_concept3b );
	print_var_location( gf_sum_dsp_concept3c );
	print_var_location( gf_sum_dsp_concept4 );
	print_var_location( gf_sum_dsp_concept5a );
	print_var_location( gf_sum_dsp_concept5b );
	print_var_location( gf_sum_dsp_concept5c );
	
	print_var_location( gf_sum_asm_dot_4 );
	print_var_location( gf_sum_asm_dot_8 );
	print_var_location( gf_sum_asm_dot_8b );
	print_var_location( gf_sum_asm_dot_16 );
	print_var_location( gf_sum_asm_dot_20 );
	
	print_var_location( gf_sum_asm_cmplx_dot_8 );
	print_var_location( gf_sum_asm_cmplx_dot_8b );
	print_var_location( gf_sum_asm_cmplx_dot_16 );
	print_var_location( gf_sum_asm_cmplx_dot_16a );
	print_var_location( gf_sum_asm_cmplx_dot_16b );
	print_var_location( gf_sum_asm_cmplx_dot_16c );
	xil_printf( "\r\n" );


	/*
		Outer cache attribute: Write-Back, Write-Allocate. 
		Inner cache attribute: Write-Back, Write-Allocate. 
	*/
	//ReportMmuTblAttributes( gf_array_src_a );

	gf_sum[0] = 0 ;
	gf_sum[1] = 0 ;
	gf_sum_dsp_concept[0] = 0 ;
	gf_sum_dsp_concept[1] = 0 ;
	gf_sum_dsp_concept2[0] = 0 ;
	gf_sum_dsp_concept2[1] = 0 ;
	gf_sum_dsp_concept3[0] = 0 ;
	gf_sum_dsp_concept3[1] = 0 ;
	gf_sum_dsp_concept3a[0] = 0 ;
	gf_sum_dsp_concept3a[1] = 0 ;
	gf_sum_dsp_concept3b[0] = 0 ;
	gf_sum_dsp_concept3b[1] = 0 ;
	gf_sum_dsp_concept3c[0] = 0 ;
	gf_sum_dsp_concept3c[1] = 0 ;
	gf_sum_dsp_concept4[0] = 0 ;
	gf_sum_dsp_concept4[1] = 0 ;
	gf_sum_dsp_concept5[0] = 0 ;
	gf_sum_dsp_concept5[1] = 0 ;
	gf_sum_dsp_concept5a[0] = 0 ;
	gf_sum_dsp_concept5a[1] = 0 ;
	gf_sum_dsp_concept5b[0] = 0 ;
	gf_sum_dsp_concept5b[1] = 0 ;
	gf_sum_dsp_concept5c[0] = 0 ;
	gf_sum_dsp_concept5c[1] = 0 ;
	

	gf_sum_asm_dot_4[0] = 0 ;
	gf_sum_asm_dot_4[1] = 0 ;
	gf_sum_asm_dot_4[2] = 0 ;
	gf_sum_asm_dot_4[3] = 0 ;

	gf_sum_asm_dot_8[0] = 0 ;
	gf_sum_asm_dot_8[1] = 0 ;
	gf_sum_asm_dot_8[2] = 0 ;
	gf_sum_asm_dot_8[3] = 0 ;

	gf_sum_asm_dot_16[0] = 0 ;
	gf_sum_asm_dot_16[1] = 0 ;
	gf_sum_asm_dot_16[2] = 0 ;
	gf_sum_asm_dot_16[3] = 0 ;

	gf_sum_asm_dot_20[0] = 0 ;
	gf_sum_asm_dot_20[1] = 0 ;
	gf_sum_asm_dot_20[2] = 0 ;
	gf_sum_asm_dot_20[3] = 0 ;

	gf_sum_asm_cmplx_dot_8[0] = 0 ;
	gf_sum_asm_cmplx_dot_8[1] = 0 ;
	gf_sum_asm_cmplx_dot_8[2] = 0 ;
	gf_sum_asm_cmplx_dot_8[3] = 0 ;

	gf_sum_asm_cmplx_dot_8b[0] = 0 ;
	gf_sum_asm_cmplx_dot_8b[1] = 0 ;
	gf_sum_asm_cmplx_dot_8b[2] = 0 ;
	gf_sum_asm_cmplx_dot_8b[3] = 0 ;

	gf_sum_asm_cmplx_dot_16[0] = 0 ;
	gf_sum_asm_cmplx_dot_16[1] = 0 ;
	gf_sum_asm_cmplx_dot_16[2] = 0 ;
	gf_sum_asm_cmplx_dot_16[3] = 0 ;

	gf_sum_asm_cmplx_dot_16a[0] = 0 ;
	gf_sum_asm_cmplx_dot_16a[1] = 0 ;
	gf_sum_asm_cmplx_dot_16a[2] = 0 ;
	gf_sum_asm_cmplx_dot_16a[3] = 0 ;

	gf_sum_asm_cmplx_dot_16b[0] = 0 ;
	gf_sum_asm_cmplx_dot_16b[1] = 0 ;
	gf_sum_asm_cmplx_dot_16b[2] = 0 ;
	gf_sum_asm_cmplx_dot_16b[3] = 0 ;

	gf_sum_asm_cmplx_dot_16c[0] = 0 ;
	gf_sum_asm_cmplx_dot_16c[1] = 0 ;
	gf_sum_asm_cmplx_dot_16c[2] = 0 ;
	gf_sum_asm_cmplx_dot_16c[3] = 0 ;

	

	for( i=0; i<(VECTOR_MAX_LENGTH*2); i++ )
	{
		gf_array_src_a[i] =  rand()/100;
		gf_array_src_b[i] =  rand()/10;
	}

#if 1
	printf( "gf_array_src_a data:\n\r" );
	for( i=0; i<16; i++ )
	{
		if( 0 == (i%4) )
		{
			printf( "\n\r" );
		}
		if( i<16 )
		{
			printf( "0x%08x  ", (unsigned int)gf_array_src_a[i] );
		}
	}

	printf( "\n\r\n\rgf_array_src_b data:" );
	for( i=0; i<16; i++ )
	{
		if( 0 == (i%4) )
		{
			printf( "\n\r" );
		}
		if( i<16 )
		{
			printf( "0x%08x  ", (unsigned int)gf_array_src_b[i] );
		}
	}
	printf( "\n\r\n\r" );
#endif

 }







