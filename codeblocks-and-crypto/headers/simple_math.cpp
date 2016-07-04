#include "simple_math.h"

static boost::multiprecision::cpp_int SimpleMath::GCD(
    boost::multiprecision::cpp_int first, boost::multiprecision::cpp_int second)
{
    if (first == 0 && second == 0)
        return 1;

    if (first == 0)
        return second;

    if (second == 0)
        return first;

    first = boost::multiprecision::abs(first);
    second = boost::multiprecision::abs(second);
    while (second != 0)
    {
        first = first % second;
        std::swap(first, second);
    }
    return first;
}

static boost::multiprecision::cpp_int SimpleMath::powerModule(
    boost::multiprecision::cpp_int base,
    boost::multiprecision::cpp_int exponent,
    boost::multiprecision::cpp_int module)
{
    boost::multiprecision::cpp_int result = 1;
    while (exponent != 0)
        if (exponent % 2 == 1)
        {
            result = (result * base) % module;
            exponent--;
        }
        else
        {
            base = (base * base) % module;
            exponent /= 2;
        }
    return result;
}

static boost::multiprecision::cpp_int SimpleMath::generateE(
    boost::multiprecision::cpp_int phi)
{
    if (GCD(257, phi) == 1)
        return static_cast<boost::multiprecision::cpp_int>(257);

    if (GCD(65537, phi) == 1)
        return static_cast<boost::multiprecision::cpp_int>(65537);

    if (GCD(17, phi) == 1)
        return static_cast<boost::multiprecision::cpp_int>(17);

    boost::random::mt11213b baseGen(clock());
    boost::random::independent_bits_engine<boost::random::mt11213b, 64,
          boost::multiprecision::cpp_int> gen(baseGen);
    boost::random::mt19937 gen2(clock());
    for (size_t i = 0; i < 10000; i++)
    {
        boost::multiprecision::cpp_int n = gen() + 50;
        if (GCD(n, phi) == 1)
            return n;
    }
    boost::random::independent_bits_engine<boost::random::mt11213b, 512,
          boost::multiprecision::cpp_int> gen3(baseGen);
    for (size_t i = 0; i < 100000000; i++)
    {
        boost::multiprecision::cpp_int n = gen3() + 50;
        if (GCD(n, phi) == 1)
            return n;
    }
    return 0;
}

static boost::multiprecision::cpp_int SimpleMath::generateD(
    boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int phi)
{
    return LinearDiophantine(e, phi).solveGCD().first;
}

static boost::multiprecision::cpp_int SimpleMath::generateRandomPrimeNumber()
{
    boost::random::mt11213b baseGen(clock());

    boost::random::independent_bits_engine<boost::random::mt11213b,
          POWER,
          boost::multiprecision::cpp_int> gen(baseGen);
    boost::random::mt19937 gen2(clock());
    for(unsigned i = 0; i < 100000000; i++)
    {
        boost::multiprecision::cpp_int n = gen();
        if(miller_rabin_test(n, 25, gen2))
            return n;
    }
    return static_cast<boost::multiprecision::cpp_int>(0);
}

static unsigned long long int SimpleMath::log256(boost::multiprecision::cpp_int x)
{
    unsigned long long int result = 0;
    boost::multiprecision::cpp_int buffer = 1;
    while (buffer * 256 < x)
    {
        buffer *= 256;
        result++;
    }
    return result;
}

//--------------------------------------------------------------------------
std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int> LinearDiophantine::solveGCD()
{
    boost::multiprecision::cpp_int firstA = A, firstB = 1, firstC = 0;
    boost::multiprecision::cpp_int secondA = B, secondB = 0, secondC = 1;
    boost::multiprecision::cpp_int q;
    while (secondA != 0)
    {
        q = static_cast<boost::multiprecision::cpp_int>(firstA / secondA);
        firstA = firstA % secondA;
        firstB = firstB - q * secondB;
        firstC = firstC - q * secondC;
        std::swap(firstA, secondA);
        std::swap(firstB, secondB);
        std::swap(firstC, secondC);
    }
    q = 0;
    if (firstB < 0)
        q = static_cast<boost::multiprecision::cpp_int>(-firstB / B + 1);

    return std::make_pair(q * B + firstB, -q * A + firstC);
}

std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int> LinearDiophantine::solveFull(
    boost::multiprecision::cpp_int C)
{
    std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int> temp =
        solveGCD();
    boost::multiprecision::cpp_int coefficient = C / SimpleMath::GCD(A, B);
    temp.first *= coefficient;
    temp.second *= coefficient;
    return temp;
}

LinearDiophantine::LinearDiophantine(boost_longint A, boost_longint B) :
    A(A), B(B)
{
}
