.. ============================================================================
..  MCKL/docs/random_testu01.rst
.. ----------------------------------------------------------------------------
..  MCKL: Monte Carlo Kernel Library
.. ----------------------------------------------------------------------------
..  Copyright (c) 2013-2018, Yan Zhou
..  All rights reserved.

..  Redistribution and use in source and binary forms, with or without
..  modification, are permitted provided that the following conditions are met:

..    Redistributions of source code must retain the above copyright notice,
..    this list of conditions and the following disclaimer.

..    Redistributions in binary form must reproduce the above copyright notice,
..    this list of conditions and the following disclaimer in the documentation
..    and/or other materials provided with the distribution.

..  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
..  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
..  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
..  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
..  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
..  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
..  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
..  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
..  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
..  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
..  POSSIBILITY OF SUCH DAMAGE.
.. ============================================================================

***************
TestU01 Results
***************

All RNGs implemented in MCKL and those in the standard library are tested with
the `TestU01 library <http://simul.iro.umontreal.ca/testu01/tu01.html>`_ test
batteries (“SmallCrush”, “Crush” and “BigCrush”). Each battery performs tests
on a sequence of real numbers to detect if it is distinguishable from the
uniform distribution on :math:`[0, 1)`. For each RNG, six types of sequences
are tested, each of them generated by the following classes,

.. code-block:: cpp

    std::uniform_real_distribution<double>;
    ::mckl::U01Distribution<double>; // Alias to U01CanonicalDistribution<double>
    ::mckl::U01CCDistribution<double>;
    ::mckl::U01CODistribution<double>;
    ::mckl::U01OCDistribution<double>;
    ::mckl::U01OODistribution<double>;

They are labeled as “STD”, “U01”, “U01CC”, “U01CO”, “U01OC” and “U01OO”,
respectively, in the tables below. See :ref:`sec-Standard Uniform Distribution`
for details of the last six distributions. The configuration macro
``MCKL_U01_USE_FIXED_POINT`` is set to false. Therefore STD and U01 both uses
the same algorithm, though not identical in their implementations. The former
use ``std::generate_canonical``. The configuration macro
``MCKL_U01_USE_64BITS_DOUBLE`` is also set to false. Thus the four fixed point
distributions only uses 32-bit random random integers unless the RNG itself
generates 64-bit integers. All RNGs in MCKL come with both 32- and 64-bit
versions. The test results of the 32-bit version when this macro is set to true
shall be the same as their 64-bit counter-parts.

The sequence of random numbers fed into the TestU01 batteries are constructed
as the following. For each RNG, eight instances of it is created with random
seeds. Let the sequence of random numbers produced by them be :math:`U_{i,j}`,
:math:`i = 0,\dots,7` and :math:`j\ge0`. The :math:`k`-th random number fed
into the batteries is :math:`U_{p(k), q(k)}`, where,

.. math::

    p(k) = \lfloor k / 1024 \rfloor \bmod 8, \qquad q(k) = k \bmod 1024.

In words, the first 1024 random numbers come from the first RNG. Then another
1024 random numbers come from the second RNG, and so on. Once all eight RNGs
are used, we start with the first one again. This is to mimic the usage of RNGs
in a parallel environment with eight threads, each thread uses one RNG.

For each test within the batteries, one or more *p*-values are produced. A
*p*-value outside the range :math:`(10^{-6}, 1 - 10^{-6})` is considered a
failure. Otherwise, a *p*-value outside the range :math:`(10^{-3}, 1 -
10^{-3})` is considered suspicious. For each test, if any one of the *p*-values
produced is a failure, we consider the RNG to fail the test. On the other hand,
if the *p*-values produced are suspicious, the particular test is repeated two
more times, with new random seeds for each RNG instances. If the total number
of suspicious *p*-values for the test is more than one, either from one run of
a test that produces multiple *p*-values, or repeated runs of a test that
produces a single *p*-value, the RNG is considered to fail the test as well.

It is best to perform each test multiple times to increase the power of the
test. A *p*-value within the range :math:`(10^{-3}, 1 - 10^{-3})` actually
tells very little about the quality of the RNG. However, the most strident
battery, BigCrush, takes many hours to finish for any RNG. And there are 60 of
them to be tested, each with six distributions. We choose to only perform
repeated tests for those with suspicious *p*-values. The tables below lists the
number of failed tests for each RNG. Those that do not fail any test are
omitted.

