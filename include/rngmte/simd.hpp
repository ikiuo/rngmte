#pragma once
#include "simd/basic.hpp"
#include "simd/x86.hpp"
#include "simd/arm.hpp"

#ifndef RngMTE_HAS_SIMD_V128
#  define RngMTE_HAS_SIMD_V128 0
#endif

namespace RngMTE
{
  namespace SIMD
  {
    /**/

    template <size_t B, typename T, size_t N>
    struct TypeSize
    {
      using type = Basic<T, N>;
    };

#if RngMTE_HAS_SIMD_V128
    template <typename T, size_t N>
    struct TypeSize<16, T, N>
    {
      using type = Register128<T, N>;
    };
#endif

    /**/

    template <size_t B>
    union Register
    {
      using s8v_t  = typename TypeSize<B, int8_t,  (B >> 0)>::type;
      using s16v_t = typename TypeSize<B, int16_t, (B >> 1)>::type;
      using s32v_t = typename TypeSize<B, int32_t, (B >> 2)>::type;
      using s64v_t = typename TypeSize<B, int64_t, (B >> 3)>::type;

      using u8v_t  = typename TypeSize<B, uint8_t,  (B >> 0)>::type;
      using u16v_t = typename TypeSize<B, uint16_t, (B >> 1)>::type;
      using u32v_t = typename TypeSize<B, uint32_t, (B >> 2)>::type;
      using u64v_t = typename TypeSize<B, uint64_t, (B >> 3)>::type;

      s8v_t sb; s16v_t sw; s32v_t sd; s64v_t sq;
      u8v_t ub; u16v_t uw; u32v_t ud; u64v_t uq;

      /**/

      Register () = default;

      constexpr Register (s8v_t  s) noexcept;
      constexpr Register (s16v_t s) noexcept;
      constexpr Register (s32v_t s) noexcept;
      constexpr Register (s64v_t s) noexcept;

      constexpr Register (u8v_t  s) noexcept;
      constexpr Register (u16v_t s) noexcept;
      constexpr Register (u32v_t s) noexcept;
      constexpr Register (u64v_t s) noexcept;

      /**/

      constexpr operator s8v_t  () const noexcept;
      constexpr operator s16v_t () const noexcept;
      constexpr operator s32v_t () const noexcept;
      constexpr operator s64v_t () const noexcept;

      constexpr operator u8v_t  () const noexcept;
      constexpr operator u16v_t () const noexcept;
      constexpr operator u32v_t () const noexcept;
      constexpr operator u64v_t () const noexcept;

      constexpr Register<B> operator ~ () const noexcept;

      constexpr Register<B> operator & (Register<B> r) const noexcept;
      constexpr Register<B> operator ^ (Register<B> r) const noexcept;
      constexpr Register<B> operator | (Register<B> r) const noexcept;

      constexpr Register<B> vaddsb (Register<B> r) const noexcept;
      constexpr Register<B> vaddsw (Register<B> r) const noexcept;
      constexpr Register<B> vaddsd (Register<B> r) const noexcept;
      constexpr Register<B> vaddsq (Register<B> r) const noexcept;

      constexpr Register<B> vaddub (Register<B> r) const noexcept;
      constexpr Register<B> vadduw (Register<B> r) const noexcept;
      constexpr Register<B> vaddud (Register<B> r) const noexcept;
      constexpr Register<B> vadduq (Register<B> r) const noexcept;

      constexpr Register<B> vsubub (Register<B> r) const noexcept;
      constexpr Register<B> vsubuw (Register<B> r) const noexcept;
      constexpr Register<B> vsubud (Register<B> r) const noexcept;
      constexpr Register<B> vsubuq (Register<B> r) const noexcept;

      constexpr Register<B> vsubsb (Register<B> r) const noexcept;
      constexpr Register<B> vsubsw (Register<B> r) const noexcept;
      constexpr Register<B> vsubsd (Register<B> r) const noexcept;
      constexpr Register<B> vsubsq (Register<B> r) const noexcept;

      constexpr Register<B> vmulub (Register<B> r) const noexcept;
      constexpr Register<B> vmuluw (Register<B> r) const noexcept;
      constexpr Register<B> vmulud (Register<B> r) const noexcept;
      constexpr Register<B> vmuluq (Register<B> r) const noexcept;

      constexpr Register<B> vmulsb (Register<B> r) const noexcept;
      constexpr Register<B> vmulsw (Register<B> r) const noexcept;
      constexpr Register<B> vmulsd (Register<B> r) const noexcept;
      constexpr Register<B> vmulsq (Register<B> r) const noexcept;

