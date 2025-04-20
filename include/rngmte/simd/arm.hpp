#pragma once
#include "basic.hpp"

#if RngMTE_HAS_SIMD && RngMTE_SIMD_ARM_NEON
#define RngMTE_HAS_SIMD_V128 1

namespace RngMTE
{
  namespace SIMD
  {
    /**/

    template <typename T, size_t N> struct ArmSimdType;
    template <> struct ArmSimdType<int8_t, 16> { using type = int8x16_t; };
    template <> struct ArmSimdType<int16_t, 8> { using type = int16x8_t; };
    template <> struct ArmSimdType<int32_t, 4> { using type = int32x4_t; };
    template <> struct ArmSimdType<int64_t, 2> { using type = int64x2_t; };
    template <> struct ArmSimdType<uint8_t, 16> { using type = uint8x16_t; };
    template <> struct ArmSimdType<uint16_t, 8> { using type = uint16x8_t; };
    template <> struct ArmSimdType<uint32_t, 4> { using type = uint32x4_t; };
    template <> struct ArmSimdType<uint64_t, 2> { using type = uint64x2_t; };

    /**/

    template <typename T> constexpr T vcast128 (T s);
    template <typename T, typename F> constexpr T vcast128 (F s);

    /**/

    template <typename T, size_t N>
    union Register128
    {
      using basic_type = Basic<T, N>;
      using vector_type = typename ArmSimdType<T, N>::type;
      using element_type = T;

      using signed_type = Register128<typename std::make_signed<T>::type, N>;
      using unsigned_type = Register128<typename std::make_unsigned<T>::type, N>;

      static constexpr size_t element_size = sizeof (T);
      static constexpr size_t element_count = N;
      static constexpr bool simd = true;

      basic_type gpr;
      vector_type qreg;

      Register128 () = default;

      constexpr Register128 (T d0) noexcept;
      constexpr Register128 (T d0, T d1) noexcept;
      constexpr Register128 (T d0, T d1, T d2, T d3) noexcept;
      constexpr Register128 (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7) noexcept;
      constexpr Register128 (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7,
                             T d8, T d9, T dA, T dB, T dC, T dD, T dE, T dF) noexcept;

      constexpr Register128 (basic_type s) noexcept;
      constexpr Register128 (vector_type s) noexcept;

      constexpr operator basic_type () const noexcept;
      constexpr operator vector_type () const noexcept;

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

    template <typename T> struct make_v128;

    template <> struct make_v128<int8_t> { using type = s8x16_t; };
    template <> struct make_v128<int16_t> { using type = s16x8_t; };
    template <> struct make_v128<int32_t> { using type = s32x4_t; };
    template <> struct make_v128<int64_t> { using type = s64x2_t; };

    template <> struct make_v128<uint8_t> { using type = u8x16_t; };
    template <> struct make_v128<uint16_t> { using type = u16x8_t; };
    template <> struct make_v128<uint32_t> { using type = u32x4_t; };
    template <> struct make_v128<uint64_t> { using type = u64x2_t; };

    /**/

    template <typename T> struct is_simd_type : std::false_type {};
    template <> struct is_simd_type<int8x16_t> : std::true_type {};
    template <> struct is_simd_type<int16x8_t> : std::true_type {};
    template <> struct is_simd_type<int32x4_t> : std::true_type {};
    template <> struct is_simd_type<int64x2_t> : std::true_type {};
    template <> struct is_simd_type<uint8x16_t> : std::true_type {};
    template <> struct is_simd_type<uint16x8_t> : std::true_type {};
    template <> struct is_simd_type<uint32x4_t> : std::true_type {};
    template <> struct is_simd_type<uint64x2_t> : std::true_type {};

    /**/

    int8x16_t vset1q_n (int8_t d0) noexcept;
    int16x8_t vset1q_n (int16_t d0) noexcept;
    int32x4_t vset1q_n (int32_t d0) noexcept;
    int64x2_t vset1q_n (int64_t d0) noexcept;

    uint8x16_t vset1q_n (uint8_t d0) noexcept;
    uint16x8_t vset1q_n (uint16_t d0) noexcept;
    uint32x4_t vset1q_n (uint32_t d0) noexcept;
    uint64x2_t vset1q_n (uint64_t d0) noexcept;

    int8x16_t vset2q_n (int8_t d0, int8_t d1) noexcept;
    int16x8_t vset2q_n (int16_t d0, int16_t d1) noexcept;
    int32x4_t vset2q_n (int32_t d0, int32_t d1) noexcept;
    int64x2_t vset2q_n (int64_t d0, int64_t d1) noexcept;

    uint8x16_t vset2q_n (uint8_t d0, uint8_t d1) noexcept;
    uint16x8_t vset2q_n (uint16_t d0, uint16_t d1) noexcept;
    uint32x4_t vset2q_n (uint32_t d0, uint32_t d1) noexcept;
    uint64x2_t vset2q_n (uint64_t d0, uint64_t d1) noexcept;

    int8x16_t vset4q_n (int8_t d0, int8_t d1, int8_t d2, int8_t d3) noexcept;
    int16x8_t vset4q_n (int16_t d0, int16_t d1, int16_t d2, int16_t d3) noexcept;
    int32x4_t vset4q_n (int32_t d0, int32_t d1, int32_t d2, int32_t d3) noexcept;

    uint8x16_t vset4q_n (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) noexcept;
    uint16x8_t vset4q_n (uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3) noexcept;
    uint32x4_t vset4q_n (uint32_t d0, uint32_t d1, uint32_t d2, uint32_t d3) noexcept;

