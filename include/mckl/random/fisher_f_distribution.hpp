//============================================================================
// MCKL/include/mckl/random/fisher_f_distribution.hpp
//----------------------------------------------------------------------------
// MCKL: Monte Carlo Kernel Library
//----------------------------------------------------------------------------
// Copyright (c) 2013-2017, Yan Zhou
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

#ifndef MCKL_RANDOM_FISHER_F_DISTRIBUTION_HPP
#define MCKL_RANDOM_FISHER_F_DISTRIBUTION_HPP

#include <mckl/random/internal/common.hpp>
#include <mckl/random/chi_squared_distribution.hpp>

namespace mckl
{

namespace internal
{

template <typename RealType>
inline bool fisher_f_distribution_check_param(RealType m, RealType n)
{
    return m > 0 && n > 0;
}

template <std::size_t K, typename RealType, typename RNGType>
inline void fisher_f_distribution_impl(
    RNGType &rng, std::size_t n, RealType *r, RealType df1, RealType df2)
{
    alignas(32) std::array<RealType, K> s;
    chi_squared_distribution(rng, n, s.data(), df1);
    chi_squared_distribution(rng, n, r, df2);
    mul(n, 1 / df1, s.data(), s.data());
    mul(n, 1 / df2, r, r);
    div(n, s.data(), r, r);
}

} // namespace mckl::internal

MCKL_DEFINE_RANDOM_DISTRIBUTION_BATCH_2(
    FisherF, fisher_f, RealType, RealType, m, RealType, n)

/// \brief Fisher-F distribution
/// \ingroup Distribution
template <typename RealType>
class FisherFDistribution
{
    MCKL_DEFINE_RANDOM_DISTRIBUTION_ASSERT_REAL_TYPE(FisherF)
    MCKL_DEFINE_RANDOM_DISTRIBUTION_2(
        FisherF, fisher_f, RealType, result_type, m, 1, result_type, n, 1)
    MCKL_DEFINE_RANDOM_DISTRIBUTION_MEMBER_2(ChiSquaredDistribution<RealType>,
        chi_squared_m_, ChiSquaredDistribution<RealType>, chi_squared_n_)

    public:
    result_type min() const { return 0; }

    result_type max() const { return std::numeric_limits<result_type>::max(); }

    void reset()
    {
        chi_squared_m_ = ChiSquaredDistribution<RealType>(m());
        chi_squared_n_ = ChiSquaredDistribution<RealType>(n());
    }

    private:
    template <typename RNGType>
    result_type generate(RNGType &rng, const param_type &param)
    {
        if (param == param_)
            return (chi_squared_m_(rng) / m()) / (chi_squared_n_(rng) / n());

        ChiSquaredDistribution<RealType> chi_squared_m(param.m());
        ChiSquaredDistribution<RealType> chi_squared_n(param.n());

        return (chi_squared_m(rng) / param.m()) /
            (chi_squared_n(rng) / param.n());
    }
}; // class FisherFDistribution

MCKL_DEFINE_RANDOM_DISTRIBUTION_RAND(FisherF, RealType)

} // namespace mckl

#endif // MCKL_RANDOM_FISHER_F_DISTRIBUTION_HPP