      constexpr Register<B> vdivub (Register<B> r) const noexcept;
      constexpr Register<B> vdivuw (Register<B> r) const noexcept;
      constexpr Register<B> vdivud (Register<B> r) const noexcept;
      constexpr Register<B> vdivuq (Register<B> r) const noexcept;

      constexpr Register<B> vdivsb (Register<B> r) const noexcept;
      constexpr Register<B> vdivsw (Register<B> r) const noexcept;
      constexpr Register<B> vdivsd (Register<B> r) const noexcept;
      constexpr Register<B> vdivsq (Register<B> r) const noexcept;

      constexpr Register<B> vmodsb (Register<B> r) const noexcept;
      constexpr Register<B> vmodsw (Register<B> r) const noexcept;
      constexpr Register<B> vmodsd (Register<B> r) const noexcept;
      constexpr Register<B> vmodsq (Register<B> r) const noexcept;

      constexpr Register<B> vmodub (Register<B> r) const noexcept;
      constexpr Register<B> vmoduw (Register<B> r) const noexcept;
      constexpr Register<B> vmodud (Register<B> r) const noexcept;
      constexpr Register<B> vmoduq (Register<B> r) const noexcept;

      constexpr Register<B> vand (Register<B> r) const noexcept;
      constexpr Register<B> vandn (Register<B> r) const noexcept;
      constexpr Register<B> vxor (Register<B> r) const noexcept;
      constexpr Register<B> vor (Register<B> r) const noexcept;

      template <size_t S> constexpr Register<B> vsllb () const noexcept;
      template <size_t S> constexpr Register<B> vsllw () const noexcept;
      template <size_t S> constexpr Register<B> vslld () const noexcept;
      template <size_t S> constexpr Register<B> vsllq () const noexcept;
      constexpr Register<B> vsllb (size_t n) const noexcept;
      constexpr Register<B> vsllw (size_t n) const noexcept;
      constexpr Register<B> vslld (size_t n) const noexcept;
      constexpr Register<B> vsllq (size_t n) const noexcept;

      template <size_t S> constexpr Register<B> vsrlb () const noexcept;
      template <size_t S> constexpr Register<B> vsrlw () const noexcept;
      template <size_t S> constexpr Register<B> vsrld () const noexcept;
      template <size_t S> constexpr Register<B> vsrlq () const noexcept;
      constexpr Register<B> vsrlb (size_t n) const noexcept;
      constexpr Register<B> vsrlw (size_t n) const noexcept;
      constexpr Register<B> vsrld (size_t n) const noexcept;
      constexpr Register<B> vsrlq (size_t n) const noexcept;

      template <size_t S> constexpr Register<B> vsrab () const noexcept;
      template <size_t S> constexpr Register<B> vsraw () const noexcept;
      template <size_t S> constexpr Register<B> vsrad () const noexcept;
      template <size_t S> constexpr Register<B> vsraq () const noexcept;
      constexpr Register<B> vsrab (size_t n) const noexcept;
      constexpr Register<B> vsraw (size_t n) const noexcept;
      constexpr Register<B> vsrad (size_t n) const noexcept;
      constexpr Register<B> vsraq (size_t n) const noexcept;

      template <size_t S> constexpr Register<B> bsll () const noexcept;
      constexpr Register<B> bsll (size_t n) const noexcept;

      template <size_t S> constexpr Register<B> bsrl () const noexcept;
      constexpr Register<B> bsrl (size_t n) const noexcept;

      /**/

      static constexpr Register<B> vzero () noexcept;
      static constexpr Register<B> vones () noexcept;

      static constexpr Register<B> *bind (void *p) noexcept;
      static constexpr const Register<B> *bind (const void *p) noexcept;

      static constexpr Register<B> load (const void *p) noexcept;
    };

    /**/

    using V128 = Register<16>; static_assert (sizeof(V128) == 16, "bug: sizeof(V128) != 16");

    /**/
  } // SIMD

  /*
   * inline
   */

  namespace SIMD
  {
    /***********
     * Register *
     ***********/

    template <size_t B>
    inline constexpr
    Register<B>::Register (s8v_t  s) noexcept
      : sb (s)
    {
      /*NOOP*/
    }

    template <size_t B>
    inline constexpr
    Register<B>::Register (s16v_t s) noexcept
      : sw (s)
    {
      /*NOOP*/
    }

