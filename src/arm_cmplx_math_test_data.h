#ifndef ARM_CMPLX_MATH_TEST_DATA_H
#define ARM_CMPLX_MATH_TEST_DATA_H

#include "arm_math.h"


/* ----------------------------------------------------------------------
** Global defines 
** ------------------------------------------------------------------- */
#define TEST_LENGTH_SAMPLES 1024
#define SNR_THRESHOLD     115.0f
#define SNR_THRESHOLD_Q31 95.0f
#define SNR_THRESHOLD_Q15 50.0f
#define MAX_BLOCKSIZE 	1024


/* ----------------------------------------------------------------------
** External Declarations for complex conjugate F32 module Test
** ------------------------------------------------------------------- */
extern float32_t testInput1_f32[64];
extern float32_t testRefOutput1_f32[64];

extern float32_t testInput2_f32[128];
extern float32_t testRefOutput2_f32[128];

extern float32_t testInput3_f32[256];
extern float32_t testRefOutput3_f32[256];

extern float32_t testInput4_f32[512];
extern float32_t testRefOutput4_f32[512];

extern float32_t testInput5_f32[1024];
extern float32_t testRefOutput5_f32[1024];
/* ----------------------------------------------------------------------
** External Declarations for complex conjugate Q15 module Test
** ------------------------------------------------------------------- */
extern float32_t testInput1_q15[64];
extern float32_t testRefOutput1_q15[64];

extern float32_t testInput2_q15[128];
extern float32_t testRefOutput2_q15[128];

extern float32_t testInput3_q15[256];
extern float32_t testRefOutput3_q15[256];

extern float32_t testInput4_q15[512];
extern float32_t testRefOutput4_q15[512];

extern float32_t testInput5_q15[1024];
extern float32_t testRefOutput5_q15[1024];

