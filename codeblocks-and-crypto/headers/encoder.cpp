#include "encoder.h"

Encryptor::Encryptor(EncryptionKey Key) : Key(Key)
    {}

boost::multiprecision::cpp_int Encryptor::encryptInt(boost::multiprecision::cpp_int intData)
{
    switch (boost::lexical_cast< int >(Key.getParameter("encryptionMode")))
    {
    case EncryptionKey::RSA:
        return SimpleMath::powerModule(intData,
                                       Key.getParameter("exponent"),
                                       Key.getParameter("module"));
        break;
    }
    return 0;
}

std::vector< boost::multiprecision::cpp_int >
    Encryptor::encryptVectorInt(std::vector< boost::multiprecision::cpp_int > & vectorData)
{
    int dataSize = (int) vectorData.size();
    std::vector< boost::multiprecision::cpp_int > encryptedInts(dataSize);
    #pragma omp parallel for
    for (int i = 0; i < dataSize; i++)
        encryptedInts[i] = encryptInt(vectorData[i]);
    return encryptedInts;
}

void Encryptor::encryptFile(std::string filename)
{
    try
    {
        std::string hashOfFilename = filename + ".encoded";
        std::vector< char > data = Scanner(filename).readByteData();
        std::vector< boost::multiprecision::cpp_int > intData =
                Converter::convert(data, getKeyMaxByteLength());
        intData = encryptVectorInt(intData);
        Writer(hashOfFilename).writeEncodedData(intData);
    }
    catch (...)
    {
        std::cout << "Error!" << std::endl;
    }

}

void Encryptor::decryptFile(std::string filename)
{
    try
    {
        std::string hashOfFilename = filename + ".encoded";
        std::vector< boost::multiprecision::cpp_int > intData =
                Scanner(hashOfFilename).readEncodedData();

        intData = encryptVectorInt(intData);
        std::vector< char > data = Converter::convert(intData);
        Writer(filename).writeByteData(data);
    }
    catch (...)
    {
        std::cout << "Error!" << std::endl;
    }
}

unsigned long long int Encryptor::getKeyMaxByteLength()
{
    return boost::lexical_cast< unsigned long long int >(Key.getParameter("maxByteLength"));
}
//////////////////////////////////////////////////////////////////////