    int8x16_t vset8q_n (int8_t d0, int8_t d1, int8_t d2, int8_t d3,
                        int8_t d4, int8_t d5, int8_t d6, int8_t d7) noexcept;
    int16x8_t vset8q_n (int16_t d0, int16_t d1, int16_t d2, int16_t d3,
                        int16_t d4, int16_t d5, int16_t d6, int16_t d7) noexcept;

    uint8x16_t vset8q_n (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                        uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) noexcept;
    uint16x8_t vset8q_n (uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3,
                        uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7) noexcept;

    int8x16_t vset16q_n (int8_t d0, int8_t d1, int8_t d2, int8_t d3,
                         int8_t d4, int8_t d5, int8_t d6, int8_t d7,
                         int8_t d8, int8_t d9, int8_t dA, int8_t dB,
                         int8_t dC, int8_t dD, int8_t dE, int8_t dF) noexcept;

    uint8x16_t vset16q_n (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                          uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                          uint8_t d8, uint8_t d9, uint8_t dA, uint8_t dB,
                          uint8_t dC, uint8_t dD, uint8_t dE, uint8_t dF) noexcept;

    /**/

    int8x16_t vcltq (int8x16_t s) noexcept;
    int16x8_t vcltq (int16x8_t s) noexcept;
    int32x4_t vcltq (int32x4_t s) noexcept;
    int64x2_t vcltq (int64x2_t s) noexcept;

    uint8x16_t vcltq (uint8x16_t s) noexcept;
    uint16x8_t vcltq (uint16x8_t s) noexcept;
    uint32x4_t vcltq (uint32x4_t s) noexcept;
    uint64x2_t vcltq (uint64x2_t s) noexcept;

    /**/

    int8x16_t vcleq (int8x16_t s) noexcept;
    int16x8_t vcleq (int16x8_t s) noexcept;
    int32x4_t vcleq (int32x4_t s) noexcept;
    int64x2_t vcleq (int64x2_t s) noexcept;

    uint8x16_t vcleq (uint8x16_t s) noexcept;
    uint16x8_t vcleq (uint16x8_t s) noexcept;
    uint32x4_t vcleq (uint32x4_t s) noexcept;
    uint64x2_t vcleq (uint64x2_t s) noexcept;

    /**/

    int8x16_t vceqq (int8x16_t s) noexcept;
    int16x8_t vceqq (int16x8_t s) noexcept;
    int32x4_t vceqq (int32x4_t s) noexcept;
    int64x2_t vceqq (int64x2_t s) noexcept;

    uint8x16_t vceqq (uint8x16_t s) noexcept;
    uint16x8_t vceqq (uint16x8_t s) noexcept;
    uint32x4_t vceqq (uint32x4_t s) noexcept;
    uint64x2_t vceqq (uint64x2_t s) noexcept;

    /**/

    int8x16_t vcgeq (int8x16_t s) noexcept;
    int16x8_t vcgeq (int16x8_t s) noexcept;
    int32x4_t vcgeq (int32x4_t s) noexcept;
    int64x2_t vcgeq (int64x2_t s) noexcept;

    uint8x16_t vcgeq (uint8x16_t s) noexcept;
    uint16x8_t vcgeq (uint16x8_t s) noexcept;
    uint32x4_t vcgeq (uint32x4_t s) noexcept;
    uint64x2_t vcgeq (uint64x2_t s) noexcept;

    /**/

    int8x16_t vcgtq (int8x16_t s) noexcept;
    int16x8_t vcgtq (int16x8_t s) noexcept;
    int32x4_t vcgtq (int32x4_t s) noexcept;
    int64x2_t vcgtq (int64x2_t s) noexcept;

    uint8x16_t vcgtq (uint8x16_t s) noexcept;
    uint16x8_t vcgtq (uint16x8_t s) noexcept;
    uint32x4_t vcgtq (uint32x4_t s) noexcept;
    uint64x2_t vcgtq (uint64x2_t s) noexcept;

    /**/

    int8x16_t vmvnq (int8x16_t s) noexcept;
    int16x8_t vmvnq (int16x8_t s) noexcept;
    int32x4_t vmvnq (int32x4_t s) noexcept;
    int64x2_t vmvnq (int64x2_t s) noexcept;

    uint8x16_t vmvnq (uint8x16_t s) noexcept;
    uint16x8_t vmvnq (uint16x8_t s) noexcept;
    uint32x4_t vmvnq (uint32x4_t s) noexcept;
    uint64x2_t vmvnq (uint64x2_t s) noexcept;

    /**/

    int8x16_t vaddq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t vaddq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t vaddq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t vaddq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t vaddq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t vaddq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t vaddq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t vaddq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    int8x16_t vsubq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t vsubq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t vsubq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t vsubq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t vsubq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t vsubq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t vsubq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t vsubq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    int8x16_t vmulq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t vmulq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t vmulq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t vmulq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t vmulq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t vmulq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t vmulq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t vmulq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    int8x16_t vandq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t vandq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t vandq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t vandq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t vandq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t vandq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t vandq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t vandq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    int8x16_t vbicq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t vbicq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t vbicq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t vbicq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t vbicq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t vbicq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t vbicq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t vbicq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    int8x16_t veorq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t veorq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t veorq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t veorq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t veorq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t veorq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t veorq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t veorq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    int8x16_t vorrq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t vorrq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t vorrq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t vorrq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t vorrq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t vorrq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t vorrq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t vorrq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    template <size_t N> int8x16_t vbslq (int8x16_t p, int8x16_t t, int8x16_t f) noexcept;
    template <size_t N> int16x8_t vbslq (int16x8_t p, int16x8_t t, int16x8_t f) noexcept;
    template <size_t N> int32x4_t vbslq (int32x4_t p, int32x4_t t, int32x4_t f) noexcept;
    template <size_t N> int64x2_t vbslq (int64x2_t p, int64x2_t t, int64x2_t f) noexcept;

