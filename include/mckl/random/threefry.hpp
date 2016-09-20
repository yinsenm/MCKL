//============================================================================
// MCKL/include/mckl/random/threefry.hpp
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

#ifndef MCKL_RANDOM_THREEFRY_HPP
#define MCKL_RANDOM_THREEFRY_HPP

#include <mckl/random/internal/common.hpp>
#include <mckl/random/counter.hpp>

#define MCKL_DEFINE_RANDOM_THREEFRY_PARITY_CONSTANT(W, val)                   \
    template <typename T>                                                     \
    class ThreefryParityConstant<T, W>                                        \
        : public std::integral_constant<T, UINT##W##_C(val)>                  \
    {                                                                         \
    }; // class ThreefryParityConstant

#define MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(W, K, N, I, val)          \
    template <typename T>                                                     \
    class ThreefryRotateConstant<T, K, N, I, W>                               \
        : public std::integral_constant<int, val>                             \
    {                                                                         \
    }; // class ThreefryRotateConstant

#define MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(K, I, val)               \
    template <>                                                               \
    class ThreefryPermuteConstant<K, I>                                       \
        : public std::integral_constant<std::size_t, val>                     \
    {                                                                         \
    }; // class ThreefryPermuteConstant

/// \brief ThreefryGenerator default rounds
/// \ingroup Config
#ifndef MCKL_THREEFRY_ROUNDS
#define MCKL_THREEFRY_ROUNDS 20
#endif

namespace mckl
{

namespace internal
{

template <typename T, int = std::numeric_limits<T>::digits>
class ThreefryParityConstant;

MCKL_DEFINE_RANDOM_THREEFRY_PARITY_CONSTANT(32, 0x1BD11BDA)
MCKL_DEFINE_RANDOM_THREEFRY_PARITY_CONSTANT(64, 0x1BD11BDAA9FC1A22)

template <typename T, std::size_t, std::size_t, std::size_t,
    int = std::numeric_limits<T>::digits>
class ThreefryRotateConstant;

MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 0, 0, 13)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 1, 0, 15)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 2, 0, 26)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 3, 0, 6)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 4, 0, 17)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 5, 0, 29)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 6, 0, 16)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 2, 7, 0, 24)

MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 0, 0, 10)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 1, 0, 11)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 2, 0, 13)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 3, 0, 23)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 4, 0, 6)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 5, 0, 17)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 6, 0, 25)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 7, 0, 18)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 0, 1, 26)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 1, 1, 21)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 2, 1, 27)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 3, 1, 5)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 4, 1, 20)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 5, 1, 11)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 6, 1, 10)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(32, 4, 7, 1, 20)

MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 0, 0, 16)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 1, 0, 42)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 2, 0, 12)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 3, 0, 31)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 4, 0, 16)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 5, 0, 32)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 6, 0, 24)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 2, 7, 0, 21)

MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 0, 0, 14)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 1, 0, 52)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 2, 0, 23)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 3, 0, 5)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 4, 0, 25)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 5, 0, 46)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 6, 0, 58)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 7, 0, 32)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 0, 1, 16)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 1, 1, 57)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 2, 1, 40)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 3, 1, 37)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 4, 1, 33)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 5, 1, 12)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 6, 1, 22)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 4, 7, 1, 32)

MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 0, 0, 46)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 1, 0, 33)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 2, 0, 17)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 3, 0, 44)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 4, 0, 39)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 5, 0, 13)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 6, 0, 25)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 7, 0, 8)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 0, 1, 36)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 1, 1, 27)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 2, 1, 49)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 3, 1, 9)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 4, 1, 30)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 5, 1, 50)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 6, 1, 29)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 7, 1, 35)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 0, 2, 19)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 1, 2, 14)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 2, 2, 36)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 3, 2, 54)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 4, 2, 34)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 5, 2, 10)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 6, 2, 39)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 7, 2, 56)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 0, 3, 37)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 1, 3, 42)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 2, 3, 39)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 3, 3, 56)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 4, 3, 24)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 5, 3, 17)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 6, 3, 43)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 8, 7, 3, 22)

MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 0, 24)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 0, 38)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 0, 33)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 0, 5)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 0, 41)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 0, 16)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 0, 31)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 0, 9)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 1, 13)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 1, 19)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 1, 4)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 1, 20)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 1, 9)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 1, 34)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 1, 44)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 1, 48)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 2, 8)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 2, 10)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 2, 51)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 2, 48)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 2, 37)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 2, 56)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 2, 47)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 2, 35)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 3, 47)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 3, 55)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 3, 13)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 3, 41)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 3, 31)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 3, 51)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 3, 46)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 3, 52)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 4, 8)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 4, 49)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 4, 34)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 4, 47)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 4, 12)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 4, 4)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 4, 19)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 4, 23)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 5, 17)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 5, 18)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 5, 41)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 5, 28)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 5, 47)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 5, 53)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 5, 42)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 5, 31)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 6, 22)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 6, 23)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 6, 59)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 6, 16)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 6, 44)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 6, 42)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 6, 44)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 6, 37)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 0, 7, 37)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 1, 7, 52)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 2, 7, 17)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 3, 7, 25)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 4, 7, 30)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 5, 7, 41)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 6, 7, 25)
MCKL_DEFINE_RANDOM_THREEFRY_ROTATE_CONSTANT(64, 16, 7, 7, 20)

template <std::size_t, std::size_t>
class ThreefryPermuteConstant;

MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(2, 0, 0)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(2, 1, 1)

MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(4, 0, 0)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(4, 1, 3)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(4, 2, 2)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(4, 3, 1)

MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 0, 2)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 1, 1)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 2, 4)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 3, 7)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 4, 6)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 5, 5)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 6, 0)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(8, 7, 3)

MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 0, 0)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 1, 9)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 2, 2)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 3, 13)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 4, 6)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 5, 11)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 6, 4)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 7, 15)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 8, 10)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 9, 7)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 10, 12)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 11, 3)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 12, 14)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 13, 5)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 14, 8)
MCKL_DEFINE_RANDOM_THREEFRY_PERMUTE_CONSTANT(16, 15, 1)

} // namespace internal

/// \brief Default Threefry constants
/// \ingroup Threefry
template <typename T, std::size_t K>
class ThreefryConstants
{
    public:
    /// \brief Key parity
    using parity = internal::ThreefryParityConstant<T>;

    /// \brief Rotate constant of I-th S-box of round `(N - 1) % 8`
    template <std::size_t N, std::size_t I>
    using rotate = internal::ThreefryRotateConstant<T, K, N, I>;

    /// \brief Permutation constant of I-th element
    template <std::size_t I>
    using permute = internal::ThreefryPermuteConstant<K, I>;
}; // class ThreefryConstants

namespace internal
{

template <std::size_t N, std::size_t I, typename Constants>
class ThreefryIndex
{
    template <std::size_t J>
    using permute = typename Constants::template permute<J>;

    public:
    static constexpr std::size_t value =
        ThreefryIndex<N - 1, permute<I>::value, Constants>::value;
}; // class ThreefryIndex

template <std::size_t I, typename Constants>
class ThreefryIndex<0, I, Constants>
{
    public:
    static constexpr std::size_t value = I;
}; // class ThreefryIndex

template <typename T, std::size_t K, std::size_t N, typename,
    bool = (N % 4 == 0)>
class ThreefrySubKey
{
    public:
    static void eval(std::array<T, K> &, const std::array<T, K + 1> &) {}
}; // class ThreefrySubKey

template <typename T, std::size_t K, std::size_t N, typename Constants>
class ThreefrySubKey<T, K, N, Constants, true>
{
    public:
    static void eval(std::array<T, K> &state, const std::array<T, K + 1> &par)
    {
        eval<0>(state, par, std::integral_constant<bool, 0 < K>());
        state.back() += static_cast<T>(s_);
    }

    private:
    template <std::size_t I>
    using index = ThreefryIndex<N, I, Constants>;

    static constexpr std::size_t s_ = N / 4;

    template <std::size_t>
    static void eval(
        std::array<T, K> &, const std::array<T, K + 1> &, std::false_type)
    {
    }

