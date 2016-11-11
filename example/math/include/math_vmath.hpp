//============================================================================
// MCKL/example/math/include/math_vmath.hpp
//----------------------------------------------------------------------------
// MCKL: Monte Carlo Kernel Library
//----------------------------------------------------------------------------
// Copyright (c) 2013-2016, Yan Zhou
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//============================================================================

#ifndef MCKL_EXAMPLE_MATH_VMATH_HPP
#define MCKL_EXAMPLE_MATH_VMATH_HPP

#include <mckl/math/vmath.hpp>
#include <mckl/random/uniform_real_distribution.hpp>
#include <mckl/utility/stop_watch.hpp>

#if MCKL_HAS_AESNI
#include <mckl/random/aes.hpp>
using MCKLRNGType = mckl::ARS;
#else
#include <mckl/random/philox.hpp>
using MCKLRNGType = mckl::Philox4x32;
#endif

using FunctionA1R1S = void (*)(std::size_t, const float *, float *);

using FunctionA1R1D = void (*)(std::size_t, const double *, double *);

using FunctionA1R2S = void (*)(std::size_t, const float *, float *, float *);

using FunctionA1R2D = void (*)(
    std::size_t, const double *, double *, double *);

using FunctionA2R1S = void (*)(
    std::size_t, const float *, const float *, float *);

using FunctionA2R1D = void (*)(
    std::size_t, const double *, const double *, double *);

#define MCKL_EXAMPLE_MATH_VMATH_RUN_A1R1(func)                                \
    watch1.start();                                                           \
    mckl::func<float>(K, as.data(), rs1.data());                              \
    watch1.stop();                                                            \
                                                                              \
    watch2.start();                                                           \
    mckl::func(K, as.data(), rs2.data());                                     \
    watch2.stop();                                                            \
                                                                              \
    watch3.start();                                                           \
    mckl::func<double>(K, ad.data(), rd1.data());                             \
    watch3.stop();                                                            \
                                                                              \
    watch4.start();                                                           \
    mckl::func(K, ad.data(), rd2.data());                                     \
    watch4.stop();

#define MCKL_EXAMPLE_MATH_VMATH_RUN_A2R1(func)                                \
    watch1.start();                                                           \
    mckl::func<float>(K, as.data(), bs.data(), rs1.data());                   \
    watch1.stop();                                                            \
                                                                              \
    watch2.start();                                                           \
    mckl::func(K, as.data(), bs.data(), rs2.data());                          \
    watch2.stop();                                                            \
                                                                              \
    watch3.start();                                                           \
    mckl::func<double>(K, ad.data(), bd.data(), rd1.data());                  \
    watch3.stop();                                                            \
                                                                              \
    watch4.start();                                                           \
    mckl::func(K, ad.data(), bd.data(), rd2.data());                          \
    watch4.stop();

#define MCKL_EXAMPLE_MATH_VMATH_RUN_A1R2(func)                                \
    watch1.start();                                                           \
    mckl::func<float>(K, as.data(), rs1.data(), rs3.data());                  \
    watch1.stop();                                                            \
                                                                              \
    watch2.start();                                                           \
    mckl::func(K, as.data(), rs2.data(), rs4.data());                         \
    watch2.stop();                                                            \
                                                                              \
    watch3.start();                                                           \
    mckl::func<double>(K, ad.data(), rd1.data(), rd3.data());                 \
    watch3.stop();                                                            \
                                                                              \
    watch4.start();                                                           \
    mckl::func(K, ad.data(), rd2.data(), rd4.data());                         \
    watch4.stop();