    template <size_t N> uint8x16_t vbslq (uint8x16_t p, uint8x16_t t, uint8x16_t f) noexcept;
    template <size_t N> uint16x8_t vbslq (uint16x8_t p, uint16x8_t t, uint16x8_t f) noexcept;
    template <size_t N> uint32x4_t vbslq (uint32x4_t p, uint32x4_t t, uint32x4_t f) noexcept;
    template <size_t N> uint64x2_t vbslq (uint64x2_t p, uint64x2_t t, uint64x2_t f) noexcept;

    /**/

    template <size_t N> int8x16_t vshlq_n (int8x16_t s) noexcept;
    template <size_t N> int16x8_t vshlq_n (int16x8_t s) noexcept;
    template <size_t N> int32x4_t vshlq_n (int32x4_t s) noexcept;
    template <size_t N> int64x2_t vshlq_n (int64x2_t s) noexcept;

    template <size_t N> uint8x16_t vshlq_n (uint8x16_t s) noexcept;
    template <size_t N> uint16x8_t vshlq_n (uint16x8_t s) noexcept;
    template <size_t N> uint32x4_t vshlq_n (uint32x4_t s) noexcept;
    template <size_t N> uint64x2_t vshlq_n (uint64x2_t s) noexcept;

    /**/

    int8x16_t vshlq (int8x16_t l, int8x16_t r) noexcept;
    int16x8_t vshlq (int16x8_t l, int16x8_t r) noexcept;
    int32x4_t vshlq (int32x4_t l, int32x4_t r) noexcept;
    int64x2_t vshlq (int64x2_t l, int64x2_t r) noexcept;

    uint8x16_t vshlq (uint8x16_t l, uint8x16_t r) noexcept;
    uint16x8_t vshlq (uint16x8_t l, uint16x8_t r) noexcept;
    uint32x4_t vshlq (uint32x4_t l, uint32x4_t r) noexcept;
    uint64x2_t vshlq (uint64x2_t l, uint64x2_t r) noexcept;

    /**/

    template <size_t N> int8x16_t vshrq_n (int8x16_t s) noexcept;
    template <size_t N> int16x8_t vshrq_n (int16x8_t s) noexcept;
    template <size_t N> int32x4_t vshrq_n (int32x4_t s) noexcept;
    template <size_t N> int64x2_t vshrq_n (int64x2_t s) noexcept;

    template <size_t N> uint8x16_t vshrq_n (uint8x16_t s) noexcept;
    template <size_t N> uint16x8_t vshrq_n (uint16x8_t s) noexcept;
    template <size_t N> uint32x4_t vshrq_n (uint32x4_t s) noexcept;
    template <size_t N> uint64x2_t vshrq_n (uint64x2_t s) noexcept;

    /**/

    template <size_t N> int8x16_t vextq (int8x16_t l, int8x16_t h) noexcept;
    template <size_t N> int16x8_t vextq (int16x8_t l, int16x8_t h) noexcept;
    template <size_t N> int32x4_t vextq (int32x4_t l, int32x4_t h) noexcept;
    template <size_t N> int64x2_t vextq (int64x2_t l, int64x2_t h) noexcept;

    template <size_t N> uint8x16_t vextq (uint8x16_t l, uint8x16_t h) noexcept;
    template <size_t N> uint16x8_t vextq (uint16x8_t l, uint16x8_t h) noexcept;
    template <size_t N> uint32x4_t vextq (uint32x4_t l, uint32x4_t h) noexcept;
    template <size_t N> uint64x2_t vextq (uint64x2_t l, uint64x2_t h) noexcept;

    /**/
  } // SIMD

  /*
   * inline - Register128
   */

  namespace SIMD
  {
    /**/

    template <typename T, size_t N>
    inline constexpr
    Register128<T, N>::Register128 (T d0) noexcept
      : qreg (vset1q_n (d0)) {}

    template <typename T, size_t N>
    inline constexpr
    Register128<T, N>::Register128 (T d0, T d1) noexcept
      : qreg (vset2q_n (d0, d1)) {}

    template <typename T, size_t N>
    inline constexpr
    Register128<T, N>::Register128 (T d0, T d1, T d2, T d3) noexcept
      : qreg (vset4q_n (d0, d1, d2, d3)) {}

    template <typename T, size_t N>
    inline constexpr
    Register128<T, N>::Register128 (T d0, T d1, T d2, T d3,
                                    T d4, T d5, T d6, T d7) noexcept
      : qreg(vset8q_n (d0, d1, d2, d3, d4, d5, d6, d7)) {}

