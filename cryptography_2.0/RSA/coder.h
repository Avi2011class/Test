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

#include "keys.h"

class IntCoder
{
    private:
        RSAKey2048 & Key;
    public:
        IntCoder(RSAKey2048 & Key) : Key(Key) {};

        void connect_with_key(RSAKey2048 & new_key)
        {
            Key = new_key;
        }

        boost::multiprecision::cpp_int code_int(boost::multiprecision::cpp_int int_data)
        {
            return simple_math::power_module(int_data, Key.get_exponent(), Key.get_module());
        }

        std::vector<boost::multiprecision::cpp_int>
        code_vector_int(std::vector<boost::multiprecision::cpp_int> & vector_data)
        {
            std::vector<boost::multiprecision::cpp_int> coded_ints;
            for(std::vector<boost::multiprecision::cpp_int>::iterator it = vector_data.begin(); it != vector_data.end(); it++)
                coded_ints.push_back(code_int(*it));

            return coded_ints;
        }

};
