/* ----------------------------------------------------------------------     
* Copyright (C) 2011 DSP Concepts LLC . All rights reserved. 
*     
* $Date:        07. October 2011  
* $Revision: 	V1.0.0  
*     
* Project: 	    Cortex-A DSP Library 
* Title:		arm_cmplx_dot_prod_f32.c     
*     
* Description:	Floating-point complex dot product     
*     
* Target Processor:          Cortex-A
* Target Tools Revision:     RVDS Version 4.0
*  
* Version 1.0.0 2011/10/07 
* Initial version.  
*   
* ---------------------------------------------------------------------------- */
#include "arm_math.h"

/**     
 * @ingroup groupCmplxMath     
 */

/**     
 * @defgroup cmplx_dot_prod Complex Dot Product     
 *     
 * Computes the dot product of two complex vectors.     
 * The vectors are multiplied element-by-element and then summed.     
 *    
 * The <code>pSrcA</code> points to the first complex input vector and     
 * <code>pSrcB</code> points to the second complex input vector.     
 * <code>numSamples</code> specifies the number of complex samples     
 * and the data in each array is stored in an interleaved fashion     
 * (real, imag, real, imag, ...).     
 * Each array has a total of <code>2*numSamples</code> values.     
 *     
 *  (a+bi)(c+di)  = (a*c-b*d) + (a*d+b*c)i 
 * The underlying algorithm is used:     
 * <pre>     
 * realResult=0;     
 * imagResult=0;     
 * for(n=0; n<numSamples; n++) {     
 *     realResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+0] - pSrcA[(2*n)+1]*pSrcB[(2*n)+1];     
 *     imagResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+1] + pSrcA[(2*n)+1]*pSrcB[(2*n)+0];     
 * }     
 * </pre>     
 *     
 * This function uses the 4 way SIMD and loop unrolled by 4. Select the blocksize as multiple of 16 for better performance how ever this function can   
 * support any block size.   
 * There are separate functions for floating-point and Q31 data types.     
 */

/**     
 * @addtogroup cmplx_dot_prod     
 * @{     
 */

/**     
 * @brief  Floating-point complex dot product     
 * @param  *pSrcA points to the first input vector     
 * @param  *pSrcB points to the second input vector     
 * @param  numSamples number of complex samples in each vector     
 * @param  *realResult real part of the result returned here     
 * @param  *imagResult imaginary part of the result returned here     
 * @return none.     
 */

