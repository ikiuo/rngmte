#pragma once
#include "rngmte/simd.hpp"

namespace RngMTE
{
  /**/

  template <typename UIntType,
            size_t MEXP, size_t POS1,
            size_t SL1, size_t SL2, size_t SR1, size_t SR2,
            size_t MSK1, size_t MSK2, size_t MSK3, size_t MSK4,
            size_t PAR1, size_t PAR2, size_t PAR3, size_t PAR4>
  class RngSFMTE;

  using RngSFMT19937 = RngSFMTE<
    uint32_t, 19937, 122, 18, 1, 11, 1,
    0xdfffffef, 0xddfecb7f, 0xbffaffff, 0xbffffff6,
    0x00000001, 0x00000000, 0x00000000, 0x13c9e684>;

  using RngSFMT19937_64 = RngSFMTE<
    uint64_t, 19937, 122, 18, 1, 11, 1,
    0xdfffffef, 0xddfecb7f, 0xbffaffff, 0xbffffff6,
    0x00000001, 0x00000000, 0x00000000, 0x13c9e684>;

  /*
   *
   */

  template <typename UIntType, size_t MEXP, size_t POS1,
            size_t SL1, size_t SL2, size_t SR1, size_t SR2,
            size_t MSK1, size_t MSK2, size_t MSK3, size_t MSK4,
            size_t PAR1, size_t PAR2, size_t PAR3, size_t PAR4>
  class RngSFMTE
  {
    using self = RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
                          MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4>;

    using v128_t = SIMD::V128;
    using u8v_t = typename v128_t::u8v_t;
    using u32v_t = typename v128_t::u32v_t;
    using u64v_t = typename v128_t::u64v_t;

    using ull_type = unsigned long long;

    static_assert (std::is_unsigned<UIntType>::value, "bad UIntType");


    static constexpr size_t NST = (MEXP >> 7) + 1;
    static constexpr size_t NDW = NST * 4;
    static constexpr size_t NDQ = NST * 2;

    static constexpr size_t UBITS = std::numeric_limits<UIntType>::digits;
    static constexpr bool FLAG_BIG_ENDIAN = RngMTE_BIG_ENDIAN;
    static constexpr bool FLAG_LITTLE_ENDIAN = RngMTE_LITTLE_ENDIAN;
    static constexpr bool FLAG_DWORD = UBITS <= 32;
    static constexpr bool FLAG_QWORD = !FLAG_DWORD;
    static constexpr bool FLAG_BLOCK = true;

    alignas (128) uint32_t state[NDW];
    size_t index;

  public:
    using result_type = UIntType;

    static constexpr result_type default_seed = 5489u;

    inline static constexpr result_type min () { return 0; }
    inline static constexpr result_type max () { return ~(result_type (0)); }

    inline RngSFMTE () : RngSFMTE (default_seed) {}
    inline RngSFMTE (UIntType seed) { set_seed (seed); };
    template <typename K> inline RngSFMTE (K &key) { set_seed (key); }

    inline void seed (UIntType value = default_seed) { set_seed (value); }
    template <typename K> inline void seed (K &key) { set_seed (key); }

    inline result_type operator () () { return generate (); }

    inline void
    discard (unsigned long long n)
    {
      if (FLAG_BLOCK)
        discard_stat (n);
    }

  protected:

    template <bool B>
    inline void
    shuf_seed (size_t i, uint32_t key = 0)
    {
      constexpr size_t L = (NDW < 39) ? 3 : (NDW < 68) ? 5 : (NDW < 623) ? 7 : 11;
      constexpr size_t M = (NDW - L) >> 1;

      size_t ic = i - (i < NDW ? 0 : NDW);
      size_t il = ic + L + M;
      size_t im = ic + M;
      size_t ip = ic + NDW - 1;

      uint32_t &dc = state[ic];
      uint32_t &dl = state[il - (il < NDW ? 0 : NDW)];
      uint32_t &dm = state[im - (im < NDW ? 0 : NDW)];
      uint32_t &dp = state[ip - (ip < NDW ? 0 : NDW)];
      uint32_t r, x;

      if (!B)
        {
          x = dc ^ dm ^ dp;
          r = (x ^ (x >> 27)) * 1664525;
          dm += r;
          r += key + i;
          dl += r;
        }
      else
        {
          x = dc + dm + dp;
          r = (x ^ (x >> 27)) * 1566083941;
          dm ^= r;
          r -= NDW;
          dl ^= r;
        }
      dp = r;
    }

