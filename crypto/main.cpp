#include <iostream>
#include <iomanip>
#include <ctime>
#include <clocale>

#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <fstream>
#include <string>

#include "headers/encoder.h"
#include "headers/scanner.h"

Encoder encoder(DEFAULT_KEY);

void main_interface()
{
    bool flag = true;
    while(flag)
    {

        std::cout << "Select an action:" << std::endl;
        std::cout << "  1. Connect the key file" << std::endl;
        std::cout << "  2. Encode file" << std::endl;
        std::cout << "  3. Decode file" << std::endl;
        std::cout << "  4. Create new key pair" << std::endl;
        std::cout << "  5. Check key pair" << std::endl;
        std::cout << "  6. Exit" << std::endl;
        std::cout << "  >> " << std::endl;
        int action;
        std::cin >> action;
        switch(action)
        {
        case 1:
            {
                std::cout << "The key file name: ";
                std::string filename;
                std::cin >> filename;
                encoder = Encoder(RSAKey2048(filename));
                break;
            }

        case 2:
            {
                std::cout << "      The file name: ";
                std::string filename;
                std::cin >> filename;
                std::vector<char> data = scanner::read_byte_file(filename);

                std::vector<boost::multiprecision::cpp_int> int_data = converter::char_to_int_vector(data, encoder.get_key_max_byte_length());
                std::vector<boost::multiprecision::cpp_int> encoded_data = encoder.code_vector_int(int_data);
                writer::write_coded_file(encoded_data, filename);
                if(encoder.is_key_default())
                    std::cout << "      completed (default key was used)" << std::endl;
                else
                    std::cout << "      comleted!" << std::endl;
                break;
            }
        case 3:
            {
                std::cout << "      The file initial name: ";
                std::string filename;
                std::cin >> filename;

                std::vector<boost::multiprecision::cpp_int> encoded_data = scanner::read_coded_file(filename);
                std::vector<boost::multiprecision::cpp_int> int_data = encoder.code_vector_int(int_data);
                std::vector<char> data = converter::int_to_char_vector(int_data);
                writer::write_byte_file(data, filename);
                if(encoder.is_key_default())
                    std::cout << "      completed (default key was used)" << std::endl;
                else
                    std::cout << "      comleted!" << std::endl;
                break;
            }
        case 4:
            {
                std::string open_key_file, closed_key_file;
                std::cout << "      Name of open key file: ";
                std::cin >> open_key_file;
                std::cout << "      Name of closed key file: ";
                std::cin >> closed_key_file;
                KEY_PAIR Keys = key_functions::create_keys();

                std::fstream open_key_stream, closed_key_stream;
                open_key_stream.open(open_key_file, std::ios::out);
                open_key_stream << Keys.first;
                open_key_stream.close();
                closed_key_stream.open(closed_key_file, std::ios::out);
                closed_key_stream << Keys.second;
                closed_key_stream.close();
                std::cout << "      completed!" << std::endl;
                break;
            }
        case 5:
            {
                std::string open_key_file, closed_key_file;
                std::cout << "      Name of open key file: ";
                std::cin >> open_key_file;
                std::cout << "      Name of closed key file: ";
                std::cin >> closed_key_file;
                RSAKey2048 open_key(open_key_file), closed_key(closed_key_file);
                if(key_functions::key_pair_OK(std::make_pair(open_key, closed_key)))
                {
                    std::cout << "       OK!" << std::endl;
                }
                else
                {
                    std::cout << "       BAD!" << std::endl;
                }
                break;
            }
        case 6:
            {
                flag = false;
            }
        }
    }
}

int main(void)
{
    main_interface();
    return 0;
}
