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


        .align  4
        .global neon_dot_product_vec_4
        .thumb
        .thumb_func

neon_dot_product_vec_4:
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ arm_result_t dot_product_float(float * dst,
        @                 float * src1,
        @                 float * src2,
        @                 unsigned int count)
        @
        @  r0: *dst & current dst entry's address
        @  r1: *src1 & current src1 entry's address
        @  r2: *src2 & current src2 entry's address
        @  r3: int count & the number of items in the input array that can be
        @                   processed in chunks of 4 vectors
        @
        @  Note: Here we assume r3%4==0
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        push              {r4}

        pld [r1]
        pld [r2]

        vmov.i32          q15, #0

.L_mainloop_vec_4:
        @ load current set of values
        vld1.32        {d0, d1}, [r1]!
        vld1.32        {d10, d11}, [r2]!
        pld [r1]
        pld [r2]

        @ calculate values for current set
        vmla.f32        q15, q0, q5
        @ loop control
        subs            r3, r3, #4
        bgt             .L_mainloop_vec_4             @ loop if r3 > 0, if we have more elements to process

.L_return_vec_4:
        @ calculate the final result and store it
        vpadd.f32       d30, d30, d31
        vpadd.f32       d30, d30, d30
        vst1.32         {d30}, [r0]!
        @ return
        pop               {r4}
        mov               r0, #0
        bx                lr

        .align  4
        .global neon_dot_product_vec_8
        .thumb
        .thumb_func

neon_dot_product_vec_8:
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ arm_result_t dot_product_float(float * dst,
        @                 float * src1,
        @                 float * src2,
        @                 unsigned int count)
        @
        @  r0: *dst & current dst entry's address
        @  r1: *src1 & current src1 entry's address
        @  r2: *src2 & current src2 entry's address
        @  r3: int count & the number of items in the input array that can be
        @                   processed in chunks of 4 vectors
        @
        @  Note: Here we assume r3%8==0
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        push              {r4}

        pld [r1]
        pld [r2]

        vmov.i32          q10, #0
        vmov.i32          q11, #0

.L_mainloop_vec_8:
        @ load current set of values
        vld1.32        {d0, d1, d2, d3}, [r1]!
        vld1.32        {d10, d11, d12, d13}, [r2]!
        pld [r1]
        pld [r2]

        @ calculate values for current set
        vmla.f32        q10, q0, q5
        vmla.f32        q11, q1, q6
        @ loop control
        subs            r3, r3, #8
        bgt             .L_mainloop_vec_8             @ loop if r3 > 0, if we have more elements to process

.L_return_vec_8:
        @ calculate the final result and store it
        vadd.f32        q15, q10, q11

        vpadd.f32       d30, d30, d31
        vpadd.f32       d30, d30, d30
        vst1.32         {d30}, [r0]!
        @ return
        pop               {r4}
        mov               r0, #0
        bx                lr

        .align  4
        .global neon_dot_product_vec_16
        .thumb
        .thumb_func

neon_dot_product_vec_16:
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ arm_result_t dot_product_float(float * dst,
        @                 float * src1,
        @                 float * src2,
        @                 unsigned int count)
        @
        @  r0: *dst & current dst entry's address
        @  r1: *src1 & current src1 entry's address
        @  r2: *src2 & current src2 entry's address
        @  r3: int count & the number of items in the input array that can be
        @                   processed in chunks of 4 vectors
        @
        @  Note: Here we assume r3%16==0
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        push              {r4}

        pld [r1, #0]
        pld [r2, #0]
		vmov.i32		  q10, #0
		vmov.i32		  q11, #0
        pld [r1, #32]
        pld [r2, #32]
        vmov.i32          q12, #0
        vmov.i32          q13, #0

.L_mainloop_vec_16:
        @ load current set of values
        vld1.32        {d0, d1, d2, d3}, [r1]!
        vld1.32        {d4, d5, d6, d7}, [r1]!
		pld [r1]
		pld [r2]
        vld1.32        {d10, d11, d12, d13}, [r2]!
        vld1.32        {d14, d15, d16, d17}, [r2]!
        pld [r1, #32]
        pld [r2, #32]

        @ calculate values for current set
        vmla.f32        q10, q0, q5
        vmla.f32        q11, q1, q6
        vmla.f32        q12, q2, q7
        vmla.f32        q13, q3, q8
        @ loop control
        subs            r3, r3, #16
        bgt             .L_mainloop_vec_16             @ loop if r3 > 0, if we have more elements to process

.L_return_vec_16:
        @ calculate the final result and store it
        vadd.f32        q15, q10, q11
        vadd.f32        q15, q15, q12
        vadd.f32        q15, q15, q13

        vpadd.f32       d30, d30, d31
        vpadd.f32       d30, d30, d30
        vst1.32         {d30}, [r0]!
        @ return
        pop               {r4}
        mov               r0, #0
        bx                lr



        .align  4
        .global neon_dot_product_vec_20
        .thumb
        .thumb_func

neon_dot_product_vec_20:
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ arm_result_t dot_product_float(float * dst,
        @                 float * src1,
        @                 float * src2,
        @                 unsigned int count)
        @
        @  r0: *dst & current dst entry's address
        @  r1: *src1 & current src1 entry's address
        @  r2: *src2 & current src2 entry's address
        @  r3: int count & the number of items in the input array that can be
        @                   processed in chunks of 4 vectors
        @
        @  Note: Here we assume r3%20==0
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        push              {r4}

        pld [r1, #0]
        pld [r2, #0]
        pld [r1, #32]
        pld [r2, #32]
        pld [r1, #64]
        pld [r2, #64]

        vmov.i32          q10, #0
        vmov.i32          q11, #0
        vmov.i32          q12, #0
        vmov.i32          q13, #0
        vmov.i32          q14, #0

.L_mainloop_vec_20:
        @ load current set of values
        vld1.32        {d0, d1, d2, d3}, [r1]!
        vld1.32        {d4, d5, d6, d7}, [r1]!
        vld1.32        {d8, d9}, [r1]!
        vld1.32        {d10, d11, d12, d13}, [r2]!
        vld1.32        {d14, d15, d16, d17}, [r2]!
        vld1.32        {d18, d19}, [r2]!
        pld [r1, #0]
        pld [r2, #0]
        pld [r1, #32]
        pld [r2, #32]
        pld [r1, #64]
        pld [r2, #64]

        @ calculate values for current set
        vmla.f32        q10, q0, q5
        vmla.f32        q11, q1, q6
        vmla.f32        q12, q2, q7
        vmla.f32        q13, q3, q8
        vmla.f32        q14, q4, q9
        @ loop control
        subs            r3, r3, #20
        bgt             .L_mainloop_vec_20             @ loop if r3 > 0, if we have more elements to process

.L_return_vec_20:
        @ calculate the final result and store it
        vadd.f32        q15, q10, q11
        vadd.f32        q15, q15, q12
        vadd.f32        q15, q15, q13
        vadd.f32        q15, q15, q14

        vpadd.f32       d30, d30, d31
        vpadd.f32       d30, d30, d30
        vst1.32         {d30}, [r0]!
        @ return
        pop               {r4}
        mov               r0, #0
        bx                lr
