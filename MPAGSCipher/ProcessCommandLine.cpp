#include <string>
#include <vector>
#include <iostream>

#include "ProcessCommandLine.hpp"

bool processCommandLine( const std::vector<std::string>& args,
			 bool& helpRequested, bool& versionRequested, bool& encrypt, unsigned long& key, std::string& inputFileName,
			 std::string& outputFileName ){
  /* Takes arguments and parses them to find if help or version number are requested.
     Sets the input and output strings if provided.*/


  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nArgs {args.size()};


  for (size_type i {1}; i < nArgs; ++i) {

    if (args[i] == "-h" || args[i] == "--help") {
      helpRequested = true;
    }
    else if (args[i] == "--version") {
      versionRequested = true;
    }
    else if (args[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nArgs-1) {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	inputFileName = args[i+1];
	++i;
      }
    }
    else if (args[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nArgs-1) {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	outputFileName = args[i+1];
	++i;
      }
    }
    else if(args[i] == "-k"){
      if (i == nArgs-1) {
	std::cerr << "[error] -k requires a key value" << std::endl;
	return false;
      }
      else{
	//Converts string to unsigned long and sets key to the value
	std::string cipherKey{ args[++i] };
	// Before doing the conversion we should check that the string contains a
	// valid positive integer.
	// Here we do that by looping through each character and checking that it
	// is a digit. What is rather hard to check is whether the number is too
	// large to be represented by an unsigned long, so we've omitted that for
	// the time being.
	// (Since the conversion function std::stoul will throw an exception if the
	// string does not represent a valid unsigned long, we could check for and
	// handled that instead but we only cover exceptions very briefly on the
	// final day of this course - they are a very complex area of C++ that
	// could take an entire course on their own!)
	for ( const auto& elem : cipherKey ) {
	  if ( ! std::isdigit(elem) ) {
	    std::cerr << "[error] cipher key must be an unsigned long integer for Caesar cipher,\n"
	      << "        the supplied key (" << cipherKey << ") could not be successfully converted" << std::endl;
	    return false;
	  }
	}
	key = std::stoul(cipherKey);
      }
    }
    else if(args[i] == "--encrypt"){
      encrypt = true;
    }
    else if(args[i] == "--decrypt"){
      encrypt = false;
    }
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
      return false;
    }
  }
  return true;
}
