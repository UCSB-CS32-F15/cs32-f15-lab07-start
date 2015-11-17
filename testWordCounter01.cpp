#include "WordCounter.h"
#include <iostream>
#include <sstream>
#include "tddFuncs.h"


using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;
  
  std::string sampleText = "This test isn't a difficult 'test' is it?";
  WordCounter wc(sampleText);
  
  std::string expectedSortedByWord = std::string("") +
    "This,1\n" + 
    "a,1\n" + 
    "difficult,1\n" + 
    "is,1\n" + 
    "isn't,1\n" +
    "it,1\n" +
    "test,2\n" + 
    "";

  ASSERT_EQUALS(size_t(7),wc.getNumWords());
  
  ostringstream oss;
  for (auto iter=wc.begin(); iter!=wc.end(); ++iter) {
    int count = wc.getWordCount(*iter);
    oss << (*iter) << "," << count << endl;
  }
  
  ASSERT_EQUALS(expectedSortedByWord,oss.str());
  ASSERT_EQUALS(0,wc.getWordCount("elephant"));
  
  return 0;
}