void arm_cmplx_dot_prod_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  uint32_t numSamples,
  float32_t * realResult,
  float32_t * imagResult)
{
  float32_t real_sum, imag_sum;                  /* Temporary result storage */
  float32x4_t acc1, acc2, acc3, acc4;            /* Accumulators */
  float32x4_t A1, A2, A3, A4, B1, B2, B3, B4;    /* Temporay variables to store input data */
  uint32_t blkCnt;                               /* loop counter */

  /* Loop over blockSize number of values */
  blkCnt = numSamples >> 4u;

  /* Clear accumulators   VDUP.32 q0,r0
	Vector Duplicate duplicates a scalar into every element of the destination vector.
    */
  acc1 = vdupq_n_f32(0.0f);
  acc2 = vdupq_n_f32(0.0f);
  acc3 = vdupq_n_f32(0.0f);
  acc4 = vdupq_n_f32(0.0f);

  /* First part of the processing with instrinsics.  Compute 16 outputs at a time.     
   ** second and third loop below computes remaining 1 to 15 samples. */
  while(blkCnt > 0)
  {
	/* ==============================================*/
	/* The first group, four vector, 8 complex data */
	/* read 2 complex values from source A buffer */
    /* real and imaginary values are in interleaved form */
    A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values from source A buffer */
    A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values from source A buffer */
    A3 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values from source A buffer */
    A4 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;

    /* read 2 complex values from source B buffer */
    B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values from source B buffer */
    B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values from source B buffer */
    B3 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values from source B buffer */
    B4 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;

    /* acc[0] = A[0]* B[0] + A[4]* B[4] + A[8]* B[8] + .....+ A[numSamples-4]* B[numSamples-4] */
    /* acc[1] = A[1]* B[1] + A[5]* B[5] + A[9]* B[9] + .....+ A[numSamples-3]* B[numSamples-3] */
    /* acc[2] = A[2]* B[2] + A[6]* B[6] + A[10]* B[10] + .....+ A[numSamples-2]* B[numSamples-2] */
    /* acc[3] = A[3]* B[3] + A[7]* B[7] + A[11]* B[11] + .....+ A[numSamples-1]* B[numSamples-1] */
    /* multiply accumulate 2 real and 2 imaginary values at a time 
	VMLA.F32 q0,q0,q0
	*/
    acc1 = vmlaq_f32(acc1, A1, B1);
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc2 = vmlaq_f32(acc2, A2, B2);
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc3 = vmlaq_f32(acc3, A3, B3);
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc4 = vmlaq_f32(acc4, A4, B4);
    
	/* ==============================================*/
	/* The second  group, four vector, 8 complex data */
    /* read 2 complex values from source A buffer */
    A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values from source A buffer */
    A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values from source A buffer */
    A3 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values from source A buffer */
    A4 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;

    /* read 2 complex values from source B buffer */
    B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values from source B buffer */
    B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values from source B buffer */
    B3 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values from source B buffer */
    B4 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;

    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc1 = vmlaq_f32(acc1, A1, B1);
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc2 = vmlaq_f32(acc2, A2, B2);
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc3 = vmlaq_f32(acc3, A3, B3);
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc4 = vmlaq_f32(acc4, A4, B4);

    /* Decrement the loop counter */
    blkCnt--;
  }

  blkCnt = numSamples & 15u;
  blkCnt = blkCnt >> 2u;

  acc1 = vaddq_f32(acc1, acc2);
  acc2 = vaddq_f32(acc3, acc4);

  /* If the blockSize is not a multiple of 16, compute remaining output samples.     
   ** Compute multiple of 4 samples at a time in second loop.  
   ** and remaining 1 to 3 samples in third loop. */

  while(blkCnt > 0)
  {
    /* read 2 complex values from source A buffer */
    A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;
    /* read 2 complex values from source A buffer */
    A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    pSrcA += 4u;

    /* read 2 complex values from source B buffer */
    B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;
    /* read 2 complex values from source B buffer */
    B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    pSrcB += 4u;

    /* acc[0] = A[0]* B[0] + A[4]* B[4] + A[8]* B[8] + .....+ A[numSamples-4]* B[numSamples-4] */
    /* acc[1] = A[1]* B[1] + A[5]* B[5] + A[9]* B[9] + .....+ A[numSamples-3]* B[numSamples-3] */
    /* acc[2] = A[2]* B[2] + A[6]* B[6] + A[10]* B[10] + .....+ A[numSamples-2]* B[numSamples-2] */
    /* acc[3] = A[3]* B[3] + A[7]* B[7] + A[11]* B[11] + .....+ A[numSamples-1]* B[numSamples-1] */
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc1 = vmlaq_f32(acc1, A1, B1);
    /* multiply accumulate 2 real and 2 imaginary values at a time */
    acc2 = vmlaq_f32(acc2, A2, B2);

    /* Decrement the loop counter */
    blkCnt--;
  }
  /* add 2 accumulators */
  acc1 = vaddq_f32(acc1, acc2);

  /*  (a+bi)(c+di)	= (a*c-b*d) + (a*d+b*c)i */
  /* add and get real result       VMOV.32 r0, d0[0]    */
  real_sum = vgetq_lane_f32(acc1, 0) + vgetq_lane_f32(acc1, 2);

  /* add and get imaginary result */
  imag_sum = vgetq_lane_f32(acc1, 1) + vgetq_lane_f32(acc1, 3);

  blkCnt = numSamples & 3u;

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.     
   ** No intrinsics is used. */
  while(blkCnt > 0)
  {
    /*  (a+bi)(c+di)  = (a*c-b*d) + (a*d+b*c)i */
    /* CReal = A[0]* B[0] + A[2]* B[2] + A[4]* B[4] + .....+ A[numSamples-2]* B[numSamples-2] */
    real_sum += (*pSrcA++) * (*pSrcB++);
    /* CImag = A[1]* B[1] + A[3]* B[3] + A[5]* B[5] + .....+ A[numSamples-1]* B[numSamples-1] */
    imag_sum += (*pSrcA++) * (*pSrcB++);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Store the real and imaginary results in the destination buffers */
  *realResult = real_sum;
  *imagResult = imag_sum;
}

/**     
 * @} end of cmplx_dot_prod group     
 */



 
 /**	 
  * @ingroup groupCmplxMath 	
  */
 
 /**	 
  * @defgroup cmplx_dot_prod Complex Dot Product	 
  * 	
  * Computes the dot product of two complex vectors.	 
  * The vectors are multiplied element-by-element and then summed.	   
  *    
  * The <code>pSrcA</code> points to the first complex input vector and 	
  * <code>pSrcB</code> points to the second complex input vector.	  
  * <code>numSamples</code> specifies the number of complex samples 	
  * and the data in each array is stored in an interleaved fashion	   
  * (real, imag, real, imag, ...).	   
  * Each array has a total of <code>2*numSamples</code> values. 	
  * 	
  *  (a+bi)(c+di)  = (a*c-b*d) + (a*d+b*c)i 
  * The underlying algorithm is used:	  
  * <pre>	  
  * realResult=0;	  
  * imagResult=0;	  
  * for(n=0; n<numSamples; n++) {	  
  * 	realResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+0] - pSrcA[(2*n)+1]*pSrcB[(2*n)+1];	 
  * 	imagResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+1] + pSrcA[(2*n)+1]*pSrcB[(2*n)+0];	 
  * }	  
  * </pre>	   
  * 	
  * This function uses the 4 way SIMD and loop unrolled by 4. Select the blocksize as multiple of 16 for better performance how ever this function can	 
  * support any block size.   
  * There are separate functions for floating-point and Q31 data types. 	
  */
 
 /**	 
  * @addtogroup cmplx_dot_prod	   
  * @{	   
  */
 
 /**	 
  * @brief	Floating-point complex dot product	   
  * @param	*pSrcA points to the first input vector 	
  * @param	*pSrcB points to the second input vector	 
  * @param	numSamples number of complex samples in each vector 	
  * @param	*realResult real part of the result returned here	  
  * @param	*imagResult imaginary part of the result returned here	   
  * @return none.	  
  */
 
 void arm_cmplx_dot_prod_f322(
   float32_t * pSrcA,
   float32_t * pSrcB,
   uint32_t numSamples,
   float32_t * realResult,
   float32_t * imagResult)
 {
   float32_t real_sum, imag_sum;				  /* Temporary result storage */
   float32x4_t acc1, acc2, acc3, acc4;			  /* Accumulators */
   float32x4_t A1, A2, A3, A4, B1, B2, B3, B4;	  /* Temporay variables to store input data */
   uint32_t blkCnt; 							  /* loop counter */
 
   /* Loop over blockSize number of values */
   blkCnt = numSamples >> 4u;
 
   /* Clear accumulators   VDUP.32 q0,r0
	 Vector Duplicate duplicates a scalar into every element of the destination vector.
	 */
   acc1 = vdupq_n_f32(0.0f);
   acc2 = vdupq_n_f32(0.0f);
   acc3 = vdupq_n_f32(0.0f);
   acc4 = vdupq_n_f32(0.0f);
 
   /* First part of the processing with instrinsics.  Compute 16 outputs at a time. 	
	** second and third loop below computes remaining 1 to 15 samples. */
   while(blkCnt > 0)
   {
	 /* ==============================================*/
	 /* The first group, four vector, 8 complex data */
	 /* read 2 complex values from source A buffer */
	 /* real and imaginary values are in interleaved form */
	 A1 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
	 /* read 2 complex values from source A buffer */
	 A2 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
	 /* read 2 complex values from source A buffer */
	 A3 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
	 /* read 2 complex values from source A buffer */
	 A4 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
 
	 /* read 2 complex values from source B buffer */
	 B1 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
	 /* read 2 complex values from source B buffer */
	 B2 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
	 /* read 2 complex values from source B buffer */
	 B3 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
	 /* read 2 complex values from source B buffer */
	 B4 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
 
	 /* acc[0] = A[0]* B[0] + A[4]* B[4] + A[8]* B[8] + .....+ A[numSamples-4]* B[numSamples-4] */
	 /* acc[1] = A[1]* B[1] + A[5]* B[5] + A[9]* B[9] + .....+ A[numSamples-3]* B[numSamples-3] */
	 /* acc[2] = A[2]* B[2] + A[6]* B[6] + A[10]* B[10] + .....+ A[numSamples-2]* B[numSamples-2] */
	 /* acc[3] = A[3]* B[3] + A[7]* B[7] + A[11]* B[11] + .....+ A[numSamples-1]* B[numSamples-1] */
	 /* multiply accumulate 2 real and 2 imaginary values at a time 
	 VMLA.F32 q0,q0,q0
	 */
	 acc1 = vmlaq_f32(acc1, A1, B1);
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc2 = vmlaq_f32(acc2, A2, B2);
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc3 = vmlaq_f32(acc3, A3, B3);
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc4 = vmlaq_f32(acc4, A4, B4);
	 
	 /* ==============================================*/
	 /* The second	group, four vector, 8 complex data */
	 /* read 2 complex values from source A buffer */
	 A1 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
	 /* read 2 complex values from source A buffer */
	 A2 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
	 /* read 2 complex values from source A buffer */
	 A3 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
	 /* read 2 complex values from source A buffer */
	 A4 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
 
	 /* read 2 complex values from source B buffer */
	 B1 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
	 /* read 2 complex values from source B buffer */
	 B2 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
	 /* read 2 complex values from source B buffer */
	 B3 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
	 /* read 2 complex values from source B buffer */
	 B4 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
 
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc1 = vmlaq_f32(acc1, A1, B1);
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc2 = vmlaq_f32(acc2, A2, B2);
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc3 = vmlaq_f32(acc3, A3, B3);
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc4 = vmlaq_f32(acc4, A4, B4);
 
	 /* Decrement the loop counter */
	 blkCnt--;
   }
 
   blkCnt = numSamples & 15u;
   blkCnt = blkCnt >> 2u;
 
   acc1 = vaddq_f32(acc1, acc2);
   acc2 = vaddq_f32(acc3, acc4);
 
   /* If the blockSize is not a multiple of 16, compute remaining output samples.	  
	** Compute multiple of 4 samples at a time in second loop.	
	** and remaining 1 to 3 samples in third loop. */
 
   while(blkCnt > 0)
   {
	 /* read 2 complex values from source A buffer */
	 A1 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
	 /* read 2 complex values from source A buffer */
	 A2 = vld1q_f32(pSrcA);
	 /* increment source A buffer by 4 */
	 pSrcA += 4u;
 
	 /* read 2 complex values from source B buffer */
	 B1 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
	 /* read 2 complex values from source B buffer */
	 B2 = vld1q_f32(pSrcB);
	 /* increment source B buffer by 4 */
	 pSrcB += 4u;
 
	 /* acc[0] = A[0]* B[0] + A[4]* B[4] + A[8]* B[8] + .....+ A[numSamples-4]* B[numSamples-4] */
	 /* acc[1] = A[1]* B[1] + A[5]* B[5] + A[9]* B[9] + .....+ A[numSamples-3]* B[numSamples-3] */
	 /* acc[2] = A[2]* B[2] + A[6]* B[6] + A[10]* B[10] + .....+ A[numSamples-2]* B[numSamples-2] */
	 /* acc[3] = A[3]* B[3] + A[7]* B[7] + A[11]* B[11] + .....+ A[numSamples-1]* B[numSamples-1] */
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc1 = vmlaq_f32(acc1, A1, B1);
	 /* multiply accumulate 2 real and 2 imaginary values at a time */
	 acc2 = vmlaq_f32(acc2, A2, B2);
 
	 /* Decrement the loop counter */
	 blkCnt--;
   }
   /* add 2 accumulators */
   acc1 = vaddq_f32(acc1, acc2);
 
   /*  (a+bi)(c+di)  = (a*c-b*d) + (a*d+b*c)i */
   /* add and get real result		VMOV.32 r0, d0[0]	 */
   real_sum = vgetq_lane_f32(acc1, 0) + vgetq_lane_f32(acc1, 2);
 
   /* add and get imaginary result */
   imag_sum = vgetq_lane_f32(acc1, 1) + vgetq_lane_f32(acc1, 3);
 
   blkCnt = numSamples & 3u;
 
   /* If the blockSize is not a multiple of 4, compute any remaining output samples here.	  
	** No intrinsics is used. */
   while(blkCnt > 0)
   {
	 /*  (a+bi)(c+di)  = (a*c-b*d) + (a*d+b*c)i */
	 /* CReal = A[0]* B[0] + A[2]* B[2] + A[4]* B[4] + .....+ A[numSamples-2]* B[numSamples-2] */
	 real_sum += (*pSrcA++) * (*pSrcB++);
	 /* CImag = A[1]* B[1] + A[3]* B[3] + A[5]* B[5] + .....+ A[numSamples-1]* B[numSamples-1] */
	 imag_sum += (*pSrcA++) * (*pSrcB++);
 
	 /* Decrement the loop counter */
	 blkCnt--;
   }
 
   /* Store the real and imaginary results in the destination buffers */
   *realResult = real_sum;
   *imagResult = imag_sum;
 }

