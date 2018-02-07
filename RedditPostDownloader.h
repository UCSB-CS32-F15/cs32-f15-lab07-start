#ifndef REDDIT_POST_DOWNLOADER_H
#define REDDIT_POST_DOWNLOADER_H

#include <vector>
#include <string>
#include <sstream>
#include <json/json.h>
#include <ctime>
#include <set>

#include "RedditPost.h"

#include <algorithm>

#define REDDIT_API_MAX_POSTS_PER_GET_REQUEST 100

class RedditPostDownloader {

public: 
  static constexpr int DEFAULT_MAX_POSTS=10;
  static constexpr int DELAY_SECONDS=2;
  
  static bool isLegalSortValue(const std::string &s) {    
    std::vector<std::string> sortValues{"new","relevance","hot","top","comments"};
    return std::find(sortValues.begin(),sortValues.end(), s) != sortValues.end();
  }
    
  static bool isLegalTimePeriodValue(const std::string &s) {
    std::vector<std::string> timePeriodValues{"all","hour","data","week","month","year"};
    return std::find(timePeriodValues.begin(), timePeriodValues.end(), s) != timePeriodValues.end();
  }
  
  RedditPostDownloader(const std::string subreddit="ucsantabarbara",
		       const std::string sort="new",
		       const std::string timePeriod="all",
		       const size_t limit=DEFAULT_MAX_POSTS,
		       bool verbose=true)  {
    this->setSubreddit(subreddit);
    this->setLimit(limit);
    this->setSort(sort);
    this->setTimePeriod(timePeriod);
    this->verbose=verbose;
  }
    
  void setSubreddit(const std::string subreddit) { this->subreddit = subreddit;}

  void setSort(const std::string sort) { 
    if (!isLegalSortValue(sort)) {
      throw std::invalid_argument(std::string("bad value for sort: ")+sort);
    }
    this->sort = sort;
  }
  
  void setTimePeriod(const std::string timePeriod) {
    if (!isLegalTimePeriodValue(timePeriod)) {
      throw std::invalid_argument(std::string("bad value for timePeriod: ")+timePeriod);
    }    
    this->timePeriod = timePeriod;
  }
  
  void setLimit(const size_t limit) { this->limit = limit;}

  std::string getSubreddit() { return this->subreddit;}
  std::string getSort() { return this->sort;}
  std::string getTimePeriod() { return this->timePeriod;}
  size_t getLimit() { return this->limit;}
  std::string getUrlPagingSuffix() const { return this->urlPagingSuffix; }

  std::string getURL() const {
    return getURL(this->limit);
  }

  // will make only one GET request; may get fewer posts that requested
  std::vector<RedditPost> getPostsOnce() {
    return getPostsOnce(std::min<int>(this->limit, REDDIT_API_MAX_POSTS_PER_GET_REQUEST));
  }


  // may make multiple GET requests, DELAY_SECONDS apart, will get as many posts as requested
  std::vector<RedditPost> getPosts(); 

  
 private:
  std::string subreddit;
  std::string sort;
  std::string timePeriod;
  size_t limit;
  std::string urlPagingSuffix;
  bool verbose;
  size_t count;

  
  // These private versions are for use inside getPosts, where we may want
  // to override the number of posts requested to be something different from
  // this->limit.

  std::vector<RedditPost> getPostsOnce(size_t limitForThisGet); 
  std::string getURL(int limit) const {
    return "http://www.reddit.com/r/" + this->subreddit 
      + "/.json" 
      + "?limit=" + std::to_string(limit)
      + "&count=" + std::to_string(this->count)
      + urlPagingSuffix;
  }

};



#endif
