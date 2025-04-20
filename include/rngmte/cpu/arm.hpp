#pragma once

#if (defined(__aarch64__) || defined(__AARCH64EL__) || defined(_M_ARM64))
#  define RngMTE_CPU_AARCH64 1
#endif
#if (defined(__arm) || defined(__arm__) ||      \
     defined(__ARMEL__) || defined(_M_ARM))
#  define RngMTE_CPU_ARM 1
#endif

/**/

#ifndef RngMTE_ARM_SVE2
#  if defined(__ARM_FEATURE_SVE2)
#    define RngMTE_ARM_SVE2 1
#  else
#    define RngMTE_ARM_SVE2 0
#  endif
#endif

#ifndef RngMTE_ARM_SVE
#  if (RngMTE_ARM_AVE2 || defined(__ARM_FEATURE_SVE))
#    define RngMTE_ARM_SVE 1
#  else
#    define RngMTE_ARM_SVE 0
#  endif
#endif

#ifndef RngMTE_ARM_MVE
#  if defined(__ARM_FEATURE_MVE)
#    define RngMTE_ARM_MVE 1
#  else
#    define RngMTE_ARM_MVE 0
#  endif
#endif

#ifndef RngMTE_ARM_NEON
#  if (RngMTE_ARM_MVE || RngMTE_ARM_SVE || defined(__ARM_NEON))
#    define RngMTE_ARM_NEON 1
#  else
#    define RngMTE_ARM_NEON 0
#  endif
#endif

/**/

#ifndef RngMTE_SIMD_ARM
#  if (RngMTE_ARM_NEON || RngMTE_ARM_MVE || RngMTE_ARM_SVE)
#    define RngMTE_SIMD_ARM 1
#    define RngMTE_HAS_SIMD 1
#  else
#    define RngMTE_SIMD_ARM 0
#  endif
#endif

#define RngMTE_SIMD_ARM_NEON (RngMTE_SIMD_ARM && RngMTE_ARM_NEON)
#define RngMTE_SIMD_ARM_MVE  (RngMTE_SIMD_ARM && RngMTE_ARM_MVE)
#define RngMTE_SIMD_ARM_SVE  (RngMTE_SIMD_ARM && RngMTE_ARM_SVE)
#define RngMTE_SIMD_ARM_SVE2 (RngMTE_SIMD_ARM && RngMTE_ARM_SVE2)

#if RngMTE_SIMD_ARM_NEON
#  include <arm_neon.h>
#endif
#if RngMTE_SIMD_ARM_MVE
#  include <arm_mve.h>
#endif
#if RngMTE_SIMD_ARM_SVE
#  include <arm_sve.h>
#endif
