#include <iostream>
#include <functional>

#include "headers/encoder.h"
#include "headers/keys.h"

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
            std::cout << "      The key file name: ";
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
            encoder.encodeFile(filename);
            if(encoder.isKeyDefault())
                std::cout << "      completed (default key was used)" << std::endl;
            else
                std::cout << "      completed!" << std::endl;
            break;
        }
        case 3:
        {
            std::cout << "      The file initial name: ";
            std::string filename;
            std::cin >> filename;
            encoder.decodeFile(filename);
            if(encoder.isKeyDefault())
                std::cout << "      completed (default key was used)" << std::endl;
            else
                std::cout << "      completed!" << std::endl;
            break;
        }
        case 4:
        {
            std::string openKeyFile, closedKeyFile;
            std::cout << "      Name of open key file: ";
            std::cin >> openKeyFile;
            std::cout << "      Name of closed key file: ";
            std::cin >> closedKeyFile;
            KEY_PAIR Keys = RSAKey2048Bulder().createKeys();

            std::fstream openKeyStream, closedKeyStream;
            openKeyStream.open(openKeyFile.c_str(), std::ios::out);
            openKeyStream << Keys.first;
            openKeyStream.close();
            closedKeyStream.open(closedKeyFile.c_str(), std::ios::out);
            closedKeyStream << Keys.second;
            closedKeyStream.close();
            std::cout << "      completed!" << std::endl;
            break;
        }
        case 5:
        {
            std::string openKeyFile, closedKeyFile;
            std::cout << "      Name of open key file: ";
            std::cin >> openKeyFile;
            std::cout << "      Name of closed key file: ";
            std::cin >> closedKeyFile;
            RSAKey2048 openKey(openKeyFile), closedKey(closedKeyFile);
            if(RSAKey2048Bulder().isKeyPairCorrect(std::make_pair(openKey, closedKey)))
                std::cout << "       OK!" << std::endl;
            else
                std::cout << "       BAD!" << std::endl;
            break;
        }
        case 6:
        {
            flag = false;
        }
        }
    }
    //*/
}

int main(void)
{
    main_interface();
    return 0;
}