    template <std::size_t I>
    static void eval(std::array<T, K> &state, const std::array<T, K + 1> &par,
        std::true_type)
    {
        static constexpr std::size_t J = index<I>::value;

        std::get<J>(state) += std::get<(s_ + J) % (K + 1)>(par);
        eval<I + 1>(state, par, std::integral_constant<bool, I + 1 < K>());
    }
}; // class ThreefrySubKey

template <typename T, std::size_t K, std::size_t N, typename, bool = (N > 0)>
class ThreefrySBox
{
    public:
    static void eval(std::array<T, K> &) {}
}; // class ThreefrySBox

template <typename T, std::size_t K, std::size_t N, typename Constants>
class ThreefrySBox<T, K, N, Constants, true>
{
    public:
    static void eval(std::array<T, K> &state)
    {
        eval<0>(state, std::integral_constant<bool, 1 < K>());
    }

    private:
    template <std::size_t I>
    using rotate = typename Constants::template rotate<(N - 1) % 8, I>;

    template <std::size_t I>
    using index = ThreefryIndex<N - 1, I, Constants>;

    template <std::size_t>
    static void eval(std::array<T, K> &, std::false_type)
    {
    }

    template <std::size_t I>
    static void eval(std::array<T, K> &state, std::true_type)
    {
        static constexpr int L = rotate<I / 2>::value;
        static constexpr int R = std::numeric_limits<T>::digits - L;
        static constexpr std::size_t I0 = index<I>::value;
        static constexpr std::size_t I1 = index<I + 1>::value;

        T x = std::get<I1>(state);
        std::get<I0>(state) += x;
        std::get<I1>(state) = (x << L) | (x >> R);
        std::get<I1>(state) ^= std::get<I0>(state);
        eval<I + 2>(state, std::integral_constant<bool, I + 3 < K>());
    }
}; // class ThreefrySBox

template <typename T, std::size_t K, std::size_t N, typename, bool = (N > 0)>
class ThreefryPBox
{
    public:
    static void eval(const std::array<T, K> &, std::array<T, K> &) {}
}; // class ThreefryPBox

template <typename T, std::size_t K, std::size_t N, typename Constants>
class ThreefryPBox<T, K, N, Constants, true>
{
    public:
    static void eval(const std::array<T, K> &state, std::array<T, K> &buffer)
    {
        eval<0>(state, buffer, std::integral_constant<bool, 0 < N>());
    }

    private:
    template <std::size_t I>
    using index = ThreefryIndex<N, I, Constants>;

    template <std::size_t>
    static void eval(
        const std::array<T, K> &, std::array<T, K> &, std::false_type)
    {
    }

    template <std::size_t I>
    static void eval(const std::array<T, K> &state, std::array<T, K> &buffer,
        std::true_type)
    {
        std::get<I>(buffer) = std::get<index<I>::value>(state);
        eval<I + 1>(state, buffer, std::integral_constant<bool, I + 1 < K>());
    }
}; // class ThreefryPBox

} // namespace mckl::internal

/// \brief Threefry RNG generator
/// \ingroup Threefry
///
/// \tparam T State type, must be 32- or 64-bit unsigned integers
/// \tparam K State vector length, must be 2 or 4 (for 32- or 64-bit states) or
/// 8 or 16 (64-bit state)
/// \tparam Rounds Number of SP rounds
/// \tparam Constants A trait class that defines algorithm constants, see
/// ThreefryConstants
///
/// \details
/// This generator implement the Threefry algorithm in
/// [Random123](http://www.deshawresearch.com/resources_random123.html),
/// developed John K. Salmon, Mark A. Moraes, Ron O. Dror, and David E. Shaw.
template <typename T, std::size_t K, std::size_t Rounds = MCKL_THREEFRY_ROUNDS,
    typename Constants = ThreefryConstants<T, K>>
class ThreefryGenerator
{
    static_assert(std::is_unsigned<T>::value,
        "**ThreefryGenerator** used with T other than unsigned integer types");

    static_assert(K != 0 && K % 2 == 0,
        "**ThreefryGenerator** used with K other than multiples of 2");

    static_assert(
        Rounds != 0, "**ThreefryGenerator** used with rounds equal to zero");

    public:
    using ctr_type = std::array<T, K>;
    using key_type = std::array<T, K>;

