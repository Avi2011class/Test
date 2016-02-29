#include <iostream>
#include <iomanip>
#include <ctime>

#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <fstream>


#include "math_of_RSA_numbers.h"

int main(void)
{
    KEY_PAIR p = math_of_RSA_numbers::create_keys();
    std::cout << p.first << std::endl << p.second << std::endl;
    std::cout << (math_of_RSA_numbers::key_pair_OK(p) ? "OK" : "ERR") << std::endl;
    return 0;
}
