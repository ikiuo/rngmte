#include <cinttypes>
#include <cstdio>
#include <ctime>

#include <random>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../include/rngmte/std.hpp"
#include "../include/rngmte.hpp"

#if defined(_WIN32) || defined(_WIN64)
#  define RngMTE_WINDOWS 1
#  define NOMINMAX 1
#  include <windows.h>
#endif

static bool flag_verbose = false;
static bool flag_json = false;
static bool flag_test = false;
static bool flag_perf = false;
static int exit_code = 0;
static const size_t check_count = 100 * 1000;

/*
 *
 */

inline static void
UNUSED (...)
{
  /*NOOP*/
}

#if defined(__GNUC__)
#define __noinline __attribute__ ((noinline))
#elif defined(_MSC_VER)
#include <intrin.h>
#define __noinline __declspec (noinline)
#endif

#if (defined(__amd64) || defined(__i386) ||     \
     defined(__x86) || defined(__x86_64))
#define CPU_RDTSC 1
#else
#define CPU_RDTSC 0
#endif

inline uint64_t
perftime ()
{
#if defined(_MSC_VER) || (CPU_RDTSC && defined(__clang__))

  return __rdtsc ();

#elif defined(__GNUC__) && CPU_RDTSC

  uint32_t eax, edx;

  __asm__ volatile ("rdtsc" : "=a"(eax), "=d"(edx));
  return (uint64_t (edx) << 32) | eax;

#else

  timespec c;

  clock_gettime (CLOCK_REALTIME, &c);
  return ((uint64_t)c.tv_sec * 1000 * 1000 * 1000 + c.tv_nsec);

#endif
}

/*
 *
 */

struct save_ostream
{
  std::ostream &out;
  std::ios_base::fmtflags f;
  std::ostream::char_type  c;
  std::streamsize w;
  std::streamsize p;

  save_ostream (std::ostream &os)
    : out (os)
    , f (os.flags ())
    , c (os.fill ())
    , w (os.width ())
    , p (os.precision ())
  {
    /*NOOP*/
  }

  ~save_ostream ()
  {
    out.flags (f);
    out.fill (c);
    out.width (w);
    out.precision (p);
  }
};

struct save_ios_cout : save_ostream { save_ios_cout () : save_ostream (std::cout) {} };
struct save_ios_cerr : save_ostream { save_ios_cerr () : save_ostream (std::cerr) {} };
struct save_ios { save_ios_cout cout; save_ios_cerr cerr; };

inline std::string
toString (double x)
{
  char buffer[16];

  snprintf (buffer, sizeof (buffer), "%7.4f", x);
  return buffer;
}

/*
 *
 */

template <typename T>
__noinline static void
discard (T &rnd, size_t count)
{
  rnd.discard (count);
}

template <typename T>
static uint64_t
perf_discard (T &rnd, size_t count)
{
  size_t check = check_count;
  uint64_t total = 0;

  while (count)
    {
      size_t step = std::min (check, count);
      uint64_t ptime = perftime ();

      discard<T> (rnd, step);

      total += perftime () - ptime;
      count -= step;
    }
  return total;
}

template <typename R, typename T>
__noinline static R
generate (T &rnd)
{
  return rnd ();
}

template <typename T>
static uint64_t
perf_generate (T &rnd, size_t count)
{
  size_t check = check_count;
  uint64_t total = 0;
  uint64_t last = 0;

  while (count)
    {
      size_t step = std::min (check, count);
      uint64_t ptime = perftime ();

      for (size_t i = 0; i < step; ++i)
        last = generate<typename T::result_type, T> (rnd);

      total += perftime () - ptime + (last & 1);
      count -= step;
    }
  return total;
}

/*
 *
 */

template <typename RS>
struct TestBase
{
  using result_type = typename RS::result_type;
  using result_list = std::vector<result_type>;

  const char **name;
  size_t name_size;
  result_type s;
  result_list r;

  TestBase (const char **p)
    : name (p)
    , name_size (0)
    , s ()
    , r ()
  {
    for (; *p; ++p)
      name_size = std::max<size_t> (name_size, std::string (*p).size ());
  }

