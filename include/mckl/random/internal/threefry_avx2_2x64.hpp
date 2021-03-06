//============================================================================
// MCKL/include/mckl/random/internal/threefry_avx2_2x64.hpp
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

#ifndef MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_HPP
#define MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_HPP

#include <mckl/random/internal/common.hpp>
#include <mckl/random/internal/threefry_common.hpp>
#include <mckl/random/internal/threefry_constants.hpp>
#include <mckl/random/internal/threefry_generic_2x64.hpp>
#include <mckl/random/increment.hpp>

MCKL_PUSH_GCC_WARNING("-Wignored-attributes")

#define MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_KBOX(N)                       \
    ymmt0 = _mm256_set1_epi64x(static_cast<MCKL_INT64>(                       \
        ThreefryKBox<T, K, N>::template key<0>(par)));                        \
    ymmt1 = _mm256_set1_epi64x(static_cast<MCKL_INT64>(                       \
        ThreefryKBox<T, K, N>::template key<1>(par)));                        \
    ymms0 = _mm256_add_epi64(ymms0, ymmt0);                                   \
    ymms1 = _mm256_add_epi64(ymms1, ymmt1);                                   \
    ymms2 = _mm256_add_epi64(ymms2, ymmt0);                                   \
    ymms3 = _mm256_add_epi64(ymms3, ymmt1);                                   \
    ymms4 = _mm256_add_epi64(ymms4, ymmt0);                                   \
    ymms5 = _mm256_add_epi64(ymms5, ymmt1);                                   \
    ymms6 = _mm256_add_epi64(ymms6, ymmt0);                                   \
    ymms7 = _mm256_add_epi64(ymms7, ymmt1);

#define MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N)                       \
    {                                                                         \
        constexpr int L0 = Constants::rotate::value[0][(N - 1) % 8];          \
        constexpr int R0 = 64 - L0;                                           \
        ymms0 = _mm256_add_epi64(ymms0, ymms1);                               \
        ymms2 = _mm256_add_epi64(ymms2, ymms3);                               \
        ymms4 = _mm256_add_epi64(ymms4, ymms5);                               \
        ymms6 = _mm256_add_epi64(ymms6, ymms7);                               \
        ymmt1 = _mm256_slli_epi64(ymms1, L0);                                 \
        ymmt3 = _mm256_slli_epi64(ymms3, L0);                                 \
        ymmt5 = _mm256_slli_epi64(ymms5, L0);                                 \
        ymmt7 = _mm256_slli_epi64(ymms7, L0);                                 \
        ymms1 = _mm256_srli_epi64(ymms1, R0);                                 \
        ymms3 = _mm256_srli_epi64(ymms3, R0);                                 \
        ymms5 = _mm256_srli_epi64(ymms5, R0);                                 \
        ymms7 = _mm256_srli_epi64(ymms7, R0);                                 \
        ymmt1 = _mm256_or_si256(ymms1, ymmt1);                                \
        ymmt3 = _mm256_or_si256(ymms3, ymmt3);                                \
        ymmt5 = _mm256_or_si256(ymms5, ymmt5);                                \
        ymmt7 = _mm256_or_si256(ymms7, ymmt7);                                \
        ymms1 = _mm256_xor_si256(ymms0, ymmt1);                               \
        ymms3 = _mm256_xor_si256(ymms2, ymmt3);                               \
        ymms5 = _mm256_xor_si256(ymms4, ymmt5);                               \
        ymms7 = _mm256_xor_si256(ymms6, ymmt7);                               \
    }

#define MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_CYCLE_4(N)                    \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 1);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 2);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 3);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 4);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_KBOX(N * 8 + 4);

#define MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_CYCLE_8(N)                    \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 1);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 2);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 3);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 4);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_KBOX(N * 8 + 4);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 5);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 6);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 7);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_RBOX(N * 8 + 8);                  \
    MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_KBOX(N * 8 + 8);