Note that, only the STD, U01 and U01CO methods produce random numbers within
the interval :math:`[0, 1)`. Other fixed point distributions might fail a few
tests due to the fact they are supposed to produce random numbers from other
distributions. For example, for the U01OC and U01CC methods, if ever their
upper bond, :math:`1`, is produced in the sequence, some tests are certain to
fail. However, since the chance of it being produced shall be roughly
:math:`2^{-32}` for 32-bit RNGs and :math:`2^{-53}` for 64-bit RNGs, if an RNG
fails many tests in a battery, it is unlikely to be due to this reason. If an
RNG fails considerably more tests with the fixed point distribution than with
the STD and U01 methods, then it is more likely to be due to the weakness of
its randomness at the bit level. Recall that, the MCKL distributions,
especially the fixed point ones, relies on the bit level randomness of the
integers produced by the RNG. In particular, ``std::ranlux24_base`` and
``std::ranlux48_base`` are ill-suited to be used with any of the distributions
in MCKL.

Last but not least, the test method used here may uncover defects in RNGs
when multiple instances are used concurrently, such as inter-stream
correlations. On the other hand, it may also hide some defects of long streams
from a particular RNG. For example, The linear and general feedback shift
register generators (such as ``std::mt19937``) are known to fail linear
dependencies tests. However, as the stream fed into the batteries is actually
mixture of multiple RNGs initialized with random seeds, these tests may or
may not fail, depending on the seeds.

.. _tab-TestU01 SmallCrush results (single stream):

.. csv-table:: TestU01 SmallCrush results (single stream)
    :delim: &
    :header: RNG, STD, U01, U01CC, U01CO, U01OC, U01OO

    ``std::minstd_rand0``  & 2 & 3 & 3 & 3 & 3 & 3
    ``std::minstd_rand``   & 2 & 3 & 3 & 3 & 3 & 3
    ``std::ranlux24_base`` & 0 & 0 & 3 & 3 & 3 & 3
    ``std::ranlux48_base`` & 0 & 0 & 3 & 3 & 3 & 3
    ``MKL_MCG59``          & 1 & 1 & 1 & 1 & 1 & 1
    ``MKL_MCG59_64``       & 1 & 1 & 1 & 1 & 1 & 1

.. _tab-TestU01 SmallCrush results (eight streams):

.. csv-table:: TestU01 SmallCrush results (eight streams)
    :delim: &
    :header: RNG, STD, U01, U01CC, U01CO, U01OC, U01OO

    ``std::minstd_rand0``  & 2 & 3 & 3 & 3 & 3 & 3
    ``std::minstd_rand``   & 2 & 3 & 3 & 3 & 3 & 3
    ``std::ranlux24_base`` & 0 & 0 & 3 & 2 & 5 & 3
    ``std::ranlux48_base`` & 0 & 0 & 3 & 3 & 3 & 3
    ``MKL_MCG59``          & 0 & 1 & 0 & 0 & 0 & 0
    ``MKL_MCG59_64``       & 0 & 0 & 1 & 0 & 0 & 1

.. _tab-TestU01 Crush results (single stream):

.. csv-table:: TestU01 Crush results (single stream)
    :delim: &
    :header: RNG, STD, U01, U01CC, U01CO, U01OC, U01OO

    ``std::mt19937``       & 2  & 2  & 1  & 2  & 1  & 2
    ``std::mt19937_64``    & 2  & 2  & 2  & 2  & 2  & 2
    ``std::minstd_rand0``  & 34 & 34 & 33 & 35 & 33 & 34
    ``std::minstd_rand``   & 36 & 31 & 32 & 31 & 31 & 34
    ``std::ranlux24_base`` & 0  & 12 & 28 & 28 & 28 & 28
    ``std::ranlux48_base`` & 12 & 12 & 28 & 28 & 29 & 28
    ``std::knuth_b``       & 6  & 0  & 0  & 0  & 1  & 0
    ``MKL_MCG59``          & 14 & 11 & 11 & 12 & 14 & 12
    ``MKL_MCG59_64``       & 14 & 11 & 15 & 14 & 16 & 14
    ``MKL_MT19937``        & 2  & 2  & 1  & 2  & 1  & 2
    ``MKL_MT19937_64``     & 2  & 2  & 2  & 2  & 3  & 2
    ``MKL_MT2203``         & 2  & 2  & 1  & 2  & 1  & 2
    ``MKL_MT2203_64``      & 2  & 2  & 2  & 2  & 2  & 2
    ``MKL_SFMT19937``      & 2  & 0  & 0  & 0  & 0  & 0
    ``MKL_SFMT19937_64``   & 2  & 0  & 2  & 2  & 2  & 2

