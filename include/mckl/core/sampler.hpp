//============================================================================
// MCKL/include/mckl/core/sampler.hpp
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

#ifndef MCKL_CORE_SAMPLER_HPP
#define MCKL_CORE_SAMPLER_HPP

#include <mckl/internal/common.hpp>
#include <mckl/core/monitor.hpp>
#include <mckl/core/particle.hpp>

namespace mckl
{

/// \brief Sampler evaluaiton stages
/// \ingroup Core
enum SamplerStage {
    SamplerInit = 1 << 0, ///< Evaluation at initialization before resampling
    SamplerMove = 1 << 1, ///< Evaluation at iteration before resampling
    SamplerMCMC = 1 << 2  ///< Evaluation at after resampling
};                        // enum SamplerStage

inline constexpr SamplerStage operator&(SamplerStage s1, SamplerStage s2)
{
    return static_cast<SamplerStage>(
        static_cast<int>(s1) & static_cast<int>(s2));
}

inline constexpr SamplerStage operator|(SamplerStage s1, SamplerStage s2)
{
    return static_cast<SamplerStage>(
        static_cast<int>(s1) | static_cast<int>(s2));
}

inline constexpr SamplerStage operator^(SamplerStage s1, SamplerStage s2)
{
    return static_cast<SamplerStage>(
        static_cast<int>(s1) ^ static_cast<int>(s2));
}

inline constexpr SamplerStage operator~(SamplerStage s)
{
    return static_cast<SamplerStage>(~static_cast<int>(s));
}

inline SamplerStage &operator&=(SamplerStage &s1, SamplerStage s2)
{
    return s1 = s1 & s2;
}

inline SamplerStage &operator|=(SamplerStage &s1, SamplerStage s2)
{
    return s1 = s1 | s2;
}

inline SamplerStage &operator^=(SamplerStage &s1, SamplerStage s2)
{
    return s1 = s1 ^ s2;
}

/// \brief SMC Sampler
/// \ingroup Core
template <typename T>
class Sampler
{
    public:
    using size_type = typename Particle<T>::size_type;
    using eval_type = std::function<void(std::size_t, Particle<T> &)>;

    /// \brief Construct a Sampler
    ///
    /// \details
    /// All arguments are passed to the constructor of Particle
    template <typename... Args>
    explicit Sampler(Args &&... args)
        : particle_(std::forward<Args>(args)...)
        , iter_num_(0)
        , resample_threshold_(resample_threshold_never())
    {
    }

    /// \brief Clone the Sampler except the RNG engines
    Sampler<T> clone() const
    {
        Sampler<T> sampler(*this);
        sampler.particle().rng_set().reset();
        Seed::instance()(sampler.particle().rng());

        return sampler;
    }

    /// \brief Number of particles
    size_type size() const { return particle_.size(); }

    /// \brief Reserve space for a specified number of iterations
    void reserve(std::size_t num)
    {
        num += iter_num_;
        size_history_.reserve(num);
        ess_history_.reserve(num);
        resampled_history_.reserve(num);
        for (auto &m : monitor_)
            m.second.reserve(num);
    }

    /// \brief Number of iterations (including initialization)
    std::size_t iter_size() const { return size_history_.size(); }

    /// \brief Current iteration number (initialization count as zero)
    std::size_t iter_num() const { return iter_num_; }

    /// \brief Reset a sampler
    void reset()
    {
        clear();
        eval_clear();
    }

    /// \brief Clear all history
    void clear()
    {
        iter_num_ = 0;
        particle_.weight().set_equal();
        for (auto &m : monitor_)
            m.second.clear();

        size_history_.clear();
        ess_history_.clear();
        resampled_history_.clear();
    }

    /// \brief Set resampling method by a built-in ResampleScheme scheme
    /// name
    Sampler<T> &resample_method(
        ResampleScheme scheme, double threshold = resample_threshold_always())
    {
        switch (scheme) {
            case Multinomial:
                resample_eval_ = ResampleEval<T>(ResampleMultinomial());
                break;
            case Residual:
                resample_eval_ = ResampleEval<T>(ResampleResidual());
                break;
            case Stratified:
                resample_eval_ = ResampleEval<T>(ResampleStratified());
                break;
            case Systematic:
                resample_eval_ = ResampleEval<T>(ResampleSystematic());
                break;
            case ResidualStratified:
                resample_eval_ = ResampleEval<T>(ResampleResidualStratified());
                break;
            case ResidualSystematic:
                resample_eval_ = ResampleEval<T>(ResampleResidualSystematic());
                break;
        }
        resample_threshold(threshold);

        return *this;
    }

