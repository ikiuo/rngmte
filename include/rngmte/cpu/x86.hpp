#ifndef __RNGMTE_X86_HPP__
#define __RNGMTE_X86_HPP__ 1
#pragma once

#if (defined(__amd64) || defined(__amd64__) ||          \
     defined(__x86_64) || defined(__x86_64__) ||        \
     defined(_M_AMD64) || defined(_M_X64))
#  define RngMTE_CPU_X64 1
#  define RngMTE_GPR_BITS 64
#endif

#if (RngMTE_CPU_X64 || defined(__x86) || defined(__x86__) || defined(_M_IX86))
#  define RngMTE_CPU_X86 1
#  define RngMTE_LITTLE_ENDIAN 1
#  ifndef RngMTE_GPR_BITS
#    define RngMTE_GPR_BITS 32
#  endif
#endif

/**/

#ifndef RngMTE_X86_AVX2
#  if (RngMTE_CPU_X86 && defined(__AVX2__))
#    define RngMTE_X86_AVX2 1
#  else
#    define RngMTE_X86_AVX2 0
#  endif
#endif

#ifndef RngMTE_X86_AVX
#  if (RngMTE_X86_AVX2 || (RngMTE_CPU_X86 && defined(__AVX__)))
#    define RngMTE_X86_AVX 1
#  else
#    define RngMTE_X86_AVX 0
#  endif
#endif

#ifndef RngMTE_X86_SSE4_2
#  if (RngMTE_X86_AVX || (RngMTE_CPU_X86 && defined(__SSE4_2__)))
#    define RngMTE_X86_SSE4_2 1
#  else
#    define RngMTE_X86_SSE4_2 0
#  endif
#endif

#ifndef RngMTE_X86_SSE4_1
#  if (RngMTE_X86_SSE4_2 || (RngMTE_CPU_X86 && defined(__SSE4_1__)))
#    define RngMTE_X86_SSE4_1 1
#  else
#    define RngMTE_X86_SSE4_1 0
#  endif
#endif

#ifndef RngMTE_X86_SSSE3
#  if (RngMTE_X86_SSE4_1 || (RngMTE_CPU_X86 && defined(__SSSE3__)))
#    define RngMTE_X86_SSSE3 1
#  else
#    define RngMTE_X86_SSSE3 0
#  endif
#endif

#ifndef RngMTE_X86_SSE3
#  if (RngMTE_X86_SSSE3 || (RngMTE_CPU_X86 && defined(__SSE3__)))
#    define RngMTE_X86_SSE3 1
#  else
#    define RngMTE_X86_SSE3 0
#  endif
#endif

#ifndef RngMTE_X86_SSE2
#  if (RngMTE_X86_SSE3 || RngMTE_CPU_X64 ||             \
       (RngMTE_CPU_X86 && defined(__SSE2__)) ||         \
       (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
#    define RngMTE_X86_SSE2 1
#  else
#    define RngMTE_X86_SSE2 0
#  endif
#endif

#ifndef RngMTE_X86_SSE
#  if (RngMTE_X86_SSE2 ||                               \
       (RngMTE_CPU_X86 && defined(__SSE__)) ||          \
       (defined(_M_IX86_FP) && _M_IX86_FP >= 1))
#    define RngMTE_X86_SSE 1
#  else
#    define RngMTE_X86_SSE 0
#  endif
#endif

#ifndef RngMTE_X86_MMX
#  if RngMTE_X86_SSE
#    define RngMTE_X86_MMX 1
#  else
#    define RngMTE_X86_MMX 0
#  endif
#endif

/**/

#ifndef RngMTE_SIMD_X86
#  if (RngMTE_X86_MMX ||                                \
       RngMTE_X86_SSE || RngMTE_X86_SSE2 ||             \
       RngMTE_X86_SSE3 || RngMTE_X86_SSSE3 ||           \
       RngMTE_X86_SSE4_1 || RngMTE_X86_SSE4_2 ||        \
       RngMTE_X86_AVX || RngMTE_X86_AVX2)
#    define RngMTE_SIMD_X86 1
#  else
#    define RngMTE_SIMD_X86 0
#  endif
#endif

#define RngMTE_SIMD_X86_MMX    (RngMTE_SIMD_X86 && RngMTE_X86_MMX)
#define RngMTE_SIMD_X86_SSE    (RngMTE_SIMD_X86 && RngMTE_X86_SSE)
#define RngMTE_SIMD_X86_SSE2   (RngMTE_SIMD_X86 && RngMTE_X86_SSE2)
#define RngMTE_SIMD_X86_SSE3   (RngMTE_SIMD_X86 && RngMTE_X86_SSE3)
#define RngMTE_SIMD_X86_SSSE3  (RngMTE_SIMD_X86 && RngMTE_X86_SSSE3)
#define RngMTE_SIMD_X86_SSE4_1 (RngMTE_SIMD_X86 && RngMTE_X86_SSE4_1)
#define RngMTE_SIMD_X86_SSE4_2 (RngMTE_SIMD_X86 && RngMTE_X86_SSE4_2)
#define RngMTE_SIMD_X86_AVX    (RngMTE_SIMD_X86 && RngMTE_X86_AVX)
#define RngMTE_SIMD_X86_AVX2   (RngMTE_SIMD_X86 && RngMTE_X86_AVX2)

/**/

#if RngMTE_SIMD_X86
#  include <immintrin.h>
#  define RngMTE_HAS_SIMD 1
#endif /* RngMTE_SIMD_X86 */

#endif /* __RNGMTE_X86_HPP__ */