#define MCKL_EXAMPLE_DEFINE_MATH_VMATH(AR, func, ls, us, ld, ud)              \
    inline void math_vmath_##func(                                            \
        std::size_t N, std::size_t M, mckl::Vector<MathvMathPerf> &perf)      \
    {                                                                         \
        mckl::UniformRealDistribution<float> unifs(ls, us);                   \
        mckl::UniformRealDistribution<double> unifd(ld, ud);                  \
        std::uniform_int_distribution<std::size_t> rsize(N / 2, N);           \
        MCKLRNGType rng;                                                      \
                                                                              \
        mckl::Vector<float> as(N);                                            \
        mckl::Vector<float> bs(N);                                            \
        mckl::Vector<double> ad(N);                                           \
        mckl::Vector<double> bd(N);                                           \
        mckl::Vector<float> rs1(N);                                           \
        mckl::Vector<float> rs2(N);                                           \
        mckl::Vector<float> rs3(N);                                           \
        mckl::Vector<float> rs4(N);                                           \
        mckl::Vector<double> rd1(N);                                          \
        mckl::Vector<double> rd2(N);                                          \
        mckl::Vector<double> rd3(N);                                          \
        mckl::Vector<double> rd4(N);                                          \
                                                                              \
        std::fill(rs1.begin(), rs1.end(), 0);                                 \
        std::fill(rs2.begin(), rs2.end(), 0);                                 \
        std::fill(rd1.begin(), rd1.end(), 0);                                 \
        std::fill(rd2.begin(), rd2.end(), 0);                                 \
                                                                              \
        bool has_cycles = mckl::StopWatch::has_cycles();                      \
                                                                              \
        float e1 = 0;                                                         \
        float e2 = 0;                                                         \
        double e3 = 0;                                                        \
        double e4 = 0;                                                        \
        double c1 = has_cycles ? std::numeric_limits<double>::max() : 0.0;    \
        double c2 = has_cycles ? std::numeric_limits<double>::max() : 0.0;    \
        double c3 = has_cycles ? std::numeric_limits<double>::max() : 0.0;    \
        double c4 = has_cycles ? std::numeric_limits<double>::max() : 0.0;    \
        for (std::size_t k = 0; k != 10; ++k) {                               \
            std::size_t n = 0;                                                \
            mckl::StopWatch watch1;                                           \
            mckl::StopWatch watch2;                                           \
            mckl::StopWatch watch3;                                           \
            mckl::StopWatch watch4;                                           \
            for (std::size_t i = 0; i != M; ++i) {                            \
                std::size_t K = rsize(rng);                                   \
                n += K;                                                       \
                                                                              \
                mckl::rand(rng, unifs, K, as.data());                         \
                mckl::rand(rng, unifs, K, bs.data());                         \
                mckl::rand(rng, unifd, K, ad.data());                         \
                mckl::rand(rng, unifd, K, bd.data());                         \
                                                                              \
                MCKL_EXAMPLE_MATH_VMATH_RUN_##AR(func);                       \
                                                                              \
                mckl::sub(K, rs1.data(), rs2.data(), rs1.data());             \
                mckl::div(K, rs1.data(), rs2.data(), rs2.data());             \
                mckl::sub(K, rd1.data(), rd2.data(), rd1.data());             \
                mckl::div(K, rd1.data(), rd2.data(), rd2.data());             \
                mckl::abs(K, rs1.data(), rs1.data());                         \
                mckl::abs(K, rs2.data(), rs2.data());                         \
                mckl::abs(K, rd1.data(), rd1.data());                         \
                mckl::abs(K, rd2.data(), rd2.data());                         \
                                                                              \
                for (std::size_t j = 0; j != K; ++j)                          \
                    e1 = std::max(e1, rs1[j]);                                \
                for (std::size_t j = 0; j != K; ++j)                          \
                    e2 = std::max(e2, rs2[j]);                                \
                for (std::size_t j = 0; j != K; ++j)                          \
                    e3 = std::max(e3, rd1[j]);                                \
                for (std::size_t j = 0; j != K; ++j)                          \
                    e4 = std::max(e4, rd2[j]);                                \
            }                                                                 \
            if (has_cycles) {                                                 \
                c1 = std::min(c1, 1.0 * watch1.cycles() / n);                 \
                c2 = std::min(c2, 1.0 * watch2.cycles() / n);                 \
                c3 = std::min(c3, 1.0 * watch3.cycles() / n);                 \
                c4 = std::min(c4, 1.0 * watch4.cycles() / n);                 \
            } else {                                                          \
                c1 = std::max(c1, n / watch1.seconds() * 1e-6);               \
                c2 = std::max(c2, n / watch2.seconds() * 1e-6);               \
                c3 = std::max(c3, n / watch3.seconds() * 1e-6);               \
                c4 = std::max(c4, n / watch4.seconds() * 1e-6);               \
            }                                                                 \
        }                                                                     \
                                                                              \
        MathvMathPerf result;                                                 \
        result.name = #func;                                                  \
        result.e1 = e1 / std::numeric_limits<float>::epsilon();               \
        result.e2 = e2 / std::numeric_limits<float>::epsilon();               \
        result.e3 = e3 / std::numeric_limits<double>::epsilon();              \
        result.e4 = e4 / std::numeric_limits<double>::epsilon();              \
        result.c1 = c1;                                                       \
        result.c2 = c2;                                                       \
        result.c3 = c3;                                                       \
        result.c4 = c4;                                                       \
                                                                              \
        perf.push_back(result);                                               \
    }

