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
void arm_cmplx_mult_cmplx_f32_dot5c(
  unsigned int numSamples )
{
  //float32x4_t A1, A2;                            /* Temporary variables to store real and imaginary values of source buffer A */
  //float32x4_t B1, B2;                            /* Temporary variables to store real and imaginary values of source buffer B */
  float32x4_t C1, C2, C3, C4;                    /* Temporary variables to store multiplication output */
  float32x4_t C5, C6, C7, C8;                    /* Temporary variables to store multiplication output */
  float32x4x2_t out1, out2, out3, out4;          /* Temporary variables to stroe output result */
  //float32x4x2_t acc1;            /* , acc2, Accumulators */
  float 	 sum_real, sum_img;            		/*  */
  uint32_t blkCnt;                               /* loop counters */
  
  float32_t * pSrcA;
  float32_t * pSrcB;
  float32_t * pDst;
  
  pSrcA = gf_array_src_a;
  pSrcB = gf_array_src_b;
  pDst = gf_sum_dsp_concept5c;


  /* Clear accumulators   VDUP.32 q0,r0
	Vector Duplicate duplicates a scalar into every element of the destination vector.
    */
  //acc1.val[0] = vdupq_n_f32(0.0f);
  //acc1.val[1] = vdupq_n_f32(0.0f);
  //acc2.val[0] = vdupq_n_f32(0.0f);
  //acc2.val[1] = vdupq_n_f32(0.0f);

  C1 = vdupq_n_f32(0.0f);
  C2 = vdupq_n_f32(0.0f);
  C3 = vdupq_n_f32(0.0f);
  C4 = vdupq_n_f32(0.0f);
  C5 = vdupq_n_f32(0.0f);
  C6 = vdupq_n_f32(0.0f);
  C7 = vdupq_n_f32(0.0f);
  C8 = vdupq_n_f32(0.0f);


  /* Loop over blockSize number of values */
  /* Compute 8 datas in each loop. Remove group c&d */
  blkCnt = numSamples >> 3u;

  while(blkCnt > 0u)
  {
  	/*  A1, A2, B1, B2 each has two complex data. */
	
	/******************************************************/
	/* Step 1: Load data A1, A2, B1, B2 for group a:*/
    /* read 2 complex values at a time from source A buffer 
	float32x4_t vld1q_f32(__transfersize(4) float32_t const * ptr);
		 VLD1.32 {d0, d1}, [r0]
		 
	float32x4x2_t vld2q_f32 (const float32_t *) 
	Form of expected instruction(s): vld2.32 {d0, d1}, [r0]
	arm_cmplx_conj_f32
	*/
    //A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    //pSrcA += 4u;
    /* read 2 complex values at a time from source A buffer */
    //A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    //pSrcA += 4u;

    /* read 2 complex values at a time from source B buffer */
    //B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    //pSrcB += 4u;
    /* read 2 complex values at a time from source B buffer */
    //B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    //pSrcB += 4u;

	/******************************************************/
	/* Step 2: Unzip data Out1, Out2 for group a:*/
    /* unzip real and imag values
	A1: reala0, imga0, reala1, imga1
	A2: realb0, imgb0, realb1, imgb1
	out1.val0: reala0, reala1, realb0, realb1;
	out1.val1: imga0, imga1, imgb0, imgb1

	vuzpq_f32:
    	float32x4x2_t vuzpq_f32 (float32x4_t, float32x4_t) 
	Form of expected instruction(s): vuzp.32 q0, q1
	Vector Unzip de-interleaves the elements of two vectors. 
	*/
	//out1 = vuzpq_f32(A1, A2);
	//out2 = vuzpq_f32(B1, B2);
	out1 = vld2q_f32(pSrcA);
    pSrcA += 8u;
	out2 = vld2q_f32(pSrcB);
    pSrcB += 8u;

	/******************************************************/
	/* Step 1: Load data A1, A2, B1, B2 for group b:*/
    /* read 2 complex values at a time from source A buffer */
    //A1 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    //pSrcA += 4u;
    /* read 2 complex values at a time from source A buffer */
    //A2 = vld1q_f32(pSrcA);
    /* increment source A buffer by 4 */
    //pSrcA += 4u;

    /* read 2 complex values at a time from source B buffer */
    //B1 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    //pSrcB += 4u;
    /* read 2 complex values at a time from source B buffer */
    //B2 = vld1q_f32(pSrcB);
    /* increment source B buffer by 4 */
    //pSrcB += 4u;

	/******************************************************/
	/* Step 3: Compute data C1,C2,C3,C4 for group a:*/
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    /* vmulq_f32: VMUL.F32 q0,q0,q0
		val[0]: real
		val[1]: img
		C1 = a.real*b.real;  		C2 = a.img*b.img
		C3 = a.img*b.real;  		C4 = a.real*b.img
	*/    
	/* multiply 4 samples at a time from A1 real input with B1 real input 	*/
    //C1 = vmulq_f32(out1.val[0], out2.val[0]);  
	C1 = vmlaq_f32(C1, out1.val[0], out2.val[0]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 imaginary input */
    //C2 = vmulq_f32(out1.val[1], out2.val[1]);
    C2 = vmlaq_f32(C2, out1.val[1], out2.val[1]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 real input */
    //C3 = vmulq_f32(out1.val[1], out2.val[0]);
    C3 = vmlaq_f32(C3, out1.val[1], out2.val[0]);
    /* multiply 4 samples at a time from A1 real input with B1 imaginary input */
    //C4 = vmulq_f32(out1.val[0], out2.val[1]);
    C4 = vmlaq_f32(C4, out1.val[0], out2.val[1]);
	/*  real: c1-c2; img: c3+c4 */

	/******************************************************/
	/* Step 2: Unzip data Out2, Out3 for group b:*/
    //out2 = vuzpq_f32(A1, A2);
    //out3 = vuzpq_f32(B1, B2);
	out3 = vld2q_f32(pSrcA);
    pSrcA += 8u;
	out4 = vld2q_f32(pSrcB);
    pSrcB += 8u;


	/******************************************************/
	/* Step 4: Output or accumlate data for group a:*/
	/*  (a+bi)*(c+di) = (ac-bd)+(ad+bc)i*/
	/*  real: c1-c2; img: c3+c4 */
    /* subtract 4 samples at time from real result to imaginary result, got four real part */
	/*  
		C1 = a.real*b.real; 		C2 = a.img*b.img
		C3 = a.img*b.real;		C4 = a.real*b.img

		vaddq_f32: 
		VADD.F32 q0,q0,q0
	*/
    //out1.val[0] = vsubq_f32(C1, C2);
	//acc1.val[0] = vaddq_f32(out1.val[0], acc1.val[0]);  /* add by Hank */
    /* add real*imaginary result with imaginary*real result 4 at a time */
    //out1.val[1] = vaddq_f32(C3, C4);
	//acc1.val[1] = vaddq_f32(out1.val[1], acc1.val[1]); /* add by Hank */
	/* out1 is four complex product. */

	/******************************************************/
	/* Step 3: Compute data C1,C2   for group b:*/
    /* multiply 4 samples at a time from A1 real input with B1 real input */
    //C1 = vmulq_f32(out2.val[0], out3.val[0]);
    C5 = vmlaq_f32(C5, out3.val[0], out4.val[0]);
    /* multiply 4 samples at a time from A1 imaginary input with B1 imaginary input */
    //C2 = vmulq_f32(out2.val[1], out3.val[1]);
    C6 = vmlaq_f32(C6, out3.val[1], out4.val[1]);

	/******************************************************/
	/* Step 5: Store data for group a:*/
    /* Store 4 complex samples to destination buffer
             VST2.32 {d0, d2}, [r0]   */
    //vst2q_f32(pDst, out1);
    /* increment destination buffer by 8 */
    //pDst += 8u;

	/******************************************************/
	/* Step 3: Compute data  C3,C4 for group b:*/
    /* multiply 4 samples at a time from A1 imaginary input with B1 real input */
    //C3 = vmulq_f32(out2.val[1], out3.val[0]);
    C7 = vmlaq_f32(C7, out3.val[1], out4.val[0]);
   /* multiply 4 samples at a time from A1 real input with B1 imaginary input */
	//C4 = vmulq_f32(out2.val[0], out3.val[1]);
	C8 = vmlaq_f32(C8, out3.val[0], out4.val[1]);


	/******************************************************/
	/* Step 4: Output or accumlate data for group b:*/
    /* subtract 4 samples at time from real result to imaginary result */
    //out2.val[0] = vsubq_f32(C1, C2);
    /* add real*imaginary result with imaginary*real result 4 at a time */
    //out2.val[1] = vaddq_f32(C3, C4);
	//acc2.val[0] = vaddq_f32(out2.val[0], acc2.val[0]);  /* add by Hank */
	//acc2.val[1] = vaddq_f32(out2.val[1], acc2.val[1]); /* add by Hank */

	/******************************************************/
	/* Step 5: Store data for group b:*/
    /* Store 4 complex samples to destination buffer */
    //vst2q_f32(pDst, out2);
    /* increment destination buffer by 8 */
    //pDst += 8u;

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }

  /******************************************************/
  /* Step 4: Output or accumlate data for group a:*/
  /*  (a+bi)*(c+di) = (ac-bd)+(ad+bc)i*/
  /*  real: c1-c2; img: c3+c4 */
  /* subtract 4 samples at time from real result to imaginary result, got four real part */
  out1.val[0] = vsubq_f32(C1, C2);
  /* add real*imaginary result with imaginary*real result 4 at a time */
  out1.val[1] = vaddq_f32(C3, C4);
  /* out1 is four complex product. */

  
  /******************************************************/
  /* Step 4: Output or accumlate data for group b:*/
  /* subtract 4 samples at time from real result to imaginary result */
  out2.val[0] = vsubq_f32(C5, C6);
  /* add real*imaginary result with imaginary*real result 4 at a time */
  out2.val[1] = vaddq_f32(C7, C8);


  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.     
   ** No intrinsics is used. */
  sum_real =0;
  sum_img =0;


	/* add 4 accumulators */
	out1.val[0] = vaddq_f32(out1.val[0], out2.val[0]);
	out1.val[1] = vaddq_f32(out1.val[1], out2.val[1]);

	sum_real = vgetq_lane_f32(out1.val[0], 0) + vgetq_lane_f32(out1.val[0], 1)
		+ vgetq_lane_f32(out1.val[0], 2) + vgetq_lane_f32(out1.val[0], 3);
	sum_img = vgetq_lane_f32(out1.val[1], 0) + vgetq_lane_f32(out1.val[1], 1)
		+ vgetq_lane_f32(out1.val[1], 2) + vgetq_lane_f32(out1.val[1], 3);

	*pDst++=sum_real;
	*pDst++=sum_img;

}





/**     
 * @} end of CmplxByCmplxMult group     
 */
 
