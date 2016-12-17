//============================================================================
// MCKL/example/algorithm/src/algorithm_pf.cpp
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

#include "algorithm_pf.hpp"

int main()
{
    constexpr std::size_t N = 1000;

    mckl::SMCSampler<AlgorithmPF> sampler(N);
    sampler.selection(AlgorithmPFSelection());
    sampler.resample(mckl::Multinomial);
    sampler.resample_threshold(0.5);
    sampler.selection_estimator(
        mckl::SMCEstimator<AlgorithmPF>(2, AlgorithmPFPos(), mckl::ColMajor),
        "pos.s");
    sampler.resample_estimator(
        mckl::SMCEstimator<AlgorithmPF>(2, AlgorithmPFPos(), mckl::ColMajor),
        "pos.r");
    sampler.mutation_estimator(
        mckl::SMCEstimator<AlgorithmPF>(2, AlgorithmPFPos(), mckl::ColMajor),
        "pos.m");
    sampler.iterate(sampler.particle().state().n());

    std::ofstream save("algorithm_pf.save");
    save << sampler << std::endl;
    save.close();

    return 0;
}
