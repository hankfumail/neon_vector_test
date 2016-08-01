@
@  Copyright 2011-12 ARM Limited
@  All rights reserved.
@
@  Redistribution and use in source and binary forms, with or without
@  modification, are permitted provided that the following conditions are met:
@    * Redistributions of source code must retain the above copyright
@      notice, this list of conditions and the following disclaimer.
@    * Redistributions in binary form must reproduce the above copyright
@      notice, this list of conditions and the following disclaimer in the
@      documentation and/or other materials provided with the distribution.
@    * Neither the name of ARM Limited nor the
@      names of its contributors may be used to endorse or promote products
@      derived from this software without specific prior written permission.
@
@  THIS SOFTWARE IS PROVIDED BY ARM LIMITED AND CONTRIBUTORS "AS IS" AND
@  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
@  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
@  DISCLAIMED. IN NO EVENT SHALL ARM LIMITED BE LIABLE FOR ANY
@  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
@  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
@  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
@  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
@  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
@  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
@

@
@ NE10 Library : math/NE10_dot.neon.s
@

        .text
        .syntax   unified




@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.align	4
.global neon_cmplx_vec_dot_prod_16
.thumb
.thumb_func

neon_cmplx_vec_dot_prod_16:
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		@
		@ arm_result_t dot_product_float(float * dst,
		@				  float * src1,
		@				  float * src2,
		@				  unsigned int count)
		@
		@  r0: *dst & current dst entry's address
		@  r1: *src1 & current src1 entry's address
		@  r2: *src2 & current src2 entry's address
		@  r3: int count & the number of items in the input array that can be
		@					processed in chunks of 4 vectors
		@	
		@	
		@	
		@  Note: Here we assume r3%16==0
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		push			  {r4}

		pld [r1, #0]
		pld [r2, #0]
		pld [r1, #32]
		pld [r2, #32]

		vmov.i32		  q10, #0
		vmov.i32		  q11, #0
		vmov.i32		  q12, #0
		vmov.i32		  q13, #0

.L_mainloop_cmplx_vec_16:
		@ load current set of values
		vld1.32 	   {d0, d1, d2, d3}, [r1]!
		vld1.32 	   {d4, d5, d6, d7}, [r1]!
		vld1.32 	   {d10, d11, d12, d13}, [r2]!
		vld1.32 	   {d14, d15, d16, d17}, [r2]!
		pld [r1]
		pld [r2]
		pld [r1, #32]
		pld [r2, #32]

		@ unzip data
		@ after unzip, q0,q2,q5,q7 is real part, q1,q3,q6,q8 is img part
		vuzp.32 q0, q1
		vuzp.32 q2, q3
		vuzp.32 q5, q6
		vuzp.32 q7, q8

		@ calculate values for current set
		@ (a+bi)(c+di)  = (ac-bd) + (ad+bc)i
		@ (q0+q1i)(q5+q6i)= (q0q5-q1q6) + (q0q6+q1q5)i
		vmla.f32		q10, q0, q5 
		vmla.f32		q11, q1, q6
		vmla.f32		q12, q0, q6
		vmla.f32		q13, q1, q5
		@ (q2+q3i)(q7+q8i)= (q5q7-q6q8) + (q5q8+q6q7)i
		vmla.f32		q10, q2, q7
		vmla.f32		q11, q3, q8
		vmla.f32		q12, q2, q8
		vmla.f32		q13, q3, q7
		@ loop control
		subs			r3, r3, #8
		bgt 			.L_mainloop_cmplx_vec_16			   @ loop if r3 > 0, if we have more elements to process

.L_return_cmplx_vec_16:
		@ q10 = ac, q12=bd
		vsub.f32		q14, q10, q11  @ real
		vadd.f32		d28, d28, d29  @ real
		vadd.f32		q15, q12, q13  @ img
		vadd.f32		d30, d30, d31  @ img
		vpadd.f32		d30, d28, d30
		vst1.32 		{d30}, [r0]!
		@ return
		pop 			  {r4}
		mov 			  r0, #0
		bx				  lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



