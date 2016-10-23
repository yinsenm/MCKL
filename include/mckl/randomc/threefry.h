//============================================================================
// MCKL/include/mckl/randomc/threefry.h
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

#ifndef MCKL_RANDOMC_THREEFRY_H
#define MCKL_RANDOMC_THREEFRY_H

#include <mckl/internal/config.h>

#ifndef UINT32_C
#error __STDC_CONSTANT_MACROS not defined before #include<stdint.h>
#endif

/// \brief Threefry2x32 counter type
/// \ingroup ThreefryC
typedef struct {
    uint32_t v[2];
} mckl_threefry2x32_ctr_t;

/// \brief Threefry4x32 counter type
/// \ingroup ThreefryC
typedef struct {
    uint32_t v[4];
} mckl_threefry4x32_ctr_t;

/// \brief Threefry2x64 counter type
/// \ingroup ThreefryC
typedef struct {
    uint64_t v[2];
} mckl_threefry2x64_ctr_t;

/// \brief Threefry4x64 counter type
/// \ingroup ThreefryC
typedef struct {
    uint64_t v[4];
} mckl_threefry4x64_ctr_t;

/// \brief Threefry2x32 key type
/// \ingroup ThreefryC
typedef struct {
    uint32_t v[2];
} mckl_threefry2x32_key_t;

/// \brief Threefry4x32 key type
/// \ingroup ThreefryC
typedef struct {
    uint32_t v[4];
} mckl_threefry4x32_key_t;

/// \brief Threefry2x64 key type
/// \ingroup ThreefryC
typedef struct {
    uint64_t v[2];
} mckl_threefry2x64_key_t;

/// \brief Threefry4x64 key type
/// \ingroup ThreefryC
typedef struct {
    uint64_t v[4];
} mckl_threefry4x64_key_t;

typedef struct {
    uint32_t v[3];
} mckl_threefry2x32_par_t;

typedef struct {
    uint32_t v[5];
} mckl_threefry4x32_par_t;

typedef struct {
    uint64_t v[3];
} mckl_threefry2x64_par_t;

typedef struct {
    uint64_t v[5];
} mckl_threefry4x64_par_t;

/// \brief Threefry2x32 RNG state structure
/// \ingroup ThreefryC
typedef struct {
    mckl_threefry2x32_ctr_t state;
    mckl_threefry2x32_ctr_t ctr;
    mckl_threefry2x32_key_t key;
    uint32_t index;
} mckl_threefry2x32;

/// \brief Threefry4x32 RNG state structure
/// \ingroup ThreefryC
typedef struct {
    mckl_threefry4x32_ctr_t state;
    mckl_threefry4x32_ctr_t ctr;
    mckl_threefry4x32_key_t key;
    uint32_t index;
} mckl_threefry4x32;

/// \brief Threefry2x64 RNG state structure
/// \ingroup ThreefryC
typedef struct {
    mckl_threefry2x64_ctr_t state;
    mckl_threefry2x64_ctr_t ctr;
    mckl_threefry2x64_key_t key;
    uint64_t index;
} mckl_threefry2x64;

/// \brief Threefry4x64 RNG state structure
/// \ingroup ThreefryC
typedef struct {
    mckl_threefry4x64_ctr_t state;
    mckl_threefry4x64_ctr_t ctr;
    mckl_threefry4x64_key_t key;
    uint64_t index;
} mckl_threefry4x64;

static inline void mckl_threefry2x32_inc(mckl_threefry2x32_ctr_t *ctr)
{
    if (++ctr->v[0] != 0)
        return;
    if (++ctr->v[1] != 0)
        return;
}

static inline void mckl_threefry4x32_inc(mckl_threefry4x32_ctr_t *ctr)
{
    if (++ctr->v[0] != 0)
        return;
    if (++ctr->v[1] != 0)
        return;
    if (++ctr->v[2] != 0)
        return;
    if (++ctr->v[3] != 0)
        return;
}

