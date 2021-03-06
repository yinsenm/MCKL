//============================================================================
// MCKL/include/mckl/internal/sse2_op.hpp
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

#ifndef MCKL_INTERNAL_SSE2_OP_HPP
#define MCKL_INTERNAL_SSE2_OP_HPP

#include <mckl/internal/config.h>
#include <array>

MCKL_PUSH_GCC_WARNING("-Wignored-attributes")

namespace mckl {

namespace internal {

template <int imm8>
MCKL_INLINE inline void slli_epi32(std::array<__m128i, 4> &s)
{
    std::get<0>(s) = _mm_slli_epi32(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_slli_epi32(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_slli_epi32(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_slli_epi32(std::get<3>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void srli_epi32(std::array<__m128i, 4> &s)
{
    std::get<0>(s) = _mm_srli_epi32(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_srli_epi32(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_srli_epi32(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_srli_epi32(std::get<3>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void slli_epi64(std::array<__m128i, 4> &s)
{
    std::get<0>(s) = _mm_slli_epi64(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_slli_epi64(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_slli_epi64(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_slli_epi64(std::get<3>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void srli_epi64(std::array<__m128i, 4> &s)
{
    std::get<0>(s) = _mm_srli_epi64(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_srli_epi64(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_srli_epi64(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_srli_epi64(std::get<3>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void shuffle_epi32(std::array<__m128i, 4> &s)
{
    std::get<0>(s) = _mm_shuffle_epi32(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_shuffle_epi32(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_shuffle_epi32(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_shuffle_epi32(std::get<3>(s), imm8);
}

MCKL_INLINE inline void and_si128(const std::array<__m128i, 4> &s,
    const __m128i &a, std::array<__m128i, 4> &t)
{
    std::get<0>(t) = _mm_and_si128(std::get<0>(s), a);
    std::get<1>(t) = _mm_and_si128(std::get<1>(s), a);
    std::get<2>(t) = _mm_and_si128(std::get<2>(s), a);
    std::get<3>(t) = _mm_and_si128(std::get<3>(s), a);
}

MCKL_INLINE inline void and_si128(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_and_si128(std::get<0>(s), a);
    std::get<1>(s) = _mm_and_si128(std::get<1>(s), a);
    std::get<2>(s) = _mm_and_si128(std::get<2>(s), a);
    std::get<3>(s) = _mm_and_si128(std::get<3>(s), a);
}

MCKL_INLINE inline void xor_si128(
    std::array<__m128i, 4> &s, const std::array<__m128i, 4> &a)
{
    std::get<0>(s) = _mm_xor_si128(std::get<0>(s), std::get<0>(a));
    std::get<1>(s) = _mm_xor_si128(std::get<1>(s), std::get<1>(a));
    std::get<2>(s) = _mm_xor_si128(std::get<2>(s), std::get<2>(a));
    std::get<3>(s) = _mm_xor_si128(std::get<3>(s), std::get<3>(a));
}

MCKL_INLINE inline void xor_si128(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_xor_si128(std::get<0>(s), a);
    std::get<1>(s) = _mm_xor_si128(std::get<1>(s), a);
    std::get<2>(s) = _mm_xor_si128(std::get<2>(s), a);
    std::get<3>(s) = _mm_xor_si128(std::get<3>(s), a);
}

MCKL_INLINE inline void add_epi32(
    std::array<__m128i, 4> &s, const std::array<__m128i, 4> &a)
{
    std::get<0>(s) = _mm_add_epi32(std::get<0>(s), std::get<0>(a));
    std::get<1>(s) = _mm_add_epi32(std::get<1>(s), std::get<1>(a));
    std::get<2>(s) = _mm_add_epi32(std::get<2>(s), std::get<2>(a));
    std::get<3>(s) = _mm_add_epi32(std::get<3>(s), std::get<3>(a));
}

MCKL_INLINE inline void add_epi64(
    std::array<__m128i, 4> &s, const std::array<__m128i, 4> &a)
{
    std::get<0>(s) = _mm_add_epi64(std::get<0>(s), std::get<0>(a));
    std::get<1>(s) = _mm_add_epi64(std::get<1>(s), std::get<1>(a));
    std::get<2>(s) = _mm_add_epi64(std::get<2>(s), std::get<2>(a));
    std::get<3>(s) = _mm_add_epi64(std::get<3>(s), std::get<3>(a));
}

MCKL_INLINE inline void add_epi64(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_add_epi64(std::get<0>(s), a);
    std::get<1>(s) = _mm_add_epi64(std::get<1>(s), a);
    std::get<2>(s) = _mm_add_epi64(std::get<2>(s), a);
    std::get<3>(s) = _mm_add_epi64(std::get<3>(s), a);
}

MCKL_INLINE inline void mul_epu32(const std::array<__m128i, 4> &s,
    const __m128i &a, std::array<__m128i, 4> &t)
{
    std::get<0>(t) = _mm_mul_epu32(std::get<0>(s), a);
    std::get<1>(t) = _mm_mul_epu32(std::get<1>(s), a);
    std::get<2>(t) = _mm_mul_epu32(std::get<2>(s), a);
    std::get<3>(t) = _mm_mul_epu32(std::get<3>(s), a);
}

MCKL_INLINE inline void add_ps(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0>(s)), _mm_castsi128_ps(a)));
    std::get<1>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<1>(s)), _mm_castsi128_ps(a)));
    std::get<2>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<2>(s)), _mm_castsi128_ps(a)));
    std::get<3>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<3>(s)), _mm_castsi128_ps(a)));
}

MCKL_INLINE inline void mul_ps(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0>(s)), _mm_castsi128_ps(a)));
    std::get<1>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<1>(s)), _mm_castsi128_ps(a)));
    std::get<2>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<2>(s)), _mm_castsi128_ps(a)));
    std::get<3>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<3>(s)), _mm_castsi128_ps(a)));
}

MCKL_INLINE inline void add_pd(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(a)));
    std::get<1>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(a)));
    std::get<2>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(a)));
    std::get<3>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void add_pd(
    std::array<__m128i, 4> &s, const std::array<__m128i, 4> &a)
{
    std::get<0>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(std::get<0>(a))));
    std::get<1>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(std::get<1>(a))));
    std::get<2>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(std::get<2>(a))));
    std::get<3>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(std::get<3>(a))));
}

MCKL_INLINE inline void sub_pd(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(a)));
    std::get<1>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(a)));
    std::get<2>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(a)));
    std::get<3>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void mul_pd(std::array<__m128i, 4> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(a)));
    std::get<1>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(a)));
    std::get<2>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(a)));
    std::get<3>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void mul_pd(
    std::array<__m128i, 4> &s, const std::array<__m128i, 4> &a)
{
    std::get<0>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(std::get<0>(a))));
    std::get<1>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(std::get<1>(a))));
    std::get<2>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(std::get<2>(a))));
    std::get<3>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(std::get<3>(a))));
}