    static constexpr std::size_t size() { return sizeof(T) * K; }

    key_type key() const
    {
        key_type key;
        std::copy_n(par_.begin(), K, key.begin());

        return key;
    }

    void reset(const key_type &key)
    {
        std::copy(key.begin(), key.end(), par_.begin());
        par_.back() = Constants::parity::value;
        for (std::size_t i = 0; i != key.size(); ++i)
            par_.back() ^= par_[i];
    }

    void enc(const ctr_type &ctr, ctr_type &buffer) const
    {
        union {
            std::array<T, K> state;
            ctr_type result;
        } buf;

        buf.result = ctr;
        generate<0>(buf.state, par_, std::true_type());
        permute(buf.state, buffer);
    }

    template <typename ResultType>
    void operator()(ctr_type &ctr,
        std::array<ResultType, size() / sizeof(ResultType)> &buffer) const
    {
        union {
            std::array<T, K> state;
            ctr_type ctr;
            std::array<ResultType, size() / sizeof(ResultType)> result;
        } buf;

        increment(ctr);
        buf.ctr = ctr;
        generate<0>(buf.state, par_, std::true_type());
        permute(buf.state, buffer);
    }

    template <typename ResultType>
    void operator()(ctr_type &ctr, std::size_t n,
        std::array<ResultType, size() / sizeof(ResultType)> *buffer) const
    {
        union {
            std::array<T, K> state;
            ctr_type ctr;
            std::array<ResultType, size() / sizeof(ResultType)> result;
        } buf;

        for (std::size_t i = 0; i != n; ++i) {
            increment(ctr);
            buf.ctr = ctr;
            generate<0>(buf.state, par_, std::true_type());
            permute(buf.state, buffer[i]);
        }
    }

    friend bool operator==(const ThreefryGenerator<T, K, Rounds> &gen1,
        const ThreefryGenerator<T, K, Rounds> &gen2)
    {
        return gen1.par_ == gen2.par_;
    }

    friend bool operator!=(const ThreefryGenerator<T, K, Rounds> &gen1,
        const ThreefryGenerator<T, K, Rounds> &gen2)
    {
        return !(gen1 == gen2);
    }

    template <typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> &operator<<(
        std::basic_ostream<CharT, Traits> &os,
        const ThreefryGenerator<T, K, Rounds> &gen)
    {
        if (!os)
            return os;

        os << gen.par_;

        return os;
    }

    template <typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits> &operator>>(
        std::basic_istream<CharT, Traits> &is,
        ThreefryGenerator<T, K, Rounds> &gen)
    {
        if (!is)
            return is;

        ThreefryGenerator<T, K, Rounds> gen_tmp;
        is >> std::ws >> gen_tmp.par_;

        if (is)
            gen = std::move(gen_tmp);

        return is;
    }

    private:
    template <std::size_t>
    void generate(std::array<T, K> &, const std::array<T, K + 1> &,
        std::false_type) const
    {
    }

    template <std::size_t N>
    void generate(std::array<T, K> &state, const std::array<T, K + 1> &par,
        std::true_type) const
    {
        internal::ThreefrySBox<T, K, N, Constants>::eval(state);
        internal::ThreefrySubKey<T, K, N, Constants>::eval(state, par);
        generate<N + 1>(
            state, par, std::integral_constant<bool, (N < Rounds)>());
    }

    template <typename U, std::size_t L>
    void permute(const std::array<T, K> &state, std::array<U, L> &buffer) const
    {
        permute(state, buffer, std::is_same<T, U>());
    }

    void permute(const std::array<T, K> &state, std::array<T, K> &buffer,
        std::true_type) const
    {
        internal::ThreefryPBox<T, K, Rounds, Constants>::eval(state, buffer);
    }

    template <typename U, std::size_t L>
    void permute(const std::array<T, K> &state, std::array<U, L> &buffer,
        std::false_type) const
    {
        std::array<T, K> tmp;
        permute(state, tmp);
        std::memcpy(buffer.data(), tmp.data(), sizeof(T) * K);
    }

    private:
    std::array<T, K + 1> par_;
}; // class ThreefryGenerator

