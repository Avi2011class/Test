#include "keys.h"

RSAKey2048::RSAKey2048() :
		exponent(DEFAULT_KEY_EXPONENT), module(DEFAULT_KEY_MODULE), maxByteLength(
				SimpleMath().log256(DEFAULT_KEY_MODULE))
{
}

RSAKey2048::RSAKey2048(boost_longint exponent, boost_longint module) :
		exponent(exponent), module(module), maxByteLength(
				SimpleMath().log256(module))
{
}

RSAKey2048::RSAKey2048(std::string filename)
{
	try
	{
		std::fstream inputStream;
		inputStream.open(filename.c_str());
		inputStream >> exponent >> module;
		maxByteLength = SimpleMath().log256(module);
	} catch (...)
	{
		std::cout << "Ошибка открытия файла или считывания ключа\n"
				<< std::endl;
	}
}

void RSAKey2048::printToFile(std::string filename)
{
	std::fstream outputStream;
	outputStream.open(filename.c_str(), std::ios::out);
	outputStream << exponent << " " << module;
	outputStream.close();
}

boost::multiprecision::cpp_int RSAKey2048::getExponent()
{
	return exponent;
}

boost::multiprecision::cpp_int RSAKey2048::getModule()
{
	return module;
}

unsigned long long int RSAKey2048::getMaxByteLength()
{
	return maxByteLength;
}

bool RSAKey2048::isDefault()
{
	return (module == DEFAULT_KEY_MODULE && exponent == DEFAULT_KEY_EXPONENT);
}

std::pair<RSAKey2048, RSAKey2048> RSAKey2048Bulder::createKeys()
{
	boost::multiprecision::cpp_int P, Q;
	{
		P = SimpleMath().generateRandomPrimeNumber();
		Q = SimpleMath().generateRandomPrimeNumber();
	}
	boost::multiprecision::cpp_int N = P * Q, Phi = (P - 1) * (Q - 1);
	boost::multiprecision::cpp_int e = SimpleMath().generateE(Phi);
	boost::multiprecision::cpp_int d = SimpleMath().generateD(e, Phi);
	return std::make_pair(RSAKey2048(e, N), RSAKey2048(d, N));
}

bool RSAKey2048Bulder::isKeyPairCorrect(KEY_PAIR keyPair)
{
	srand(time(0));
	bool result = true;
	for (size_t i = 0;i < 100;i++)
	{
		boost::multiprecision::cpp_int N = rand();
		boost::multiprecision::cpp_int NCoded = SimpleMath().powerModule(N,keyPair.first.getExponent(), keyPair.first.getModule());
        boost::multiprecision::cpp_int N_decoded = SimpleMath().powerModule(NCoded, keyPair.second.getExponent(), keyPair.second.getModule());
        if (N_decoded != N)
            result = false;
    }
    if (keyPair.first.getModule() != keyPair.second.getModule())
        result = false;

    if (keyPair.first.getMaxByteLength() <= 3 || keyPair.second.getMaxByteLength() <= 3)
        result = false;

    return result;
}
