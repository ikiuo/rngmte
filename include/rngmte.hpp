#pragma once
#include "rngmte/std.hpp"
#include "rngmte/simd.hpp"

namespace RngMTE
{
  struct MethodParam
  {
    static constexpr int MASK_BLOCK = 1;
    static constexpr int MASK_VALUE = 2;
    static constexpr int MASK_PRETWIST = 4;
    static constexpr int MASK_CONDMOVE = 8;
    static constexpr int MASK_TWIEXT = 16;
    static constexpr int MASK_SIMD = 32;

    static constexpr int MODE_SEQ_BR = 0;
    static constexpr int MODE_SEQ_CM = MASK_CONDMOVE;
    static constexpr int MODE_SEQ_BRPT = MASK_PRETWIST;
    static constexpr int MODE_SEQ_CMPT = MASK_PRETWIST | MASK_CONDMOVE;

    static constexpr int MODE_SEQ_SIMD_BR = MASK_SIMD;
    static constexpr int MODE_SEQ_SIMD_CM = MASK_CONDMOVE | MASK_SIMD;

    static constexpr int MODE_BLOCK_STATE_BR = MASK_BLOCK;
    static constexpr int MODE_BLOCK_STATE_CM = MASK_CONDMOVE | MASK_BLOCK;
    static constexpr int MODE_BLOCK_VALUE_BR = MASK_BLOCK | MASK_VALUE;
    static constexpr int MODE_BLOCK_VALUE_CM = MASK_CONDMOVE | MASK_BLOCK | MASK_VALUE;
    static constexpr int MODE_BLOCK_TWIEXT_BR = MASK_BLOCK | MASK_VALUE | MASK_TWIEXT;
    static constexpr int MODE_BLOCK_TWIEXT_CM = MASK_CONDMOVE |MASK_BLOCK | MASK_VALUE | MASK_TWIEXT;

    static constexpr int MODE_BLOCK_SIMD_STATE_BR = MASK_BLOCK | MASK_SIMD;
    static constexpr int MODE_BLOCK_SIMD_STATE_CM = MASK_CONDMOVE | MASK_BLOCK | MASK_SIMD;
    static constexpr int MODE_BLOCK_SIMD_VALUE_BR = MASK_BLOCK | MASK_VALUE | MASK_SIMD;
    static constexpr int MODE_BLOCK_SIMD_VALUE_CM = MASK_CONDMOVE | MASK_BLOCK | MASK_VALUE | MASK_SIMD;
    static constexpr int MODE_BLOCK_SIMD_TWIEXT_BR = MASK_BLOCK | MASK_VALUE | MASK_TWIEXT | MASK_SIMD;
    static constexpr int MODE_BLOCK_SIMD_TWIEXT_CM = MASK_CONDMOVE | MASK_BLOCK | MASK_VALUE | MASK_TWIEXT | MASK_SIMD;
  };

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P /* MethodParam */>
  class RngMTE;

  /**/

  template <int P>
  using RngMT19937U32 = RngMTE<
    uint_fast32_t, 32, 624, 397, 31,
    0x9908b0df, 11, 0xffffffff,  7,
    0x9d2c5680, 15, 0xefc60000, 18,
    0x6c078965, P>;

  using RngMT19937SeqB32   = RngMT19937U32<MethodParam::MODE_SEQ_BR>;
  using RngMT19937SeqC32   = RngMT19937U32<MethodParam::MODE_SEQ_CM>;
  using RngMT19937SeqBP32  = RngMT19937U32<MethodParam::MODE_SEQ_BRPT>;
  using RngMT19937SeqCP32  = RngMT19937U32<MethodParam::MODE_SEQ_CMPT>;
  using RngMT19937SeqSB32  = RngMT19937U32<MethodParam::MODE_SEQ_SIMD_BR>;
  using RngMT19937SeqSC32  = RngMT19937U32<MethodParam::MODE_SEQ_SIMD_CM>;
  using RngMT19937BlkB32   = RngMT19937U32<MethodParam::MODE_BLOCK_STATE_BR>;
  using RngMT19937BlkC32   = RngMT19937U32<MethodParam::MODE_BLOCK_STATE_CM>;
  using RngMT19937BlkBV32  = RngMT19937U32<MethodParam::MODE_BLOCK_VALUE_BR>;
  using RngMT19937BlkCV32  = RngMT19937U32<MethodParam::MODE_BLOCK_VALUE_CM>;
  using RngMT19937BlkBT32  = RngMT19937U32<MethodParam::MODE_BLOCK_TWIEXT_BR>;
  using RngMT19937BlkCT32  = RngMT19937U32<MethodParam::MODE_BLOCK_TWIEXT_CM>;
  using RngMT19937BlkSB32  = RngMT19937U32<MethodParam::MODE_BLOCK_SIMD_STATE_BR>;
  using RngMT19937BlkSC32  = RngMT19937U32<MethodParam::MODE_BLOCK_SIMD_STATE_CM>;
  using RngMT19937BlkSBV32 = RngMT19937U32<MethodParam::MODE_BLOCK_SIMD_VALUE_BR>;
  using RngMT19937BlkSCV32 = RngMT19937U32<MethodParam::MODE_BLOCK_SIMD_VALUE_CM>;
  using RngMT19937BlkSBT32 = RngMT19937U32<MethodParam::MODE_BLOCK_SIMD_TWIEXT_BR>;
  using RngMT19937BlkSCT32 = RngMT19937U32<MethodParam::MODE_BLOCK_SIMD_TWIEXT_CM>;