/* ----------------------------------------------------------------------
** External Declarations for complex Magnitude squared F32 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMagSqrd_src_buf1_f32[64];
extern float32_t cmplxMagSqrd_dst_buf1_f32[32];

extern float32_t cmplxMagSqrd_src_buf2_f32[128];  
extern float32_t cmplxMagSqrd_dst_buf2_f32[64];
	 
extern float32_t cmplxMagSqrd_src_buf3_f32[256]; 
extern float32_t cmplxMagSqrd_dst_buf3_f32[128]; 

extern float32_t cmplxMagSqrd_src_buf4_f32[512];  
extern float32_t cmplxMagSqrd_dst_buf4_f32[256];
	 
extern float32_t cmplxMagSqrd_src_buf5_f32[1024]; 
extern float32_t cmplxMagSqrd_dst_buf5_f32[512]; 
/* ----------------------------------------------------------------------
** External Declarations for complex Magnitude squared Q15 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMagSqrd_src_buf1_q15[64];  
extern float32_t cmplxMagSqrd_dst_buf1_q15[32];

extern float32_t cmplxMagSqrd_src_buf2_q15[128];
extern float32_t cmplxMagSqrd_dst_buf2_q15[64];

extern float32_t cmplxMagSqrd_src_buf3_q15[256];  
extern float32_t cmplxMagSqrd_dst_buf3_q15[128];	

extern float32_t cmplxMagSqrd_src_buf4_q15[512];  
extern float32_t cmplxMagSqrd_dst_buf4_q15[256];	

extern float32_t cmplxMagSqrd_src_buf5_q15[1024];  
extern float32_t cmplxMagSqrd_dst_buf5_q15[512];	

/* ----------------------------------------------------------------------
** External Declarations for complex Magnitude F32 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMag_src_buf1_f32[64];
extern float32_t cmplxMag_dst_buf1_f32[32];

extern float32_t cmplxMag_src_buf2_f32[128];  
extern float32_t cmplxMag_dst_buf2_f32[64];	
 
extern float32_t cmplxMag_src_buf3_f32[256] ; 
extern float32_t cmplxMag_dst_buf3_f32[128]; 

extern float32_t cmplxMag_src_buf4_f32[512];  
extern float32_t cmplxMag_dst_buf4_f32[256];	
 
extern float32_t cmplxMag_src_buf5_f32[1024] ; 
extern float32_t cmplxMag_dst_buf5_f32[512]; 

/* ----------------------------------------------------------------------
** External Declarations for complex Magnitude Q15 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMag_src_buf1_q15[64];  
extern float32_t cmplxMag_dst_buf1_q15[32];

extern float32_t cmplxMag_src_buf2_q15[128];
extern float32_t cmplxMag_dst_buf2_q15[64];

extern float32_t cmplxMag_src_buf3_q15[256];  
extern float32_t cmplxMag_dst_buf3_q15[128];	

extern float32_t cmplxMag_src_buf4_q15[512];
extern float32_t cmplxMag_dst_buf4_q15[256];

extern float32_t cmplxMag_src_buf5_q15[1024];  
extern float32_t cmplxMag_dst_buf5_q15[512];	

/* ----------------------------------------------------------------------
** External Declarations for complex Dot Product F32 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxDotProd_srcA_buf1_f32[64];
extern float32_t cmplxDotProd_srcB_buf1_f32[64];

extern float32_t cmplxDotProd_srcA_buf2_f32[128]; 
extern float32_t cmplxDotProd_srcB_buf2_f32[128]; 

extern float32_t cmplxDotProd_srcA_buf3_f32[256] ; 
extern float32_t cmplxDotProd_srcB_buf3_f32[256] ; 

extern float32_t cmplxDotProd_srcA_buf4_f32[512]; 
extern float32_t cmplxDotProd_srcB_buf4_f32[512]; 

extern float32_t cmplxDotProd_srcA_buf5_f32[1024] ; 
extern float32_t cmplxDotProd_srcB_buf5_f32[1024] ; 

extern float32_t cmplxDotProd_srcA_buf6_f32[4];
extern float32_t cmplxDotProd_srcB_buf6_f32[4];

extern float32_t cmplxDotProd_srcA_buf7_f32[30]; 
extern float32_t cmplxDotProd_srcB_buf7_f32[30]; 

/* ----------------------------------------------------------------------
** External Declarations for complex Dot Product Q15 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxDotProd_srcA_buf1_q15[64]; 
extern float32_t cmplxDotProd_srcB_buf1_q15[64];  

extern float32_t cmplxDotProd_srcA_buf2_q15[128];
extern float32_t cmplxDotProd_srcB_buf2_q15[128];

extern float32_t cmplxDotProd_srcA_buf3_q15[256];  
extern float32_t cmplxDotProd_srcB_buf3_q15[256];

extern float32_t cmplxDotProd_srcA_buf4_q15[512];
extern float32_t cmplxDotProd_srcB_buf4_q15[512];

extern float32_t cmplxDotProd_srcA_buf5_q15[1024];  
extern float32_t cmplxDotProd_srcB_buf5_q15[1024];

extern float32_t cmplxDotProd_srcA_buf6_q15[4];
extern float32_t cmplxDotProd_srcB_buf6_q15[4];

extern float32_t cmplxDotProd_srcA_buf7_q15[30];  
extern float32_t cmplxDotProd_srcB_buf7_q15[30];

/* ----------------------------------------------------------------------
** External Declarations for Complex Multiplication By Real F32 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMultReal_srcA_buf1_f32[64];
extern float32_t cmplxMultReal_srcB_buf1_f32[32];
extern float32_t cmplxMultReal_dst_buf1_f32[64];

extern float32_t cmplxMultReal_srcA_buf2_f32[128]; 
extern float32_t cmplxMultReal_srcB_buf2_f32[64]; 
extern float32_t cmplxMultReal_dst_buf2_f32[128];
	 
extern float32_t cmplxMultReal_srcA_buf3_f32[256] ; 
extern float32_t cmplxMultReal_srcB_buf3_f32[128] ; 
extern float32_t cmplxMultReal_dst_buf3_f32[256]; 

extern float32_t cmplxMultReal_srcA_buf4_f32[512]; 
extern float32_t cmplxMultReal_srcB_buf4_f32[256]; 
extern float32_t cmplxMultReal_dst_buf4_f32[512];
	 
extern float32_t cmplxMultReal_srcA_buf5_f32[1024] ; 
extern float32_t cmplxMultReal_srcB_buf5_f32[512] ; 
extern float32_t cmplxMultReal_dst_buf5_f32[1024]; 

/* ----------------------------------------------------------------------
** External Declarations for Complex Multiplication By Real Q15 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMultReal_srcA_buf1_q15[64]; 
extern float32_t cmplxMultReal_srcB_buf1_q15[32];  
extern float32_t cmplxMultReal_dst_buf1_q15[64];

extern float32_t cmplxMultReal_srcA_buf2_q15[128];
extern float32_t cmplxMultReal_srcB_buf2_q15[64];
extern float32_t cmplxMultReal_dst_buf2_q15[128];

extern float32_t cmplxMultReal_srcA_buf3_q15[256];  
extern float32_t cmplxMultReal_srcB_buf3_q15[128];
extern float32_t cmplxMultReal_dst_buf3_q15[256];	

extern float32_t cmplxMultReal_srcA_buf4_q15[512];
extern float32_t cmplxMultReal_srcB_buf4_q15[256];
extern float32_t cmplxMultReal_dst_buf4_q15[512];

extern float32_t cmplxMultReal_srcA_buf5_q15[1024];
extern float32_t cmplxMultReal_srcB_buf5_q15[512];
extern float32_t cmplxMultReal_dst_buf5_q15[1024];

/* ----------------------------------------------------------------------
** External Declarations for Complex Multiplication By Complex F32 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMultCmplx_srcA_buf1_f32[64];
extern float32_t cmplxMultCmplx_srcB_buf1_f32[64];
extern float32_t cmplxMultCmplx_dst_buf1_f32[64];

extern float32_t cmplxMultCmplx_srcA_buf2_f32[128]; 
extern float32_t cmplxMultCmplx_srcB_buf2_f32[128]; 
extern float32_t cmplxMultCmplx_dst_buf2_f32[128];
	 
extern float32_t cmplxMultCmplx_srcA_buf3_f32[256] ; 
extern float32_t cmplxMultCmplx_srcB_buf3_f32[256] ; 
extern float32_t cmplxMultCmplx_dst_buf3_f32[256];
 
extern float32_t cmplxMultCmplx_srcA_buf4_f32[512]; 
extern float32_t cmplxMultCmplx_srcB_buf4_f32[512]; 
extern float32_t cmplxMultCmplx_dst_buf4_f32[512];
	 
extern float32_t cmplxMultCmplx_srcA_buf5_f32[1024] ; 
extern float32_t cmplxMultCmplx_srcB_buf5_f32[1024] ; 
extern float32_t cmplxMultCmplx_dst_buf5_f32[1024];

/* ----------------------------------------------------------------------
** External Declarations for Complex Multiplication By Complex Q15 module Test
** ------------------------------------------------------------------- */

extern float32_t cmplxMultCmplx_srcA_buf1_q15[64]; 
extern float32_t cmplxMultCmplx_srcB_buf1_q15[64];  
extern float32_t cmplxMultCmplx_dst_buf1_q15[64];

extern float32_t cmplxMultCmplx_srcA_buf2_q15[128];
extern float32_t cmplxMultCmplx_srcB_buf2_q15[128];
extern float32_t cmplxMultCmplx_dst_buf2_q15[128];

extern float32_t cmplxMultCmplx_srcA_buf3_q15[256];  
extern float32_t cmplxMultCmplx_srcB_buf3_q15[256];
extern float32_t cmplxMultCmplx_dst_buf3_q15[256];

extern float32_t cmplxMultCmplx_srcA_buf4_q15[512];  
extern float32_t cmplxMultCmplx_srcB_buf4_q15[512];
extern float32_t cmplxMultCmplx_dst_buf4_q15[512];

extern float32_t cmplxMultCmplx_srcA_buf5_q15[1024];  
extern float32_t cmplxMultCmplx_srcB_buf5_q15[1024];
extern float32_t cmplxMultCmplx_dst_buf5_q15[1024];

#endif



