#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

class Scanner
{
private:
    std::string filename;
public:
    Scanner(std::string filename) : filename(filename) {}
    std::vector<char> readByteData();
    std::vector<boost::multiprecision::cpp_int> readEncodedData();
};
#endif // SCANNER_H_INCLUDED
