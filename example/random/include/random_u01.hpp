//============================================================================
// MCKL/example/random/include/random_u01.hpp
//----------------------------------------------------------------------------
// MCKL: Monte Carlo Kernel Library
//----------------------------------------------------------------------------
// Copyright (c) 2013-2018, Yan Zhou
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

#ifndef MCKL_EXAMPLE_RANDOM_U01_HPP
#define MCKL_EXAMPLE_RANDOM_U01_HPP

#include <mckl/random/philox.hpp>
#include <mckl/random/u01.hpp>
#include <mckl/random/uniform_int_distribution.hpp>
#include "random_common.hpp"

template <typename Lower, typename RealType>
inline bool random_u01_check_lb(RealType x)
{
    MCKL_PUSH_CLANG_WARNING("-Wfloat-equal")
    MCKL_PUSH_INTEL_WARNING(1572) // floating-point comparison
    return std::is_same<Lower, mckl::Closed>::value ? x == 0 : x > 0;
    MCKL_POP_CLANG_WARNING
    MCKL_POP_INTEL_WARNING
}

template <typename Upper, typename RealType>
inline bool random_u01_check_ub(RealType x)
{
    MCKL_PUSH_CLANG_WARNING("-Wfloat-equal")
    MCKL_PUSH_INTEL_WARNING(1572) // floating-point comparison
    return std::is_same<Upper, mckl::Closed>::value ? x == 1 : x < 1;
    MCKL_POP_CLANG_WARNING
    MCKL_POP_INTEL_WARNING
}

template <typename RealType>
inline std::string random_u01_minimum(RealType x)
{
    std::stringstream ss;
    MCKL_PUSH_CLANG_WARNING("-Wfloat-equal")
    MCKL_PUSH_INTEL_WARNING(1572) // floating-point comparison
    if (x == 0)
        ss << 0;
    else
        ss << "2^" << std::log2(x);
    MCKL_POP_CLANG_WARNING
    MCKL_POP_INTEL_WARNING

    return ss.str();
}

template <typename RealType>
inline std::string random_u01_maximum(RealType x)
{
    std::stringstream ss;
    MCKL_PUSH_CLANG_WARNING("-Wfloat-equal")
    MCKL_PUSH_INTEL_WARNING(1572) // floating-point comparison
    if (x == 1)
        ss << 1;
    else
        ss << "1 - 2^" << std::log2(static_cast<RealType>(1) - x);
    MCKL_POP_CLANG_WARNING
    MCKL_POP_INTEL_WARNING

    return ss.str();
}

class RandomU01Range
{
  public:
    MCKL_PUSH_CLANG_WARNING("-Wpadded")
    bool pass_b;
    bool pass_l;
    bool pass_u;
    std::string function;
    std::string minimum;
    std::string maximum;
    std::string lower;
    std::string upper;
    double c1;
    double c2;
    MCKL_POP_CLANG_WARNING
}; // class RandomU01Range

template <typename UIntType, typename RealType, typename Lower, typename Upper>
inline RandomU01Range random_u01(std::size_t N, std::size_t M)
{
    mckl::Philox4x32Engine<UIntType> rng;
    mckl::UniformIntDistribution<std::size_t> rsize(N / 2, N);

    mckl::Vector<RealType> r1(N);
    mckl::Vector<RealType> r2(N);
    mckl::Vector<UIntType> ru(N);

    RealType lb = mckl::u01<UIntType, RealType, Lower, Upper>(
        std::numeric_limits<UIntType>::min());

    RealType ub = mckl::u01<UIntType, RealType, Lower, Upper>(
        std::numeric_limits<UIntType>::max());

    bool pass_b = true;
    bool pass_l = random_u01_check_lb<Lower>(lb);
    bool pass_u = random_u01_check_ub<Upper>(ub);

    bool has_cycles = mckl::StopWatch::has_cycles();

    double c1 = has_cycles ? std::numeric_limits<double>::max() : 0.0;
    double c2 = has_cycles ? std::numeric_limits<double>::max() : 0.0;
    for (std::size_t k = 0; k != 10; ++k) {
        std::size_t n = 0;
        mckl::StopWatch watch1;
        mckl::StopWatch watch2;
        for (std::size_t i = 0; i != M; ++i) {
            std::size_t K = rsize(rng);
            r1.resize(K);
            r2.resize(K);
            ru.resize(K);
            n += K;

            for (std::size_t j = 0; j != K; ++j) {
                UIntType u = rng();
                switch (u % 3) {
                    case 0:
                        ru[j] = 0;
                        break;
                    case 1:
                        ru[j] = std::numeric_limits<UIntType>::max();
                        break;
                    default:
                        ru[j] = u;
                }
            }

            watch1.start();
            for (std::size_t j = 0; j != K; ++j)
                r1[j] = mckl::u01<UIntType, RealType, Lower, Upper>(ru[j]);
            watch1.stop();

            watch2.start();
            mckl::u01<UIntType, RealType, Lower, Upper>(
                K, ru.data(), r2.data());
            watch2.stop();

            RealType lbi = *std::min_element(r1.begin(), r1.end());
            RealType ubi = *std::max_element(r1.begin(), r1.end());

            pass_b = pass_b && r2 == r1;
            pass_l = pass_l && lbi >= lb;
            pass_u = pass_u && ubi <= ub;
        }
        if (has_cycles) {
            c1 = std::min(c1, 1.0 * watch1.cycles() / n);
            c2 = std::min(c2, 1.0 * watch2.cycles() / n);
        } else {
            c1 = std::max(c1, n / watch1.seconds() * 1e-6);
            c2 = std::max(c2, n / watch2.seconds() * 1e-6);
        }
    }

    std::stringstream ss;
    ss << "u01" + random_typename<Lower>() + random_typename<Upper>() + "<";
    ss << std::setw(10) << std::left << random_typename<UIntType>() + ",";
    ss << random_typename<RealType>() + ">";

    RandomU01Range result;
    result.pass_b = pass_b;
    result.pass_l = pass_l;
    result.pass_u = pass_u;
    result.function = ss.str();
    result.minimum = random_u01_minimum(lb);
    result.maximum = random_u01_maximum(ub);
    result.c1 = c1;
    result.c2 = c2;

    return result;
}

