#include "GenericTfIdfDocument.h"
#include "SimpleTfIdfDocument.h"
#include "RedditPostTfIdfDocument.h"

#include "tddFuncs.h"
#include <iostream>
#include <vector>


using std::cerr;
using std::endl;

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  SimpleTfIdfDocument sd("doc00","This is some text","Some metadata");
  RedditPost rp("t3_br5649","A title","Some text","2015-11-11 21:57","/r/ucsantabarbara/br549/a_title/","test data");
  
  RedditPostTfIdfDocument rd(rp);

  std::vector<GenericTfIdfDocument *> docs;

  docs.push_back(&sd);
  docs.push_back(&rd);
  
  ASSERT_EQUALS("doc00",docs[0]->getId());
  ASSERT_EQUALS("This is some text",docs[0]->getText());
  ASSERT_EQUALS("Some metadata",docs[0]->getMetadata());
  
  ASSERT_EQUALS("/r/ucsantabarbara/br549/a_title/",docs[1]->getId());
  ASSERT_EQUALS("A title Some text",docs[1]->getText());
  ASSERT_EQUALS("2015-11-11 21:57",docs[1]->getMetadata());
  
  
  return 0;
}

