#ifndef CODER_H_INCLUDED
#define CODER_H_INCLUDED

#include <boost/multiprecision/cpp_int.hpp>

#include <boost/multiprecision/number.hpp>
#include <boost/lexical_cast.hpp>

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "converter.h"
#include "keys.h"
#include "scanner.h"
#include "simple_math.h"
#include "writer.h"

class Encryptor
{
    typedef boost::multiprecision::cpp_int boost_longint;
private:
    EncryptionKey Key;
public:
    Encryptor(EncryptionKey Key);
    boost_longint encryptInt(boost_longint intData);
    std::vector<boost_longint> encryptVectorInt(std::vector<boost_longint> & vectorData);
    void encryptFile(std::string filename);
    void decryptFile(std::string filename);
    unsigned long long int getKeyMaxByteLength();
};

#endif // CODER_H_INCLUDED