namespace mckl {

namespace internal {

template <typename T>
class Threefry2x64GeneratorAVX2Impl
{
    static_assert(std::numeric_limits<T>::digits == 64,
        "**Threefry2x64GeneratorAVX2Impl** used with T other than a 64-bit "
        "unsigned integers");

    static constexpr std::size_t K = 2;
    static constexpr std::size_t Rounds = 20;
    using Constants = ThreefryConstants<T, 2>;

  public:
    static void eval(
        const void *plain, void *cipher, const std::array<T, K + 4> &par)
    {
        Threefry2x64GeneratorGenericImpl<T>::eval(plain, cipher, par);
    }

    template <typename ResultType>
    static void eval(std::array<std::uint64_t, 2> &ctr, ResultType *r,
        const std::array<T, K + 4> &par)
    {
        Threefry2x64GeneratorGenericImpl<T>::eval(ctr, r, par);
    }

    template <typename ResultType>
    static void eval(std::array<std::uint64_t, 2> &ctr, std::size_t n,
        ResultType *r, const std::array<T, K + 4> &par)
    {
        constexpr std::size_t R = sizeof(T) * K / sizeof(ResultType);

        const std::size_t n0 =
            static_cast<std::size_t>(std::min(static_cast<std::uint64_t>(n),
                std::numeric_limits<std::uint64_t>::max() - ctr.front()));

        eval_kernel(ctr, n0, r, par);
        n -= n0;
        r += n0 * R;

        if (n != 0) {
            eval(ctr, r, par);
            n -= 1;
            r += R;
        }

        eval_kernel(ctr, n, r, par);
    }

