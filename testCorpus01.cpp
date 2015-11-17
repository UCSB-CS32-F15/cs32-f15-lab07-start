#include "GenericTfIdfDocument.h"
#include "SimpleTfIdfDocument.h"
#include "Corpus.h"
#include "WordCounter.h"

#include <iostream>
#include <utility>
#include "tddFuncs.h"

#include <cmath>

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  std::string text0 = "this this this this this a sample";

  SimpleTfIdfDocument d0("zero",text0);
  SimpleTfIdfDocument d1("one","this a sample sample sample");
  SimpleTfIdfDocument d2("two","wonderful is in in in sample");
  SimpleTfIdfDocument d3("three","wonderful a sample");

  vector<GenericTfIdfDocument *> docs2;
  docs2.push_back(&d0);
  docs2.push_back(&d1);
  docs2.push_back(&d2);
  docs2.push_back(&d3);

  Corpus c2 = Corpus(docs2);
  
  /* |  word       |  Post 0  |  Post 1  |  Post 2  |  Post 3  |  Corpus
     |-------------|----------|----------|----------|----------|--------
     |      this   |    5     |    1     |    0     |     0    |    2
     |        is   |    0     |    0     |    1     |     0    |    1
     |        in   |    0     |    0     |    3     |     0    |    1
     |         a   |    1     |    1     |    0     |     1    |    3
     | wonderful   |    0     |    0     |    1     |     1    |    2
     |    sample   |    1     |    3     |    1     |     1    |    4
  */


  APPROX_EQUALS(1.5051, c2.getTfIdf("this","zero"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("is","zero"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("in","zero"),0.0001);

  ASSERT_EQUALS(text0, d0.getText());
  ASSERT_EQUALS(text0, c2.getDocumentById("zero")->getText());
  ASSERT_EQUALS("zero", c2.getDocumentById("zero")->getId());

  ASSERT_EQUALS(1, c2.getDocWordCount(d0.getId(),"a"));
  ASSERT_EQUALS(3, c2.getNumDocsContainingWord("a"));
  ASSERT_EQUALS(4, c2.getNumDocuments());

  APPROX_EQUALS(log10(4.0/3.0), c2.getIdf("a"),0.0001);

  APPROX_EQUALS(0.1249, c2.getTfIdf("a","zero"),0.0001);



  APPROX_EQUALS(0,      c2.getTfIdf("wonderful","zero"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("sample","zero"),0.0001);

  APPROX_EQUALS(0.3010, c2.getTfIdf("this","one"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("is","one"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("in","one"),0.0001);
  APPROX_EQUALS(0.1249, c2.getTfIdf("a","one"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("wonderful","one"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("sample","one"),0.0001);

  APPROX_EQUALS(0,      c2.getTfIdf("this","two"),0.0001);
  APPROX_EQUALS(0.6021, c2.getTfIdf("is","two"),0.0001);
  APPROX_EQUALS(1.8062, c2.getTfIdf("in","two"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("a","two"),0.0001);
  APPROX_EQUALS(0.3010, c2.getTfIdf("wonderful","two"),0.0001);
  APPROX_EQUALS(0,      c2.getTfIdf("sample","two"),0.0001);

  APPROX_EQUALS(0, c2.getTfIdf("this","three"),0.0001);
  APPROX_EQUALS(0, c2.getTfIdf("is","three"),0.0001);
  APPROX_EQUALS(0, c2.getTfIdf("in","three"),0.0001);
  APPROX_EQUALS(0.1249, c2.getTfIdf("a","three"),0.0001);
  APPROX_EQUALS(0.3010, c2.getTfIdf("wonderful","three"),0.0001);
  APPROX_EQUALS(0, c2.getTfIdf("sample","three"),0.0001);

  return 0;
}
