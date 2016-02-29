#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#define POWER 2048

namespace simple_math
{
/* Наибольший общий делитель двух длинных чисел */
    inline boost::multiprecision::cpp_int
    GCD(boost::multiprecision::cpp_int __1, boost::multiprecision::cpp_int __2)
    {
        if(__1 == 0 && __2 == 0) return 1;
        if(__1 == 0) return __2;
        if(__2 == 0) return __1;
        __1 = boost::multiprecision::abs(__1);
        __2 = boost::multiprecision::abs(__2);
        while(__2 != 0)
        {
            __1 = __1 % __2;
            std::swap(__1, __2);
        }
        return __1;
    }

    /* Быстрое возведение в степень по модулю */
    inline boost::multiprecision::cpp_int
    power_module(boost::multiprecision::cpp_int base,
                 boost::multiprecision::cpp_int exponent,
                 boost::multiprecision::cpp_int module)
    {
        boost::multiprecision::cpp_int result = 1;
        while(exponent != 0)
            if(exponent % 2 == 1)
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

    /* Генерация длинного простого числа */
    inline boost::multiprecision::cpp_int generate_random_prime_number()
    {
        boost::random::mt11213b base_gen(clock());
        boost::random::independent_bits_engine<boost::random::mt11213b,
              POWER,
              boost::multiprecision::cpp_int> gen(base_gen);
        boost::random::mt19937 gen2(clock());

        for(unsigned i = 0; i < 100000000; i++)
        {
            boost::multiprecision::cpp_int n = gen();
            if(miller_rabin_test(n, 25, gen2))
                return n;
        }
        return static_cast<boost::multiprecision::cpp_int>(0);
    }

    /* Поиск частного решения линейного диофантового уравнение
    ax + by = GCD(x, y), причем a - наименьшее положиельное */
    inline std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>
    linear_diophantine_equations(boost::multiprecision::cpp_int x, boost::multiprecision::cpp_int y)
    {
        boost::multiprecision::cpp_int first_a = x, first_b = 1, first_c = 0;
        boost::multiprecision::cpp_int second_a = y, second_b = 0, second_c = 1;

        boost::multiprecision::cpp_int q;
        while(second_a != 0)
        {
            q = static_cast<boost::multiprecision::cpp_int> (first_a / second_a);
            first_a = first_a % second_a;
            first_b = first_b - q * second_b;
            first_c = first_c - q * second_c;
            std::swap(first_a, second_a);
            std::swap(first_b, second_b);
            std::swap(first_c, second_c);
        }
        q = 0;
        if(first_b < 0)
            q = static_cast<boost::multiprecision::cpp_int> (- first_b / y + 1);
        return std::make_pair(q * y + first_b, -q * x + first_c);
    }

    /* Генерация экспоненты открытого ключа */
    inline boost::multiprecision::cpp_int generate_e(boost::multiprecision::cpp_int phi)
    {
        if(GCD(257, phi) == 1)
            return static_cast<boost::multiprecision::cpp_int>(257);
        if(GCD(65537, phi) == 1)
            return static_cast<boost::multiprecision::cpp_int>(65537);
        if(GCD(17, phi) == 1)
            return static_cast<boost::multiprecision::cpp_int>(17);

        boost::random::mt11213b base_gen(clock());
        boost::random::independent_bits_engine<boost::random::mt11213b,
              64,
              boost::multiprecision::cpp_int> gen(base_gen);
        boost::random::mt19937 gen2(clock());

        for(size_t i = 0; i < 10000; i++)
        {
            boost::multiprecision::cpp_int n = gen() + 50;
            if(GCD(n, phi) == 1)
                return n;
        }

        boost::random::independent_bits_engine<boost::random::mt11213b,
              512,
              boost::multiprecision::cpp_int> gen3(base_gen);

        for(size_t i = 0; i < 100000000; i++)
        {
            boost::multiprecision::cpp_int n = gen3() + 50;
            if(GCD(n, phi) == 1)
                return n;
        }
        return 0;
    }

    /* Генерация экспоненты закрытого ключа */
    inline boost::multiprecision::cpp_int
    generate_d(boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int phi)
    {
        return linear_diophantine_equations(e, phi).first;
    }
    /*Извлечение целой части логарифма по модулю 256*/
    inline unsigned long long int log256(boost::multiprecision::cpp_int __1)
    {
        unsigned long long int result = 0;
        boost::multiprecision::cpp_int buffer = 1;
        while(buffer * 256 < __1)
        {
            buffer *= 256;
            result ++;
        }
        return result;
    }
}
