#include "RedditPost.h"

#include <iostream>
#include <fstream>
#include "tddFuncs.h"

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  std::string filename("sampleSimplifiedReddit.json");
  std::ifstream ifs(filename);
  if (!ifs) {
    cerr << "ERROR: Could not open: " << filename << endl;
    exit(1);    
  }
  std::stringstream jsonSS;
  jsonSS << ifs.rdbuf();

  std::vector<RedditPost> posts =
    RedditPost::simplifiedJsonArrayToRedditPosts(jsonSS.str());
  
  ASSERT_EQUALS(size_t(4),posts.size());
  
  ASSERT_EQUALS("2015-11-13 10:54",posts[0].getDate());
  ASSERT_EQUALS("QUESTION REGARDING PSTAT 109",posts[0].getTitle());
  ASSERT_EQUALS("Hello, I am a freshman in the econ/accounting major and was wondering if PSTAT 109 covers area C of the GE's. I am a little confused because on the general tab in gold, it doesn't say so. Thank you!", posts[0].getSelftext());

  ASSERT_EQUALS("/r/UCSantaBarbara/comments/3slamf/workshops/?ref=search_posts",posts[1].getPermalink());
  ASSERT_EQUALS("2015-11-12 22:45",posts[1].getDate());
  
  ASSERT_EQUALS("2015-11-12 03:55",posts[2].getDate());
  ASSERT_EQUALS("Fulfilling GE Requirements",posts[2].getTitle());
  ASSERT_EQUALS("/r/UCSantaBarbara/comments/3shuxa/fulfilling_ge_requirements/?ref=search_posts",posts[2].getPermalink());
  
  return 0;
}