  /**/

  template <int P>
  using RngMT19937U64 = RngMTE<
    uint_fast64_t, 64, 312, 156, 31,
    0xb5026f5aa96619e9ULL, 29, 0x5555555555555555ULL, 17,
    0x71d67fffeda60000ULL, 37, 0xfff7eee000000000ULL, 43,
    0x5851f42d4c957f2dULL, P>;

  using RngMT19937SeqB64  = RngMT19937U64<MethodParam::MODE_SEQ_BR>;
  using RngMT19937SeqC64  = RngMT19937U64<MethodParam::MODE_SEQ_CM>;
  using RngMT19937SeqBP64 = RngMT19937U64<MethodParam::MODE_SEQ_BRPT>;
  using RngMT19937SeqCP64 = RngMT19937U64<MethodParam::MODE_SEQ_CMPT>;
  using RngMT19937SeqSB64 = RngMT19937U64<MethodParam::MODE_SEQ_SIMD_BR>;
  using RngMT19937SeqSC64 = RngMT19937U64<MethodParam::MODE_SEQ_SIMD_CM>;
  using RngMT19937BlkB64  = RngMT19937U64<MethodParam::MODE_BLOCK_STATE_BR>;
  using RngMT19937BlkC64  = RngMT19937U64<MethodParam::MODE_BLOCK_STATE_CM>;
  using RngMT19937BlkBV64 = RngMT19937U64<MethodParam::MODE_BLOCK_VALUE_BR>;
  using RngMT19937BlkCV64 = RngMT19937U64<MethodParam::MODE_BLOCK_VALUE_CM>;
  using RngMT19937BlkBT64 = RngMT19937U64<MethodParam::MODE_BLOCK_TWIEXT_BR>;
  using RngMT19937BlkCT64 = RngMT19937U64<MethodParam::MODE_BLOCK_TWIEXT_CM>;
  using RngMT19937BlkSB64  = RngMT19937U64<MethodParam::MODE_BLOCK_SIMD_STATE_BR>;
  using RngMT19937BlkSC64  = RngMT19937U64<MethodParam::MODE_BLOCK_SIMD_STATE_CM>;
  using RngMT19937BlkSBV64 = RngMT19937U64<MethodParam::MODE_BLOCK_SIMD_VALUE_BR>;
  using RngMT19937BlkSCV64 = RngMT19937U64<MethodParam::MODE_BLOCK_SIMD_VALUE_CM>;
  using RngMT19937BlkSBT64 = RngMT19937U64<MethodParam::MODE_BLOCK_SIMD_TWIEXT_BR>;
  using RngMT19937BlkSCT64 = RngMT19937U64<MethodParam::MODE_BLOCK_SIMD_TWIEXT_CM>;