    void
    set_seed (UIntType value)
    {
      uint32_t s = uint32_t (value);

      state[0] = s;
      for (uint32_t i = 1; i < NDW; ++i)
        state[i] = s = UINT32_C(1812433253) * (s ^ (s >> 30)) + i;
      fin_seed ();
    }

    template <typename K>
    void
    set_seed (K &key)
    {
      uint32_t seq[1 + NDW];

      seq[0] = NDW;
      key.generate (seq + 1, seq + 1 + NDW);

      for (size_t i = 0; i < NDW; ++i)
        state[i] = 0x8b8b8b8b;
      for (size_t i = 0; i < NDW + 1; ++i)
        shuf_seed<false> (i, key[i]);
      for (size_t i = 1; i < NDW + 1; ++i)
        shuf_seed<true> (i);

      fin_seed ();
    }

    inline void
    fin_seed ()
    {
      u32v_t mask (PAR1, PAR2, PAR3, PAR4);
      v128_t m (v128_t::load (state) & mask);
      v128_t x (m ^ m.bsrl<8> ());

      if (is_parity (x.uq.get (0))) /*NOOP*/;
      else if (PAR1) state[0] ^= PAR1 & -PAR1;
      else if (PAR2) state[1] ^= PAR2 & -PAR2;
      else if (PAR3) state[2] ^= PAR3 & -PAR3;
      else if (PAR4) state[3] ^= PAR4 & -PAR4;

      index = NDW;
    }

    inline v128_t
    recursion (v128_t cur, v128_t pos, v128_t old, v128_t pre)
    {
      u32v_t mask (MSK1, MSK2, MSK3, MSK4);
      v128_t sl2 = cur.bsll<SL2> ();
      v128_t sr2 = old.bsrl<SR2> ();
      v128_t sr1 = pos.vsrld<SR1> () & mask;
      v128_t sl1 = pre.vslld<SL1> ();

      return cur ^ sl1 ^ sl2 ^ sr1 ^ sr2;
    }

    void
    twist ()
    {
      v128_t *p = v128_t::bind (state);
      v128_t *e1 = p + NST - POS1;
      v128_t *e2 = p + NST;
      v128_t old = p[NST - 2];
      v128_t pre = p[NST - 1];
      v128_t cur;

      do
        {
          *p = cur = recursion (*p, *(p + POS1), old, pre);
          old = pre;
          pre = cur;
        }
      while (++p < e1);

      do
        {
          *p = cur = recursion (*p, *(p + POS1 - NST), old, pre);
          old = pre;
          pre = cur;
        }
      while (++p < e2);
    }

    inline result_type
    generate ()
    {
      RngMTE_unlikely_if (index >= NDW)
        {
          twist ();
          index = 0;
        }
      size_t idx = index;

      if (FLAG_DWORD)
        {
          index = idx + 1;
          return state[idx];
        }
      else
        {
          index = idx + 2;
          if (FLAG_LITTLE_ENDIAN)
            return *reinterpret_cast<uint64_t *>(state + idx);

          uint32_t l = state[idx + 0];
          uint32_t h = state[idx + 1];

          index = idx + 2;
          return UIntType ((uint64_t (h) << 32) | l);
        }
    }

    inline void
    discard_gen (ull_type n)
    {
      RngMTE_likely_while (n--)
        generate ();
    }

    void
    discard_stat (ull_type n)
    {
      ull_type s = NDW - index;

      if (FLAG_QWORD)
        n <<= 1;

      RngMTE_unlikely_if (n <= s)
        {
          index += n;
          return;
        }
      n += NDW - s;
      do
        twist ();
      while ((n -= NDW) > NDW);

      index = size_t (n);
    }