static inline void mckl_threefry2x64_inc(mckl_threefry2x64_ctr_t *ctr)
{
    if (++ctr->v[0] != 0)
        return;
    if (++ctr->v[1] != 0)
        return;
}

static inline void mckl_threefry4x64_inc(mckl_threefry4x64_ctr_t *ctr)
{
    if (++ctr->v[0] != 0)
        return;
    if (++ctr->v[1] != 0)
        return;
    if (++ctr->v[2] != 0)
        return;
    if (++ctr->v[3] != 0)
        return;
}

static inline void mckl_threefry2x32_initpar(
    const mckl_threefry2x32_key_t *key, mckl_threefry2x32_par_t *par)
{
    par->v[0] = key->v[0];
    par->v[1] = key->v[1];

    par->v[2] = UINT32_C(0x1BD11BDA);
    par->v[2] ^= par->v[0];
    par->v[2] ^= par->v[1];
}

static inline void mckl_threefry4x32_initpar(
    const mckl_threefry4x32_key_t *key, mckl_threefry4x32_par_t *par)
{
    par->v[0] = key->v[0];
    par->v[1] = key->v[1];
    par->v[2] = key->v[2];
    par->v[3] = key->v[3];

    par->v[4] = UINT32_C(0x1BD11BDA);
    par->v[4] ^= par->v[0];
    par->v[4] ^= par->v[1];
    par->v[4] ^= par->v[2];
    par->v[4] ^= par->v[3];
}

static inline void mckl_threefry2x64_initpar(
    const mckl_threefry2x64_key_t *key, mckl_threefry2x64_par_t *par)
{
    par->v[0] = key->v[0];
    par->v[1] = key->v[1];

    par->v[2] = UINT64_C(0x1BD11BDAA9FC1A22);
    par->v[2] ^= par->v[0];
    par->v[2] ^= par->v[1];
}

static inline void mckl_threefry4x64_initpar(
    const mckl_threefry4x64_key_t *key, mckl_threefry4x64_par_t *par)
{
    par->v[0] = key->v[0];
    par->v[1] = key->v[1];
    par->v[2] = key->v[2];
    par->v[3] = key->v[3];

    par->v[4] = UINT64_C(0x1BD11BDAA9FC1A22);
    par->v[4] ^= par->v[0];
    par->v[4] ^= par->v[1];
    par->v[4] ^= par->v[2];
    par->v[4] ^= par->v[3];
}

static inline void mckl_threefry2x32_rotate(
    mckl_threefry2x32_ctr_t *state, uint32_t r)
{
    state->v[0] += state->v[1];
    state->v[1] = ((state->v[1]) << r) | ((state->v[1]) >> (32 - r));
    state->v[1] ^= state->v[0];
}

static inline void mckl_threefry4x32_rotate(
    mckl_threefry4x32_ctr_t *state, uint32_t r0, uint32_t r2, int i0, int i2)
{
    state->v[0] += state->v[i0];
    state->v[i0] = ((state->v[i0]) << r0) | ((state->v[i0]) >> (32 - r0));
    state->v[i0] ^= state->v[0];

    state->v[2] += state->v[i2];
    state->v[i2] = ((state->v[i2]) << r2) | ((state->v[i2]) >> (32 - r2));
    state->v[i2] ^= state->v[2];
}

static inline void mckl_threefry2x64_rotate(
    mckl_threefry2x64_ctr_t *state, uint64_t r)
{
    state->v[0] += state->v[1];
    state->v[1] = ((state->v[1]) << r) | ((state->v[1]) >> (64 - r));
    state->v[1] ^= state->v[0];
}

static inline void mckl_threefry4x64_rotate(
    mckl_threefry4x64_ctr_t *state, uint64_t r0, uint64_t r2, int i0, int i2)
{
    state->v[0] += state->v[i0];
    state->v[i0] = ((state->v[i0]) << r0) | ((state->v[i0]) >> (64 - r0));
    state->v[i0] ^= state->v[0];

    state->v[2] += state->v[i2];
    state->v[i2] = ((state->v[i2]) << r2) | ((state->v[i2]) >> (64 - r2));
    state->v[i2] ^= state->v[2];
}