  virtual void seed (result_type = RS::default_seed) {}
  virtual void discard (unsigned long long) {}
  virtual void generate () {}

  virtual void load (std::istream &) {}
  virtual void save (std::ostream &) {}

  bool
  check ()
  {
    save_ios save;
    bool success = true;

    for (size_t i = 0; i < r.size (); ++i)
      if (s != r[i])
        {
          std::cerr << "error: "
                    << std::hex
                    << name[0] << "(0x" << s << ")"
                    << " != "
                    << name[i + 1] << "(0x" << r[i] << ")"
                    << std::endl;
          exit_code = 2;
          success = false;
        }
    return success;
  }

  bool
  genchk ()
  {
    generate ();
    return check ();
  }

  void
  test (const char *message)
  {
    if (flag_verbose || !flag_json)
      (flag_json ? std::cerr : std::cout) << message << std::endl;
    for (size_t i = 1; i <= 20000; ++i)
      {
        if (!genchk ())
          {
            std::cerr << "index=" << i << std::endl;
	    seed ();
            return;
          }
        if (i == 10000 && flag_verbose)
          {
            save_ios save;

            (flag_json ? std::cerr : std::cout)
              << "    Generate[10000]:" << std::endl
              << "        " << std::setw (int (name_size)) << std::right << name[0]
              << " : " << std::setw (0) << s << std::endl;
            for (size_t i = 0; i < r.size (); ++i)
              (flag_json ? std::cerr : std::cout)
                << "        " << std::setw (int (name_size)) << std::right << name[i + 1]
                << " : " << std::setw (0) << r[i] << std::endl;
          }
      }

    if (true)
      for (size_t i = 1; i < RS::state_size + 16; ++i)
	for (size_t j = 1; j < RS::state_size * 2 + 16; ++j)
	  {
	    seed ();
	    discard (i - 1);
	    if (!genchk ())
	      {
		std::cerr << "discard[i]: " << i << ", " << j << std::endl;
		seed ();
		return;
	      }
	    discard (j - 1);
	    if (!genchk ())
	      {
		std::cerr << "discard[j]: " << i << ", " << j << std::endl;
		seed ();
		return;
	      }
	  }

    if (true)
      {
	std::stringstream buf;

	save (buf);
	seed ();
	load (buf);
	if (!genchk ())
	  {
	    seed ();
	    return;
	  }
      }
  }

  template <typename T>
  void
  perf_rnd (T &rnd, bool generate, const char *tname, bool end = false)
  {
    const auto &func = (generate ? perf_generate<T> : perf_discard<T>);
    save_ios save;

    const size_t count = check_count;
    const size_t loop = 1000;
    uint64_t best = UINT64_MAX;

    for (size_t i = 0; i < loop; ++i)
      best = std::min (best, func (rnd, count));

    double value = double (best) / count;
    if (flag_verbose)
      (flag_json ? std::cerr : std::cout)
        << "  "
        << std::right << std::setw (int (name_size)) << tname
        << " : " << toString(value)
        << " = " << std::right << std::setw (10) << best
        << " / " << std::left << std::setw (0) << count
        << std::endl;
    if (flag_json)
      std::cout << "    \"" << tname << "\": " << value << (end ? "" : ",") << std::endl;
  }
};

template <typename T1, typename T2>
static void
test_perf (const char **name1, const char **name2)
{
  T1 rng1 (name1);
  T2 rng2 (name2);

  if (flag_test)
    {
      rng1.test ("Test(32bit):");
      rng2.test ("Test(64bit):");
    }
  if (flag_perf)
    {
      if (flag_json)
        std::cout << "{" << std::endl
                  << "  \"generate\": {" << std::endl;
      rng1.perf ("Generate(32bit):", true);
      rng2.perf ("Generate(64bit):", true, true);
      if (flag_json)
        std::cout << "  }," << std::endl
                  << "  \"discard\": {" << std::endl;
      rng1.perf ("Discard(32bit):", false);
      rng2.perf ("Discard(64bit):", false, true);
      if (flag_json)
        std::cout << "  }" << std::endl
                  << "}" << std::endl;
    }
}