    /*
     *
     */

    template <typename tUIntType, size_t tMEXP, size_t tPOS1,
              size_t tSL1, size_t tSL2, size_t tSR1, size_t tSR2,
              size_t tMSK1, size_t tMSK2, size_t tMSK3, size_t tMSK4,
              size_t tPAR1, size_t tPAR2, size_t tPAR3, size_t tPAR4>
    friend bool operator == (const RngSFMTE<tUIntType, tMEXP, tPOS1, tSL1, tSL2, tSR1, tSR2,
                             tMSK1, tMSK2, tMSK3, tMSK4, tPAR1, tPAR2, tPAR3, tPAR4> &,
                             const RngSFMTE<tUIntType, tMEXP, tPOS1, tSL1, tSL2, tSR1, tSR2,
                             tMSK1, tMSK2, tMSK3, tMSK4, tPAR1, tPAR2, tPAR3, tPAR4> &);

    template <typename tUIntType, size_t tMEXP, size_t tPOS1,
              size_t tSL1, size_t tSL2, size_t tSR1, size_t tSR2,
              size_t tMSK1, size_t tMSK2, size_t tMSK3, size_t tMSK4,
              size_t tPAR1, size_t tPAR2, size_t tPAR3, size_t tPAR4>
    friend bool operator != (const RngSFMTE<tUIntType, tMEXP, tPOS1, tSL1, tSL2, tSR1, tSR2,
                             tMSK1, tMSK2, tMSK3, tMSK4, tPAR1, tPAR2, tPAR3, tPAR4> &,
                             const RngSFMTE<tUIntType, tMEXP, tPOS1, tSL1, tSL2, tSR1, tSR2,
                             tMSK1, tMSK2, tMSK3, tMSK4, tPAR1, tPAR2, tPAR3, tPAR4> &);

    template <typename scT, typename stT,
              typename tUIntType, size_t tMEXP, size_t tPOS1,
              size_t tSL1, size_t tSL2, size_t tSR1, size_t tSR2,
              size_t tMSK1, size_t tMSK2, size_t tMSK3, size_t tMSK4,
              size_t tPAR1, size_t tPAR2, size_t tPAR3, size_t tPAR4>
    friend std::basic_ostream<scT, stT> &
    operator << (std::basic_ostream<scT, stT> &,
                 const RngSFMTE<tUIntType, tMEXP, tPOS1, tSL1, tSL2, tSR1, tSR2,
                 tMSK1, tMSK2, tMSK3, tMSK4, tPAR1, tPAR2, tPAR3, tPAR4> &);

    template <typename scT, typename stT,
              typename tUIntType, size_t tMEXP, size_t tPOS1,
              size_t tSL1, size_t tSL2, size_t tSR1, size_t tSR2,
              size_t tMSK1, size_t tMSK2, size_t tMSK3, size_t tMSK4,
              size_t tPAR1, size_t tPAR2, size_t tPAR3, size_t tPAR4>
    friend std::basic_istream<scT, stT> &
    operator >> (std::basic_istream<scT, stT> &,
		 RngSFMTE<tUIntType, tMEXP, tPOS1, tSL1, tSL2, tSR1, tSR2,
                 tMSK1, tMSK2, tMSK3, tMSK4, tPAR1, tPAR2, tPAR3, tPAR4> &);
  };

  /*
   * operator ==
   * operator !=
   */

