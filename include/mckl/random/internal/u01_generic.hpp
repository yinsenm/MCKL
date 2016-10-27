//============================================================================
// MCKL/include/mckl/random/internal/u01_generic.hpp
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

#ifndef MCKL_RANDOM_INTERNAL_U01_GENERIC_HPP
#define MCKL_RANDOM_INTERNAL_U01_GENERIC_HPP

#include <mckl/random/internal/common.hpp>

namespace mckl
{

namespace internal
{

template <int P,
    int Q = (std::numeric_limits<unsigned long long>::digits <
                        std::numeric_limits<long double>::digits ?
                    std::numeric_limits<unsigned long long>::digits :
                    std::numeric_limits<long double>::digits) -
        1,
    bool = (Q < P)>
class U01Pow2L
{
    public:
    static constexpr long double value =
        static_cast<long double>(1ULL << Q) * U01Pow2L<P - Q>::value;
}; // class U01Pow2L

template <int P, int Q>
class U01Pow2L<P, Q, false>
{
    public:
    static constexpr long double value = static_cast<long double>(1ULL << P);
}; // class U01Pow2L

template <int P>
class U01Pow2InvL
{
    public:
    static constexpr long double value = 1.0L / U01Pow2L<P>::value;
}; // class U01Pow2InvL

template <typename RealType, int P>
class U01Pow2
{
    public:
    static constexpr RealType value =
        static_cast<RealType>(U01Pow2L<P>::value);
}; // class U01Pow2

template <typename RealType, int P>
class U01Pow2Inv
{
    public:
    static constexpr RealType value =
        static_cast<RealType>(U01Pow2InvL<P>::value);
}; // class U01Pow2Inv

template <int W, typename UIntType>
using U01UIntLeastType = typename std::conditional<W <= 32, std::uint32_t,
    typename std::conditional<W <= 64, std::uint64_t, UIntType>::type>::type;

template <typename UIntType, typename, typename, typename,
    int = std::numeric_limits<UIntType>::digits>
class U01GenericImpl;

template <typename UIntType, typename RealType, int W>
class U01GenericImpl<UIntType, RealType, Closed, Closed, W>
{
    public:
    static RealType eval(UIntType u)
    {
        constexpr int M = std::numeric_limits<RealType>::digits;
        constexpr int P = W - 1 < M ? W - 1 : M;
        constexpr int V = P + 1;
        constexpr int L = V < W ? 1 : 0;
        constexpr int R = V < W ? W - 1 - V : 0;

        using UIntLeastType = U01UIntLeastType<W - R, UIntType>;

        return trans(static_cast<UIntLeastType>((u << L) >> (R + L)),
                   std::integral_constant<bool, (V < W)>()) *
            U01Pow2Inv<RealType, P + 1>::value;
    }

    static void eval(std::size_t n, const UIntType *u, RealType *r)
    {
        for (std::size_t i = 0; i != n; ++i)
            r[i] = eval(u[i]);
    }

    private:
    template <typename UIntLeastType>
    static RealType trans(UIntLeastType u, std::true_type)
    {
        return static_cast<RealType>((u & 1) + u);
    }

    template <typename UIntLeastType>
    static RealType trans(UIntLeastType u, std::false_type)
    {
        return static_cast<RealType>(u & 1) + static_cast<RealType>(u);
    }
}; // class U01GenericImpl

template <typename UIntType, typename RealType, int W>
class U01GenericImpl<UIntType, RealType, Closed, Open, W>
{

    public:
    static RealType eval(UIntType u)
    {
        constexpr int M = std::numeric_limits<RealType>::digits;
        constexpr int P = W < M ? W : M;
        constexpr int R = W - P;

        using UIntLeastType = U01UIntLeastType<W - R, UIntType>;

        return static_cast<RealType>(static_cast<UIntLeastType>(u >> R)) *
            U01Pow2Inv<RealType, P>::value;
    }

    static void eval(std::size_t n, const UIntType *u, RealType *r)
    {
        for (std::size_t i = 0; i != n; ++i)
            r[i] = eval(u[i]);
    }
}; // class U01GenericImpl

template <typename UIntType, typename RealType, int W>
class U01GenericImpl<UIntType, RealType, Open, Closed, W>
{

    public:
    static RealType eval(UIntType u)
    {
        constexpr int M = std::numeric_limits<RealType>::digits;
        constexpr int P = W < M ? W : M;
        constexpr int R = W - P;

        using UIntLeastType = U01UIntLeastType<W - R, UIntType>;

        return static_cast<RealType>(static_cast<UIntLeastType>(u >> R)) *
            U01Pow2Inv<RealType, P>::value +
            U01Pow2Inv<RealType, P>::value;
    }

    static void eval(std::size_t n, const UIntType *u, RealType *r)
    {
        for (std::size_t i = 0; i != n; ++i)
            r[i] = eval(u[i]);
    }
}; // class U01GenericImpl

template <typename UIntType, typename RealType, int W>
class U01GenericImpl<UIntType, RealType, Open, Open, W>
{
    public:
    static RealType eval(UIntType u)
    {
        constexpr int M = std::numeric_limits<RealType>::digits;
        constexpr int P = W + 1 < M ? W + 1 : M;
        constexpr int R = W + 1 - P;

        using UIntLeastType = U01UIntLeastType<W - R, UIntType>;

        return static_cast<RealType>(static_cast<UIntLeastType>(u >> R)) *
            U01Pow2Inv<RealType, P - 1>::value +
            U01Pow2Inv<RealType, P>::value;
    }

    static void eval(std::size_t n, const UIntType *u, RealType *r)
    {
        for (std::size_t i = 0; i != n; ++i)
            r[i] = eval(u[i]);
    }
}; // class U01GenericImpl

// #if MCKL_HAS_LITTLE_ENDIAN
//
// template <typename UIntType>
// class U01GenericImpl<UIntType, double, Closed, Open, 32>
// {
//     public:
//     static double eval(UIntType, u)
//     {
//     }
// }; // class U01GenericImpl
//
// #elif MCKL_HAS_BIG_ENDIAN
//
// #endif // MCKL_HAS_LITTLE_ENDIAN

} // namespace mckl::internal

} // namespace mckl;

#endif // MCKL_RANDOM_INTERNAL_U01_GENERIC_HPP
