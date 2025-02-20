/* SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright:
 *   2023      Yi-Yen Chung <eric681@andestech.com> (Copyright owned by Andes Technology)
 *   2023      Chi-Wei Chu <wewe5215@gapp.nthu.edu.tw> (Copyright owned by NTHU pllab)
 */

#if !defined(SIMDE_ARM_NEON_MINNMV_H)
#define SIMDE_ARM_NEON_MINNMV_H

#include "types.h"
#include <float.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_float16_t
simde_vminnmv_f16(simde_float16x4_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    return vminnmv_f16(a);
  #else
    simde_float16x4_private a_ = simde_float16x4_to_private(a);
    #if defined(SIMDE_RISCV_V_NATIVE) && defined(SIMDE_ARCH_RISCV_ZVFH)
      return __riscv_vfmv_f_s_f16m1_f16(__riscv_vfredmin_vs_f16m1_f16m1(a_.sv64, \
        __riscv_vfmv_v_f_f16m1(SIMDE_INFINITYHF, 4), 4));
    #else
      simde_float32_t r_ = simde_float16_to_float32(SIMDE_INFINITYHF);

      #if defined(SIMDE_FAST_NANS)
        SIMDE_VECTORIZE_REDUCTION(min:r_)
      #else
        SIMDE_VECTORIZE
      #endif
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        simde_float32_t tmp_a = simde_float16_to_float32(a_.values[i]);
        #if defined(SIMDE_FAST_NANS)
          r_ = tmp_a < r_ ? tmp_a : r_;
        #else
          r_ = (tmp_a < r_) ? tmp_a : ((tmp_a >= r_) ? r_ : ((tmp_a == tmp_a) ? r_ : tmp_a));
        #endif
      }
      return simde_float16_from_float32(r_);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && \
  !(defined(SIMDE_ARM_NEON_FP16)))
  #undef vminnmv_f16
  #define vminnmv_f16(v) simde_vminnmv_f16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float32_t
simde_vminnmv_f32(simde_float32x2_t a) {
  simde_float32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminnmv_f32(a);
  #else
    simde_float32x2_private a_ = simde_float32x2_to_private(a);

    r = SIMDE_MATH_INFINITYF;
    #if defined(SIMDE_RISCV_V_NATIVE)
      r = __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmin_vs_f32m1_f32m1(a_.sv64, \
        __riscv_vfmv_v_f_f32m1(r, 2), 2));
    #else
      #if defined(SIMDE_FAST_NANS)
        SIMDE_VECTORIZE_REDUCTION(min:r)
      #else
        SIMDE_VECTORIZE
      #endif
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        #if defined(SIMDE_FAST_NANS)
          r = a_.values[i] < r ? a_.values[i] : r;
        #else
          r = (a_.values[i] < r) ? a_.values[i] : ((a_.values[i] >= r) ? r : ((a_.values[i] == a_.values[i]) ? r : a_.values[i]));
        #endif
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminnmv_f32
  #define vminnmv_f32(v) simde_vminnmv_f32(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float16_t
simde_vminnmvq_f16(simde_float16x8_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    return vminnmvq_f16(a);
  #else
    simde_float16x8_private a_ = simde_float16x8_to_private(a);

    #if defined(SIMDE_RISCV_V_NATIVE) && defined(SIMDE_ARCH_RISCV_ZVFH)
      return __riscv_vfmv_f_s_f16m1_f16(__riscv_vfredmin_vs_f16m1_f16m1(a_.sv128, \
        __riscv_vfmv_v_f_f16m1(SIMDE_INFINITYHF, 8), 8));
    #else
      simde_float32_t r_ = simde_float16_to_float32(SIMDE_INFINITYHF);
      #if defined(SIMDE_FAST_NANS)
        SIMDE_VECTORIZE_REDUCTION(min:r_)
      #else
        SIMDE_VECTORIZE
      #endif
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        simde_float32_t tmp_a = simde_float16_to_float32(a_.values[i]);
        #if defined(SIMDE_FAST_NANS)
          r_ = tmp_a < r_ ? tmp_a : r_;
        #else
          r_ = (tmp_a < r_) ? tmp_a : ((tmp_a >= r_) ? r_ : ((tmp_a == tmp_a) ? r_ : tmp_a));
        #endif
      }
      return simde_float16_from_float32(r_);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && \
  !(defined(SIMDE_ARM_NEON_FP16)))
  #undef vminnmvq_f16
  #define vminnmvq_f16(v) simde_vminnmvq_f16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float32_t
simde_vminnmvq_f32(simde_float32x4_t a) {
  simde_float32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminnmvq_f32(a);
  #else
    simde_float32x4_private a_ = simde_float32x4_to_private(a);

    r = SIMDE_MATH_INFINITYF;
    #if defined(SIMDE_RISCV_V_NATIVE)
      r = __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmin_vs_f32m1_f32m1(a_.sv128, \
        __riscv_vfmv_v_f_f32m1(r, 4), 4));
    #else
      #if defined(SIMDE_FAST_NANS)
        SIMDE_VECTORIZE_REDUCTION(min:r)
      #else
        SIMDE_VECTORIZE
      #endif
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        #if defined(SIMDE_FAST_NANS)
          r = a_.values[i] < r ? a_.values[i] : r;
        #else
          r = (a_.values[i] < r) ? a_.values[i] : ((a_.values[i] >= r) ? r : ((a_.values[i] == a_.values[i]) ? r : a_.values[i]));
        #endif
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminnmvq_f32
  #define vminnmvq_f32(v) simde_vminnmvq_f32(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float64_t
simde_vminnmvq_f64(simde_float64x2_t a) {
  simde_float64_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminnmvq_f64(a);
  #else
    simde_float64x2_private a_ = simde_float64x2_to_private(a);

    r = SIMDE_MATH_INFINITY;
    #if defined(SIMDE_RISCV_V_NATIVE)
      r = __riscv_vfmv_f_s_f64m1_f64(__riscv_vfredmin_vs_f64m1_f64m1(a_.sv128, \
        __riscv_vfmv_v_f_f64m1(r, 2), 2));
    #else
      #if defined(SIMDE_FAST_NANS)
        SIMDE_VECTORIZE_REDUCTION(min:r)
      #else
        SIMDE_VECTORIZE
      #endif
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        #if defined(SIMDE_FAST_NANS)
          r = a_.values[i] < r ? a_.values[i] : r;
        #else
          r = (a_.values[i] < r) ? a_.values[i] : ((a_.values[i] >= r) ? r : ((a_.values[i] == a_.values[i]) ? r : a_.values[i]));
        #endif
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminnmvq_f64
  #define vminnmvq_f64(v) simde_vminnmvq_f64(v)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif /* !defined(SIMDE_ARM_NEON_MINNMV_H) */
