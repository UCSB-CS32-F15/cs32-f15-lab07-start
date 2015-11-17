#include "GenericTfIdfDocument.h"
#include "SimpleTfIdfDocument.h"
#include "RedditPostVectorTfIdfDocument.h"

#include "tddFuncs.h"
#include <iostream>
#include <vector>


using std::cerr;
using std::endl;

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  
  RedditPost rp0("t3_br540","zero","This","2015-11-11 21:00","/r/ucsantabarbara/br540/a_title/","test rp0");
  RedditPost rp1("t3_br541","one","is","2015-11-11 21:01","/r/ucsantabarbara/br541/a_title/","test rp1");
  RedditPost rp2("t3_br542","two","a","2015-11-11 21:02","/r/ucsantabarbara/br542/a_title/","test rp2");
  RedditPost rp3("t3_br543","three","test.","2015-11-11 21:03","/r/ucsantabarbara/br543/a_title/","test rp3");

  std::vector<RedditPost> rpv;

  rpv.push_back(rp0);
  rpv.push_back(rp1);
  rpv.push_back(rp2);
  rpv.push_back(rp3);

  RedditPostVectorTfIdfDocument rd(rpv,"IdOfBigDoc");

  std::vector<GenericTfIdfDocument *> docs;

  docs.push_back(&rd);
  
  ASSERT_EQUALS("IdOfBigDoc",docs[0]->getId());
  ASSERT_EQUALS("zero This\none is\ntwo a\nthree test.\n",docs[0]->getText());
  ASSERT_EQUALS("",docs[0]->getMetadata());
  
  return 0;
}

