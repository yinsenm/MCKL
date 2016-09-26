//============================================================================
// MCKL/include/mckl/random/threefry8x64_avx2.hpp
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

template <typename T, std::size_t Rounds, typename Constants>
class ThreefryGeneratorImpl<T, 8, Rounds, Constants, 64>
{
    static constexpr std::size_t K_ = 8;

    public:
    static constexpr bool batch() { return true; }

    static constexpr std::size_t blocks() { return 64 / K_; }

    static void eval(
        std::array<T, K_> &state, const std::array<T, K_ + 1> &par)
    {
        ThreefryGeneratorGenericImpl<T, K_, Rounds, Constants>::eval(
            state, par);
    }

    static void eval(std::array<std::array<T, K_>, blocks()> &state,
        const std::array<T, K_ + 1> &par)
    {
        std::array<__m256i, 16> s;

        pack(state, s);

        // clang-format off
        sbox<0x00>(s); pbox<0x00>(s); kbox<0x00>(s, par);
        sbox<0x01>(s); pbox<0x01>(s); kbox<0x01>(s, par);
        sbox<0x02>(s); pbox<0x02>(s); kbox<0x02>(s, par);
        sbox<0x03>(s); pbox<0x03>(s); kbox<0x03>(s, par);
        sbox<0x04>(s); pbox<0x04>(s); kbox<0x04>(s, par);
        sbox<0x05>(s); pbox<0x05>(s); kbox<0x05>(s, par);
        sbox<0x06>(s); pbox<0x06>(s); kbox<0x06>(s, par);
        sbox<0x07>(s); pbox<0x07>(s); kbox<0x07>(s, par);
        sbox<0x08>(s); pbox<0x08>(s); kbox<0x08>(s, par);
        sbox<0x09>(s); pbox<0x09>(s); kbox<0x09>(s, par);
        sbox<0x0A>(s); pbox<0x0A>(s); kbox<0x0A>(s, par);
        sbox<0x0B>(s); pbox<0x0B>(s); kbox<0x0B>(s, par);
        sbox<0x0C>(s); pbox<0x0C>(s); kbox<0x0C>(s, par);
        sbox<0x0D>(s); pbox<0x0D>(s); kbox<0x0D>(s, par);
        sbox<0x0E>(s); pbox<0x0E>(s); kbox<0x0E>(s, par);
        sbox<0x0F>(s); pbox<0x0F>(s); kbox<0x0F>(s, par);
        sbox<0x10>(s); pbox<0x10>(s); kbox<0x10>(s, par);
        sbox<0x11>(s); pbox<0x11>(s); kbox<0x11>(s, par);
        sbox<0x12>(s); pbox<0x12>(s); kbox<0x12>(s, par);
        sbox<0x13>(s); pbox<0x13>(s); kbox<0x13>(s, par);
        sbox<0x14>(s); pbox<0x14>(s); kbox<0x14>(s, par);
        sbox<0x15>(s); pbox<0x15>(s); kbox<0x15>(s, par);
        sbox<0x16>(s); pbox<0x16>(s); kbox<0x16>(s, par);
        sbox<0x17>(s); pbox<0x17>(s); kbox<0x17>(s, par);
        sbox<0x18>(s); pbox<0x18>(s); kbox<0x18>(s, par);
        sbox<0x19>(s); pbox<0x19>(s); kbox<0x19>(s, par);
        sbox<0x1A>(s); pbox<0x1A>(s); kbox<0x1A>(s, par);
        sbox<0x1B>(s); pbox<0x1B>(s); kbox<0x1B>(s, par);
        sbox<0x1C>(s); pbox<0x1C>(s); kbox<0x1C>(s, par);
        sbox<0x1D>(s); pbox<0x1D>(s); kbox<0x1D>(s, par);
        sbox<0x1E>(s); pbox<0x1E>(s); kbox<0x1E>(s, par);
        sbox<0x1F>(s); pbox<0x1F>(s); kbox<0x1F>(s, par);
        // clang-format on

        eval<0x20>(s, par, std::integral_constant<bool, 0x20 <= Rounds>());

        unpack(state, s);
    }

    private:
    template <std::size_t>
    static void eval(std::array<__m256i, 16> &, const std::array<T, K_ + 1> &,
        std::false_type)
    {
    }

