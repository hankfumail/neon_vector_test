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
	
		 
#ifndef __ARM_NEON_ASM_DOT_PROD_H__
#define __ARM_NEON_ASM_DOT_PROD_H__


#include "arm_math.h"
#include "arm_cmplx_vector_dot_prod_data.h"

void asm_dot_prod4( unsigned int ui_vector_length );
void asm_dot_prod8( unsigned int ui_vector_length );
void asm_dot_prod16( unsigned int ui_vector_length );
void asm_dot_prod20( unsigned int ui_vector_length );
void asm_dot_prod24( unsigned int ui_vector_length );

void asm_cmplx_dot_prod8( unsigned int ui_vector_length );
void asm_cmplx_dot_prod8b( unsigned int ui_vector_length );
void asm_cmplx_dot_prod16( unsigned int ui_vector_length );
void asm_cmplx_dot_prod16a( unsigned int ui_vector_length );
void asm_cmplx_dot_prod16b( unsigned int ui_vector_length );
void asm_cmplx_dot_prod16c( unsigned int ui_vector_length );


#endif /* __ARM_NEON_ASM_DOT_PROD_H__  */


/**     
 * @} end of CmplxByCmplxMult group     
 */
 
