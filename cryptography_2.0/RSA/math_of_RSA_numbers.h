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
#define KEY_PAIR std::pair<RSAKey2048, RSAKey2048>





class RSAKey2048
{
    private:
        boost::multiprecision::cpp_int  exponent;
        boost::multiprecision::cpp_int  module;
        boost::multiprecision::cpp_int  max_byte_length;
    public:
        RSAKey2048(boost::multiprecision::cpp_int exponent, boost::multiprecision::cpp_int module) :
            exponent(exponent), module(module), max_byte_length(math_of_RSA_numbers::log256(module))
        {

        }
        RSAKey2048(std::string file_name)
        {
            try
            {
                std::fstream input_file;
                input_file.open(file_name.c_str());
                std::string data;
                std::getline(input_file, data);
                input_file >> exponent >> module;

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
};

