#include <iostream>
#include <functional>

#include "headers/encoder.h"
#include "headers/keys.h"


int main(void)
{
    //std::pair< EncryptionKey, EncryptionKey > p = EncryptionKeyBuilder(EncryptionKey::RSA).createKeyPair();
    //p.first.toFile("openKey.txt");
    //p.second.toFile("closedKey.txt");

    EncryptionKey e("openKey.txt"), f("closedKey.txt");
    Encryptor C(f);
    //C.encryptFile("map.txt");
    C.decryptFile("map.txt");
    //main_interface();
    return 0;
}