static inline void mckl_threefry2x32_insertkey(mckl_threefry2x32_ctr_t *state,
    const mckl_threefry2x32_par_t *par, uint32_t inc, int i0, int i1)
{
    state->v[0] += par->v[i0];
    state->v[1] += par->v[i1];
    state->v[1] += inc;
}

static inline void mckl_threefry4x32_insertkey(mckl_threefry4x32_ctr_t *state,
    const mckl_threefry4x32_par_t *par, uint32_t inc, int i0, int i1, int i2,
    int i3)
{
    state->v[0] += par->v[i0];
    state->v[1] += par->v[i1];
    state->v[2] += par->v[i2];
    state->v[3] += par->v[i3];
    state->v[3] += inc;
}

static inline void mckl_threefry2x64_insertkey(mckl_threefry2x64_ctr_t *state,
    const mckl_threefry2x64_par_t *par, uint64_t inc, int i0, int i1)
{
    state->v[0] += par->v[i0];
    state->v[1] += par->v[i1];
    state->v[1] += inc;
}

static inline void mckl_threefry4x64_insertkey(mckl_threefry4x64_ctr_t *state,
    const mckl_threefry4x64_par_t *par, uint64_t inc, int i0, int i1, int i2,
    int i3)
{
    state->v[0] += par->v[i0];
    state->v[1] += par->v[i1];
    state->v[2] += par->v[i2];
    state->v[3] += par->v[i3];
    state->v[3] += inc;
}

/// \brief Generate Threefry2x32 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry2x32_gen(const mckl_threefry2x32_ctr_t *ctr,
    const mckl_threefry2x32_key_t *key, mckl_threefry2x32_ctr_t *state)
{
    *state = *ctr;
    mckl_threefry2x32_par_t par;
    mckl_threefry2x32_initpar(key, &par);

    mckl_threefry2x32_insertkey(state, &par, 0, 0, 1); // Round 0
    mckl_threefry2x32_rotate(state, 13);               // Round 1
    mckl_threefry2x32_rotate(state, 15);               // Round 2
    mckl_threefry2x32_rotate(state, 26);               // Round 3
    mckl_threefry2x32_rotate(state, 6);                // Round 4
    mckl_threefry2x32_insertkey(state, &par, 1, 1, 2); // Round 4
    mckl_threefry2x32_rotate(state, 17);               // Round 5
    mckl_threefry2x32_rotate(state, 29);               // Round 6
    mckl_threefry2x32_rotate(state, 16);               // Round 7
    mckl_threefry2x32_rotate(state, 24);               // Round 8
    mckl_threefry2x32_insertkey(state, &par, 2, 2, 0); // Round 8
    mckl_threefry2x32_rotate(state, 13);               // Round 9
    mckl_threefry2x32_rotate(state, 15);               // Round 10
    mckl_threefry2x32_rotate(state, 26);               // Round 11
    mckl_threefry2x32_rotate(state, 6);                // Round 12
    mckl_threefry2x32_insertkey(state, &par, 3, 0, 1); // Round 12
    mckl_threefry2x32_rotate(state, 17);               // Round 13
    mckl_threefry2x32_rotate(state, 29);               // Round 14
    mckl_threefry2x32_rotate(state, 16);               // Round 15
    mckl_threefry2x32_rotate(state, 24);               // Round 16
    mckl_threefry2x32_insertkey(state, &par, 4, 1, 2); // Round 16
    mckl_threefry2x32_rotate(state, 13);               // Round 17
    mckl_threefry2x32_rotate(state, 15);               // Round 18
    mckl_threefry2x32_rotate(state, 26);               // Round 19
    mckl_threefry2x32_rotate(state, 6);                // Round 20
    mckl_threefry2x32_insertkey(state, &par, 5, 2, 0); // Round 20
}