template <int imm8>
MCKL_INLINE inline void slli_epi32(std::array<__m128i, 8> &s)
{
    std::get<0>(s) = _mm_slli_epi32(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_slli_epi32(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_slli_epi32(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_slli_epi32(std::get<3>(s), imm8);
    std::get<4>(s) = _mm_slli_epi32(std::get<4>(s), imm8);
    std::get<5>(s) = _mm_slli_epi32(std::get<5>(s), imm8);
    std::get<6>(s) = _mm_slli_epi32(std::get<6>(s), imm8);
    std::get<7>(s) = _mm_slli_epi32(std::get<7>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void srli_epi32(std::array<__m128i, 8> &s)
{
    std::get<0>(s) = _mm_srli_epi32(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_srli_epi32(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_srli_epi32(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_srli_epi32(std::get<3>(s), imm8);
    std::get<4>(s) = _mm_srli_epi32(std::get<4>(s), imm8);
    std::get<5>(s) = _mm_srli_epi32(std::get<5>(s), imm8);
    std::get<6>(s) = _mm_srli_epi32(std::get<6>(s), imm8);
    std::get<7>(s) = _mm_srli_epi32(std::get<7>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void slli_epi64(std::array<__m128i, 8> &s)
{
    std::get<0>(s) = _mm_slli_epi64(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_slli_epi64(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_slli_epi64(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_slli_epi64(std::get<3>(s), imm8);
    std::get<4>(s) = _mm_slli_epi64(std::get<4>(s), imm8);
    std::get<5>(s) = _mm_slli_epi64(std::get<5>(s), imm8);
    std::get<6>(s) = _mm_slli_epi64(std::get<6>(s), imm8);
    std::get<7>(s) = _mm_slli_epi64(std::get<7>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void srli_epi64(std::array<__m128i, 8> &s)
{
    std::get<0>(s) = _mm_srli_epi64(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_srli_epi64(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_srli_epi64(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_srli_epi64(std::get<3>(s), imm8);
    std::get<4>(s) = _mm_srli_epi64(std::get<4>(s), imm8);
    std::get<5>(s) = _mm_srli_epi64(std::get<5>(s), imm8);
    std::get<6>(s) = _mm_srli_epi64(std::get<6>(s), imm8);
    std::get<7>(s) = _mm_srli_epi64(std::get<7>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void shuffle_epi32(std::array<__m128i, 8> &s)
{
    std::get<0>(s) = _mm_shuffle_epi32(std::get<0>(s), imm8);
    std::get<1>(s) = _mm_shuffle_epi32(std::get<1>(s), imm8);
    std::get<2>(s) = _mm_shuffle_epi32(std::get<2>(s), imm8);
    std::get<3>(s) = _mm_shuffle_epi32(std::get<3>(s), imm8);
    std::get<4>(s) = _mm_shuffle_epi32(std::get<4>(s), imm8);
    std::get<5>(s) = _mm_shuffle_epi32(std::get<5>(s), imm8);
    std::get<6>(s) = _mm_shuffle_epi32(std::get<6>(s), imm8);
    std::get<7>(s) = _mm_shuffle_epi32(std::get<7>(s), imm8);
}

MCKL_INLINE inline void and_si128(const std::array<__m128i, 8> &s,
    const __m128i &a, std::array<__m128i, 8> &t)
{
    std::get<0>(t) = _mm_and_si128(std::get<0>(s), a);
    std::get<1>(t) = _mm_and_si128(std::get<1>(s), a);
    std::get<2>(t) = _mm_and_si128(std::get<2>(s), a);
    std::get<3>(t) = _mm_and_si128(std::get<3>(s), a);
    std::get<4>(t) = _mm_and_si128(std::get<4>(s), a);
    std::get<5>(t) = _mm_and_si128(std::get<5>(s), a);
    std::get<6>(t) = _mm_and_si128(std::get<6>(s), a);
    std::get<7>(t) = _mm_and_si128(std::get<7>(s), a);
}

MCKL_INLINE inline void and_si128(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_and_si128(std::get<0>(s), a);
    std::get<1>(s) = _mm_and_si128(std::get<1>(s), a);
    std::get<2>(s) = _mm_and_si128(std::get<2>(s), a);
    std::get<3>(s) = _mm_and_si128(std::get<3>(s), a);
    std::get<4>(s) = _mm_and_si128(std::get<4>(s), a);
    std::get<5>(s) = _mm_and_si128(std::get<5>(s), a);
    std::get<6>(s) = _mm_and_si128(std::get<6>(s), a);
    std::get<7>(s) = _mm_and_si128(std::get<7>(s), a);
}

MCKL_INLINE inline void xor_si128(
    std::array<__m128i, 8> &s, const std::array<__m128i, 8> &a)
{
    std::get<0>(s) = _mm_xor_si128(std::get<0>(s), std::get<0>(a));
    std::get<1>(s) = _mm_xor_si128(std::get<1>(s), std::get<1>(a));
    std::get<2>(s) = _mm_xor_si128(std::get<2>(s), std::get<2>(a));
    std::get<3>(s) = _mm_xor_si128(std::get<3>(s), std::get<3>(a));
    std::get<4>(s) = _mm_xor_si128(std::get<4>(s), std::get<4>(a));
    std::get<5>(s) = _mm_xor_si128(std::get<5>(s), std::get<5>(a));
    std::get<6>(s) = _mm_xor_si128(std::get<6>(s), std::get<6>(a));
    std::get<7>(s) = _mm_xor_si128(std::get<7>(s), std::get<7>(a));
}

MCKL_INLINE inline void xor_si128(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_xor_si128(std::get<0>(s), a);
    std::get<1>(s) = _mm_xor_si128(std::get<1>(s), a);
    std::get<2>(s) = _mm_xor_si128(std::get<2>(s), a);
    std::get<3>(s) = _mm_xor_si128(std::get<3>(s), a);
    std::get<4>(s) = _mm_xor_si128(std::get<4>(s), a);
    std::get<5>(s) = _mm_xor_si128(std::get<5>(s), a);
    std::get<6>(s) = _mm_xor_si128(std::get<6>(s), a);
    std::get<7>(s) = _mm_xor_si128(std::get<7>(s), a);
}

MCKL_INLINE inline void add_epi32(
    std::array<__m128i, 8> &s, const std::array<__m128i, 8> &a)
{
    std::get<0>(s) = _mm_add_epi32(std::get<0>(s), std::get<0>(a));
    std::get<1>(s) = _mm_add_epi32(std::get<1>(s), std::get<1>(a));
    std::get<2>(s) = _mm_add_epi32(std::get<2>(s), std::get<2>(a));
    std::get<3>(s) = _mm_add_epi32(std::get<3>(s), std::get<3>(a));
    std::get<4>(s) = _mm_add_epi32(std::get<4>(s), std::get<4>(a));
    std::get<5>(s) = _mm_add_epi32(std::get<5>(s), std::get<5>(a));
    std::get<6>(s) = _mm_add_epi32(std::get<6>(s), std::get<6>(a));
    std::get<7>(s) = _mm_add_epi32(std::get<7>(s), std::get<7>(a));
}

MCKL_INLINE inline void add_epi64(
    std::array<__m128i, 8> &s, const std::array<__m128i, 8> &a)
{
    std::get<0>(s) = _mm_add_epi64(std::get<0>(s), std::get<0>(a));
    std::get<1>(s) = _mm_add_epi64(std::get<1>(s), std::get<1>(a));
    std::get<2>(s) = _mm_add_epi64(std::get<2>(s), std::get<2>(a));
    std::get<3>(s) = _mm_add_epi64(std::get<3>(s), std::get<3>(a));
    std::get<4>(s) = _mm_add_epi64(std::get<4>(s), std::get<4>(a));
    std::get<5>(s) = _mm_add_epi64(std::get<5>(s), std::get<5>(a));
    std::get<6>(s) = _mm_add_epi64(std::get<6>(s), std::get<6>(a));
    std::get<7>(s) = _mm_add_epi64(std::get<7>(s), std::get<7>(a));
}

MCKL_INLINE inline void add_epi64(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_add_epi64(std::get<0>(s), a);
    std::get<1>(s) = _mm_add_epi64(std::get<1>(s), a);
    std::get<2>(s) = _mm_add_epi64(std::get<2>(s), a);
    std::get<3>(s) = _mm_add_epi64(std::get<3>(s), a);
    std::get<4>(s) = _mm_add_epi64(std::get<4>(s), a);
    std::get<5>(s) = _mm_add_epi64(std::get<5>(s), a);
    std::get<6>(s) = _mm_add_epi64(std::get<6>(s), a);
    std::get<7>(s) = _mm_add_epi64(std::get<7>(s), a);
}

MCKL_INLINE inline void mul_epu32(const std::array<__m128i, 8> &s,
    const __m128i &a, std::array<__m128i, 8> &t)
{
    std::get<0>(t) = _mm_mul_epu32(std::get<0>(s), a);
    std::get<1>(t) = _mm_mul_epu32(std::get<1>(s), a);
    std::get<2>(t) = _mm_mul_epu32(std::get<2>(s), a);
    std::get<3>(t) = _mm_mul_epu32(std::get<3>(s), a);
    std::get<4>(t) = _mm_mul_epu32(std::get<4>(s), a);
    std::get<5>(t) = _mm_mul_epu32(std::get<5>(s), a);
    std::get<6>(t) = _mm_mul_epu32(std::get<6>(s), a);
    std::get<7>(t) = _mm_mul_epu32(std::get<7>(s), a);
}

MCKL_INLINE inline void add_ps(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0>(s)), _mm_castsi128_ps(a)));
    std::get<1>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<1>(s)), _mm_castsi128_ps(a)));
    std::get<2>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<2>(s)), _mm_castsi128_ps(a)));
    std::get<3>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<3>(s)), _mm_castsi128_ps(a)));
    std::get<4>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<4>(s)), _mm_castsi128_ps(a)));
    std::get<5>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<5>(s)), _mm_castsi128_ps(a)));
    std::get<6>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<6>(s)), _mm_castsi128_ps(a)));
    std::get<7>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<7>(s)), _mm_castsi128_ps(a)));
}

