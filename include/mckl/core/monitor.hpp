//============================================================================
// MCKL/include/mckl/core/monitor.hpp
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

#ifndef MCKL_CORE_MONITOR_HPP
#define MCKL_CORE_MONITOR_HPP

#include <mckl/internal/common.hpp>

namespace mckl
{

/// \brief Monitor stage
/// \ingroup Definitions
enum MonitorStage {
    MonitorMove,     ///< Monitor evaluated after moves
    MonitorResample, ///< Monitor evaluated after resampling
    MonitorMCMC      ///< Monitor evaluated after MCMC moves
};                   // enum MonitorStage

/// \brief Monitor for Monte Carlo integration
/// \ingroup Core
template <typename T>
class Monitor
{
    public:
    using eval_type =
        std::function<void(std::size_t, std::size_t, Particle<T> &, double *)>;

    Monitor(std::size_t dim, const eval_type &eval, bool record_only = false,
        MonitorStage stage = MonitorMCMC)
        : dim_(dim)
        , eval_(eval)
        , record_only_(record_only)
        , stage_(stage)
        , name_(dim)
    {
        internal::size_check<MCKL_BLAS_INT>(dim_, "Monitor::Monitor");
    }

    /// \brief The dimension of the Monitor
    std::size_t dim() const { return dim_; }

    /// \brief If this is a record only Monitor
    bool record_only() const { return record_only_; }

    /// \brief The stage of the Montior
    MonitorStage stage() const { return stage_; }

    /// \brief The number of iterations has been recorded
    std::size_t iter_size() const { return index_.size(); }

    /// \brief Reserve space for a specified number of iterations
    void reserve(std::size_t num)
    {
        index_.reserve(num);
        record_.reserve(dim_ * num);
    }

    /// \brief Whether the evaluation object is valid
    bool empty() const { return !eval_; }

    /// \brief Read and write access to the names of variables
    ///
    /// \details
    /// By default, each variable of a Monitor is unnamed and the returned
    /// string is empty. However, the user can selectively set the names of
    /// each variable. This effect how Sampler will print the headers of the
    /// summary table.
    std::string &name(std::size_t id)
    {
        runtime_assert(id < dim(), "**Monitor::name** index out of range");

        return name_[id];
    }

    /// \brief Read only access to the names of variables
    const std::string &name(std::size_t id) const
    {
        runtime_assert(id < dim(), "**Monitor::name** index out of range");

        return name_[id];
    }

    /// \brief Get the latest iteration index of the sampler
    std::size_t index() const
    {
        runtime_assert(
            iter_size() > 0, "**Monitor::index** no iteration recorded");

        return index_[iter_size() - 1];
    }

    /// \brief Get the iteration index of the sampler of a given Monitor
    /// iteration
    ///
    /// \details
    /// For example, if a Monitor is only added to the sampler at the
    /// sampler's iteration `siter`. Then `index(0)` will be `siter` and so
    /// on. If the Monitor is added before the sampler's initialization and
    /// continued to be evaluated during the iterations without calling
    /// `turnoff()`, then iter(iter) shall just be `iter`.
    std::size_t index(std::size_t iter) const
    {
        runtime_assert(iter < iter_size(),
            "**Monitor::index** iteration number out of range");

        return index_[iter];
    }

    /// \brief Read the index history through an output iterator
    template <typename OutputIter>
    OutputIter read_index(OutputIter first) const
    {
        return std::copy(index_.begin(), index_.end(), first);
    }

    /// \brief Get the latest Monte Carlo integration record of a given
    /// variable
    double record(std::size_t id) const
    {
        runtime_assert(id < dim(), "**Monitor::record** index out of range");
        runtime_assert(
            iter_size() > 0, "**Monitor::record** no iteration reocorded");

        return record_[(iter_size() - 1) * dim_ + id];
    }

    /// \brief Get the Monte Carlo integration record of a given variable and
    /// the Monitor iteration
    double record(std::size_t id, std::size_t iter) const
    {
        runtime_assert(id < dim(), "**Monitor::record** index out of range");
        runtime_assert(iter < iter_size(),
            "**Monitor::record** iteration number out of range");

        return record_[iter * dim_ + id];
    }