.. _tab-TestU01 Crush results (eight streams):

.. csv-table:: TestU01 Crush results (eight streams)
    :delim: &
    :header: RNG, STD, U01, U01CC, U01CO, U01OC, U01OO

    ``std::minstd_rand0``  & 33 & 33 & 31 & 30 & 32 & 30
    ``std::minstd_rand``   & 29 & 29 & 30 & 29 & 37 & 29
    ``std::ranlux24_base`` & 0  & 12 & 28 & 28 & 29 & 28
    ``std::ranlux48_base`` & 12 & 12 & 29 & 28 & 29 & 28
    ``std::knuth_b``       & 5  & 0  & 0  & 0  & 0  & 0
    ``MKL_MCG59``          & 14 & 10 & 10 & 9  & 11 & 10
    ``MKL_MCG59_64``       & 14 & 10 & 15 & 14 & 12 & 12

.. _tab-TestU01 BigCrush results (single stream):

.. csv-table:: TestU01 BigCrush results (single stream)
    :delim: &
    :header: RNG, STD, U01, U01CC, U01CO, U01OC, U01OO

    ``std::mt19937``       & 2  & 2  & 1  & 2  & 1  & 2
    ``std::mt19937_64``    & 2  & 2  & 2  & 2  & 2  & 2
    ``std::minstd_rand0``  & 53 & 56 & 55 & 55 & 51 & 54
    ``std::minstd_rand``   & 54 & 58 & 57 & 57 & 61 & 55
    ``std::ranlux24_base`` & 0  & 27 & 41 & 40 & 41 & 40
    ``std::ranlux48_base`` & 27 & 24 & 41 & 40 & 41 & 40
    ``knuth_b``            & 7  & 0  & 3  & 2  & 2  & 2
    ``MKL_MCG59``          & 23 & 22 & 23 & 22 & 26 & 23
    ``MKL_MCG59_64``       & 23 & 22 & 26 & 24 & 24 & 23
    ``MKL_MT19937``        & 2  & 2  & 1  & 2  & 1  & 2
    ``MKL_MT19937_64``     & 2  & 2  & 2  & 2  & 2  & 2
    ``MKL_MT2203``         & 4  & 4  & 2  & 4  & 2  & 4
    ``MKL_MT2203_64``      & 4  & 4  & 4  & 4  & 5  & 4
    ``MKL_SFMT19937``      & 2  & 2  & 1  & 2  & 1  & 2
    ``MKL_SFMT19937_64``   & 2  & 2  & 2  & 2  & 2  & 2

.. _tab-TestU01 BigCrush results (eight streams):

.. csv-table:: TestU01 BigCrush results (eight streams)
    :delim: &
    :header: RNG, STD, U01, U01CC, U01CO, U01OC, U01OO

    ``std::minstd_rand0``  & 39 & 44 & 39 & 39 & 38 & 39
    ``std::minstd_rand``   & 43 & 43 & 43 & 41 & 46 & 43
    ``std::ranlux24_base`` & 0  & 28 & 40 & 40 & 41 & 40
    ``std::ranlux48_base`` & 27 & 26 & 41 & 40 & 41 & 40
    ``MKL_MCG59``          & 22 & 15 & 17 & 17 & 14 & 15
    ``MKL_MCG59_64``       & 22 & 15 & 26 & 22 & 21 & 22
    ``MKL_MT2203``         & 2  & 2  & 1  & 2  & 1  & 2
    ``MKL_MT2203_64``      & 2  & 2  & 2  & 2  & 2  & 2
