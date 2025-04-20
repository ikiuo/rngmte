#pragma once
#include <cstddef>
#include <cstdint>

#include <type_traits>
#include <iterator>
#include <limits>

#include <functional>
#include <algorithm>
#include <utility>
#include <iosfwd>

#include "cpu/x86.hpp"
#include "cpu/arm.hpp"

////////////////////////////////////////////////////////////////////////////////

#ifndef RngMTE_HAS_SIMD
#  define RngMTE_HAS_SIMD 0
#endif

/*
 * GPR
 */

#ifndef RngMTE_GPR_BITS
#  if ((defined(_LP64) && _LP64) ||           \
       defined(RngMTE_CPU_AARCH64) ||         \
       defined(_WIN64))
#    define RngMTE_GPR_BITS 64
#  else
#    define RngMTE_GPR_BITS 32
#  endif
#endif

#define RngMTE_GPR32 (RngMTE_GPR_BITS == 32)
#define RngMTE_GPR64 (RngMTE_GPR_BITS == 64)

/*
 * endian
 */

#ifndef RngMTE_BIG_ENDIAN
#  define RngMTE_BIG_ENDIAN 0
#endif

#ifndef RngMTE_LITTLE_ENDIAN
#  if (defined(__ARMEL__) || defined(__AARCH64EL__))
#    define RngMTE_LITTLE_ENDIAN 1
#  else
#    define RngMTE_LITTLE_ENDIAN 0
#  endif
#endif

#if RngMTE_BIG_ENDIAN && RngMTE_LITTLE_ENDIAN
#  error "RngMTE_BIG_ENDIAN == RngMTE_LITTLE_ENDIAN"
#endif

////////////////////////////////////////////////////////////////////////////////

/*
 * C++20
 */

#ifndef RngMTE_CXX20
#  if __cplusplus >= 202002L || _MSVC_LANG >= 202002L
#    define RngMTE_CXX20 1
#  else
#    define RngMTE_CXX20 0
#  endif
#endif
#ifndef RngMTE_CXX17
#  if __cplusplus >= 201703L || _MSVC_LANG >= 201703L
#    define RngMTE_CXX17 1
#  else
#    define RngMTE_CXX17 0
#  endif
#endif
#ifndef RngMTE_CXX14
#  if __cplusplus >= 201402L || _MSVC_LANG >= 201402L
#    define RngMTE_CXX14 1
#  else
#    define RngMTE_CXX14 0
#  endif
#endif
#if !RngMTE_CXX14
#  error "C++14 is required."
#endif

/*
 * __attribute__
 */

#if defined(__GNUC__)
#  define RngMTE_attribute(x) __attribute__ (x)
#else
#  define RngMTE_attribute(x) /**/
#endif

/*
 * __has_builtin
 */

#ifdef __has_builtin
#  define RngMTE_HAS_BUILTIN 1
#  define RngMTE_check_builtin __has_builtin
#else
#  define RngMTE_HAS_BUILTIN 0
#  define RngMTE_check_builtin(x) 0
#endif

/*
 * __builtin_constant_p
 */
#if defined(__GNUC__) || RngMTE_check_builtin(__builtin_constant_p)
#  define RngMTE_builtin_constant_p 1
#  define RngMTE_check_constant_p(x) __builtin_constant_p (x)
#else
#  define RngMTE_builtin_constant_p 0
#  define RngMTE_check_constant_p(x) false
#endif

/*
 * likely / unlikely
 */

#if RngMTE_CXX20
#  define RngMTE_attr_likely [[likely]]
#  define RngMTE_attr_unlikely [[likely]]
#else
#  define RngMTE_attr_likely /**/
#  define RngMTE_attr_unlikely /**/
#  if defined(__GNUC__) || RngMTE_check_builtin(__builtin_expect)
#    define RngMTE_builtin_expect 1
#    define RngMTE_cond_likely(x) __builtin_expect (!!(x), 1)
#    define RngMTE_cond_unlikely(x) __builtin_expect (!!(x), 0)
#  endif
#endif
#ifndef RngMTE_builtin_expect
#  define RngMTE_builtin_expect 0
#  define RngMTE_cond_likely(x) (x)
#  define RngMTE_cond_unlikely(x) (x)
#endif

