//============================================================================
// MCKL/include/mckl/random/normal_mv_distribution.hpp
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

#ifndef MCKL_RANDOM_NORMAL_MV_DISTRIBUTION_HPP
#define MCKL_RANDOM_NORMAL_MV_DISTRIBUTION_HPP

#include <mckl/random/internal/common.hpp>
#include <mckl/random/normal_distribution.hpp>

namespace mckl {

namespace internal {

inline void normal_mv_distribution_mulchol(
    std::size_t n, float *r, std::size_t dim, const float *chol)
{
    cblas_strmm(CblasRowMajor, CblasRight, CblasLower, CblasTrans,
        CblasNonUnit, static_cast<MCKL_BLAS_INT>(n),
        static_cast<MCKL_BLAS_INT>(dim), 1, chol,
        static_cast<MCKL_BLAS_INT>(dim), r, static_cast<MCKL_BLAS_INT>(dim));
}

inline void normal_mv_distribution_mulchol(
    std::size_t n, double *r, std::size_t dim, const double *chol)
{
    cblas_dtrmm(CblasRowMajor, CblasRight, CblasLower, CblasTrans,
        CblasNonUnit, static_cast<MCKL_BLAS_INT>(n),
        static_cast<MCKL_BLAS_INT>(dim), 1, chol,
        static_cast<MCKL_BLAS_INT>(dim), r, static_cast<MCKL_BLAS_INT>(dim));
}

} // namespace internal

template <typename RealType, typename RNGType>
inline void normal_mv_distribution(RNGType &rng, std::size_t n, RealType *r,
    std::size_t dim, RealType mean, RealType chol)
{
    internal::size_check<MCKL_BLAS_INT>(n, "normal_mv_distribution");
    internal::size_check<MCKL_BLAS_INT>(dim, "normal_mv_distribution");

    normal_distribution(rng, n * dim, r, mean, chol);
}

template <typename RealType, typename RNGType>
inline void normal_mv_distribution(RNGType &rng, std::size_t n, RealType *r,
    std::size_t dim, RealType mean, const RealType *chol)
{
    internal::size_check<MCKL_BLAS_INT>(n, "normal_mv_distribution");
    internal::size_check<MCKL_BLAS_INT>(dim, "normal_mv_distribution");

    normal_distribution(
        rng, n * dim, r, const_zero<RealType>(), const_one<RealType>());
    Vector<RealType> cholf(dim * dim);
    for (std::size_t i = 0; i != dim; ++i) {
        for (std::size_t j = 0; j <= i; ++j) {
            cholf[i * dim + j] = *chol++;
        }
    }
    internal::normal_mv_distribution_mulchol(n, r, dim, cholf.data());
    MCKL_PUSH_CLANG_WARNING("-Wfloat-equal")
    MCKL_PUSH_INTEL_WARNING(1572) // floating-point comparison
    if (mean != 0) {
        add(n * dim, mean, r, r);
    }
    MCKL_POP_CLANG_WARNING
    MCKL_POP_INTEL_WARNING
}

template <typename RealType, typename RNGType>
inline void normal_mv_distribution(RNGType &rng, std::size_t n, RealType *r,
    std::size_t dim, const RealType *mean, RealType chol)
{
    internal::size_check<MCKL_BLAS_INT>(n, "normal_mv_distribution");
    internal::size_check<MCKL_BLAS_INT>(dim, "normal_mv_distribution");

    normal_distribution(rng, n * dim, r, const_zero<RealType>(), chol);
    for (std::size_t i = 0; i != n; ++i, r += dim) {
        add<RealType>(dim, mean, r, r);
    }
}

template <typename RealType, typename RNGType>
inline void normal_mv_distribution(RNGType &rng, std::size_t n, RealType *r,
    std::size_t dim, const RealType *mean, const RealType *chol)
{
    internal::size_check<MCKL_BLAS_INT>(n, "normal_mv_distribution");
    internal::size_check<MCKL_BLAS_INT>(dim, "normal_mv_distribution");

    normal_distribution(
        rng, n * dim, r, const_zero<RealType>(), const_one<RealType>());
    Vector<RealType> cholf(dim * dim);
    for (std::size_t i = 0; i != dim; ++i) {
        for (std::size_t j = 0; j <= i; ++j) {
            cholf[i * dim + j] = *chol++;
        }
    }
    internal::normal_mv_distribution_mulchol(n, r, dim, cholf.data());
    for (std::size_t i = 0; i != n; ++i, r += dim) {
        add<RealType>(dim, mean, r, r);
    }
}

/// \brief Multivariate Normal distribution
/// \ingroup Distribution
///
/// \details
/// The distribution is parameterized by its mean vector and the lower
/// triangular elements of the Cholesky decomposition of the covaraince matrix,
/// packed row by row.
template <typename RealType>
class NormalMVDistribution
{
    MCKL_DEFINE_RANDOM_DISTRIBUTION_ASSERT_BLAS_TYPE(NormalMV)

