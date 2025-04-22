#ifndef ENCRYPTION_H_INCLUDED
#define ENCRYPTION_H_INCLUDED
#include <string>
#define CHAR_LIMIT 127
///*************
/// Funcoes para criptografia e descriptografia de arquivo utilizando
/// a cifra de cesar.
///********

std::string encryptString(std::string str, int key)
{
    std::string encrypted = str;
    for (char &c : encrypted)
    {
        c = ((c + key) % CHAR_LIMIT);
    }
    return encrypted;
}

std::string decryptString(std::string str, int key)
{
    std::string decrypted = str;
    for (char &c : decrypted)
    {
        c = ((c - key) % CHAR_LIMIT);
    }
    return decrypted;
}

#endif
