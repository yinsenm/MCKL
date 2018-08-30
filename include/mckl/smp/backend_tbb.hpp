//============================================================================
// MCKL/include/mckl/smp/backend_tbb.hpp
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

#ifndef MCKL_SMP_BACKEND_TBB_HPP
#define MCKL_SMP_BACKEND_TBB_HPP

#include <mckl/smp/backend_base.hpp>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>

namespace mckl {

namespace internal {

template <typename IntType>
inline ::tbb::blocked_range<IntType> backend_tbb_range(
    IntType N, std::size_t grainsize)
{
    return grainsize == 0 ? ::tbb::blocked_range<IntType>(0, N) :
                            ::tbb::blocked_range<IntType>(0, N, grainsize);
}

} // namespace mckl::internal

/// \brief SMCSampler<T>::eval_type subtype using Intel Threading Building
/// Blocks
/// \ingroup TBB
template <typename T, typename Derived>
class SMCSamplerEvalSMP<T, Derived, BackendTBB>
    : public SMCSamplerEvalBase<T, Derived>
{
    class work_type
    {
      public:
        using size_type = typename Particle<T>::size_type;

        work_type(SMCSamplerEvalSMP<T, Derived, BackendTBB> *wptr,
            std::size_t iter, Particle<T> *pptr)
            : wptr_(wptr), iter_(iter), pptr_(pptr)
        {
        }

        void operator()(const ::tbb::blocked_range<size_type> &range) const
        {
            wptr_->eval_range(iter_, pptr_->range(range.begin(), range.end()));
        }

      private:
        SMCSamplerEvalSMP<T, Derived, BackendTBB> *const wptr_;
        const std::size_t iter_;
        Particle<T> *const pptr_;
    }; // class work_type

  public:
    void operator()(std::size_t iter, Particle<T> &particle)
    {
        run(iter, particle);
    }

  protected:
    MCKL_DEFINE_SMP_BACKEND_SPECIAL(TBB, SMCSamplerEval)

    void run(std::size_t iter, Particle<T> &particle)
    {
        run(iter, particle, 1);
    }

    template <typename... Args>
    void run(std::size_t iter, Particle<T> &particle, std::size_t grainsize,
        Args &&... args)
    {
        this->eval_first(iter, particle);
        ::tbb::parallel_for(
            internal::backend_tbb_range(particle.size(), grainsize),
            work_type(this, iter, &particle), std::forward<Args>(args)...);
        this->eval_last(iter, particle);
    }
}; // class SMCSamplerEvalSMP

/// \brief SMCEstimator<T>::eval_type subtype using Intel Threading Building
/// Blocks
/// \ingroup TBB
template <typename T, typename Derived>
class SMCEstimatorEvalSMP<T, Derived, BackendTBB>
    : public SMCEstimatorEvalBase<T, Derived>
{
    class work_type
    {
      public:
        using size_type = typename Particle<T>::size_type;

        work_type(SMCEstimatorEvalSMP<T, Derived, BackendTBB> *wptr,
            std::size_t iter, std::size_t dim, Particle<T> *pptr, double *r)
            : wptr_(wptr), iter_(iter), dim_(dim), pptr_(pptr), r_(r)
        {
        }

        void operator()(const ::tbb::blocked_range<size_type> &range) const
        {
            wptr_->eval_range(iter_, dim_,
                pptr_->range(range.begin(), range.end()),
                r_ + static_cast<std::size_t>(range.begin()) * dim_);
        }

      private:
        SMCEstimatorEvalSMP<T, Derived, BackendTBB> *const wptr_;
        const std::size_t iter_;
        const std::size_t dim_;
        Particle<T> *const pptr_;
        double *const r_;
    }; // class work_type

  public:
    void operator()(
        std::size_t iter, std::size_t dim, Particle<T> &particle, double *r)
    {
        run(iter, dim, particle, r);
    }

  protected:
    MCKL_DEFINE_SMP_BACKEND_SPECIAL(TBB, SMCEstimatorEval)

    void run(
        std::size_t iter, std::size_t dim, Particle<T> &particle, double *r)
    {
        run(iter, dim, particle, r, 1);
    }

    template <typename... Args>
    void run(std::size_t iter, std::size_t dim, Particle<T> &particle,
        double *r, std::size_t grainsize, Args &&... args)
    {
        this->eval_first(iter, particle);
        ::tbb::parallel_for(
            internal::backend_tbb_range(particle.size(), grainsize),
            work_type(this, iter, dim, &particle, r),
            std::forward<Args>(args)...);
        this->eval_last(iter, particle);
    }
}; // class SMCEstimatorEvalSMP

/// \brief SMCSampler<T>::eval_type subtype using Intel Threading Building
/// Blocks
/// \ingroup TBB
template <typename T, typename Derived>
using SMCSamplerEvalTBB = SMCSamplerEvalSMP<T, Derived, BackendTBB>;

/// \brief SMCEstimator<T>::eval_type subtype using Intel Threading Building
/// Blocks
/// \ingroup TBB
template <typename T, typename Derived>
using SMCEstimatorEvalTBB = SMCEstimatorEvalSMP<T, Derived, BackendTBB>;

} // namespace mckl

#endif // MCKL_SMP_BACKEND_TBB_HPP
