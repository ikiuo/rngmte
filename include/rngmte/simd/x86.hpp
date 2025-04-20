#pragma once
#include "basic.hpp"

#if RngMTE_HAS_SIMD && RngMTE_SIMD_X86_SSE2
#define RngMTE_HAS_SIMD_V128 1

namespace RngMTE
{
  namespace SIMD
  {
    /**/

    using m128i_t = __m128i;
    using m128s_t = __m128;
    using m128d_t = __m128d;

    /**/

    template <typename T, size_t N>
    union Register128
    {
      using basic_type = Basic<T, N>;
      using vector_type = m128i_t;
      using element_type = T;

      static constexpr size_t element_size = sizeof (T);
      static constexpr size_t element_count = N;
      static constexpr bool simd = true;

      basic_type gpr;
      vector_type xmm;

      Register128 () = default;

      Register128 (T d0) noexcept;
      Register128 (T d0, T d1) noexcept;
      Register128 (T d0, T d1, T d2, T d3) noexcept;
      Register128 (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7) noexcept;
      Register128 (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7,
                   T d8, T d9, T dA, T dB, T dC, T dD, T dE, T dF) noexcept;

      constexpr Register128 (basic_type s) noexcept;
      constexpr Register128 (m128i_t s) noexcept;
      constexpr Register128 (m128s_t s) noexcept;
      constexpr Register128 (m128d_t s) noexcept;

      constexpr operator basic_type () const noexcept;
      constexpr operator m128i_t () const noexcept;
      constexpr operator m128s_t () const noexcept;
      constexpr operator m128d_t () const noexcept;

      constexpr Register128<T, N> operator ~ () const noexcept;
      constexpr Register128<T, N> operator - () const noexcept;

