#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED
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
#include <omp.h>

#include "simple_math.h"

#define KEY_PAIR std::pair<RSAKey2048, RSAKey2048>
#define DEFAULT_KEY RSAKey2048(1814012943, 3264797647)
/*
Класс, реализущий ключ RSA 2048 bit
 */
class RSAKey2048
{
    private:
        boost::multiprecision::cpp_int  exponent;
        boost::multiprecision::cpp_int  module;
        unsigned long long int  max_byte_length;
    public:
        /* Дефолтовый двухсторонний ключ */
        RSAKey2048(): exponent(1814012943), module(3264797647), max_byte_length(simple_math::log256(3264797647)) {};
        /* Конструктор, принимающий три числа и строящий ключ по ним */
        RSAKey2048(boost::multiprecision::cpp_int exponent, boost::multiprecision::cpp_int module) :
            exponent(exponent), module(module), max_byte_length(simple_math::log256(module)) {}
        RSAKey2048(boost::multiprecision::cpp_int exponent, boost::multiprecision::cpp_int module, boost::multiprecision::cpp_int max_byte_length) : exponent(exponent), module(module), max_byte_length(max_byte_length) {};
        /* Конструктор, считывающий ключ из файла */
        RSAKey2048(std::string file_name)
        {
            try
            {
                std::fstream input_stream;
                input_stream.open(file_name.c_str());
                input_stream >> exponent >> module;
                max_byte_length = simple_math::log256(module);
            }
            catch(std::exception e)
            {
                std::cout << "Ошибка открытия файла или считывания ключа\n" << std::endl;
            }
        }
        /* Оператор вывода в поток */
        friend std::ostream& operator << (std::ostream& output, RSAKey2048& Key)
        {
            try
            {
                output << Key.exponent << " " << Key.module;
                return output;
            }
            catch(std::exception e)
            {
                std::cout << "Ошибка считывания ключа\n" << std::endl;
                exit(0);
            }
        }
        /* Метод вывода в файл*/
        void print_to_file(std::string filename)
        {
            std::fstream output_stream;
            output_stream.open(filename.c_str(), std::ios::out);
            output_stream << exponent << " " << module;
            output_stream.close();
        }
        /* Методы, позволяющие получить переменные private */
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
        bool is_default()
        {
            return (module == 3264797647) && (exponent == 1814012943);
        }
};

/* ПРостранство имен, содержащее основные действия над ключами */
namespace key_functions
{
    /* Генерация ключей */
    std::pair<RSAKey2048, RSAKey2048> create_keys()
    {
        boost::multiprecision::cpp_int P, Q;

        #pragma omp parallel sections
        {
            #pragma omp section
            P = simple_math::generate_random_prime_number();
            #pragma omp section
            Q = simple_math::generate_random_prime_number();
        }
        boost::multiprecision::cpp_int N = P * Q, Phi = (P - 1) * (Q - 1);
        boost::multiprecision::cpp_int e = simple_math::generate_e(Phi);
        boost::multiprecision::cpp_int d = simple_math::generate_d(e, Phi);

        return std::make_pair(RSAKey2048(e, N), RSAKey2048(d, N));
    }
    /* Проверка корректности пары ключей */
    inline bool key_pair_OK(KEY_PAIR key_pair)
    {
        srand(time(0));
        bool result = true;
        #pragma omp parallel for
        for(size_t i = 0; i < 20; i++)
        {
            boost::multiprecision::cpp_int
            N = rand();
            boost::multiprecision::cpp_int
            N_coded = simple_math::power_module(N, key_pair.first.get_exponent(), key_pair.first.get_module());
            boost::multiprecision::cpp_int
            N_decoded = simple_math::power_module(N_coded, key_pair.second.get_exponent(), key_pair.second.get_module());
            if(N_decoded != N)
                result = false;
        }
        if(key_pair.first.get_module() != key_pair.second.get_module())
            result = false;
        if(key_pair.first.get_max_byte_length() == 0 || key_pair.second.get_max_byte_length() == 0)
            result = false;
        return result;
    }

}



#endif // KEYS_H_INCLUDED
