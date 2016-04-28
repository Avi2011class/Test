#include "encoder.h"

boost::multiprecision::cpp_int Encoder::encodeInt(
		boost::multiprecision::cpp_int intData)
{
	return SimpleMath().powerModule(intData, Key.getExponent(),
			Key.getModule());
}
std::vector<boost::multiprecision::cpp_int>
Encoder::encodeVectorInt(std::vector<boost::multiprecision::cpp_int> & vectorData)
{
	std::vector<boost::multiprecision::cpp_int> encodedInts(vectorData.size());

#pragma omp parallel for
	for(size_t i = 0; i < vectorData.size(); i++)
		encodedInts[i] = encodeInt(vectorData[i]);
	return encodedInts;
}
void Encoder::encodeFile(std::string filename)
{
	try
	{
		// std::string hash_of_filename = boost::lexical_cast< std::string >(std::hash< std::string >()(filename)) + ".encoded";
		std::string hashOfFilename = filename + ".encoded";
		std::vector<char> data = Scanner(filename).readByteData();
		std::vector<boost::multiprecision::cpp_int> intData =
				Converter().convert(data, getKeyMaxByteLength());
		intData = encodeVectorInt(intData);
		Writer(hashOfFilename).writeEncodedData(intData);
	}
	catch (...)
	{
		std::cout << "Error!" << std::endl;
	}
}
void Encoder::decodeFile(std::string filename)
{
	try
	{
		// std::string hash_of_filename = boost::lexical_cast< std::string > (std::hash< std::string >(filename)) + ".encoded";
		std::string hashOfFilename = filename + ".encoded";
		std::vector<boost::multiprecision::cpp_int> intData = Scanner(hashOfFilename).readEncodedData();
		intData = encodeVectorInt(intData);
		std::vector<char> data = Converter().convert(intData);
		Writer(filename).writeByteData(data);
	}
	catch(...)
	{
		std::cout << "Error!" << std::endl;
	}
}

bool Encoder::isKeyDefault()
{
	return Key.isDefault();
}
int Encoder::getKeyMaxByteLength()
{
	return Key.getMaxByteLength();
}
