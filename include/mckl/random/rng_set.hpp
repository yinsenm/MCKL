//============================================================================
// MCKL/include/mckl/random/rng_set.hpp
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

#ifndef MCKL_RANDOM_RNG_SET_HPP
#define MCKL_RANDOM_RNG_SET_HPP

#include <mckl/random/internal/common.hpp>
#include <mckl/random/rng.hpp>
#include <mckl/random/seed.hpp>

#if MCKL_HAS_TBB
#include <tbb/combinable.h>
#endif

/// \brief Default RNG set type
/// \ingroup Config
#ifndef MCKL_RNG_SET_TYPE
#if MCKL_USE_TBB_TLS
#define MCKL_RNG_SET_TYPE ::mckl::RNGSetTBB
#else
#define MCKL_RNG_SET_TYPE ::mckl::RNGSetVector
#endif
#endif

namespace mckl
{

/// \brief Scalar RNG set
/// \ingroup Random
template <typename RNGType = RNG>
class RNGSetScalar
{
    MCKL_DEFINE_NEW_DELETE(RNGSetScalar<RNGType>)

    public:
    using rng_type = RNGType;
    using size_type = std::size_t;

    explicit RNGSetScalar(size_type N = 0) : size_(N) { seed(); }

    size_type size() const { return size_; }

    void resize(std::size_t) {}

    void seed() { Seed::instance()(rng_); }

    rng_type &operator[](size_type) { return rng_; }

    private:
    std::size_t size_;
    rng_type rng_;
}; // class RNGSetScalar

/// \brief Vector RNG set
/// \ingroup Random
template <typename RNGType = RNGMini>
class RNGSetVector
{
    public:
    using rng_type = RNGType;
    using size_type = typename Vector<rng_type>::size_type;

    explicit RNGSetVector(size_type N = 0) : rng_(N, rng_type()) { seed(); }

    size_type size() const { return rng_.size(); }

    void resize(std::size_t n)
    {
        if (n == rng_.size())
            return;

        if (n < rng_.size())
            rng_.resize(n);

        size_type m = rng_.size();
        rng_.resize(n);
        Seed::instance()(n - m, rng_.data() + m);
    }

    void seed() { Seed::instance()(rng_.size(), rng_.begin()); }

    rng_type &operator[](size_type id) { return rng_[id % size()]; }

    private:
    Vector<rng_type> rng_;
}; // class RNGSetVector

#if MCKL_HAS_TBB

/// \brief Thread-local storage RNG set using tbb::combinable
/// \ingroup Random
template <typename RNGType = RNG>
class RNGSetTBB
{
    public:
    using rng_type = RNGType;
    using size_type = std::size_t;

    explicit RNGSetTBB(size_type N = 0)
        : size_(N), rng_([]() {
            rng_type rng;
            Seed::instance()(rng);
            return rng;
        })
    {
        seed();
    }

    size_type size() const { return size_; }

    void resize(std::size_t) {}

    void seed() { rng_.clear(); }

    rng_type &operator[](size_type) { return rng_.local(); }

    private:
    std::size_t size_;
    ::tbb::combinable<rng_type> rng_;
}; // class RNGSetTBB

#endif // MCKL_HAS_TBB

/// \brief Default RNG set
/// \ingroup Random
template <typename RNGType = typename std::conditional<
              std::is_same<MCKL_RNG_SET_TYPE<RNG>, RNGSetVector<RNG>>::value,
              RNGMini, RNG>::type>
using RNGSet = MCKL_RNG_SET_TYPE<RNGType>;

/// \brief Particle::rng_set_type trait
/// \ingroup Traits
MCKL_DEFINE_TYPE_DISPATCH_TRAIT(RNGSetType, rng_set_type, RNGSet<>)

} // namespace mckl

#endif // MCKL_RANDOM_RNG_SET_HPP
