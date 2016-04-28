#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

#include <boost/multiprecision/cpp_int.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class Writer
{
private:
    std::string filename;
public:
    Writer(std::string filename) : filename(filename) {}
    void writeByteData(std::vector<char> & byteData);
    void writeEncodedData(std::vector<boost::multiprecision::cpp_int> & intData);
};
#endif // WRITER_H_INCLUDED
