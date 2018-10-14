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
	key = std::stoul(args[++i]);
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
