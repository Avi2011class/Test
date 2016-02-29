#include <iostream>
#include <iomanip>
#include <ctime>

#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <fstream>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#include "simple_math.h"

#define KEY_PAIR std::pair<RSAKey2048, RSAKey2048>

enum key_mode {OPEN_KEY, CLOSED_KEY, NULL_KEY, INCORRECT_KEY};

class RSAKey2048
{
    private:
        boost::multiprecision::cpp_int  exponent;
        boost::multiprecision::cpp_int  module;
        unsigned long long int  max_byte_length;
    public:
        RSAKey2048(boost::multiprecision::cpp_int exponent, boost::multiprecision::cpp_int module) :
            exponent(exponent), module(module), max_byte_length(simple_math::log256(module)) {}
        RSAKey2048(std::string file_name)
        {
            try
            {
                std::fstream input_file;
                input_file.open(file_name.c_str());
                input_file >> exponent >> module;
                max_byte_length = simple_math::log256(module);
            }
            catch(std::exception e)
            {
                std::cout << "Ошибка открытия файла или считывания ключа\n" << std::endl;
                exit(0);
            }
        }
        friend std::ostream& operator << (std::ostream& output, RSAKey2048& Key)
        {
            try
            {
                output << Key.exponent << " " << Key.module;
                return output;
            }
            catch(std::exception e)
            {
                std::cout << "Ошибка считавания ключа\n" << std::endl;
                exit(0);
            }

        }
        boost::multiprecision::cpp_int get_exponent()
        {
            return exponent;
        }
        boost::multiprecision::cpp_int get_module()
        {
            return module;
        }
        unsigned long long int get_max_byte_length()
        {
            return max_byte_length;
        }

};

namespace key_functions
{
    /* Генерация ключей */
    std::pair<RSAKey2048, RSAKey2048> create_keys()
    {
        boost::multiprecision::cpp_int P = simple_math::generate_random_prime_number();
        boost::multiprecision::cpp_int Q = simple_math::generate_random_prime_number();
        boost::multiprecision::cpp_int N = P * Q, Phi = (P - 1) * (Q - 1);
        boost::multiprecision::cpp_int e = simple_math::generate_e(Phi);
        boost::multiprecision::cpp_int d = simple_math::generate_d(e, Phi);

        return std::make_pair(RSAKey2048(e, N), RSAKey2048(d, N));
    }
    /* Проверка корректности пары ключей */
    inline bool key_pair_OK(KEY_PAIR key_pair)
    {
        srand(time(0));
        std::cout << "Start test key's correct:" << std::endl;
        for(size_t i = 0; i < 10; i++)
        {
            boost::multiprecision::cpp_int
                N = rand();
            std::cout << "   " << i + 1 << ". " << N << std::endl;
            boost::multiprecision::cpp_int
                N_coded = simple_math::power_module(N, key_pair.first.get_exponent(), key_pair.first.get_module());
            boost::multiprecision::cpp_int
                N_decoded = simple_math::power_module(N_coded, key_pair.second.get_exponent(), key_pair.second.get_module());
            if(N_decoded != N)
                return false;
        }
        if(key_pair.first.get_module() != key_pair.second.get_module())
            return false;
        if(key_pair.first.get_max_byte_length() == 0 || key_pair.second.get_max_byte_length() == 0)
            return false;
        return true;
    }

}
