/* ----------------------------------------------------------------------     
* Copyright (C) 2011 DSP Concepts LLC . All rights reserved. 
*     
* $Date:        07. October 2011  
* $Revision: 	V1.0.0  
*     
* Project: 	    Cortex-A DSP Library 
* Title:	    arm_cmplx_mult_cmplx_f32.c     
*     
* Description:	Floating-point complex-by-complex multiplication     
*     
* Target Processor:          Cortex-A
* Target Tools Revision:     RVDS Version 4.0
*  
* Version 1.0.0 2011/10/07 
* Initial version.  
*   
* -------------------------------------------------------------------- */
	
		 
#ifndef __ARM_CMPLX_MULT_CMPLX_F32_DOT_H_
#define __ARM_CMPLX_MULT_CMPLX_F32_DOT_H_


#include "arm_math.h"
#include "arm_cmplx_vector_dot_prod_data.h"
#include "arm_cmplx_math_test_data.h"

void arm_cmplx_mult_cmplx_f32_dot(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t numSamples);



void  sp_cmplx_vector_dot_mul_dsp_concept( unsigned int ui_vector_length );



#endif /* __ARM_CMPLX_MULT_CMPLX_F32_DOT_H_  */


/**     
 * @} end of CmplxByCmplxMult group     
 */
 