    template <typename T, size_t N>
    inline constexpr
    Register128<T, N>::Register128 (T d0, T d1, T d2, T d3,
                                    T d4, T d5, T d6, T d7,
                                    T d8, T d9, T dA, T dB,
                                    T dC, T dD, T dE, T dF) noexcept
      : qreg(vset16q_n (d0, d1, d2, d3, d4, d5, d6, d7,
                        d8, d9, dA, dB, dC, dD, dE, dF)) {}

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::Register128 (basic_type s) noexcept
      : gpr (s) {}

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::Register128 (vector_type s) noexcept
      : qreg (s) {}

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::operator basic_type () const noexcept
    {
      return gpr;
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>::operator vector_type () const noexcept
    {
      return qreg;
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
      return vmvnq (qreg);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vneg () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vneg ();
      return vsubq (vzero (), qreg);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vclt (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vclt (r);
      return vcltq (qreg, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vcle (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vcle (r);
      return vcleq (qreg, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vceq (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vceq (r);
      return vceqq (qreg, r);
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
      return vcgeq (qreg, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vcgt (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vcgt (r);
      return vcgtq (qreg, r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vadd (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vadd (r);
      return vaddq (qreg, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsub (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vsub (r);
      return vsubq (qreg, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vmul (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vmul (r);
      return vmulq (qreg, r);
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
      return vandq (qreg, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vandn (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vandn (r);
      return vbicq (r, qreg);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vxor (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vxor (r);
      return veorq (qreg, r);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vor (Register128<T, N> r) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vor (r);
      return vorrq (qreg, r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vbsl (Register128<T, N> t, Register128<T, N> f) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vbsl (t, f);
      return vbslq (qreg, t, f);
    }

    /**/

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsll () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template vsll<S> ();
      return vshlq_n<S> (qreg);
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsll (size_t s) const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.vsll (s);
      return vshlq (qreg, vset1q_n (T (s)));
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsrl () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template vsrl<S> ();
      return vshrq_n<S> (unsigned_type (qreg));
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsrl (size_t s) const noexcept
    {
      return gpr.vsrl (s);
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsra () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template vsra<S> ();
      return vshrq_n<S> (signed_type (qreg));
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vsra (size_t s) const noexcept
    {
      return gpr.vsra (s);
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
        return vextq<N - S> (vzero (), qreg);
      return vzero ();
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Register128<T, N>
    Register128<T, N>::esrl () const noexcept
    {
      if (is_constant_evaluated ())
        return gpr.template esrl <S> ();
      if (S < N)
        return vextq<S> (qreg, vzero ());
      return vzero ();
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vzero () noexcept
    {
      if (is_constant_evaluated ())
        return basic_type::vzero ();
      return vset1q_n (T (0));
    }

    template <typename T, size_t N>
    inline constexpr Register128<T, N>
    Register128<T, N>::vones () noexcept
    {
      if (is_constant_evaluated ())
        return basic_type::vones ();
      return vset1q_n (~T (0));
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
      return vextq<S> (l, h);
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
   * inline
   */

  namespace SIMD
  {
    /**/

    template <typename T>
    inline constexpr T
    vcast128 (T s)
    {
      return s;
    }

    template <typename T, typename F>
    inline constexpr T
    vcast128 (F s)
    {
      static_assert (is_simd_type<T>::value, "error");
      static_assert (is_simd_type<F>::value, "error");
      static_assert (sizeof (T) == sizeof (F), "error");

      union cast {
        F t;
        T r;

        constexpr cast (F x) : t (x) {}
        constexpr operator T () const { return r; }
      } u (s);

      return u;
    }

    /**/

    inline int8x16_t vset1q_n (int8_t d0) noexcept { return vdupq_n_s8 (d0); }
    inline int16x8_t vset1q_n (int16_t d0) noexcept { return vdupq_n_s16 (d0); }
    inline int32x4_t vset1q_n (int32_t d0) noexcept { return vdupq_n_s32 (d0); }
    inline int64x2_t vset1q_n (int64_t d0) noexcept { return vdupq_n_s64 (d0); }

    inline uint8x16_t vset1q_n (uint8_t d0) noexcept { return vdupq_n_u8 (d0); }
    inline uint16x8_t vset1q_n (uint16_t d0) noexcept { return vdupq_n_u16 (d0); }
    inline uint32x4_t vset1q_n (uint32_t d0) noexcept { return vdupq_n_u32 (d0); }
    inline uint64x2_t vset1q_n (uint64_t d0) noexcept { return vdupq_n_u64 (d0); }

    /**/

    inline int8x16_t
    vset2q_n (int8_t d0, int8_t d1) noexcept
    {
      return (int8x16_t) {
        d0, d1, d0, d1, d0, d1, d0, d1,
        d0, d1, d0, d1, d0, d1, d0, d1
      };
    }

    inline int16x8_t
    vset2q_n (int16_t d0, int16_t d1) noexcept
    {
      return (int16x8_t) { d0, d1, d0, d1, d0, d1, d0, d1 };
    }

    inline int32x4_t
    vset2q_n (int32_t d0, int32_t d1) noexcept
    {
      return (int32x4_t) { d0, d1, d0, d1 };
    }

    inline int64x2_t
    vset2q_n (int64_t d0, int64_t d1) noexcept
    {
      return (int64x2_t) { d0, d1 };
    }

    inline uint8x16_t
    vset2q_n (uint8_t d0, uint8_t d1) noexcept
    {
      return (uint8x16_t) {
        d0, d1, d0, d1, d0, d1, d0, d1,
        d0, d1, d0, d1, d0, d1, d0, d1
      };
    }

    inline uint16x8_t
    vset2q_n (uint16_t d0, uint16_t d1) noexcept
    {
      return (uint16x8_t) { d0, d1, d0, d1, d0, d1, d0, d1 };
    }

    inline uint32x4_t
    vset2q_n (uint32_t d0, uint32_t d1) noexcept
    {
      return (uint32x4_t) { d0, d1, d0, d1 };
    }

    inline uint64x2_t
    vset2q_n (uint64_t d0, uint64_t d1) noexcept
    {
      return (uint64x2_t) { d0, d1 };
    }

    /**/

    inline int8x16_t
    vset4q_n (int8_t d0, int8_t d1, int8_t d2, int8_t d3) noexcept
    {
      return (int8x16_t) {
        d0, d1, d2, d3, d0, d1, d2, d3,
        d0, d1, d2, d3, d0, d1, d2, d3
      };
    }

    inline int16x8_t
    vset4q_n (int16_t d0, int16_t d1, int16_t d2, int16_t d3) noexcept
    {
      return (int16x8_t) { d0, d1, d2, d3, d0, d1, d2, d3 };
    }

    inline int32x4_t
    vset4q_n (int32_t d0, int32_t d1, int32_t d2, int32_t d3) noexcept
    {
      return (int32x4_t) { d0, d1, d2, d3 };
    }

    inline uint8x16_t
    vset4q_n (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) noexcept
    {
      return (uint8x16_t) {
        d0, d1, d2, d3, d0, d1, d2, d3,
        d0, d1, d2, d3, d0, d1, d2, d3
      };
    }

    inline uint16x8_t
    vset4q_n (uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3) noexcept
    {
      return (uint16x8_t) { d0, d1, d2, d3, d0, d1, d2, d3 };
    }

    inline uint32x4_t
    vset4q_n (uint32_t d0, uint32_t d1, uint32_t d2, uint32_t d3) noexcept
    {
      return (uint32x4_t) { d0, d1, d2, d3 };
    }

    /**/

    inline int8x16_t
    vset8q_n (int8_t d0, int8_t d1, int8_t d2, int8_t d3,
              int8_t d4, int8_t d5, int8_t d6, int8_t d7) noexcept
    {
      return (int8x16_t) {
        d0, d1, d2, d3, d4, d5, d6, d7,
        d0, d1, d2, d3, d4, d5, d6, d7
      };
    }

    inline int16x8_t
    vset8q_n (int16_t d0, int16_t d1, int16_t d2, int16_t d3,
              int16_t d4, int16_t d5, int16_t d6, int16_t d7) noexcept
    {
      return (int16x8_t) { d0, d1, d2, d3, d4, d5, d6, d7 };
    }

    inline uint8x16_t
    vset8q_n (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
              uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) noexcept
    {
      return (uint8x16_t) {
        d0, d1, d2, d3, d4, d5, d6, d7,
        d0, d1, d2, d3, d4, d5, d6, d7
      };
    }

    inline uint16x8_t
    vset8q_n (uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3,
              uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7) noexcept
    {
      return (uint16x8_t) { d0, d1, d2, d3, d4, d5, d6, d7 };
    }

    /**/

    inline int8x16_t
    vset16q_n (int8_t d0, int8_t d1, int8_t d2, int8_t d3,
               int8_t d4, int8_t d5, int8_t d6, int8_t d7,
               int8_t d8, int8_t d9, int8_t dA, int8_t dB,
               int8_t dC, int8_t dD, int8_t dE, int8_t dF) noexcept
    {
      return (int8x16_t) {
        d0, d1, d2, d3, d4, d5, d6, d7,
        d8, d9, dA, dB, dC, dD, dE, dF
      };
    }

    inline uint8x16_t
    vset16q_n (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
               uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
               uint8_t d8, uint8_t d9, uint8_t dA, uint8_t dB,
               uint8_t dC, uint8_t dD, uint8_t dE, uint8_t dF) noexcept
    {
      return (uint8x16_t) {
        d0, d1, d2, d3, d4, d5, d6, d7,
        d8, d9, dA, dB, dC, dD, dE, dF
      };
    }

    /**/

    inline uint8x16_t vcltq (int8x16_t l, int8x16_t r) noexcept { return vcltq_s8 (l, r); }
    inline uint16x8_t vcltq (int16x8_t l, int16x8_t r) noexcept { return vcltq_s16 (l, r); }
    inline uint32x4_t vcltq (int32x4_t l, int32x4_t r) noexcept { return vcltq_s32 (l, r); }
    inline uint64x2_t vcltq (int64x2_t l, int64x2_t r) noexcept { return vcltq_s64 (l, r); }

    inline uint8x16_t vcltq (uint8x16_t l, uint8x16_t r) noexcept { return vcltq_u8 (l, r); }
    inline uint16x8_t vcltq (uint16x8_t l, uint16x8_t r) noexcept { return vcltq_u16 (l, r); }
    inline uint32x4_t vcltq (uint32x4_t l, uint32x4_t r) noexcept { return vcltq_u32 (l, r); }
    inline uint64x2_t vcltq (uint64x2_t l, uint64x2_t r) noexcept { return vcltq_u64 (l, r); }

    /**/

    inline uint8x16_t vcleq (int8x16_t l, int8x16_t r) noexcept { return vcleq_s8 (l, r); }
    inline uint16x8_t vcleq (int16x8_t l, int16x8_t r) noexcept { return vcleq_s16 (l, r); }
    inline uint32x4_t vcleq (int32x4_t l, int32x4_t r) noexcept { return vcleq_s32 (l, r); }
    inline uint64x2_t vcleq (int64x2_t l, int64x2_t r) noexcept { return vcleq_s64 (l, r); }

    inline uint8x16_t vcleq (uint8x16_t l, uint8x16_t r) noexcept { return vcleq_u8 (l, r); }
    inline uint16x8_t vcleq (uint16x8_t l, uint16x8_t r) noexcept { return vcleq_u16 (l, r); }
    inline uint32x4_t vcleq (uint32x4_t l, uint32x4_t r) noexcept { return vcleq_u32 (l, r); }
    inline uint64x2_t vcleq (uint64x2_t l, uint64x2_t r) noexcept { return vcleq_u64 (l, r); }

    /**/

    inline uint8x16_t vceqq (int8x16_t l, int8x16_t r) noexcept { return vceqq_s8 (l, r); }
    inline uint16x8_t vceqq (int16x8_t l, int16x8_t r) noexcept { return vceqq_s16 (l, r); }
    inline uint32x4_t vceqq (int32x4_t l, int32x4_t r) noexcept { return vceqq_s32 (l, r); }
    inline uint64x2_t vceqq (int64x2_t l, int64x2_t r) noexcept { return vceqq_s64 (l, r); }

    inline uint8x16_t vceqq (uint8x16_t l, uint8x16_t r) noexcept { return vceqq_u8 (l, r); }
    inline uint16x8_t vceqq (uint16x8_t l, uint16x8_t r) noexcept { return vceqq_u16 (l, r); }
    inline uint32x4_t vceqq (uint32x4_t l, uint32x4_t r) noexcept { return vceqq_u32 (l, r); }
    inline uint64x2_t vceqq (uint64x2_t l, uint64x2_t r) noexcept { return vceqq_u64 (l, r); }

    /**/

    inline uint8x16_t vcgeq (int8x16_t l, int8x16_t r) noexcept { return vcgeq_s8 (l, r); }
    inline uint16x8_t vcgeq (int16x8_t l, int16x8_t r) noexcept { return vcgeq_s16 (l, r); }
    inline uint32x4_t vcgeq (int32x4_t l, int32x4_t r) noexcept { return vcgeq_s32 (l, r); }
    inline uint64x2_t vcgeq (int64x2_t l, int64x2_t r) noexcept { return vcgeq_s64 (l, r); }

    inline uint8x16_t vcgeq (uint8x16_t l, uint8x16_t r) noexcept { return vcgeq_u8 (l, r); }
    inline uint16x8_t vcgeq (uint16x8_t l, uint16x8_t r) noexcept { return vcgeq_u16 (l, r); }
    inline uint32x4_t vcgeq (uint32x4_t l, uint32x4_t r) noexcept { return vcgeq_u32 (l, r); }
    inline uint64x2_t vcgeq (uint64x2_t l, uint64x2_t r) noexcept { return vcgeq_u64 (l, r); }

    /**/

    inline uint8x16_t vcgtq (int8x16_t l, int8x16_t r) noexcept { return vcgtq_s8 (l, r); }
    inline uint16x8_t vcgtq (int16x8_t l, int16x8_t r) noexcept { return vcgtq_s16 (l, r); }
    inline uint32x4_t vcgtq (int32x4_t l, int32x4_t r) noexcept { return vcgtq_s32 (l, r); }
    inline uint64x2_t vcgtq (int64x2_t l, int64x2_t r) noexcept { return vcgtq_s64 (l, r); }

    inline uint8x16_t vcgtq (uint8x16_t l, uint8x16_t r) noexcept { return vcgtq_u8 (l, r); }
    inline uint16x8_t vcgtq (uint16x8_t l, uint16x8_t r) noexcept { return vcgtq_u16 (l, r); }
    inline uint32x4_t vcgtq (uint32x4_t l, uint32x4_t r) noexcept { return vcgtq_u32 (l, r); }
    inline uint64x2_t vcgtq (uint64x2_t l, uint64x2_t r) noexcept { return vcgtq_u64 (l, r); }

    /**/

    inline int8x16_t vmvnq (int8x16_t s) noexcept { return vmvnq_s8 (s); }
    inline int16x8_t vmvnq (int16x8_t s) noexcept { return vmvnq_s16 (s); }
    inline int32x4_t vmvnq (int32x4_t s) noexcept { return vmvnq_s32 (s); }
    inline int64x2_t vmvnq (int64x2_t s) noexcept { return vcast128<int64x2_t> (vmvnq_s32 (vcast128<int32x4_t> (s))); }

    inline uint8x16_t vmvnq (uint8x16_t s) noexcept { return vmvnq_u8 (s); }
    inline uint16x8_t vmvnq (uint16x8_t s) noexcept { return vmvnq_u16 (s); }
    inline uint32x4_t vmvnq (uint32x4_t s) noexcept { return vmvnq_u32 (s); }
    inline uint64x2_t vmvnq (uint64x2_t s) noexcept { return vcast128<uint64x2_t> (vmvnq_u32 (vcast128<uint32x4_t> (s))); }

    /**/

    inline int8x16_t vaddq (int8x16_t l, int8x16_t r) noexcept { return vaddq_s8 (l, r); }
    inline int16x8_t vaddq (int16x8_t l, int16x8_t r) noexcept { return vaddq_s16 (l, r); }
    inline int32x4_t vaddq (int32x4_t l, int32x4_t r) noexcept { return vaddq_s32 (l, r); }
    inline int64x2_t vaddq (int64x2_t l, int64x2_t r) noexcept { return vaddq_s64 (l, r); }

    inline uint8x16_t vaddq (uint8x16_t l, uint8x16_t r) noexcept { return vaddq_u8 (l, r); }
    inline uint16x8_t vaddq (uint16x8_t l, uint16x8_t r) noexcept { return vaddq_u16 (l, r); }
    inline uint32x4_t vaddq (uint32x4_t l, uint32x4_t r) noexcept { return vaddq_u32 (l, r); }
    inline uint64x2_t vaddq (uint64x2_t l, uint64x2_t r) noexcept { return vaddq_u64 (l, r); }

    /**/

    inline int8x16_t vsubq (int8x16_t l, int8x16_t r) noexcept { return vsubq_s8 (l, r); }
    inline int16x8_t vsubq (int16x8_t l, int16x8_t r) noexcept { return vsubq_s16 (l, r); }
    inline int32x4_t vsubq (int32x4_t l, int32x4_t r) noexcept { return vsubq_s32 (l, r); }
    inline int64x2_t vsubq (int64x2_t l, int64x2_t r) noexcept { return vsubq_s64 (l, r); }

    inline uint8x16_t vsubq (uint8x16_t l, uint8x16_t r) noexcept { return vsubq_u8 (l, r); }
    inline uint16x8_t vsubq (uint16x8_t l, uint16x8_t r) noexcept { return vsubq_u16 (l, r); }
    inline uint32x4_t vsubq (uint32x4_t l, uint32x4_t r) noexcept { return vsubq_u32 (l, r); }
    inline uint64x2_t vsubq (uint64x2_t l, uint64x2_t r) noexcept { return vsubq_u64 (l, r); }

    /**/

    inline int8x16_t vandq (int8x16_t l, int8x16_t r) noexcept { return vandq_s8 (l, r); }
    inline int16x8_t vandq (int16x8_t l, int16x8_t r) noexcept { return vandq_s16 (l, r); }
    inline int32x4_t vandq (int32x4_t l, int32x4_t r) noexcept { return vandq_s32 (l, r); }
    inline int64x2_t vandq (int64x2_t l, int64x2_t r) noexcept { return vandq_s64 (l, r); }

    inline uint8x16_t vandq (uint8x16_t l, uint8x16_t r) noexcept { return vandq_u8 (l, r); }
    inline uint16x8_t vandq (uint16x8_t l, uint16x8_t r) noexcept { return vandq_u16 (l, r); }
    inline uint32x4_t vandq (uint32x4_t l, uint32x4_t r) noexcept { return vandq_u32 (l, r); }
    inline uint64x2_t vandq (uint64x2_t l, uint64x2_t r) noexcept { return vandq_u64 (l, r); }

    /**/

    inline int8x16_t vbicq (int8x16_t l, int8x16_t r) noexcept { return vbicq_s8 (l, r); }
    inline int16x8_t vbicq (int16x8_t l, int16x8_t r) noexcept { return vbicq_s16 (l, r); }
    inline int32x4_t vbicq (int32x4_t l, int32x4_t r) noexcept { return vbicq_s32 (l, r); }
    inline int64x2_t vbicq (int64x2_t l, int64x2_t r) noexcept { return vbicq_s64 (l, r); }

    inline uint8x16_t vbicq (uint8x16_t l, uint8x16_t r) noexcept { return vbicq_u8 (l, r); }
    inline uint16x8_t vbicq (uint16x8_t l, uint16x8_t r) noexcept { return vbicq_u16 (l, r); }
    inline uint32x4_t vbicq (uint32x4_t l, uint32x4_t r) noexcept { return vbicq_u32 (l, r); }
    inline uint64x2_t vbicq (uint64x2_t l, uint64x2_t r) noexcept { return vbicq_u64 (l, r); }

    /**/

    inline int8x16_t veorq (int8x16_t l, int8x16_t r) noexcept { return veorq_s8 (l, r); }
    inline int16x8_t veorq (int16x8_t l, int16x8_t r) noexcept { return veorq_s16 (l, r); }
    inline int32x4_t veorq (int32x4_t l, int32x4_t r) noexcept { return veorq_s32 (l, r); }
    inline int64x2_t veorq (int64x2_t l, int64x2_t r) noexcept { return veorq_s64 (l, r); }

    inline uint8x16_t veorq (uint8x16_t l, uint8x16_t r) noexcept { return veorq_u8 (l, r); }
    inline uint16x8_t veorq (uint16x8_t l, uint16x8_t r) noexcept { return veorq_u16 (l, r); }
    inline uint32x4_t veorq (uint32x4_t l, uint32x4_t r) noexcept { return veorq_u32 (l, r); }
    inline uint64x2_t veorq (uint64x2_t l, uint64x2_t r) noexcept { return veorq_u64 (l, r); }

    /**/

    inline int8x16_t vorrq (int8x16_t l, int8x16_t r) noexcept { return vorrq_s8 (l, r); }
    inline int16x8_t vorrq (int16x8_t l, int16x8_t r) noexcept { return vorrq_s16 (l, r); }
    inline int32x4_t vorrq (int32x4_t l, int32x4_t r) noexcept { return vorrq_s32 (l, r); }
    inline int64x2_t vorrq (int64x2_t l, int64x2_t r) noexcept { return vorrq_s64 (l, r); }

    inline uint8x16_t vorrq (uint8x16_t l, uint8x16_t r) noexcept { return vorrq_u8 (l, r); }
    inline uint16x8_t vorrq (uint16x8_t l, uint16x8_t r) noexcept { return vorrq_u16 (l, r); }
    inline uint32x4_t vorrq (uint32x4_t l, uint32x4_t r) noexcept { return vorrq_u32 (l, r); }
    inline uint64x2_t vorrq (uint64x2_t l, uint64x2_t r) noexcept { return vorrq_u64 (l, r); }

    /**/

    inline int8x16_t vbslq (uint8x16_t p, int8x16_t t, int8x16_t f) noexcept { return vbslq_s8 (p, t, f); }
    inline int16x8_t vbslq (uint16x8_t p, int16x8_t t, int16x8_t f) noexcept { return vbslq_s16 (p, t, f); }
    inline int32x4_t vbslq (uint32x4_t p, int32x4_t t, int32x4_t f) noexcept { return vbslq_s32 (p, t, f); }
    inline int64x2_t vbslq (uint64x2_t p, int64x2_t t, int64x2_t f) noexcept { return vbslq_s64 (p, t, f); }

    inline uint8x16_t vbslq (uint8x16_t p, uint8x16_t t, uint8x16_t f) noexcept { return vbslq_u8 (p, t, f); }
    inline uint16x8_t vbslq (uint16x8_t p, uint16x8_t t, uint16x8_t f) noexcept { return vbslq_u16 (p, t, f); }
    inline uint32x4_t vbslq (uint32x4_t p, uint32x4_t t, uint32x4_t f) noexcept { return vbslq_u32 (p, t, f); }
    inline uint64x2_t vbslq (uint64x2_t p, uint64x2_t t, uint64x2_t f) noexcept { return vbslq_u64 (p, t, f); }

    /**/

    template <size_t N> inline int8x16_t vbslq (int8x16_t p, int8x16_t t, int8x16_t f) noexcept { return vbslq_s8 (vcast128<uint8x16_t> (p), t, f); }
    template <size_t N> inline int16x8_t vbslq (int16x8_t p, int16x8_t t, int16x8_t f) noexcept { return vbslq_s16 (vcast128<uint16x8_t> (p), t, f); }
    template <size_t N> inline int32x4_t vbslq (int32x4_t p, int32x4_t t, int32x4_t f) noexcept { return vbslq_s32 (vcast128<uint32x4_t> (p), t, f); }
    template <size_t N> inline int64x2_t vbslq (int64x2_t p, int64x2_t t, int64x2_t f) noexcept { return vbslq_s64 (vcast128<uint64x2_t> (p), t, f); }

    template <size_t N> inline uint8x16_t vbslq (uint8x16_t p, uint8x16_t t, uint8x16_t f) noexcept { return vbslq_u8 (p, t, f); }
    template <size_t N> inline uint16x8_t vbslq (uint16x8_t p, uint16x8_t t, uint16x8_t f) noexcept { return vbslq_u16 (p, t, f); }
    template <size_t N> inline uint32x4_t vbslq (uint32x4_t p, uint32x4_t t, uint32x4_t f) noexcept { return vbslq_u32 (p, t, f); }
    template <size_t N> inline uint64x2_t vbslq (uint64x2_t p, uint64x2_t t, uint64x2_t f) noexcept { return vbslq_u64 (p, t, f); }

    /**/

    template <size_t N> inline int8x16_t vshlq_n (int8x16_t s) noexcept { return vshlq_n_s8 (s, N); }
    template <size_t N> inline int16x8_t vshlq_n (int16x8_t s) noexcept { return vshlq_n_s16 (s, N); }
    template <size_t N> inline int32x4_t vshlq_n (int32x4_t s) noexcept { return vshlq_n_s32 (s, N); }
    template <size_t N> inline int64x2_t vshlq_n (int64x2_t s) noexcept { return vshlq_n_s64 (s, N); }

    template <size_t N> inline uint8x16_t vshlq_n (uint8x16_t s) noexcept { return vshlq_n_u8 (s, N); }
    template <size_t N> inline uint16x8_t vshlq_n (uint16x8_t s) noexcept { return vshlq_n_u16 (s, N); }
    template <size_t N> inline uint32x4_t vshlq_n (uint32x4_t s) noexcept { return vshlq_n_u32 (s, N); }
    template <size_t N> inline uint64x2_t vshlq_n (uint64x2_t s) noexcept { return vshlq_n_u64 (s, N); }

    /**/

    inline int8x16_t vshlq (int8x16_t l, int8x16_t r) noexcept { return vshlq_s8 (l, r); }
    inline int16x8_t vshlq (int16x8_t l, int16x8_t r) noexcept { return vshlq_s16 (l, r); }
    inline int32x4_t vshlq (int32x4_t l, int32x4_t r) noexcept { return vshlq_s32 (l, r); }
    inline int64x2_t vshlq (int64x2_t l, int64x2_t r) noexcept { return vshlq_s64 (l, r); }

    inline uint8x16_t vshlq (uint8x16_t l, int8x16_t r) noexcept { return vshlq_u8 (l, r); }
    inline uint16x8_t vshlq (uint16x8_t l, int16x8_t r) noexcept { return vshlq_u16 (l, r); }
    inline uint32x4_t vshlq (uint32x4_t l, int32x4_t r) noexcept { return vshlq_u32 (l, r); }
    inline uint64x2_t vshlq (uint64x2_t l, int64x2_t r) noexcept { return vshlq_u64 (l, r); }

    /**/

    template <size_t N> inline int8x16_t vshrq_n (int8x16_t s) noexcept { return vshrq_n_s8 (s, N); }
    template <size_t N> inline int16x8_t vshrq_n (int16x8_t s) noexcept { return vshrq_n_s16 (s, N); }
    template <size_t N> inline int32x4_t vshrq_n (int32x4_t s) noexcept { return vshrq_n_s32 (s, N); }
    template <size_t N> inline int64x2_t vshrq_n (int64x2_t s) noexcept { return vshrq_n_s64 (s, N); }

    template <size_t N> inline uint8x16_t vshrq_n (uint8x16_t s) noexcept { return vshrq_n_u8 (s, N); }
    template <size_t N> inline uint16x8_t vshrq_n (uint16x8_t s) noexcept { return vshrq_n_u16 (s, N); }
    template <size_t N> inline uint32x4_t vshrq_n (uint32x4_t s) noexcept { return vshrq_n_u32 (s, N); }
    template <size_t N> inline uint64x2_t vshrq_n (uint64x2_t s) noexcept { return vshrq_n_u64 (s, N); }

    /**/

    template <size_t N> inline int8x16_t vextq (int8x16_t l, int8x16_t h) noexcept { return vextq_s8  (l, h, N); }
    template <size_t N> inline int16x8_t vextq (int16x8_t l, int16x8_t h) noexcept { return vextq_s16 (l, h, N); }
    template <size_t N> inline int32x4_t vextq (int32x4_t l, int32x4_t h) noexcept { return vextq_s32 (l, h, N); }
    template <size_t N> inline int64x2_t vextq (int64x2_t l, int64x2_t h) noexcept { return vextq_s64 (l, h, N); }

    template <size_t N> inline uint8x16_t vextq (uint8x16_t l, uint8x16_t h) noexcept { return vextq_u8  (l, h, N); }
    template <size_t N> inline uint16x8_t vextq (uint16x8_t l, uint16x8_t h) noexcept { return vextq_u16 (l, h, N); }
    template <size_t N> inline uint32x4_t vextq (uint32x4_t l, uint32x4_t h) noexcept { return vextq_u32 (l, h, N); }
    template <size_t N> inline uint64x2_t vextq (uint64x2_t l, uint64x2_t h) noexcept { return vextq_u64 (l, h, N); }

    /**/
  } // SIMD
} // RngMTE

#endif /* RngMTE_HAS_SIMD && RngMTE_SIMD_ARM_NEON */