/// \brief Generate Threefry4x32 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry4x32_gen(const mckl_threefry4x32_ctr_t *ctr,
    const mckl_threefry4x32_key_t *key, mckl_threefry4x32_ctr_t *state)
{
    *state = *ctr;
    mckl_threefry4x32_par_t par;
    mckl_threefry4x32_initpar(key, &par);

    mckl_threefry4x32_insertkey(state, &par, 0, 0, 1, 2, 3); // Round 0
    mckl_threefry4x32_rotate(state, 10, 26, 1, 3);           // Round 1
    mckl_threefry4x32_rotate(state, 11, 21, 3, 1);           // Round 2
    mckl_threefry4x32_rotate(state, 13, 27, 1, 3);           // Round 3
    mckl_threefry4x32_rotate(state, 23, 5, 3, 1);            // Round 4
    mckl_threefry4x32_insertkey(state, &par, 1, 1, 2, 3, 4); // Round 4
    mckl_threefry4x32_rotate(state, 6, 20, 1, 3);            // Round 5
    mckl_threefry4x32_rotate(state, 17, 11, 3, 1);           // Round 6
    mckl_threefry4x32_rotate(state, 25, 10, 1, 3);           // Round 7
    mckl_threefry4x32_rotate(state, 18, 20, 3, 1);           // Round 8
    mckl_threefry4x32_insertkey(state, &par, 2, 2, 3, 4, 0); // Round 8
    mckl_threefry4x32_rotate(state, 10, 26, 1, 3);           // Round 9
    mckl_threefry4x32_rotate(state, 11, 21, 3, 1);           // Round 10
    mckl_threefry4x32_rotate(state, 13, 27, 1, 3);           // Round 11
    mckl_threefry4x32_rotate(state, 23, 5, 3, 1);            // Round 12
    mckl_threefry4x32_insertkey(state, &par, 3, 3, 4, 0, 1); // Round 12
    mckl_threefry4x32_rotate(state, 6, 20, 1, 3);            // Round 13
    mckl_threefry4x32_rotate(state, 17, 11, 3, 1);           // Round 14
    mckl_threefry4x32_rotate(state, 25, 10, 1, 3);           // Round 15
    mckl_threefry4x32_rotate(state, 18, 20, 3, 1);           // Round 16
    mckl_threefry4x32_insertkey(state, &par, 4, 4, 0, 1, 2); // Round 16
    mckl_threefry4x32_rotate(state, 10, 26, 1, 3);           // Round 17
    mckl_threefry4x32_rotate(state, 11, 21, 3, 1);           // Round 18
    mckl_threefry4x32_rotate(state, 13, 27, 1, 3);           // Round 19
    mckl_threefry4x32_rotate(state, 23, 5, 3, 1);            // Round 20
    mckl_threefry4x32_insertkey(state, &par, 5, 0, 1, 2, 3); // Round 20
}

