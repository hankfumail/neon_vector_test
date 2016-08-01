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

	 
#ifndef __ARM_COMLEX_VECTOR_DOT_PRODUCT_DATA_H_
#define __ARM_COMLEX_VECTOR_DOT_PRODUCT_DATA_H_


#include <stdio.h>
#include <stdlib.h>

#include "platform.h"

#include <time.h>
#include "xparameters.h"




/**************************** Type Definitions *******************************/



/************************** Constant Definitions *****************************/
#define 	VECTOR_MAX_LENGTH	2048



/***************** Macros (Inline Functions) Definitions *********************/








/************************** Variable Definitions *****************************/

extern   float  gf_array_src_a[VECTOR_MAX_LENGTH*2];
extern   float  gf_array_src_b[VECTOR_MAX_LENGTH*2];
extern   float 	gf_sum[2];
extern   float 	gf_sum_dsp_concept[2];
extern   float 	gf_sum_dsp_concept2[2];
extern   float 	gf_sum_dsp_concept2a[2];
extern   float 	gf_sum_dsp_concept3[2];
extern   float 	gf_sum_dsp_concept3a[2];
extern   float 	gf_sum_dsp_concept3b[2];
extern   float 	gf_sum_dsp_concept3c[2];
extern   float 	gf_sum_dsp_concept4[2];
extern   float 	gf_sum_dsp_concept5[2];
extern   float 	gf_sum_dsp_concept5a[2];
extern   float 	gf_sum_dsp_concept5b[2];
extern   float 	gf_sum_dsp_concept5c[2];

extern   float 	gf_sum_asm_dot_4[4];
extern   float 	gf_sum_asm_dot_8[4];
extern   float 	gf_sum_asm_dot_8b[4];
extern   float 	gf_sum_asm_dot_16[4];
extern   float 	gf_sum_asm_dot_20[4];

extern   float 	gf_sum_asm_cmplx_dot_8[4];
extern   float 	gf_sum_asm_cmplx_dot_8b[4];
extern   float 	gf_sum_asm_cmplx_dot_16[4];
extern   float 	gf_sum_asm_cmplx_dot_16a[4];
extern   float 	gf_sum_asm_cmplx_dot_16b[4];
extern   float 	gf_sum_asm_cmplx_dot_16c[4];


/************************** Function Prototypes ******************************/

void  sp_cmplx_vector_init( void );



#endif /* __ARM_COMLEX_VECTOR_DOT_PRODUCT_DATA_H_  */

