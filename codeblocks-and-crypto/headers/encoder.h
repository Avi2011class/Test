#ifndef CODER_H_INCLUDED
#define CODER_H_INCLUDED

#include <boost/multiprecision/cpp_int.hpp>

#include <boost/multiprecision/number.hpp>
#include <stddef.h>
#include <iostream>
#include <string>
#include <vector>

#include "converter.h"
#include "keys.h"
#include "scanner.h"
#include "simple_math.h"
#include "writer.h"

class Encoder
{
    typedef boost::multiprecision::cpp_int boost_longint;
private:
    RSAKey2048 Key;
public:
    Encoder(RSAKey2048 Key) : Key(Key) {};
    boost_longint encodeInt(boost_longint int_data);
    std::vector<boost_longint> encodeVectorInt(std::vector<boost_longint> & vectorData);
    void encodeFile(std::string filename);
    void decodeFile(std::string filename);
    bool isKeyDefault();
    int getKeyMaxByteLength();
};
#endif // CODER_H_INCLUDED