/// \brief Generate Threefry2x64 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry2x64_gen(const mckl_threefry2x64_ctr_t *ctr,
    const mckl_threefry2x64_key_t *key, mckl_threefry2x64_ctr_t *state)
{
    *state = *ctr;
    mckl_threefry2x64_par_t par;
    mckl_threefry2x64_initpar(key, &par);

    mckl_threefry2x64_insertkey(state, &par, 0, 0, 1); // Round 0
    mckl_threefry2x64_rotate(state, 16);               // Round 1
    mckl_threefry2x64_rotate(state, 42);               // Round 2
    mckl_threefry2x64_rotate(state, 12);               // Round 3
    mckl_threefry2x64_rotate(state, 31);               // Round 4
    mckl_threefry2x64_insertkey(state, &par, 1, 1, 2); // Round 4
    mckl_threefry2x64_rotate(state, 16);               // Round 5
    mckl_threefry2x64_rotate(state, 32);               // Round 6
    mckl_threefry2x64_rotate(state, 24);               // Round 7
    mckl_threefry2x64_rotate(state, 21);               // Round 8
    mckl_threefry2x64_insertkey(state, &par, 2, 2, 0); // Round 8
    mckl_threefry2x64_rotate(state, 16);               // Round 9
    mckl_threefry2x64_rotate(state, 42);               // Round 10
    mckl_threefry2x64_rotate(state, 12);               // Round 11
    mckl_threefry2x64_rotate(state, 31);               // Round 12
    mckl_threefry2x64_insertkey(state, &par, 3, 0, 1); // Round 12
    mckl_threefry2x64_rotate(state, 16);               // Round 13
    mckl_threefry2x64_rotate(state, 32);               // Round 14
    mckl_threefry2x64_rotate(state, 24);               // Round 15
    mckl_threefry2x64_rotate(state, 21);               // Round 16
    mckl_threefry2x64_insertkey(state, &par, 4, 1, 2); // Round 16
    mckl_threefry2x64_rotate(state, 16);               // Round 17
    mckl_threefry2x64_rotate(state, 42);               // Round 18
    mckl_threefry2x64_rotate(state, 12);               // Round 19
    mckl_threefry2x64_rotate(state, 31);               // Round 20
    mckl_threefry2x64_insertkey(state, &par, 5, 2, 0); // Round 20
}

/// \brief Generate Threefry4x64 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry4x64_gen(const mckl_threefry4x64_ctr_t *ctr,
    const mckl_threefry4x64_key_t *key, mckl_threefry4x64_ctr_t *state)
{
    *state = *ctr;
    mckl_threefry4x64_par_t par;
    mckl_threefry4x64_initpar(key, &par);

    mckl_threefry4x64_insertkey(state, &par, 0, 0, 1, 2, 3); // Round 0
    mckl_threefry4x64_rotate(state, 14, 16, 1, 3);           // Round 1
    mckl_threefry4x64_rotate(state, 52, 57, 3, 1);           // Round 2
    mckl_threefry4x64_rotate(state, 23, 40, 1, 3);           // Round 3
    mckl_threefry4x64_rotate(state, 5, 37, 3, 1);            // Round 4
    mckl_threefry4x64_insertkey(state, &par, 1, 1, 2, 3, 4); // Round 4
    mckl_threefry4x64_rotate(state, 25, 33, 1, 3);           // Round 5
    mckl_threefry4x64_rotate(state, 46, 12, 3, 1);           // Round 6
    mckl_threefry4x64_rotate(state, 58, 22, 1, 3);           // Round 7
    mckl_threefry4x64_rotate(state, 32, 32, 3, 1);           // Round 8
    mckl_threefry4x64_insertkey(state, &par, 2, 2, 3, 4, 0); // Round 8
    mckl_threefry4x64_rotate(state, 14, 16, 1, 3);           // Round 9
    mckl_threefry4x64_rotate(state, 52, 57, 3, 1);           // Round 10
    mckl_threefry4x64_rotate(state, 23, 40, 1, 3);           // Round 11
    mckl_threefry4x64_rotate(state, 5, 37, 3, 1);            // Round 12
    mckl_threefry4x64_insertkey(state, &par, 3, 3, 4, 0, 1); // Round 12
    mckl_threefry4x64_rotate(state, 25, 33, 1, 3);           // Round 13
    mckl_threefry4x64_rotate(state, 46, 12, 3, 1);           // Round 14
    mckl_threefry4x64_rotate(state, 58, 22, 1, 3);           // Round 15
    mckl_threefry4x64_rotate(state, 32, 32, 3, 1);           // Round 16
    mckl_threefry4x64_insertkey(state, &par, 4, 4, 0, 1, 2); // Round 16
    mckl_threefry4x64_rotate(state, 14, 16, 1, 3);           // Round 17
    mckl_threefry4x64_rotate(state, 52, 57, 3, 1);           // Round 18
    mckl_threefry4x64_rotate(state, 23, 40, 1, 3);           // Round 19
    mckl_threefry4x64_rotate(state, 5, 37, 3, 1);            // Round 20
    mckl_threefry4x64_insertkey(state, &par, 5, 0, 1, 2, 3); // Round 20
}