/*
 *
 */

template <typename RS,
          typename R0, typename R1, typename R2, typename R3,
          typename R4, typename R5, typename R6, typename R7,
	  typename R8, typename R9, typename RA, typename RB,
	  typename RC, typename RD, typename RE, typename RF,
	  typename RG, typename RH>
struct TestRngMTE : TestBase<RS>
{
  using base_type = TestBase<RS>;
  using result_type = typename base_type::result_type;
  using result_list = typename base_type::result_list;

  const char **&name = base_type::name;
  result_type &s = base_type::s;
  result_list &r = base_type::r;

  RS rs;
  R0 r0; R1 r1; R2 r2; R3 r3;
  R4 r4; R5 r5; R6 r6; R7 r7;
  R8 r8; R9 r9; RA ra; RB rb;
  RC rc; RD rd; RE re; RF rf;
  RG rg; RH rh;

  TestRngMTE (const char **name)
    : base_type (name)
  {
    r.resize (18);
  }

  void
  seed (result_type seed = RS::default_seed)
  {
    rs.seed (seed);
    r0.seed (seed); r1.seed (seed); r2.seed (seed); r3.seed (seed);
    r4.seed (seed); r5.seed (seed); r6.seed (seed); r7.seed (seed);
    r8.seed (seed); r9.seed (seed); ra.seed (seed); rb.seed (seed);
    rc.seed (seed); rd.seed (seed); re.seed (seed); rf.seed (seed);
    rg.seed (seed); rh.seed (seed);
  }

  template <typename T>
  void
  seed (T &seed)
  {
    rs.seed (seed);
    r0.seed (seed); r1.seed (seed); r2.seed (seed); r3.seed (seed);
    r4.seed (seed); r5.seed (seed); r6.seed (seed); r7.seed (seed);
    r8.seed (seed); r9.seed (seed); ra.seed (seed); rb.seed (seed);
    rc.seed (seed); rd.seed (seed); re.seed (seed); rf.seed (seed);
    rg.seed (seed); rh.seed (seed);
  }

  inline void
  discard (unsigned long long n)
  {
    rs.discard (n);
    r0.discard (n); r1.discard (n); r2.discard (n); r3.discard (n);
    r4.discard (n); r5.discard (n); r6.discard (n); r7.discard (n);
    r8.discard (n); r9.discard (n); ra.discard (n); rb.discard (n);
    rc.discard (n); rd.discard (n); re.discard (n); rf.discard (n);
    rg.discard (n); rh.discard (n);
  }

  void
  generate ()
  {
    s = rs ();
    r[ 0] = r0 (); r[ 1] = r1 (); r[ 2] = r2 (); r[ 3] = r3 ();
    r[ 4] = r4 (); r[ 5] = r5 (); r[ 6] = r6 (); r[ 7] = r7 ();
    r[ 8] = r8 (); r[ 9] = r9 (); r[10] = ra (); r[11] = rb ();
    r[12] = rc (); r[13] = rd (); r[14] = re (); r[15] = rf ();
    r[16] = rg (); r[17] = rh ();
  }

  void
  load (std::istream &stream)
  {
    stream >> rs
	   >> r0 >> r1 >> r2 >> r3 >> r4 >> r5 >> r6 >> r7
	   >> r8 >> r9 >> ra >> rb >> rc >> rd >> re >> rf
	   >> rg >> rh;
  }

  void
  save (std::ostream &stream)
  {
    stream << rs << std::endl
	   << r0 << std::endl << r1 << std::endl
	   << r2 << std::endl << r3 << std::endl
	   << r4 << std::endl << r5 << std::endl
	   << r6 << std::endl << r7 << std::endl
	   << r8 << std::endl << r9 << std::endl
	   << ra << std::endl << rb << std::endl
	   << rc << std::endl << rd << std::endl
	   << re << std::endl << rf << std::endl
	   << rg << std::endl << rh << std::endl;
  }

