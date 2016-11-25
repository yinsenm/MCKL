//============================================================================
// MCKL/include/mckl/mckl.h
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

#ifndef MCKL_MCKL_H
#define MCKL_MCKL_H

#ifdef __cplusplus

#include <cstddef>
#include <cstdint>

extern "C" {

#else // __cplusplus

#include <stddef.h>
#include <stdint.h>

#endif // __cplusplus

// sqrt.asm
void mckl_vd_sqrt(size_t, const double *, double *);

// exp.asm
void mckl_vd_exp(size_t, const double *, double *);
void mckl_vd_exp2(size_t, const double *, double *);
void mckl_vd_expm1(size_t, const double *, double *);

// log.asm
void mckl_vd_log(size_t, const double *, double *);
void mckl_vd_log2(size_t, const double *, double *);
void mckl_vd_log10(size_t, const double *, double *);
void mckl_vd_log1p(size_t, const double *, double *);

// sincos.asm
void mckl_vd_sin(size_t, const double *, double *);
void mckl_vd_cos(size_t, const double *, double *);
void mckl_vd_sincos(size_t, const double *, double *, double *);

// fma.asm
void mckl_fma_vvv_ps(
    size_t, const float *, const float *, const float *, float *);
void mckl_fma_vvs_ps(size_t, const float *, const float *, float, float *);
void mckl_fma_vsv_ps(size_t, const float *, float, const float *, float *);
void mckl_fma_svv_ps(size_t, float, const float *, const float *, float *);
void mckl_fma_ssv_ps(size_t, float, float, const float *, float *);
void mckl_fma_svs_ps(size_t, float, const float *, float, float *);
void mckl_fma_vss_ps(size_t, const float *, float, float, float *);
void mckl_fma_vvv_pd(
    size_t, const double *, const double *, const double *, double *);
void mckl_fma_vvs_pd(size_t, const double *, const double *, double, double *);
void mckl_fma_vsv_pd(size_t, const double *, double, const double *, double *);
void mckl_fma_svv_pd(size_t, double, const double *, const double *, double *);
void mckl_fma_ssv_pd(size_t, double, double, const double *, double *);
void mckl_fma_svs_pd(size_t, double, const double *, double, double *);
void mckl_fma_vss_pd(size_t, const double *, double, double, double *);

// aes_aesni_sse2.asm
void mckl_aes128_aesni_sse2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_aes192_aesni_sse2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_aes256_aesni_sse2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_ars_aesni_sse2_kernel(uint64_t *, size_t, void *, const void *);

// aes_aesni_avx2.asm
void mckl_aes128_aesni_avx2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_aes192_aesni_avx2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_aes256_aesni_avx2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_ars_aesni_avx2_kernel(uint64_t *, size_t, void *, const void *);

// philox_sse2_32.asm
void mckl_philox4x32_sse2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_philox2x32_sse2_kernel(uint64_t *, size_t, void *, const void *);

// philox_avx2_32.asm
void mckl_philox2x32_avx2_kernel(uint64_t *, size_t, void *, const void *);
void mckl_philox4x32_avx2_kernel(uint64_t *, size_t, void *, const void *);

// philox_bmi2_2x64.asm
void mckl_philox2x64_bmi2_kernel(uint64_t *, size_t, void *, const void *);

// philox_bmi2_4x64.asm
void mckl_philox4x64_bmi2_kernel(uint64_t *, size_t, void *, const void *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MCKL_MCKL_H