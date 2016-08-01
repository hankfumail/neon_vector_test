/* ----------------------------------------------------------------------
 * Copyright (C) 2011 DSP Concepts LLC . All rights reserved. 
 *
 * $Date:        07. October 2011  
 * $Revision: 	V1.0.0  
 *
 * Project:      Cortex-A DSP Library
 * Title:	     arm_math.h
 *
 * Description:	 Public header file for Cortex-A DSP Library
 *
 * Target Processor: Cortex-A
 * Target Tools Revision:     RVDS Version 4.0
 *  
 * Version 1.0.0 2011/10/07 
 * Initial version.  
 *  
 *-------------------------------------------------------------------*/

/**
   \mainpage Cortex-A Series DSP Software Library
   *
   * <b>Introduction</b>
   *
   * This user manual describes the Cortex-A Series DSP software library, 
   * a suite of common signal processing functions for use on Cortex-A family of processors based devices.
   *
   * The library is divided into a number of modules each covering a specific category:
   * - Basic math functions
   * - Complex math functions
   * - Fast math functions
   * - Filters
   * - Interpolation Functions
   * - Matrix Functions
   * - Statistics Functions
   * - Support functions
   * - Transform functions
   *
   * The library has separate functions for operating on 32-bit integer and 32-bit floating-point values. 
   *
   * <b>Processor Support</b>
   *
   * The library is completely written in C. 
   * High performance is achieved through maximum use of Cortex-A NEON intrinsics. 
   *
   *
   * <b>Toolchain Support</b>
   *
   * The library has been developed and tested on Cortex-A8 processor (Beagle board) and Cortex-A9 processor (Panda board) with RVDS version 4.0. But can be re-usable on all Cortex-A family processors. 
   *
   * <b>Using the Library</b>
   *
   * The library installer contains prebuilt version of the library in the <code>Lib</code> folder.
   *
   * The library functions are declared in the public file <code>arm_math.h</code> which is placed in the <code>Include</code> folder.
   * Simply include this file and link the library in your application and begin calling the library functions.
   *
   * <b>Examples</b>
   *
   * The library ships with a number of examples which demonstrate how to use the library functions.
   *
   * <b>Building the Library</b>
   *
   * The library installer also contains project files to re build the library on RVDS Tool chain, and Linux machines with GCC and ARMCC in the <code>Libs</code> folder.
   *
   *
   * The project can be built by opening the project in RVDS Version 4.0 Tool chain or on Linux machine with makefile. 
   *
   * <b>Copyright Notice</b>
   *
   * Copyright (C) 2011 DSP Concepts LLC . All rights reserved. 
   */


/**
 * @defgroup groupMath Basic Math Functions
 */

/**
 * @defgroup groupCmplxMath Complex Math Functions
 * This set of functions operates on complex data vectors.
 * The data in the complex arrays is stored in an interleaved fashion
 * (real, imag, real, imag, ...).
 * In the API functions, the number of samples in a complex array refers
 * to the number of complex values; the array contains twice this number of
 * real values.
 */

/**
 * @defgroup groupFastMath Fast Math Functions
 * This set of functions provides a fast approximation to sine, cosine, and square root.
 * As compared to most of the other functions in the Cortex-A DSP library, the fast math functions
 * operate on individual values and not arrays.
 * There are separate functions for Q31 and floating-point data.
 *
 */

/**
 * @defgroup groupFilters Filtering Functions
 */

/**
 * @defgroup groupInterpolation Interpolation Functions
 */

/**
 * @defgroup groupMatrix Matrix Functions
 */

/**
 * @defgroup groupStats Statistics Functions
 */

/**
 * @defgroup groupSupport Support Functions
 */

/**
 * @defgroup groupTransforms Transforms Functions
 */

/**
 * @defgroup groupExamples Examples
 */

#ifndef _ARM_MATH_H
#define _ARM_MATH_H

#include <arm_neon.h>
#include "string.h"

#ifdef NO_ALIGN
#define __align(x)
#endif


