/* ----------------------------------------------------------------------   
* Copyright (C) 2011 DSP Concepts LLC . All rights reserved. 
*    
* $Date:        01. August 2011  
* $Revision: 	V0.0.5  
*    
* Project: 	    Cortex-A8/A9 DSP Library 
* Title:	    arm_cmplx_dot_prod_f32_test.c		    
*    
* Description:	Test function for the floating-point Complex Dot Product.   
*   
* Target Processor:          Cortex-A8/A9
* Target Tools Revision:     RVDS Version 4.0
*  
* Version 0.0.5 2011/08/01 
* Initial version.  
* ------------------------------------------------------------------- */   
   
/* ----------------------------------------------------------------------   
** Include Files   
** ------------------------------------------------------------------- */   
  
#include "arm_math.h"   
#include "arm_cmplx_math_test_data.h"   
#include "math_helper.h"   
    
#ifdef ARM_MATH_A
	//#define AVG_CYCLES
#endif
 
/* ----------------------------------------------------------------------   
** Internal functions   
** ------------------------------------------------------------------- */   
   
static void arm_cmplx_dot_prod_f32_test_render(float32_t *A,     
									 float32_t *B,   
									 uint32_t blockSize,  
									 float32_t *realResult,  
									 float32_t *imagResult);   
   
/* ----------------------------------------------------------------------   
** F32 Output buffer   
** ------------------------------------------------------------------- */   
//static float32_t __align(16) testOutput_real[1]; /* real part of Output buffer for each test case */
//static float32_t __align(16) testOutput_imag[1]; /* imag part of Output buffer for each test case */
static float32_t  testOutput_real[1]; /* real part of Output buffer for each test case */
static float32_t  testOutput_imag[1]; /* imag part of Output buffer for each test case */
   
/* ----------------------------------------------------------------------   
** Defines each of the tests performed   
** ------------------------------------------------------------------- */   
   
typedef struct   
{   
  float32_t *inputAF32;   
  float32_t *inputBF32;   
  float32_t outputF32_real;   
  float32_t outputF32_imag;   
  uint32_t  blockSize;   
} test_config;   
   
/* All Test configurations, 100% Code Coverage */   
   
static test_config CONFIG[] = {  
#ifdef AVG_CYCLES 
		{&cmplxDotProd_srcA_buf1_f32[0], &cmplxDotProd_srcB_buf1_f32[0], 5.927364480635, 6.084205819065, 32}, 
		{&cmplxDotProd_srcA_buf1_f32[0], &cmplxDotProd_srcB_buf1_f32[0], 5.927364480635, 6.084205819065, 32}, 
		{&cmplxDotProd_srcA_buf2_f32[0], &cmplxDotProd_srcB_buf2_f32[0], 13.031497835172, -3.891710380381, 64}, 
		{&cmplxDotProd_srcA_buf2_f32[0], &cmplxDotProd_srcB_buf2_f32[0], 13.031497835172, -3.891710380381, 64}, 
		{&cmplxDotProd_srcA_buf3_f32[0], &cmplxDotProd_srcB_buf3_f32[0], 9.336356163147, -2.088406326528, 128}, 
		{&cmplxDotProd_srcA_buf3_f32[0], &cmplxDotProd_srcB_buf3_f32[0], 9.336356163147, -2.088406326528, 128}, 
		{&cmplxDotProd_srcA_buf4_f32[0], &cmplxDotProd_srcB_buf4_f32[0], -20.094836327621, -0.025705374055, 256}, 
		{&cmplxDotProd_srcA_buf4_f32[0], &cmplxDotProd_srcB_buf4_f32[0], -20.094836327621, -0.025705374055, 256}, 
		{&cmplxDotProd_srcA_buf5_f32[0], &cmplxDotProd_srcB_buf5_f32[0], 26.784958633827, 36.999778152901, 512}, 
		{&cmplxDotProd_srcA_buf5_f32[0], &cmplxDotProd_srcB_buf5_f32[0], 26.784958633827, 36.999778152901, 512} 
#else 
		{&cmplxDotProd_srcA_buf6_f32[0], &cmplxDotProd_srcB_buf6_f32[0], -0.977470, 0.818522, 2}, 
		{&cmplxDotProd_srcA_buf7_f32[0], &cmplxDotProd_srcB_buf7_f32[0], 0.616391, 5.759680, 15},
		{&cmplxDotProd_srcA_buf1_f32[0], &cmplxDotProd_srcB_buf1_f32[0], 5.927364480635, 6.084205819065, 32}, 
		{&cmplxDotProd_srcA_buf2_f32[0], &cmplxDotProd_srcB_buf2_f32[0], 13.031497835172, -3.891710380381, 64}, 
		{&cmplxDotProd_srcA_buf3_f32[0], &cmplxDotProd_srcB_buf3_f32[0], 9.336356163147, -2.088406326528, 128}, 
		{&cmplxDotProd_srcA_buf4_f32[0], &cmplxDotProd_srcB_buf4_f32[0], -20.094836327621, -0.025705374055, 256}, 
		{&cmplxDotProd_srcA_buf5_f32[0], &cmplxDotProd_srcB_buf5_f32[0], 26.784958633827, 36.999778152901, 512} 
#endif		 
}; 
 
   
#define NUM_TESTS (sizeof(CONFIG) / sizeof(CONFIG[0]))   
   