  bool
  perf (const char *message, bool gen, bool end = false)
  {
    if (flag_verbose || !flag_json)
      (flag_json ? std::cerr : std::cout) << message << std::endl;

    base_type::perf_rnd (rs, gen, name[ 0]);
    base_type::perf_rnd (r0, gen, name[ 1]);
    base_type::perf_rnd (r1, gen, name[ 2]);
    base_type::perf_rnd (r2, gen, name[ 3]);
    base_type::perf_rnd (r3, gen, name[ 4]);
    base_type::perf_rnd (r4, gen, name[ 5]);
    base_type::perf_rnd (r5, gen, name[ 6]);
    base_type::perf_rnd (r6, gen, name[ 7]);
    base_type::perf_rnd (r7, gen, name[ 8]);
    base_type::perf_rnd (r8, gen, name[ 9]);
    base_type::perf_rnd (r9, gen, name[10]);
    base_type::perf_rnd (ra, gen, name[11]);
    base_type::perf_rnd (rb, gen, name[12]);
    base_type::perf_rnd (rc, gen, name[13]);
    base_type::perf_rnd (rd, gen, name[14]);
    base_type::perf_rnd (re, gen, name[15]);
    base_type::perf_rnd (rf, gen, name[16]);
    base_type::perf_rnd (rg, gen, name[17]);
    base_type::perf_rnd (rh, gen, name[18], end);

    return base_type::genchk ();
  }
};

using namespace RngMTE;

using MteTest32 = TestRngMTE<
  std::mt19937,
  RngMT19937SeqB32,   RngMT19937SeqC32,
  RngMT19937SeqBP32,  RngMT19937SeqCP32,
  RngMT19937SeqSB32,   RngMT19937SeqSC32,
  RngMT19937BlkB32,   RngMT19937BlkC32,
  RngMT19937BlkBV32,  RngMT19937BlkCV32,
  RngMT19937BlkBT32,  RngMT19937BlkCT32,
  RngMT19937BlkSB32,  RngMT19937BlkSC32,
  RngMT19937BlkSBV32, RngMT19937BlkSCV32,
  RngMT19937BlkSBT32, RngMT19937BlkSCT32>;
static const char *test32_name[] = {
  "std::mt19937",
  "RngMT19937SeqB32",   "RngMT19937SeqC32",
  "RngMT19937SeqBP32",  "RngMT19937SeqCP32",
  "RngMT19937SeqSB32",  "RngMT19937SeqSC32",
  "RngMT19937BlkB32",   "RngMT19937BlkC32",
  "RngMT19937BlkBV32",  "RngMT19937BlkCV32",
  "RngMT19937BlkBT32",  "RngMT19937BlkCT32",
  "RngMT19937BlkSB32",  "RngMT19937BlkSC32",
  "RngMT19937BlkSBV32", "RngMT19937BlkSCV32",
  "RngMT19937BlkSBT32", "RngMT19937BlkSCT32",
  nullptr,
};

using MteTest64 = TestRngMTE<
  std::mt19937_64,
  RngMT19937SeqB64,   RngMT19937SeqC64,
  RngMT19937SeqBP64,  RngMT19937SeqCP64,
  RngMT19937SeqSB64,  RngMT19937SeqSC64,
  RngMT19937BlkB64,   RngMT19937BlkC64,
  RngMT19937BlkBV64,  RngMT19937BlkCV64,
  RngMT19937BlkBT64,  RngMT19937BlkCT64,
  RngMT19937BlkSB64,  RngMT19937BlkSC64,
  RngMT19937BlkSBV64, RngMT19937BlkSCV64,
  RngMT19937BlkSBT64, RngMT19937BlkSCT64>;
static const char *test64_name[] = {
  "std::mt19937_64",
  "RngMT19937SeqB64",   "RngMT19937SeqC64",
  "RngMT19937SeqBP64",  "RngMT19937SeqCP64",
  "RngMT19937SeqSB64",  "RngMT19937SeqSC64",
  "RngMT19937BlkB64",   "RngMT19937BlkC64",
  "RngMT19937BlkBV64",  "RngMT19937BlkCV64",
  "RngMT19937BlkBT64",  "RngMT19937BlkCT64",
  "RngMT19937BlkSB64",  "RngMT19937BlkSC64",
  "RngMT19937BlkSBV64", "RngMT19937BlkSCV64",
  "RngMT19937BlkSBT64", "RngMT19937BlkSCT64",
  nullptr,
};