class MathvMathPerf
{
    public:
    std::string name;
    float e1;
    float e2;
    double e3;
    double e4;
    double c1;
    double c2;
    double c3;
    double c4;
}; // class MathvMathPerf

MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, acos, -1.0f, 1.0f, -1.0, 1.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, asin, -1.0f, 1.0f, -1.0, 1.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, atan, -5.0f, 5.0f, -5.0, 5.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A2R1, atan2, -1e3f, 1e3f, -1e3, 1e3)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, cos, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, sin, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R2, sincos, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, tan, -1e3f, 1e3f, -1e3, 1e3)

MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, acosh, 4.0f, 1e19f, 1.001, 1e154)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, asinh, 4.0f, 1e19f, 0.002, 1e154)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, atanh, 0.77f, 0.99999f, 0.005, 0.99999)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, cosh, -87.0f, 87.0f, -675.0, 675.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, sinh, -87.0f, 87.0f, -675.0, 675.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, tanh, -9.0f, 9.0f, -19.0, 19.0)

MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, cbrt, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A2R1, hypot, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, inv, 1e-3f, 1e4f, 1e-3, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, invcbrt, 0.1f, 1e4f, 0.1, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, invsqrt, 0.1f, 1e4f, 0.1, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A2R1, pow, 0.1f, 10.0f, 5.0, 100.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, pow2o3, 0.1f, 1e4f, 0.1, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, pow3o2, 0.1f, 1e4f, 0.1, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, sqrt, 0.0f, 1e4f, 0.0, 1e4)

MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, exp, -87.0f, 87.0f, -707.0, 707.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, expm1, -70.0f, 70.0f, -500.0, 500.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, log, 0.1f, 1e4, 0.1, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, log10, 0.1f, 1e4, 0.1, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, log1p, 1.0f, 999.0f, 1.0, 999.0)

MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, abs, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A2R1, add, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A2R1, div, 1e-4f, 1e4f, 1e-4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A2R1, mul, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, sqr, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A2R1, sub, -1e4f, 1e4f, -1e4, 1e4)

MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, ceil, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, floor, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R2, modf, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, nearbyint, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, rint, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, round, -1e4f, 1e4f, -1e4, 1e4)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, trunc, -1e4f, 1e4f, -1e4, 1e4)

MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, cdfnorm, -8.0f, 5.0f, -32.0, 8.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(
    A1R1, cdfnorminv, 1e-5f, 0.99999f, 1e-5, 0.99999)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, erf, 1.0f, 4.0f, 0.5, 5.9)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, erfc, -3.0f, 9.0f, -5.0, 25.0)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(
    A1R1, erfinv, -0.99999f, 0.99999f, -0.99999, 0.99999)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, erfcinv, 1e-5f, 1.99999f, 1e-5, 1.99999)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, lgamma, 1e-5f, 1e3f, 1e-5, 1e3)
MCKL_EXAMPLE_DEFINE_MATH_VMATH(A1R1, tgamma, 1e-4f, 35.0f, 1e-4, 171.0)