    /// \brief Read the record history for a given variable through an output
    /// iterator
    template <typename OutputIter>
    OutputIter read_record(std::size_t id, OutputIter first) const
    {
        runtime_assert(
            id < dim(), "**Monitor::read_record** index out of range");

        const std::size_t N = iter_size();
        const double *riter = record_.data() + id;
        for (std::size_t i = 0; i != N; ++i, ++first, riter += dim_)
            *first = *riter;

        return first;
    }

    /// \brief Read the record history of all variables as a matrix through an
    /// output iterator
    template <typename OutputIter>
    OutputIter read_record_matrix(MatrixLayout layout, OutputIter first) const
    {
        runtime_assert(layout == RowMajor || layout == ColMajor,
            "**Monitor::read_record_matrix** invalid layout parameter");

        if (layout == RowMajor)
            return std::copy(record_.begin(), record_.end(), first);

        if (layout == ColMajor) {
            for (std::size_t d = 0; d != dim_; ++d)
                for (std::size_t i = 0; i != iter_size(); ++i)
                    *first++ = record(d, i);
        }

        return first;
    }

    /// \brief Summary of monitor history
    std::map<std::string, Vector<double>> summary() const
    {
        std::map<std::string, Vector<double>> df;
        Vector<double> data(iter_size());

        std::copy(index_.begin(), index_.end(), data.begin());
        df["Index"] = data;

        for (std::size_t d = 0; d != dim_; ++d) {
            for (std::size_t i = 0; i != iter_size(); ++i)
                data[i] = record(d, i);
            if (name_[d].empty())
                df["X." + std::to_string(d)] = data;
            else
                df[name_[d]] = data;
        }

        return df;
    }

    /// \brief Set a new evaluation object of type eval_type
    void eval(const eval_type &new_eval, bool record_only = false,
        MonitorStage stage = MonitorMCMC)
    {
        eval_ = new_eval;
        record_only_ = record_only;
        stage_ = stage;
    }

    /// \brief Perform the evaluation for a given iteration and a Particle<T>
    /// object.
    void operator()(
        std::size_t iter, Particle<T> &particle, MonitorStage stage)
    {
        internal::size_check<MCKL_BLAS_INT>(particle.size(), "Monitor::eval");

        if (stage != stage_)
            return;

        runtime_assert(static_cast<bool>(eval_),
            "**Monitor::operator()** invalid evaluation object");

        result_.resize(dim_);
        if (record_only_) {
            eval_(iter, dim_, particle, result_.data());
            push_back(iter);

            return;
        }

        const std::size_t N = static_cast<std::size_t>(particle.size());
        r_.resize(N * dim_);
        eval_(iter, dim_, particle, r_.data());
        std::fill(result_.begin(), result_.end(), 0);
#if MCKL_HAS_BLAS
        internal::cblas_dgemv(internal::CblasColMajor, internal::CblasNoTrans,
            static_cast<MCKL_BLAS_INT>(dim_), static_cast<MCKL_BLAS_INT>(N),
            1.0, r_.data(), static_cast<MCKL_BLAS_INT>(dim_),
            particle.weight().data(), 1, 0.0, result_.data(), 1);
#else  // MCKL_HAS_BLAS
        const double *w = particle.weight().data();
        const double *r = r_.data();
        for (std::size_t i = 0; i != N; ++i, ++w)
            for (std::size_t d = 0; d != dim_; ++d, ++r)
                result_[d] += (*w) * (*r);
#endif // MCKL_HAS_BLAS
        push_back(iter);
    }

    /// \brief Clear all records of the index and integrations
    void clear()
    {
        index_.clear();
        record_.clear();
    }

    private:
    std::size_t dim_;
    eval_type eval_;
    bool record_only_;
    MonitorStage stage_;
    Vector<std::string> name_;
    Vector<std::size_t> index_;
    Vector<double> record_;
    Vector<double> result_;
    Vector<double> r_;

    void push_back(std::size_t iter)
    {
        index_.push_back(iter);
        record_.insert(record_.end(), result_.begin(), result_.end());
    }
}; // class Monitor

} // namespace mckl

#endif // MCKL_CORE_MONITOR_HPP
