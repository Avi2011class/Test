#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>

namespace scanner
{
    /* Чтение из файла байтового вектора */
    std::vector<char> read_byte_file(std::string filename)
    {
        std::fstream input_stream;
        try
        {
            input_stream.open(filename.c_str(), std::ios::in|std::ios::binary);
            std::vector<char> result;
            std::copy(std::istreambuf_iterator<char>(input_stream),
                      std::istreambuf_iterator<char>(),
                      std::back_inserter(result));
            input_stream.close();
            return result;
        }
        catch(...)
        {
            std::cout << "Can't open file or read data" << std::endl;
            return std::vector<char>();
        }
    }

    /* Чтение из файла целочисленного вектора */
    std::vector<boost::multiprecision::cpp_int> read_coded_file(std::string filename)
    {
        std::fstream input_stream;
        try
        {
            std::string hash_of_filename =
                boost::lexical_cast<std::string>(std::hash<std::string>()(filename)) + ".encoded";
            input_stream.open(hash_of_filename.c_str(), std::ios::in|std::ios::binary);
            std::vector<boost::multiprecision::cpp_int> result;
            std::copy(std::istream_iterator<boost::multiprecision::cpp_int>(input_stream),
                      std::istream_iterator<boost::multiprecision::cpp_int>(),
                      std::back_inserter(result));
            input_stream.close();
            return result;
        }
        catch(...)
        {
            std::cout << "Can't open file or read data" << std::endl;
            return std::vector<boost::multiprecision::cpp_int>();
        }
    }
}

namespace writer
{
    /* Запись в файл байтового вектора */
    void write_byte_file(std::vector<char> & data, std::string filename)
    {
        std::fstream output_stream;
        output_stream.open(filename.c_str(), std::ios::out|std::ios::binary);
        std::copy(data.begin(), data.end(),
                  std::ostreambuf_iterator<char>(output_stream));
        output_stream.close();
    }

    /* Запись в файл целочисленного вектора */
    void write_coded_file(std::vector<boost::multiprecision::cpp_int> & data, std::string filename)
    {
        std::string hash_of_filename = boost::lexical_cast<std::string>(std::hash<std::string>()(filename)) + ".encoded";
        std::fstream output_stream;
        output_stream.open(hash_of_filename.c_str(), std::ios::out|std::ios::binary);
        std::copy(data.begin(), data.end(),
                  std::ostream_iterator<boost::multiprecision::cpp_int>(output_stream, " "));
        output_stream.close();
    }
}
#endif // SCANNER_H_INCLUDED