    template <std::size_t N>
    static void eval(std::array<__m256i, 16> &s,
        const std::array<T, K_ + 1> &par, std::true_type)
    {
        sbox<N>(s);
        pbox<N>(s);
        kbox<N>(s, par);
        eval<N + 1>(s, par, std::integral_constant<bool, N + 1 <= Rounds>());
    }

    static void pack(std::array<std::array<T, K_>, blocks()> &state,
        std::array<__m256i, 16> &s)
    {
        const __m256i *sptr = reinterpret_cast<const __m256i *>(state.data());
        std::get<0x0>(s) = _mm256_load_si256(sptr++);
        std::get<0x4>(s) = _mm256_load_si256(sptr++);
        std::get<0x1>(s) = _mm256_load_si256(sptr++);
        std::get<0x5>(s) = _mm256_load_si256(sptr++);
        std::get<0x2>(s) = _mm256_load_si256(sptr++);
        std::get<0x6>(s) = _mm256_load_si256(sptr++);
        std::get<0x3>(s) = _mm256_load_si256(sptr++);
        std::get<0x7>(s) = _mm256_load_si256(sptr++);
        std::get<0x8>(s) = _mm256_load_si256(sptr++);
        std::get<0xC>(s) = _mm256_load_si256(sptr++);
        std::get<0x9>(s) = _mm256_load_si256(sptr++);
        std::get<0xD>(s) = _mm256_load_si256(sptr++);
        std::get<0xA>(s) = _mm256_load_si256(sptr++);
        std::get<0xE>(s) = _mm256_load_si256(sptr++);
        std::get<0xB>(s) = _mm256_load_si256(sptr++);
        std::get<0xF>(s) = _mm256_load_si256(sptr++);

        transpose4x64_si256<0x0, 0x1, 0x2, 0x3>(s);
        transpose4x64_si256<0x4, 0x5, 0x6, 0x7>(s);
        transpose4x64_si256<0x8, 0x9, 0xA, 0xB>(s);
        transpose4x64_si256<0xC, 0xD, 0xE, 0xF>(s);
    }

    static void unpack(std::array<std::array<T, K_>, blocks()> &state,
        std::array<__m256i, 16> &s)
    {
        transpose4x64_si256<0x0, 0x1, 0x2, 0x3>(s);
        transpose4x64_si256<0x4, 0x5, 0x6, 0x7>(s);
        transpose4x64_si256<0x8, 0x9, 0xA, 0xB>(s);
        transpose4x64_si256<0xC, 0xD, 0xE, 0xF>(s);

        __m256i *sptr = reinterpret_cast<__m256i *>(state.data());
        _mm256_store_si256(sptr++, std::get<0x0>(s));
        _mm256_store_si256(sptr++, std::get<0x4>(s));
        _mm256_store_si256(sptr++, std::get<0x1>(s));
        _mm256_store_si256(sptr++, std::get<0x5>(s));
        _mm256_store_si256(sptr++, std::get<0x2>(s));
        _mm256_store_si256(sptr++, std::get<0x6>(s));
        _mm256_store_si256(sptr++, std::get<0x3>(s));
        _mm256_store_si256(sptr++, std::get<0x7>(s));
        _mm256_store_si256(sptr++, std::get<0x8>(s));
        _mm256_store_si256(sptr++, std::get<0xC>(s));
        _mm256_store_si256(sptr++, std::get<0x9>(s));
        _mm256_store_si256(sptr++, std::get<0xD>(s));
        _mm256_store_si256(sptr++, std::get<0xA>(s));
        _mm256_store_si256(sptr++, std::get<0xE>(s));
        _mm256_store_si256(sptr++, std::get<0xB>(s));
        _mm256_store_si256(sptr++, std::get<0xF>(s));
    }

    template <std::size_t N>
    static void kbox(
        std::array<__m256i, 16> &s, const std::array<T, K_ + 1> &par)
    {
        kbox<N>(s, par,
            std::integral_constant<bool, (N % 4 == 0 && N <= Rounds)>());
    }

    template <std::size_t>
    static void kbox(std::array<__m256i, 16> &, const std::array<T, K_ + 1> &,
        std::false_type)
    {
    }

