#include "GenericTfIdfDocument.h"
#include "SimpleTfIdfDocument.h"
#include "Corpus.h"

#include <iostream>
#include <utility>
#include "tddFuncs.h"
using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;
  
  // These examples of tfIdf come from the Wikipedia page for tfIdf
  // retrieved on 05/27/2015 http://en.wikipedia.org/wiki/Tf-idf
  
  SimpleTfIdfDocument da("alpha","this is a a sample");
  SimpleTfIdfDocument db("beta","this is another another example example example");
  
  vector<GenericTfIdfDocument *> docs1;

  docs1.push_back(&da);
  docs1.push_back(&db);

  Corpus c1 = Corpus(docs1);
  APPROX_EQUALS(0.9030, c1.getTfIdf("example","beta"),0.0001);

  return 0;
}
