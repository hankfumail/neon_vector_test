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

/**     
 * @ingroup groupCmplxMath     
 */

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

void arm_cmplx_mult_cmplx_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t numSamples)
{
  float32_t a, b, c, d;                          /* Temporary variables to store real and imaginary values */
  float32x4_t A1, A2;                            /* Temporary variables to store real and imaginary values of source buffer A */
  float32x4_t B1, B2;                            /* Temporary variables to store real and imaginary values of source buffer B */
  float32x4_t C1, C2, C3, C4;                    /* Temporary variables to store multiplication output */
  float32x4x2_t out1, out2, out3, out4;          /* Temporary variables to stroe output result */
  uint32_t blkCnt;                               /* loop counters */

  /* Loop over blockSize number of values */
  blkCnt = numSamples >> 4u;

  while(blkCnt > 0u)
  {
    /* read 2 complex values at a time from source A buffer 
	float32x4_t vld1q_f32(__transfersize(4) float32_t const * ptr);
		 VLD1.32 {d0, d1}, [r0]
	*/
    A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values at a time from source A buffer */
    A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;

    /* read 2 complex values at a time from source B buffer */
    B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values at a time from source B buffer */
    B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;

    /* unzip real and imag values
	A1: real, imag, real, imag
	A2: real, imag, real, imag
	out1.val0: real, real, real, real;
	out1.val1: img, img, img, img
    	float32x4x2_t vuzpq_f32 (float32x4_t, float32x4_t) 
	Form of expected instruction(s): vuzp.32 q0, q1
	*/
    out1 = vuzpq_f32(A1, A2);
    out2 = vuzpq_f32(B1, B2);

    /* read 2 complex values at a time from source A buffer */
    A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values at a time from source A buffer */
    A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;

    /* read 2 complex values at a time from source B buffer */
    B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values at a time from source B buffer */
    B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;

    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    /* multiply 4 samples at a time from A1 real input with B1 real input 
            // VMUL.F32 q0,q0,q0
	*/
    C1 = vmulq_f32(out1.val[0], out2.val[0]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 imaginary input */
    C2 = vmulq_f32(out1.val[1], out2.val[1]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 real input */
    C3 = vmulq_f32(out1.val[1], out2.val[0]);
    /* multiply 4 samples at a time from A1 real input with B1 imaginary input */
    C4 = vmulq_f32(out1.val[0], out2.val[1]);

    out2 = vuzpq_f32(A1, A2);
    out3 = vuzpq_f32(B1, B2);

    /* read 2 complex values at a time from source A buffer */
    A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values at a time from source A buffer */
    A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;

	/*  (a+bi)*(c+di) = (ac-bd)+(ad+bc)i*/
    /* subtract 4 samples at time from real result to imaginary result, got four real part */
    out1.val[0] = vsubq_f32(C1, C2);
    /* add real*imaginary result with imaginary*real result 4 at a time */
    out1.val[1] = vaddq_f32(C3, C4);
	/* out1 is four complex product. */

    /* read 2 complex values at a time from source B buffer */
    B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values at a time from source B buffer */
    B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;

    /* multiply 4 samples at a time from A1 real input with B1 real input */
    C1 = vmulq_f32(out2.val[0], out3.val[0]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 imaginary input */
    C2 = vmulq_f32(out2.val[1], out3.val[1]);

    /* Store 4 complex samples to destination buffer
             VST2.32 {d0, d2}, [r0]   */
    vst2q_f32(pDst, out1);
    /* increment destination buffer by 8 */
    pDst += 8u;

    /* multiply 4 samples at a time from A1 imaginary input with B1 real input */
    C3 = vmulq_f32(out2.val[1], out3.val[0]);
                               /* multiply 4 samples at a time from A1 real input with B1 imaginary input */
      C4 = vmulq_f32(out2.val[0], out3.val[1]);

    out3 = vuzpq_f32(A1, A2);
    out4 = vuzpq_f32(B1, B2);

    /* read 4 complex values from source A buffer */
    A1 = vld1q_f32(pSrcA);
    pSrcA += 4u;
    A2 = vld1q_f32(pSrcA);
    pSrcA += 4u;

    /* read 4 complex values from source B buffer */
    B1 = vld1q_f32(pSrcB);
    pSrcB += 4u;
    B2 = vld1q_f32(pSrcB);
    pSrcB += 4u;

    /* subtract 4 samples at time from real result to imaginary result */
    out2.val[0] = vsubq_f32(C1, C2);
    /* add real*imaginary result with imaginary*real result 4 at a time */
    out2.val[1] = vaddq_f32(C3, C4);

    /* multiply 4 samples at a time from A3 real input with B3 real input */
    C1 = vmulq_f32(out3.val[0], out4.val[0]);
    /* multiply 4 samples at a time from A3 imaginary input with B3 imaginary input */
    C2 = vmulq_f32(out3.val[1], out4.val[1]);
    /* multiply 4 samples at a time from A3 imaginary input with B3 real input */
    C3 = vmulq_f32(out3.val[1], out4.val[0]);
    /* multiply 4 samples at a time from A3 real input with B3 imaginary input */
    C4 = vmulq_f32(out3.val[0], out4.val[1]);

    out1 = vuzpq_f32(A1, A2);
    out4 = vuzpq_f32(B1, B2);

    /* Store 4 complex samples to destination buffer */
    vst2q_f32(pDst, out2);
    /* increment destination buffer by 8 */
    pDst += 8u;

    /* subtract 4 samples at time from real result to imaginary result */
    out3.val[0] = vsubq_f32(C1, C2);
    /* add real*imaginary result with imaginary*real result 4 at a time */
    out3.val[1] = vaddq_f32(C3, C4);

    /* multiply 4 samples at a time from A1 real input with B1 real input */
    C1 = vmulq_f32(out1.val[0], out4.val[0]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 imaginary input */
    C2 = vmulq_f32(out1.val[1], out4.val[1]);

    /* multiply 4 samples at a time from A1 imaginary input with B1 real input */
    C3 = vmulq_f32(out1.val[1], out4.val[0]);
    /* multiply 4 samples at a time from A1 real input with B1 imaginary input */
    C4 = vmulq_f32(out1.val[0], out4.val[1]);

    /* Store 4 complex samples to destination buffer */
    vst2q_f32(pDst, out3);

    /* subtract 4 samples at time from real result to imaginary result */
    out4.val[0] = vsubq_f32(C1, C2);

    /* increment destination buffer by 8 */
    pDst += 8u;

    /* add real*imaginary result with imaginary*real result 4 at a time */
    out4.val[1] = vaddq_f32(C3, C4);

    /* zip real and imag values */
    out4 = vzipq_f32(out4.val[0], out4.val[1]);

    /* Store 4 complex samples to destination buffer */
    vst1q_f32(pDst, out4.val[0]);
    pDst += 4u;
    vst1q_f32(pDst, out4.val[1]);
    pDst += 4u;

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }

  blkCnt = numSamples & 15u;
  blkCnt = blkCnt >> 2u;

  /* If the blockSize is not a multiple of 16, compute remaining output samples.     
   ** Compute multiple of 4 samples at a time in second loop.  
   ** and remaining 1 to 3 samples in third loop. */
  while(blkCnt > 0u)
  {
    /* read 4 complex values at a time from source A buffer */
    A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 8 */
    pSrcA += 4u;
    A2 = vld1q_f32(pSrcA);
    pSrcA += 4u;
    /* read 4 complex values at a time from source B buffer */
    B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 8 */
    pSrcB += 4u;
    B2 = vld1q_f32(pSrcB);
    pSrcB += 4u;

    out1 = vuzpq_f32(A1, A2);
    out2 = vuzpq_f32(B1, B2);

    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    /* multiply 4 samples at a time from A1 real input with B1 real input */
    C1 = vmulq_f32(out1.val[0], out2.val[0]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 imaginary input */
    C2 = vmulq_f32(out1.val[1], out2.val[1]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 real input */
    C3 = vmulq_f32(out1.val[1], out2.val[0]);
    /* multiply 4 samples at a time from A1 real input with B1 imaginary input */
    C4 = vmulq_f32(out1.val[0], out2.val[1]);

    /* subtract 4 samples at time from real result to imaginary result */
    out1.val[0] = vsubq_f32(C1, C2);
    /* add real*imaginary result with imaginary*real result 4 at a time */
    out1.val[1] = vaddq_f32(C3, C4);

    out1 = vzipq_f32(out1.val[0], out1.val[1]);

    /* Store 4 complex samples to destination buffer */
    vst1q_f32(pDst, out1.val[0]);
    pDst += 4u;
    vst1q_f32(pDst, out1.val[1]);
    pDst += 4u;

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }

  blkCnt = numSamples & 3u;

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.     
   ** No intrinsics is used. */
  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in the destination buffer. */
    *pDst++ = (a * c) - (b * d);
    *pDst++ = (a * d) + (b * c);

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }
}





/**     
 * @} end of CmplxByCmplxMult group     
 */
