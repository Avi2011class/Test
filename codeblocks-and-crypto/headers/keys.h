#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/detail/et_ops.hpp>
#include <boost/multiprecision/detail/number_base.hpp>
#include <boost/multiprecision/detail/number_compare.hpp>
#include <boost/multiprecision/number.hpp>
#include <stddef.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "simple_math.h"

#define KEY_PAIR std::pair<RSAKey2048, RSAKey2048>

#define DEFAULT_KEY RSAKey2048(1814012943, 3264797647)
#define DEFAULT_KEY_EXPONENT 1814012943
#define DEFAULT_KEY_MODULE 3264797647

class RSAKey2048
{
    typedef boost::multiprecision::cpp_int boost_longint;
private:
    boost_longint  exponent;
    boost_longint  module;
    unsigned long long int  maxByteLength;
public:
    RSAKey2048();
    RSAKey2048(boost_longint exponent, boost_longint module);
    RSAKey2048(std::string filename);
    friend std::ostream& operator << (std::ostream& outputSteam, RSAKey2048& Key)
    {
        outputSteam << Key.exponent << " " << Key.module;
        return outputSteam;
    }
    friend std::istream& operator >> (std::istream& inputStream, RSAKey2048& Key)
    {
        inputStream >> Key.exponent >> Key.module;
        return inputStream;
    }
    friend bool operator ==( RSAKey2048& Key1, RSAKey2048& Key2 )
    {
        return (Key1.exponent == Key2.exponent && Key1.module == Key2.module);
    }
    void printToFile(std::string filename);
    boost_longint getExponent();
    boost_longint getModule();
    unsigned long long int getMaxByteLength();
    bool isDefault();
};

class RSAKey2048Bulder
{
public:
    std::pair<RSAKey2048, RSAKey2048> createKeys();
    bool isKeyPairCorrect(KEY_PAIR keyPair);
};
#endif // KEYS_H_INCLUDED