  public:
    using result_type = RealType;
    using distribution_type = NormalMVDistribution<RealType>;

    MCKL_PUSH_CLANG_WARNING("-Wpadded")
    class param_type
    {
      public:
        using result_type = RealType;
        using distribution_type = NormalMVDistribution<RealType>;

        explicit param_type(std::size_t dim = 1)
            : mean_(dim, 0)
            , chol_(dim * (dim + 1) / 2, 0)
            , is_scalar_mean_(true)
            , is_scalar_chol_(true)
        {
            scalar_chol(1);
        }

        param_type(std::size_t dim, result_type mean, result_type chol)
            : mean_(dim, mean)
            , chol_(dim * (dim + 1) / 2, 0)
            , is_scalar_mean_(true)
            , is_scalar_chol_(true)
        {
            scalar_chol(chol);
        }

        param_type(std::size_t dim, result_type mean, const result_type *chol)
            : mean_(dim, mean)
            , chol_(chol, chol + dim * (dim + 1) / 2)
            , is_scalar_mean_(true)
            , is_scalar_chol_(false)
        {
        }

        param_type(std::size_t dim, const result_type *mean, result_type chol)
            : mean_(mean, mean + dim)
            , chol_(dim * (dim + 1) / 2, 0)
            , is_scalar_mean_(false)
            , is_scalar_chol_(true)
        {
            scalar_chol(chol);
        }

        param_type(
            std::size_t dim, const result_type *mean, const result_type *chol)
            : mean_(mean, mean + dim)
            , chol_(chol, chol + dim * (dim + 1) / 2)
            , is_scalar_mean_(false)
            , is_scalar_chol_(false)
        {
        }

        std::size_t dim() const { return mean_.size(); }

        const result_type *mean() const { return mean_.data(); }

        const result_type *chol() const { return chol_.data(); }

        friend bool operator==(
            const param_type &param1, const param_type &param2)
        {
            if (param1.mean_ != param2.mean_) {
                return false;
            }
            if (param1.chol_ != param2.chol_) {
                return false;
            }
            if (param1.is_scalar_mean_ != param2.is_scalar_mean_) {
                return false;
            }
            if (param1.is_scalar_chol_ != param2.is_scalar_chol_) {
                return false;
            }
            return true;
        }

        friend bool operator!=(
            const param_type &param1, const param_type &param2)
        {
            return !(param1 == param2);
        }

        template <typename CharT, typename Traits>
        friend std::basic_ostream<CharT, Traits> &operator<<(
            std::basic_ostream<CharT, Traits> &os, const param_type &param)
        {
            if (!os) {
                return os;
            }

            os << param.mean_ << ' ';
            os << param.chol_ << ' ';
            os << param.is_scalar_mean_ << ' ';
            os << param.is_scalar_chol_;

            return os;
        }

