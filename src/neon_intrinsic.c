
#include <arm_neon.h>

void dot_product_intrinsic_4(float * __restrict result, float * __restrict vec1, float * __restrict vec2)
{
	float32x4_t vec1_1, vec2_1;
	float32x4_t sum = {0.0, 0.0, 0.0, 0.0};
	float32x2_t tmp[2];

	float *pvec1=vec1, *pvec2=vec2;

	asm("pld [%0]\n\t" : : "r" (pvec1));
	asm("pld [%0]\n\t" : : "r" (pvec2));

	unsigned int i;

	for( i=0; i< 10000; i+=4 )
	{
	    vec1_1=vld1q_f32(pvec1);
	    vec2_1=vld1q_f32(pvec2);
	    pvec1+=4;
	    pvec2+=4;

		asm("pld [%0]\n\t" : : "r" (pvec1));
		asm("pld [%0]\n\t" : : "r" (pvec2));

	    sum = vmlaq_f32(sum, vec1_1, vec2_1 );
	}
	tmp[0]=vget_high_f32(sum);
	tmp[1]=vget_low_f32 (sum);
	tmp[0] = vpadd_f32(tmp[0], tmp[1]);
	tmp[0] = vpadd_f32(tmp[0], tmp[0]);
	vst1_f32(result, tmp[0]);
}

void dot_product_intrinsic_8(float * __restrict result, float * __restrict vec1, float * __restrict vec2)
{
	float32x4x2_t vec1_1, vec2_1;
	float32x4_t sum_1 = {0.0, 0.0, 0.0, 0.0};
	float32x4_t sum_2 = {0.0, 0.0, 0.0, 0.0};
	float32x2_t tmp[4];

	float *pvec1=vec1, *pvec2=vec2;

	asm("pld [%0]\n\t" : : "r" (pvec1));
	asm("pld [%0]\n\t" : : "r" (pvec2));

	unsigned int i;

	for( i=0; i< 10000; i+=8 )
	{
	    vec1_1=vld2q_f32(pvec1);
	    vec2_1=vld2q_f32(pvec2);
	    pvec1+=8;
	    pvec2+=8;

		asm("pld [%0]\n\t" : : "r" (pvec1));
		asm("pld [%0]\n\t" : : "r" (pvec2));

	    sum_1 = vmlaq_f32(sum_1, vec1_1.val[0], vec2_1.val[0] );
	    sum_2 = vmlaq_f32(sum_2, vec1_1.val[1], vec2_1.val[1] );
	}

	tmp[0] = vget_high_f32(sum_1);
	tmp[1] = vget_low_f32 (sum_1);
	tmp[2] = vget_high_f32(sum_2);
    tmp[3] = vget_low_f32 (sum_2);

	tmp[0] = vpadd_f32(tmp[0], tmp[1]);
	tmp[2] = vpadd_f32(tmp[2], tmp[3]);
	tmp[0] = vpadd_f32(tmp[0], tmp[2]);
	tmp[0] = vpadd_f32(tmp[0], tmp[0]);

	vst1_f32(result, tmp[0]);
}