    template <std::size_t N>
    static void kbox(std::array<__m256i, 16> &s,
        const std::array<T, K_ + 1> &par, std::true_type)
    {
        static constexpr std::size_t S = N / 4;

        const MCKL_INT64 k0 =
            static_cast<MCKL_INT64>(std::get<(S + 0) % (K_ + 1)>(par));
        const MCKL_INT64 k1 =
            static_cast<MCKL_INT64>(std::get<(S + 1) % (K_ + 1)>(par));
        const MCKL_INT64 k2 =
            static_cast<MCKL_INT64>(std::get<(S + 2) % (K_ + 1)>(par));
        const MCKL_INT64 k3 =
            static_cast<MCKL_INT64>(std::get<(S + 3) % (K_ + 1)>(par));
        const MCKL_INT64 k4 =
            static_cast<MCKL_INT64>(std::get<(S + 4) % (K_ + 1)>(par));
        const MCKL_INT64 k5 =
            static_cast<MCKL_INT64>(std::get<(S + 5) % (K_ + 1)>(par));
        const MCKL_INT64 k6 =
            static_cast<MCKL_INT64>(std::get<(S + 6) % (K_ + 1)>(par));
        const MCKL_INT64 k7 =
            static_cast<MCKL_INT64>(std::get<(S + 7) % (K_ + 1)>(par) + S);

        const __m256i p0 = _mm256_set1_epi64x(k0);
        const __m256i p1 = _mm256_set1_epi64x(k1);
        const __m256i p2 = _mm256_set1_epi64x(k2);
        const __m256i p3 = _mm256_set1_epi64x(k3);
        const __m256i p4 = _mm256_set1_epi64x(k4);
        const __m256i p5 = _mm256_set1_epi64x(k5);
        const __m256i p6 = _mm256_set1_epi64x(k6);
        const __m256i p7 = _mm256_set1_epi64x(k7);

        std::get<0x0>(s) = _mm256_add_epi64(std::get<0x0>(s), p0);
        std::get<0x1>(s) = _mm256_add_epi64(std::get<0x1>(s), p1);
        std::get<0x2>(s) = _mm256_add_epi64(std::get<0x2>(s), p2);
        std::get<0x3>(s) = _mm256_add_epi64(std::get<0x3>(s), p3);
        std::get<0x4>(s) = _mm256_add_epi64(std::get<0x4>(s), p4);
        std::get<0x5>(s) = _mm256_add_epi64(std::get<0x5>(s), p5);
        std::get<0x6>(s) = _mm256_add_epi64(std::get<0x6>(s), p6);
        std::get<0x7>(s) = _mm256_add_epi64(std::get<0x7>(s), p7);
        std::get<0x8>(s) = _mm256_add_epi64(std::get<0x8>(s), p0);
        std::get<0x9>(s) = _mm256_add_epi64(std::get<0x9>(s), p1);
        std::get<0xA>(s) = _mm256_add_epi64(std::get<0xA>(s), p2);
        std::get<0xB>(s) = _mm256_add_epi64(std::get<0xB>(s), p3);
        std::get<0xC>(s) = _mm256_add_epi64(std::get<0xC>(s), p4);
        std::get<0xD>(s) = _mm256_add_epi64(std::get<0xD>(s), p5);
        std::get<0xE>(s) = _mm256_add_epi64(std::get<0xE>(s), p6);
        std::get<0xF>(s) = _mm256_add_epi64(std::get<0xF>(s), p7);
    }

    template <std::size_t N>
    static void sbox(std::array<__m256i, 16> &s)
    {
        sbox<N>(s, std::integral_constant<bool, (N > 0 && N <= Rounds)>());
    }

    template <std::size_t>
    static void sbox(std::array<__m256i, 16> &, std::false_type)
    {
    }