        template <typename CharT, typename Traits>
        friend std::basic_istream<CharT, Traits> &operator>>(
            std::basic_istream<CharT, Traits> &is, param_type &param)
        {
            if (!is) {
                return is;
            }

            param_type tmp;

            is >> std::ws >> tmp.mean_;
            is >> std::ws >> tmp.chol_;
            is >> std::ws >> tmp.is_scalar_mean_;
            is >> std::ws >> tmp.is_scalar_chol_;

            if (is) {
                param = std::move(tmp);
            } else {
                is.setstate(std::ios_base::failbit);
            }

            return is;
        }

      private:
        Vector<result_type> mean_;
        Vector<result_type> chol_;
        bool is_scalar_mean_;
        bool is_scalar_chol_;

        friend distribution_type;

        void scalar_chol(result_type chol)
        {
            for (std::size_t i = 0; i != dim(); ++i) {
                chol_[(i + 1) * (i + 2) / 2 - 1] = chol;
            }
        }
    }; // class param_type
    MCKL_POP_CLANG_WARNING

    /// \brief Construct a distribution with scalar mean and scalar covariance
    explicit NormalMVDistribution(std::size_t dim = 1) : param_(dim)
    {
        reset();
    }

    /// \brief Construct a distribution with scalar mean and scalar covariance
    NormalMVDistribution(std::size_t dim, result_type mean, result_type chol)
        : param_(dim, mean, chol)
    {
        reset();
    }

    /// \brief Construct a distribution with scalar mean and vector covariance
    NormalMVDistribution(
        std::size_t dim, result_type mean, const result_type *chol)
        : param_(dim, mean, chol)
    {
        reset();
    }

    /// \brief Construct a distribution with vector mean and scalar covariance
    NormalMVDistribution(
        std::size_t dim, const result_type *mean, result_type chol)
        : param_(dim, mean, chol)
    {
        reset();
    }

    /// \brief Construct a distribution with vector mean and vector covariance
    NormalMVDistribution(
        std::size_t dim, const result_type *mean, const result_type *chol)
        : param_(dim, mean, chol)
    {
        reset();
    }

    explicit NormalMVDistribution(const param_type &param) : param_(param)
    {
        reset();
    }

    explicit NormalMVDistribution(param_type &&param)
        : param_(std::move(param))
    {
        reset();
    }

    template <typename OutputIter>
    OutputIter min(OutputIter first) const
    {
        return std::fill_n(
            first, dim(), std::numeric_limits<result_type>::lowest());
    }

    template <typename OutputIter>
    OutputIter max(OutputIter first) const
    {
        return std::fill_n(
            first, dim(), std::numeric_limits<result_type>::max());
    }

    void reset() {}

    std::size_t dim() const { return param_.dim(); }

    const result_type *mean() const { return param_.mean(); }

    const result_type *chol() const { return param_.chol(); }

    const param_type &param() const { return param_; }

    void param(const param_type &param)
    {
        param_ = param;
        reset();
    }

    void param(param_type &&param)
    {
        param_ = std::move(param);
        reset();
    }

    template <typename RNGType>
    void operator()(RNGType &rng, result_type *r)
    {
        operator()(rng, r, param_);
    }

    template <typename RNGType>
    void operator()(RNGType &rng, result_type *r, const param_type &param)
    {
        generate(rng, r, param);
    }

    template <typename RNGType>
    void operator()(RNGType &rng, std::size_t n, result_type *r)
    {
        operator()(rng, n, r, param_);
    }

    template <typename RNGType>
    void operator()(
        RNGType &rng, std::size_t n, result_type *r, const param_type &param)
    {
        if (param.is_scalar_mean_ && param.is_scalar_chol_) {
            normal_mv_distribution(
                rng, n, r, param.dim(), param.mean()[0], param.chol()[0]);
        } else if (param.is_scalar_mean_ && !param.is_scalar_chol_) {
            normal_mv_distribution(
                rng, n, r, param.dim(), param.mean()[0], param.chol());
        } else if (!param.is_scalar_mean_ && param.is_scalar_chol_) {
            normal_mv_distribution(
                rng, n, r, param.dim(), param.mean(), param.chol()[0]);
        } else if (!param.is_scalar_mean_ && !param.is_scalar_chol_) {
            normal_mv_distribution(
                rng, n, r, param.dim(), param.mean(), param.chol());
        }
    }

