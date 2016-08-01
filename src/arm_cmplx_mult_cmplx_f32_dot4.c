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
#include "arm_math.h"
#include "arm_cmplx_vector_dot_prod_data.h"

/**     
 * @ingroup groupCmplxMath     
 */

#if 0

// System may be reseted if ".ocm_low.text" is used for sp_cmplx_vector_dot_mul
void __attribute__((section(".ocm_low.text"))) arm_cmplx_mult_cmplx_f32_dot(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t numSamples);

void  __attribute__((section(".ocm_low.text"))) sp_cmplx_vector_dot_mul_dsp_concept( unsigned int ui_vector_length );

#endif


/**     
 * @defgroup CmplxByCmplxMult Complex-by-Complex Multiplication     
 *     
 * Multiplies a complex vector by another complex vector and generates a complex result.     
 * The data in the complex arrays is stored in an interleaved fashion     
 * (real, imag, real, imag, ...).     
 * The parameter <code>numSamples</code> represents the number of complex     
 * samples processed.  The complex arrays have a total of <code>2*numSamples</code>     
 * real values.     
 *     
 * The underlying algorithm is used:     
 *     
 * <pre>     
 * for(n=0; n<numSamples; n++) {     
 *     pDst[(2*n)+0] = pSrcA[(2*n)+0] * pSrcB[(2*n)+0] - pSrcA[(2*n)+1] * pSrcB[(2*n)+1];     
 *     pDst[(2*n)+1] = pSrcA[(2*n)+0] * pSrcB[(2*n)+1] + pSrcA[(2*n)+1] * pSrcB[(2*n)+0];     
 * }     
 * </pre>     
 *     
 * This function uses the 4 way SIMD and loop unrolled by 4. Select the blocksize as multiple of 16 for better performance how ever this function can   
 * support any block size.   
 * There are separate functions for floating-point and Q31 data types.     
 */



/**     
 * @addtogroup CmplxByCmplxMult     
 * @{     
 */


/**     
 * @brief  Floating-point complex-by-complex multiplication     
 * @param[in]  *pSrcA points to the first input vector     
 * @param[in]  *pSrcB points to the second input vector     
 * @param[out]  *pDst  points to the output vector     
 * @param[in]  numSamples number of complex samples in each vector     
 * @return none.     
 */
// __INLINE
void arm_cmplx_mult_cmplx_f32_dot4(
  unsigned int numSamples )
{
  float32_t a, b, c, d;                          /* Temporary variables to store real and imaginary values */
  float 	 sum_real, sum_img;            		/*  */
  uint32_t blkCnt;                               /* loop counters */
  
  float32_t * pSrcA;
  float32_t * pSrcB;
  float32_t * pDst;
  
  pSrcA = gf_array_src_a;
  pSrcB = gf_array_src_b;
  pDst = gf_sum_dsp_concept4;



  blkCnt = numSamples;

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.     
   ** No intrinsics is used. */
  sum_real =0;
  sum_img =0;
  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in the destination buffer. */
    sum_real += ((a * c) - (b * d));
    sum_img += ((a * d) + (b * c));

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }

	*pDst++=sum_real;
	*pDst++=sum_img;

}





/**     
 * @} end of CmplxByCmplxMult group     
 */
 