    template <std::size_t N>
    static void sbox(std::array<__m256i, 16> &s, std::true_type)
    {
        static constexpr int L0 = Constants::rotate[0][(N - 1) % 8];
        static constexpr int L1 = Constants::rotate[1][(N - 1) % 8];
        static constexpr int L2 = Constants::rotate[2][(N - 1) % 8];
        static constexpr int L3 = Constants::rotate[3][(N - 1) % 8];
        static constexpr int R0 = 64 - L0;
        static constexpr int R1 = 64 - L1;
        static constexpr int R2 = 64 - L2;
        static constexpr int R3 = 64 - L3;

        std::get<0x0>(s) =
            _mm256_add_epi64(std::get<0x0>(s), std::get<0x1>(s));
        std::get<0x2>(s) =
            _mm256_add_epi64(std::get<0x2>(s), std::get<0x3>(s));
        std::get<0x4>(s) =
            _mm256_add_epi64(std::get<0x4>(s), std::get<0x5>(s));
        std::get<0x6>(s) =
            _mm256_add_epi64(std::get<0x6>(s), std::get<0x7>(s));
        std::get<0x8>(s) =
            _mm256_add_epi64(std::get<0x8>(s), std::get<0x9>(s));
        std::get<0xA>(s) =
            _mm256_add_epi64(std::get<0xA>(s), std::get<0xB>(s));
        std::get<0xC>(s) =
            _mm256_add_epi64(std::get<0xC>(s), std::get<0xD>(s));
        std::get<0xE>(s) =
            _mm256_add_epi64(std::get<0xE>(s), std::get<0xF>(s));

        __m256i l0 = _mm256_slli_epi64(std::get<0x1>(s), L0);
        __m256i l1 = _mm256_slli_epi64(std::get<0x3>(s), L1);
        __m256i l2 = _mm256_slli_epi64(std::get<0x5>(s), L2);
        __m256i l3 = _mm256_slli_epi64(std::get<0x7>(s), L3);
        __m256i l4 = _mm256_slli_epi64(std::get<0x9>(s), L0);
        __m256i l5 = _mm256_slli_epi64(std::get<0xB>(s), L1);
        __m256i l6 = _mm256_slli_epi64(std::get<0xD>(s), L2);
        __m256i l7 = _mm256_slli_epi64(std::get<0xF>(s), L3);

        __m256i r0 = _mm256_srli_epi64(std::get<0x1>(s), R0);
        __m256i r1 = _mm256_srli_epi64(std::get<0x3>(s), R1);
        __m256i r2 = _mm256_srli_epi64(std::get<0x5>(s), R2);
        __m256i r3 = _mm256_srli_epi64(std::get<0x7>(s), R3);
        __m256i r4 = _mm256_srli_epi64(std::get<0x9>(s), R0);
        __m256i r5 = _mm256_srli_epi64(std::get<0xB>(s), R1);
        __m256i r6 = _mm256_srli_epi64(std::get<0xD>(s), R2);
        __m256i r7 = _mm256_srli_epi64(std::get<0xF>(s), R3);

        std::get<0x1>(s) = _mm256_or_si256(l0, r0);
        std::get<0x3>(s) = _mm256_or_si256(l1, r1);
        std::get<0x5>(s) = _mm256_or_si256(l2, r2);
        std::get<0x7>(s) = _mm256_or_si256(l3, r3);
        std::get<0x9>(s) = _mm256_or_si256(l4, r4);
        std::get<0xB>(s) = _mm256_or_si256(l5, r5);
        std::get<0xD>(s) = _mm256_or_si256(l6, r6);
        std::get<0xF>(s) = _mm256_or_si256(l7, r7);

        std::get<0x1>(s) =
            _mm256_xor_si256(std::get<0x0>(s), std::get<0x1>(s));
        std::get<0x3>(s) =
            _mm256_xor_si256(std::get<0x2>(s), std::get<0x3>(s));
        std::get<0x5>(s) =
            _mm256_xor_si256(std::get<0x4>(s), std::get<0x5>(s));
        std::get<0x7>(s) =
            _mm256_xor_si256(std::get<0x6>(s), std::get<0x7>(s));
        std::get<0x9>(s) =
            _mm256_xor_si256(std::get<0x8>(s), std::get<0x9>(s));
        std::get<0xB>(s) =
            _mm256_xor_si256(std::get<0xA>(s), std::get<0xB>(s));
        std::get<0xD>(s) =
            _mm256_xor_si256(std::get<0xC>(s), std::get<0xD>(s));
        std::get<0xF>(s) =
            _mm256_xor_si256(std::get<0xE>(s), std::get<0xF>(s));
    }

    template <std::size_t N>
    static void pbox(std::array<__m256i, 16> &s)
    {
        pbox<N>(s, std::integral_constant<bool, (N > 0 && N <= Rounds)>());
    }

    template <std::size_t N>
    static void pbox(std::array<__m256i, 16> &, std::false_type)
    {
    }

    template <std::size_t N>
    static void pbox(std::array<__m256i, 16> &s, std::true_type)
    {
        ThreefryPBox<__m256i, K_, N, Constants>::eval(
            *(reinterpret_cast<std::array<__m256i, K_> *>(s.data()) + 0));
        ThreefryPBox<__m256i, K_, N, Constants>::eval(
            *(reinterpret_cast<std::array<__m256i, K_> *>(s.data()) + 1));
    }
}; // class ThreefryGeneratorImpl
