#include "keys.h"

EncryptionKey::EncryptionKey()
{}

EncryptionKey::EncryptionKey(std::map< std::string, boost_longint> parameters) : parameters(parameters)
{}

EncryptionKey::EncryptionKey(std::string filename)
{
	std::fstream inputStream;
	inputStream.open(filename, std::ios::in);
	inputStream >> *this;
	inputStream.close();
}
void EncryptionKey::toFile(std::string filename)
{
	std::fstream outputStream;
	outputStream.open(filename, std::ios::out);
	outputStream << *this;
	outputStream.close();
}
boost::multiprecision::cpp_int EncryptionKey::getParameter(std::string nameOfParameter)
{
	return parameters[nameOfParameter];
}
///////////////////////////////////////////////////////////////////////////////


EncryptionKeyBuilder::EncryptionKeyBuilder(EncryptionKey::encryptionMode mode) : mode(mode)
{}

std::pair< EncryptionKey, EncryptionKey > EncryptionKeyBuilder::createKeyPair()
{
	switch ((int)mode)
	{
	case (int)EncryptionKey::RSA:
		boost::multiprecision::cpp_int P, Q;
		#pragma omp parallel sections
		{
			#pragma omp section
			P = SimpleMath::generateRandomPrimeNumber();
			#pragma omp section
			Q = SimpleMath::generateRandomPrimeNumber();
		}
		boost::multiprecision::cpp_int N = P * Q, Phi = (P - 1) * (Q - 1);
		boost::multiprecision::cpp_int e = SimpleMath::generateE(Phi);
		boost::multiprecision::cpp_int d = SimpleMath::generateD(e, Phi);
		std::map< std::string, boost::multiprecision::cpp_int > openKeyMap;
            openKeyMap["encryptionMode"] = EncryptionKey::RSA;
            openKeyMap["keyType"] = EncryptionKey::OpenKey;
            openKeyMap["exponent"] = e;
            openKeyMap["module"] = N;
            openKeyMap["maxByteLength"] = SimpleMath::log256(N);
		std::map< std::string, boost::multiprecision::cpp_int > closedKeyMap;
            closedKeyMap["encryptionMode"] = EncryptionKey::RSA;
            closedKeyMap["keyType"] = EncryptionKey::ClosedKey;
            closedKeyMap["exponent"] = d;
            closedKeyMap["module"] = N;
            closedKeyMap["maxByteLength"] = SimpleMath::log256(N);
		return std::make_pair(EncryptionKey(openKeyMap), EncryptionKey(closedKeyMap));
		break;
	case (int)EncryptionKey::ELGamal:
		break;

	default:
		throw std::invalid_argument("EncryptionKeyBuilder.createKeyPair needs correct mode parameter!");
		break;
	}
	throw std::invalid_argument("EncryptionKeyBuilder.createKeyPair needs correct mode parameter!");
}


bool EncryptionKeyBuilder::checkKeyPair(std::pair< EncryptionKey, EncryptionKey > keyPair)
{
	switch ((int)mode)
	{
	case (int)EncryptionKey::RSA:
        #define CHECK(__var) if(!(__var)) \
        {\
            /*throw std::invalid_argument(std::to_string(__LINE__));*/\
            return false;\
        }
		CHECK(keyPair.first.getParameter("encryptionMode") == EncryptionKey::RSA);
		CHECK(keyPair.first.getParameter("keyType") == EncryptionKey::OpenKey);
		CHECK(keyPair.first.getParameter("maxByteLength") > 1);
		CHECK(keyPair.first.getParameter("module") != 0);
		CHECK(keyPair.first.getParameter("exponent") != 0);
		CHECK(keyPair.first.getParameter("maxByteLength") ==
			  SimpleMath::log256(keyPair.first.getParameter("module")));

		CHECK(keyPair.second.getParameter("encryptionMode") == EncryptionKey::RSA);
		CHECK(keyPair.second.getParameter("keyType") == EncryptionKey::ClosedKey);
		CHECK(keyPair.second.getParameter("maxByteLength") > 1);
		CHECK(keyPair.second.getParameter("module") != 0);
		CHECK(keyPair.second.getParameter("exponent") != 0);
		CHECK(keyPair.second.getParameter("maxByteLength") ==
			  SimpleMath::log256(keyPair.second.getParameter("module")));

		CHECK(keyPair.first.getParameter("module") ==
			  keyPair.second.getParameter("module"));

		//#pragma omp parallel for
		for (size_t i = 0; i < 10; i++)
		{
			boost::multiprecision::cpp_int N = rand();
			boost::multiprecision::cpp_int NCoded = SimpleMath::powerModule(N,
											keyPair.first.getParameter("exponent"),
											keyPair.first.getParameter("module"));
			boost::multiprecision::cpp_int N_decoded = SimpleMath::powerModule(NCoded,
											keyPair.second.getParameter("exponent"),
											keyPair.second.getParameter("module"));
			CHECK(N_decoded == N);
        }

        #undef CHECK
		return true;
		break;
	case EncryptionKey::ELGamal:
		break;

	default:
		throw std::invalid_argument("EncryptionKeyBuilder.checkKeyPair needs correct mode parameter!");
		break;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////
