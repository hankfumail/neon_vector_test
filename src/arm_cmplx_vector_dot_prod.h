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

	 
#ifndef __ARM_COMPLEX_VECTOR_DOT_H_
#define __ARM_COMPLEX_VECTOR_DOT_H_


#include <stdio.h>
#include <stdlib.h>

#include "platform.h"

#include <time.h>
#include "xparameters.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "dbg_print.h"

#include "arm_math.h"



/**************************** Type Definitions *******************************/



/************************** Constant Definitions *****************************/



/***************** Macros (Inline Functions) Definitions *********************/



/************************** Variable Definitions *****************************/



/************************** Function Prototypes ******************************/



void  sp_cmplx_vector_dot_mul( unsigned int ui_vector_length );



#endif /* __ARM_COMPLEX_VECTOR_DOT_H_  */

