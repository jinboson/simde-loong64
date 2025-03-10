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
 *   2020-2021 Evan Nemerson <evan@nemerson.com>
 *   2023      Yi-Yen Chung <eric681@andestech.com> (Copyright owned by Andes Technology)
 */

#if !defined(SIMDE_ARM_NEON_RNDI_H)
#define SIMDE_ARM_NEON_RNDI_H

#include "types.h"

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_float16_t
simde_vrndih_f16(simde_float16_t a) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && !defined(SIMDE_BUG_GCC_95399) && defined(SIMDE_ARM_NEON_FP16)
    return vrndih_f16(a);
  #else
    return simde_float16_from_float32(simde_math_nearbyintf(simde_float16_to_float32(a)));
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && !(!defined(SIMDE_BUG_GCC_95399) && defined(SIMDE_ARM_NEON_FP16)))
  #undef vrndih_f16
  #define vrndih_f16(a) simde_vrndih_f16(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float16x4_t
simde_vrndi_f16(simde_float16x4_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && !defined(SIMDE_BUG_GCC_95399) && defined(SIMDE_ARM_NEON_FP16)
    return vrndi_f16(a);
  #else
    simde_float16x4_private
      r_,
      a_ = simde_float16x4_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vrndih_f16(a_.values[i]);
    }

    return simde_float16x4_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && !(!defined(SIMDE_BUG_GCC_95399) && defined(SIMDE_ARM_NEON_FP16)))
  #undef vrndi_f16
  #define vrndi_f16(a) simde_vrndi_f16(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float32x2_t
simde_vrndi_f32(simde_float32x2_t a) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && !defined(SIMDE_BUG_GCC_95399)
    return vrndi_f32(a);
  #else
    simde_float32x2_private
      r_,
      a_ = simde_float32x2_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_math_nearbyintf(a_.values[i]);
    }

    return simde_float32x2_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && !(!defined(SIMDE_BUG_GCC_95399)))
  #undef vrndi_f32
  #define vrndi_f32(a) simde_vrndi_f32(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float64x1_t
simde_vrndi_f64(simde_float64x1_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && !defined(SIMDE_BUG_GCC_95399)
    return vrndi_f64(a);
  #else
    simde_float64x1_private
      r_,
      a_ = simde_float64x1_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_math_nearbyint(a_.values[i]);
    }

    return simde_float64x1_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && !(!defined(SIMDE_BUG_GCC_95399)))
  #undef vrndi_f64
  #define vrndi_f64(a) simde_vrndi_f64(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float16x8_t
simde_vrndiq_f16(simde_float16x8_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && !defined(SIMDE_BUG_GCC_95399) && defined(SIMDE_ARM_NEON_FP16)
    return vrndiq_f16(a);
  #else
    simde_float16x8_private
      r_,
      a_ = simde_float16x8_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vrndih_f16(a_.values[i]);
    }

    return simde_float16x8_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && !(!defined(SIMDE_BUG_GCC_95399) && defined(SIMDE_ARM_NEON_FP16)))
  #undef vrndiq_f16
  #define vrndiq_f16(a) simde_vrndiq_f16(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float32x4_t
simde_vrndiq_f32(simde_float32x4_t a) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && !defined(SIMDE_BUG_GCC_95399)
    return vrndiq_f32(a);
  #else
    simde_float32x4_private
      r_,
      a_ = simde_float32x4_to_private(a);

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128 = _mm_round_ps(a_.m128, _MM_FROUND_CUR_DIRECTION);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = simde_math_nearbyintf(a_.values[i]);
      }
    #endif

    return simde_float32x4_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && !(!defined(SIMDE_BUG_GCC_95399)))
  #undef vrndiq_f32
  #define vrndiq_f32(a) simde_vrndiq_f32(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float64x2_t
simde_vrndiq_f64(simde_float64x2_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && !defined(SIMDE_BUG_GCC_95399)
    return vrndiq_f64(a);
  #else
    simde_float64x2_private
      r_,
      a_ = simde_float64x2_to_private(a);

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128d = _mm_round_pd(a_.m128d, _MM_FROUND_CUR_DIRECTION);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = simde_math_nearbyint(a_.values[i]);
      }
    #endif

    return simde_float64x2_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES) || (defined(SIMDE_ENABLE_NATIVE_ALIASES) && !(!defined(SIMDE_BUG_GCC_95399)))
  #undef vrndiq_f64
  #define vrndiq_f64(a) simde_vrndiq_f64(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif /* !defined(SIMDE_ARM_NEON_RNDI_H) */