#ifdef	__cplusplus
extern "C"
{
#endif


  /**
   * @brief Macros required for reciprocal calculation in Normalized LMS
   */

#define DELTA_Q31 			(0x100)
#define DELTA_Q15 			0x5
#define INDEX_MASK 			0x0000003F
#define PI					3.14159265358979f

  /**
   * @brief Macros required for SINE and COSINE Fast math approximations
   */

#define TABLE_SIZE			256
#define TABLE_SPACING_Q31	0x800000
#define TABLE_SPACING_Q15	0x80

  /**
   * @brief Macros required for SINE and COSINE Controller functions
   */
  /* 1.31(q31) Fixed value of 2/360 */
  /* -1 to +1 is divided into 360 values so total spacing is (2/360) */
#define INPUT_SPACING			0xB60B61


  /**
   * @brief Error status returned by some functions in the library.
   */

  typedef enum
  {
    ARM_MATH_SUCCESS = 0,                /**< No error */
    ARM_MATH_ARGUMENT_ERROR = -1,        /**< One or more arguments are incorrect */
    ARM_MATH_LENGTH_ERROR = -2,          /**< Length of data buffer is incorrect */
    ARM_MATH_SIZE_MISMATCH = -3,         /**< Size of matrices is not compatible with the operation. */
    ARM_MATH_NANINF = -4,                /**< Not-a-number (NaN) or infinity is generated */
    ARM_MATH_SINGULAR = -5,              /**< Generated by matrix inversion if the input matrix is singular and cannot be inverted. */
    ARM_MATH_TEST_FAILURE = -6           /**< Test Failed  */
  } arm_status;

   /**
   * @brief 8-bit integer data type.
   */
  typedef signed char int8_t;
  typedef unsigned char uint8_t;

    /**
   * @brief 8-bit integer data type.
   */
  typedef signed short int16_t;
  typedef unsigned short uint16_t;

    /**
   * @brief 8-bit integer data type.
   */
  //typedef signed int int32_t;
  //typedef unsigned int uint32_t;

#define __INLINE __inline

  /**
   * @brief 8-bit fractional data type in 1.7 format.
   */
  typedef int8_t q7_t;

  /**
   * @brief 16-bit fractional data type in 1.15 format.
   */
  typedef int16_t q15_t;

  /**
   * @brief 32-bit fractional data type in 1.31 format.
   */
  typedef int32_t q31_t;

  /**
   * @brief 64-bit fractional data type in 1.63 format.
   */
  typedef int64_t q63_t;

  /**
   * @brief 32-bit floating-point type definition.
   */
  typedef float float32_t;

  /**
   * @brief 64-bit floating-point type definition.
   */
  typedef double float64_t;

  /**
   * @brief definition to read/write two 16 bit values.
   */
#define __SIMD32(addr)  (*(int32_t **) & (addr))


  /**
   * @brief definition to pack four 8 bit values.
   */
#define __PACKq7(v0,v1,v2,v3) ( (((int32_t)(v0) <<  0) & (int32_t)0x000000FF) |	\
                                (((int32_t)(v1) <<  8) & (int32_t)0x0000FF00) |	\
							    (((int32_t)(v2) << 16) & (int32_t)0x00FF0000) |	\
							    (((int32_t)(v3) << 24) & (int32_t)0xFF000000)  )


  /**
   * @brief Clips Q63 to Q31 values.
   */
  static __INLINE q31_t clip_q63_to_q31(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFFFFFF ^ ((q31_t) (x >> 62)))) : (q31_t) x;
  }

  /**
   * @brief Clips Q63 to Q15 values.
   */
  static __INLINE q15_t clip_q63_to_q15(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFF ^ ((q15_t) (x >> 63)))) : (q15_t) (x >> 15);
  }

  /**
   * @brief Clips Q31 to Q7 values.
   */
  static __INLINE q7_t clip_q31_to_q7(
  q31_t x)
  {
    return ((q31_t) (x >> 24) != ((q31_t) x >> 23)) ?
      ((0x7F ^ ((q7_t) (x >> 31)))) : (q7_t) x;
  }

  /**
   * @brief Clips Q31 to Q15 values.
   */
  static __INLINE q15_t clip_q31_to_q15(
  q31_t x)
  {
    return ((q31_t) (x >> 16) != ((q31_t) x >> 15)) ?
      ((0x7FFF ^ ((q15_t) (x >> 31)))) : (q15_t) x;
  }

  /**
   * @brief Multiplies 32 X 64 and returns 32 bit result in 2.30 format.
   */

  static __INLINE q63_t mult32x64(
  q63_t x,
  q31_t y)
  {
    return ((((q63_t) (x & 0x00000000FFFFFFFF) * y) >> 32) +
            (((q63_t) (x >> 32) * y)));
  }


    /**
   * @brief Function to Calculates 1/in(reciprocal) value of Q31 Data type.
   */

  static __INLINE uint32_t arm_recip_q31(
  q31_t in,
  q31_t * dst,
  q31_t * pRecipTable)
  {

    int32x2_t out, tempVal;
    int32_t inp, signBit;
	uint32_t i;
    int32x2_t signBits, index, chk, chk1, one, var_in;

    var_in = vdup_n_s32(in);
    chk = vdup_n_s32(0x7FFFFFFF);
    one = vdup_n_s32(1);
    out = vdup_n_s32(0);
    chk1 = vdup_n_s32(INDEX_MASK);

    signBits = vcls_s32(var_in);

    /* Convert input sample to 1.31 format */
    var_in = vshl_s32(var_in, signBits);

    /* calculation of index for initial approximated Val */
    index = vshr_n_s32(var_in, 24);
    index = vand_s32(index, chk1);

    inp = vget_lane_s32(index, 0);

    out = vdup_n_s32(pRecipTable[inp]);

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0u; i < 2u; i++)
    {
      tempVal = vqsub_s32(chk, vqdmulh_s32(var_in, out));
      /*      1.31 with exp 1 */
      out = vqshl_n_s32(vqdmulh_s32(out, tempVal), 1);
    }

    /* write output */
    *dst = vget_lane_s32(out, 0);

    signBits = vqadd_s32(signBits, one);
    signBit = vget_lane_s32(signBits, 0);

    /* return num of signbits of out = 1/in value */
    return (signBit);

  }

  /**
   * @brief Function to Calculates 1/in(reciprocal) value of int32x2_t Data type.
   */

  static __INLINE int32x2_t arm_recipD_q31(
  int32x2_t in,
  q31_t * dst,
  q31_t * pRecipTable)
  {

    int32x2_t out, tempVal;
    int32_t inp1, inp2;
	uint32_t i;
    int32x2_t signBits, index, chk, chk1, one;

    chk = vdup_n_s32(0x7FFFFFFF);
    one = vdup_n_s32(1);
    out = vdup_n_s32(0);
    chk1 = vdup_n_s32(INDEX_MASK);

    signBits = vcls_s32(in);

    /* Convert input sample to 1.31 format */
    in = vshl_s32(in, signBits);

    /* calculation of index for initial approximated Val */
    index = vshr_n_s32(in, 24);
    index = vand_s32(index, chk1);

    inp1 = vget_lane_s32(index, 0);
    inp2 = vget_lane_s32(index, 1);

    out = vset_lane_s32(pRecipTable[inp1], out, 0);
    out = vset_lane_s32(pRecipTable[inp2], out, 1);

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0u; i < 2u; i++)
    {
      tempVal = vqsub_s32(chk, vqdmulh_s32(in, out));
      /*      1.31 with exp 1 */
      out = vqshl_n_s32(vqdmulh_s32(out, tempVal), 1);
    }
    /* write output */
    vst1_s32(dst, out);

    signBits = vqadd_s32(signBits, one);

    /* return num of signbits of out = 1/in value */
    return (signBits);

  }
 /**
   * @brief Function to Calculates 1/in(reciprocal) value of int32x4_t Data type.
   */

  static __INLINE int32x4_t arm_recipQ_q31(
  int32x4_t in,
  q31_t * dst,
  q31_t * pRecipTable)
  {

    int32x4_t out, tempVal;
    int32_t  inp[5];
	uint32_t i;
    int32x4_t signBits, index, chk, chk1, one;

    chk = vdupq_n_s32(0x7FFFFFFF);
    one = vdupq_n_s32(1);
    out = vdupq_n_s32(0);
    chk1 = vdupq_n_s32(INDEX_MASK);

    signBits = vclsq_s32(in);

    /* Convert input sample to 1.31 format */
    in = vshlq_s32(in, signBits);

    /* calculation of index for initial approximated Val */
    index = vshrq_n_s32(in, 24);
    index = vandq_s32(index, chk1);

    // inp[0] = vgetq_lane_s32(index, 0);
    // inp[1] = vgetq_lane_s32(index, 1);
    // inp[2] = vgetq_lane_s32(index, 2);
    // inp[3] = vgetq_lane_s32(index, 3);
    vst1q_s32(inp, index);

    out = vsetq_lane_s32(pRecipTable[inp[0]], out, 0);
    out = vsetq_lane_s32(pRecipTable[inp[1]], out, 1);
    out = vsetq_lane_s32(pRecipTable[inp[2]], out, 2);
    out = vsetq_lane_s32(pRecipTable[inp[3]], out, 3);

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0u; i < 2u; i++)
    {
      tempVal = vqsubq_s32(chk, vqdmulhq_s32(in, out));
      /*      1.31 with exp 1 */
      out = vqshlq_n_s32(vqdmulhq_s32(out, tempVal), 1);
    }

    /* write output */
    vst1q_s32(dst, out);

    signBits = vqaddq_s32(signBits, one);

    /* return num of signbits of out = 1/in value */
    return (signBits);

  }

  /**
   * @brief Instance structure for the floating-point Linear Interpolate function.
   */
  typedef struct
  {
    uint32_t nValues;
    float32_t x1;
    float32_t xSpacing;
    float32_t *pYData;          /**< pointer to the table of Y values */
  } arm_linear_interp_instance_f32;

  /**
   * @brief Instance structure for the floating-point bilinear interpolation function.
   */

  typedef struct
  {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    float32_t *pData;   /**< points to the data table. */
  } arm_bilinear_interp_instance_f32;

   /**
   * @brief Instance structure for the Q31 bilinear interpolation function.
   */

  typedef struct
  {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    q31_t *pData;       /**< points to the data table. */
  } arm_bilinear_interp_instance_q31;


  /*
   * @brief C custom defined intrinsic function for M3 and M0 processors
   */

  /**
   * @brief Instance structure for the Q31 FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;         /**< number of filter coefficients in the filter. */
    q31_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;     /**< number of filter coefficients in the filter. */
    float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_f32;



 /**
   * @brief Processing function for the Q31 FIR filter.
   * @param[in] *S points to an instance of the Q31 FIR filter structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */
  void arm_fir_q31(
  const arm_fir_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR filter.
   * @param[in,out] *S points to an instance of the Q31 FIR structure.
   * @param[in] 	numTaps  Number of filter coefficients in the filter.
   * @param[in] 	*pCoeffs points to the filter coefficients.
   * @param[in] 	*pState points to the state buffer.
   * @param[in] 	blockSize number of samples that are processed at a time.
   * @return 		none.
   */
  void arm_fir_init_q31(
  arm_fir_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);

  /**
   * @brief Processing function for the floating-point FIR filter.
   * @param[in] *S points to an instance of the floating-point FIR structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */
  void arm_fir_f32(
  const arm_fir_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point FIR filter.
   * @param[in,out] *S points to an instance of the floating-point FIR filter structure.
   * @param[in] 	numTaps  Number of filter coefficients in the filter.
   * @param[in] 	*pCoeffs points to the filter coefficients.
   * @param[in] 	*pState points to the state buffer.
   * @param[in] 	blockSize number of samples that are processed at a time.
   * @return    	none.
   */
  void arm_fir_init_f32(
  arm_fir_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 Biquad cascade filter.
   */
  typedef struct
  {
    uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    q31_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    q31_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
    uint8_t postShift;       /**< Additional shift, in bits, applied to each output sample. */

  } arm_biquad_casd_df1_inst_q31;

  /**
   * @brief Instance structure for the floating-point Biquad cascade filter.
   */
  typedef struct
  {
    uint32_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;          /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    float32_t *pCoeffs;         /**< Points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_casd_df1_inst_f32;


  /**
   * @brief Processing function for the Q31 Biquad cascade filter of single channel
   * @param[in]  *S         points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  *pSrc      points to the block of input data.
   * @param[out] *pDst      points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   * @return     none.
   */

  void arm_biquad_cascade_df1_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

    /**
   * @brief Processing function for the Q31 Biquad cascade filter of two channels
   * @param[in]  *S         points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  *pSrc      points to the block of input data.
   * @param[out] *pDst      points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   * @return     none.
   */

  void arm_biquad_cascade_df1_q31_2ch_simd(
  const arm_biquad_casd_df1_inst_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 Biquad cascade filter.
   * @param[in,out] *S           points to an instance of the Q31 Biquad cascade structure.
   * @param[in]     numStages      number of 2nd order stages in the filter.
   * @param[in]     *pCoeffs     points to the filter coefficients.
   * @param[in]     *pState      points to the state buffer.
   * @param[in]     postShift    Shift to be applied to the output. Varies according to the coefficients format
   * @param[in]     numChannels  Number of channels to process.
   * @return        none
   */

  void arm_biquad_cascade_df1_init_q31(
  arm_biquad_casd_df1_inst_q31 * S,
  uint8_t numStages,
  q31_t * pCoeffs,
  q31_t * pState,
  int8_t postShift,
  uint32_t numChannels);

  /**
   * @brief Processing function for the floating-point Biquad cascade filter for single channel.
   * @param[in]  *S         points to an instance of the floating-point Biquad cascade structure.
   * @param[in]  *pSrc      points to the block of input data.
   * @param[out] *pDst      points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   * @return     none.
   */

  void arm_biquad_cascade_df1_f32(
  const arm_biquad_casd_df1_inst_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

   /**
   * @brief Processing function for the floating-point Biquad cascade filter for two channels.
   * @param[in]  *S         points to an instance of the floating-point Biquad cascade structure.
   * @param[in]  *pSrc      points to the block of input data.
   * @param[out] *pDst      points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   * @return     none.
   */

  void arm_biquad_cascade_df1_f32_2ch_simd(
  const arm_biquad_casd_df1_inst_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point Biquad cascade filter.
   * @param[in,out] *S           points to an instance of the floating-point Biquad cascade structure.
   * @param[in]     numStages    number of 2nd order stages in the filter.
   * @param[in]     *pCoeffs     points to the filter coefficients.
   * @param[in]     *pState      points to the state buffer.
   * @param[in]     numChannels  Number of channels to process.
   * @return        none
   */

  void arm_biquad_cascade_df1_init_f32(
  arm_biquad_casd_df1_inst_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t numChannels);


 /**
   * @brief Q31 vector multiplication.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_mult_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Floating-point vector multiplication.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_mult_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */

  typedef struct
  {
    uint16_t fftLen;                   /**< length of the FFT. */
    uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    float32_t *pTwiddle;               /**< points to the twiddle factor table. */
    uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
    float32_t onebyfftLen;             /**< value of 1/fftLen. */
  } arm_cfft_radix4_instance_f32;

  /**
   * @brief Processing function for the floating-point CFFT/CIFFT.
   * @param[in]      *S    points to an instance of the floating-point CFFT/CIFFT structure.
   * @param[in, out] *pSrc points to the complex data buffer. Processing occurs in-place.
   * @return none.
   */

  void arm_cfft_radix4_f32(
  const arm_cfft_radix4_instance_f32 * S,
  float32_t * pSrc);

  /**
   * @brief  Initialization function for the floating-point CFFT/CIFFT.
   * @param[in,out] *S             points to an instance of the floating-point CFFT/CIFFT structure.
   * @param[in]     fftLen         length of the FFT.
   * @param[in]     ifftFlag       flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform.
   * @param[in]     bitReverseFlag flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>fftLen</code> is not a supported value.
   */

  arm_status arm_cfft_radix4_init_f32(
  arm_cfft_radix4_instance_f32 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);


  /*----------------------------------------------------------------------
   *		Internal functions prototypes FFT function
   ----------------------------------------------------------------------*/

  /**
   * @brief  Core function for the floating-point CFFT butterfly process.
   * @param[in, out] *pSrc            points to the in-place buffer of floating-point data type.
   * @param[in]      fftLen           length of the FFT.
   * @param[in]      *pCoef           points to the twiddle coefficient buffer.
   * @return none.
   */

  void arm_radix4_butterfly_f32(
  float32_t * pSrc,
  uint16_t fftLen,
  float32_t * pCoef);

  /**
   * @brief  Core function for the floating-point CIFFT butterfly process.
   * @param[in, out] *pSrc            points to the in-place buffer of floating-point data type.
   * @param[in]      fftLen           length of the FFT.
   * @param[in]      *pCoef           points to twiddle coefficient buffer.
   * @param[in]      onebyfftLen      value of 1/fftLen.
   * @return none.
   */

  void arm_radix4_butterfly_inverse_f32(
  float32_t * pSrc,
  uint16_t fftLen,
  float32_t * pCoef,
  float32_t onebyfftLen);

  /**
   * @brief  In-place bit reversal function.
   * @param[in, out] *pSrc        points to the in-place buffer of floating-point data type.
   * @param[in]      fftSize      length of the FFT.
   * @param[in]      bitRevFactor bit reversal modifier that supports different size FFTs with the same bit reversal table.
   * @param[in]      *pBitRevTab  points to the bit reversal table.
   * @return none.
   */

  void arm_bitreversal_f32(
  float32_t * pSrc,
  uint16_t fftSize,
  uint16_t bitRevFactor,
  uint16_t * pBitRevTab);


  /**
   * @brief Instance structure for the Q31 CFFT/CIFFT function.
   */

  typedef struct
  {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    q31_t *pTwiddle;                 /**< points to the twiddle factor table. */
    uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } arm_cfft_radix4_instance_q31;

  /**
   * @brief Processing function for the Q31 CFFT/CIFFT.
   * @param[in]      *S    points to an instance of the Q31 CFFT/CIFFT structure.
   * @param[in, out] *pSrc points to the complex data buffer. Processing occurs in-place.
   * @return none.
   */

  void arm_cfft_radix4_q31(
  const arm_cfft_radix4_instance_q31 * S,
  q31_t * pSrc);

  /**
   * @brief  Initialization function for the Q31 CFFT/CIFFT.
   * @param[in,out] *S             points to an instance of the Q31 CFFT/CIFFT structure.
   * @param[in]     fftLen         length of the FFT.
   * @param[in]     ifftFlag       flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform.
   * @param[in]     bitReverseFlag flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output.
   * @return        arm_status     function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>fftLen</code> is not a supported value.
   */

  arm_status arm_cfft_radix4_init_q31(
  arm_cfft_radix4_instance_q31 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  /**
   * @brief  Core function for the Q31 CFFT butterfly process.
   * @param[in, out] *pSrc            points to the in-place buffer of Q31 data type.
   * @param[in]      fftLen           length of the FFT.
   * @param[in]      *pCoef           points to twiddle coefficient buffer.
   * @return none.
   */

  void arm_radix4_butterfly_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  q31_t * pCoef);

  /**
   * @brief  Core function for the Q31 CIFFT butterfly process.
   * @param[in, out] *pSrc            points to the in-place buffer of Q31 data type.
   * @param[in]      fftLen           length of the FFT.
   * @param[in]      *pCoef           points to twiddle coefficient buffer.
   * @return none.
   */

  void arm_radix4_butterfly_inverse_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  q31_t * pCoef);
  /**
   * @brief  In-place bit reversal function.
   * @param[in, out] *pSrc        points to the in-place buffer of Q31 data type.
   * @param[in]      fftLen       length of the FFT.
   * @param[in]      bitRevFactor bit reversal modifier that supports different size FFTs with the same bit reversal table
   * @param[in]      *pBitRevTab  points to bit reversal table.
   * @return none.
   */

  void arm_bitreversal_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  uint16_t bitRevFactor,
  uint16_t * pBitRevTab);


  /**
   * @brief Instance structure for the floating-point RFFT/RIFFT function.
   */

  typedef struct
  {
    uint32_t fftLenReal;                        /**< length of the real FFT. */
    uint16_t fftLenBy2;                         /**< length of the complex FFT. */
    uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;                 /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    float32_t *pTwiddleAReal;                   /**< points to the real twiddle factor table. */
    float32_t *pTwiddleBReal;                   /**< points to the imag twiddle factor table. */
    arm_cfft_radix4_instance_f32 *pCfft;        /**< points to the complex FFT instance. */
  } arm_rfft_instance_f32;

  /**
   * @brief  Initialization function for the floating-point RFFT/RIFFT.
   * @param[in,out] *S             points to an instance of the floating-point RFFT/RIFFT structure.
   * @param[in,out] *S_CFFT        points to an instance of the floating-point CFFT/CIFFT structure.
   * @param[in]     fftLenReal     length of the FFT.
   * @param[in]     ifftFlagR      flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform.
   * @param[in]     bitReverseFlag flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output.
   * @return		The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>fftLenReal</code> is not a supported value.
   */

  arm_status arm_rfft_init_f32(
  arm_rfft_instance_f32 * S,
  arm_cfft_radix4_instance_f32 * S_CFFT,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  /**
   * @brief Processing function for the floating-point RFFT/RIFFT.
   * @param[in]  *S    points to an instance of the floating-point RFFT/RIFFT structure.
   * @param[in]  *pSrc points to the input buffer.
   * @param[out] *pDst points to the output buffer.
   * @return none.
   */

  void arm_rfft_f32(
  const arm_rfft_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst);

  /**
   * @brief Instance structure for the Q31 RFFT/RIFFT function.
   */

  typedef struct
  {
    uint32_t fftLenReal;                        /**< length of the real FFT. */
    uint32_t fftLenBy2;                         /**< length of the complex FFT. */
    uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;                 /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    q31_t *pTwiddleAReal;                       /**< points to the real twiddle factor table. */
    q31_t *pTwiddleBReal;                       /**< points to the imag twiddle factor table. */
    arm_cfft_radix4_instance_q31 *pCfft;        /**< points to the complex FFT instance. */
  } arm_rfft_instance_q31;

  /**
   * @brief Processing function for the Q31 RFFT/RIFFT.
   * @param[in]  *S    points to an instance of the Q31 RFFT/RIFFT structure.
   * @param[in]  *pSrc points to the input buffer.
   * @param[out] *pDst points to the output buffer.
   * @return none.
   */

  void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst);

  /**
   * @brief  Initialization function for the Q31 RFFT/RIFFT.
   * @param[in, out] *S             points to an instance of the Q31 RFFT/RIFFT structure.
   * @param[in, out] *S_CFFT        points to an instance of the Q31 CFFT/CIFFT structure.
   * @param[in]      fftLenReal     length of the FFT.
   * @param[in]      ifftFlagR      flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform.
   * @param[in]      bitReverseFlag flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output.
   * @return		The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>fftLenReal</code> is not a supported value.
   */

  arm_status arm_rfft_init_q31(
  arm_rfft_instance_q31 * S,
  arm_cfft_radix4_instance_q31 * S_CFFT,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  /**
   * @brief Instance structure for the floating-point DCT4/IDCT4 function.
   */

  typedef struct
  {
    uint16_t N;                         /**< length of the DCT4. */
    uint16_t Nby2;                      /**< half of the length of the DCT4. */
    float32_t normalize;                /**< normalizing factor. */
    float32_t *pTwiddle;                /**< points to the twiddle factor table. */
    float32_t *pCosFactor;              /**< points to the cosFactor table. */
    arm_rfft_instance_f32 *pRfft;        /**< points to the real FFT instance. */
    arm_cfft_radix4_instance_f32 *pCfft; /**< points to the complex FFT instance. */
  } arm_dct4_instance_f32;

  /**
   * @brief  Initialization function for the floating-point DCT4/IDCT4.
   * @param[in,out] *S         points to an instance of floating-point DCT4/IDCT4 structure.
   * @param[in]     *S_RFFT    points to an instance of floating-point RFFT/RIFFT structure.
   * @param[in]     *S_CFFT    points to an instance of floating-point CFFT/CIFFT structure.
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return		arm_status function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>fftLenReal</code> is not a supported transform length.
   */

  arm_status arm_dct4_init_f32(
  arm_dct4_instance_f32 * S,
  arm_rfft_instance_f32 * S_RFFT,
  arm_cfft_radix4_instance_f32 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  float32_t normalize);

  /**
   * @brief Processing function for the floating-point DCT4/IDCT4.
   * @param[in]       *S             points to an instance of the floating-point DCT4/IDCT4 structure.
   * @param[in]       *pState        points to state buffer.
   * @param[in,out]   *pInlineBuffer points to the in-place input and output buffer.
   * @return none.
   */

  void arm_dct4_f32(
  const arm_dct4_instance_f32 * S,
  float32_t * pState,
  float32_t * pInlineBuffer);

  /**
   * @brief Instance structure for the Q31 DCT4/IDCT4 function.
   */

  typedef struct
  {
    uint16_t N;                         /**< length of the DCT4. */
    uint16_t Nby2;                      /**< half of the length of the DCT4. */
    q31_t normalize;                    /**< normalizing factor. */
    q31_t *pTwiddle;                    /**< points to the twiddle factor table. */
    q31_t *pCosFactor;                  /**< points to the cosFactor table. */
    arm_rfft_instance_q31 *pRfft;        /**< points to the real FFT instance. */
    arm_cfft_radix4_instance_q31 *pCfft; /**< points to the complex FFT instance. */
  } arm_dct4_instance_q31;


  /**
   * @brief  Initialization function for the Q31 DCT4/IDCT4.
   * @param[in,out] *S         points to an instance of Q31 DCT4/IDCT4 structure.
   * @param[in]     *S_RFFT    points to an instance of Q31 RFFT/RIFFT structure
   * @param[in]     *S_CFFT    points to an instance of Q31 CFFT/CIFFT structure
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return		arm_status function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>N</code> is not a supported transform length.
   */

  arm_status arm_dct4_init_q31(
  arm_dct4_instance_q31 * S,
  arm_rfft_instance_q31 * S_RFFT,
  arm_cfft_radix4_instance_q31 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  q31_t normalize);

  /**
   * @brief Processing function for the Q31 DCT4/IDCT4.
   * @param[in]       *S             points to an instance of the Q31 DCT4 structure.
   * @param[in]       *pState        points to state buffer.
   * @param[in,out]   *pInlineBuffer points to the in-place input and output buffer.
   * @return none.
   */

  void arm_dct4_q31(
  const arm_dct4_instance_q31 * S,
  q31_t * pState,
  q31_t * pInlineBuffer);

  /**
   * @brief Floating-point vector addition.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_add_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q31 vector addition.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_add_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Floating-point vector subtraction.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_sub_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q31 vector subtraction.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_sub_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Multiplies a floating-point vector by a scalar.
   * @param[in]       *pSrc points to the input vector
   * @param[in]       scale scale factor to be applied
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */

  void arm_scale_f32(
  float32_t * pSrc,
  float32_t scale,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Multiplies a Q31 vector by a scalar.
   * @param[in]       *pSrc points to the input vector
   * @param[in]       scaleFract fractional portion of the scale value
   * @param[in]       shift number of bits to shift the result by
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */

  void arm_scale_q31(
  q31_t * pSrc,
  q31_t scaleFract,
  int8_t shift,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Floating-point vector absolute value.
   * @param[in]       *pSrc points to the input buffer
   * @param[out]      *pDst points to the output buffer
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_abs_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Q31 vector absolute value.
   * @param[in]       *pSrc points to the input buffer
   * @param[out]      *pDst points to the output buffer
   * @param[in]       blockSize number of samples in each vector
   * @return none.
   */

  void arm_abs_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Dot product of floating-point vectors.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[in]       blockSize number of samples in each vector
   * @param[out]      *result output result returned here
   * @return none.
   */

  void arm_dot_prod_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  uint32_t blockSize,
  float32_t * result);


  /**
   * @brief Dot product of Q31 vectors.
   * @param[in]       *pSrcA points to the first input vector
   * @param[in]       *pSrcB points to the second input vector
   * @param[in]       blockSize number of samples in each vector
   * @param[out]      *result output result returned here
   * @return none.
   */

  void arm_dot_prod_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  uint32_t blockSize,
  q63_t * result);


  /**
   * @brief  Shifts the elements of a Q31 vector a specified number of bits.
   * @param[in]  *pSrc points to the input vector
   * @param[in]  shiftBits number of bits to shift.  A positive value shifts left; a negative value shifts right.
   * @param[out]  *pDst points to the output vector
   * @param[in]  blockSize number of samples in the vector
   * @return none.
   */

  void arm_shift_q31(
  q31_t * pSrc,
  int8_t shiftBits,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Adds a constant offset to a floating-point vector.
   * @param[in]  *pSrc points to the input vector
   * @param[in]  offset is the offset to be added
   * @param[out]  *pDst points to the output vector
   * @param[in]  blockSize number of samples in the vector
   * @return none.
   */

  void arm_offset_f32(
  float32_t * pSrc,
  float32_t offset,
  float32_t * pDst,
  uint32_t blockSize);

 /**
   * @brief  Adds a constant offset to a Q31 vector.
   * @param[in]  *pSrc points to the input vector
   * @param[in]  offset is the offset to be added
   * @param[out]  *pDst points to the output vector
   * @param[in]  blockSize number of samples in the vector
   * @return none.
   */

  void arm_offset_q31(
  q31_t * pSrc,
  q31_t offset,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Negates the elements of a floating-point vector.
   * @param[in]  *pSrc points to the input vector
   * @param[out]  *pDst points to the output vector
   * @param[in]  blockSize number of samples in the vector
   * @return none.
   */

  void arm_negate_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Negates the elements of a Q31 vector.
   * @param[in]  *pSrc points to the input vector
   * @param[out]  *pDst points to the output vector
   * @param[in]  blockSize number of samples in the vector
   * @return none.
   */

  void arm_negate_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);
  /**
   * @brief  Copies the elements of a floating-point vector. 
   * @param[in]  *pSrc input pointer
   * @param[out]  *pDst output pointer
   * @param[in]  blockSize number of samples to process
   * @return none.
   */
  void arm_copy_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Copies the elements of a Q31 vector. 
   * @param[in]  *pSrc input pointer
   * @param[out]  *pDst output pointer
   * @param[in]  blockSize number of samples to process
   * @return none.
   */
  void arm_copy_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);
  /**
   * @brief  Fills a constant value into a floating-point vector. 
   * @param[in]  value input value to be filled
   * @param[out]  *pDst output pointer
   * @param[in]  blockSize number of samples to process
   * @return none.
   */
  void arm_fill_f32(
  float32_t value,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a Q31 vector. 
   * @param[in]  value input value to be filled
   * @param[out]  *pDst output pointer
   * @param[in]  blockSize number of samples to process
   * @return none.
   */
  void arm_fill_q31(
  q31_t value,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Convolution of floating-point sequences.
   * @param[in] *pSrcA points to the first input sequence.
   * @param[in] srcALen length of the first input sequence.
   * @param[in] *pSrcB points to the second input sequence.
   * @param[in] srcBLen length of the second input sequence.
   * @param[out] *pDst points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in] *pScratch1 points to the scratch buffer of Length max(srcALen, srcBLen) + min(srcALen, srcBLen)- 1.
   * @param[in] *pScratch2 points to the scratch buffer of Length min(srcALen, srcBLen).
   * @return none.
   */

  void arm_conv_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst,
  float32_t * pScratch1,
  float32_t * pScratch2);


  /**
   * @brief Convolution of Q31 sequences.
   * @param[in] *pSrcA points to the first input sequence.
   * @param[in] srcALen length of the first input sequence.
   * @param[in] *pSrcB points to the second input sequence.
   * @param[in] srcBLen length of the second input sequence.
   * @param[out] *pDst points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in] *pScratch1 points to the scratch buffer of Length max(srcALen, srcBLen) + min(srcALen, srcBLen)- 1.
   * @param[in] *pScratch2 points to the scratch buffer of Length min(srcALen, srcBLen).
   * @return none.
   */

  void arm_conv_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst,
  q31_t * pScratch1,
  q31_t * pScratch2);


  /**
   * @brief Partial convolution of floating-point sequences.
   * @param[in]       *pSrcA points to the first input sequence.
   * @param[in]       srcALen length of the first input sequence.
   * @param[in]       *pSrcB points to the second input sequence.
   * @param[in]       srcBLen length of the second input sequence.
   * @param[out]      *pDst points to the block of output data
   * @param[in]       firstIndex is the first output sample to start with.
   * @param[in]       numPoints is the number of output points to be computed.
   * @param[in]		  *pScratch1 points to the scratch buffer of Length max(srcALen, srcBLen) + min(srcALen, srcBLen)- 1.
   * @param[in]		  *pScratch2 points to the scratch buffer of Length min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */

  arm_status arm_conv_partial_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  float32_t * pScratch1,
  float32_t * pScratch2);

  /**
   * @brief Partial convolution of Q31 sequences.
   * @param[in]       *pSrcA points to the first input sequence.
   * @param[in]       srcALen length of the first input sequence.
   * @param[in]       *pSrcB points to the second input sequence.
   * @param[in]       srcBLen length of the second input sequence.
   * @param[out]      *pDst points to the block of output data
   * @param[in]       firstIndex is the first output sample to start with.
   * @param[in]       numPoints is the number of output points to be computed.
   * @param[in]		  *pScratch1 points to the scratch buffer of Length max(srcALen, srcBLen) + min(srcALen, srcBLen)- 1.
   * @param[in]		  *pScratch2 points to the scratch buffer of Length min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */

  arm_status arm_conv_partial_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  q31_t * pScratch1,
  q31_t * pScratch2);



  /**
   * @brief Instance structure for the Q31 FIR decimator.
   */

  typedef struct
  {
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    q31_t *pCoeffs;              /**< points to the coefficient array. The array is of length numTaps.*/
    q31_t *pState;               /**< points to the state variable array. The array is of length numTaps+blockSize-1. */

  } arm_fir_decimate_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR decimator.
   */

  typedef struct
  {
    uint8_t M;                          /**< decimation factor. */
    uint16_t numTaps;                   /**< number of coefficients in the filter. */
    float32_t *pCoeffs;                  /**< points to the coefficient array. The array is of length numTaps.*/
    float32_t *pState;                   /**< points to the state variable array. The array is of length numTaps+blockSize-1. */

  } arm_fir_decimate_instance_f32;



  /**
   * @brief Processing function for the floating-point FIR decimator.
   * @param[in] *S points to an instance of the floating-point FIR decimator structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data
   * @param[in] blockSize number of input samples to process per call.
   * @return none
   */

  void arm_fir_decimate_f32(
  const arm_fir_decimate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point FIR decimator.
   * @param[in,out] *S points to an instance of the floating-point FIR decimator structure.
   * @param[in] numTaps  number of coefficients in the filter.
   * @param[in] M  decimation factor.
   * @param[in] *pCoeffs points to the filter coefficients.
   * @param[in] *pState points to the state buffer.
   * @param[in] blockSize number of input samples to process per call.
   * @return    The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */

  arm_status arm_fir_decimate_init_f32(
  arm_fir_decimate_instance_f32 * S,
  uint16_t numTaps,
  uint8_t M,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR decimator.
   * @param[in] *S points to an instance of the Q31 FIR decimator structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data
   * @param[in] blockSize number of input samples to process per call.
   * @return none
   */

  void arm_fir_decimate_q31(
  const arm_fir_decimate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR decimator.
   * @param[in,out] *S points to an instance of the Q31 FIR decimator structure.
   * @param[in] numTaps  number of coefficients in the filter.
   * @param[in] M  decimation factor.
   * @param[in] *pCoeffs points to the filter coefficients.
   * @param[in] *pState points to the state buffer.
   * @param[in] blockSize number of input samples to process per call.
   * @return    The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */

  arm_status arm_fir_decimate_init_q31(
  arm_fir_decimate_instance_q31 * S,
  uint16_t numTaps,
  uint8_t M,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);

  /**
   * @brief Instance structure for the Q31 FIR interpolator.
   */

  typedef struct
  {
    uint8_t L;                      /**< upsample factor. */
    uint16_t phaseLength;           /**< length of each polyphase filter component. */
    q31_t *pCoeffs;                  /**< points to the coefficient array. The array is of length L*phaseLength. */
    q31_t *pState;                   /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
  } arm_fir_interpolate_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR interpolator.
   */

  typedef struct
  {
    uint8_t L;                     /**< upsample factor. */
    uint16_t phaseLength;          /**< length of each polyphase filter component. */
    float32_t *pCoeffs;             /**< points to the coefficient array. The array is of length L*phaseLength. */
    float32_t *pState;              /**< points to the state variable array. The array is of length phaseLength+numTaps-1. */
  } arm_fir_interpolate_instance_f32;


  /**
   * @brief Processing function for the Q31 FIR interpolator.
   * @param[in] *S        points to an instance of the Q15 FIR interpolator structure.
   * @param[in] *pSrc     points to the block of input data.
   * @param[out] *pDst    points to the block of output data.
   * @param[in] blockSize number of input samples to process per call.
   * @return none.
   */

  void arm_fir_interpolate_q31(
  const arm_fir_interpolate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q31 FIR interpolator.
   * @param[in,out] *S        points to an instance of the Q31 FIR interpolator structure.
   * @param[in]     L         upsample factor.
   * @param[in]     numTaps   number of filter coefficients in the filter.
   * @param[in]     *pCoeffs  points to the filter coefficient buffer.
   * @param[in]     *pState   points to the state buffer.
   * @param[in]     blockSize number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */

  arm_status arm_fir_interpolate_init_q31(
  arm_fir_interpolate_instance_q31 * S,
  uint8_t L,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point FIR interpolator.
   * @param[in] *S        points to an instance of the floating-point FIR interpolator structure.
   * @param[in] *pSrc     points to the block of input data.
   * @param[out] *pDst    points to the block of output data.
   * @param[in] blockSize number of input samples to process per call.
   * @return none.
   */

  void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point FIR interpolator.
   * @param[in,out] *S        points to an instance of the floating-point FIR interpolator structure.
   * @param[in]     L         upsample factor.
   * @param[in]     numTaps   number of filter coefficients in the filter.
   * @param[in]     *pCoeffs  points to the filter coefficient buffer.
   * @param[in]     *pState   points to the state buffer.
   * @param[in]     blockSize number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */

  arm_status arm_fir_interpolate_init_f32(
  arm_fir_interpolate_instance_f32 * S,
  uint8_t L,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */

  typedef struct
  {
    uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_df2T_instance_f32;


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter for one channel.
   * @param[in]  *S        points to an instance of the filter data structure.
   * @param[in]  *pSrc     points to the block of input data.
   * @param[out] *pDst     points to the block of output data
   * @param[in]  blockSize number of samples to process.
   * @return none.
   */

  void arm_biquad_cascade_df2T_f32(
  const arm_biquad_cascade_df2T_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

   /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter
   * of two channels.
   * @param[in]  *S        points to an instance of the filter data structure.
   * @param[in]  *pSrc     points to the block of input data.
   * @param[out] *pDst     points to the block of output data
   * @param[in]  blockSize number of samples to process.
   * @return none.
   */

  void arm_biquad_cascade_df2T_f32_2ch_simd(
  const arm_biquad_cascade_df2T_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] *S           points to an instance of the filter data structure.
   * @param[in]     numStages    number of 2nd order stages in the filter.
   * @param[in]     *pCoeffs     points to the filter coefficients.
   * @param[in]     *pState      points to the state buffer.
   * @param[in]     numChannels  Number of channels to process.
   * @return        none
   */

  void arm_biquad_cascade_df2T_init_f32(
  arm_biquad_cascade_df2T_instance_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t numChannels);


  /**
   * @brief Instance structure for the Q31 FIR lattice filter.
   */

  typedef struct
  {
    uint16_t numStages;                          /**< number of filter stages. */
    q31_t *pState;                               /**< points to the state variable array. The array is of length numStages. */
    q31_t *pCoeffs;                              /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR lattice filter.
   */

  typedef struct
  {
    uint16_t numStages;                  /**< number of filter stages. */
    float32_t *pState;                   /**< points to the state variable array. The array is of length numStages. */
    float32_t *pCoeffs;                  /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_f32;



  /**
   * @brief Initialization function for the Q31 FIR lattice filter.
   * @param[in] *S points to an instance of the Q31 FIR lattice structure.
   * @param[in] numStages  number of filter stages.
   * @param[in] *pCoeffs points to the coefficient buffer.  The array is of length numStages.
   * @param[in] *pState points to the state buffer.   The array is of length numStages.
   * @return none.
   */

  void arm_fir_lattice_init_q31(
  arm_fir_lattice_instance_q31 * S,
  uint16_t numStages,
  q31_t * pCoeffs,
  q31_t * pState);


  /**
   * @brief Processing function for the Q31 FIR lattice filter.
   * @param[in]  *S        points to an instance of the Q31 FIR lattice structure.
   * @param[in]  *pSrc     points to the block of input data.
   * @param[out] *pDst     points to the block of output data
   * @param[in]  blockSize number of samples to process.
   * @return none.
   */

  void arm_fir_lattice_q31(
  const arm_fir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

/**
 * @brief Initialization function for the floating-point FIR lattice filter.
 * @param[in] *S points to an instance of the floating-point FIR lattice structure.
 * @param[in] numStages  number of filter stages.
 * @param[in] *pCoeffs points to the coefficient buffer.  The array is of length numStages.
 * @param[in] *pState points to the state buffer.  The array is of length numStages.
 * @return none.
 */

  void arm_fir_lattice_init_f32(
  arm_fir_lattice_instance_f32 * S,
  uint16_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);

  /**
   * @brief Processing function for the floating-point FIR lattice filter.
   * @param[in]  *S        points to an instance of the floating-point FIR lattice structure.
   * @param[in]  *pSrc     points to the block of input data.
   * @param[out] *pDst     points to the block of output data
   * @param[in]  blockSize number of samples to process.
   * @return none.
   */

  void arm_fir_lattice_f32(
  const arm_fir_lattice_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 IIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                         /**< number of stages in the filter. */
    q31_t *pState;                              /**< points to the state variable array. The array is of length numStages+blockSize. */
    q31_t *pkCoeffs;                            /**< points to the reflection coefficient array. The array is of length numStages. */
    q31_t *pvCoeffs;                            /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point IIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                         /**< number of stages in the filter. */
    float32_t *pState;                          /**< points to the state variable array. The array is of length numStages+blockSize. */
    float32_t *pkCoeffs;                        /**< points to the reflection coefficient array. The array is of length numStages. */
    float32_t *pvCoeffs;                        /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_f32;

  /**
   * @brief Processing function for the floating-point IIR lattice filter.
   * @param[in] *S points to an instance of the floating-point IIR lattice structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_iir_lattice_f32(
  const arm_iir_lattice_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Initialization function for the floating-point IIR lattice filter for numChannels.
   * @param[in] *S points to an instance of the floating-point IIR lattice structure.
   * @param[in] numStages number of stages in the filter.
   * @param[in] *pkCoeffs points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] *pvCoeffs points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] *pState points to the state buffer.  The array is of length numStages+blockSize-1.
   * @param[in] blockSize number of samples to process.
   * @param[in] numChannels number of channels to process.
   * @return none.
   */

  void arm_iir_lattice_init_f32(
  arm_iir_lattice_instance_f32 * S,
  uint16_t numStages,
  float32_t * pkCoeffs,
  float32_t * pvCoeffs,
  float32_t * pState,
  uint32_t blockSize,
  uint32_t numChannels);


  /**
   * @brief Processing function for the Q31 IIR lattice filter.
   * @param[in] *S points to an instance of the Q31 IIR lattice structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_iir_lattice_q31(
  const arm_iir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Initialization function for the Q31 IIR lattice filter for numChannels.
   * @param[in] *S points to an instance of the Q31 IIR lattice structure.
   * @param[in] numStages number of stages in the filter.
   * @param[in] *pkCoeffs points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] *pvCoeffs points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] *pState points to the state buffer.  The array is of length numStages+blockSize.
   * @param[in] blockSize number of samples to process.
   * @param[in] numChannels number of channels to process.
   * @return none.
   */

  void arm_iir_lattice_init_q31(
  arm_iir_lattice_instance_q31 * S,
  uint16_t numStages,
  q31_t * pkCoeffs,
  q31_t * pvCoeffs,
  q31_t * pState,
  uint32_t blockSize,
  uint32_t numChannels);


  /**
   * @brief Two channel processing function for the floating-point IIR lattice filter.
   * @param[in] *S points to an instance of the floating-point IIR lattice structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_iir_lattice_f32_2ch_simd(
  const arm_iir_lattice_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Two channel processing function for the Q31 IIR lattice filter.
   * @param[in] *S points to an instance of the Q31 IIR lattice structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[out] *pDst points to the block of output data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_iir_lattice_q31_2ch_simd(
  const arm_iir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);



  /**
   * @brief Instance structure for the floating-point LMS filter.
   */

  typedef struct
  {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    float32_t *pState;   /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;  /**< points to the coefficient array. The array is of length numTaps. */
    float32_t mu;        /**< step size that controls filter coefficient updates. */
  } arm_lms_instance_f32;

  /**
   * @brief Processing function for floating-point LMS filter.
   * @param[in]  *S points to an instance of the floating-point LMS filter structure.
   * @param[in]  *pSrc points to the block of input data.
   * @param[in]  *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in]  blockSize number of samples to process.
   * @return     none.
   */

  void arm_lms_f32(
  const arm_lms_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);

  /**
   * @brief Initialization function for floating-point LMS filter for numChannels.
   * @param[in] *S points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps  number of filter coefficients.
   * @param[in] *pCoeffs points to the coefficient buffer.
   * @param[in] *pState points to state buffer.
   * @param[in] mu step size that controls filter coefficient updates.
   * @param[in] blockSize number of samples to process.
   * @param[in] numChannels number of channels to process.
   * @return none.
   */

  void arm_lms_init_f32(
  arm_lms_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  float32_t mu,
  uint32_t blockSize,
  uint32_t numChannels);


  /**
   * @brief Two channel processing function for floating-point LMS filter.
   * @param[in]  *S points to an instance of the floating-point LMS filter structure.
   * @param[in]  *pSrc points to the block of input data.
   * @param[in]  *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in]  blockSize number of samples to process.
   * @return     none.
   */

  void arm_lms_f32_2ch_simd(
  const arm_lms_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 LMS filter.
   */

  typedef struct
  {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    q31_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
    q31_t mu;            /**< step size that controls filter coefficient updates. */
    uint32_t postShift;  /**< bit shift applied to coefficients. */

  } arm_lms_instance_q31;

  /**
   * @brief Processing function for Q31 LMS filter.
   * @param[in]  *S points to an instance of the Q15 LMS filter structure.
   * @param[in]  *pSrc points to the block of input data.
   * @param[in]  *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in]  blockSize number of samples to process.
   * @return     none.
   */

  void arm_lms_q31(
  const arm_lms_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);

  /**
   * @brief Initialization function for Q31 LMS filter for numChannels.
   * @param[in] *S points to an instance of the Q31 LMS filter structure.
   * @param[in] numTaps  number of filter coefficients.
   * @param[in] *pCoeffs points to coefficient buffer.
   * @param[in] *pState points to state buffer.
   * @param[in] mu step size that controls filter coefficient updates.
   * @param[in] blockSize number of samples to process.
   * @param[in] numChannels number of channels to process.
   * @param[in] postShift bit shift applied to coefficients.
   * @return none.
   */

  void arm_lms_init_q31(
  arm_lms_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  q31_t mu,
  uint32_t blockSize,
  uint32_t numChannels,
  uint32_t postShift);

  /**
   * @brief Two channel processing function for Q31 LMS filter.
   * @param[in]  *S points to an instance of the Q15 LMS filter structure.
   * @param[in]  *pSrc points to the block of input data.
   * @param[in]  *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in]  blockSize number of samples to process.
   * @return     none.
   */

  void arm_lms_q31_2ch_simd(
  const arm_lms_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);

  /**
   * @brief Instance structure for the floating-point normalized LMS filter.
   */

  typedef struct
  {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
    float32_t mu;        /**< step size that control filter coefficient updates. */
    float32_t energy;    /**< saves previous frame energy. */
    float32_t x0;        /**< saves previous input sample. */
  } arm_lms_norm_instance_f32;


   /**
   * @brief Instance structure for two channel floating-point normalized LMS filter.
   */

  typedef struct
  {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
    float32_t mu;        /**< step size that control filter coefficient updates. */
    float32_t energy[2];    /**< saves previous frame energy. */
    float32_t x0[2];        /**< saves previous input sample. */
  } arm_lms_norm_instance_f32_2ch_simd;

 /**
   * @brief Processing function for floating-point normalized LMS filter.
   * @param[in] *S points to an instance of the floating-point normalized LMS filter structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[in] *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_lms_norm_f32(
  arm_lms_norm_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);

   /**
   * @brief Initialization function for floating-point normalized LMS filter.
   * @param[in] *S points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps  number of filter coefficients.
   * @param[in] *pCoeffs points to coefficient buffer.
   * @param[in] *pState points to state buffer.
   * @param[in] mu step size that controls filter coefficient updates.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_lms_norm_init_f32(
  arm_lms_norm_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  float32_t mu,
  uint32_t blockSize);


   /**
   * @brief Initialization function for floating-point normalized LMS filter for 2 channels.  
   * @param[in] *S points to an instance of the floating-point LMS filter 2 channel structure.  
   * @param[in] numTaps  number of filter coefficients.  
   * @param[in] *pCoeffs points to coefficient buffer.  
   * @param[in] *pState points to state buffer.  
   * @param[in] mu step size that controls filter coefficient updates.  
   * @param[in] blockSize number of samples to process.  
   * @return none.  
   */

  void arm_lms_norm_init_f32_2ch_simd(
  arm_lms_norm_instance_f32_2ch_simd * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  float32_t mu,
  uint32_t blockSize);

  /**
   * @brief Two channel processing function for floating-point normalized LMS filter.
   * @param[in] *S points to an instance of the floating-point normalized LMS filter structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[in] *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_lms_norm_f32_2ch_simd(
  arm_lms_norm_instance_f32_2ch_simd * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);

  /**
   * @brief Instance structure for the Q31 normalized LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    q31_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
    q31_t mu;             /**< step size that controls filter coefficient updates. */
    uint8_t postShift;    /**< bit shift applied to coefficients. */
    q31_t *recipTable;    /**< points to the reciprocal initial value table. */
    q31_t energy;         /**< saves previous frame energy. */
    q31_t x0;             /**< saves previous input sample. */
  } arm_lms_norm_instance_q31;

  /**
   * @brief Processing function for Q31 normalized LMS filter.
   * @param[in] *S points to an instance of the Q31 normalized LMS filter structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[in] *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_lms_norm_q31(
  arm_lms_norm_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);

  /**
   * @brief Initialization function for Q31 normalized LMS filter.
   * @param[in] *S points to an instance of the Q31 normalized LMS filter structure.
   * @param[in] numTaps  number of filter coefficients.
   * @param[in] *pCoeffs points to coefficient buffer.
   * @param[in] *pState points to state buffer.
   * @param[in] mu step size that controls filter coefficient updates.
   * @param[in] blockSize number of samples to process.
   * @param[in] postShift bit shift applied to coefficients.
   * @return none.
   */

  void arm_lms_norm_init_q31(
  arm_lms_norm_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  q31_t mu,
  uint32_t blockSize,
  uint8_t postShift);

   /**
   * @brief Instance structure for two channel Q31 normalized LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    q31_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
    q31_t mu;             /**< step size that controls filter coefficient updates. */
    uint8_t postShift;    /**< bit shift applied to coefficients. */
    q31_t *recipTable;    /**< points to the reciprocal initial value table. */
    q31_t energy[2];         /**< saves previous frame energy. */
    q31_t x0[2];             /**< saves previous input sample. */
  } arm_lms_norm_instance_q31_2ch_simd;

  /**
   * @brief Initialization function for Q31 normalized LMS filter for 2 channels.  
   * @param[in] *S points to an instance of the Q31 normalized LMS filter 2 channel structure.  
   * @param[in] numTaps  number of filter coefficients.  
   * @param[in] *pCoeffs points to coefficient buffer.  
   * @param[in] *pState points to state buffer.  
   * @param[in] mu step size that controls filter coefficient updates.  
   * @param[in] blockSize number of samples to process.  
   * @param[in] postShift bit shift applied to coefficients.  
   * @return none.  
   */

  void arm_lms_norm_init_q31_2ch_simd(
  arm_lms_norm_instance_q31_2ch_simd * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  q31_t mu,
  uint32_t blockSize,
  uint8_t postShift);

  /**
   * @brief Two channel processing function for Q31 normalized LMS filter.
   * @param[in] *S points to an instance of the Q31 normalized LMS filter structure.
   * @param[in] *pSrc points to the block of input data.
   * @param[in] *pRef points to the block of reference data.
   * @param[out] *pOut points to the block of output data.
   * @param[out] *pErr points to the block of error data.
   * @param[in] blockSize number of samples to process.
   * @return none.
   */

  void arm_lms_norm_q31_2ch_simd(
  arm_lms_norm_instance_q31_2ch_simd * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);


 /**
   * @brief Correlation of floating-point sequences.
   * @param[in] *pSrcA points to the first input sequence.
   * @param[in] srcALen length of the first input sequence.
   * @param[in] *pSrcB points to the second input sequence.
   * @param[in] srcBLen length of the second input sequence.
   * @param[out] *pDst points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   * @param[out] *pScratch points to the scratch buffer of Length max(srcALen, srcBLen) + 2 * (min(srcALen, srcBLen)- 1).
   * @return none.
   */

  void arm_correlate_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst,
  float32_t * pScratch);


  /**
   * @brief Correlate Q31 sequences
   * @param[in] *pSrcA points to the first input sequence.
   * @param[in] srcALen length of the first input sequence.
   * @param[in] *pSrcB points to the second input sequence.
   * @param[in] srcBLen length of the second input sequence.
   * @param[out] *pDst points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   * @param[out] *pScratch points to the scratch buffer of Length max(srcALen, srcBLen) + 2 * (min(srcALen, srcBLen)- 1).
   * @return none.
   */

  void arm_correlate_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst,
  q31_t * pScratch);


  /**
   * @brief Instance structure for the floating-point sparse FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    float32_t *pState;            /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    float32_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_f32;

  /**
   * @brief Instance structure for the Q31 sparse FIR filter.
   */

  typedef struct
  {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    q31_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    q31_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q31;


  /**
   * @brief Processing function for the floating-point sparse FIR filter.
   * @param[in]  *S          points to an instance of the floating-point sparse FIR structure.
   * @param[in]  *pSrc       points to the block of input data.
   * @param[out] *pDst       points to the block of output data
   * @param[in]  *pScratchIn points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   * @return none.
   */

  void arm_fir_sparse_f32(
  arm_fir_sparse_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  float32_t * pScratchIn,
  uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point sparse FIR filter.
   * @param[in,out] *S         points to an instance of the floating-point sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     *pCoeffs   points to the array of filter coefficients.
   * @param[in]     *pState    points to the state buffer.
   * @param[in]     *pTapDelay points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   * @return none
   */

  void arm_fir_sparse_init_f32(
  arm_fir_sparse_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 sparse FIR filter.
   * @param[in]  *S          points to an instance of the Q31 sparse FIR structure.
   * @param[in]  *pSrc       points to the block of input data.
   * @param[out] *pDst       points to the block of output data
   * @param[in]  *pScratchIn points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   * @return none.
   */

  void arm_fir_sparse_q31(
  arm_fir_sparse_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  q31_t * pScratchIn,
  uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q31 sparse FIR filter.
   * @param[in,out] *S         points to an instance of the Q31 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     *pCoeffs   points to the array of filter coefficients.
   * @param[in]     *pState    points to the state buffer.
   * @param[in]     *pTapDelay points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   * @return none
   */

  void arm_fir_sparse_init_q31(
  arm_fir_sparse_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);


  /**
   * @brief  Floating-point complex conjugate.
   * @param[in]  *pSrc points to the input vector
   * @param[out]  *pDst points to the output vector
   * @param[in]  numSamples number of complex samples in each vector
   * @return none.
   */

  void arm_cmplx_conj_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);

  /**
   * @brief  Q31 complex conjugate.
   * @param[in]  *pSrc points to the input vector
   * @param[out]  *pDst points to the output vector
   * @param[in]  numSamples number of complex samples in each vector
   * @return none.
   */

  void arm_cmplx_conj_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);


  /**
   * @brief  Floating-point complex magnitude squared
   * @param[in]  *pSrc points to the complex input vector
   * @param[out]  *pDst points to the real output vector
   * @param[in]  numSamples number of complex samples in the input vector
   * @return none.
   */

  void arm_cmplx_mag_squared_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);

  /**
   * @brief  Q31 complex magnitude squared
   * @param[in]  *pSrc points to the complex input vector
   * @param[out]  *pDst points to the real output vector
   * @param[in]  numSamples number of complex samples in the input vector
   * @return none.
   */

  void arm_cmplx_mag_squared_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);

  /**
   * @brief  Converts the elements of the Q7 vector to Q31 vector.
   * @param[in]  *pSrc     input pointer
   * @param[out]  *pDst    output pointer
   * @param[in]  blockSize number of samples to process
   * @return none.
   */
  void arm_q7_to_q31(
  q7_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q7 vector to Q15 vector.
   * @param[in]  *pSrc     input pointer
   * @param[out] *pDst     output pointer
   * @param[in]  blockSize number of samples to process
   * @return none.
   */
  void arm_q7_to_q15(
  q7_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q7 vector to floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[out]  *pDst is output pointer
   * @param[in]  blockSize is the number of samples to process
   * @return none.
   */
  void arm_q7_to_float(
  q7_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q31 vector to floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[out]  *pDst is output pointer
   * @param[in]  blockSize is the number of samples to process
   * @return none.
   */
  void arm_q31_to_float(
  q31_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);



  /**
   * @brief  Fast approximation to the trigonometric sine function for floating-point data.
   * @param[in]       *pSrc points to the input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */

  void arm_sin_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Fast approximation to the trigonometric sine function for Q31 data.
   * @param[in]       *pSrc points to the input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */

  void arm_sin_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Fast approximation to the trigonometric cosine function for floating-point data.
   * @param[in]       *pSrc points to the input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */

  void arm_cos_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Fast approximation to the trigonometric cosine function for Q31 data.
   * @param[in]       *pSrc points to the input vector
   * @param[out]      *pDst points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */

  void arm_cos_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


 /**
   * @brief F32 square root function.
   * @param[in]       *pSrc points to the input vector
   * @param[out]      *pOut points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */
  void arm_sqrt_f32(
  float32_t * pSrc,
  float32_t * pOut,
  uint32_t blockSize);

 /**
   * @brief Q31 square root function.
   * @param[in]       *pSrc points to the input vector
   * @param[out]      *pOut points to the output vector
   * @param[in]       blockSize number of samples in the vector
   * @return none.
   */
  void arm_sqrt_q31(
  q31_t * pSrc,
  q31_t * pOut,
  uint32_t blockSize);


  /**
   * @} end of SQRT group
   */



  /**
   * @brief floating-point Circular write function.
   */

  static __INLINE void arm_circularWrite_f32(
  int32_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t * src,
  uint32_t blockSize)
  {
    int wOffset;                                 /* temporary variable for write offset */
    int count1, count2;                          /* temporary loop counters */
    int32_t *ptr;                                /* temporary poionter for circular buffer */
    uint32_t blkCnt;	                         /* loop counter */
    int32x4_t x1, x2, x3, x4;                    /* temporary variables */
	int32_t size = blockSize;

    /* read offset */
    wOffset = *writeOffset;

    if((wOffset + size) <= L)
    {
      ptr = circBuffer + wOffset;

      /* unroll by 16 */
      blkCnt = blockSize >> 4u;

      while(blkCnt > 0u)
      {
        /* read 4 samples at a time */
        x1 = vld1q_s32(src);
        src += 4u;
        x2 = vld1q_s32(src);
        src += 4u;
        x3 = vld1q_s32(src);
        src += 4u;
        x4 = vld1q_s32(src);
        src += 4u;

        vst1q_s32(ptr, x1);
        ptr += 4u;
        vst1q_s32(ptr, x2);
        ptr += 4u;
        vst1q_s32(ptr, x3);
        ptr += 4u;
        vst1q_s32(ptr, x4);
        ptr += 4u;

        blkCnt--;
      }

      blkCnt = blockSize % 16u;

      /* If the blockSize is not a multiple of 16 but a multiple of 4, compute those output samples here.   
       ** No loop unrolling is used. */
      blkCnt = (blkCnt / 4);

      while(blkCnt > 0u)
      {
        vst1q_s32(ptr, vld1q_s32(src));
        src += 4u;
        ptr += 4u;

        /* Decrement the loop counter */
        blkCnt--;
      }

      blkCnt = (blockSize % 4u);

      while(blkCnt > 0)
      {
        *ptr++ = *src++;
        blkCnt--;
      }
      /* incremnet write offset */
      wOffset += blockSize;

      /* check write offset is greater than or equal to L */
      if(wOffset >= L)
        wOffset -= L;
    }

    else
    {
      if(size > L)
        src += blockSize - L;

      count1 = (L - wOffset);
      blkCnt = count1 >> 4u;

      ptr = circBuffer + wOffset;

      while(blkCnt > 0u)
      {
        x1 = vld1q_s32(src);
        src += 4u;
        x2 = vld1q_s32(src);
        src += 4u;
        x3 = vld1q_s32(src);
        src += 4u;
        x4 = vld1q_s32(src);
        src += 4u;

        vst1q_s32(ptr, x1);
        ptr += 4u;
        vst1q_s32(ptr, x2);
        ptr += 4u;
        vst1q_s32(ptr, x3);
        ptr += 4u;
        vst1q_s32(ptr, x4);
        ptr += 4u;

        blkCnt--;
      }

      /* If the blockSize is not a multiple of 16, compute any remaining output samples here.   
       ** No loop unrolling is used. */
      blkCnt = count1 % 16u;

      /* If the blockSize is not a multiple of 16 but a multiple of 4, compute those output samples here.   
       ** No loop unrolling is used. */
      blkCnt = (blkCnt / 4);

      while(blkCnt > 0u)
      {
        vst1q_s32(ptr, vld1q_s32(src));
        src += 4u;
        ptr += 4u;

        /* Decrement the loop counter */
        blkCnt--;
      }

      blkCnt = (count1 % 4u);

      wOffset += count1;

      while(blkCnt > 0)
      {
        /* If the blockSize is not a multiple of 4, compute any remaining output samples here.   
         ** No loop unrolling is used. */
        *ptr++ = *src++;
        blkCnt--;
      }

      wOffset -= L;

      count2 = (blockSize - count1);
      blkCnt = count2 >> 4u;

      ptr = circBuffer + wOffset;

      while(blkCnt > 0u)
      {
        x1 = vld1q_s32(src);
        src += 4u;
        x2 = vld1q_s32(src);
        src += 4u;
        x3 = vld1q_s32(src);
        src += 4u;
        x4 = vld1q_s32(src);
        src += 4u;

        vst1q_s32(ptr, x1);
        ptr += 4u;
        vst1q_s32(ptr, x2);
        ptr += 4u;
        vst1q_s32(ptr, x3);
        ptr += 4u;
        vst1q_s32(ptr, x4);
        ptr += 4u;

        blkCnt--;
      }

      blkCnt = count2 % 16u;

      /* If the blockSize is not a multiple of 16 but a multiple of 4, compute those output samples here.   
       ** No loop unrolling is used. */
      blkCnt = (blkCnt / 4);

      while(blkCnt > 0u)
      {
        vst1q_s32(ptr, vld1q_s32(src));
        src += 4u;
        ptr += 4u;

        /* Decrement the loop counter */
        blkCnt--;
      }

      blkCnt = (count2 % 4u);

      while(blkCnt > 0)
      {
        /* If the blockSize is not a multiple of 4, compute any remaining output samples here.   
         ** No loop unrolling is used. */
        *ptr++ = *src++;

        blkCnt--;
      }
      wOffset += count2;
    }
    *writeOffset = wOffset;
  }

  /**
   * @brief floating-point Circular Read function.
   */
  static __INLINE void arm_circularRead_f32(
  int32_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t * dst,
  uint32_t blockSize)
  {
    int count1, count2;                          /* loop counters */
    uint32_t blkCnt;                         /* loop counter */
    int32_t *ptr;                                /* temporary pointer */
    int rOffset;                                 /* read offset */
    int32x4_t x1, x2, x3, x4;                    /* temporary variables */
	int32_t size=blockSize;

    /* read offset */
    rOffset = *readOffset;

    if((rOffset + size) <= L)
    {
      /* unroll by 16 */
      blkCnt = blockSize >> 4u;

      ptr = circBuffer + rOffset;

      while(blkCnt > 0u)
      {
        /* read four samples at a time */
        x1 = vld1q_s32(ptr);
        ptr += 4u;
        x2 = vld1q_s32(ptr);
        ptr += 4u;
        x3 = vld1q_s32(ptr);
        ptr += 4u;
        x4 = vld1q_s32(ptr);
        ptr += 4u;

        /* store 4 samples at a time to destination buffer */
        vst1q_s32(dst, x1);
        dst += 4u;
        vst1q_s32(dst, x2);
        dst += 4u;
        vst1q_s32(dst, x3);
        dst += 4u;
        vst1q_s32(dst, x4);
        dst += 4u;

        /* decrement the loop counter */
        blkCnt--;
      }

      blkCnt = blockSize % 16u;

      /* If the blockSize is not a multiple of 16 but a multiple of 4, compute those output samples here.   
       ** No loop unrolling is used. */
      blkCnt = (blkCnt / 4);

      while(blkCnt > 0u)
      {
        vst1q_s32(dst, vld1q_s32(ptr));
        dst += 4u;
        ptr += 4u;

        /* Decrement the loop counter */
        blkCnt--;
      }

      blkCnt = (blockSize % 4u);

      rOffset += blockSize;
      while(blkCnt > 0u)
      {
        *dst++ = *ptr++;

        /* Decrement the loop counter */
        blkCnt--;
      }

      if(rOffset >= L)
        rOffset -= L;
    }

    else
    {
      count1 = (L - rOffset);
      blkCnt = count1 >> 4u;

      ptr = circBuffer + rOffset;

      while(blkCnt > 0u)
      {
        x1 = vld1q_s32(ptr);
        ptr += 4u;
        x2 = vld1q_s32(ptr);
        ptr += 4u;
        x3 = vld1q_s32(ptr);
        ptr += 4u;
        x4 = vld1q_s32(ptr);
        ptr += 4u;

        vst1q_s32(dst, x1);
        dst += 4u;
        vst1q_s32(dst, x2);
        dst += 4u;
        vst1q_s32(dst, x3);
        dst += 4u;
        vst1q_s32(dst, x4);
        dst += 4u;

        /* decrement the loop counter */
        blkCnt--;
      }

      blkCnt = count1 % 16u;

      /* If the blockSize is not a multiple of 16 but a multiple of 4, compute those output samples here.   
       ** No loop unrolling is used. */
      blkCnt = (blkCnt / 4);

      while(blkCnt > 0u)
      {
        vst1q_s32(dst, vld1q_s32(ptr));
        dst += 4u;
        ptr += 4u;

        /* Decrement the loop counter */
        blkCnt--;
      }

      blkCnt = (count1 % 4u);

      rOffset += count1;

      while(blkCnt > 0u)
      {
        *dst++ = *ptr++;

        /* Decrement the loop counter */
        blkCnt--;
      }

      rOffset -= L;

      count2 = (blockSize - count1);
      blkCnt = count2 >> 4u;

      ptr = circBuffer + rOffset;

      while(blkCnt > 0u)
      {
        x1 = vld1q_s32(ptr);
        ptr += 4u;
        x2 = vld1q_s32(ptr);
        ptr += 4u;
        x3 = vld1q_s32(ptr);
        ptr += 4u;
        x4 = vld1q_s32(ptr);
        ptr += 4u;

        vst1q_s32(dst, x1);
        dst += 4u;
        vst1q_s32(dst, x2);
        dst += 4u;
        vst1q_s32(dst, x3);
        dst += 4u;
        vst1q_s32(dst, x4);
        dst += 4u;

        /* decrement the loop counter */
        blkCnt--;
      }
      blkCnt = count2 % 16u;

      /* If the blockSize is not a multiple of 16 but a multiple of 4, compute those output samples here.   
       ** No loop unrolling is used. */
      blkCnt = (blkCnt / 4);

      while(blkCnt > 0u)
      {
        vst1q_s32(dst, vld1q_s32(ptr));
        dst += 4u;
        ptr += 4u;

        /* Decrement the loop counter */
        blkCnt--;
      }

      blkCnt = (count2 % 4u);

      rOffset += count2;

      while(blkCnt > 0u)
      {
        *dst++ = *ptr++;

        /* Decrement the loop counter */
        blkCnt--;
      }
    }
    *readOffset = rOffset;
  }



  /**
   * @brief  Sum of the squares of the elements of a Q31 vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_power_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q63_t * pResult);

  /**
   * @brief  Sum of the squares of the elements of a floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_power_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);


  /**
   * @brief  Mean value of a Q31 vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */
  void arm_mean_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

  /**
   * @brief  Mean value of a floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */
  void arm_mean_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  /**
   * @brief  Variance of the elements of a floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_var_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  /**
   * @brief  Variance of the elements of a Q31 vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_var_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q63_t * pResult);


  /**
   * @brief  Root Mean Square of the elements of a floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_rms_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  /**
   * @brief  Root Mean Square of the elements of a Q31 vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_rms_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);


  /**
   * @brief  Standard deviation of the elements of a floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_std_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  /**
   * @brief  Standard deviation of the elements of a Q31 vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output value.
   * @return none.
   */

  void arm_std_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);


  /**
   * @brief  Floating-point complex magnitude
   * @param[in]  *pSrc points to the complex input vector
   * @param[out]  *pDst points to the real output vector
   * @param[in]  numSamples number of complex samples in the input vector
   * @return none.
   */

  void arm_cmplx_mag_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);

  /**
   * @brief  Q31 complex magnitude
   * @param[in]  *pSrc points to the complex input vector
   * @param[out]  *pDst points to the real output vector
   * @param[in]  numSamples number of complex samples in the input vector
   * @return none.
   */

  void arm_cmplx_mag_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);



  /**
   * @brief  Q31 complex dot product
   * @param[in]  *pSrcA points to the first input vector
   * @param[in]  *pSrcB points to the second input vector
   * @param[in]  numSamples number of complex samples in each vector
   * @param[out]  *realResult real part of the result returned here
   * @param[out]  *imagResult imaginary part of the result returned here
   * @return none.
   */

  void arm_cmplx_dot_prod_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  uint32_t numSamples,
  q63_t * realResult,
  q63_t * imagResult);

  /**
   * @brief  Floating-point complex dot product
   * @param[in]  *pSrcA points to the first input vector
   * @param[in]  *pSrcB points to the second input vector
   * @param[in]  numSamples number of complex samples in each vector
   * @param[out]  *realResult real part of the result returned here
   * @param[out]  *imagResult imaginary part of the result returned here
   * @return none.
   */

  void arm_cmplx_dot_prod_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  uint32_t numSamples,
  float32_t * realResult,
  float32_t * imagResult);


  /**
   * @brief  Q31 complex-by-real multiplication
   * @param[in]  *pSrcCmplx points to the complex input vector
   * @param[in]  *pSrcReal points to the real input vector
   * @param[out]  *pCmplxDst points to the complex output vector
   * @param[in]  numSamples number of samples in each vector
   * @return none.
   */

  void arm_cmplx_mult_real_q31(
  q31_t * pSrcCmplx,
  q31_t * pSrcReal,
  q31_t * pCmplxDst,
  uint32_t numSamples);

  /**
   * @brief  Floating-point complex-by-real multiplication
   * @param[in]  *pSrcCmplx points to the complex input vector
   * @param[in]  *pSrcReal points to the real input vector
   * @param[out]  *pCmplxDst points to the complex output vector
   * @param[in]  numSamples number of samples in each vector
   * @return none.
   */

  void arm_cmplx_mult_real_f32(
  float32_t * pSrcCmplx,
  float32_t * pSrcReal,
  float32_t * pCmplxDst,
  uint32_t numSamples);



  /**
   * @brief  Minimum value of a Q31 vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output pointer
   * @return none.
   */
  void arm_min_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

  /**
   * @brief  Minimum value of a floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[in]  blockSize is the number of samples to process
   * @param[out]  *pResult is output pointer
   * @return none.
   */

  void arm_min_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

/**
 * @brief Maximum value of a Q31 vector.
 * @param[in]       *pSrc points to the input buffer
 * @param[in]       blockSize length of the input vector
 * @param[out]      *pResult maximum value returned here
 * @return none.
 */

  void arm_max_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

/**
 * @brief Maximum value of a floating-point vector.
 * @param[in]       *pSrc points to the input buffer
 * @param[in]       blockSize length of the input vector
 * @param[out]      *pResult maximum value returned here
 * @return none.
 */

  void arm_max_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);


  /**
   * @brief  Q31 complex-by-complex multiplication
   * @param[in]  *pSrcA points to the first input vector
   * @param[in]  *pSrcB points to the second input vector
   * @param[out]  *pDst  points to the output vector
   * @param[in]  numSamples number of complex samples in each vector
   * @return none.
   */

  void arm_cmplx_mult_cmplx_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t numSamples);

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
  uint32_t numSamples);

  /**
   * @brief Converts the elements of the floating-point vector to Q31 vector. 
   * @param[in]       *pSrc points to the floating-point input vector 
   * @param[out]      *pDst points to the Q31 output vector
   * @param[in]       blockSize length of the input vector 
   * @return none. 
   */
  void arm_float_to_q31(
  float32_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Converts the elements of the floating-point vector to Q15 vector. 
   * @param[in]       *pSrc points to the floating-point input vector 
   * @param[out]      *pDst points to the Q15 output vector
   * @param[in]       blockSize length of the input vector 
   * @return          none
   */
  void arm_float_to_q15(
  float32_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Converts the elements of the floating-point vector to Q7 vector. 
   * @param[in]       *pSrc points to the floating-point input vector 
   * @param[out]      *pDst points to the Q7 output vector
   * @param[in]       blockSize length of the input vector 
   * @return          none
   */
  void arm_float_to_q7(
  float32_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q31 vector to Q15 vector.
   * @param[in]  *pSrc is input pointer
   * @param[out]  *pDst is output pointer
   * @param[in]  blockSize is the number of samples to process
   * @return none.
   */
  void arm_q31_to_q15(
  q31_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Converts the elements of the Q31 vector to Q7 vector.
   * @param[in]  *pSrc is input pointer
   * @param[out]  *pDst is output pointer
   * @param[in]  blockSize is the number of samples to process
   * @return none.
   */
  void arm_q31_to_q7(
  q31_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Converts the elements of the Q15 vector to floating-point vector.
   * @param[in]  *pSrc is input pointer
   * @param[out]  *pDst is output pointer
   * @param[in]  blockSize is the number of samples to process
   * @return none.
   */
  void arm_q15_to_float(
  q15_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q15 vector to Q31 vector.
   * @param[in]  *pSrc is input pointer
   * @param[out]  *pDst is output pointer
   * @param[in]  blockSize is the number of samples to process
   * @return none.
   */
  void arm_q15_to_q31(
  q15_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q15 vector to Q7 vector.
   * @param[in]  *pSrc is input pointer
   * @param[out]  *pDst is output pointer
   * @param[in]  blockSize is the number of samples to process
   * @return none.
   */
  void arm_q15_to_q7(
  q15_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the floating-point matrix structure.
   */

  typedef struct
  {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    float32_t *pData;     /**< points to the data of the matrix. */
  } arm_matrix_instance_f32;


  /**
   * @brief Instance structure for the Q31 matrix structure.
   */

  typedef struct
  {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    q31_t *pData;         /**< points to the data of the matrix. */

  } arm_matrix_instance_q31;



  /**
   * @brief Floating-point matrix addition.
   * @param[in]       *pSrcA points to the first input matrix structure
   * @param[in]       *pSrcB points to the second input matrix structure
   * @param[out]      *pDst points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_add_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);

  /**
   * @brief Q31 matrix addition.
   * @param[in]       *pSrcA points to the first input matrix structure
   * @param[in]       *pSrcB points to the second input matrix structure
   * @param[out]      *pDst points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_add_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Floating-point matrix transpose.
   * @param[in]  *pSrc points to the input matrix
   * @param[out] *pDst points to the output matrix
   * @return 	The function returns either  <code>ARM_MATH_SIZE_MISMATCH</code>
   * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */

  arm_status arm_mat_trans_f32(
  const arm_matrix_instance_f32 * pSrc,
  arm_matrix_instance_f32 * pDst);

  /**
   * @brief Q31 matrix transpose.
   * @param[in]  *pSrc points to the input matrix
   * @param[out] *pDst points to the output matrix
   * @return 	The function returns either  <code>ARM_MATH_SIZE_MISMATCH</code>
   * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */

  arm_status arm_mat_trans_q31(
  const arm_matrix_instance_q31 * pSrc,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Floating-point matrix multiplication
   * @param[in]       *pSrcA points to the first input matrix structure
   * @param[in]       *pSrcB points to the second input matrix structure
   * @param[out]      *pDst points to output matrix structure
   * @param[in]		  *pScratch points to scratch buffer of size of first input matrix
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst,
  float32_t * pScratch);

  /**
   * @brief Q31 matrix multiplication
   * @param[in]       *pSrcA points to the first input matrix structure
   * @param[in]       *pSrcB points to the second input matrix structure
   * @param[out]      *pDst points to output matrix structure
   * @param[in]		  *pScratch points to scratch buffer of size of first input matrix
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst,
  q31_t * pScratch);

  /**
   * @brief Floating-point matrix subtraction
   * @param[in]       *pSrcA points to the first input matrix structure
   * @param[in]       *pSrcB points to the second input matrix structure
   * @param[out]      *pDst points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_sub_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);

  /**
   * @brief Q31 matrix subtraction
   * @param[in]       *pSrcA points to the first input matrix structure
   * @param[in]       *pSrcB points to the second input matrix structure
   * @param[out]      *pDst points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_sub_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);

  /**
   * @brief Floating-point matrix scaling.
   * @param[in]  *pSrc points to the input matrix
   * @param[in]  scale scale factor
   * @param[out] *pDst points to the output matrix
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_scale_f32(
  const arm_matrix_instance_f32 * pSrc,
  float32_t scale,
  arm_matrix_instance_f32 * pDst);

  /**
   * @brief Q31 matrix scaling.
   * @param[in]       *pSrc points to input matrix
   * @param[in]       scaleFract fractional portion of the scale factor
   * @param[in]       shift number of bits to shift the result by
   * @param[out]      *pDst points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS based on the outcome of size checking.
   */

  arm_status arm_mat_scale_q31(
  const arm_matrix_instance_q31 * pSrc,
  q31_t scaleFract,
  int32_t shift,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief  Q31 matrix initialization.
   * @param[in,out] *S             points to an instance of the floating-point matrix structure.
   * @param[in]     nRows          number of rows in the matrix.
   * @param[in]     nColumns       number of columns in the matrix.
   * @param[in]     *pData	       points to the matrix data array.
   * @return        none
   */

  void arm_mat_init_q31(
  arm_matrix_instance_q31 * S,
  uint16_t nRows,
  uint16_t nColumns,
  q31_t * pData);

  /**
   * @brief  Floating-point matrix initialization.
   * @param[in,out] *S             points to an instance of the floating-point matrix structure.
   * @param[in]     nRows          number of rows in the matrix.
   * @param[in]     nColumns       number of columns in the matrix.
   * @param[in]     *pData	       points to the matrix data array.
   * @return        none
   */

  void arm_mat_init_f32(
  arm_matrix_instance_f32 * S,
  uint16_t nRows,
  uint16_t nColumns,
  float32_t * pData);

  /**
   * @brief  Floating-point matrix initialization.
   * @param[in]       *pSrc points to input matrix structure   
   * @param[out]      *pDst points to output matrix structure   
   * @return        none
   */

  arm_status arm_mat_inverse_f32(
  const arm_matrix_instance_f32 * pSrc,
  arm_matrix_instance_f32 * pDst);


  /**
  *
  * @brief  Floating-point bilinear interpolation.
  * @param[in,out] *S points to an instance of the interpolation structure.
  * @param[in] *X points to input buffer x.
  * @param[in] *Y points to input buffer y.
  * @param[out] *Z points to output buffer.
  * @param[in] blockSize number of samples.
  */

  void arm_bilinear_interp_f32(
  const arm_bilinear_interp_instance_f32 * S,
  float32_t * X,
  float32_t * Y,
  float32_t * Z,
  int32_t blockSize);

/**
  *
  * @brief  Q31 bilinear interpolation.
  * @param[in,out] *S points to an instance of the interpolation structure.
  * @param[in] *X points to input buffer in 12.20 format.
  * @param[in] *Y points to input buffer in 12.20 format.
  * @param[out] *Z points to output buffer.
  * @param[in] blockSize number of samples.
  */

  void arm_bilinear_interp_q31(
  arm_bilinear_interp_instance_q31 * S,
  q31_t * X,
  q31_t * Y,
  q31_t * Z,
  uint32_t blockSize);

  /**
   * @brief  Process function for the floating-point Linear Interpolation Function.
   * @param[in,out] *S is an instance of the floating-point Linear Interpolation structure
   * @param[in] *x points to input buffer
   * @param[out] *y points to output buffer
   * @param[in] blockSize number of samples
   *
   */

  void arm_linear_interp_f32(
  arm_linear_interp_instance_f32 * S,
  float32_t * x,
  float32_t * y,
  uint32_t blockSize);

   /**
   *
   * @brief  Process function for the Q31 Linear Interpolation Function.
   * @param[in] *pYData  pointer to Q31 Linear Interpolation table
   * @param[in] *x points to the input buffer
   * @param[out] *y points to the output buffer
   * @param[in] nValues number of table values
   * @param[in] blockSize number of samples
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   *
   */


  void arm_linear_interp_q31(
  q31_t * pYData,
  q31_t * x,
  q31_t * y,
  uint32_t nValues,
  uint32_t blockSize);
  
#ifdef __GNUC__

  /*
   * @brief C custom defined QADD for M3 and M0 processors
   */
  static __INLINE q31_t __qadd(
			       q31_t x,
			       q31_t y)
  {
    return clip_q63_to_q31((q63_t) x + y);
  }

  /*
   * @brief C custom defined QSUB for M3 and M0 processors
   */
  static __INLINE q31_t __qsub(
			       q31_t x,
			       q31_t y)
  {
    return clip_q63_to_q31((q63_t) x - y);
  }
  
static inline q31_t __ssat(
			       q31_t x,
			       uint32_t y)
				   
{
    int32_t posMax, negMin;
    uint32_t i;

    posMax = 1;
    for (i = 0; i < (y - 1); i++)
      {
	posMax = posMax * 2;
      }

    if(x > 0)
      {
	posMax = (posMax - 1);

	if(x > posMax)
	  {
	    x = posMax;
	  }
      }
    else
      {
	negMin = -posMax;

	if(x < negMin)
	  {
	    x = negMin;
	  }
      }
    return (x);
  }		
#endif
  
#ifdef	__cplusplus
}
#endif


#endif /* _ARM_MATH_H */


/**
 *
 * End of file.
 */