template <typename UIntType, typename RealType>
inline RandomU01Range random_u01(std::size_t N, std::size_t M)
{
    constexpr int w = std::numeric_limits<UIntType>::digits;
    constexpr int m = std::numeric_limits<RealType>::digits;
    constexpr int p = (m + w - 1) / w;
    constexpr int Q = 1 > p ? 1 : p;

    mckl::Philox4x32Engine<UIntType> rng;
    mckl::UniformIntDistribution<std::size_t> rsize(N / 2, N);

    mckl::Vector<RealType> r1(N);
    mckl::Vector<RealType> r2(N);
    mckl::Vector<UIntType> ru(N * Q);

    std::fill_n(ru.begin(), Q, std::numeric_limits<UIntType>::min());
    RealType lb = mckl::u01_canonical<UIntType, RealType, Q>(ru.data());

    std::fill_n(ru.begin(), Q, std::numeric_limits<UIntType>::max());
    RealType ub = mckl::u01_canonical<UIntType, RealType, Q>(ru.data());

    bool pass_b = true;
    bool pass_l = true;
    bool pass_u = true;

    bool has_cycles = mckl::StopWatch::has_cycles();

    double c1 = has_cycles ? std::numeric_limits<double>::max() : 0.0;
    double c2 = has_cycles ? std::numeric_limits<double>::max() : 0.0;
    for (std::size_t k = 0; k != 10; ++k) {
        std::size_t n = 0;
        mckl::StopWatch watch1;
        mckl::StopWatch watch2;
        for (std::size_t i = 0; i != M; ++i) {
            std::size_t K = rsize(rng);
            r1.resize(K);
            r2.resize(K);
            ru.resize(K * Q);
            n += K;

            for (std::size_t j = 0; j != K * Q; ++j) {
                UIntType u = rng();
                switch (u % 3) {
                    case 0:
                        ru[j] = 0;
                        break;
                    case 1:
                        ru[j] = std::numeric_limits<UIntType>::max();
                        break;
                    default:
                        ru[j] = u;
                }
            }

            watch1.start();
            const UIntType *uptr = ru.data();
            for (std::size_t j = 0; j != K; ++j, uptr += Q)
                r1[j] = mckl::u01_canonical<UIntType, RealType, Q>(uptr);
            watch1.stop();

            watch2.start();
            mckl::u01_canonical<UIntType, RealType, Q>(
                K, ru.data(), r2.data());
            watch2.stop();

            RealType lbi = *std::min_element(r1.begin(), r1.end());
            RealType ubi = *std::max_element(r1.begin(), r1.end());

            pass_b = pass_b && r2 == r1;
            pass_l = pass_l && lbi >= lb;
            pass_u = pass_u && ubi <= ub;
        }
        if (has_cycles) {
            c1 = std::min(c1, 1.0 * watch1.cycles() / n);
            c2 = std::min(c2, 1.0 * watch2.cycles() / n);
        } else {
            c1 = std::max(c1, n / watch1.seconds() * 1e-6);
            c2 = std::max(c2, n / watch2.seconds() * 1e-6);
        }
    }

    std::stringstream ss;
    ss << "u01_canonical<";
    ss << std::setw(10) << std::left << random_typename<UIntType>() + ",";
    ss << std::setw(13) << std::left << random_typename<RealType>() + ",";
    ss << Q << ">";

    RandomU01Range result;
    result.pass_b = pass_b;
    result.pass_l = pass_l;
    result.pass_u = pass_u;
    result.function = ss.str();
    result.minimum = random_u01_minimum(lb);
    result.maximum = random_u01_maximum(ub);
    result.c1 = c1;
    result.c2 = c2;

    return result;
}