    template <size_t B>
    inline constexpr
    Register<B>::Register (s32v_t s) noexcept
      : sd (s)
    {
      /*NOOP*/
    }

    template <size_t B>
    inline constexpr
    Register<B>::Register (s64v_t s) noexcept
      : sq (s)
    {
      /*NOOP*/
    }

    /**/

    template <size_t B>
    inline constexpr
    Register<B>::Register (u16v_t s) noexcept
      : uw (s)
    {
      /*NOOP*/
    }

    template <size_t B>
    inline constexpr
    Register<B>::Register (u8v_t  s) noexcept
      : ub (s)
    {
      /*NOOP*/
    }

    template <size_t B>
    inline constexpr
    Register<B>::Register (u32v_t s) noexcept
      : ud (s)
    {
      /*NOOP*/
    }

    template <size_t B>
    inline constexpr
    Register<B>::Register (u64v_t s) noexcept
      : uq (s)
    {
      /*NOOP*/
    }

    /******************
     * operator: cast *
     ******************/

    template <size_t B>
    inline constexpr
    Register<B>::operator s8v_t () const noexcept
    {
      return sb;
    }

    template <size_t B>
    inline constexpr
    Register<B>::operator s16v_t () const noexcept
    {
      return sw;
    }

    template <size_t B>
    inline constexpr
    Register<B>::operator s32v_t () const noexcept
    {
      return sd;
    }

    template <size_t B>
    inline constexpr
    Register<B>::operator s64v_t () const noexcept
    {
      return sq;
    }

    /**/

    template <size_t B>
    inline constexpr
    Register<B>::operator u8v_t () const noexcept
    {
      return ub;
    }

    template <size_t B>
    inline constexpr
    Register<B>::operator u16v_t () const noexcept
    {
      return uw;
    }

    template <size_t B>
    inline constexpr
    Register<B>::operator u32v_t () const noexcept
    {
      return ud;
    }

    template <size_t B>
    inline constexpr
    Register<B>::operator u64v_t () const noexcept
    {
      return uq;
    }

