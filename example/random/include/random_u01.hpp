//============================================================================
// MCKL/example/random/include/random_u01.hpp
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

#ifndef MCKL_EXAMPLE_RANDOM_U01_HPP
#define MCKL_EXAMPLE_RANDOM_U01_HPP

#include <mckl/random/u01.hpp>
#include <mckl/randomc/u01.h>
#include "random_common.hpp"

#define MCKL_DEFINE_RANDOMC_U01_TEST(                                         \
    ubits, fsuffix, lr, Lower, Upper, RealType)                               \
    template <>                                                               \
    inline RealType random_u01_c<std::uint##ubits##_t, RealType, mckl::Lower, \
        mckl::Upper>(std::uint##ubits##_t u)                                  \
    {                                                                         \
        return mckl_u01_##lr##_u##ubits##fsuffix(u);                          \
    }

#define MCKL_RANDOM_U01_TEST(Lower, Upper)                                    \
    random_u01<std::uint32_t, float, mckl::Lower, mckl::Upper>(               \
        N, M, nwid, swid, twid);                                              \
    random_u01<std::uint64_t, float, mckl::Lower, mckl::Upper>(               \
        N, M, nwid, swid, twid);                                              \
    random_u01<std::uint32_t, double, mckl::Lower, mckl::Upper>(              \
        N, M, nwid, swid, twid);                                              \
    random_u01<std::uint64_t, double, mckl::Lower, mckl::Upper>(              \
        N, M, nwid, swid, twid);                                              \
    random_u01<std::uint32_t, long double, mckl::Lower, mckl::Upper>(         \
        N, M, nwid, swid, twid);                                              \
    random_u01<std::uint64_t, long double, mckl::Lower, mckl::Upper>(         \
        N, M, nwid, swid, twid);

template <typename UIntType, typename RealType, typename, typename>
inline RealType random_u01_c(UIntType u);

MCKL_DEFINE_RANDOMC_U01_TEST(32, f, cc, Closed, Closed, float)
MCKL_DEFINE_RANDOMC_U01_TEST(64, f, cc, Closed, Closed, float)
MCKL_DEFINE_RANDOMC_U01_TEST(32, d, cc, Closed, Closed, double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, d, cc, Closed, Closed, double)
MCKL_DEFINE_RANDOMC_U01_TEST(32, l, cc, Closed, Closed, long double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, l, cc, Closed, Closed, long double)

MCKL_DEFINE_RANDOMC_U01_TEST(32, f, co, Closed, Open, float)
MCKL_DEFINE_RANDOMC_U01_TEST(64, f, co, Closed, Open, float)
MCKL_DEFINE_RANDOMC_U01_TEST(32, d, co, Closed, Open, double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, d, co, Closed, Open, double)
MCKL_DEFINE_RANDOMC_U01_TEST(32, l, co, Closed, Open, long double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, l, co, Closed, Open, long double)

MCKL_DEFINE_RANDOMC_U01_TEST(32, f, oc, Open, Closed, float)
MCKL_DEFINE_RANDOMC_U01_TEST(64, f, oc, Open, Closed, float)
MCKL_DEFINE_RANDOMC_U01_TEST(32, d, oc, Open, Closed, double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, d, oc, Open, Closed, double)
MCKL_DEFINE_RANDOMC_U01_TEST(32, l, oc, Open, Closed, long double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, l, oc, Open, Closed, long double)

MCKL_DEFINE_RANDOMC_U01_TEST(32, f, oo, Open, Open, float)
MCKL_DEFINE_RANDOMC_U01_TEST(64, f, oo, Open, Open, float)
MCKL_DEFINE_RANDOMC_U01_TEST(32, d, oo, Open, Open, double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, d, oo, Open, Open, double)
MCKL_DEFINE_RANDOMC_U01_TEST(32, l, oo, Open, Open, long double)
MCKL_DEFINE_RANDOMC_U01_TEST(64, l, oo, Open, Open, long double)

template <typename UIntType, typename RealType, typename Lower, typename Upper>
inline std::string random_u01_function_name()
{
    std::stringstream ss;
    ss << "u01<uint";
    ss << std::numeric_limits<UIntType>::digits << "_t, ";
    ss << random_typename<RealType>() << ", ";
    ss << random_typename<Lower>() << ", ";
    ss << random_typename<Upper>() << ">";

    return ss.str();
}

template <typename RealType>
inline void random_u01_lb(RealType x, std::string &minimum, std::string &left)
{
    std::stringstream ss;
    if (mckl::internal::is_equal(x, static_cast<RealType>(0)))
        ss << 0;
    else
        ss << "2^" << std::log2(x);
    minimum = ss.str();

    if (x < static_cast<RealType>(0))
        left = "< 0";
    else if (x > static_cast<RealType>(0))
        left = "Open";
    else
        left = "Closed";
}

template <typename RealType>
inline void random_u01_rb(RealType x, std::string &maximum, std::string &right)
{
    std::stringstream ss;
    if (mckl::internal::is_equal(x, static_cast<RealType>(1)))
        ss << 1;
    else
        ss << "1 - 2^" << std::log2(static_cast<RealType>(1) - x);
    maximum = ss.str();
    if (x > static_cast<RealType>(1))
        right = "> 1";
    else if (x < static_cast<RealType>(1))
        right = "Open";
    else
        right = "Closed";
}

template <typename UIntType, typename RealType, typename Lower, typename Upper>
inline void random_u01(
    std::size_t N, std::size_t M, int nwid, int swid, int twid)
{
    mckl::ThreefryEngine<UIntType, UIntType, 4> rng;
    mckl::Vector<UIntType> u(N);
    mckl::Vector<RealType> r(N);
    mckl::Vector<RealType> r1(N);
    mckl::Vector<RealType> r2(N);
    bool pass1 = true;
    bool pass2 = true;
    for (std::size_t i = 0; i != M; ++i) {
        mckl::rand(rng, N, u.data());

        for (std::size_t j = 0; j != N; ++j)
            r[j] = mckl::u01<UIntType, RealType, Lower, Upper>(u[j]);

        for (std::size_t j = 0; j != N; ++j)
            r1[j] = random_u01_c<UIntType, RealType, Lower, Upper>(u[j]);
        pass1 = pass1 && r1 == r;

        mckl::u01<UIntType, RealType, Lower, Upper>(N, u.data(), r2.data());
        pass2 = pass2 && r2 == r;
    }

    std::string function =
        random_u01_function_name<UIntType, RealType, Lower, Upper>();
    std::string minimum;
    std::string maximum;
    std::string left;
    std::string right;
    random_u01_lb(mckl::u01<UIntType, RealType, Lower, Upper>(
                      std::numeric_limits<UIntType>::min()),
        minimum, left);
    random_u01_rb(mckl::u01<UIntType, RealType, Lower, Upper>(
                      std::numeric_limits<UIntType>::max()),
        maximum, right);
    std::cout << std::setw(nwid) << std::left << function;
    std::cout << std::setw(swid) << std::right << minimum;
    std::cout << std::setw(swid) << std::right << maximum;
    std::cout << std::setw(twid) << std::right << left;
    std::cout << std::setw(twid) << std::right << right;
    std::cout << std::setw(twid) << std::right << random_pass(pass1);
    std::cout << std::setw(twid) << std::right << random_pass(pass2);
    std::cout << std::endl;
}

inline void random_u01(std::size_t N, std::size_t M, int, char **)
{
    const int nwid = 45;
    const int swid = 15;
    const int twid = 10;
    const std::size_t lwid = nwid + swid * 2 + twid * 4;

    std::cout << std::string(lwid, '=') << std::endl;
    std::cout << std::setw(nwid) << std::left << "Function";
    std::cout << std::setw(swid) << std::right << "Mininum";
    std::cout << std::setw(swid) << std::right << "Maximum";
    std::cout << std::setw(twid) << std::right << "Lower";
    std::cout << std::setw(twid) << std::right << "Upper";
    std::cout << std::setw(twid) << std::right << "C API";
    std::cout << std::setw(twid) << std::right << "Batch";
    std::cout << std::endl;
    std::cout << std::string(lwid, '-') << std::endl;
    MCKL_RANDOM_U01_TEST(Closed, Closed);
    std::cout << std::string(lwid, '-') << std::endl;
    MCKL_RANDOM_U01_TEST(Closed, Open);
    std::cout << std::string(lwid, '-') << std::endl;
    MCKL_RANDOM_U01_TEST(Open, Closed);
    std::cout << std::string(lwid, '-') << std::endl;
    MCKL_RANDOM_U01_TEST(Open, Open);
    std::cout << std::string(lwid, '-') << std::endl;
}

#endif // MCKL_EXAMPLE_RANDOM_U01_HPP