inline void math_vmath(std::size_t N, std::size_t M)
{
    mckl::Vector<MathvMathPerf> perf;
    math_vmath_add(N, M, perf);
    math_vmath_sub(N, M, perf);
    math_vmath_sqr(N, M, perf);
    math_vmath_mul(N, M, perf);
    math_vmath_abs(N, M, perf);

    math_vmath_inv(N, M, perf);
    math_vmath_div(N, M, perf);
    math_vmath_sqrt(N, M, perf);
    math_vmath_invsqrt(N, M, perf);
    math_vmath_cbrt(N, M, perf);
    math_vmath_invcbrt(N, M, perf);
    math_vmath_pow2o3(N, M, perf);
    math_vmath_pow3o2(N, M, perf);
    math_vmath_pow(N, M, perf);
    math_vmath_hypot(N, M, perf);

    math_vmath_exp(N, M, perf);
    math_vmath_expm1(N, M, perf);
    math_vmath_log(N, M, perf);
    math_vmath_log10(N, M, perf);
    math_vmath_log1p(N, M, perf);

    math_vmath_cos(N, M, perf);
    math_vmath_sin(N, M, perf);
    math_vmath_sincos(N, M, perf);
    math_vmath_tan(N, M, perf);
    math_vmath_acos(N, M, perf);
    math_vmath_asin(N, M, perf);
    math_vmath_atan(N, M, perf);
    math_vmath_atan2(N, M, perf);

    math_vmath_cosh(N, M, perf);
    math_vmath_sinh(N, M, perf);
    math_vmath_tanh(N, M, perf);
    math_vmath_acosh(N, M, perf);
    math_vmath_asinh(N, M, perf);
    math_vmath_atanh(N, M, perf);

    math_vmath_erf(N, M, perf);
    math_vmath_erfc(N, M, perf);
    math_vmath_cdfnorm(N, M, perf);
    math_vmath_erfinv(N, M, perf);
    math_vmath_erfcinv(N, M, perf);
    math_vmath_cdfnorminv(N, M, perf);
    math_vmath_lgamma(N, M, perf);
    math_vmath_tgamma(N, M, perf);

    math_vmath_floor(N, M, perf);
    math_vmath_ceil(N, M, perf);
    math_vmath_trunc(N, M, perf);
    math_vmath_round(N, M, perf);
    math_vmath_nearbyint(N, M, perf);
    math_vmath_rint(N, M, perf);

    const int nwid = 10;
    const int twid = 10;
    const int ewid = 15;
    const std::size_t lwid = nwid + twid * 4 + ewid * 4;

    std::cout << std::string(lwid, '=') << std::endl;

    std::cout << std::setw(nwid) << std::left << "Function";
    if (mckl::StopWatch::has_cycles()) {
        std::cout << std::setw(twid) << std::right << "cpE (S)";
        std::cout << std::setw(twid) << std::right << "cpE (SV)";
        std::cout << std::setw(twid) << std::right << "cpE (D)";
        std::cout << std::setw(twid) << std::right << "cpE (DV)";
    } else {
        std::cout << std::setw(twid) << std::right << "ME/s (S)";
        std::cout << std::setw(twid) << std::right << "ME/s (SV)";
        std::cout << std::setw(twid) << std::right << "ME/s (D)";
        std::cout << std::setw(twid) << std::right << "ME/s (DV)";
    }
    std::cout << std::setw(ewid) << std::right << "Err.Abs (S)";
    std::cout << std::setw(ewid) << std::right << "Err.Rel (S)";
    std::cout << std::setw(ewid) << std::right << "Err.Abs (D)";
    std::cout << std::setw(ewid) << std::right << "Err.Rel (D)";
    std::cout << std::endl;

    std::cout << std::string(lwid, '-') << std::endl;

    for (std::size_t i = 0; i != perf.size(); ++i) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(nwid) << std::left << perf[i].name;
        std::cout << std::setw(twid) << std::right << perf[i].c1;
        std::cout << std::setw(twid) << std::right << perf[i].c2;
        std::cout << std::setw(twid) << std::right << perf[i].c3;
        std::cout << std::setw(twid) << std::right << perf[i].c4;
        std::cout.unsetf(std::ios_base::floatfield);
        std::cout << std::setprecision(2);
        std::cout << std::setw(ewid) << std::right << perf[i].e1;
        std::cout << std::setw(ewid) << std::right << perf[i].e2;
        std::cout << std::setw(ewid) << std::right << perf[i].e3;
        std::cout << std::setw(ewid) << std::right << perf[i].e4;
        std::cout << std::endl;
    }

    std::cout << std::string(lwid, '-') << std::endl;
}

#endif // MCKL_EXAMPLE_MATH_VMATH_HPP
