#include "RedditPost.h"

#include <iostream>
#include <fstream>
#include "tddFuncs.h"

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  std::string filename("sampleRedditResultsPage.json");
  std::ifstream ifs(filename);
  if (!ifs) {
    cerr << "ERROR: Could not open: " << filename << endl;
    exit(1);    
  }
  std::stringstream jsonSS;
  jsonSS << ifs.rdbuf();

  std::string urlPagingSuffix;
  
  std::vector<RedditPost> tenPosts =
    RedditPost::redditJsonPageToRedditPosts(jsonSS.str(),
					    urlPagingSuffix);

  std::string expectedFirstPostTitle = 
    "Reminder: Tomorrow (11/12) Is the Last Day to Change Grading Option for Classes";
  
  ASSERT_EQUALS(size_t(10),tenPosts.size());
  ASSERT_EQUALS("t3_3rlph8",urlPagingSuffix);

  if (tenPosts.size() > 0)
    ASSERT_EQUALS(expectedFirstPostTitle,tenPosts[0].getTitle());
  else
    cerr << "ONE TEST SKIPPED AT " __FILE__ ":" << __LINE__ << endl;

  


  std::vector<RedditPost> posts = 
    RedditPost::redditJsonPageToRedditPosts(jsonSS.str(),
    urlPagingSuffix,100);
  
  ASSERT_EQUALS(size_t(24),posts.size());
  ASSERT_EQUALS("t3_3rlph8",urlPagingSuffix);
  if (posts.size() > 0)
    ASSERT_EQUALS(expectedFirstPostTitle,posts[0].getTitle());
  else
    cerr << "ONE TEST SKIPPED AT " __FILE__ ":" << __LINE__ << endl;

  std::string expectedLastPostTitle=
    "It would be very helpful if any of you fellow gauchos would be willing to fill out a relatively quick survey for me. Thanks!!!";

  if (posts.size() >= 24) {
    ASSERT_EQUALS(expectedLastPostTitle,posts[23].getTitle());
    
    std::string expectedLastPostSelftext = "I am currently in a writing class and I need participants for my survey. Thank you!!\nhttps://www.surveymonkey.com/r/GVGMMLH";
    
    ASSERT_EQUALS(expectedLastPostSelftext,
		posts[23].getSelftext());
  } else {
    cerr << "TWO TESTS SKIPPED AT " __FILE__ ":" << __LINE__ << endl;
  }

  return 0;
}
