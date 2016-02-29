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
void print_container(T container)
{
    std::copy(container.begin(), container.end(),
              std::ostream_iterator<boost::multiprecision::cpp_int>(std::cout, " "));
    std::cout << std::endl << std::endl;
}

int main(void)
{
    RSAKey2048 open_key("open_key"), closed_key("closed_key");
    IntCoder coder(open_key), decoder(closed_key);

    std::vector<boost::multiprecision::cpp_int> data, coded_data, decoded_data;
    for(size_t i = 0; i < 20; i++)
        data.push_back(i);
    print_container(data);
    coded_data = coder.code_vector_int(data);
    print_container(coded_data);
    decoded_data = decoder.code_vector_int(coded_data);
    print_container(decoded_data);
    //*/

    return 0;
}
