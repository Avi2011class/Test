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

class RSAKey2048
{
    private:
        boost::multiprecision::cpp_int exponent;
        boost::multiprecision::cpp_int module;
    public:
        RSAKey2048(boost::multiprecision::cpp_int exponent, boost::multiprecision::cpp_int module) :
            exponent(exponent), module(module) {};
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
};
