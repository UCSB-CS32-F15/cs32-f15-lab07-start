
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


#include "RedditPost.h"
#include "RedditPostDownloader.h"
#include "UCSubreddits.h"

#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <vector>
#include <cstring>

#include <boost/filesystem.hpp>

using std::cout;
using std::cerr;
using std::endl;

#include <cstdlib>


const size_t DEFAULT_numPosts = 100;

void usage(int argc, char *argv[]) {

  cerr << argv[0] << "  Gets specified number of reddit posts from subreddit\n"
       << " for each of the nine undergrad UC campuses.  Stores data in \n"
       << " subdirectory called data, which is created if it doesn't already exist.\n"
       << " simplified json format as an array.\n\n"
       << "Uses paging to make multiple requests, respecting Reddit's rate limit.\n"
       << endl;
    
  cerr << "Usage: " << argv[0] << " numPosts sort timePeriod\n"
       << "  numPosts   default " << DEFAULT_numPosts << "\n"
       << "  sort       default new  (or relevance, hot, top, comments)\n"
       << "  timePeriod default all  (or hour, day, week, month, year)\n"
       << endl;
  
}

int main(int argc, char * argv[]) {
  
  cerr << "Running from: " << __FILE__ << endl;

  size_t numPosts = DEFAULT_numPosts;
  std::string sort = "new";
  std::string timePeriod = "all";

  if (argc > 1 && ( !strcmp(argv[1],"-h") || !strcmp(argv[1],"--help") ) ) {
    usage(argc, argv);  exit(1);
  }

  if (argc > 1) {  numPosts = (size_t)(atoi(argv[1])); }
  if (argc > 2) {  sort = std::string(argv[2]); }
  if (argc > 3) {  timePeriod = std::string(argv[3]); }

  cerr << "Getting " << numPosts << " posts for each subreddit\n" 
       << "\t with sort " << sort << " and timePeriod " << timePeriod
       << endl;
  
  std::string dirname="data/" + std::to_string(numPosts);

  if (!boost::filesystem::is_directory(dirname)) {
    boost::filesystem::path dir(dirname);
    if(boost::filesystem::create_directories(dir)) {
      std::cerr << "Created " << dirname << std::endl;
    } else {
      cerr << "ERROR: Unable to make data subdirectory" << endl;
      exit(3);    
    }
  }
  
  UCSubreddits ucsrs;
      
  for (auto uc: ucsrs.ucSubreddits) {  
    RedditPostDownloader rpd(uc,sort,timePeriod,numPosts);
    cerr << "Url =" << rpd.getURL() << endl;
    std::vector<RedditPost> posts = rpd.getPosts();

    std::string filename = dirname+"/"+uc+".txt";
    std::ofstream of(filename);
    if (!of) {
      cerr << "Could not open " << filename << endl;
      exit(4);
    }	     
    of << RedditPost::toJSONArray(posts) << endl;
    of.close();
    cerr << "Wrote " << posts.size() << " posts to " << filename << endl;
  }
  return 0;
}