    /**********************************
     * operator: not / and / xor / or *
     **********************************/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::operator ~ () const noexcept
    {
      return ub.vnot ();
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::operator & (Register<B> r) const noexcept
    {
      return ub.vand (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::operator ^ (Register<B> r) const noexcept
    {
      return ub.vxor (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::operator | (Register<B> r) const noexcept
    {
      return ub.vor (r);
    }

    /********
     * vadd *
     ********/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vaddsb (Register<B> r) const noexcept
    {
      return sb.vadd (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vaddsw (Register<B> r) const noexcept
    {
      return sw.vadd (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vaddsd (Register<B> r) const noexcept
    {
      return sd.vadd (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vaddsq (Register<B> r) const noexcept
    {
      return sq.vadd (r);
    }

    /**/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vaddub (Register<B> r) const noexcept
    {
      return ub.vadd (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vadduw (Register<B> r) const noexcept
    {
      return uw.vadd (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vaddud (Register<B> r) const noexcept
    {
      return ud.vadd (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vadduq (Register<B> r) const noexcept
    {
      return uq.vadd (r);
    }

    /********
     * vsub *
     ********/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubsb (Register<B> r) const noexcept
    {
      return sb.vsub (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubsw (Register<B> r) const noexcept
    {
      return sw.vsub (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubsd (Register<B> r) const noexcept
    {
      return sd.vsub (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubsq (Register<B> r) const noexcept
    {
      return sq.vsub (r);
    }

    /**/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubub (Register<B> r) const noexcept
    {
      return ub.vsub (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubuw (Register<B> r) const noexcept
    {
      return uw.vsub (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubud (Register<B> r) const noexcept
    {
      return ud.vsub (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsubuq (Register<B> r) const noexcept
    {
      return uq.vsub (r);
    }

    /********
     * vmul *
     ********/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmulsb (Register<B> r) const noexcept
    {
      return sb.vmul (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmulsw (Register<B> r) const noexcept
    {
      return sw.vmul (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmulsd (Register<B> r) const noexcept
    {
      return sd.vmul (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmulsq (Register<B> r) const noexcept
    {
      return sq.vmul (r);
    }

    /**/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmulub (Register<B> r) const noexcept
    {
      return ub.vmul (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmuluw (Register<B> r) const noexcept
    {
      return uw.vmul (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmulud (Register<B> r) const noexcept
    {
      return ud.vmul (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmuluq (Register<B> r) const noexcept
    {
      return uq.vmul (r);
    }

    /********
     * vdiv *
     ********/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivsb (Register<B> r) const noexcept
    {
      return sb.vdiv (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivsw (Register<B> r) const noexcept
    {
      return sw.vdiv (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivsd (Register<B> r) const noexcept
    {
      return sd.vdiv (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivsq (Register<B> r) const noexcept
    {
      return sq.vdiv (r);
    }

    /**/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivub (Register<B> r) const noexcept
    {
      return ub.vdiv (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivuw (Register<B> r) const noexcept
    {
      return uw.vdiv (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivud (Register<B> r) const noexcept
    {
      return ud.vdiv (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vdivuq (Register<B> r) const noexcept
    {
      return uq.vdiv (r);
    }

    /********
     * vmod *
     ********/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmodsb (Register<B> r) const noexcept
    {
      return sb.vmod (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmodsw (Register<B> r) const noexcept
    {
      return sw.vmod (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmodsd (Register<B> r) const noexcept
    {
      return sd.vmod (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmodsq (Register<B> r) const noexcept
    {
      return sq.vmod (r);
    }

    /**/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmodub (Register<B> r) const noexcept
    {
      return ub.vmod (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmoduw (Register<B> r) const noexcept
    {
      return uw.vmod (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmodud (Register<B> r) const noexcept
    {
      return ud.vmod (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vmoduq (Register<B> r) const noexcept
    {
      return uq.vmod (r);
    }

    /*****************************
     * vand / vandn / vxor / vor *
     *****************************/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vand (Register<B> r) const noexcept
    {
      return ub.vand (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vandn (Register<B> r) const noexcept
    {
      return ub.vandn (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vxor (Register<B> r) const noexcept
    {
      return ub.vxor (r);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vor (Register<B> r) const noexcept
    {
      return ub.vor (r);
    }

    /********
     * vsll *
     ********/

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsllb () const noexcept
    {
      return ub.template vsll<S> ();
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsllw () const noexcept
    {
      return uw.template vsll<S> ();
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vslld () const noexcept
    {
      return ud.template vsll<S> ();
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsllq () const noexcept
    {
      return uq.template vsll<S> ();
    }

    /**/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsllb (size_t n) const noexcept
    {
      return ub.vsll (n);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsllw (size_t n) const noexcept
    {
      return uw.vsll (n);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vslld (size_t n) const noexcept
    {
      return ud.vsll (n);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsllq (size_t n) const noexcept
    {
      return uq.vsll (n);
    }

    /********
     * vsrl *
     ********/

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsrlb () const noexcept
    {
      return ub.template vsrl<S> ();
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsrlw () const noexcept
    {
      return uw.template vsrl<S> ();
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsrld () const noexcept
    {
      return ud.template vsrl<S> ();
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsrlq (size_t n) const noexcept
    {
      return uq.vsrl (n);
    }

    /********
     * vsra *
     ********/

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsrab () const noexcept
    {
      return sb.template vsra<S> ();
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsraw () const noexcept
    {
      return sw.template vsra<S> ();
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::vsrad () const noexcept
    {
      return sd.template vsra<S> ();
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vsraq (size_t n) const noexcept
    {
      return sq.vsra (n);
    }

    /***************
     * bsll / bsrl *
     ***************/

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::bsll () const noexcept
    {
      return ub.template esll<S> ();
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::bsll (size_t n) const noexcept
    {
      return ub.esll (n);
    }

    template <size_t B>
    template <size_t S>
    inline constexpr Register<B>
    Register<B>::bsrl () const noexcept
    {
      return ub.template esrl<S> ();
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::bsrl (size_t n) const noexcept
    {
      return ub.esrl (n);
    }

    /*****************
     * vzero / vones *
     *****************/

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vzero () noexcept
    {
      return u8v_t::vzero ();
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::vones () noexcept
    {
      return u8v_t::vones ();
    }

    /***************
     * bind / load *
     ***************/

    template <size_t B>
    inline constexpr Register<B> *
    Register<B>::bind (void *p) noexcept
    {
      return reinterpret_cast<Register<B> *>(p);
    }

    template <size_t B>
    inline constexpr const Register<B> *
    Register<B>::bind (const void *p) noexcept
    {
      return reinterpret_cast<const Register<B> *>(p);
    }

    template <size_t B>
    inline constexpr Register<B>
    Register<B>::load (const void *p) noexcept
    {
      return *bind (p);
    }

    /**/
  } // SIMD
} // RngMTE
