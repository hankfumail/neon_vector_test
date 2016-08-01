#include "xparameters.h"
#include "xscutimer.h"
#include "xil_printf.h"

#include "arm_math.h"
#include "arm_cmplx_vector_dot_prod_data.h"


/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID
#define TIMER_LOAD_VALUE	0xFFFFFFFF

#define SIZE 10000
#define LOOP 100

#define CACHE_LINE_SIZE    32


/************************** Variable Definitions *****************************/

XScuTimer Timer;		/* Cortex A9 SCU Private Timer Instance */

float __attribute__((aligned(CACHE_LINE_SIZE))) result[4];
float __attribute__((aligned(CACHE_LINE_SIZE))) result_golden =8334.33398;
//float result_golden=8334.333008;
float  __attribute__((aligned(CACHE_LINE_SIZE)))vec1[SIZE];
float __attribute__((aligned(CACHE_LINE_SIZE))) vec2[SIZE];


/************************** Function Definitions *****************************/
int neon_dot_product_vec_4(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_dot_product_vec_8(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_dot_product_vec_16(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_cmplx_vec_dot_prod_8(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_cmplx_vec_dot_prod_8b(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_cmplx_vec_dot_prod_16(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_cmplx_vec_dot_prod_16a(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_cmplx_vec_dot_prod_16b(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_cmplx_vec_dot_prod_16c(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);
int neon_dot_product_vec_20(float * dst,
                         float * src1,
                         float * src2,
                         unsigned int count);



float float32DftMem(float *__restrict AA, float *__restrict BB, int n)
{
	float tmp[4]={0.0, 0.0, 0.0, 0.0};
	int i,j;

    n=SIZE;
	for(i=0;i<n/4;i++)
	{
        j=i*4;
		tmp[0] += AA[j] * BB[j];
		tmp[1] += AA[j+1] * BB[j+1];
		tmp[2] += AA[j+2] * BB[j+2];
		tmp[3] += AA[j+3] * BB[j+3];
	}
	return tmp[0] + tmp[1] + tmp[2] + tmp[3];
}



int main_test(void)
{
	int  Status;
	volatile u32 CntValue1 = 0;
	volatile u32 CntValue2 = 0;
	XScuTimer_Config *ConfigPtr;
	XScuTimer *TimerInstancePtr = &Timer;

	int i;
	int Delta, DeltaMax, DeltaMin, DeltaTotal;

	float sum[4]={0.0, 0.0, 0.0, 0.0};

	printf("%p, %p, %p, %p \r\n", &result, &result_golden, vec1, vec2 );

	/* Initialize the Scu Private Timer so that it is ready to use. */
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);

	/* This is where the virtual address would be used, this example uses physical address. */
	Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr,
				 ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	XScuTimer_SetPrescaler(TimerInstancePtr, 0);

    for(i=0; i<SIZE; i++)
    {
        vec1[i]=(i+1)/(float)SIZE;
        vec2[i]=(i+SIZE+1)/(float)SIZE;
    }

    DeltaMax=0;
    DeltaMin=0x7FFFFFFF;
    DeltaTotal=0;
    for(i=0; i<LOOP; i++)
    {
	    /* Load the timer counter register. */
	    XScuTimer_LoadTimer(TimerInstancePtr, TIMER_LOAD_VALUE);
	    /* Get a snapshot of the timer counter value before it's started to compare against later. */
	    CntValue1 = XScuTimer_GetCounterValue(TimerInstancePtr);
	    result[0]=0.0;
	    result[1]=0.0;
	    result[2]=0.0;
	    result[3]=0.0;
	    /* Start the Scu Private Timer device. */
	    XScuTimer_Start(TimerInstancePtr);

	    //result[0] = float32DftMem(vec1, vec2, SIZE);

	    neon_dot_product_vec_16(result, vec1, vec2, SIZE);

	    //dot_product_intrinsic_8(result, vec1, vec2);

	    XScuTimer_Stop(TimerInstancePtr);
	    CntValue2 = XScuTimer_GetCounterValue(TimerInstancePtr);

	    Delta = CntValue1 - CntValue2;
	    if(DeltaMax<Delta)
	    	DeltaMax = Delta;
	    if(DeltaMin>Delta)
	    	DeltaMin = Delta;
	    DeltaTotal += Delta;
    }
    printf("\r\n");
    printf("result=%f, %f, %f, %f \r\n", result[0], result[1], result[2], result[3]);
    printf("result=%f, %f, %s\r\n", result[0], result_golden, (*((int*)(&result[0])))^(*((int*)(&result_golden)))?"NOT EQUAL":"EQUAL");
    printf("         (PCLK tick), (us)\r\n");
    printf("DeltaMin=%7d   , %f \r\n", DeltaMin, (float)DeltaMin/333.0);
    printf("DeltaMax=%7d   , %f \r\n", DeltaMax, (float)DeltaMax/333.0);
    printf("Arithmatic Average\r\n");
    printf("DeltaAvg=%10.2f, %f \r\n", (float)DeltaTotal/LOOP, (float)DeltaTotal/LOOP/333.0);
    printf("Filtered Arithmatic Average\r\n");
    printf("DeltaAvg=%10.2f, %f \r\n", (float)(DeltaTotal-DeltaMax-DeltaMin)/(LOOP-2), (float)(DeltaTotal-DeltaMax-DeltaMin)/(LOOP-2)/333.0);

	return XST_SUCCESS;
}



extern   float 	gf_sum_asm_dot_4[4];
extern   float 	gf_sum_asm_dot_8[4];
extern   float 	gf_sum_asm_dot_16[4];
extern   float 	gf_sum_asm_dot_20[4];


void asm_dot_prod4( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_dot_4;


    neon_dot_product_vec_4(pDst, pSrcA, pSrcB, ui_vector_length);

}


void asm_dot_prod8( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_dot_8;


    neon_dot_product_vec_8(pDst, pSrcA, pSrcB, ui_vector_length);

}


void asm_dot_prod16( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_dot_16;


    neon_dot_product_vec_16(pDst, pSrcA, pSrcB, ui_vector_length);

}


void asm_dot_prod20( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_dot_20;


    neon_dot_product_vec_20(pDst, pSrcA, pSrcB, ui_vector_length);

}

void asm_cmplx_dot_prod8( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_cmplx_dot_8;

    neon_cmplx_vec_dot_prod_8(pDst, pSrcA, pSrcB, ui_vector_length);

}

void asm_cmplx_dot_prod8b( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_cmplx_dot_8b;

    neon_cmplx_vec_dot_prod_8b(pDst, pSrcA, pSrcB, ui_vector_length);

}

void asm_cmplx_dot_prod16( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_cmplx_dot_16;


    neon_cmplx_vec_dot_prod_16(pDst, pSrcA, pSrcB, ui_vector_length);

}

void asm_cmplx_dot_prod16a( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_cmplx_dot_16a;


    neon_cmplx_vec_dot_prod_16a(pDst, pSrcA, pSrcB, ui_vector_length);

}



void asm_cmplx_dot_prod16b( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_cmplx_dot_16b;


    neon_cmplx_vec_dot_prod_16b(pDst, pSrcA, pSrcB, ui_vector_length);

}



void asm_cmplx_dot_prod16c( unsigned int ui_vector_length )
{
	float * pSrcA;
	float * pSrcB;
	float * pDst;

	pSrcA = gf_array_src_a;
	pSrcB = gf_array_src_b;
	pDst = gf_sum_asm_cmplx_dot_16c;


    neon_cmplx_vec_dot_prod_16c(pDst, pSrcA, pSrcB, ui_vector_length);

}