static void
mte_test ()
{
  test_perf<MteTest32, MteTest64> (test32_name, test64_name);
}

/*
 * SFMTE
 */
#ifdef TEST_SFMTE
#include <ext/random>
#include "../include/rngsfmte.hpp"

template <typename RS,
          typename R0>
struct TestRngSFMTE : TestBase<RS>
{
  using base_type = TestBase<RS>;
  using result_type = typename base_type::result_type;
  using result_list = typename base_type::result_list;

  const char **&name = base_type::name;
  result_type &s = base_type::s;
  result_list &r = base_type::r;

  RS rs;
  R0 r0;

  TestRngSFMTE (const char **name)
    : base_type (name)
  {
    r.resize (1);
  }

  void
  seed (result_type seed = RS::default_seed)
  {
    rs.seed (seed);
    r0.seed (seed);
  }

  template <typename T>
  void
  seed (T &seed)
  {
    rs.seed (seed);
    r0.seed (seed);
  }

  inline void
  discard (unsigned long long n)
  {
    rs.discard (n);
    r0.discard (n);
  }

  void
  generate ()
  {
    s = rs ();
    r[0] = r0 ();
  }

  bool
  perf (const char *message, bool gen, bool end = false)
  {
    if (flag_verbose || !flag_json)
      (flag_json ? std::cerr : std::cout) << message << std::endl;

    base_type::perf_rnd (rs, gen, name[ 0]);
    base_type::perf_rnd (r0, gen, name[ 1], end);

    return base_type::genchk ();
  }

  void
  load (std::istream &stream)
  {
    stream >> rs >> r0;
  }

  void
  save (std::ostream &stream)
  {
    stream << rs << std::endl
	   << r0 << std::endl;
  }
};

using RngSFTest32 = TestRngSFMTE<
  __gnu_cxx::sfmt19937,
  RngSFMT19937>;
static const char *sf_test32_name[] = {
  "__gnu_cxx::sfmt19937",
  "RngSFMT19937",
  nullptr,
};

using RngSFTest64 = TestRngSFMTE<
  __gnu_cxx::sfmt19937_64,
  RngSFMT19937_64>;
static const char *sf_test64_name[] = {
  "__gnu_cxx::sfmt19937_64",
  "RngSFMT19937_64",
  nullptr,
};

static void
sfmte_test ()
{
  test_perf<RngSFTest32, RngSFTest64> (sf_test32_name, sf_test64_name);
}

#else

static void sfmte_test () {}

#endif
/*
 *
 */

static const char *program = NULL;

static int
usage ()
{
  std::cout << "使用方法: " << program << " [オプション]" << std::endl
            << std::endl
            << "オプション:" << std::endl
            << "    -v    冗長" << std::endl
            << "    -j    JSON 出力" << std::endl
            << "    -t    動作確認" << std::endl
            << "    -p    処理速度計測" << std::endl
            << std::endl;
  return 1;
}

static char *
shift_arg (int &argc, char **&argv)
{
  char *arg = NULL;

  if (argc > 0)
    {
      arg = *argv;
      --argc;
      ++argv;
    }
  return arg;
}

#define shift()  (shift_arg (argc, argv))

