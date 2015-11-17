#include "RedditPost.h"

#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  RedditPost rp("t3_br549","A title","Some text","2015-11-11 21:57","/r/ucsantabarbara/br549/a_title/","test data");

  std::string expected=
    "\n{\n"
    "\t\"date\" : \"2015-11-11 21:57\",\n"
    "\t\"metadata\" : \"test data\",\n"
    "\t\"name\" : \"t3_br549\",\n"
    "\t\"permalink\" : \"/r/ucsantabarbara/br549/a_title/\",\n"
    "\t\"selftext\" : \"Some text\",\n" 
    "\t\"title\" : \"A title\"\n"
    "}\n";
  
  ASSERT_EQUALS(expected,rp.toJSON());

  return 0;
}