MCKL_INLINE inline void mul_ps(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0>(s)), _mm_castsi128_ps(a)));
    std::get<1>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<1>(s)), _mm_castsi128_ps(a)));
    std::get<2>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<2>(s)), _mm_castsi128_ps(a)));
    std::get<3>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<3>(s)), _mm_castsi128_ps(a)));
    std::get<4>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<4>(s)), _mm_castsi128_ps(a)));
    std::get<5>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<5>(s)), _mm_castsi128_ps(a)));
    std::get<6>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<6>(s)), _mm_castsi128_ps(a)));
    std::get<7>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<7>(s)), _mm_castsi128_ps(a)));
}

MCKL_INLINE inline void add_pd(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(a)));
    std::get<1>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(a)));
    std::get<2>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(a)));
    std::get<3>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(a)));
    std::get<4>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<4>(s)), _mm_castsi128_pd(a)));
    std::get<5>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<5>(s)), _mm_castsi128_pd(a)));
    std::get<6>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<6>(s)), _mm_castsi128_pd(a)));
    std::get<7>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<7>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void add_pd(
    std::array<__m128i, 8> &s, const std::array<__m128i, 8> &a)
{
    std::get<0>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(std::get<0>(a))));
    std::get<1>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(std::get<1>(a))));
    std::get<2>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(std::get<2>(a))));
    std::get<3>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(std::get<3>(a))));
    std::get<4>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<4>(s)), _mm_castsi128_pd(std::get<4>(a))));
    std::get<5>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<5>(s)), _mm_castsi128_pd(std::get<5>(a))));
    std::get<6>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<6>(s)), _mm_castsi128_pd(std::get<6>(a))));
    std::get<7>(s) = _mm_castpd_si128(_mm_add_pd(
        _mm_castsi128_pd(std::get<7>(s)), _mm_castsi128_pd(std::get<7>(a))));
}

MCKL_INLINE inline void sub_pd(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(a)));
    std::get<1>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(a)));
    std::get<2>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(a)));
    std::get<3>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(a)));
    std::get<4>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<4>(s)), _mm_castsi128_pd(a)));
    std::get<5>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<5>(s)), _mm_castsi128_pd(a)));
    std::get<6>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<6>(s)), _mm_castsi128_pd(a)));
    std::get<7>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<7>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void mul_pd(std::array<__m128i, 8> &s, const __m128i &a)
{
    std::get<0>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(a)));
    std::get<1>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(a)));
    std::get<2>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(a)));
    std::get<3>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(a)));
    std::get<4>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<4>(s)), _mm_castsi128_pd(a)));
    std::get<5>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<5>(s)), _mm_castsi128_pd(a)));
    std::get<6>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<6>(s)), _mm_castsi128_pd(a)));
    std::get<7>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<7>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void mul_pd(
    std::array<__m128i, 8> &s, const std::array<__m128i, 8> &a)
{
    std::get<0>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<0>(s)), _mm_castsi128_pd(std::get<0>(a))));
    std::get<1>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<1>(s)), _mm_castsi128_pd(std::get<1>(a))));
    std::get<2>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<2>(s)), _mm_castsi128_pd(std::get<2>(a))));
    std::get<3>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<3>(s)), _mm_castsi128_pd(std::get<3>(a))));
    std::get<4>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<4>(s)), _mm_castsi128_pd(std::get<4>(a))));
    std::get<5>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<5>(s)), _mm_castsi128_pd(std::get<5>(a))));
    std::get<6>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<6>(s)), _mm_castsi128_pd(std::get<6>(a))));
    std::get<7>(s) = _mm_castpd_si128(_mm_mul_pd(
        _mm_castsi128_pd(std::get<7>(s)), _mm_castsi128_pd(std::get<7>(a))));
}