/// \brief Threefry RNG engine
/// \ingroup Threefry
template <typename ResultType, typename T, std::size_t K,
    std::size_t Rounds = MCKL_THREEFRY_ROUNDS,
    typename Constants = ThreefryConstants<T, K>>
using ThreefryEngine =
    CounterEngine<ResultType, ThreefryGenerator<T, K, Rounds, Constants>>;

/// \brief Threefry2x32 RNG engine
/// \ingroup Threefry
template <typename ResultType>
using Threefry2x32Engine = ThreefryEngine<ResultType, std::uint32_t, 2>;

/// \brief Threefry4x32 RNG engine
/// \ingroup Threefry
template <typename ResultType>
using Threefry4x32Engine = ThreefryEngine<ResultType, std::uint32_t, 4>;

/// \brief Threefry2x64 RNG engine
/// \ingroup Threefry
template <typename ResultType>
using Threefry2x64Engine = ThreefryEngine<ResultType, std::uint64_t, 2>;

/// \brief Threefry4x64 RNG engine
/// \ingroup Threefry
template <typename ResultType>
using Threefry4x64Engine = ThreefryEngine<ResultType, std::uint64_t, 4>;

/// \brief Threefry8x64 RNG engine
/// \ingroup Threefry
template <typename ResultType>
using Threefry8x64Engine = ThreefryEngine<ResultType, std::uint64_t, 8>;

/// \brief Threefry16x64 RNG engine
/// \ingroup Threefry
template <typename ResultType>
using Threefry16x64Engine = ThreefryEngine<ResultType, std::uint64_t, 16>;

/// \brief Threefish-256 RNG engine
template <typename ResultType>
using Threefish256Engine = ThreefryEngine<ResultType, std::uint64_t, 4, 72>;

/// \brief Threefish-512 RNG engine
template <typename ResultType>
using Threefish512Engine = ThreefryEngine<ResultType, std::uint64_t, 8, 72>;

/// \brief Threefish-1024 RNG engine
template <typename ResultType>
using Threefish1024Engine = ThreefryEngine<ResultType, std::uint64_t, 16, 80>;

/// \brief Threefry2x32 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefry2x32 = Threefry2x32Engine<std::uint32_t>;

/// \brief Threefry4x32 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefry4x32 = Threefry4x32Engine<std::uint32_t>;

/// \brief Threefry2x64 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefry2x64 = Threefry2x64Engine<std::uint32_t>;

/// \brief Threefry4x64 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefry4x64 = Threefry4x64Engine<std::uint32_t>;

/// \brief Threefry8x64 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefry8x64 = Threefry8x64Engine<std::uint32_t>;

/// \brief Threefry16x64 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefry16x64 = Threefry16x64Engine<std::uint32_t>;

/// \brief Threefish-256 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefish256 = Threefish256Engine<std::uint32_t>;

/// \brief Threefish-512 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefish512 = Threefish512Engine<std::uint32_t>;

/// \brief Threefish-1024 RNG engine with 32-bit integer output
/// \ingroup Threefry
using Threefish1024 = Threefish1024Engine<std::uint32_t>;

/// \brief Threefry2x32 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefry2x32_64 = Threefry2x32Engine<std::uint64_t>;

/// \brief Threefry4x32 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefry4x32_64 = Threefry4x32Engine<std::uint64_t>;

/// \brief Threefry2x64 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefry2x64_64 = Threefry2x64Engine<std::uint64_t>;

/// \brief Threefry4x64 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefry4x64_64 = Threefry4x64Engine<std::uint64_t>;

/// \brief Threefry8x64 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefry8x64_64 = Threefry8x64Engine<std::uint64_t>;

/// \brief Threefry16x64 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefry16x64_64 = Threefry16x64Engine<std::uint64_t>;

/// \brief Threefish-256 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefish256_64 = Threefish256Engine<std::uint64_t>;

/// \brief Threefish-512 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefish512_64 = Threefish512Engine<std::uint64_t>;

/// \brief Threefish-1024 RNG engine with 64-bit integer output
/// \ingroup Threefry
using Threefish1024_64 = Threefish1024Engine<std::uint64_t>;

} // namespace mckl

#endif // MCKL_RANDOM_THREEFRY_HPP