      constexpr Register128<T, N> operator <  (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator <= (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator == (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator != (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator >= (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator >  (Register128<T, N> r) const noexcept;

      constexpr Register128<T, N> operator + (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator - (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator * (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator / (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator % (Register128<T, N> r) const noexcept;

      constexpr Register128<T, N> operator & (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator ^ (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> operator | (Register128<T, N> r) const noexcept;

      constexpr Register128<T, N> operator << (size_t r) const noexcept;
      constexpr Register128<T, N> operator >> (size_t r) const noexcept;

      constexpr T get (size_t n) const noexcept;
      constexpr void set (size_t n, T r) noexcept;

      constexpr Register128<T, N> vnot () const noexcept;
      constexpr Register128<T, N> vneg () const noexcept;

      constexpr Register128<T, N> vclt (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vcle (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vceq (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vcne (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vcge (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vcgt (Register128<T, N> r) const noexcept;

      constexpr Register128<T, N> vadd (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vsub (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vmul (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vdiv (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vmod (Register128<T, N> r) const noexcept;

      constexpr Register128<T, N> vand (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vandn (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vxor (Register128<T, N> r) const noexcept;
      constexpr Register128<T, N> vor (Register128<T, N> r) const noexcept;

      constexpr Register128<T, N> vbsl (Register128<T, N> t, Register128<T, N> f) const noexcept;

      template <size_t S> constexpr Register128<T, N> vsll () const noexcept;
      constexpr Register128<T, N> vsll (size_t s) const noexcept;
      template <size_t S> constexpr Register128<T, N> vsrl () const noexcept;
      constexpr Register128<T, N> vsrl (size_t s) const noexcept;
      template <size_t S> constexpr Register128<T, N> vsra () const noexcept;
      constexpr Register128<T, N> vsra (size_t s) const noexcept;

      template <size_t S> constexpr Register128<T, N> esll () const noexcept;
      template <size_t S> constexpr Register128<T, N> esrl () const noexcept;

      /**/

      static constexpr Register128<T, N> vzero () noexcept;
      static constexpr Register128<T, N> vones () noexcept;

      static constexpr Register128<T, N> make (T d0) noexcept;
      static constexpr Register128<T, N> make (T d0, T d1) noexcept;
      static constexpr Register128<T, N> make (T d0, T d1, T d2, T d3) noexcept;
      static constexpr Register128<T, N> make (T d0, T d1, T d2, T d3,
                                               T d4, T d5, T d6, T d7) noexcept;
      static constexpr Register128<T, N> make (T d0, T d1, T d2, T d3,
                                               T d4, T d5, T d6, T d7,
                                               T d8, T d9, T dA, T dB,
                                               T dC, T dD, T dE, T dF) noexcept;

      template <size_t S> static constexpr Register128<T, N>
      extr (Register128<T, N> l, Register128<T, N> h) noexcept;

      /**/

      static constexpr Register128<T, N> *bind (void *p) noexcept;
      static constexpr const Register128<T, N> *bind (const void *p) noexcept;

      static constexpr Register128<T, N> load (const void *p) noexcept;
    };

    /**/

    using s8x16_t = Register128<int8_t, 16>;
    using s16x8_t = Register128<int16_t, 8>;
    using s32x4_t = Register128<int32_t, 4>;
    using s64x2_t = Register128<int64_t, 2>;

    using u8x16_t = Register128<uint8_t, 16>;
    using u16x8_t = Register128<uint16_t, 8>;
    using u32x4_t = Register128<uint32_t, 4>;
    using u64x2_t = Register128<uint64_t, 2>;

    /**/

    template <typename T> struct make_reg128;

    template <> struct make_reg128<int8_t> { using type = s8x16_t; };
    template <> struct make_reg128<int16_t> { using type = s16x8_t; };
    template <> struct make_reg128<int32_t> { using type = s32x4_t; };
    template <> struct make_reg128<int64_t> { using type = s64x2_t; };

    template <> struct make_reg128<uint8_t> { using type = u8x16_t; };
    template <> struct make_reg128<uint16_t> { using type = u16x8_t; };
    template <> struct make_reg128<uint32_t> { using type = u32x4_t; };
    template <> struct make_reg128<uint64_t> { using type = u64x2_t; };

    /**/

    m128i_t xmm_zero () noexcept;
    m128i_t xmm_ones () noexcept;

    /**/

    template <typename T>
    typename make_reg128<T>::type xmm_set (T d0) noexcept;

    template <typename T>
    typename make_reg128<T>::type xmm_set (T d0, T d1) noexcept;

    template <typename T>
    typename make_reg128<T>::type xmm_set (T d0, T d1, T d2, T d3) noexcept;

    template <typename T>
    typename make_reg128<T>::type xmm_set (T d0, T d1, T d2, T d3,
                                           T d4, T d5, T d6, T d7) noexcept;

    template <typename T>
    typename make_reg128<T>::type xmm_set (T d0, T d1, T d2, T d3,
                                           T d4, T d5, T d6, T d7,
                                           T d8, T d9, T dA, T dB,
                                           T dC, T dD, T dE, T dF) noexcept;

    /**/

    s8x16_t xmm_cmpeq (s8x16_t a, s8x16_t b) noexcept;
    s16x8_t xmm_cmpeq (s16x8_t a, s16x8_t b) noexcept;
    s32x4_t xmm_cmpeq (s32x4_t a, s32x4_t b) noexcept;
    s64x2_t xmm_cmpeq (s64x2_t a, s64x2_t b) noexcept;

    u8x16_t xmm_cmpeq (u8x16_t a, u8x16_t b) noexcept;
    u16x8_t xmm_cmpeq (u16x8_t a, u16x8_t b) noexcept;
    u32x4_t xmm_cmpeq (u32x4_t a, u32x4_t b) noexcept;
    u64x2_t xmm_cmpeq (u64x2_t a, u64x2_t b) noexcept;

    s8x16_t xmm_cmplt (s8x16_t a, s8x16_t b) noexcept;
    s16x8_t xmm_cmplt (s16x8_t a, s16x8_t b) noexcept;
    s32x4_t xmm_cmplt (s32x4_t a, s32x4_t b) noexcept;

    s8x16_t xmm_cmpgt (s8x16_t a, s8x16_t b) noexcept;
    s16x8_t xmm_cmpgt (s16x8_t a, s16x8_t b) noexcept;
    s32x4_t xmm_cmpgt (s32x4_t a, s32x4_t b) noexcept;

#if RngMTE_X86_SSE4_1
    s64x2_t xmm_cmplt (s64x2_t a, s64x2_t b) noexcept;
    s64x2_t xmm_cmpgt (s64x2_t a, s64x2_t b) noexcept;
#endif

    /**/

    template <typename T> T xmm_not (T s) noexcept;
    template <typename T> T xmm_neg (T s) noexcept;

    /**/

    s8x16_t xmm_add (s8x16_t a, s8x16_t b) noexcept;
    s16x8_t xmm_add (s16x8_t a, s16x8_t b) noexcept;
    s32x4_t xmm_add (s32x4_t a, s32x4_t b) noexcept;
    s64x2_t xmm_add (s64x2_t a, s64x2_t b) noexcept;

    u8x16_t xmm_add (u8x16_t a, u8x16_t b) noexcept;
    u16x8_t xmm_add (u16x8_t a, u16x8_t b) noexcept;
    u32x4_t xmm_add (u32x4_t a, u32x4_t b) noexcept;
    u64x2_t xmm_add (u64x2_t a, u64x2_t b) noexcept;

    /**/

    s8x16_t xmm_sub (s8x16_t a, s8x16_t b) noexcept;
    s16x8_t xmm_sub (s16x8_t a, s16x8_t b) noexcept;
    s32x4_t xmm_sub (s32x4_t a, s32x4_t b) noexcept;
    s64x2_t xmm_sub (s64x2_t a, s64x2_t b) noexcept;

    u8x16_t xmm_sub (u8x16_t a, u8x16_t b) noexcept;
    u16x8_t xmm_sub (u16x8_t a, u16x8_t b) noexcept;
    u32x4_t xmm_sub (u32x4_t a, u32x4_t b) noexcept;
    u64x2_t xmm_sub (u64x2_t a, u64x2_t b) noexcept;

    /**/

    s16x8_t xmm_mul (s16x8_t a, s16x8_t b) noexcept;
    u16x8_t xmm_mul (u16x8_t a, u16x8_t b) noexcept;

    /**/

    template <typename T> T xmm_and (T a, T b) noexcept;
    template <typename T> T xmm_andn (T a, T b) noexcept;
    template <typename T> T xmm_xor (T a, T b) noexcept;
    template <typename T> T xmm_or (T a, T b) noexcept;
    template <typename T> T xmm_bsl (T p, T t, T f) noexcept;

    /**/

    template <size_t N> s16x8_t xmm_slli (s16x8_t s) noexcept;
    template <size_t N> s32x4_t xmm_slli (s32x4_t s) noexcept;
    template <size_t N> s64x2_t xmm_slli (s64x2_t s) noexcept;
    s16x8_t xmm_sll (s16x8_t s, s16x8_t n) noexcept;
    s32x4_t xmm_sll (s32x4_t s, s32x4_t n) noexcept;
    s64x2_t xmm_sll (s64x2_t s, s64x2_t n) noexcept;

    template <size_t N> u16x8_t xmm_slli (u16x8_t s) noexcept;
    template <size_t N> u32x4_t xmm_slli (u32x4_t s) noexcept;
    template <size_t N> u64x2_t xmm_slli (u64x2_t s) noexcept;
    u16x8_t xmm_sll (u16x8_t s, u16x8_t n) noexcept;
    u32x4_t xmm_sll (u32x4_t s, u32x4_t n) noexcept;
    u64x2_t xmm_sll (u64x2_t s, u64x2_t n) noexcept;

    /**/

    template <size_t N> s16x8_t xmm_srli (s16x8_t s) noexcept;
    template <size_t N> s32x4_t xmm_srli (s32x4_t s) noexcept;
    template <size_t N> s64x2_t xmm_srli (s64x2_t s) noexcept;

    template <size_t N> u16x8_t xmm_srli (u16x8_t s) noexcept;
    template <size_t N> u32x4_t xmm_srli (u32x4_t s) noexcept;
    template <size_t N> u64x2_t xmm_srli (u64x2_t s) noexcept;

    /**/

    template <size_t N> s16x8_t xmm_srai (s16x8_t s) noexcept;
    template <size_t N> s32x4_t xmm_srai (s32x4_t s) noexcept;
    template <size_t N> s64x2_t xmm_srai (s64x2_t s) noexcept;

    template <size_t N> u16x8_t xmm_srai (u16x8_t s) noexcept;
    template <size_t N> u32x4_t xmm_srai (u32x4_t s) noexcept;
    template <size_t N> u64x2_t xmm_srai (u64x2_t s) noexcept;

    /**/

    template <size_t N, typename T> T xmm_bslli (T s) noexcept;
    template <size_t N, typename T> T xmm_brlli (T s) noexcept;
    template <size_t N, typename T> T xmm_bextr (T h, T l) noexcept;

    /**/
  } // SIMD

  /*
   * inline - Register128
   */

  namespace SIMD
  {
    /**/

    template <typename T, size_t N>
    inline Register128<T, N>::Register128 (T d0) noexcept
      : xmm (xmm_set (d0)) {}

    template <typename T, size_t N>
    inline Register128<T, N>::Register128 (T d0, T d1) noexcept
      : xmm (xmm_set (d0, d1)) {}

    template <typename T, size_t N>
    inline Register128<T, N>::Register128 (T d0, T d1, T d2, T d3) noexcept
      : xmm (xmm_set (d0, d1, d2, d3)) {}

    template <typename T, size_t N>
    inline Register128<T, N>::Register128 (T d0, T d1, T d2, T d3,
                                           T d4, T d5, T d6, T d7) noexcept
      : xmm (xmm_set (d0, d1, d2, d3, d4, d5, d6, d7)) {}

    template <typename T, size_t N>
    inline Register128<T, N>::Register128 (T d0, T d1, T d2, T d3,
                                           T d4, T d5, T d6, T d7,
                                           T d8, T d9, T dA, T dB,
                                           T dC, T dD, T dE, T dF) noexcept
      : xmm (xmm_set (d0, d1, d2, d3, d4, d5, d6, d7,
                      d8, d9, dA, dB, dC, dD, dE, dF)) {}

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::Register128 (basic_type s) noexcept
      : gpr (s) {}

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::Register128 (m128i_t s) noexcept
      : xmm (vector_type (s)) {}

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::Register128 (m128s_t s) noexcept
      : xmm (vector_type (s)) {}

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::Register128 (m128d_t s) noexcept
      : xmm (vector_type (s)) {}

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::operator basic_type () const noexcept
    {
      return gpr;
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::operator m128i_t () const noexcept
    {
      return m128i_t (xmm);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::operator m128s_t () const noexcept
    {
      return m128s_t (xmm);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::operator m128d_t () const noexcept
    {
      return m128d_t (xmm);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator ~ () const noexcept
    {
      return vnot ();
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator - () const noexcept
    {
      return vneg ();
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator < (Register128<T, N> r) const noexcept
    {
      return vclt (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator <= (Register128<T, N> r) const noexcept
    {
      return vcle (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator == (Register128<T, N> r) const noexcept
    {
      return vceq (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator != (Register128<T, N> r) const noexcept
    {
      return vcne (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator >= (Register128<T, N> r) const noexcept
    {
      return vcge (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator > (Register128<T, N> r) const noexcept
    {
      return vcgt (r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator + (Register128<T, N> r) const noexcept
    {
      return vadd (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator - (Register128<T, N> r) const noexcept
    {
      return vsub (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator * (Register128<T, N> r) const noexcept
    {
      return vmul (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator / (Register128<T, N> r) const noexcept
    {
      return vdiv (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator % (Register128<T, N> r) const noexcept
    {
      return vmod (r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator & (Register128<T, N> r) const noexcept
    {
      return vand (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator ^ (Register128<T, N> r) const noexcept
    {
      return vxor (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::operator | (Register128<T, N> r) const noexcept
    {
      return vor (r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr T
    Register128<T, N>::get (size_t n) const noexcept
    {
      return gpr.get (n);
    }

    template <typename T, size_t N>
    inline constexpr void
    Register128<T, N>::set (size_t n, T r) noexcept
    {
      gpr.set (n, r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vnot () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vnot ();
      return xmm_not (xmm);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vneg () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vneg ();
      return xmm_neg (xmm);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vclt (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vclt (r);
      return xmm_cmplt (xmm, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vcle (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vcle (r);
      return xmm_or (xmm_cmpeq (xmm, r), xmm_cmplt (xmm, r));
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vceq (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vceq (r);
      return xmm_cmpeq (xmm, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vcne (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vcne (r);
      return vceq (r).vnot ();
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vcge (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vcge (r);
      return xmm_or (xmm_cmplt (r, xmm), xmm_cmpeq (xmm, r));
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vcgt (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vcgt (r);
      return xmm_cmplt (r, xmm);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vadd (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vadd (r);
      return xmm_add (*this, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsub (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vsub (r);
      return xmm_sub (*this, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vmul (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vmul (r);
      return xmm_mul (*this, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vdiv (Register128<T, N> r) const noexcept
    {
      return gpr.vdiv (r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vmod (Register128<T, N> r) const noexcept
    {
      return gpr.vmod (r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vand (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vand (r);
      return xmm_and<vector_type> (xmm, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vandn (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vandn (r);
      return xmm_andn<vector_type> (xmm, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vxor (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vxor (r);
      return xmm_xor<vector_type> (xmm, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vor (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vor (r);
      return xmm_or<vector_type> (xmm, r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vbsl (Register128<T, N> t, Register128<T, N> f) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vbsl (t, f);
      return xmm_bsl<vector_type> (f, t, xmm);
    }

    /**/

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsll () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template vsll<S> ();
      return xmm_slli<S> (*this);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsll (size_t s) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vsll (s);
      return xmm_sll (*this, xmm_set (int64_t (s), int64_t (0)));
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsrl () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template vsrl<S> ();
      return xmm_srli<S> (*this);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsrl (size_t s) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vsrl (s);
      return xmm_srl (*this, xmm_set (int64_t (s), int64_t (0)));
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsra () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template vsra<S> ();
      return xmm_srai<S> (*this);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsra (size_t s) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vsra (s);
      return xmm_sra (*this, xmm_set (int64_t (s), int64_t (0)));
    }

    /**/

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::esll () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template esll <S> ();
      if (S < N)
        return xmm_bextr<(N - S) * sizeof (T)> (xmm, xmm_zero ());
      return xmm_zero ();
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::esrl () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template esrl <S> ();
      if (S < N)
        return xmm_bextr<S * sizeof (T)> (xmm_zero (), xmm);
      return xmm_zero ();
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vzero () noexcept
    {
      if (is_constant_evaluated ())
        return basic_type::vzero ();
      return xmm_zero ();
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vones () noexcept
    {
      if (is_constant_evaluated ())
        return basic_type::vones ();
      return xmm_ones ();
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::make (T d0) noexcept
    {
      return basic_type (d0);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::make (T d0, T d1) noexcept
    {
      return basic_type (d0, d1);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::make (T d0, T d1, T d2, T d3) noexcept
    {
      return basic_type (d0, d1, d2, d3);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::make (T d0, T d1, T d2, T d3,
                             T d4, T d5, T d6, T d7) noexcept
    {
      return basic_type (d0, d1, d2, d3, d4, d5, d6, d7);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::make (T d0, T d1, T d2, T d3,
                             T d4, T d5, T d6, T d7,
                             T d8, T d9, T dA, T dB,
                             T dC, T dD, T dE, T dF) noexcept
    {
      return basic_type (d0, d1, d2, d3, d4, d5, d6, d7,
                         d8, d9, dA, dB, dC, dD, dE, dF);
    }

    /**/

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::extr (Register128<T, N> l, Register128<T, N> h) noexcept
    {
      if (is_constant_evaluated ())
        return basic_type::template extr <S> (l, h);
      return xmm_bextr<S * sizeof (T)> (h, l);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N> *
    Register128<T, N>::bind (void *p) noexcept
    {
      return reinterpret_cast<Register128<T, N> *>(p);
    }

    template <typename T, size_t N>
    inline constexpr const Register128<T, N> *
    Register128<T, N>::bind (const void *p) noexcept
    {
      return reinterpret_cast<const Register128<T, N> *>(p);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::load (const void *p) noexcept
    {
      return *bind (p);
    }

    /**/
  } // SIMD

  /*
   *
   */

  namespace SIMD
  {
    /**/

    inline m128i_t
    xmm_zero () noexcept
    {
      return _mm_setzero_si128 ();
    }

    inline m128i_t
    xmm_ones () noexcept
    {
      return _mm_set1_epi8 (~0);
    }

    /**/

    template <typename T>
    inline typename make_reg128<T>::type
    xmm_set (T d0) noexcept
    {
      switch (sizeof (T))
        {
        case 1:
          return _mm_set1_epi8 (char (d0));

        case 2:
          return _mm_set1_epi16 (short (d0));

        case 4:
          return _mm_set1_epi32 (int (d0));

        case 8:
          return _mm_set1_epi64x (int64_t (d0));

        default:
          return xmm_zero ();
        }
    }

    template <typename T>
    inline typename make_reg128<T>::type
    xmm_set (T d0, T d1) noexcept
    {
      switch (sizeof (T))
        {
        case 1:
          return _mm_set_epi8
            (char (d1), char (d0),
             char (d1), char (d0),
             char (d1), char (d0),
             char (d1), char (d0),
             char (d1), char (d0),
             char (d1), char (d0),
             char (d1), char (d0),
             char (d1), char (d0));

        case 2:
          return _mm_set_epi16
            (short (d1), short (d0),
             short (d1), short (d0),
             short (d1), short (d0),
             short (d1), short (d0));

        case 4:
          return _mm_set_epi32
            (int (d1), int (d0),
             int (d1), int (d0));

        case 8:
          return _mm_set_epi64x (int64_t (d1), int64_t (d0));

        default:
          return xmm_zero ();
        }
    }

    template <typename T>
    inline typename make_reg128<T>::type
    xmm_set (T d0, T d1, T d2, T d3) noexcept
    {
      switch (sizeof (T))
        {
        case 1:
          return _mm_set_epi8
            (char (d3), char (d2), char (d1), char (d0),
             char (d3), char (d2), char (d1), char (d0),
             char (d3), char (d2), char (d1), char (d0),
             char (d3), char (d2), char (d1), char (d0));

        case 2:
          return _mm_set_epi16
            (short (d3), short (d2), short (d1), short (d0),
             short (d3), short (d2), short (d1), short (d0));

        case 4:
          return _mm_set_epi32 (int (d3), int (d2), int (d1), int (d0));

        case 8:
          return _mm_set_epi64x (int64_t (d1), int64_t (d0));

        default:
          return xmm_zero ();
        }
    }

    template <typename T>
    inline typename make_reg128<T>::type
    xmm_set (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7) noexcept
    {
      switch (sizeof (T))
        {
        case 1:
          return _mm_set_epi8
            (char (d7), char (d6), char (d5), char (d4),
             char (d3), char (d2), char (d1), char (d0),
             char (d7), char (d6), char (d5), char (d4),
             char (d3), char (d2), char (d1), char (d0));

        case 2:
          return _mm_set_epi16
            (short (d7), short (d6), short (d5), short (d4),
             short (d3), short (d2), short (d1), short (d0));

        case 4:
          return _mm_set_epi32 (int (d3), int (d2), int (d1), int (d0));

        case 8:
          return _mm_set_epi64x (int64_t (d1), int64_t (d0));

        default:
          return xmm_zero ();
        }
    }

    template <typename T>
    inline typename make_reg128<T>::type
    xmm_set (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7,
             T d8, T d9, T dA, T dB, T dC, T dD, T dE, T dF) noexcept
    {
      switch (sizeof (T))
        {
        case 1:
          return _mm_set_epi8
            (char (dF), char (dE), char (dD), char (dC),
             char (dB), char (dA), char (d9), char (d8),
             char (d7), char (d6), char (d5), char (d4),
             char (d3), char (d2), char (d1), char (d0));

        case 2:
          return _mm_set_epi16
            (short (d7), short (d6), short (d5), short (d4),
             short (d3), short (d2), short (d1), short (d0));

        case 4:
          return _mm_set_epi32 (int (d3), int (d2), int (d1), int (d0));

        case 8:
          return _mm_set_epi64x (int64_t (d1), int64_t (d0));

        default:
          return xmm_zero ();
        }
    }

    /**/

    inline s8x16_t
    xmm_cmpeq (s8x16_t a, s8x16_t b) noexcept
    {
      return _mm_cmpeq_epi8 (a, b);
    }

    inline s16x8_t
    xmm_cmpeq (s16x8_t a, s16x8_t b) noexcept
    {
      return _mm_cmpeq_epi16 (a, b);
    }

    inline s32x4_t
    xmm_cmpeq (s32x4_t a, s32x4_t b) noexcept
    {
      return _mm_cmpeq_epi32 (a, b);
    }

    inline u8x16_t
    xmm_cmpeq (u8x16_t a, u8x16_t b) noexcept
    {
      return _mm_cmpeq_epi8 (a, b);
    }

    inline u16x8_t
    xmm_cmpeq (u16x8_t a, u16x8_t b) noexcept
    {
      return _mm_cmpeq_epi16 (a, b);
    }

    inline u32x4_t
    xmm_cmpeq (u32x4_t a, u32x4_t b) noexcept
    {
      return _mm_cmpeq_epi32 (a, b);
    }

#if RngMTE_X86_SSE4_1

    inline s64x2_t
    xmm_cmpeq (s64x2_t a, s64x2_t b) noexcept
    {
      return _mm_cmpeq_epi64 (a, b);
    }

    inline u64x2_t
    xmm_cmpeq (u64x2_t a, u64x2_t b) noexcept
    {
      return _mm_cmpeq_epi64 (a, b);
    }

#else  /* SSE2 */

    inline s64x2_t
    xmm_cmpeq (s64x2_t a, s64x2_t b) noexcept
    {
      return s64x2_t (_mm_cmpeq_epi64 (a, b));
    }

    inline u64x2_t
    xmm_cmpeq (u64x2_t a, u64x2_t b) noexcept
    {
      m128i_t c32 = _mm_cmpeq_epi32 (a, b);
      m128i_t l32 = _mm_slli_epi64 (c32, 32);
      m128i_t h32 = _mm_srli_epi64 (c32, 32);
      m128i_t r32 = _mm_or_si128 (l32, h32);
      return _mm_and_si128 (c32, r32);
    }

#endif

    /**/

    inline s8x16_t
    xmm_cmplt (s8x16_t a, s8x16_t b) noexcept
    {
      return _mm_cmplt_epi8 (a, b);
    }

    inline s16x8_t
    xmm_cmplt (s16x8_t a, s16x8_t b) noexcept
    {
      return _mm_cmplt_epi16 (a, b);
    }

    inline s32x4_t
    xmm_cmplt (s32x4_t a, s32x4_t b) noexcept
    {
      return _mm_cmplt_epi32 (a, b);
    }

    /**/

    inline s8x16_t
    xmm_cmpgt (s8x16_t a, s8x16_t b) noexcept
    {
      return _mm_cmpgt_epi8 (a, b);
    }

    inline s16x8_t
    xmm_cmpgt (s16x8_t a, s16x8_t b) noexcept
    {
      return _mm_cmpgt_epi16 (a, b);
    }

    inline s32x4_t
    xmm_cmpgt (s32x4_t a, s32x4_t b) noexcept
    {
      return _mm_cmpgt_epi32 (a, b);
    }

    /**/

#if RngMTE_X86_SSE4_1

    inline s64x2_t
    xmm_cmplt (s64x2_t a, s64x2_t b) noexcept
    {
      return xmm_cmpgt (b, a);
    }

    inline s64x2_t
    xmm_cmpgt (s64x2_t a, s64x2_t b) noexcept
    {
      return _mm_cmpgt_epi64 (a, b);
    }

#endif

    /**/

    template <typename T>
    inline T
    xmm_not (T s) noexcept
    {
      return xmm_xor (m128i_t (s), xmm_ones ());
    }

    template <typename T>
    inline T
    xmm_neg (T s) noexcept
    {
      return xmm_sub (T (xmm_zero ()), s);
    }

    /**/

    inline s8x16_t
    xmm_add (s8x16_t a, s8x16_t b) noexcept
    {
      return _mm_add_epi8 (a, b);
    }

    inline s16x8_t
    xmm_add (s16x8_t a, s16x8_t b) noexcept
    {
      return _mm_add_epi16 (a, b);
    }

    inline s32x4_t
    xmm_add (s32x4_t a, s32x4_t b) noexcept
    {
      return _mm_add_epi32 (a, b);
    }

    inline s64x2_t
    xmm_add (s64x2_t a, s64x2_t b) noexcept
    {
      return _mm_add_epi64 (a, b);
    }

    inline u8x16_t
    xmm_add (u8x16_t a, u8x16_t b) noexcept
    {
      return _mm_add_epi8 (a, b);
    }

    inline u16x8_t
    xmm_add (u16x8_t a, u16x8_t b) noexcept
    {
      return _mm_add_epi16 (a, b);
    }

    inline u32x4_t
    xmm_add (u32x4_t a, u32x4_t b) noexcept
    {
      return _mm_add_epi32 (a, b);
    }

    inline u64x2_t
    xmm_add (u64x2_t a, u64x2_t b) noexcept
    {
      return _mm_add_epi64 (a, b);
    }

    /**/

    inline s8x16_t
    xmm_sub (s8x16_t a, s8x16_t b) noexcept
    {
      return _mm_sub_epi8 (a, b);
    }

    inline s16x8_t
    xmm_sub (s16x8_t a, s16x8_t b) noexcept
    {
      return _mm_sub_epi16 (a, b);
    }

    inline s32x4_t
    xmm_sub (s32x4_t a, s32x4_t b) noexcept
    {
      return _mm_sub_epi32 (a, b);
    }

    inline s64x2_t
    xmm_sub (s64x2_t a, s64x2_t b) noexcept
    {
      return _mm_sub_epi64 (a, b);
    }

    inline u8x16_t
    xmm_sub (u8x16_t a, u8x16_t b) noexcept
    {
      return _mm_sub_epi8 (a, b);
    }

    inline u16x8_t
    xmm_sub (u16x8_t a, u16x8_t b) noexcept
    {
      return _mm_sub_epi16 (a, b);
    }

    inline u32x4_t
    xmm_sub (u32x4_t a, u32x4_t b) noexcept
    {
      return _mm_sub_epi32 (a, b);
    }

    inline u64x2_t
    xmm_sub (u64x2_t a, u64x2_t b) noexcept
    {
      return _mm_sub_epi64 (a, b);
    }

    /**/

    inline s16x8_t
    xmm_mul (s16x8_t a, s16x8_t b) noexcept
    {
      return _mm_mullo_epi16 (a, b);
    }

    inline u16x8_t
    xmm_mul (u16x8_t a, u16x8_t b) noexcept
    {
      return _mm_mullo_epi16 (a, b);
    }

    /**/

    template <typename T>
    inline T
    xmm_and (T a, T b) noexcept
    {
      return T (_mm_and_si128 (m128i_t (a), m128i_t (b)));
    }

    template <typename T>
    inline T
    xmm_andn (T a, T b) noexcept
    {
      return T (_mm_andnot_si128 (m128i_t (a), m128i_t (b)));
    }

    template <typename T>
    inline T xmm_xor (T a, T b) noexcept
    {
      return T (_mm_xor_si128 (m128i_t (a), m128i_t (b)));
    }

    template <typename T>
    inline T xmm_or (T a, T b) noexcept
    {
      return T (_mm_or_si128 (m128i_t (a), m128i_t (b)));
    }

    template <typename T>
    inline T xmm_bsl (T f, T t, T p) noexcept
    {
      return T (_mm_or_si128
                (_mm_and_si128 (m128i_t (p), m128i_t (t)),
                 _mm_andnot_si128 (m128i_t (p), m128i_t (f))));
    }

    /**/

    template <size_t N>
    inline s16x8_t
    xmm_slli (s16x8_t s) noexcept
    {
      return _mm_slli_epi16 (s, N);
    }

    template <size_t N>
    inline s32x4_t
    xmm_slli (s32x4_t s) noexcept
    {
      return _mm_slli_epi32 (s, N);
    }

    template <size_t N>
    inline s64x2_t
    xmm_slli (s64x2_t s) noexcept
    {
      return _mm_slli_epi64 (s, N);
    }

    template <size_t N>
    inline u16x8_t
    xmm_slli (u16x8_t s) noexcept
    {
      return _mm_slli_epi16 (s, N);
    }

    template <size_t N>
    inline u32x4_t
    xmm_slli (u32x4_t s) noexcept
    {
      return _mm_slli_epi32 (s, N);
    }

    template <size_t N>
    inline u64x2_t
    xmm_slli (u64x2_t s) noexcept
    {
      return _mm_slli_epi64 (s, N);
    }

    /**/

    template <size_t N>
    inline s16x8_t
    xmm_srli (s16x8_t s) noexcept
    {
      return _mm_srli_epi16 (s, N);
    }

    template <size_t N>
    inline s32x4_t
    xmm_srli (s32x4_t s) noexcept
    {
      return _mm_srli_epi32 (s, N);
    }

    template <size_t N>
    inline s64x2_t
    xmm_srli (s64x2_t s) noexcept
    {
      return _mm_srli_epi64 (s, N);
    }

    template <size_t N>
    inline u16x8_t
    xmm_srli (u16x8_t s) noexcept
    {
      return _mm_srli_epi16 (s, N);
    }

    template <size_t N>
    inline u32x4_t
    xmm_srli (u32x4_t s) noexcept
    {
      return _mm_srli_epi32 (s, N);
    }

    template <size_t N>
    inline u64x2_t
    xmm_srli (u64x2_t s) noexcept
    {
      return _mm_srli_epi64 (s, N);
    }

    /**/

    template <size_t N>
    inline s16x8_t
    xmm_srai (s16x8_t s) noexcept
    {
      return _mm_srai_epi16 (s, N);
    }

    template <size_t N>
    inline s32x4_t
    xmm_srai (s32x4_t s) noexcept
    {
      return _mm_srai_epi32 (s, N);
    }

    template <size_t N>
    inline s64x2_t
    xmm_srai (s64x2_t s) noexcept
    {
      return _mm_srai_epi64 (s, N);
    }

    template <size_t N>
    inline u16x8_t
    xmm_srai (u16x8_t s) noexcept
    {
      return _mm_srai_epi16 (s, N);
    }

    template <size_t N>
    inline u32x4_t
    xmm_srai (u32x4_t s) noexcept
    {
      return _mm_srai_epi32 (s, N);
    }

    template <size_t N>
    inline u64x2_t
    xmm_srai (u64x2_t s) noexcept
    {
      return _mm_srai_epi64 (s, N);
    }

    /**/

    template <size_t N, typename T>
    inline T xmm_bslli (T s) noexcept
    {
      return T (_mm_bslli_si128 (m128i_t (s), N));
    }

    template <size_t N, typename T>
    inline T xmm_bsrli (T s) noexcept
    {
      return T (_mm_bsrli_si128 (m128i_t (s), N));
    }

    template <size_t N, typename T>
    inline T xmm_bextr (T h, T l) noexcept
    {
#if RngMTE_X86_SSSE3
      return T (_mm_alignr_epi8 (m128i_t (h), m128i_t (l), N));
#else
      constexpr size_t W = 16;
      constexpr size_t S = std::min (N, W);
      constexpr size_t H = W - S;
      constexpr size_t U = N - S;

      if (N >= W * 2)
        return T (xmm_zero ());
      if (N > W)
        return xmm_bsrli<U> (h);
      if (N == W)
        return h;
      if (N > 0)
        return xmm_or (xmm_bsrli<S> (l), xmm_bslli<H> (h));
      return l;
#endif /* SSSE3 */
    }

    /**/
  } // SIMD
} // RngMTE

#endif /* RngMTE_HAS_SIMD && RngMTE_SIMD_X86_SSE2 */
