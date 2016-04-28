#include "converter.h"

std::vector<boost::multiprecision::cpp_int> Converter::convert(
		std::vector<char>& data, int blockSize)
{
	int startDataSize = data.size();
	data.resize(
			startDataSize
					+ (blockSize - (startDataSize % blockSize)) % blockSize);
	std::vector<boost::multiprecision::cpp_int> resultIntVector(
			data.size() / blockSize + 2);
	resultIntVector[0] = blockSize;
	resultIntVector[1] = startDataSize;
	int newDataSize = data.size();
	for (int i = 0; i < newDataSize; i += blockSize)
	{
		boost::multiprecision::cpp_int buffer = 0;
		boost::multiprecision::cpp_int carry = 1;
		for (int j = 0; j < blockSize; j++)
		{
			buffer += carry * (((int) ((data[i + j])) + 256) % 256);
			carry *= 256;
		}
		resultIntVector[i / blockSize + 2] = buffer;
	}
	data.resize(startDataSize);
	return resultIntVector;
}

std::vector<char> Converter::convert(std::vector<boost::multiprecision::cpp_int> & data)
{
    int blockSize = boost::lexical_cast<int>(data[0]);
    int startResultSize = boost::lexical_cast<int>(data[1]);

    std::vector<char> resultCharVector((data.size() - 2) * blockSize);

    #pragma omp parallel for
    for(size_t i = 2; i < data.size(); i++)
    {
        for(int j = 0; j < blockSize; j++)
        {
            resultCharVector[ (i - 2) * blockSize + j] =
                static_cast<char>(boost::lexical_cast<int>(data[i] % 256));
            data[i] = data[i] / 256;
        }
    }
    resultCharVector.resize(startResultSize);
    return resultCharVector;
}