  template <typename UIntType, size_t MEXP, size_t POS1,
            size_t SL1, size_t SL2, size_t SR1, size_t SR2,
            size_t MSK1, size_t MSK2, size_t MSK3, size_t MSK4,
            size_t PAR1, size_t PAR2, size_t PAR3, size_t PAR4>
  bool
  operator == (const RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
               MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4> &lhs,
               const RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
               MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4> &rhs)
  {
    using TYPE = RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
                          MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4>;

    const uint32_t *sl = lhs.state;
    const uint32_t *sr = rhs.state;
    size_t il = lhs.index, zl = TYPE::NDW - lhs.index;
    size_t ir = rhs.index, zr = TYPE::NDW - rhs.index;

    if (TYPE::FLAG_BLOCK || il == ir)
      return std::equal (sl, sl + TYPE::NDW, sr);
    if (il > ir)
      {
        std::swap (sl, sr);
        std::swap (il, ir);
        std::swap (zl, zr);
      }

    size_t zd = ir - il;
    size_t zw = TYPE::NDW - zd;

    return il
      ? (std::equal (sl + il, sl + zw, sr + ir) &&
         std::equal (sl + zw, sl + TYPE::NDW, sr) &&
         std::equal (sl, sl + il, sr + zd))
      : (std::equal (sl, sl + zr, sr + ir) &&
         std::equal (sl + zr, sl + TYPE::NDW, sr));
  }

  template <typename UIntType, size_t MEXP, size_t POS1,
            size_t SL1, size_t SL2, size_t SR1, size_t SR2,
            size_t MSK1, size_t MSK2, size_t MSK3, size_t MSK4,
            size_t PAR1, size_t PAR2, size_t PAR3, size_t PAR4>
  inline bool
  operator != (const RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
               MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4> &lhs,
               const RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
               MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4> &rhs)
  {
    return !(lhs == rhs);
  }

  /*
   * operator <<
   * operator >>
   */

  template <typename charT, typename traitsT,
            typename UIntType, size_t MEXP, size_t POS1,
            size_t SL1, size_t SL2, size_t SR1, size_t SR2,
            size_t MSK1, size_t MSK2, size_t MSK3, size_t MSK4,
            size_t PAR1, size_t PAR2, size_t PAR3, size_t PAR4>
  std::basic_ostream<charT, traitsT> &
  operator << (std::basic_ostream<charT, traitsT> &ostream,
               const RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
               MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4> &rhs)
  {
    using TYPE = const RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
                                MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4>;
    using stream_type = std::basic_ostream<charT, traitsT>;
    using char_type = typename stream_type::char_type;
    using fmtflags = typename stream_type::fmtflags;

    fmtflags oflags = ostream.flags (stream_type::dec | stream_type::left);
    char_type space = ostream.widen (' ');
    char_type ofill = ostream.fill (space);
    size_t index = rhs.index;

    ostream << rhs.state[0];
    for (size_t i = 1; i < TYPE::NDW; ++i)
      ostream << space << rhs.state[i];
    ostream << space << index;

    ostream.fill (ofill);
    ostream.flags (oflags);
    return ostream;
  }

  template <typename charT, typename traitsT,
            typename UIntType, size_t MEXP, size_t POS1,
            size_t SL1, size_t SL2, size_t SR1, size_t SR2,
            size_t MSK1, size_t MSK2, size_t MSK3, size_t MSK4,
            size_t PAR1, size_t PAR2, size_t PAR3, size_t PAR4>
  std::basic_istream<charT, traitsT> &
  operator >> (std::basic_istream<charT, traitsT> &istream,
	       RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
               MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4> &rhs)
  {
    using TYPE = const RngSFMTE<UIntType, MEXP, POS1, SL1, SL2, SR1, SR2,
                                MSK1, MSK2, MSK3, MSK4, PAR1, PAR2, PAR3, PAR4>;
    using stream_type = std::basic_istream<charT, traitsT>;
    using fmtflags = typename stream_type::fmtflags;

    fmtflags iflags = istream.flags (stream_type::dec | stream_type::skipws);
    UIntType state[TYPE::NDW];
    UIntType index = 0;

    for (size_t i = 0; i < TYPE::NDW; ++i)
      istream >> state[i];
    istream >> index;
    if (!istream.fail ())
      {
        for (size_t i = 0; i < TYPE::NDW; ++i)
          rhs.state[i] = state[i];
	rhs.index = index;
      }

    istream.flags (iflags);
    return istream;
  }

  /**/
} // RngMTE
