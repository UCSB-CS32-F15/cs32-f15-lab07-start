#include "WordCounter.h"

#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Running tests from: " << __FILE__ << endl;
  
  ASSERT_EQUALS("foo",WordCounter::stripWord(".foo"));
  ASSERT_EQUALS("bar",WordCounter::stripWord("bar?"));
  ASSERT_EQUALS("fum",WordCounter::stripWord("...fum***"));
  ASSERT_EQUALS("quote",WordCounter::stripWord("\"quote\""));
  ASSERT_EQUALS("isn't",WordCounter::stripWord("isn't"));
  ASSERT_EQUALS("mother-in-law",WordCounter::stripWord("mother-in-law"));

  
  return 0;
}
