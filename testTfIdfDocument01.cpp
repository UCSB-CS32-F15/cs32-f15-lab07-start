#include "GenericTfIdfDocument.h"
#include "SimpleTfIdfDocument.h"
#include "RedditPostTfIdfDocument.h"

#include "tddFuncs.h"
#include <iostream>

using std::cerr;
using std::endl;

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  RedditPost rp("t3_br549","A title","Some text","2015-11-11 21:57","/r/ucsantabarbara/br549/a_title/","test data");
  
  RedditPostTfIdfDocument d(rp);
  GenericTfIdfDocument &gd = d;  

  ASSERT_EQUALS("/r/ucsantabarbara/br549/a_title/",gd.getId());
  ASSERT_EQUALS("A title Some text",gd.getText());
  ASSERT_EQUALS("2015-11-11 21:57",gd.getMetadata());

  return 0;
}