template <int imm8>
MCKL_INLINE inline void slli_epi32(std::array<__m128i, 16> &s)
{
    std::get<0x0>(s) = _mm_slli_epi32(std::get<0x0>(s), imm8);
    std::get<0x1>(s) = _mm_slli_epi32(std::get<0x1>(s), imm8);
    std::get<0x2>(s) = _mm_slli_epi32(std::get<0x2>(s), imm8);
    std::get<0x3>(s) = _mm_slli_epi32(std::get<0x3>(s), imm8);
    std::get<0x4>(s) = _mm_slli_epi32(std::get<0x4>(s), imm8);
    std::get<0x5>(s) = _mm_slli_epi32(std::get<0x5>(s), imm8);
    std::get<0x6>(s) = _mm_slli_epi32(std::get<0x6>(s), imm8);
    std::get<0x7>(s) = _mm_slli_epi32(std::get<0x7>(s), imm8);
    std::get<0x8>(s) = _mm_slli_epi32(std::get<0x8>(s), imm8);
    std::get<0x9>(s) = _mm_slli_epi32(std::get<0x9>(s), imm8);
    std::get<0xA>(s) = _mm_slli_epi32(std::get<0xA>(s), imm8);
    std::get<0xB>(s) = _mm_slli_epi32(std::get<0xB>(s), imm8);
    std::get<0xC>(s) = _mm_slli_epi32(std::get<0xC>(s), imm8);
    std::get<0xD>(s) = _mm_slli_epi32(std::get<0xD>(s), imm8);
    std::get<0xE>(s) = _mm_slli_epi32(std::get<0xE>(s), imm8);
    std::get<0xF>(s) = _mm_slli_epi32(std::get<0xF>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void srli_epi32(std::array<__m128i, 16> &s)
{
    std::get<0x0>(s) = _mm_srli_epi32(std::get<0x0>(s), imm8);
    std::get<0x1>(s) = _mm_srli_epi32(std::get<0x1>(s), imm8);
    std::get<0x2>(s) = _mm_srli_epi32(std::get<0x2>(s), imm8);
    std::get<0x3>(s) = _mm_srli_epi32(std::get<0x3>(s), imm8);
    std::get<0x4>(s) = _mm_srli_epi32(std::get<0x4>(s), imm8);
    std::get<0x5>(s) = _mm_srli_epi32(std::get<0x5>(s), imm8);
    std::get<0x6>(s) = _mm_srli_epi32(std::get<0x6>(s), imm8);
    std::get<0x7>(s) = _mm_srli_epi32(std::get<0x7>(s), imm8);
    std::get<0x8>(s) = _mm_srli_epi32(std::get<0x8>(s), imm8);
    std::get<0x9>(s) = _mm_srli_epi32(std::get<0x9>(s), imm8);
    std::get<0xA>(s) = _mm_srli_epi32(std::get<0xA>(s), imm8);
    std::get<0xB>(s) = _mm_srli_epi32(std::get<0xB>(s), imm8);
    std::get<0xC>(s) = _mm_srli_epi32(std::get<0xC>(s), imm8);
    std::get<0xD>(s) = _mm_srli_epi32(std::get<0xD>(s), imm8);
    std::get<0xE>(s) = _mm_srli_epi32(std::get<0xE>(s), imm8);
    std::get<0xF>(s) = _mm_srli_epi32(std::get<0xF>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void slli_epi64(std::array<__m128i, 16> &s)
{
    std::get<0x0>(s) = _mm_slli_epi64(std::get<0x0>(s), imm8);
    std::get<0x1>(s) = _mm_slli_epi64(std::get<0x1>(s), imm8);
    std::get<0x2>(s) = _mm_slli_epi64(std::get<0x2>(s), imm8);
    std::get<0x3>(s) = _mm_slli_epi64(std::get<0x3>(s), imm8);
    std::get<0x4>(s) = _mm_slli_epi64(std::get<0x4>(s), imm8);
    std::get<0x5>(s) = _mm_slli_epi64(std::get<0x5>(s), imm8);
    std::get<0x6>(s) = _mm_slli_epi64(std::get<0x6>(s), imm8);
    std::get<0x7>(s) = _mm_slli_epi64(std::get<0x7>(s), imm8);
    std::get<0x8>(s) = _mm_slli_epi64(std::get<0x8>(s), imm8);
    std::get<0x9>(s) = _mm_slli_epi64(std::get<0x9>(s), imm8);
    std::get<0xA>(s) = _mm_slli_epi64(std::get<0xA>(s), imm8);
    std::get<0xB>(s) = _mm_slli_epi64(std::get<0xB>(s), imm8);
    std::get<0xC>(s) = _mm_slli_epi64(std::get<0xC>(s), imm8);
    std::get<0xD>(s) = _mm_slli_epi64(std::get<0xD>(s), imm8);
    std::get<0xE>(s) = _mm_slli_epi64(std::get<0xE>(s), imm8);
    std::get<0xF>(s) = _mm_slli_epi64(std::get<0xF>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void srli_epi64(std::array<__m128i, 16> &s)
{
    std::get<0x0>(s) = _mm_srli_epi64(std::get<0x0>(s), imm8);
    std::get<0x1>(s) = _mm_srli_epi64(std::get<0x1>(s), imm8);
    std::get<0x2>(s) = _mm_srli_epi64(std::get<0x2>(s), imm8);
    std::get<0x3>(s) = _mm_srli_epi64(std::get<0x3>(s), imm8);
    std::get<0x4>(s) = _mm_srli_epi64(std::get<0x4>(s), imm8);
    std::get<0x5>(s) = _mm_srli_epi64(std::get<0x5>(s), imm8);
    std::get<0x6>(s) = _mm_srli_epi64(std::get<0x6>(s), imm8);
    std::get<0x7>(s) = _mm_srli_epi64(std::get<0x7>(s), imm8);
    std::get<0x8>(s) = _mm_srli_epi64(std::get<0x8>(s), imm8);
    std::get<0x9>(s) = _mm_srli_epi64(std::get<0x9>(s), imm8);
    std::get<0xA>(s) = _mm_srli_epi64(std::get<0xA>(s), imm8);
    std::get<0xB>(s) = _mm_srli_epi64(std::get<0xB>(s), imm8);
    std::get<0xC>(s) = _mm_srli_epi64(std::get<0xC>(s), imm8);
    std::get<0xD>(s) = _mm_srli_epi64(std::get<0xD>(s), imm8);
    std::get<0xE>(s) = _mm_srli_epi64(std::get<0xE>(s), imm8);
    std::get<0xF>(s) = _mm_srli_epi64(std::get<0xF>(s), imm8);
}

template <int imm8>
MCKL_INLINE inline void shuffle_epi32(std::array<__m128i, 16> &s)
{
    std::get<0x0>(s) = _mm_shuffle_epi32(std::get<0x0>(s), imm8);
    std::get<0x1>(s) = _mm_shuffle_epi32(std::get<0x1>(s), imm8);
    std::get<0x2>(s) = _mm_shuffle_epi32(std::get<0x2>(s), imm8);
    std::get<0x3>(s) = _mm_shuffle_epi32(std::get<0x3>(s), imm8);
    std::get<0x4>(s) = _mm_shuffle_epi32(std::get<0x4>(s), imm8);
    std::get<0x5>(s) = _mm_shuffle_epi32(std::get<0x5>(s), imm8);
    std::get<0x6>(s) = _mm_shuffle_epi32(std::get<0x6>(s), imm8);
    std::get<0x7>(s) = _mm_shuffle_epi32(std::get<0x7>(s), imm8);
    std::get<0x8>(s) = _mm_shuffle_epi32(std::get<0x8>(s), imm8);
    std::get<0x9>(s) = _mm_shuffle_epi32(std::get<0x9>(s), imm8);
    std::get<0xA>(s) = _mm_shuffle_epi32(std::get<0xA>(s), imm8);
    std::get<0xB>(s) = _mm_shuffle_epi32(std::get<0xB>(s), imm8);
    std::get<0xC>(s) = _mm_shuffle_epi32(std::get<0xC>(s), imm8);
    std::get<0xD>(s) = _mm_shuffle_epi32(std::get<0xD>(s), imm8);
    std::get<0xE>(s) = _mm_shuffle_epi32(std::get<0xE>(s), imm8);
    std::get<0xF>(s) = _mm_shuffle_epi32(std::get<0xF>(s), imm8);
}

MCKL_INLINE inline void and_si128(const std::array<__m128i, 16> &s,
    const __m128i &a, std::array<__m128i, 16> &t)
{
    std::get<0x0>(t) = _mm_and_si128(std::get<0x0>(s), a);
    std::get<0x1>(t) = _mm_and_si128(std::get<0x1>(s), a);
    std::get<0x2>(t) = _mm_and_si128(std::get<0x2>(s), a);
    std::get<0x3>(t) = _mm_and_si128(std::get<0x3>(s), a);
    std::get<0x4>(t) = _mm_and_si128(std::get<0x4>(s), a);
    std::get<0x5>(t) = _mm_and_si128(std::get<0x5>(s), a);
    std::get<0x6>(t) = _mm_and_si128(std::get<0x6>(s), a);
    std::get<0x7>(t) = _mm_and_si128(std::get<0x7>(s), a);
    std::get<0x8>(t) = _mm_and_si128(std::get<0x8>(s), a);
    std::get<0x9>(t) = _mm_and_si128(std::get<0x9>(s), a);
    std::get<0xA>(t) = _mm_and_si128(std::get<0xA>(s), a);
    std::get<0xB>(t) = _mm_and_si128(std::get<0xB>(s), a);
    std::get<0xC>(t) = _mm_and_si128(std::get<0xC>(s), a);
    std::get<0xD>(t) = _mm_and_si128(std::get<0xD>(s), a);
    std::get<0xE>(t) = _mm_and_si128(std::get<0xE>(s), a);
    std::get<0xF>(t) = _mm_and_si128(std::get<0xF>(s), a);
}

MCKL_INLINE inline void and_si128(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_and_si128(std::get<0x0>(s), a);
    std::get<0x1>(s) = _mm_and_si128(std::get<0x1>(s), a);
    std::get<0x2>(s) = _mm_and_si128(std::get<0x2>(s), a);
    std::get<0x3>(s) = _mm_and_si128(std::get<0x3>(s), a);
    std::get<0x4>(s) = _mm_and_si128(std::get<0x4>(s), a);
    std::get<0x5>(s) = _mm_and_si128(std::get<0x5>(s), a);
    std::get<0x6>(s) = _mm_and_si128(std::get<0x6>(s), a);
    std::get<0x7>(s) = _mm_and_si128(std::get<0x7>(s), a);
    std::get<0x8>(s) = _mm_and_si128(std::get<0x8>(s), a);
    std::get<0x9>(s) = _mm_and_si128(std::get<0x9>(s), a);
    std::get<0xA>(s) = _mm_and_si128(std::get<0xA>(s), a);
    std::get<0xB>(s) = _mm_and_si128(std::get<0xB>(s), a);
    std::get<0xC>(s) = _mm_and_si128(std::get<0xC>(s), a);
    std::get<0xD>(s) = _mm_and_si128(std::get<0xD>(s), a);
    std::get<0xE>(s) = _mm_and_si128(std::get<0xE>(s), a);
    std::get<0xF>(s) = _mm_and_si128(std::get<0xF>(s), a);
}

MCKL_INLINE inline void xor_si128(
    std::array<__m128i, 16> &s, const std::array<__m128i, 16> &a)
{
    std::get<0x0>(s) = _mm_xor_si128(std::get<0x0>(s), std::get<0x0>(a));
    std::get<0x1>(s) = _mm_xor_si128(std::get<0x1>(s), std::get<0x1>(a));
    std::get<0x2>(s) = _mm_xor_si128(std::get<0x2>(s), std::get<0x2>(a));
    std::get<0x3>(s) = _mm_xor_si128(std::get<0x3>(s), std::get<0x3>(a));
    std::get<0x4>(s) = _mm_xor_si128(std::get<0x4>(s), std::get<0x4>(a));
    std::get<0x5>(s) = _mm_xor_si128(std::get<0x5>(s), std::get<0x5>(a));
    std::get<0x6>(s) = _mm_xor_si128(std::get<0x6>(s), std::get<0x6>(a));
    std::get<0x7>(s) = _mm_xor_si128(std::get<0x7>(s), std::get<0x7>(a));
    std::get<0x8>(s) = _mm_xor_si128(std::get<0x8>(s), std::get<0x8>(a));
    std::get<0x9>(s) = _mm_xor_si128(std::get<0x9>(s), std::get<0x9>(a));
    std::get<0xA>(s) = _mm_xor_si128(std::get<0xA>(s), std::get<0xA>(a));
    std::get<0xB>(s) = _mm_xor_si128(std::get<0xB>(s), std::get<0xB>(a));
    std::get<0xC>(s) = _mm_xor_si128(std::get<0xC>(s), std::get<0xC>(a));
    std::get<0xD>(s) = _mm_xor_si128(std::get<0xD>(s), std::get<0xD>(a));
    std::get<0xE>(s) = _mm_xor_si128(std::get<0xE>(s), std::get<0xE>(a));
    std::get<0xF>(s) = _mm_xor_si128(std::get<0xF>(s), std::get<0xF>(a));
}

MCKL_INLINE inline void xor_si128(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_xor_si128(std::get<0x0>(s), a);
    std::get<0x1>(s) = _mm_xor_si128(std::get<0x1>(s), a);
    std::get<0x2>(s) = _mm_xor_si128(std::get<0x2>(s), a);
    std::get<0x3>(s) = _mm_xor_si128(std::get<0x3>(s), a);
    std::get<0x4>(s) = _mm_xor_si128(std::get<0x4>(s), a);
    std::get<0x5>(s) = _mm_xor_si128(std::get<0x5>(s), a);
    std::get<0x6>(s) = _mm_xor_si128(std::get<0x6>(s), a);
    std::get<0x7>(s) = _mm_xor_si128(std::get<0x7>(s), a);
    std::get<0x8>(s) = _mm_xor_si128(std::get<0x8>(s), a);
    std::get<0x9>(s) = _mm_xor_si128(std::get<0x9>(s), a);
    std::get<0xA>(s) = _mm_xor_si128(std::get<0xA>(s), a);
    std::get<0xB>(s) = _mm_xor_si128(std::get<0xB>(s), a);
    std::get<0xC>(s) = _mm_xor_si128(std::get<0xC>(s), a);
    std::get<0xD>(s) = _mm_xor_si128(std::get<0xD>(s), a);
    std::get<0xE>(s) = _mm_xor_si128(std::get<0xE>(s), a);
    std::get<0xF>(s) = _mm_xor_si128(std::get<0xF>(s), a);
}

MCKL_INLINE inline void add_epi32(
    std::array<__m128i, 16> &s, const std::array<__m128i, 16> &a)
{
    std::get<0x0>(s) = _mm_add_epi32(std::get<0x0>(s), std::get<0x0>(a));
    std::get<0x1>(s) = _mm_add_epi32(std::get<0x1>(s), std::get<0x1>(a));
    std::get<0x2>(s) = _mm_add_epi32(std::get<0x2>(s), std::get<0x2>(a));
    std::get<0x3>(s) = _mm_add_epi32(std::get<0x3>(s), std::get<0x3>(a));
    std::get<0x4>(s) = _mm_add_epi32(std::get<0x4>(s), std::get<0x4>(a));
    std::get<0x5>(s) = _mm_add_epi32(std::get<0x5>(s), std::get<0x5>(a));
    std::get<0x6>(s) = _mm_add_epi32(std::get<0x6>(s), std::get<0x6>(a));
    std::get<0x7>(s) = _mm_add_epi32(std::get<0x7>(s), std::get<0x7>(a));
    std::get<0x8>(s) = _mm_add_epi32(std::get<0x8>(s), std::get<0x8>(a));
    std::get<0x9>(s) = _mm_add_epi32(std::get<0x9>(s), std::get<0x9>(a));
    std::get<0xA>(s) = _mm_add_epi32(std::get<0xA>(s), std::get<0xA>(a));
    std::get<0xB>(s) = _mm_add_epi32(std::get<0xB>(s), std::get<0xB>(a));
    std::get<0xC>(s) = _mm_add_epi32(std::get<0xC>(s), std::get<0xC>(a));
    std::get<0xD>(s) = _mm_add_epi32(std::get<0xD>(s), std::get<0xD>(a));
    std::get<0xE>(s) = _mm_add_epi32(std::get<0xE>(s), std::get<0xE>(a));
    std::get<0xF>(s) = _mm_add_epi32(std::get<0xF>(s), std::get<0xF>(a));
}

MCKL_INLINE inline void add_epi64(
    std::array<__m128i, 16> &s, const std::array<__m128i, 16> &a)
{
    std::get<0x0>(s) = _mm_add_epi64(std::get<0x0>(s), std::get<0x0>(a));
    std::get<0x1>(s) = _mm_add_epi64(std::get<0x1>(s), std::get<0x1>(a));
    std::get<0x2>(s) = _mm_add_epi64(std::get<0x2>(s), std::get<0x2>(a));
    std::get<0x3>(s) = _mm_add_epi64(std::get<0x3>(s), std::get<0x3>(a));
    std::get<0x4>(s) = _mm_add_epi64(std::get<0x4>(s), std::get<0x4>(a));
    std::get<0x5>(s) = _mm_add_epi64(std::get<0x5>(s), std::get<0x5>(a));
    std::get<0x6>(s) = _mm_add_epi64(std::get<0x6>(s), std::get<0x6>(a));
    std::get<0x7>(s) = _mm_add_epi64(std::get<0x7>(s), std::get<0x7>(a));
    std::get<0x8>(s) = _mm_add_epi64(std::get<0x8>(s), std::get<0x8>(a));
    std::get<0x9>(s) = _mm_add_epi64(std::get<0x9>(s), std::get<0x9>(a));
    std::get<0xA>(s) = _mm_add_epi64(std::get<0xA>(s), std::get<0xA>(a));
    std::get<0xB>(s) = _mm_add_epi64(std::get<0xB>(s), std::get<0xB>(a));
    std::get<0xC>(s) = _mm_add_epi64(std::get<0xC>(s), std::get<0xC>(a));
    std::get<0xD>(s) = _mm_add_epi64(std::get<0xD>(s), std::get<0xD>(a));
    std::get<0xE>(s) = _mm_add_epi64(std::get<0xE>(s), std::get<0xE>(a));
    std::get<0xF>(s) = _mm_add_epi64(std::get<0xF>(s), std::get<0xF>(a));
}

MCKL_INLINE inline void add_epi64(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_add_epi64(std::get<0x0>(s), a);
    std::get<0x1>(s) = _mm_add_epi64(std::get<0x1>(s), a);
    std::get<0x2>(s) = _mm_add_epi64(std::get<0x2>(s), a);
    std::get<0x3>(s) = _mm_add_epi64(std::get<0x3>(s), a);
    std::get<0x4>(s) = _mm_add_epi64(std::get<0x4>(s), a);
    std::get<0x5>(s) = _mm_add_epi64(std::get<0x5>(s), a);
    std::get<0x6>(s) = _mm_add_epi64(std::get<0x6>(s), a);
    std::get<0x7>(s) = _mm_add_epi64(std::get<0x7>(s), a);
    std::get<0x8>(s) = _mm_add_epi64(std::get<0x8>(s), a);
    std::get<0x9>(s) = _mm_add_epi64(std::get<0x9>(s), a);
    std::get<0xA>(s) = _mm_add_epi64(std::get<0xA>(s), a);
    std::get<0xB>(s) = _mm_add_epi64(std::get<0xB>(s), a);
    std::get<0xC>(s) = _mm_add_epi64(std::get<0xC>(s), a);
    std::get<0xD>(s) = _mm_add_epi64(std::get<0xD>(s), a);
    std::get<0xE>(s) = _mm_add_epi64(std::get<0xE>(s), a);
    std::get<0xF>(s) = _mm_add_epi64(std::get<0xF>(s), a);
}

MCKL_INLINE inline void mul_epu32(const std::array<__m128i, 16> &s,
    const __m128i &a, std::array<__m128i, 16> &t)
{
    std::get<0x0>(t) = _mm_mul_epu32(std::get<0x0>(s), a);
    std::get<0x1>(t) = _mm_mul_epu32(std::get<0x1>(s), a);
    std::get<0x2>(t) = _mm_mul_epu32(std::get<0x2>(s), a);
    std::get<0x3>(t) = _mm_mul_epu32(std::get<0x3>(s), a);
    std::get<0x4>(t) = _mm_mul_epu32(std::get<0x4>(s), a);
    std::get<0x5>(t) = _mm_mul_epu32(std::get<0x5>(s), a);
    std::get<0x6>(t) = _mm_mul_epu32(std::get<0x6>(s), a);
    std::get<0x7>(t) = _mm_mul_epu32(std::get<0x7>(s), a);
    std::get<0x8>(t) = _mm_mul_epu32(std::get<0x8>(s), a);
    std::get<0x9>(t) = _mm_mul_epu32(std::get<0x9>(s), a);
    std::get<0xA>(t) = _mm_mul_epu32(std::get<0xA>(s), a);
    std::get<0xB>(t) = _mm_mul_epu32(std::get<0xB>(s), a);
    std::get<0xC>(t) = _mm_mul_epu32(std::get<0xC>(s), a);
    std::get<0xD>(t) = _mm_mul_epu32(std::get<0xD>(s), a);
    std::get<0xE>(t) = _mm_mul_epu32(std::get<0xE>(s), a);
    std::get<0xF>(t) = _mm_mul_epu32(std::get<0xF>(s), a);
}

MCKL_INLINE inline void add_ps(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x0>(s)), _mm_castsi128_ps(a)));
    std::get<0x1>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x1>(s)), _mm_castsi128_ps(a)));
    std::get<0x2>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x2>(s)), _mm_castsi128_ps(a)));
    std::get<0x3>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x3>(s)), _mm_castsi128_ps(a)));
    std::get<0x4>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x4>(s)), _mm_castsi128_ps(a)));
    std::get<0x5>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x5>(s)), _mm_castsi128_ps(a)));
    std::get<0x6>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x6>(s)), _mm_castsi128_ps(a)));
    std::get<0x7>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x7>(s)), _mm_castsi128_ps(a)));
    std::get<0x8>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x8>(s)), _mm_castsi128_ps(a)));
    std::get<0x9>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0x9>(s)), _mm_castsi128_ps(a)));
    std::get<0xA>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0xA>(s)), _mm_castsi128_ps(a)));
    std::get<0xB>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0xB>(s)), _mm_castsi128_ps(a)));
    std::get<0xC>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0xC>(s)), _mm_castsi128_ps(a)));
    std::get<0xD>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0xD>(s)), _mm_castsi128_ps(a)));
    std::get<0xE>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0xE>(s)), _mm_castsi128_ps(a)));
    std::get<0xF>(s) = _mm_castps_si128(
        _mm_add_ps(_mm_castsi128_ps(std::get<0xF>(s)), _mm_castsi128_ps(a)));
}

