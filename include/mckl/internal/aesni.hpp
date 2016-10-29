//============================================================================
// MCKL/include/mckl/internal/aesni.hpp
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

#ifndef MCKL_INTERNAL_AESNI_HPP
#define MCKL_INTERNAL_AESNI_HPP

#include <mckl/internal/config.h>
#include <array>

#ifdef MCKL_GCC
#if MCKL_GCC_VERSION >= 60000
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif
#endif

namespace mckl
{

namespace internal
{

MCKL_FLATTEN inline void aesenc_si128(
    std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_aesenc_si128(std::get<0>(s), a);
    std::get<1>(s) = _mm_aesenc_si128(std::get<1>(s), a);
    std::get<2>(s) = _mm_aesenc_si128(std::get<2>(s), a);
    std::get<3>(s) = _mm_aesenc_si128(std::get<3>(s), a);
    std::get<4>(s) = _mm_aesenc_si128(std::get<4>(s), a);
    std::get<5>(s) = _mm_aesenc_si128(std::get<5>(s), a);
    std::get<6>(s) = _mm_aesenc_si128(std::get<6>(s), a);
    std::get<7>(s) = _mm_aesenc_si128(std::get<7>(s), a);
}

MCKL_FLATTEN inline void aesenclast_si128(
    std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_aesenclast_si128(std::get<0>(s), a);
    std::get<1>(s) = _mm_aesenclast_si128(std::get<1>(s), a);
    std::get<2>(s) = _mm_aesenclast_si128(std::get<2>(s), a);
    std::get<3>(s) = _mm_aesenclast_si128(std::get<3>(s), a);
    std::get<4>(s) = _mm_aesenclast_si128(std::get<4>(s), a);
    std::get<5>(s) = _mm_aesenclast_si128(std::get<5>(s), a);
    std::get<6>(s) = _mm_aesenclast_si128(std::get<6>(s), a);
    std::get<7>(s) = _mm_aesenclast_si128(std::get<7>(s), a);
}

MCKL_FLATTEN inline void aesenc_si128(
    std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_aesenc_si128(std::get<0x0>(s), a);
    std::get<0x1>(s) = _mm_aesenc_si128(std::get<0x1>(s), a);
    std::get<0x2>(s) = _mm_aesenc_si128(std::get<0x2>(s), a);
    std::get<0x3>(s) = _mm_aesenc_si128(std::get<0x3>(s), a);
    std::get<0x4>(s) = _mm_aesenc_si128(std::get<0x4>(s), a);
    std::get<0x5>(s) = _mm_aesenc_si128(std::get<0x5>(s), a);
    std::get<0x6>(s) = _mm_aesenc_si128(std::get<0x6>(s), a);
    std::get<0x7>(s) = _mm_aesenc_si128(std::get<0x7>(s), a);
    std::get<0x8>(s) = _mm_aesenc_si128(std::get<0x8>(s), a);
    std::get<0x9>(s) = _mm_aesenc_si128(std::get<0x9>(s), a);
    std::get<0xA>(s) = _mm_aesenc_si128(std::get<0xA>(s), a);
    std::get<0xB>(s) = _mm_aesenc_si128(std::get<0xB>(s), a);
    std::get<0xC>(s) = _mm_aesenc_si128(std::get<0xC>(s), a);
    std::get<0xD>(s) = _mm_aesenc_si128(std::get<0xD>(s), a);
    std::get<0xE>(s) = _mm_aesenc_si128(std::get<0xE>(s), a);
    std::get<0xF>(s) = _mm_aesenc_si128(std::get<0xF>(s), a);
}

MCKL_FLATTEN inline void aesenclast_si128(
    std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_aesenclast_si128(std::get<0x0>(s), a);
    std::get<0x1>(s) = _mm_aesenclast_si128(std::get<0x1>(s), a);
    std::get<0x2>(s) = _mm_aesenclast_si128(std::get<0x2>(s), a);
    std::get<0x3>(s) = _mm_aesenclast_si128(std::get<0x3>(s), a);
    std::get<0x4>(s) = _mm_aesenclast_si128(std::get<0x4>(s), a);
    std::get<0x5>(s) = _mm_aesenclast_si128(std::get<0x5>(s), a);
    std::get<0x6>(s) = _mm_aesenclast_si128(std::get<0x6>(s), a);
    std::get<0x7>(s) = _mm_aesenclast_si128(std::get<0x7>(s), a);
    std::get<0x8>(s) = _mm_aesenclast_si128(std::get<0x8>(s), a);
    std::get<0x9>(s) = _mm_aesenclast_si128(std::get<0x9>(s), a);
    std::get<0xA>(s) = _mm_aesenclast_si128(std::get<0xA>(s), a);
    std::get<0xB>(s) = _mm_aesenclast_si128(std::get<0xB>(s), a);
    std::get<0xC>(s) = _mm_aesenclast_si128(std::get<0xC>(s), a);
    std::get<0xD>(s) = _mm_aesenclast_si128(std::get<0xD>(s), a);
    std::get<0xE>(s) = _mm_aesenclast_si128(std::get<0xE>(s), a);
    std::get<0xF>(s) = _mm_aesenclast_si128(std::get<0xF>(s), a);
}

} // namespace mckl::internal

} // namespace mckl

#ifdef MCKL_GCC
#if MCKL_GCC_VERSION >= 60000
#pragma GCC diagnostic pop
#endif
#endif

#endif // MCKL_INTERNAL_AESNI_HPP
