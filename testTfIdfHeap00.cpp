#include "TfIdfHeap.h"

#include <iostream>
#include <utility>
#include "tddFuncs.h"

#include <cmath>

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  TfIdfItem item0(1.0,2,0.5,"word0","metadata0");
  TfIdfItem item1(1.1,11,0.1,"word2","metadata1");
  TfIdfItem item12(6.0,10,0.6,"word2","metadata2");

  APPROX_EQUALS(1.0,item0.tfIdf,0.001);
  ASSERT_EQUALS(2,item0.tf);
  APPROX_EQUALS(0.5,item0.idf,0.001);
  ASSERT_EQUALS("word0",item0.word);
  ASSERT_EQUALS("metadata0",item0.metadata);

  return 0;
}