/// \brief Initialize Threefry2x32 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry2x32_init(
    mckl_threefry2x32 *rng, uint32_t seed)
{
    rng->ctr.v[0] = 0;
    rng->ctr.v[1] = 0;
    rng->key.v[0] = seed;
    rng->key.v[1] = 0;
    rng->index = 2;
}

/// \brief Initialize Threefry4x32 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry4x32_init(
    mckl_threefry4x32 *rng, uint32_t seed)
{
    rng->ctr.v[0] = 0;
    rng->ctr.v[1] = 0;
    rng->ctr.v[2] = 0;
    rng->ctr.v[3] = 0;
    rng->key.v[0] = seed;
    rng->key.v[1] = 0;
    rng->key.v[2] = 0;
    rng->key.v[3] = 0;
    rng->index = 4;
}

/// \brief Initialize Threefry2x64 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry2x64_init(
    mckl_threefry2x64 *rng, uint64_t seed)
{
    rng->ctr.v[0] = 0;
    rng->ctr.v[1] = 0;
    rng->key.v[0] = seed;
    rng->key.v[1] = 0;
    rng->index = 2;
}

/// \brief Initialize Threefry4x64 RNG state
/// \ingroup ThreefryC
static inline void mckl_threefry4x64_init(
    mckl_threefry4x64 *rng, uint64_t seed)
{
    rng->ctr.v[0] = 0;
    rng->ctr.v[1] = 0;
    rng->ctr.v[2] = 0;
    rng->ctr.v[3] = 0;
    rng->key.v[0] = seed;
    rng->key.v[1] = 0;
    rng->key.v[2] = 0;
    rng->key.v[3] = 0;
    rng->index = 4;
}

/// \brief Generate random 32-bit integers from Threefry2x32 RNG
/// \ingroup ThreefryC
static inline uint32_t mckl_threefry2x32_rand(mckl_threefry2x32 *rng)
{
    if (rng->index == 2) {
        mckl_threefry2x32_inc(&rng->ctr);
        mckl_threefry2x32_gen(&rng->ctr, &rng->key, &rng->state);
        rng->index = 0;
    }

    return rng->state.v[rng->index++];
}

/// \brief Generate random 32-bit integers from Threefry4x32 RNG
/// \ingroup ThreefryC
static inline uint32_t mckl_threefry4x32_rand(mckl_threefry4x32 *rng)
{
    if (rng->index == 4) {
        mckl_threefry4x32_inc(&rng->ctr);
        mckl_threefry4x32_gen(&rng->ctr, &rng->key, &rng->state);
        rng->index = 0;
    }

    return rng->state.v[rng->index++];
}

/// \brief Generate random 64-bit integers from Threefry2x64 RNG
/// \ingroup ThreefryC
static inline uint64_t mckl_threefry2x64_rand(mckl_threefry2x64 *rng)
{
    if (rng->index == 2) {
        mckl_threefry2x64_inc(&rng->ctr);
        mckl_threefry2x64_gen(&rng->ctr, &rng->key, &rng->state);
        rng->index = 0;
    }

    return rng->state.v[rng->index++];
}

/// \brief Generate random 64-bit integers from Threefry4x64 RNG
/// \ingroup ThreefryC
static inline uint64_t mckl_threefry4x64_rand(mckl_threefry4x64 *rng)
{
    if (rng->index == 4) {
        mckl_threefry4x64_inc(&rng->ctr);
        mckl_threefry4x64_gen(&rng->ctr, &rng->key, &rng->state);
        rng->index = 0;
    }

    return rng->state.v[rng->index++];
}

#endif // MCKL_RANDOMC_THREEFRY_H
