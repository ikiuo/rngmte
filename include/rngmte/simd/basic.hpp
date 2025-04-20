#pragma once
#include "../std.hpp"

namespace RngMTE
{
  namespace SIMD
  {
    /**/

    template <typename T, size_t N>
    struct Basic
    {
      using basic_type = Basic<T, N>;
      using element_type = T;

      static constexpr size_t element_size = sizeof (T);
      static constexpr size_t element_count = N;
      static constexpr bool simd = false;

      T elem[N];

      Basic () = default;

      constexpr Basic (T d0) noexcept;
      constexpr Basic (T d0, T d1) noexcept;
      constexpr Basic (T d0, T d1, T d2, T d3) noexcept;
      constexpr Basic (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7) noexcept;
      constexpr Basic (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7,
                       T d8, T d9, T dA, T dB, T dC, T dD, T dE, T dF) noexcept;
      constexpr Basic (T d00, T d01, T d02, T d03, T d04, T d05, T d06, T d07,
                       T d08, T d09, T d0A, T d0B, T d0C, T d0D, T d0E, T d0F,
                       T d10, T d11, T d12, T d13, T d14, T d15, T d16, T d17,
                       T d18, T d19, T d1A, T d1B, T d1C, T d1D, T d1E, T d1F) noexcept;

      constexpr Basic<T, N> operator ~ () const noexcept;
      constexpr Basic<T, N> operator - () const noexcept;

