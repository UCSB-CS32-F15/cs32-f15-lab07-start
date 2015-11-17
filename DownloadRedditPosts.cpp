#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


#include "RedditPost.h"
#include "RedditPostDownloader.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <vector>
#include <cstring>

using std::cout;
using std::cerr;
using std::endl;

#include <cstdlib>


const size_t DEFAULT_numPosts = 100;
const std::string DEFAULT_subreddit = "ucsantabarbara";

void usage(int argc, char *argv[]) {

  cerr << argv[0] << "  Gets specified number of reddit posts from specified"
       << " subreddit using Reddit API and dumps results to stdout in "
       << " simplified json format as an array.\n\n"
       << "Uses paging to make multiple requests, respecting Reddit's rate limit.\n"
       << endl;
    
  cerr << "Usage: " << argv[0] << " numPosts subreddit sort timePeriod\n"
       << "  numPosts   default " << DEFAULT_numPosts << "\n"
       << "  subreddit  default " << DEFAULT_subreddit << "\n"
       << "  sort       default new  (or relevance, hot, top, comments)\n"
       << "  timePeriod default all  (or hour, day, week, month, year)\n"
       << endl;
  
}

int main(int argc, char * argv[]) {
  
  cerr << "Running from: " << __FILE__ << endl;

  size_t numPosts = DEFAULT_numPosts;
  std::string subreddit = DEFAULT_subreddit;
  std::string sort = "new";
  std::string timePeriod = "all";

  if (argc > 1 && ( !strcmp(argv[1],"-h") || !strcmp(argv[1],"--help") ) ) {
    usage(argc, argv);  exit(1);
  }

  if (argc > 1) {  numPosts = (size_t)(atoi(argv[1])); }
  if (argc > 2) {  subreddit = std::string(argv[2]); }
  if (argc > 4) {  sort = std::string(argv[3]); }
  if (argc > 3) {  timePeriod = std::string(argv[4]); }

  cerr << "Getting " << numPosts << " posts from " << subreddit 
       << "\t with sort " << sort << " and timePeriod " << timePeriod
       << endl;

  RedditPostDownloader rpd(subreddit,sort,timePeriod,numPosts);
  cerr << "Url =" << rpd.getURL() << endl;
  std::vector<RedditPost> posts = rpd.getPosts();
  cout << RedditPost::toJSONArray(posts) << endl;
  	
  return 0;
}