/* ----------------------------------------------------------------------   
** Main f32 test function.  It returns either ARM_MATH_TEST_FAILURE or   
** ARM_MATH_SUCCESS.   
** ------------------------------------------------------------------- */   
   
float snr_real, snr_imag;  /* Signal-to-Noise Ratio for real and imaginary outputs */  
  
arm_status test_arm_cmplx_dot_prod_f32( void )   
{   
  uint32_t i;	       /* loop counter */  
  test_config *config; /* configuration structure pointer variable */  
   
  /* Loop over number of test cases */  
  for(i = 0; i < NUM_TESTS; i++)   
  {   
	  /* points to each configuration */  
      config = &CONFIG[i];   
         
      /* Process the data through the Complex Dot Product */   
      arm_cmplx_dot_prod_f32_test_render(config->inputAF32, config->inputBF32,   
	  		config->blockSize, testOutput_real, testOutput_imag);   
   
      /* compare the Real parts of final result with the reference output */   
      snr_real = arm_snr_f32(&config->outputF32_real, &testOutput_real[0], 1);   
   
	  /* compare the calculated snr withe the threshold value */  
      if (snr_real < SNR_THRESHOLD)   
	  {   
	    /* If the output is not matched with the refereence output values,   
		   return the status as ARM_MATH_TEST_FAILURE */  
	  	return(ARM_MATH_TEST_FAILURE); 			   
	  }   
  
	  /* compare the Imaginary parts of final result with the reference output */  
	  snr_imag = arm_snr_f32(&config->outputF32_imag, &testOutput_imag[0], 1);   
   
	  /* compare the calculated snr withe the threshold value */  
      if (snr_imag < SNR_THRESHOLD)   
	  { 		      
	    /* If the output is not matched with the refereence output values,   
		   return the status as ARM_MATH_TEST_FAILURE */  
	  	return(ARM_MATH_TEST_FAILURE); 			   
	  }  
   }   
   
   /* All tests passed! */   
   return(ARM_MATH_SUCCESS);   
}   
   
   
   
/**    
 * @brief  helper function that passes test data through a F32 Complex Dot Product function.   
 * @param[in]  A points to the InputA pointer   
 * @param[in]  B points to the InputB pointer   
 * @param[in]  blockSize is the number of Complex samples to be processed   
 * @param[out] realResult points to the real output pointer   
 * @param[out] imagResult points to the imaginary output pointer   
 */   
   
   
/* Declare these outside of the function so that they are visible to   
** the debuffer. */   
   
static void arm_cmplx_dot_prod_f32_test_render(float32_t *A,     
									 float32_t *B,   
									 uint32_t blockSize,  
									 float32_t *realResult,  
									 float32_t *imagResult)  
{   

#ifdef AVG_CYCLES 
	
	int i, avg_cycles, sum = 0; 
	unsigned int cycle_count_asm = 0; 
	 	 
  for(i=0; i<1000; i++) 
  { 
	  /* ----------------------------------------------------------------------   
	  **  Initialize the timer calculation.   
	  ** ------------------------------------------------------------------- */   
	  enable_ccnt(); 
	  enable_cntens(0x80000001); 
 
	  /* ----------------------------------------------------------------------   
	  ** Call the Complex Dot Product process function     
	  ** ------------------------------------------------------------------- */   
	   
	  arm_cmplx_dot_prod_f32(A, B, blockSize, realResult, imagResult);   
	   
	  /* ----------------------------------------------------------------------   
	  ** Calculate the execution time   
	  ** ------------------------------------------------------------------- */   
	   
	  cycle_count_asm = ccnt(); 
	  disable_ccnt(); 
	  /* copying cycles of the function called each time */ 
	  sum += cycle_count_asm;    
 
  } 
   
  avg_cycles = sum/1000; 
   
  printf("Cmplx_dot_prod_f32 Size = %d Cycles = %d\n", blockSize, avg_cycles);  
   
#else 
 
	/* ----------------------------------------------------------------------   
	** Call the Complex Dot Product process function     
	** ------------------------------------------------------------------- */   
	   
	arm_cmplx_dot_prod_f32(A, B, blockSize, realResult, imagResult);   
 
#endif	   
}   
		   