MCKL_INLINE inline void mul_ps(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x0>(s)), _mm_castsi128_ps(a)));
    std::get<0x1>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x1>(s)), _mm_castsi128_ps(a)));
    std::get<0x2>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x2>(s)), _mm_castsi128_ps(a)));
    std::get<0x3>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x3>(s)), _mm_castsi128_ps(a)));
    std::get<0x4>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x4>(s)), _mm_castsi128_ps(a)));
    std::get<0x5>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x5>(s)), _mm_castsi128_ps(a)));
    std::get<0x6>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x6>(s)), _mm_castsi128_ps(a)));
    std::get<0x7>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x7>(s)), _mm_castsi128_ps(a)));
    std::get<0x8>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x8>(s)), _mm_castsi128_ps(a)));
    std::get<0x9>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0x9>(s)), _mm_castsi128_ps(a)));
    std::get<0xA>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0xA>(s)), _mm_castsi128_ps(a)));
    std::get<0xB>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0xB>(s)), _mm_castsi128_ps(a)));
    std::get<0xC>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0xC>(s)), _mm_castsi128_ps(a)));
    std::get<0xD>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0xD>(s)), _mm_castsi128_ps(a)));
    std::get<0xE>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0xE>(s)), _mm_castsi128_ps(a)));
    std::get<0xF>(s) = _mm_castps_si128(
        _mm_mul_ps(_mm_castsi128_ps(std::get<0xF>(s)), _mm_castsi128_ps(a)));
}

