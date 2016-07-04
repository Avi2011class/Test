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
class Converter
{
    typedef boost::multiprecision::cpp_int boost_longint;
public:
    Converter() {};
    static std::vector< boost_longint > convert(std::vector< char > & data, int blockSize);
    static std::vector< char >          convert(std::vector< boost_longint > & data);
};

#endif // CONVERTER_H_INCLUDED