int
main (int argc, char **argv)
{
  int new_argc = 0;
  char **new_argv = argv;
  bool sfmte = false;

  UNUSED (0);

#if RngMTE_WINDOWS
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif

  program = shift ();
  while (argc > 0)
    {
      char *arg = shift ();

      if ((arg[0] != '-') || (arg[1] == 0))
        {
          new_argv[new_argc++] = arg;
          continue;
        }

      int s_opt;

      while ((s_opt = *(++arg)) != 0)
        {
          switch (s_opt)
            {
            case 'v':
              flag_verbose = true;
              continue;

            case 't':
              flag_test = true;
              continue;
            case 'p':
              flag_perf = true;
              continue;
            case 'j':
              flag_json = true;
              continue;
            case 's':
              sfmte = true;
              continue;

            default:
              return usage ();
            }
        }
    }

  if (!flag_test && !flag_perf)
    return usage ();

  argc = new_argc;
  argv = new_argv;

  if (flag_verbose && !flag_json)
    {
      std::cout << "RngMTE_GPR_BITS=" << RngMTE_GPR_BITS << std::endl
                << "RngMTE_GPR32=" << RngMTE_GPR32 << std::endl
                << "RngMTE_GPR64=" << RngMTE_GPR64 << std::endl
                << "RngMTE_BIG_ENDIAN=" << RngMTE_BIG_ENDIAN << std::endl
                << "RngMTE_LITTLE_ENDIAN=" << RngMTE_LITTLE_ENDIAN << std::endl

#if RngMTE_CPU_ARM
                << "RngMTE_CPU_ARM=" << RngMTE_CPU_ARM << std::endl
#endif
#if RngMTE_CPU_AARCH64
                << "RngMTE_CPU_AARCH64=" << RngMTE_CPU_AARCH64 << std::endl
#endif
                << "RngMTE_SIMD_ARM=" << RngMTE_SIMD_ARM << std::endl
                << "RngMTE_SIMD_ARM_NEON=" << RngMTE_SIMD_ARM_NEON << std::endl
                << "RngMTE_SIMD_ARM_MVE=" << RngMTE_SIMD_ARM_MVE << std::endl
                << "RngMTE_SIMD_ARM_SVE=" << RngMTE_SIMD_ARM_SVE << std::endl
                << "RngMTE_SIMD_ARM_SVE2=" << RngMTE_SIMD_ARM_SVE2 << std::endl

#if RngMTE_CPU_X86
                << "RngMTE_CPU_X86=" << RngMTE_CPU_X86 << std::endl
#endif
#if RngMTE_CPU_X64
                << "RngMTE_CPU_X64=" << RngMTE_CPU_X64 << std::endl
#endif
                << "RngMTE_SIMD_X86=" << RngMTE_SIMD_X86 << std::endl
                << "RngMTE_SIMD_X86_MMX=" << RngMTE_SIMD_X86_MMX << std::endl
                << "RngMTE_SIMD_X86_SSE=" << RngMTE_SIMD_X86_SSE << std::endl
                << "RngMTE_SIMD_X86_SSE2=" << RngMTE_SIMD_X86_SSE2 << std::endl
                << "RngMTE_SIMD_X86_SSE3=" << RngMTE_SIMD_X86_SSE3 << std::endl
                << "RngMTE_SIMD_X86_SSSE3=" << RngMTE_SIMD_X86_SSSE3 << std::endl
                << "RngMTE_SIMD_X86_SSE4_1=" << RngMTE_SIMD_X86_SSE4_1 << std::endl
                << "RngMTE_SIMD_X86_SSE4_2=" << RngMTE_SIMD_X86_SSE4_2 << std::endl
                << "RngMTE_SIMD_X86_AVX=" << RngMTE_SIMD_X86_AVX << std::endl
                << "RngMTE_SIMD_X86_AVX2=" << RngMTE_SIMD_X86_AVX2 << std::endl

                << "RngMTE_HAS_SIMD=" << RngMTE_HAS_SIMD << std::endl

                << "RngMTE_CXX20=" << RngMTE_CXX20 << std::endl
                << "RngMTE_HAS_BUILTIN=" << RngMTE_HAS_BUILTIN << std::endl

                << "RngMTE_STD_POPCNT=" << RngMTE_STD_POPCNT << std::endl
                << "RngMTE_HAS_POPCNT32=" << RngMTE_HAS_POPCNT32 << std::endl
                << "RngMTE_HAS_POPCNT64=" << RngMTE_HAS_POPCNT64 << std::endl

                << "RngMTE_builtin_expect=" << RngMTE_builtin_expect << std::endl
                << std::endl
        ;
    }

  if (!flag_json)
    {
      mte_test ();
      sfmte_test ();
    }
  else if (sfmte)
    sfmte_test ();
  else
    mte_test ();
  return exit_code;
}
