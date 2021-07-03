# RANDU-CRC Random Number Generator

Rucrc is a long running random number generator based on IBM's
RANDU random number algorithm, the CCITT 32-bit CRC algorithm,
and a Bays-Durham shuffle.

The period length of the standard RANDU random number generator
is 2^30 generations.  The period length of a 32-bit CRC is 2^32
generations.  With the Bays-Durham shuffle, the period length of
rucrc approximates 1.2 * 10^61036 generations.

The RANDU random number generator is very weak, and its period
length quite short.  RANDU fails the visual 3D test badly.
However, combined with a 32-bit CRC and the Bays-Durham
shuffle, rucrc passes the dieharder test, as well as taus2
and the Mersenne Twister 19937 do.  It performs as fast as
the Mersenne Twister 19937.

The tests in this repository go beyond the dieharder suite
of tests.  In this repository, there are visual tests, not
present in dieharder.  Additional repositories under this
aquila57 account illustrate how the rucrc generator can
be tested, in comparison to a wide variety of other random
number generators.

The template test in this repository is different from the
template test in dieharder.  The template test used here,
called qmatch, is based on a random pattern.  Each time the
test is run the pattern changes.  The main way to cause the
template test to fail, is to duplicate the input data.  The
template test fails, when the template is repeated in its
entirety.  Of course, if the input data is not random, the
template test also fails the chi square test predictably.
Read more about the template test in TESTING, under qmatch.

Almost all other random number test suites shy away from
running Monte Carlo tests.  Several Monte Carlo tests are
included in this repository.  The results of Mersenne
Twister and ranlxd2 are compared to the results of this
generator.  The results of all three generators are very
close and juggle back and forth in each instance of the test.

# Rucrc generator subroutines.

The following subroutines are kept in a static subroutine
library, called librucrc.a.

* rucrcinit - Initialize the rucrc random number generator.
This routine is based on date and time in milliseconds.  The
generator output is unpredictable.  See rucrcstrt for
initialization with one seed parameter.

* rucrcstrt - Initialize the rucrc random number generator with
one seed parameter.  The generator output is repeatable, and
is used for regression testing.  See rucrcinit for initialization
based on date and time in milliseconds.

* rucrc - Generate one 32 bit random unsigned integer with a
uniform distribution.  All other formats of output are based
on this subroutine.

* rucrcint - Generate a positive random integer between zero
and a limit minus one.

* rucrcpwr - Generate from 1 to 32 random bits. 

* rucrcbit - Generate one random bit.

* rucrcunif - Generate a random fraction from zero to one.
This rountine has 32 bit precision.  See rucrcfrac() for
a routine with 53 bit precision.  This routine is faster
than rucrcfrac().

* rucrcfrac - Generate a random fraction from zero to one.
This rountine has 53 bit precision.  See rucrcunif() for
a faster routine with 32 bit precision.

* rucrcdspl - Display the state of the rucrc random number
generator.

* rucrcabt - Write a summary of the copyright and license to
stderr.

* rucrcprm - Calculate 3 prime numbers at random for regression
testing.  One of these prime numbers may be used as the parameter
for rucrcstrt.

# Platforms.

This repository may be compiled under Linux.  Examples are
given for the Debian distribution of Linux.  Download the
zip file for the repository into your private source directory.
Unzip the zip file using unzip.  Change to the master directory.
Chmod the install and de-install scripts.  Run inst.sh to compile.

You may also compile this repository under mingw in Windows.
Instead of initializing rucrc with rucrcinit.c, it is easier
to use rucrcstrt.c with one initial seeds as a parameter.  You
may initialize that seed with date and time, to make your
testing less predictable.  The XWindows programs in this
repository will not run directly under Microsoft Windows.

See other repositories under this aquila57 account to follow
more examples of how to write applications using the rucrc
random number generator.

Read INSTALL, TESTING for more information.
