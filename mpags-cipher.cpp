// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// For std::isalpha and std::isupper
#include <cctype>

// Project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"


// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  bool encrypt{true};
  unsigned long key {0};
  
  if(!processCommandLine(cmdLineArgs, helpRequested, versionRequested, encrypt, key, inputFile, outputFile)){
    return 1;
  }

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n"
      << "  -k KEY           Use key from KEY in Caesar Cipher\n\n"
      << "  --encrypt        Encrypt the input text\n\n"
      << "  --decrypt        Decrypt the input text\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }
  


  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.2.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  //Recieves user input from the appropriate source
  if (!inputFile.empty()) {
    std::ifstream in_file {inputFile};
    if (in_file.good()){
      while(in_file >> inputChar)
	{
	  inputText += transformChar(inputChar);
	}
    }
    else{
      std::cerr << "[error] Input file ('"
		<< inputFile
		<< "') was not correctly opened.";
      return 1;
    }
  }
  else{
    // Loop over each character from user input
    // (until Return then CTRL-D (EOF) pressed)
    while(std::cin >> inputChar)
      {
	inputText += transformChar(inputChar);
      }
  }

  
  //Encrypt or decrypt the input text
  std::cout << (encrypt ? "Encrypting " : "Decrypting ") << "input using key = " << key << std::endl;
  std::string outputText { runCaesarCipher( inputText, key, encrypt) };
  

  // Output the transliterated text
  if (!outputFile.empty()) {
    std::ofstream out_file{outputFile};
    if (out_file.good()){
      out_file << outputText;
    }
    else{
      std::cerr << "[error] Output file ('"
		<< outputFile
		<< "') was not correctly opened.";
      return 1;
    }
  }
  else{
    std::cout << outputText << std::endl;
  }

  return 0;
}
