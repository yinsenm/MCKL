//============================================================================
// MCKL/include/mckl/mckl.hpp
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

#ifndef MCKL_HPP
#define MCKL_HPP

/// \defgroup Config Configuration
/// \brief Configuration macros and default values if undefined

/// \defgroup Definitions Enumerators, placeholders and macros
/// \brief Enumerator, placeholder and macro definitions

/// \defgroup Traits Traits
/// \brief Trait classes

/// \defgroup Core Core
/// \brief Constructing samplers with operations on the whole particle set

/// \defgroup Algorithm Algorithm
/// \brief Monte Carlo algorithms

/// \defgroup MH Metropolis-Hastings
/// \ingroup Algorithm
/// \brief Metropolis-Hastings algorithm

/// \defgroup SMP Symmetric multiprocessing
/// \brief Parallel samplers using multi-threading on SMP architecture

/// \defgroup SEQ Sequential
/// \ingroup SMP
/// \brief Sequential samplers

/// \defgroup STD Standard library
/// \ingroup SMP
/// \brief Parallel samplers using the standard library

/// \defgroup OMP OpenMP
/// \ingroup SMP
/// \brief Parallel samplers using OpenMP

/// \defgroup TBB Intel Threading Building Blocks
/// \ingroup SMP
/// \brief Parallel samplers using Intel TBB

/// \defgroup Math Mathematics
/// \brief Elementary mathematical functions

/// \defgroup Constants Constants
/// \ingroup Math
/// \brief Constants

/// \defgroup Special Special functions
/// \ingroup Math
/// \brief Special functions

/// \defgroup vMath Vectorized functions
/// \ingroup Math
/// \brief Vectorized functions

/// \defgroup Random Random number generating
/// \brief Random number generating engines and utilities

/// \defgroup AES AES
/// \ingroup Random
/// \brief Random number generating using AES round function

/// \defgroup Philox Philox
/// \ingroup Random
/// \brief Random number generating using Random123 Philox algorithm

/// \defgroup Threefry Threefry
/// \ingroup Random
/// \brief Random number generating using Random123 Threefry algorithm

/// \defgroup MKL Intel Math Kernel Library
/// \ingroup Random
/// \brief Random number generating using MKL

/// \defgroup RDRAND Intel DRNG
/// \ingroup Random
/// \brief Random number generating using Intel RDRAND instructions

/// \defgroup Distribution Distribution
/// \ingroup Random
/// \brief Distribution random variates

/// \defgroup U01 U01
/// \ingroup Random
/// \brief Converting random integers to uniform floating points

/// \defgroup RandomTest Randomness tests
/// \ingroup Random
/// \brief Testing randomness of standard uniform distribution

/// \defgroup RandomC Random number generating in C and OpenCL
/// \brief Random number generating in C and OpenCL

/// \defgroup PhiloxC Philox
/// \ingroup RandomC
/// \brief Random number generating using Random123 Philox RNG

/// \defgroup ThreefryC Threefry
/// \ingroup RandomC
/// \brief Random number generating using Random123 Threefry RNG

/// \defgroup U01C U01
/// \ingroup RandomC
/// \brief Converting random integers to uniform floating points

/// \defgroup Resample Resampling algorithms
/// \brief Resampling algorithm functor classes

/// \defgroup Utility Utility
/// \brief Utilities

/// \defgroup AlignedMemory Aligned memory alignment
/// \ingroup Utility
/// \brief Memory allocation with alignment requirement

/// \defgroup Covariance Covariance
/// \ingroup Utility
/// \brief Covariance matrix estimation

/// \defgroup HDF5 HDF5 objects I/O
/// \ingroup Utility
/// \brief Load and store objects in the HDF5 format

/// \defgroup StopWatch Stop watch
/// \ingroup Utility
/// \brief Time measurement

#include <mckl/internal/config.h>
#include <mckl/algorithm.hpp>
#include <mckl/core.hpp>
#include <mckl/math.hpp>
#include <mckl/random.hpp>
#include <mckl/randomc.h>
#include <mckl/resample.hpp>
#include <mckl/smp.hpp>
#include <mckl/utility.hpp>

#endif // MCKL_HPP