      constexpr Basic<T, N> operator <  (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator <= (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator == (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator != (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator >= (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator >  (Basic<T, N> r) const noexcept;

      constexpr Basic<T, N> operator + (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator - (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator * (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator / (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator % (Basic<T, N> r) const noexcept;

      constexpr Basic<T, N> operator & (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator ^ (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> operator | (Basic<T, N> r) const noexcept;

      constexpr Basic<T, N> operator << (size_t r) const noexcept;
      constexpr Basic<T, N> operator >> (size_t r) const noexcept;

      constexpr T get (size_t n) const noexcept;
      constexpr void set (size_t n, T r) noexcept;

      template <typename F> constexpr Basic<T, N> op_unary (F op) const noexcept;
      template <typename F> constexpr Basic<T, N> op_binary (Basic<T, N> r, F op) const noexcept;

      constexpr Basic<T, N> vnot () const noexcept;
      constexpr Basic<T, N> vneg () const noexcept;

      constexpr Basic<T, N> vclt (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vcle (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vceq (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vcne (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vcge (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vcgt (Basic<T, N> r) const noexcept;

      constexpr Basic<T, N> vadd (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vsub (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vmul (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vdiv (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vmod (Basic<T, N> r) const noexcept;

      constexpr Basic<T, N> vand (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vandn (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vxor (Basic<T, N> r) const noexcept;
      constexpr Basic<T, N> vor (Basic<T, N> r) const noexcept;

      constexpr Basic<T, N> vbsl (Basic<T, N> t, Basic<T, N> f) const noexcept;

      template <size_t S> constexpr Basic<T, N> vsll () const noexcept;
      constexpr Basic<T, N> vsll (size_t s) const noexcept;
      template <size_t S> constexpr Basic<T, N> vsrl () const noexcept;
      constexpr Basic<T, N> vsrl (size_t s) const noexcept;
      template <size_t S> constexpr Basic<T, N> vsra () const noexcept;
      constexpr Basic<T, N> vsra (size_t s) const noexcept;

      template <size_t S> constexpr Basic<T, N> esll () const noexcept;
      template <size_t S> constexpr Basic<T, N> esrl () const noexcept;

      /**/

      static constexpr Basic<T, N> vzero () noexcept;
      static constexpr Basic<T, N> vones () noexcept;

      template <size_t S> static constexpr Basic<T, N> extr (Basic<T, N> l, Basic<T, N>  h) noexcept;

      /**/

      using iterator = T *;
      using const_iterator = const T *;

      constexpr iterator begin () noexcept;
      constexpr iterator end () noexcept;
      constexpr const_iterator cbegin () const noexcept;
      constexpr const_iterator cend () const noexcept;
      static constexpr size_t size () noexcept;

      /**/

      static constexpr Basic<T, N> *bind (void *p) noexcept;
      static constexpr const Basic<T, N> *bind (const void *p) noexcept;

      static constexpr Basic<T, N> load (const void *p) noexcept;
    };
  } // SIMD

  /*
   * inline
   */

  namespace SIMD
  {
    /**/

    template <typename T, size_t N>
    inline constexpr
    Basic<T, N>::Basic (T d0) noexcept
      : elem ()
    {
      for (size_t i = 0; i < N; ++i)
        set (i, d0);
    }

    template <typename T, size_t N>
    inline constexpr
    Basic<T, N>::Basic (T d0, T d1) noexcept
      : elem ()
    {
      constexpr size_t R = N % 2;

      for (size_t i = 0; i < N - R; i += 2)
        {
          set (i + 0, d0);
          set (i + 1, d1);
        }
      if (R > 0) set (N - R + 0, d0);
    }

    template <typename T, size_t N>
    inline constexpr
    Basic<T, N>::Basic (T d0, T d1, T d2, T d3) noexcept
      : elem ()
    {
      constexpr size_t R = N % 4;

      for (size_t i = 0; i < N - R; i += 4)
        {
          set (i + 0, d0);
          set (i + 1, d1);
          set (i + 2, d2);
          set (i + 3, d3);
        }
      if (R > 0) set (N - R + 0, d0);
      if (R > 1) set (N - R + 1, d1);
      if (R > 2) set (N - R + 2, d2);
    }

    template <typename T, size_t N>
    inline constexpr
    Basic<T, N>::Basic (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7) noexcept
      : elem ()
    {
      constexpr size_t R = N % 8;

      for (size_t i = 0; i < N - R; i += 8)
        {
          set (i + 0, d0);
          set (i + 1, d1);
          set (i + 2, d2);
          set (i + 3, d3);
          set (i + 4, d4);
          set (i + 5, d5);
          set (i + 6, d6);
          set (i + 7, d7);
        }
      if (R > 0) set (N - R + 0, d0);
      if (R > 1) set (N - R + 1, d1);
      if (R > 2) set (N - R + 2, d2);
      if (R > 3) set (N - R + 3, d3);
      if (R > 4) set (N - R + 4, d4);
      if (R > 5) set (N - R + 5, d5);
      if (R > 6) set (N - R + 6, d6);
    }

    template <typename T, size_t N>
    inline constexpr
    Basic<T, N>::Basic (T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7,
                        T d8, T d9, T dA, T dB, T dC, T dD, T dE, T dF) noexcept
      : elem ()
    {
      constexpr size_t R = N % 16;

      for (size_t i = 0; i < N - R; i += 16)
        {
          set (i +  0, d0);
          set (i +  1, d1);
          set (i +  2, d2);
          set (i +  3, d3);
          set (i +  4, d4);
          set (i +  5, d5);
          set (i +  6, d6);
          set (i +  7, d7);
          set (i +  8, d8);
          set (i +  9, d9);
          set (i + 10, dA);
          set (i + 11, dB);
          set (i + 12, dC);
          set (i + 13, dD);
          set (i + 14, dE);
          set (i + 15, dF);
        }
      if (R >  0) set (N - R +  0, d0);
      if (R >  1) set (N - R +  1, d1);
      if (R >  2) set (N - R +  2, d2);
      if (R >  3) set (N - R +  3, d3);
      if (R >  4) set (N - R +  4, d4);
      if (R >  5) set (N - R +  5, d5);
      if (R >  6) set (N - R +  6, d6);
      if (R >  7) set (N - R +  7, d7);
      if (R >  8) set (N - R +  8, d8);
      if (R >  9) set (N - R +  9, d9);
      if (R > 10) set (N - R + 10, dA);
      if (R > 11) set (N - R + 11, dB);
      if (R > 12) set (N - R + 12, dC);
      if (R > 13) set (N - R + 13, dD);
      if (R > 14) set (N - R + 14, dE);
    }

    template <typename T, size_t N>
    inline constexpr
    Basic<T, N>::Basic (T d00, T d01, T d02, T d03, T d04, T d05, T d06, T d07,
                        T d08, T d09, T d0A, T d0B, T d0C, T d0D, T d0E, T d0F,
                        T d10, T d11, T d12, T d13, T d14, T d15, T d16, T d17,
                        T d18, T d19, T d1A, T d1B, T d1C, T d1D, T d1E, T d1F) noexcept
      : elem ()
    {
      constexpr size_t R = N % 32;

      for (size_t i = 0; i < N - R; i += 32)
        {
          set (i +  0, d00);
          set (i +  1, d01);
          set (i +  2, d02);
          set (i +  3, d03);
          set (i +  4, d04);
          set (i +  5, d05);
          set (i +  6, d06);
          set (i +  7, d07);
          set (i +  8, d08);
          set (i +  9, d09);
          set (i + 10, d0A);
          set (i + 11, d0B);
          set (i + 12, d0C);
          set (i + 13, d0D);
          set (i + 14, d0E);
          set (i + 15, d0F);
          set (i + 16, d10);
          set (i + 17, d11);
          set (i + 18, d12);
          set (i + 19, d13);
          set (i + 20, d14);
          set (i + 21, d15);
          set (i + 22, d16);
          set (i + 23, d17);
          set (i + 24, d18);
          set (i + 25, d19);
          set (i + 26, d1A);
          set (i + 27, d1B);
          set (i + 28, d1C);
          set (i + 29, d1D);
          set (i + 30, d1E);
          set (i + 31, d1F);
        }
      if (R >  0) set (N - R +  0, d00);
      if (R >  1) set (N - R +  1, d01);
      if (R >  2) set (N - R +  2, d02);
      if (R >  3) set (N - R +  3, d03);
      if (R >  4) set (N - R +  4, d04);
      if (R >  5) set (N - R +  5, d05);
      if (R >  6) set (N - R +  6, d06);
      if (R >  7) set (N - R +  7, d07);
      if (R >  8) set (N - R +  8, d08);
      if (R >  9) set (N - R +  9, d09);
      if (R > 10) set (N - R + 10, d0A);
      if (R > 11) set (N - R + 11, d0B);
      if (R > 12) set (N - R + 12, d0C);
      if (R > 13) set (N - R + 13, d0D);
      if (R > 14) set (N - R + 14, d0E);
      if (R > 15) set (N - R + 15, d0F);
      if (R > 16) set (N - R + 16, d10);
      if (R > 17) set (N - R + 17, d11);
      if (R > 18) set (N - R + 18, d12);
      if (R > 19) set (N - R + 19, d13);
      if (R > 20) set (N - R + 20, d14);
      if (R > 21) set (N - R + 21, d15);
      if (R > 22) set (N - R + 22, d16);
      if (R > 23) set (N - R + 23, d17);
      if (R > 24) set (N - R + 24, d18);
      if (R > 25) set (N - R + 25, d19);
      if (R > 26) set (N - R + 26, d1A);
      if (R > 27) set (N - R + 27, d1B);
      if (R > 28) set (N - R + 28, d1C);
      if (R > 29) set (N - R + 29, d1D);
      if (R > 30) set (N - R + 30, d1E);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator ~ () const noexcept
    {
      return vnot ();
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator - () const noexcept
    {
      return vneg ();
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator < (Basic<T, N> r) const noexcept
    {
      return vclt (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator <= (Basic<T, N> r) const noexcept
    {
      return vcle (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator == (Basic<T, N> r) const noexcept
    {
      return vceq (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator != (Basic<T, N> r) const noexcept
    {
      return vcne (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator >= (Basic<T, N> r) const noexcept
    {
      return vcge (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator > (Basic<T, N> r) const noexcept
    {
      return vcgt (r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator + (Basic<T, N> r) const noexcept
    {
      return vadd (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator - (Basic<T, N> r) const noexcept
    {
      return vsub (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator * (Basic<T, N> r) const noexcept
    {
      return vmul (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator / (Basic<T, N> r) const noexcept
    {
      return vdiv (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator % (Basic<T, N> r) const noexcept
    {
      return vmod (r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator & (Basic<T, N> r) const noexcept
    {
      return vand (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator ^ (Basic<T, N> r) const noexcept
    {
      return vxor (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator | (Basic<T, N> r) const noexcept
    {
      return vor (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator << (size_t r) const noexcept
    {
      return vsll (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::operator >> (size_t r) const noexcept
    {
      return vsra (r);
    }

    /**/

    template <typename T, size_t N>
    inline constexpr T
    Basic<T, N>::get (size_t n) const noexcept
    {
      return elem[n];
    }

    template <typename T, size_t N>
    inline constexpr void
    Basic<T, N>::set (size_t n, T r) noexcept
    {
      elem[n] = r;
    }

    /**/

    template <typename T, size_t N>
    template <typename F>
    inline constexpr Basic<T, N>
    Basic<T, N>::op_unary (F op) const noexcept
    {
      Basic<T, N> v (0);

      for (size_t i = 0; i < N; ++i)
        v.set (i, op (get (i)));
      return v;
    }

    template <typename T, size_t N>
    template <typename F>
    inline constexpr Basic<T, N>
    Basic<T, N>::op_binary (Basic<T, N> r, F op) const noexcept
    {
      Basic<T, N> v (0);

      for (size_t i = 0; i < N; ++i)
        v.set (i, op (get (i), r.get (i)));
      return v;
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vnot () const noexcept
    {
      return op_unary (std::bit_not<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vneg () const noexcept
    {
      return op_unary (std::negate<T> ());
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vclt (Basic<T, N> r) const noexcept
    {
      return op_binary(r, [] (T s, T u) { return s < u ? T (-1) : T (0); });
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vcle (Basic<T, N> r) const noexcept
    {
      return op_binary(r, [] (T s, T u) { return s <= u ? T (-1) : T (0); });
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vceq (Basic<T, N> r) const noexcept
    {
      return op_binary(r, [] (T s, T u) { return s == u ? T (-1) : T (0); });
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vcne (Basic<T, N> r) const noexcept
    {
      return op_binary(r, [] (T s, T u) { return s != u ? T (-1) : T (0); });
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vcge (Basic<T, N> r) const noexcept
    {
      return op_binary(r, [] (T s, T u) { return s >= u ? T (-1) : T (0); });
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vcgt (Basic<T, N> r) const noexcept
    {
      return op_binary(r, [] (T s, T u) { return s > u ? T (-1) : T (0); });
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vadd (Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::plus<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vsub (Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::minus<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vmul (Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::multiplies<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vdiv (Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::divides<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vmod (Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::modulus<T> ());
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vand(Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::bit_and<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vandn (Basic<T, N> r) const noexcept
    {
      return vnot ().vand (r);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vxor (Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::bit_xor<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vor(Basic<T, N> r) const noexcept
    {
      return op_binary (r, std::bit_or<T> ());
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vbsl (Basic<T, N> t, Basic<T, N> f) const noexcept
    {
      return vand (t).vor (vandn (f));
    }

    /**/

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Basic<T, N>
    Basic<T, N>::vsll () const noexcept
    {
      return vsll (S);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vsll (size_t s) const noexcept
    {
      Basic<T, N> v (0);

      for (size_t i = 0; i < N; ++i)
        v.set (i, get (i) << s);
      return v;
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Basic<T, N>
    Basic<T, N>::vsrl () const noexcept
    {
      return vsra<S> ();
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vsrl (size_t s) const noexcept
    {
      return vsra (s);
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Basic<T, N>
    Basic<T, N>::vsra () const noexcept
    {
      return vsra (S);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vsra (size_t s) const noexcept
    {
      Basic<T, N> v (0);

      for (size_t i = 0; i < N; ++i)
        v.set (i, get (i) >> s);
      return v;
    }

    /**/

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Basic<T, N>
    Basic<T, N>::esll () const noexcept
    {
      Basic<T, N> v (0);

      for (size_t i = 0; i < S; ++i)
        v.set (i, 0);
      for (size_t i = S; i < N; ++i)
        v.set (i, get (i - S));
      return v;
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Basic<T, N>
    Basic<T, N>::esrl () const noexcept
    {
      if (S >= N)
        return vzero ();

      constexpr size_t W = N - std::min (S, N);
      Basic<T, N> v (0);

      for (size_t i = 0; i < W; ++i)
        v.set (i, get (i + S));
      for (size_t i = W; i < N; ++i)
        v.set (i, 0);
      return v;
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vzero () noexcept
    {
      return Basic<T, N> (0);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::vones () noexcept
    {
      return Basic<T, N> (~T (0));
    }

    template <typename T, size_t N>
    template <size_t S>
    inline constexpr Basic<T, N>
    Basic<T, N>::extr (Basic<T, N> l, Basic<T, N>  h) noexcept
    {
      constexpr size_t H = S - std::min (S, N);
      constexpr size_t U = N - std::min (S, N);

      if (S >= N * 2)
        return vzero ();
      if (S > N)
        return h.esrl<H> ();
      if (S == N)
        return h;
      if (S == 0)
        return l;

      Basic<T, N> v = vzero ();

      for (size_t i = S; i < N; ++i)
        v.set (i - S, l.get (i));
      for (size_t i = 0; i < S; ++i)
        v.set (i + U, h.get (i));
      return v;
    }

    /**/

    template <typename T, size_t N>
    inline constexpr typename Basic<T, N>::iterator
    Basic<T, N>::begin () noexcept
    {
      return elem;
    }

    template <typename T, size_t N>
    inline constexpr typename Basic<T, N>::iterator
    Basic<T, N>::end () noexcept
    {
      return elem + N;
    }

    /**/

    template <typename T, size_t N>
    inline constexpr typename Basic<T, N>::const_iterator
    Basic<T, N>::cbegin () const noexcept
    {
      return elem;
    }

    template <typename T, size_t N>
    inline constexpr typename Basic<T, N>::const_iterator
    Basic<T, N>::cend () const noexcept
    {
      return elem + N;
    }

    /**/

    template <typename T, size_t N>
    inline constexpr size_t
    Basic<T, N>::size () noexcept
    {
      return N;
    }

    /**/

    template <typename T, size_t N>
    inline constexpr Basic<T, N> *
    Basic<T, N>::bind (void *p) noexcept
    {
      return reinterpret_cast<Basic<T, N> *>(p);
    }

    template <typename T, size_t N>
    inline constexpr const Basic<T, N> *
    Basic<T, N>::bind (const void *p) noexcept
    {
      return reinterpret_cast<const Basic<T, N> *>(p);
    }

    template <typename T, size_t N>
    inline constexpr Basic<T, N>
    Basic<T, N>::load (const void *p) noexcept
    {
      return *bind (p);
    }

    /**/
  } // SIMD

} // RngMTE
