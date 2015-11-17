#include "RedditPostDownloader.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "RedditPost.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <vector>
#include <cstring>

#include <cstdlib>

#include <unistd.h> // for sleep()
#include <iostream>
using std::cerr;
using std::endl;

std::vector<RedditPost> RedditPostDownloader::getPostsOnce(size_t limit) {


  if (limit > REDDIT_API_MAX_POSTS_PER_GET_REQUEST) {
    throw std::invalid_argument("RedditPostDownloader::getPostsOnce must be called with limit of " + std::to_string(REDDIT_API_MAX_POSTS_PER_GET_REQUEST) + "or less");
  }
  
  // Get the json for the posts from reddit.com using libcurl

  std::string url= this->getURL(limit);
  
  cerr << __FILE__ << ":" << __LINE__ << " this->getURL(limit)= "
       << url << endl;
  
  std::ostringstream oss;
  
  curlpp::Cleanup myCleanup; // constructor/destructor does setup/teardown
  try {
    oss << curlpp::options::Url(url);
  } catch (...) { // ... means "any exception"
    std::cerr << "ERROR: Unable to retrieve url: " << url << std::endl;
    exit(2);
  };

  // Interpret the json using jsoncpp
  std::vector<RedditPost> posts =
    RedditPost::redditJsonPageToRedditPosts(oss.str(), this->urlPagingSuffix, limit, url);
  
  return posts;
}


std::vector<RedditPost> RedditPostDownloader::getPosts() {

  this->count = 0;
  this->urlPagingSuffix = "";
  
  size_t postsLeft = this->limit;
  std::vector<RedditPost> posts;

  bool firstTime=true;
  
  // Until we have as many posts as we need
  while (postsLeft > 0 && this->urlPagingSuffix != "&after=") {    

    int thisCall = std::min<size_t> (postsLeft, size_t(REDDIT_API_MAX_POSTS_PER_GET_REQUEST));
    
    if (this->verbose) { 
      cerr << " In " << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ 
	   << " postsLeft=" << postsLeft << endl; 
    }

    if (firstTime) {
      firstTime = false;
    } else {
      sleep(DELAY_SECONDS); // RATE LIMIT (See: https://github.com/reddit/reddit/wiki/API)
    }

    std::vector<RedditPost> thisPagesPosts = getPostsOnce(thisCall);
    this->count += thisCall;
    
    cerr << __FILE__ << ":" << __LINE__ << " this->urlPagingSuffix=" << this->urlPagingSuffix << endl;

    posts.insert(posts.end(), thisPagesPosts.begin(), thisPagesPosts.end());
    // Do the accounting
    assert( thisPagesPosts.size() <= postsLeft );
    postsLeft -= thisPagesPosts.size();
    
  }
  
  return posts;
}