template <typename Lower, typename Upper>
inline void random_u01(std::size_t N, std::size_t M, int nwid, int twid)
{
    mckl::Vector<RandomU01Range> range;
    range.push_back(random_u01<std::uint32_t, float, Lower, Upper>(N, M));
    range.push_back(random_u01<std::uint64_t, float, Lower, Upper>(N, M));
    range.push_back(random_u01<std::uint32_t, double, Lower, Upper>(N, M));
    range.push_back(random_u01<std::uint64_t, double, Lower, Upper>(N, M));
    range.push_back(
        random_u01<std::uint32_t, long double, Lower, Upper>(N, M));
    range.push_back(
        random_u01<std::uint64_t, long double, Lower, Upper>(N, M));

    for (std::size_t i = 0; i != range.size(); ++i) {
        std::cout << std::setw(nwid) << std::left << range[i].function;
        std::cout << std::setw(twid) << std::right << range[i].minimum;
        std::cout << std::setw(twid) << std::right << range[i].maximum;
        std::cout << std::setw(twid) << std::right << range[i].c1;
        std::cout << std::setw(twid) << std::right << range[i].c2;
        std::string pass;
        pass += range[i].pass_b ? "-" : "*";
        pass += range[i].pass_l ? "-" : "*";
        pass += range[i].pass_u ? "-" : "*";
        pass +=
            random_pass(range[i].pass_b && range[i].pass_l && range[i].pass_u);
        std::cout << std::setw(15) << std::right << pass;
        std::cout << std::endl;
    }
}

inline void random_u01(std::size_t N, std::size_t M, int nwid, int twid)
{
    mckl::Vector<RandomU01Range> range;
    range.push_back(random_u01<std::uint32_t, float>(N, M));
    range.push_back(random_u01<std::uint64_t, float>(N, M));
    range.push_back(random_u01<std::uint32_t, double>(N, M));
    range.push_back(random_u01<std::uint64_t, double>(N, M));
    range.push_back(random_u01<std::uint32_t, long double>(N, M));
    range.push_back(random_u01<std::uint64_t, long double>(N, M));

    for (std::size_t i = 0; i != range.size(); ++i) {
        std::cout << std::setw(nwid) << std::left << range[i].function;
        std::cout << std::setw(twid) << std::right << range[i].minimum;
        std::cout << std::setw(twid) << std::right << range[i].maximum;
        std::cout << std::setw(twid) << std::right << range[i].c1;
        std::cout << std::setw(twid) << std::right << range[i].c2;
        std::string pass;
        pass += range[i].pass_b ? "-" : "*";
        pass += range[i].pass_l ? "-" : "*";
        pass += range[i].pass_u ? "-" : "*";
        pass +=
            random_pass(range[i].pass_b && range[i].pass_l && range[i].pass_u);
        std::cout << std::setw(15) << std::right << pass;
        std::cout << std::endl;
    }
}

inline void random_u01(std::size_t N, std::size_t M)
{
    const int nwid = 40;
    const int twid = 15;
    const std::size_t lwid = nwid + twid * 4 + 15;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::string(lwid, '=') << std::endl;

    std::cout << std::setw(nwid) << std::left << "Function";
    std::cout << std::setw(twid) << std::right << "Mininum";
    std::cout << std::setw(twid) << std::right << "Maximum";
    if (mckl::StopWatch::has_cycles()) {
        std::cout << std::setw(twid) << std::right << "cpE (S)";
        std::cout << std::setw(twid) << std::right << "cpE (B)";
    } else {
        std::cout << std::setw(twid) << std::right << "ME/s (S)";
        std::cout << std::setw(twid) << std::right << "ME/s (B)";
    }
    std::cout << std::setw(15) << std::right << "Deterministics";
    std::cout << std::endl;

    std::cout << std::string(lwid, '-') << std::endl;
    random_u01<mckl::Closed, mckl::Closed>(N, M, nwid, twid);
    std::cout << std::string(lwid, '-') << std::endl;
    random_u01<mckl::Closed, mckl::Open>(N, M, nwid, twid);
    std::cout << std::string(lwid, '-') << std::endl;
    random_u01<mckl::Open, mckl::Closed>(N, M, nwid, twid);
    std::cout << std::string(lwid, '-') << std::endl;
    random_u01<mckl::Open, mckl::Open>(N, M, nwid, twid);
    std::cout << std::string(lwid, '-') << std::endl;
    random_u01(N, M, nwid, twid);
    std::cout << std::string(lwid, '-') << std::endl;
}

#endif // MCKL_EXAMPLE_RANDOM_U01_HPP