  /*
   *
   */

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  class RngMTE : public MethodParam
  {
  protected:
    using ull_type = unsigned long long;

    template <size_t bT, size_t bM>
    struct ConstMASK
    {
      static constexpr UIntType value =
        (bT == bM ? ~(UIntType (0)) : bM == 0 ? 0 :
         (((UIntType (1) << (bM - 1)) - 1) << 1) | 1);
    };

    static constexpr size_t UBITS = std::numeric_limits<UIntType>::digits;
    static constexpr UIntType WMASK = ConstMASK<UBITS, W>::value;
    static constexpr UIntType RMASK = ConstMASK<UBITS, R>::value;
    static constexpr UIntType PMASK = ~RMASK & WMASK;

    static constexpr bool FLAG_WMASK = (W != sizeof (UIntType) * 8);

    static constexpr bool FLAG_BLOCK    = bool (P & MASK_BLOCK);
    static constexpr bool FLAG_VALUE    = bool (P & MASK_VALUE);
    static constexpr bool FLAG_PSTATE   = bool (P & MASK_PRETWIST);
    static constexpr bool FLAG_CONDMOVE = bool (P & MASK_CONDMOVE);
    static constexpr bool FLAG_TWIEXT   = bool (P & MASK_TWIEXT);
    static constexpr bool FLAG_SIMD     = bool (P & MASK_SIMD);

    static_assert (std::is_unsigned<UIntType>::value, "bad type: UIntType");
    static_assert (W >  2, "invalid parameter: W > 2");
    static_assert (W >= R, "invalid parameter: W >= R");
    static_assert (W >= U, "invalid parameter: W >= R");
    static_assert (W >= S, "invalid parameter: W >= S");
    static_assert (W >= T, "invalid parameter: W >= T");
    static_assert (W >= L, "invalid parameter: W >= L");
    static_assert (W >= L, "invalid parameter: W >= L");
    static_assert (W <= UBITS, "invalid parameter: W or UIntType");
    static_assert (N >= M, "invalid parameter: M >= M");
    static_assert (M >  0, "invalid parameter: M > 0");

    static_assert (A <= WMASK, "invalid parameter: A <= (1 << W) - 1");
    static_assert (C <= WMASK, "invalid parameter: C <= (1 << W) - 1");
    static_assert (B <= WMASK, "invalid parameter: B <= (1 << W) - 1");
    static_assert (D <= WMASK, "invalid parameter: D <= (1 << W) - 1");
    static_assert (F <= WMASK, "invalid parameter: F <= (1 << W) - 1");

    /**/

    inline static constexpr bool
    postmask(size_t shift, size_t mask) noexcept
    {
      return ((UIntType(1) << shift) - 1) & mask;
    }

    static constexpr bool POSTMASK_SB = postmask (S, B);
    static constexpr bool POSTMASK_TC = postmask (T, C);

  public:
    using result_type = UIntType;

    static constexpr size_t word_size = W;
    static constexpr size_t state_size = N;
    static constexpr size_t shift_size = M;
    static constexpr size_t mask_bits = R;
    static constexpr UIntType xor_mask = A;
    static constexpr size_t tempering_u = U;
    static constexpr UIntType tempering_d = D;
    static constexpr size_t tempering_s = S;
    static constexpr UIntType tempering_b = B;
    static constexpr size_t tempering_t = T;
    static constexpr UIntType tempering_c = C;
    static constexpr size_t tempering_l = L;
    static constexpr UIntType initialization_multiplier = F;

    static constexpr result_type default_seed = 5489u;

  protected:
    using simd_t = SIMD::V128;
    using vec_t = typename std::conditional<
      sizeof (UIntType) == 4, simd_t::u32v_t, simd_t::u64v_t>::type;
    using vec_bt = typename vec_t::basic_type;

    static constexpr size_t VW = vec_t::element_count;
    static constexpr size_t VN = N / VW;
    static constexpr size_t VM = M / VW;
    static constexpr size_t ME = M % VW;

    static constexpr vec_t VWMASK = vec_bt (WMASK);
    static constexpr vec_t VRMASK = vec_bt (RMASK);
    static constexpr vec_t V0 = vec_bt (0);
    static constexpr vec_t V1 = vec_bt (1);
    static constexpr vec_t VA = vec_bt (A);
    static constexpr vec_t VB = vec_bt (B);
    static constexpr vec_t VC = vec_bt (C);
    static constexpr vec_t VD = vec_bt (D);

    static constexpr size_t VALALIGN = FLAG_VALUE ? 128 : alignof (vec_t);
    static constexpr size_t VALSIZE = FLAG_VALUE ? N : VW;

  protected:
    alignas (128) UIntType state[N];
    alignas (VALALIGN) UIntType value[VALSIZE];
    UIntType seqp_state;
    size_t index;

  public:
    inline static constexpr result_type min () noexcept { return 0; }
    inline static constexpr result_type max () noexcept { return WMASK; }

    inline RngMTE () noexcept : RngMTE (default_seed) {}
    inline RngMTE (UIntType seed) noexcept { set_seed (seed); };
    template <typename K> inline RngMTE (K &key) noexcept { set_seed (key); }

    inline void seed (UIntType value = default_seed) noexcept { set_seed (value); }
    template <typename K> inline void seed (K &key) noexcept { set_seed (key); }

    inline result_type operator () () noexcept { return generate (); }

    inline void
    discard (unsigned long long n) noexcept
    {
      RngMTE_unlikely_if (!n)
        return;

      switch (P)
        {
        default:
          if (FLAG_BLOCK)
	    discard_block (n);
	  else if (FLAG_SIMD)
	    discard_simd (n);
	  else
	    discard_seq (n);
          break;

        case MODE_SEQ_BRPT:
        case MODE_SEQ_CMPT:
          if (n > 1)
            discard_seq (n - 1);
          if (n > 0)
            init_pretwist ();
          break;
        }
    }

  protected:

    /**/

    inline static UIntType
    wmask (UIntType s) noexcept
    {
      return FLAG_WMASK ? s & WMASK : s;
    }

    inline static vec_t
    wmask (vec_t v) noexcept
    {
      return FLAG_WMASK ? v & VWMASK : v;
    }

    /**/

    inline void
    init_index () noexcept
    {
      seqp_state = 0;
      index = FLAG_BLOCK ? N : 0;
    }

    inline void
    init_pretwist () noexcept
    {
      if (FLAG_PSTATE)
        generate ();
    }

    void
    set_seed (UIntType value) noexcept
    {
      UIntType s = wmask (value);

      state[0] = s;
      for (size_t i = 1; i < N; ++i)
        state[i] = s = wmask ((s ^ (wmask (s) >> (W - 2))) * F + UIntType (i));

      init_index ();
      init_pretwist ();
    }

    /**/

    template <typename K>
    void
    set_seed (K &key) noexcept
    {
      constexpr size_t NK = UBITS ? ((UBITS + 31) >> 5) : 1;
      constexpr size_t NN = N * NK;
      uint32_t seq[NN];

      key.generate (seq + 0, seq + NN);

      result_type zmask = PMASK;
      bool zero = true;

      for (size_t i = 0; i < N; ++i)
        {
          size_t p = i * NK;
          UIntType value = 0;

          for (size_t j = NK; j--;)
            value = result_type ((uint_fast64_t (value) << 32) | seq[p + j]);
          state[i] = wmask (value);

          zero &= !(value & zmask);
          zmask = WMASK;
        }
      if (zero)
        state[0] = result_type (1) << (W - 1);

      init_index ();
      init_pretwist ();
    }

    /**/

    inline static UIntType
    twist_val (UIntType c, UIntType n, UIntType x) noexcept
    {
      UIntType y, z, t;

      y = ((c & PMASK) | (n & RMASK)) >> 1;
      if (FLAG_CONDMOVE)
        {
          z = A;
          t = n & 1;
          if (!t)
            z = t;
        }
      else // if (!FLAG_CONDMOVE)
        {
          z = (n & 1) ? A : 0;
        }
      return wmask (x ^ y ^ z);
    }

    template <bool discard>
    inline UIntType
    twist_ptr (UIntType *i0, UIntType *i1, UIntType *j) noexcept
    {
      ptrdiff_t vso = value - state;
      UIntType r = twist_val (*i0, *i1, *j);

      if (FLAG_VALUE && FLAG_TWIEXT && !discard)
        *(i0 + vso) = extract (r);
      return (*i0 = r);
    }

    template <bool discard>
    inline UIntType
    twist_idx (size_t i0, size_t i1, size_t j) noexcept
    {
      return twist_ptr<discard> (state + i0, state + i1, state + j);
    }

    template <bool discard>
    void
    twist_block () noexcept
    {
      constexpr size_t N_M = N - M;
      UIntType *p, *q;

      p = state;
      for (q = p + N_M; p != q; ++p)
        twist_ptr<discard> (p, p + 1, p + M);
      for (q = state + N - 1; p != q; ++p)
        twist_ptr<discard> (p, p + 1, p + M - N);
      twist_ptr<discard> (p, state, p - N_M);
    }

    /**/

    RngMTE_attribute ((always_inline))
    inline static vec_t
    twist_val (vec_t c, vec_t n, vec_t x,
	       const vec_t &v0 = V0, const vec_t &v1 = V1,
               const vec_t &vA = VA, const vec_t &vRMASK = VRMASK) noexcept
    {
      vec_t y = vRMASK.vbsl (n, c).template vsrl<1> ();
      vec_t z = ((n & v1) == v0).vandn (vA);

      return wmask (x ^ y ^ z);
    }

    template <bool discard>
    inline vec_t
    twist_ptr (vec_t *i0, vec_t *i1, vec_t *j0, vec_t *j1,
	       const vec_t &v0 = V0, const vec_t &v1 = V1,
	       const vec_t &vA = VA, const vec_t &vB = VB,
	       const vec_t &vC = VC, const vec_t &vD = VD,
	       const vec_t &vRMASK = VRMASK) noexcept
    {
      const ptrdiff_t vso = vec_t::bind (value) - vec_t::bind (state);

      vec_t sc, sd, se;
      vec_t xc, xd, xe;
      vec_t r;

      sc = *i0;
      sd = *i1;
      se = vec_t::template extr<1> (sc, sd);

      if (!ME)
        xe = *j0;
      else
        {
          xc = *j0;
          xd = *j1;
          xe = vec_t::template extr<ME> (xc, xd);
        }

      r = twist_val (sc, se, xe, v0, v1, vA, vRMASK);
      if (FLAG_VALUE && FLAG_TWIEXT && !discard)
        *(i0 + vso) = extract (r, vB, vC, vD);
      return (*i0 = r);
    }

    template <bool discard>
    inline vec_t
    twist_idx (size_t i0, size_t i1, size_t j0, size_t j1,
	       const vec_t &v0 = V0, const vec_t &v1 = V1,
	       const vec_t &vA = VA, const vec_t &vB = VB,
	       const vec_t &vC = VC, const vec_t &vD = VD,
	       const vec_t &vRMASK = VRMASK) noexcept
    {
      vec_t *s = vec_t::bind (state);

      return twist_ptr<discard> (s + i0, s + i1, s + j0, s + j1,
                                 v0, v1, vA, vB, vC, vD, vRMASK);
    }

    /**/

    inline vec_t
    twist_simd (size_t pos)
    {
      using lssz_t = typename std::make_signed<size_t>::type;

      vec_t *sp = vec_t::bind (state);

      size_t ci, ni, xi, yi;
      lssz_t nt, xt, yt;
      vec_t sc, sd, se;
      vec_t xc, xd, xe;

      ci = pos / VW;
      if (FLAG_CONDMOVE)
	{
	  nt = lssz_t (ci) + 1 - VN;
	  ni = nt == 0 ? size_t (nt) : ci + 1;

	  sc = sp[ci];
	  sd = sp[ni];
	  se = vec_t::template extr<1> (sc, sd);

	  xt = lssz_t (ci) + VM - VN;
	  xi = xt >= 0 ? size_t (xt) : ci + VM;

	  xc = sp[xi];
	  if (!ME)
	    xe = xc;
	  else
	    {
	      yt = lssz_t (ci) + VM + 1 - VN;
	      yi = yt >= 0 ? size_t (yt) : ci + VM + 1;

	      xd = sp[yi];
	      xe = vec_t::template extr<ME> (xc, xd);
	    }
	}
      else // if (!FLAG_CONDMOVE)
	{
	  sc = sp[ci];
	  RngMTE_unlikely_if (ci >= VN - 1)
	    {
	      sd = sp[0];
	      if (!ME)
		xe = sp[VM - 1];
	      else
		{
		  xc = sp[VM - 1];
		  xd = sp[VM + 0];
		}
	    }
	  else
	    {
	      sd = sp[ci + 1];

	      if (!ME)
		{
		  if (VM < VN - VM)
		    {
		      RngMTE_unlikely_if (ci >= VN - VM)
			xe = sp[ci + VM - VN];
		      else
			xe = sp[ci + VM];
		    }
		  else
		    {
		      RngMTE_unlikely_if (ci < VN - VM)
			xe = sp[ci + VM];
		      else
			xe = sp[ci + VM - VN];
		    }
		}
	      else
		{
		  if (VM < VN - VM)
		    {
		      RngMTE_unlikely_if (ci >= VN - VM)
			{
			  xc = sp[ci + VM + 0 - VN];
			  xd = sp[ci + VM + 1 - VN];
			}
		      else
			{
			  xc = sp[ci + VM];
			  RngMTE_unlikely_if (ci >= VN - VM - 1)
			    xd = sp[ci + VM + 1 - VN];
			  else
			    xd = sp[ci + VM + 1];
			}
		    }
		  else
		    {
		      RngMTE_unlikely_if (ci < VN - VM)
			{
			  xc = sp[ci + VM];
			  RngMTE_unlikely_if (ci < VN - VM - 1)
			    xd = sp[ci + VM + 1];
			  else
			    xd = sp[ci + VM + 1 - VN];
			}
		      else
			{
			  xc = sp[ci + VM + 0 - VN];
			  xd = sp[ci + VM + 1 - VN];
			}
		    }
		}
	    }

	  se = vec_t::template extr<1> (sc, sd);
	  if (ME)
	    xe = vec_t::template extr<ME> (xc, xd);
	}
      return (sp[ci] = twist_val (sc, se, xe));
    }

    template <bool discard>
    void
    twist_simd () noexcept
    {
      static_assert (!(N % VW), "error: (N % VW) != 0");

      constexpr size_t VN_M = VN - VM;
      size_t i = 0;

      for (; i < VN_M - (ME ? 1 : 0); ++i)
        twist_idx<discard> (i, i + 1, i + VM, i + VM + 1);
      if (ME)
        {
          twist_idx<discard> (i, i + 1, i + VM, 0);
          ++i;
        }
      for (; i < VN - 1; ++i)
        twist_idx<discard> (i, i + 1, i - VN_M, i - VN_M + 1);
      twist_idx<discard> (VN - 1, 0, VM - 1, VM);
    }

    template <bool discard = false>
    inline void
    twist () noexcept
    {
      if (!FLAG_SIMD)
        twist_block<discard> ();
      else
        twist_simd<discard> ();
    }

    /**/

    inline static UIntType
    extract (UIntType s) noexcept
    {
      UIntType x, y, z;

      x = s ^ ((wmask (s) >> U) & D);
      y = x ^ (POSTMASK_SB ? (x << S) & B : (x & (B >> S)) << S);
      z = y ^ (POSTMASK_TC ? (y << T) & C : (y & (C >> T)) << T);
      return wmask (z ^ (wmask (z) >> L));
    }

    void
    extract_block () noexcept
    {
      for (size_t i = 0; i < N; ++i)
        value[i] = extract (state[i]);
    }

    /**/

    inline static vec_t
    extract (vec_t s,
	     const vec_t &vB = VB,
	     const vec_t &vC = VC,
	     const vec_t &vD = VD) noexcept
    {
      vec_t x, y, z;

      x = s ^ (wmask (s).template vsrl<U> () & vD);
      y = x ^ (x.template vsll<S> () & vB);
      z = y ^ (y.template vsll<T> () & vC);
      return wmask (z ^ wmask (z).template vsrl<L> ());
    }

    void
    extract_simd () noexcept
    {
      vec_t *sp = vec_t::bind (state);
      vec_t *vp = vec_t::bind (value);

      for (size_t i = 0; i < VN; ++i)
        vp[i] = extract (sp[i]);
    }

    /**/

    inline void
    extract () noexcept
    {
      if (!FLAG_SIMD)
        extract_block ();
      else
        extract_simd ();
    }

    /**/

    inline UIntType
    generate_block () noexcept
    {
      size_t ci = index;

      RngMTE_unlikely_if (ci >= N)
	{
	  twist ();
	  if (FLAG_VALUE && !FLAG_TWIEXT)
	    extract ();
	  ci = 0;
	}
      index = ci + 1;
      return FLAG_VALUE ? value[ci] : extract (state[ci]);
    }

    inline UIntType
    generate_simd () noexcept
    {
      if ((N % VW) || FLAG_PSTATE)
	return generate_seq ();

      size_t pos = index++;

      RngMTE_likely_if ((pos % VW))
	return value[pos % VW];

      RngMTE_unlikely_if (pos >= N)
	{
	  index = 1;
	  pos = 0;
	}

      vec_t *vp = vec_t::bind (value);
      vec_t vr = extract (twist_simd (pos));

      *vp = vr;
      return vr.get (0);
    }

    inline UIntType
    generate_seq () noexcept
    {
      using lssz_t = typename std::make_signed<size_t>::type;

      UIntType pstate, lstate;
      UIntType x, y, z, r;

      size_t ci, ni, xi;
      lssz_t nt, xt;

      if (FLAG_PSTATE)
	pstate = seqp_state;

      ci = index;
      if (FLAG_CONDMOVE)
	{
	  x = state[ci];

	  nt = lssz_t (ci) + 1 - N;
	  ni = nt == 0 ? size_t (nt) : ci + 1;

	  index = ni;
	  y = state[ni];

	  xt = lssz_t (ci) + M - N;
	  xi = xt >= 0 ? size_t (xt) : ci + M;

	  z = state[xi];
	}
      else // if (!FLAG_CONDMOVE)
	{
	  x = state[ci];
	  RngMTE_unlikely_if (ci >= N - 1)
	    {
	      y = state[index = 0];
	      z = state[M - 1];
	    }
	  else
	    {
	      y = state[index = ci + 1];
	      if (M < N - M)
		{
		  RngMTE_unlikely_if (ci >= N - M)
		    z = state[ci + M - N];
		  else
		    z = state[ci + M];
		}
	      else
		{
		  RngMTE_unlikely_if (ci < N - M)
		    z = state[ci + M];
		  else
		    z = state[ci + M - N];
		}
	    }
	}
      if (FLAG_PSTATE)
	r = extract (pstate);
      state[ci] = lstate = twist_val (x, y, z);
      if (FLAG_PSTATE)
	seqp_state = lstate;
      else
	r = extract (lstate);
      return r;
    }

    inline UIntType
    generate () noexcept
    {
      if (FLAG_BLOCK)
	return generate_block ();
      if (FLAG_SIMD)
	return generate_simd ();
      return generate_seq ();
    }

    /**/

    inline void
    discard_gen (ull_type n) noexcept
    {
      while (n--)
        generate ();
    }

    void
    discard_seq (ull_type n) noexcept
    {
      if (index > 0 && !(n = discard_seqsub (index, n)))
        return;
      for (; n >= N; n -= N)
        twist<true> ();
      if (n)
        discard_seqsub (0, n);
    }

    ull_type
    discard_seqsub (size_t i, ull_type n) noexcept
    {
      constexpr size_t M_1 = M - 1;
      constexpr size_t N_1 = N - 1;
      constexpr size_t N_M = N - M;
      ull_type m;
      size_t k;

      if (i < N_M)
        {
          m = std::min<ull_type> (n, N_M - i);
          k = i + size_t (m);
          for (; i < k; ++i)
            twist_idx<true> (i, i + 1, i + M);
          index = i;
          if (!(n -= m))
            return 0;
        }
      if (i < N_1)
        {
          m = std::min<ull_type> (n, N_1 - i);
          k = i + size_t (m);
          for (; i < k; ++i)
            twist_idx<true> (i, i + 1, i - N_M);
          index = i;
          if (!(n -= m))
            return 0;
        }

      twist_idx<true> (N_1, 0, M_1);
      index = 0;
      return --n;
    }

    void
    discard_block (ull_type n) noexcept
    {
      ull_type s = N - index;

      if (n <= s)
        {
          index += n;
          return;
        }
      n += N - s;

      do
        twist<true> ();
      while ((n -= N) > N);

      if (FLAG_VALUE)
        extract ();

      index = size_t (n);
    }

    void
    discard_simd (ull_type n) noexcept
    {
      if ((N % VW) || FLAG_PSTATE)
	{
	  discard_seq (n);
	  return;
	}

      vec_t *sp = vec_t::bind (state);
      vec_t *vp = vec_t::bind (value);

      size_t pos = index;
      ull_type ns;

      ns = pos % VW;
      if (ns)
	{
	  ns = std::min<ull_type> (n, VW - ns);

	  pos += size_t (ns);
	  if (pos >= N)
	    pos = 0;
	  index = pos;

	  n -= ns;
	  if (!n)
	    return;
	}
      if (pos >= N)
	pos = 0;
      ns = n / VW;
      if (pos > 0 && ns)
	{
	  ns = discard_simdsub (pos / VW, ns);
	  pos = index;
	}
      for (; ns >= VN; ns -= VN)
	twist_simd<true> ();
      if (ns)
	{
	  discard_simdsub (0, ns);
	  pos = index;
	}
      ns = n % VW;
      index = pos + size_t (ns);
      if (ns)
	twist_simd (index);
      *vp = extract (sp[index / VW]);
    }

    ull_type
    discard_simdsub (size_t i, ull_type n)
    {
      constexpr size_t VN_M = VN - VM;
      constexpr size_t VNME = VN_M - (ME ? 1 : 0);
      ull_type m;
      size_t k;

      if (i < VNME)
	{
          m = std::min<ull_type> (n, VNME - i);
          k = i + size_t (m);
          for (; i < k; ++i)
            twist_idx<true> (i, i + 1, i + VM, i + VM + 1);
	  index = i * VW;
          if (!(n -= m))
            return 0;
	}
      if (ME && i == VN_M - 1)
	{
	  twist_idx<true> (i, i + 1, i + VM, 0);
	  index = ++i * VW;
	  if (!--n)
	    return 0;
	}
      if (i < VN - 1)
	{
          m = std::min<ull_type> (n, VN - 1 - i);
          k = i + size_t (m);
          for (; i < k; ++i)
            twist_idx<true> (i, i + 1, i - VN_M, i - VN_M + 1);
          index = i * VW;
          if (!(n -= m))
            return 0;
	}
      twist_idx<true> (VN - 1, 0, VM - 1, VM);
      index = 0;
      return --n;
    }

    /*
     *
     */

    template <typename tUIntType, size_t tW, size_t tN, size_t tM,
              size_t tR, tUIntType tA, size_t tU, tUIntType tD,
              size_t tS, tUIntType tB, size_t tT, tUIntType tC,
              size_t tL, tUIntType tF, int tP>
    friend bool operator == (const RngMTE<tUIntType, tW, tN, tM, tR, tA, tU, tD, tS, tB, tT, tC, tL, tF, tP> &,
                             const RngMTE<tUIntType, tW, tN, tM, tR, tA, tU, tD, tS, tB, tT, tC, tL, tF, tP> &) noexcept;

    template <typename tUIntType, size_t tW, size_t tN, size_t tM,
              size_t tR, tUIntType tA, size_t tU, tUIntType tD,
              size_t tS, tUIntType tB, size_t tT, tUIntType tC,
              size_t tL, tUIntType tF, int tP>
    friend bool operator != (const RngMTE<tUIntType, tW, tN, tM, tR, tA, tU, tD, tS, tB, tT, tC, tL, tF, tP> &,
                             const RngMTE<tUIntType, tW, tN, tM, tR, tA, tU, tD, tS, tB, tT, tC, tL, tF, tP> &) noexcept;

    template <typename scT, typename stT,
              typename tUIntType, size_t tW, size_t tN, size_t tM,
              size_t tR, tUIntType tA, size_t tU, tUIntType tD,
              size_t tS, tUIntType tB, size_t tT, tUIntType tC,
              size_t tL, tUIntType tF, int tP>
    friend std::basic_ostream<scT, stT> &
    operator << (std::basic_ostream<scT, stT> &,
                 const RngMTE<tUIntType, tW, tN, tM, tR, tA, tU, tD, tS, tB, tT, tC, tL, tF, tP> &);

    template <typename scT, typename stT,
              typename tUIntType, size_t tW, size_t tN, size_t tM,
              size_t tR, tUIntType tA, size_t tU, tUIntType tD,
              size_t tS, tUIntType tB, size_t tT, tUIntType tC,
              size_t tL, tUIntType tF, int tP>
    friend std::basic_istream<scT, stT> &
    operator >> (std::basic_istream<scT, stT> &,
                 RngMTE<tUIntType, tW, tN, tM, tR, tA, tU, tD, tS, tB, tT, tC, tL, tF, tP> &);

  };

