#ifndef MPAGSCIPHER_RUNCAESARCIPHER_HPP
#define MPAGSCIPHER_RUNCAESARCIPHER_HPP


#include <string>

//Encrypts or decrypts using the Caesar Cipher as required
std::string runCaesarCipher( const std::string& inputText, const size_t key, const bool encrypt );

#endif // MPAGSCIPHER_RUNCAESARCIPHER_HPP