  private:
    template <typename ResultType>
    static void eval_kernel(std::array<std::uint64_t, 2> &ctr, std::size_t n,
        ResultType *r, const std::array<T, K + 4> &par)
    {
        constexpr std::size_t S = 8;
        constexpr std::size_t N = sizeof(__m256i) * S / (sizeof(T) * K);

        __m256i ymmc =
            _mm256_set_epi64x(static_cast<MCKL_INT64>(std::get<1>(ctr)),
                static_cast<MCKL_INT64>(std::get<0>(ctr)),
                static_cast<MCKL_INT64>(std::get<1>(ctr)),
                static_cast<MCKL_INT64>(std::get<0>(ctr)));
        ctr.front() += n;

        __m256i *rptr = reinterpret_cast<__m256i *>(r);
        while (n != 0) {
            __m256i ymms0 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x02, 0, 0x01));
            __m256i ymms1 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x04, 0, 0x03));
            __m256i ymms2 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x06, 0, 0x05));
            __m256i ymms3 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x08, 0, 0x07));
            __m256i ymms4 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x0A, 0, 0x09));
            __m256i ymms5 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x0C, 0, 0x0B));
            __m256i ymms6 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x0E, 0, 0x0D));
            __m256i ymms7 =
                _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x10, 0, 0x0F));
            ymmc = _mm256_add_epi64(ymmc, _mm256_set_epi64x(0, 0x10, 0, 0x10));

            __m256i ymmt0;
            __m256i ymmt1;
            __m256i ymmt2;
            __m256i ymmt3;
            __m256i ymmt4;
            __m256i ymmt5;
            __m256i ymmt6;
            __m256i ymmt7;

            ymmt1 = ymms1;
            ymms1 = ymms2;
            ymms2 = ymms4;
            ymms4 = ymmt1;

            ymmt3 = ymms3;
            ymms3 = ymms6;
            ymms6 = ymms5;
            ymms5 = ymmt3;

            ymmt0 = _mm256_unpacklo_epi64(ymms0, ymms1);
            ymmt1 = _mm256_unpacklo_epi64(ymms2, ymms3);
            ymmt2 = _mm256_unpackhi_epi64(ymms0, ymms1);
            ymmt3 = _mm256_unpackhi_epi64(ymms2, ymms3);
            ymmt4 = _mm256_unpacklo_epi64(ymms4, ymms5);
            ymmt5 = _mm256_unpacklo_epi64(ymms6, ymms7);
            ymmt6 = _mm256_unpackhi_epi64(ymms4, ymms5);
            ymmt7 = _mm256_unpackhi_epi64(ymms6, ymms7);
            ymms0 = _mm256_permute2x128_si256(ymmt0, ymmt1, 0x20);
            ymms1 = _mm256_permute2x128_si256(ymmt2, ymmt3, 0x20);
            ymms2 = _mm256_permute2x128_si256(ymmt0, ymmt1, 0x31);
            ymms3 = _mm256_permute2x128_si256(ymmt2, ymmt3, 0x31);
            ymms4 = _mm256_permute2x128_si256(ymmt4, ymmt5, 0x20);
            ymms5 = _mm256_permute2x128_si256(ymmt6, ymmt7, 0x20);
            ymms6 = _mm256_permute2x128_si256(ymmt4, ymmt5, 0x31);
            ymms7 = _mm256_permute2x128_si256(ymmt6, ymmt7, 0x31);

            MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_KBOX(0)
            MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_CYCLE_8(0)
            MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_CYCLE_8(1)
            MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_CYCLE_4(2)

            ymmt0 = _mm256_unpacklo_epi64(ymms0, ymms1);
            ymmt1 = _mm256_unpacklo_epi64(ymms2, ymms3);
            ymmt2 = _mm256_unpackhi_epi64(ymms0, ymms1);
            ymmt3 = _mm256_unpackhi_epi64(ymms2, ymms3);
            ymmt4 = _mm256_unpacklo_epi64(ymms4, ymms5);
            ymmt5 = _mm256_unpacklo_epi64(ymms6, ymms7);
            ymmt6 = _mm256_unpackhi_epi64(ymms4, ymms5);
            ymmt7 = _mm256_unpackhi_epi64(ymms6, ymms7);
            ymms0 = _mm256_permute2x128_si256(ymmt0, ymmt1, 0x20);
            ymms1 = _mm256_permute2x128_si256(ymmt2, ymmt3, 0x20);
            ymms2 = _mm256_permute2x128_si256(ymmt0, ymmt1, 0x31);
            ymms3 = _mm256_permute2x128_si256(ymmt2, ymmt3, 0x31);
            ymms4 = _mm256_permute2x128_si256(ymmt4, ymmt5, 0x20);
            ymms5 = _mm256_permute2x128_si256(ymmt6, ymmt7, 0x20);
            ymms6 = _mm256_permute2x128_si256(ymmt4, ymmt5, 0x31);
            ymms7 = _mm256_permute2x128_si256(ymmt6, ymmt7, 0x31);

            ymmt2 = ymms2;
            ymms2 = ymms1;
            ymms1 = ymms4;
            ymms4 = ymmt2;

            ymmt6 = ymms6;
            ymms6 = ymms3;
            ymms3 = ymms5;
            ymms5 = ymmt6;

            if (n >= N) {
                n -= N;
                _mm256_storeu_si256(rptr++, ymms0);
                _mm256_storeu_si256(rptr++, ymms1);
                _mm256_storeu_si256(rptr++, ymms2);
                _mm256_storeu_si256(rptr++, ymms3);
                _mm256_storeu_si256(rptr++, ymms4);
                _mm256_storeu_si256(rptr++, ymms5);
                _mm256_storeu_si256(rptr++, ymms6);
                _mm256_storeu_si256(rptr++, ymms7);
            } else {
                std::array<__m256i, S> s;
                std::get<0>(s) = ymms0;
                std::get<1>(s) = ymms1;
                std::get<2>(s) = ymms2;
                std::get<3>(s) = ymms3;
                std::get<4>(s) = ymms4;
                std::get<5>(s) = ymms5;
                std::get<6>(s) = ymms6;
                std::get<7>(s) = ymms7;
                std::memcpy(rptr, s.data(), n * sizeof(T) * K);
                break;
            }
        }
    }
}; // class Threefry2x64GeneratorAVX2Impl

} // namespace internal

} // namespace mckl

MCKL_POP_GCC_WARNING

#endif // MCKL_RANDOM_INTERNAL_THREEFRY_AVX2_2X64_HPP
