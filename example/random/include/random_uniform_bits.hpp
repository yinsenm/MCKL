//============================================================================
// MCKL/example/random/include/random_uniform_bits.hpp
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

#include <mckl/random/uniform_bits_distribution.hpp>
#include "random_common.hpp"

template <typename RNGType, typename UIntType>
inline void random_uniform_bits(std::size_t N, std::size_t M, int nwid,
    int swid, int twid, const std::string &name)
{
    RNGType rng;
    RNGType rng1;
    RNGType rng2;
    mckl::Vector<UIntType> r1;
    mckl::Vector<UIntType> r2;
    r1.reserve(N);
    r2.reserve(N);
    mckl::StopWatch watch1;
    mckl::StopWatch watch2;
    bool pass = true;

    std::uniform_int_distribution<std::size_t> runif(N / 2, N);
    std::size_t num = 0;
    mckl::UniformBitsDistribution<UIntType> rubits;
    for (std::size_t i = 0; i != M; ++i) {
        std::size_t K = runif(rng);
        num += K;
        r1.resize(K);
        r2.resize(K);

        watch1.start();
        for (std::size_t j = 0; j != K; ++j)
            r1[j] = rubits(rng1);
        watch1.stop();

        watch2.start();
        mckl::rand(rng2, rubits, K, r2.data());
        watch2.stop();
        pass = pass && (r1 == r2 || rng != rng);
    }

    bool full = mckl::RNGTraits<RNGType>::is_full_range;
    int rbits = mckl::RNGTraits<RNGType>::bits;
    int tbits = std::numeric_limits<typename RNGType::result_type>::digits;
    int ubits = std::numeric_limits<UIntType>::digits;

    std::cout << std::setw(nwid) << std::left << name;
    std::cout << std::setw(swid) << std::right << (full ? "Yes" : "No");
    std::cout << std::setw(swid) << std::right << rbits;
    std::cout << std::setw(swid) << std::right << tbits;
    std::cout << std::setw(swid) << std::right << ubits;
    std::cout << std::setw(twid) << std::right << random_pass(pass);
    std::cout << std::endl;
}

template <typename RNGType>
inline void random_uniform_bits(
    std::size_t N, std::size_t M, const std::string &name)
{
    const int nwid = 20;
    const int swid = 5;
    const int twid = 15;
    const std::size_t lwid = nwid + swid * 4 + twid;

    std::cout << std::string(lwid, '=') << std::endl;
    std::cout << std::setw(nwid) << std::left << "RNGType";
    std::cout << std::setw(swid) << std::right << "Full";
    std::cout << std::setw(swid) << std::right << "R";
    std::cout << std::setw(swid) << std::right << "T";
    std::cout << std::setw(swid) << std::right << "U";
    std::cout << std::setw(twid) << std::right << "Deterministics";
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::string(lwid, '-') << std::endl;
    random_uniform_bits<RNGType, std::uint16_t>(N, M, nwid, swid, twid, name);
    random_uniform_bits<RNGType, std::uint32_t>(N, M, nwid, swid, twid, name);
    random_uniform_bits<RNGType, std::uint64_t>(N, M, nwid, swid, twid, name);
    std::cout << std::string(lwid, '-') << std::endl;
}
