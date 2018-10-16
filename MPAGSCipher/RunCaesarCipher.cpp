#include <string>
#include <vector>

#include "RunCaesarCipher.hpp"



/*Runs the Caesar Cipher encrypting or decrypting according to
 the value of encrypt and using key*/
std::string runCaesarCipher( const std::string& inputText,
			     const size_t key, const bool encrypt )
{
  // Create the alphabet container and output string
  const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  const size_t alphabetSize = alphabet.size();
  std::string outputText{""};

  // Make sure that the key is in the range 0 - 25
  const size_t truncatedKey { key % alphabetSize };
  
  // Loop over the input text
  for(const char& inputChar : inputText){
    // For each character find the corresponding position in the alphabet
    //Likely would be better to use a map
    for(size_t pos{0}; pos < alphabetSize; ++pos){
      if(inputChar == alphabet[pos]){
	// Makes shift +ve or -ve depending on encrypt/decrypt
	// -ve is implemented as 26 - key%26 to avoid using % on any negative values below
	size_t shift = encrypt ? truncatedKey : alphabetSize - truncatedKey;
	// Apply the shift (+ve or –ve depending on encrypt/decrypt)
	// to the position, handling correctly potential wrap-around
	// Determine the new character and add it to the output string
	outputText += alphabet[(pos+shift)%alphabetSize];
	break;
      }
    }
  }
  // Return the output string
  return outputText;
}
