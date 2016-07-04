#ifndef SIMPLE_MATH_H_INCLUDED
#define SIMPLE_MATH_H_INCLUDED

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/detail/default_ops.hpp>
#include <boost/multiprecision/detail/et_ops.hpp>
#include <boost/multiprecision/detail/number_base.hpp>
#include <boost/multiprecision/detail/number_compare.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/random.hpp>
#include <boost/random/independent_bits.hpp>
#include <boost/random/mersenne_twister.hpp>

#include <stddef.h>
#include <algorithm>
#include <ctime>
#include <utility>

#define POWER 128
class SimpleMath
{
    typedef boost::multiprecision::cpp_int boost_longint;
public:
    static boost_longint GCD(boost_longint A, boost_longint B);
    static boost_longint powerModule(boost_longint base, boost_longint exponent, boost_longint module);
    static boost_longint generateE(boost_longint phi);
    static boost_longint generateD(boost_longint e, boost_longint phi);
    static boost_longint generateRandomPrimeNumber();
    static unsigned long long int log256(boost_longint x);
};
class LinearDiophantine
{
    typedef boost::multiprecision::cpp_int boost_longint;
private:
    boost_longint A;
    boost_longint B;
public:
    LinearDiophantine(boost_longint A, boost_longint B);
    std::pair<boost_longint, boost_longint> solveGCD();
    std::pair<boost_longint, boost_longint> solveFull(boost_longint C);
};
#endif // SIMPLE_MATH_H_INCLUDED
