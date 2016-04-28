#include "scanner.h"

std::vector<char> Scanner::readByteData()
{
	std::fstream inputStream;
	try
	{
		inputStream.open(filename.c_str(), std::ios::in | std::ios::binary);
		std::vector<char> result;
		std::copy(std::istreambuf_iterator<char>(inputStream),
				std::istreambuf_iterator<char>(), std::back_inserter(result));
		inputStream.close();
		return result;
	} catch (...)
	{
		std::cout << "Can't open file or read data" << std::endl;
		return std::vector<char>();
	}
}

std::vector<boost::multiprecision::cpp_int> Scanner::readEncodedData()
{
	std::fstream inputStream;
	try
	{
		inputStream.open(filename.c_str(), std::ios::in | std::ios::binary);
		std::vector<boost::multiprecision::cpp_int> result;
		std::copy(
				std::istream_iterator<boost::multiprecision::cpp_int>(
						inputStream),
				std::istream_iterator<boost::multiprecision::cpp_int>(),
				std::back_inserter(result));
		inputStream.close();
		return result;
	} catch (...)
	{
		std::cout << "Can't open file or read data" << std::endl;
		return std::vector<boost::multiprecision::cpp_int>();
	}
}
