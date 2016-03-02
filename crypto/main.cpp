#include <iostream>
#include <iomanip>
#include <ctime>

#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <fstream>

#include "coder.h"

template<typename T>
void print_container_cpp_int(T container)
{
    std::copy(container.begin(), container.end(),
              std::ostream_iterator<boost::multiprecision::cpp_int>(std::cout, " "));
    std::cout << std::endl << std::endl;
}
template<typename T>
void print_container_int(T container)
{
    std::copy(container.begin(), container.end(),
              std::ostream_iterator<boost::multiprecision::cpp_int>(std::cout, " "));
    std::cout << std::endl << std::endl;
}
template<typename T>
void print_container_char(T container)
{
    std::copy(container.begin(), container.end(),
              std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl << std::endl;
}

int main(void)
{
    /*
    RSAKey2048 open_key("open_key"), closed_key("closed_key");
    IntCoder coder(open_key), decoder(closed_key);
    std::vector<boost::multiprecision::cpp_int> data, coded_data, decoded_data;
    for(size_t i = 0; i < 200; i++)
        data.push_back(i);
    print_container(data);
    coded_data = coder.code_vector_int(data);
    print_container(coded_data);
    decoded_data = decoder.code_vector_int(coded_data);
    print_container(decoded_data);
    //*/
    std::vector<char> data = {'1', '2', '3', '4', '5', '6', '7'};
    std::vector<boost::multiprecision::cpp_int> result = Converter::char_to_int_vector(data, 90);
    std::vector<char> data2 = Converter::int_to_char_vector(result);
    print_container_char(data);
    print_container_cpp_int(result);
    print_container_char(data2);
    return 0;
}