MCKL_INLINE inline void add_pd(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x0>(s)), _mm_castsi128_pd(a)));
    std::get<0x1>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x1>(s)), _mm_castsi128_pd(a)));
    std::get<0x2>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x2>(s)), _mm_castsi128_pd(a)));
    std::get<0x3>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x3>(s)), _mm_castsi128_pd(a)));
    std::get<0x4>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x4>(s)), _mm_castsi128_pd(a)));
    std::get<0x5>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x5>(s)), _mm_castsi128_pd(a)));
    std::get<0x6>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x6>(s)), _mm_castsi128_pd(a)));
    std::get<0x7>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x7>(s)), _mm_castsi128_pd(a)));
    std::get<0x8>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x8>(s)), _mm_castsi128_pd(a)));
    std::get<0x9>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0x9>(s)), _mm_castsi128_pd(a)));
    std::get<0xA>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0xA>(s)), _mm_castsi128_pd(a)));
    std::get<0xB>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0xB>(s)), _mm_castsi128_pd(a)));
    std::get<0xC>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0xC>(s)), _mm_castsi128_pd(a)));
    std::get<0xD>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0xD>(s)), _mm_castsi128_pd(a)));
    std::get<0xE>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0xE>(s)), _mm_castsi128_pd(a)));
    std::get<0xF>(s) = _mm_castpd_si128(
        _mm_add_pd(_mm_castsi128_pd(std::get<0xF>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void add_pd(
    std::array<__m128i, 16> &s, const std::array<__m128i, 16> &a)
{
    std::get<0x0>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x0>(s)),
            _mm_castsi128_pd(std::get<0x0>(a))));
    std::get<0x1>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x1>(s)),
            _mm_castsi128_pd(std::get<0x1>(a))));
    std::get<0x2>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x2>(s)),
            _mm_castsi128_pd(std::get<0x2>(a))));
    std::get<0x3>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x3>(s)),
            _mm_castsi128_pd(std::get<0x3>(a))));
    std::get<0x4>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x4>(s)),
            _mm_castsi128_pd(std::get<0x4>(a))));
    std::get<0x5>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x5>(s)),
            _mm_castsi128_pd(std::get<0x5>(a))));
    std::get<0x6>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x6>(s)),
            _mm_castsi128_pd(std::get<0x6>(a))));
    std::get<0x7>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x7>(s)),
            _mm_castsi128_pd(std::get<0x7>(a))));
    std::get<0x8>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x8>(s)),
            _mm_castsi128_pd(std::get<0x8>(a))));
    std::get<0x9>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0x9>(s)),
            _mm_castsi128_pd(std::get<0x9>(a))));
    std::get<0xA>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0xA>(s)),
            _mm_castsi128_pd(std::get<0xA>(a))));
    std::get<0xB>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0xB>(s)),
            _mm_castsi128_pd(std::get<0xB>(a))));
    std::get<0xC>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0xC>(s)),
            _mm_castsi128_pd(std::get<0xC>(a))));
    std::get<0xD>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0xD>(s)),
            _mm_castsi128_pd(std::get<0xD>(a))));
    std::get<0xE>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0xE>(s)),
            _mm_castsi128_pd(std::get<0xE>(a))));
    std::get<0xF>(s) =
        _mm_castpd_si128(_mm_add_pd(_mm_castsi128_pd(std::get<0xF>(s)),
            _mm_castsi128_pd(std::get<0xF>(a))));
}

