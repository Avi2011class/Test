#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/detail/et_ops.hpp>
#include <boost/multiprecision/detail/number_base.hpp>
#include <boost/multiprecision/detail/number_compare.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/lexical_cast.hpp>

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <map>
#include <exception>
#include <iomanip>

#include "simple_math.h"

#define DEFAULT_RSA_KEY_EXPONENT 1814012943
#define DEFAULT_RSA_KEY_MODULE 3264797647
class EncryptionKey
{
    typedef boost::multiprecision::cpp_int boost_longint;
public:
    enum encryptionMode {RSA, ELGamal};
    enum keyType {OpenKey, ClosedKey};
private:
    std::map< std::string, boost_longint > parameters;
    // encryptionMode: RSA / ELGamal
    // keyType: OPenKey / ClosedKey
    //
    // RSA: exponent, module
    // maxByteLength
    //
public:

    EncryptionKey();
    EncryptionKey(std::map< std::string, boost_longint> parameters);
    EncryptionKey(std::string filename);

    void toFile(std::string filename);
    boost_longint getParameter(std::string nameOfParameter);

    friend std::ostream & operator << (std::ostream & outputStream, EncryptionKey & key)
    {
        for(std::pair< std::string, boost_longint > cur : key.parameters)
            outputStream << cur.first << " " << cur.second << std::endl;
        return outputStream;
    }
    friend std::istream & operator >> (std::istream & inputStream, EncryptionKey & Key)
    {
        Key.parameters.clear();
        std::string parameter, value;
        while (inputStream >> parameter >> value)
            Key.parameters[parameter] = boost_longint(value);
        return inputStream;
    }
};
///////////////////////////////////////////////////////////////////////////////
class EncryptionKeyBuilder
{
    typedef boost::multiprecision::cpp_int boost_longint;
private:
    EncryptionKey::encryptionMode mode;
public:
    EncryptionKeyBuilder(EncryptionKey::encryptionMode mode);
    std::pair< EncryptionKey, EncryptionKey > createKeyPair();
    bool checkKeyPair(std::pair< EncryptionKey, EncryptionKey > keyPair);
};



#endif // KEYS_H_INCLUDED
