//============================================================================
// MCKL/include/mckl/resample/index.hpp
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

#ifndef MCKL_RESAMPLE_INDEX_HPP
#define MCKL_RESAMPLE_INDEX_HPP

#include <mckl/internal/common.hpp>

namespace mckl
{

/// \brief Record and trace resampling index
/// \ingroup Resample
template <typename IntType = std::size_t>
class ResampleIndex
{
    public:
    using index_type = IntType;

    ResampleIndex() : iter_size_(0) {}

    /// \brief Number of iterations recorded
    std::size_t iter_size() const { return iter_size_; }

    /// \brief The sample size of the last iteration
    std::size_t size() const
    {
        if (index_.size() == 0)
            return 0;
        return index_.back().size();
    }

    /// \brief The sample size of a given iteration
    std::size_t size(std::size_t iter) const
    {
        if (iter >= index_.size())
            return 0;
        return index_[iter].size();
    }

    /// \brief Reset history
    void reset() { iter_size_ = 0; }

    /// \brief Release memory
    void clear() { index_.clear(); }

    /// \brief Append an identity resampling index
    void push_back(std::size_t N)
    {
        ++iter_size_;
        resize_identity(N);
        if (index_.size() < iter_size_)
            index_.push_back(identity_);
        else
            index_[iter_size_ - 1] = identity_;
    }

    /// \brief Append a resampling index
    template <typename InputIter>
    void push_back(std::size_t N, InputIter first)
    {
        ++iter_size_;
        if (index_.size() < iter_size_)
            index_.emplace_back(N);
        else
            index_[iter_size_ - 1].resize(N);
        std::copy_n(first, N, index_[iter_size_ - 1].begin());
    }

    index_type index(std::size_t id) const
    {
        return index(id, iter_size_ - 1, 0);
    }

    index_type index(std::size_t id, std::size_t iter_back) const
    {
        return index(id, iter_back, 0);
    }

    /// \brief Get the index given the particle ID and iteration number
    index_type index(
        std::size_t id, std::size_t iter_back, std::size_t iter) const
    {
        runtime_assert(iter <= iter_back && iter_back < iter_size(),
            "**ResampleIndex::index** iteration numbers out of range");

        index_type idx = index_.back()[id];
        while (iter_back > iter) {
            --iter_back;
            idx = index_[iter_back][idx];
        }

        return idx;
    }

    std::size_t index_matrix_nrow() const
    {
        return index_matrix_nrow(iter_size_ - 1);
    }

    std::size_t index_matrix_nrow(std::size_t iter_back) const
    {
        runtime_assert(iter_back < iter_size(),
            "**ResampleIndex::index_matrix_nrow** iteration numbers out of "
            "range");

        return index_[iter_back].size();
    }

    std::size_t index_matrix_ncol() const
    {
        return index_matrix_ncol(iter_size_ - 1, 0);
    }

    std::size_t index_matrix_ncol(std::size_t iter_back) const
    {
        return index_matrix_ncol(iter_back, 0);
    }

    std::size_t index_matrix_ncol(
        std::size_t iter_back, std::size_t iter) const
    {
        runtime_assert(iter <= iter_back && iter_back < iter_size(),
            "**ResampleIndex::index_matrix_ncol** iteration numbers out of "
            "range");

        return iter_back - iter + 1;
    }

    Vector<index_type> index_matrix(MatrixLayout layout) const
    {
        return index_matrix(layout, iter_size_ - 1, 0);
    }

    Vector<index_type> index_matrix(
        MatrixLayout layout, std::size_t iter_back) const
    {
        return index_matrix(layout, iter_back, 0);
    }

    /// \brief Get the resampling index matrix.
    Vector<index_type> index_matrix(
        MatrixLayout layout, std::size_t iter_back, std::size_t iter) const
    {
        runtime_assert(iter <= iter_back && iter_back < iter_size(),
            "**ResampleIndex::index_matrix** iteration numbers out of range");

        Vector<index_type> idxmat(
            index_matrix_nrow(iter_back) * index_matrix_ncol(iter_back, iter));
        read_index_matrix(layout, idxmat.begin(), iter_back, iter);

        return idxmat;
    }

    template <typename RandomIter>
    RandomIter read_index_matrix(MatrixLayout layout, RandomIter first) const
    {
        return read_index_matrix(layout, first, iter_size_ - 1, 0);
    }

    template <typename RandomIter>
    RandomIter read_index_matrix(
        MatrixLayout layout, RandomIter first, std::size_t iter_back) const
    {
        return read_index_matrix(layout, first, iter_back, 0);
    }

    /// \brief Read the resampling index matrix into an random access iterator
    ///
    /// \details
    /// The matrix, say \f$M\f$ is assume to be \f$N\f$ by \f$R\f$, where
    /// \f$R\f$ is the number of iterations between `iter` and `iter_back`,
    /// inclusive; and \f$N\f$ is the sample size at iteration `iter_back`. The
    /// output is equivalent to set the \f$M_{i,j}\f$ to
    /// `index(i, j, iter_back)`. Note that, column major will be more
    /// efficient.
    template <typename RandomIter>
    RandomIter read_index_matrix(MatrixLayout layout, RandomIter first,
        std::size_t iter_back, std::size_t iter) const
    {
        runtime_assert(iter <= iter_back && iter_back < iter_size(),
            "**ResampleIndex::read_index_matrix** iteration numbers out of "
            "range");

        using difference_type =
            typename std::iterator_traits<RandomIter>::difference_type;
        const std::size_t N = index_matrix_nrow(iter_back);
        const std::size_t R = index_matrix_ncol(iter_back, iter);

        if (layout == RowMajor) {
            RandomIter back = first + static_cast<difference_type>(R - 1);
            const index_type *idx = index_[iter_back].data();
            for (std::size_t i = 0; i != N; ++i)
                back[static_cast<difference_type>(i * R)] = idx[i];
            for (std::size_t r = 1; r != R; ++r) {
                const std::size_t j = iter_back - r;
                RandomIter last = back;
                --back;
                idx = index_[j].data();
                for (std::size_t i = 0; i != N; ++i) {
                    back[static_cast<difference_type>(i * R)] =
                        idx[static_cast<std::size_t>(
                            last[static_cast<difference_type>(i * R)])];
                }
            }
        }

        if (layout == ColMajor) {
            RandomIter back =
                first + static_cast<difference_type>(N * (R - 1));
            const index_type *idx = index_[iter_back].data();
            std::copy_n(idx, N, back);
            for (std::size_t r = 1; r != R; ++r) {
                const std::size_t j = iter_back - r;
                RandomIter last = back;
                back -= static_cast<difference_type>(N);
                idx = index_[j].data();
                for (std::size_t i = 0; i != N; ++i) {
                    back[static_cast<difference_type>(i)] =
                        idx[static_cast<std::size_t>(
                            last[static_cast<difference_type>(i)])];
                }
            }
        }

        return first + static_cast<difference_type>(N * R);
    }

    private:
    std::size_t iter_size_;
    Vector<index_type> identity_;
    Vector<Vector<index_type>> index_;

    void resize_identity(std::size_t N)
    {
        std::size_t n = identity_.size();
        identity_.resize(N);
        if (n < N)
            for (std::size_t i = n; i != N; ++i)
                identity_[i] = static_cast<index_type>(i);
    }
}; // class ResampleIndex

} // namespace mckl

#endif // MCKL_RESAMPLE_INDEX_HPP