#define RngMTE_likely_if(x) if (RngMTE_cond_likely (x)) RngMTE_attr_likely
#define RngMTE_unlikely_if(x) if (RngMTE_cond_unlikely (x)) RngMTE_attr_unlikely

#define RngMTE_likely_while(x) while (RngMTE_cond_likely (x)) RngMTE_attr_likely
#define RngMTE_unlikely_while(x) while (RngMTE_cond_unlikely (x)) RngMTE_attr_unlikely

/*
 * popcount
 */

#if RngMTE_CXX20
#  define RngMTE_STD_POPCNT 1
#else
#  if RngMTE_HAS_BUILTIN
#    if RngMTE_check_builtin(__builtin_popcount)
#      define RngMTE_HAS_POPCNT32 1
#    endif
#    if RngMTE_check_builtin(__builtin_popcountll)
#      define RngMTE_HAS_POPCNT64 1
#    endif
#  else
#    if RngMTE_SIMD_X86_SSE3
#      define RngMTE_HAS_POPCNT32 1
#      if RngMTE_GPR64
#        define RngMTE_HAS_POPCNT64 1
#      endif
#    endif
#  endif
#endif

#ifndef RngMTE_STD_POPCNT
#  define RngMTE_STD_POPCNT 0
#endif
#ifndef RngMTE_HAS_POPCNT32
#  define RngMTE_HAS_POPCNT32 0
#endif
#ifndef RngMTE_HAS_POPCNT64
#  define RngMTE_HAS_POPCNT64 0
#endif

// /////////////////////////////////////////////////////////////////////////////

namespace RngMTE
{
  /*************************
   * is_constant_evaluated *
   *************************/

  inline constexpr bool
  is_constant_evaluated ()
  {
#if RngMTE_CXX20
    return std::is_constant_evaluated ();
#elif (RngMTE_check_builtin(__builtin_is_constant_evaluated) || \
       defined(__GNUC__) || defined(_MSC_VER))
    return __builtin_is_constant_evaluated ();
#else
    return false;
#endif
  }

  /**********
   * popcnt *
   **********/

#if RngMTE_STD_POPCNT

  template <typename T>
  inline constexpr int
  popcount (T x) noexcept
  {
    return std::popcount (x);
  }

#else /* ! C++20 */

  template <typename T>
  inline constexpr int
  popcount_cxx (T x) noexcept
  {
    using U = typename std::make_unsigned<T>::type;
    constexpr size_t digits = std::numeric_limits<U>::digits;
    using U16 = typename std::conditional<(digits < 16), uint16_t, U>::type;
    using U32 = typename std::conditional<(digits < 32), uint32_t, U>::type;
    using U64 = uint64_t;

    U u1 = U (x);

    U h1 = (u1 >> 1) & U (UINT64_C (0x5555555555555555));
    U l1 = (u1 >> 0) & U (UINT64_C (0x5555555555555555));
    U u2 = h1 + l1;

    U h2 = (u2 >> 2) & U (UINT64_C (0x3333333333333333));
    U l2 = (u2 >> 0) & U (UINT64_C (0x3333333333333333));
    U u4 = h2 + l2;

    U h4 = (u4 >> 4) & U (UINT64_C (0x0f0f0f0f0f0f0f0f));
    U l4 = (u4 >> 0) & U (UINT64_C (0x0f0f0f0f0f0f0f0f));
    U u8 = h4 + l4;
    if (digits <= 8)
      return int (u8 & 0x0f);

    U h8 = U (U16 (u8) >> 8); // & U (UINT64_C (0x00ff00ff00ff00ff));
    U l8 = U (U16 (u8) >> 0); // & U (UINT64_C (0x00ff00ff00ff00ff));
    U u16 = h8 + l8;
    if (digits <= 16)
      return int (u16 & 0x1f);

    U h16 = U (U32 (u16) >> 16); // & U (UINT64_C (0x0000ffff0000ffff));
    U l16 = U (U32 (u16) >>  0); // & U (UINT64_C (0x0000ffff0000ffff));
    U u32 = h16 + l16;
    if (digits <= 32)
      return int (u32 & 0x3f);

    U h32 = U (U64 (u32) >> 32); // & UINT64_C (0x00000000ffffffff);
    U l32 = U (U64 (u32) >>  0); // & UINT64_C (0x00000000ffffffff);
    U u64 = h32 + l32;
    return int (u64 & 0x7f);
  }

  template <typename T>
  inline constexpr int
  popcount (T x) noexcept
  {
    return popcount_cxx (x);
  }

  inline constexpr int popcount (int8_t x) noexcept { return popcount (uint8_t (x)); }
  inline constexpr int popcount (int16_t x) noexcept { return popcount (uint16_t (x)); }
  inline constexpr int popcount (int32_t x) noexcept { return popcount (uint32_t (x)); }
  inline constexpr int popcount (int64_t x) noexcept { return popcount (uint64_t (x)); }