    /// \brief Set resampling method by a `eval_type` object
    Sampler<T> &resample_method(const eval_type &res_eval,
        double threshold = resample_threshold_always())
    {
        resample_eval_ = res_eval;
        resample_threshold(threshold);

        return *this;
    }

    /// \brief Get resampling threshold
    double resample_threshold() const { return resample_threshold_; }

    /// \brief Set resampling threshold
    Sampler<T> &resample_threshold(double threshold)
    {
        resample_threshold_ = threshold;
        return *this;
    }

    /// \brief Special value of resampling threshold that indicate no
    /// resampling will be ever performed
    static double resample_threshold_never() { return -const_inf<double>(); }

    /// \brief Special value of resampling threshold that indicate no
    /// resampling will always be performed
    static double resample_threshold_always() { return const_inf<double>(); }

    /// \brief Add a new evaluation object
    Sampler<T> &eval(const eval_type &new_eval, SamplerStage stage)
    {
        eval_.push_back(std::make_pair(stage, new_eval));

        return *this;
    }

    /// \brief Clear the evaluation sequence
    void eval_clear() { eval_.clear(); }

    /// \brief Attach a new monitor
    ///
    /// The monitor is attached to
    Sampler<T> &monitor(const std::string &name, const Monitor<T> &mon)
    {
        monitor_clear(name);
        monitor_.push_back(std::make_pair(name, mon));

        return *this;
    }

    /// \brief Read and write access to a Monitor
    Monitor<T> &monitor(const std::string &name)
    {
        auto miter = std::find_if(monitor_.begin(), monitor_.end(),
            [&name](const std::pair<std::string, Monitor<T>> &m) {
                return m.first == name;
            });

        return miter->second;
    }

    /// \brief Read only access to a Monitor
    const Monitor<T> &monitor(const std::string &name) const
    {
        auto miter = std::find_if(monitor_.begin(), monitor_.end(),
            [&name](const std::pair<std::string, Monitor<T>> &m) {
                return m.first == name;
            });

        return miter->second;
    }

    /// \brief Clear a named monitor sequence
    void monitor_clear(const std::string &name)
    {
        auto miter = std::find_if(monitor_.begin(), monitor_.end(),
            [&name](const std::pair<std::string, Monitor<T>> &m) {
                return m.first == name;
            });
        if (miter != monitor_.end())
            monitor_.erase(miter);
    }

    /// \brief Clear the monitor sequence
    void monitor_clear() { monitor_.clear(); }

    /// \brief Initialization
    Sampler<T> &initialize()
    {
        do_initialize();

        return *this;
    }

    /// \brief Iteration
    Sampler<T> &iterate(std::size_t num = 1)
    {
        if (num > 1)
            reserve(num);
        for (std::size_t i = 0; i != num; ++i)
            do_iterate();

        return *this;
    }

    /// \brief Read and write access to the Particle<T> object
    Particle<T> &particle() { return particle_; }

    /// \brief Read only access to the Particle<T> object
    const Particle<T> &particle() const { return particle_; }

    /// \brief Get sampler size of a given iteration (initialization count as
    /// iteration zero)
    size_type size_history(std::size_t iter) const
    {
        return size_history_[iter];
    }

    /// \brief Read sampler size history through an output iterator
    template <typename OutputIter>
    OutputIter read_size_history(OutputIter first) const
    {
        return std::copy(size_history_.begin(), size_history_.end(), first);
    }

    /// \brief Get ESS of a given iteration, (initialization count as iter
    /// zero)
    double ess_history(std::size_t iter) const { return ess_history_[iter]; }

    /// \brief Read ESS history through an output iterator
    template <typename OutputIter>
    OutputIter read_ess_history(OutputIter first) const
    {
        return std::copy(ess_history_.begin(), ess_history_.end(), first);
    }

    /// \brief Get resampling indicator of a given iteration
    bool resampled_history(std::size_t iter) const
    {
        return resampled_history_[iter];
    }

    /// \brief Read resampling indicator history through an output iterator
    template <typename OutputIter>
    OutputIter read_resampled_history(OutputIter first) const
    {
        return std::copy(
            resampled_history_.begin(), resampled_history_.end(), first);
    }