  /*
   * V0, V1, VA, VB, VC, VD, VRMASK
   */

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::VWMASK;

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::VRMASK;

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::V0;

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::V1;

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::VA;

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::VB;

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::VC;

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  constexpr typename RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::vec_t
  RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>::VD;

  /*
   * operator ==
   * operator !=
   */

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  bool
  operator == (const RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P> &lhs,
               const RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P> &rhs) noexcept
  {
    using TYPE = RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>;
    using result_type = typename TYPE::result_type;

    const result_type *sl = lhs.state;
    const result_type *sr = rhs.state;
    size_t il = lhs.index, zl = N - lhs.index;
    size_t ir = rhs.index, zr = N - rhs.index;

    if (TYPE::FLAG_BLOCK || il == ir)
      return std::equal (sl, sl + N, sr);
    if (il > ir)
      {
        std::swap (sl, sr);
        std::swap (il, ir);
        std::swap (zl, zr);
      }

    size_t zd = ir - il;
    size_t zw = N - zd;

    return il
      ? (std::equal (sl + il, sl + zw, sr + ir) &&
         std::equal (sl + zw, sl + N, sr) &&
         std::equal (sl, sl + il, sr + zd))
      : (std::equal (sl, sl + zr, sr + ir) &&
         std::equal (sl + zr, sl + N, sr));
  }

  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  inline bool
  operator != (const RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P> &lhs,
               const RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P> &rhs) noexcept
  {
    return !(lhs == rhs);
  }