#endif /* !C++20 */

#if RngMTE_HAS_POPCNT32

  inline constexpr int
  popcount (uint8_t x) noexcept
  {
    return popcount (uint16_t (x));
  }

  inline constexpr int
  popcount (uint16_t x) noexcept
  {
#  if defined(__GNUC__)
    return __builtin_popcount (x);
#  elif defined(_MSC_VER)
    return __builtin_is_constant_evaluated () ? popcount_cxx (x) : int (__popcnt16 (x));
#  endif
  }

  inline constexpr int
  popcount (uint32_t x) noexcept
  {
#  if defined(__GNUC__)
    return __builtin_popcount (x);
#  elif defined(_MSC_VER)
    return __builtin_is_constant_evaluated () ? popcount_cxx (x) : int (__popcnt (x));
#  endif
  }

#endif /* RngMTE_HAS_POPCNT32 */
#if RngMTE_HAS_POPCNT64

  inline constexpr int
  popcount (uint64_t x) noexcept
  {
#  if defined(__GNUC__)
    return __builtin_popcountll (x);
#  elif defined(_MSC_VER)
    return __builtin_is_constant_evaluated () ? popcount_cxx (x) : int (__popcnt64 (x));
#  endif
  }

#elif RngMTE_HAS_POPCNT32 /* && !RngMTE_HAS_POPCNT64 */

  inline constexpr int
  popcount (uint64_t x) noexcept
  {
    return (popcount (uint32_t (x >>  0)) +
            popcount (uint32_t (x >> 32)));

  }

#endif /* RngMTE_HAS_POPCNT64 */

  /**********
   * parity *
   **********/

  template <typename T>
  inline constexpr bool
  is_parity (T x) noexcept
  {
    if (RngMTE_HAS_POPCNT32 || RngMTE_HAS_POPCNT64)
      return popcount (x) & 1;

    using U = typename std::make_unsigned<T>::type;
    constexpr size_t digits = std::numeric_limits<U>::digits;
    using U16 = typename std::conditional<(digits < 16), uint16_t, U>::type;
    using U32 = typename std::conditional<(digits < 32), uint32_t, U>::type;
    using U64 = uint64_t;

    U u = U (x);

    if (digits > 32)
      u ^= U (U64 (u) >> 32);
    if (digits > 16)
      u ^= U (U32 (u) >> 16);
    if (digits > 8)
      u ^= U (U16 (u) >> 8);
    u ^= u >> 4;
    u ^= u >> 2;
    u ^= u >> 1;
    return u & 1;
  }

  /**/
} // RngMTE

// /////////////////////////////////////////////////////////////////////////////

namespace RngMTE
{
  namespace SIMD
  {
    /**/

    template <typename T, size_t N>
    struct Basic;

    template <typename T, size_t N>
    struct Extend;

    /**/
  } // SIMD

  /*
   * inline
   */

  namespace SIMD
  {
  } // SIMD
} // RngMTE