    /// \brief Summary of sampler history
    std::map<std::string, Vector<double>> summary() const
    {
        std::map<std::string, Vector<double>> df;
        Vector<double> data(iter_size());

        std::copy(size_history_.begin(), size_history_.end(), data.begin());
        df["Size"] = data;

        std::copy(resampled_history_.begin(), resampled_history_.end(),
            data.begin());
        df["Resampled"] = data;

        df["ESS"] = ess_history_;

        for (const auto &m : monitor_) {
            if (m.second.iter_size() > 0) {
                for (std::size_t d = 0; d != m.second.dim(); ++d) {
                    std::size_t miter = 0;
                    for (std::size_t i = 0; i != iter_size(); ++i) {
                        if (miter != m.second.iter_size() &&
                            i == m.second.index(miter)) {
                            data[i] = m.second.record(d, miter++);
                        } else {
                            data[i] = const_nan<double>();
                        }
                    }
                    if (m.second.name(d).empty())
                        df[m.first + "." + std::to_string(d)] = data;
                    else
                        df[m.second.name(d)] = data;
                }
            }
        }

        return df;
    }

    /// \brief Print the history of the Sampler
    ///
    /// \param os The ostream to which the contents are printed
    /// \param sepchar The seperator of fields
    template <typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits> &print(
        std::basic_ostream<CharT, Traits> &os, char sepchar = '\t') const
    {
        if (!os || iter_size() == 0)
            return os;

        const std::map<std::string, Vector<double>> df = summary();

        for (const auto &v : df)
            os << v.first << sepchar;
        os << '\n';
        for (std::size_t i = 0; i != iter_size(); ++i) {
            for (const auto &v : df)
                os << v.second[i] << sepchar;
            os << '\n';
        }

        return os;
    }

    private:
    Particle<T> particle_;
    std::size_t iter_num_;

    double resample_threshold_;
    eval_type resample_eval_;
    Vector<std::pair<SamplerStage, eval_type>> eval_;
    Vector<std::pair<std::string, Monitor<T>>> monitor_;

    Vector<size_type> size_history_;
    Vector<double> ess_history_;
    Vector<bool> resampled_history_;

    void do_initialize()
    {
        clear();
        do_init();
        do_common();
    }

    void do_iterate()
    {
        ++iter_num_;
        do_move();
        do_common();
    }

    void do_common()
    {
        do_monitor(MonitorMove);
        do_resample(resample_threshold_);
        do_monitor(MonitorResample);
        do_mcmc();
        do_monitor(MonitorMCMC);
    }

    void do_init()
    {
        for (auto &e : eval_) {
            if ((e.first & SamplerInit) != 0) {
                runtime_assert(static_cast<bool>(e.second),
                    "**Sampler** invalid evaluation object");
                e.second(iter_num_, particle_);
            }
        }
    }

    void do_move()
    {
        for (auto &e : eval_) {
            if ((e.first & SamplerMove) != 0) {
                runtime_assert(static_cast<bool>(e.second),
                    "**Sampler** invalid evaluation object");
                e.second(iter_num_, particle_);
            }
        }
    }

    void do_mcmc()
    {
        for (auto &e : eval_) {
            if ((e.first & SamplerMCMC) != 0) {
                runtime_assert(static_cast<bool>(e.second),
                    "**Sampler** invalid evaluation object");
                e.second(iter_num_, particle_);
            }
        }
    }

    void do_resample(double threshold)
    {
        size_history_.push_back(size());
        ess_history_.push_back(particle_.weight().ess());

        if (ess_history_.back() < size() * threshold) {
            resampled_history_.push_back(true);
            resample_eval_(iter_num_, particle_);
        } else {
            resampled_history_.push_back(false);
        }
    }

    void do_monitor(MonitorStage stage)
    {
        for (auto &m : monitor_)
            if (!m.second.empty())
                m.second(iter_num_, particle_, stage);
    }
}; // class Sampler

template <typename CharT, typename Traits, typename T>
inline std::basic_ostream<CharT, Traits> &operator<<(
    std::basic_ostream<CharT, Traits> &os, const Sampler<T> &sampler)
{
    return sampler.print(os);
}

} // namespace mckl

#endif // MCKL_CORE_SAMPLER_HPP
