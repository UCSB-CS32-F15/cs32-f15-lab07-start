#include "GenericTfIdfDocument.h"
#include "RedditPostTfIdfDocument.h"
#include "RedditPostVectorTfIdfDocument.h"
#include "Corpus.h"
#include "WordCounter.h"

#include <iostream>
#include <utility>
#include "tddFuncs.h"

#include <cmath>

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  RedditPost rp0("t3_br540","zero","This","2015-11-11 21:00","/r/ucsantabarbara/br540/a_title/","");
  RedditPost rp1("t3_br541","one","is","2015-11-11 21:01","/r/ucsantabarbara/br541/a_title/","");
  RedditPost rp2("t3_br542","two","a","2015-11-11 21:02","/r/ucr/br542/a_title/","");
  RedditPost rp3("t3_br543","three","test.","2015-11-11 21:03","/r/ucr/br543/a_title/","");

  std::vector<RedditPost> rpvUCSB;
  std::vector<RedditPost> rpvUCR;

  rpvUCSB.push_back(rp0);
  rpvUCSB.push_back(rp1);
  rpvUCR.push_back(rp2);
  rpvUCR.push_back(rp3);

  RedditPostVectorTfIdfDocument rdUCSB(rpvUCSB,"UCSB");
  RedditPostVectorTfIdfDocument rdUCR(rpvUCR,"UCR");

  std::vector<GenericTfIdfDocument *> docs;

  docs.push_back(&rdUCSB);
  docs.push_back(&rdUCR);

  Corpus c2 = Corpus(docs);

  try {
    ASSERT_EQUALS("UCSB", c2.getDocumentById("UCSB")->getId());
    ASSERT_EQUALS("UCR", c2.getDocumentById("UCR")->getId());
    
    ASSERT_EQUALS("zero This\none is\n",
		  c2.getDocumentById("UCSB")->getText());
    
    ASSERT_EQUALS("two a\nthree test.\n",
		  c2.getDocumentById("UCR")->getText());
    
    APPROX_EQUALS(1, c2.getTf("This","UCSB"),0.0001);
    APPROX_EQUALS(0.30103, c2.getIdf("This"),0.0001);
    APPROX_EQUALS(0.30103, c2.getTfIdf("This","UCSB"),0.0001);
  } catch (std::out_of_range oor) {
    cerr << "FAILURE: test failed with std::out_of_range error" << endl;
  }
  return 0;
}
