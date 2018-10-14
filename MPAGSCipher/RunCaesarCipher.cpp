#include <string>
#include <vector>

#include "RunCaesarCipher.hpp"



/*Runs the Caesar Cipher encrypting or decrypting according to
 the value of encrypt and using key*/
std::string runCaesarCipher( const std::string& inputText,
			     const size_t key, const bool encrypt )
{
  // Create the alphabet container and output string
  std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  std::string outputText{""};

  
  // Loop over the input text
  for(unsigned int i{0}; i<inputText.length(); ++i){
    // For each character find the corresponding position in the alphabet
    //Likely would be better to use a map
    int pos{0};
    while(inputText[i] != alphabet[pos]){
      ++pos;
    }
    // Makes shift +ve or -ve depending on encrypt/decrypt
    int shift = encrypt ? key : 26 - key%26;
    // Apply the shift (+ve or –ve depending on encrypt/decrypt)
    // to the position, handling correctly potential wrap-around
    // Determine the new character and add it to the output string
    outputText += alphabet[(pos+shift)%26];
  }
  // Return the output string
  return outputText;
}