    friend bool operator==(
        const distribution_type &dist1, const distribution_type &dist2)
    {
        if (dist1.param_ != dist2.param_) {
            return false;
        }
        return true;
    }

    friend bool operator!=(
        const distribution_type &dist1, const distribution_type &dist2)
    {
        return !(dist1 == dist2);
    }

    template <typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> &operator<<(
        std::basic_ostream<CharT, Traits> &os, const distribution_type &dist)
    {
        if (!os) {
            return os;
        }

        os << dist.param_;

        return os;
    }

    template <typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits> &operator>>(
        std::basic_istream<CharT, Traits> &is, distribution_type &dist)
    {
        if (!is) {
            return is;
        }

        param_type param;
        is >> std::ws >> param;
        if (is) {
            dist.param_ = std::move(param);
        }

        return is;
    }

  private:
    param_type param_;

    template <typename RNGType>
    void generate(RNGType &rng, result_type *r, const param_type &param)
    {
        MCKL_PUSH_CLANG_WARNING("-Wfloat-equal")
        MCKL_PUSH_INTEL_WARNING(1572) // floating-point comparison
        if (param.is_scalar_mean_ && param.is_scalar_chol_) {
            NormalDistribution<RealType> normal(
                param.mean()[0], param.chol()[0]);
            for (std::size_t i = 0; i != param.dim(); ++i) {
                r[i] = normal(rng);
            }
        } else if (param.is_scalar_mean_ && !param.is_scalar_chol_) {
            NormalDistribution<RealType> normal(0, 1);
            for (std::size_t i = 0; i != param.dim(); ++i) {
                r[i] = normal(rng);
            }
            mulchol(r, param);
            if (param.mean()[0] != 0) {
                add<result_type>(param.dim(), param.mean(), r, r);
            }
        } else if (!param.is_scalar_mean_ && param.is_scalar_chol_) {
            NormalDistribution<RealType> normal(0, param.chol()[0]);
            for (std::size_t i = 0; i != param.dim(); ++i) {
                r[i] = normal(rng);
            }
            add<result_type>(param.dim(), param.mean(), r, r);
        } else if (!param.is_scalar_mean_ && !param.is_scalar_chol_) {
            NormalDistribution<RealType> normal(0, 1);
            normal(rng, param.dim(), r);
            mulchol(r, param);
            add<result_type>(param.dim(), param.mean(), r, r);
        }
        MCKL_POP_CLANG_WARNING
        MCKL_POP_INTEL_WARNING
    }

    void mulchol(float *r, const param_type &param)
    {
        internal::cblas_stpmv(internal::CblasRowMajor, internal::CblasLower,
            internal::CblasNoTrans, internal::CblasNonUnit,
            static_cast<MCKL_BLAS_INT>(dim()), param.chol(), r, 1);
    }

    void mulchol(double *r, const param_type &param)
    {
        internal::cblas_dtpmv(internal::CblasRowMajor, internal::CblasLower,
            internal::CblasNoTrans, internal::CblasNonUnit,
            static_cast<MCKL_BLAS_INT>(dim()), param.chol(), r, 1);
    }
}; // class NormalMVDistribution

template <typename RealType, typename RNGType>
inline void rand(
    RNGType &rng, NormalMVDistribution<RealType> &distribution, RealType *r)
{
    distribution(rng, r);
}

template <typename RealType, typename RNGType>
inline void rand(RNGType &rng, NormalMVDistribution<RealType> &distribution,
    std::size_t n, RealType *r)
{
    distribution(rng, n, r);
}

} // namespace mckl

#endif // MCKL_RANDOM_NORMAL_MV_DISTRIBUTION_HPP