MCKL_INLINE inline void sub_pd(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x0>(s)), _mm_castsi128_pd(a)));
    std::get<0x1>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x1>(s)), _mm_castsi128_pd(a)));
    std::get<0x2>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x2>(s)), _mm_castsi128_pd(a)));
    std::get<0x3>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x3>(s)), _mm_castsi128_pd(a)));
    std::get<0x4>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x4>(s)), _mm_castsi128_pd(a)));
    std::get<0x5>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x5>(s)), _mm_castsi128_pd(a)));
    std::get<0x6>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x6>(s)), _mm_castsi128_pd(a)));
    std::get<0x7>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x7>(s)), _mm_castsi128_pd(a)));
    std::get<0x8>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x8>(s)), _mm_castsi128_pd(a)));
    std::get<0x9>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0x9>(s)), _mm_castsi128_pd(a)));
    std::get<0xA>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0xA>(s)), _mm_castsi128_pd(a)));
    std::get<0xB>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0xB>(s)), _mm_castsi128_pd(a)));
    std::get<0xC>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0xC>(s)), _mm_castsi128_pd(a)));
    std::get<0xD>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0xD>(s)), _mm_castsi128_pd(a)));
    std::get<0xE>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0xE>(s)), _mm_castsi128_pd(a)));
    std::get<0xF>(s) = _mm_castpd_si128(
        _mm_sub_pd(_mm_castsi128_pd(std::get<0xF>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void mul_pd(std::array<__m128i, 16> &s, const __m128i &a)
{
    std::get<0x0>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x0>(s)), _mm_castsi128_pd(a)));
    std::get<0x1>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x1>(s)), _mm_castsi128_pd(a)));
    std::get<0x2>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x2>(s)), _mm_castsi128_pd(a)));
    std::get<0x3>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x3>(s)), _mm_castsi128_pd(a)));
    std::get<0x4>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x4>(s)), _mm_castsi128_pd(a)));
    std::get<0x5>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x5>(s)), _mm_castsi128_pd(a)));
    std::get<0x6>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x6>(s)), _mm_castsi128_pd(a)));
    std::get<0x7>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x7>(s)), _mm_castsi128_pd(a)));
    std::get<0x8>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x8>(s)), _mm_castsi128_pd(a)));
    std::get<0x9>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0x9>(s)), _mm_castsi128_pd(a)));
    std::get<0xA>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0xA>(s)), _mm_castsi128_pd(a)));
    std::get<0xB>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0xB>(s)), _mm_castsi128_pd(a)));
    std::get<0xC>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0xC>(s)), _mm_castsi128_pd(a)));
    std::get<0xD>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0xD>(s)), _mm_castsi128_pd(a)));
    std::get<0xE>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0xE>(s)), _mm_castsi128_pd(a)));
    std::get<0xF>(s) = _mm_castpd_si128(
        _mm_mul_pd(_mm_castsi128_pd(std::get<0xF>(s)), _mm_castsi128_pd(a)));
}

