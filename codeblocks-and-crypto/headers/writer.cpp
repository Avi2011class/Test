#include "writer.h"

void Writer::writeByteData(std::vector<char>& data)
{
    std::fstream outputStream;
    outputStream.open(filename.c_str(), std::ios::out | std::ios::binary);
    std::copy(data.begin(), data.end(),
              std::ostreambuf_iterator<char>(outputStream));
    outputStream.close();
}

void Writer::writeEncodedData(std::vector<boost::multiprecision::cpp_int>& data)
{
    std::fstream outputStream;
    outputStream.open(filename.c_str(), std::ios::out | std::ios::binary);
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<boost::multiprecision::cpp_int>(outputStream,
                      " "));
    outputStream.close();
}
