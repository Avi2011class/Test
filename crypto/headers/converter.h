#ifndef CONVERTER_H_INCLUDED
#define CONVERTER_H_INCLUDED

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/lexical_cast.hpp>

#include <omp.h>

namespace converter
{
    std::vector<boost::multiprecision::cpp_int>
    char_to_int_vector(std::vector<char> data, int block_size)
    {
        int start_data_size = data.size();

        data.resize(start_data_size + ( block_size - (start_data_size % block_size) ) % block_size);

        std::vector<boost::multiprecision::cpp_int> result_int_vector(data.size() / block_size + 2);
        result_int_vector[0] = block_size;
        result_int_vector[1] = start_data_size;

        int new_data_size = data.size();

        #pragma omp parallel for
        for(int i = 0; i < new_data_size; i += block_size)
        {
            boost::multiprecision::cpp_int buffer = 0;
            boost::multiprecision::cpp_int carry = 1;
            for(int j = 0; j < block_size; j++)
            {
                buffer += carry * (((int)(data[i + j]) + 256) % 256);
                carry *= 256;
            }
            result_int_vector[i / block_size + 2] = buffer;
        }
        return result_int_vector;
    }

    std::vector<char> int_to_char_vector(std::vector<boost::multiprecision::cpp_int> data)
    {
        int block_size = boost::lexical_cast<int>(data[0]);
        int start_result_size = boost::lexical_cast<int>(data[1]);

        std::vector<char> result_char_vector((data.size() - 2) * block_size);

        #pragma omp parallel for
        for(size_t i = 2; i < data.size(); i++)
        {
            for(int j = 0; j < block_size; j++)
            {
                result_char_vector[ (i - 2) * block_size + j] =
                    static_cast<char>(boost::lexical_cast<int>(data[i] % 256));
                data[i] = data[i] / 256;
            }
        }
        result_char_vector.resize(start_result_size);
        return result_char_vector;
    }
}

#endif // CONVERTER_H_INCLUDED