MCKL_INLINE inline void mul_pd(
    std::array<__m128i, 16> &s, const std::array<__m128i, 16> &a)
{
    std::get<0x0>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x0>(s)),
            _mm_castsi128_pd(std::get<0x0>(a))));
    std::get<0x1>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x1>(s)),
            _mm_castsi128_pd(std::get<0x1>(a))));
    std::get<0x2>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x2>(s)),
            _mm_castsi128_pd(std::get<0x2>(a))));
    std::get<0x3>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x3>(s)),
            _mm_castsi128_pd(std::get<0x3>(a))));
    std::get<0x4>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x4>(s)),
            _mm_castsi128_pd(std::get<0x4>(a))));
    std::get<0x5>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x5>(s)),
            _mm_castsi128_pd(std::get<0x5>(a))));
    std::get<0x6>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x6>(s)),
            _mm_castsi128_pd(std::get<0x6>(a))));
    std::get<0x7>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x7>(s)),
            _mm_castsi128_pd(std::get<0x7>(a))));
    std::get<0x8>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x8>(s)),
            _mm_castsi128_pd(std::get<0x8>(a))));
    std::get<0x9>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0x9>(s)),
            _mm_castsi128_pd(std::get<0x9>(a))));
    std::get<0xA>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0xA>(s)),
            _mm_castsi128_pd(std::get<0xA>(a))));
    std::get<0xB>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0xB>(s)),
            _mm_castsi128_pd(std::get<0xB>(a))));
    std::get<0xC>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0xC>(s)),
            _mm_castsi128_pd(std::get<0xC>(a))));
    std::get<0xD>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0xD>(s)),
            _mm_castsi128_pd(std::get<0xD>(a))));
    std::get<0xE>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0xE>(s)),
            _mm_castsi128_pd(std::get<0xE>(a))));
    std::get<0xF>(s) =
        _mm_castpd_si128(_mm_mul_pd(_mm_castsi128_pd(std::get<0xF>(s)),
            _mm_castsi128_pd(std::get<0xF>(a))));
}

} // namespace internal

} // namespace mckl

MCKL_POP_GCC_WARNING

#endif // MCKL_INTERNAL_SSE2_OP_HPP
