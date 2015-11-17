#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <sstream>
#include <cstdlib>

int main(int argc, char *argv[]) {

  if (argc <= 1) {
    cerr << "Usage: " << argv[0] << " url" << endl;
    exit(1);
  }

  // set up a stringstream to read web page content into
  std::ostringstream oss;

  // Use CURL library to get web content from this url
  curlpp::Cleanup myCleanup;
    try {
      oss << curlpp::options::Url(argv[1]);
    } catch (...) {
      cerr << "ERROR: Unable to retrieve url: " << argv[1] << endl;
      exit(2);
    }
  // Output contents of oss as a std::string
  cout << oss.str();
  return 0;
}