  /*
   * operator <<
   * operator >>
   */

  template <typename charT, typename traitsT,
            typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  std::basic_ostream<charT, traitsT> &
  operator << (std::basic_ostream<charT, traitsT> &ostream,
               const RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P> &rhs)
  {
    using TYPE = RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>;
    using stream_type = std::basic_ostream<charT, traitsT>;
    using char_type = typename stream_type::char_type;
    using fmtflags = typename stream_type::fmtflags;

    fmtflags oflags = ostream.flags (stream_type::dec | stream_type::left);
    char_type space = ostream.widen (' ');
    char_type ofill = ostream.fill (space);

    ostream << rhs.state[0];
    for (size_t i = 1; i < N; ++i)
      ostream << space << rhs.state[i];
    ostream << space << rhs.index;
    if (TYPE::FLAG_PSTATE)
      ostream << space << rhs.seqp_state;

    ostream.fill (ofill);
    ostream.flags (oflags);
    return ostream;
  }

  template <typename charT, typename traitsT,
            typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F, int P>
  std::basic_istream<charT, traitsT> &
  operator >> (std::basic_istream<charT, traitsT> &istream,
               RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P> &rhs)
  {
    using TYPE = RngMTE<UIntType, W, N, M, R, A, U, D, S, B, T, C, L, F, P>;
    using stream_type = std::basic_istream<charT, traitsT>;
    using fmtflags = typename stream_type::fmtflags;

    fmtflags iflags = istream.flags (stream_type::dec | stream_type::skipws);
    UIntType state[N], pstate = 0;
    UIntType index = 0;

    for (size_t i = 0; i < N; ++i)
      istream >> state[i];
    istream >> index;
    if (TYPE::FLAG_PSTATE)
      istream >> pstate;
    if (!istream.fail ())
      {
        for (size_t i = 0; i < N; ++i)
          rhs.state[i] = state[i];
        rhs.seqp_state = pstate;
	rhs.index = index;
        if (TYPE::FLAG_VALUE)
          rhs.extract ();
	else if (TYPE::FLAG_SIMD && (index % TYPE::VW))
	  *TYPE::vec_t::bind (rhs.value) = TYPE::extract
	    (TYPE::vec_t::bind (rhs.state)[index / TYPE::VW]);
      }

    istream.flags (iflags);
    return istream;
  }
} // RngMTE
