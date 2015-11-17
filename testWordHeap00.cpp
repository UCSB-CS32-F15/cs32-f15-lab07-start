#include "WordHeap.h"

#include <iostream>
#include <utility>
#include "tddFuncs.h"

#include <cmath>

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  WordItem item0(1,"foo","unit testing");
  WordItem item1(7,"bar","more unit testing");
  WordItem item2(4,"fum","still unit testing");
  WordItem item3(4,"baz","you guessed it, unit testing");


  ASSERT_EQUALS(1,item0.count);
  ASSERT_EQUALS("foo",item0.word);
  ASSERT_EQUALS("unit testing",item0.metadata);

  ASSERT_EQUALS(7,item1.count);
  ASSERT_EQUALS("bar",item1.word);
  ASSERT_EQUALS("more unit testing",item1.metadata);

  ASSERT_EQUALS(4,item2.count);
  ASSERT_EQUALS("fum",item2.word);
  ASSERT_EQUALS("still unit testing",item2.metadata);

  ASSERT_EQUALS(4,item3.count);
  ASSERT_EQUALS("baz",item3.word);
  ASSERT_EQUALS("you guessed it, unit testing",item3.metadata);

  
  
  return 0;
}
