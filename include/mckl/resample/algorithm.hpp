//============================================================================
// MCKL/include/mckl/resample/algorithm.hpp
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

#ifndef MCKL_RESAMPLE_ALGORITHM_HPP
#define MCKL_RESAMPLE_ALGORITHM_HPP

#include <mckl/internal/common.hpp>
#include <mckl/resample/transform.hpp>
#include <mckl/resample/u01_sequence.hpp>

namespace mckl
{

/// \brief Sampler<T>::eval_type subtype
template <typename T>
class ResampleEval
{
    public:
    using eval_type = std::function<void(std::size_t, std::size_t,
        typename Particle<T>::rng_type &, const double *,
        typename Particle<T>::size_type *)>;

    /// \brief Construct a `Sampler::move_type` object
    ///
    /// \param eval A resampling algorithm evaluation object, see interface of
    /// ResampleAlgorithm
    explicit ResampleEval(const eval_type &eval) : eval_(eval) {}

    /// \brief Set a new evaluation object of type eval_type
    void eval(const eval_type &new_eval) { eval_ = new_eval; }

    /// \brief Returns how many particles having non-zero replication number
    void operator()(std::size_t, Particle<T> &particle) const
    {
        runtime_assert(static_cast<bool>(eval_),
            "**ResampleEval::operator()** invalid evaluation object");

        using size_type = typename Particle<T>::size_type;

        const std::size_t N = static_cast<std::size_t>(particle.size());
        Vector<size_type> rep(N);
        Vector<size_type> idx(N);
        eval_(N, N, particle.rng(), particle.weight().data(), rep.data());
        resample_trans_rep_index(N, N, rep.data(), idx.data());
        particle.state().select(N, idx.data());
        particle.weight().set_equal();
    }

    private:
    eval_type eval_;
}; // class ResampleEval

/// \brief Resampling algorithm
/// \ingroup Resample
template <typename U01SeqType, bool Residual>
class ResampleAlgorithm
{
    public:
    /// \brief Generate replication numbers from normalized weights
    ///
    /// \param N Sample size before resampling
    /// \param M Sample size after resampling
    /// \param rng An RNG engine
    /// \param weight N-vector of normalized weights
    /// \param replication N-vector of replication numbers
    template <typename RNGType, typename InputIter, typename OutputIter>
    void operator()(std::size_t N, std::size_t M, RNGType &rng,
        InputIter weight, OutputIter replication) const
    {
        eval(N, M, rng, weight, replication,
            std::integral_constant<bool, Residual>());
    }

    private:
    U01SeqType u01seq_;

    template <typename RNGType, typename InputIter, typename OutputIter>
    void eval(std::size_t N, std::size_t M, RNGType &rng, InputIter weight,
        OutputIter replication, std::false_type) const
    {
        using real_type = typename std::iterator_traits<InputIter>::value_type;

        Vector<real_type> u01(M);
        u01seq_(rng, M, u01.data());
        resample_trans_u01_rep(N, M, weight, u01.data(), replication);
    }

    template <typename RNGType, typename InputIter, typename OutputIter>
    void eval(std::size_t N, std::size_t M, RNGType &rng, InputIter weight,
        OutputIter replication, std::true_type) const
    {
        using real_type = typename std::iterator_traits<InputIter>::value_type;
        using rep_type = typename std::iterator_traits<OutputIter>::value_type;

        Vector<real_type> resid(N);
        Vector<rep_type> integ(N);
        std::size_t R =
            resample_trans_residual(N, M, weight, resid.data(), integ.data());

        Vector<real_type> u01(R);
        u01seq_(rng, R, u01.data());
        resample_trans_u01_rep(N, R, resid.data(), u01.data(), replication);
        for (std::size_t i = 0; i != N; ++i, ++replication)
            *replication += integ[i];
    }
}; // class ResampleAlgorithm

/// \brief Multinomial resampling
/// \ingroup Resample
using ResampleMultinomial = ResampleAlgorithm<U01SequenceSorted, false>;

/// \brief Stratified resampling
/// \ingroup Resample
using ResampleStratified = ResampleAlgorithm<U01SequenceStratified, false>;

/// \brief Systematic resampling
/// \ingroup Resample
using ResampleSystematic = ResampleAlgorithm<U01SequenceSystematic, false>;

/// \brief Residual resampling
/// \ingroup Resample
using ResampleResidual = ResampleAlgorithm<U01SequenceSorted, true>;

/// \brief Residual stratified resampling
/// \ingroup Resample
using ResampleResidualStratified =
    ResampleAlgorithm<U01SequenceStratified, true>;

/// \brief Residual systematic resampling
/// \ingroup Resample
using ResampleResidualSystematic =
    ResampleAlgorithm<U01SequenceSystematic, true>;

} // namespace mckl

#endif // MCKL_RESAMPLE_ALGORITHM_HPP
