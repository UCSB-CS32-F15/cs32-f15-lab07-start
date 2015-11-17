#ifndef REDDIT_POST_H
#define REDDIT_POST_H

#include <vector>
#include <string>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <ctime>
#include <set>

class RedditPost {

 public:
 RedditPost(std::string name,
	    std::string title,
	    std::string selftext,
	    std::string date,
	    std::string permalink,
	    std::string metadata) :
  name(name),
    title(title),
    selftext(selftext),
    date(date),
    permalink(permalink),
    metadata(metadata) {}

  std::string getName() const { return this->name;}
  std::string getTitle() const { return this->title;}
  std::string getSelftext() const { return this->selftext;}
  std::string getDate() const { return this->date;}
  std::string getPermalink() const { return this->permalink;}
  std::string getMetadata() const { return this->metadata;}
  
  std::string toJSON() const;

  static std::string toJSONArray(std::vector<RedditPost> posts);
  
  static constexpr int MAX_POSTS=10;

  // There are two JSON formats that we consider.

  // (1) redditJson is the format used by the Reddit API.
  //     It contains every field that Reddit makes available.

  // (2) simpliedJson is our own format used to serialize RedditPosts.
  //     It includes a subset of fields that we consider interesting.

  // nextPageUrlSuffix is the suffix to append to the next URL
  // to get to the correct post 
  
  static std::vector<RedditPost>
    redditJsonPageToRedditPosts(std::string jsonForSinglePageAsString,
				std::string &nextPageURLSuffix,
				size_t maxPosts=MAX_POSTS,
				std::string metadata="");
  static std::vector<RedditPost>
    simplifiedJsonArrayToRedditPosts(std::string jsonArrayAsString);
  
  static std::string
    convertNumericTimeToString(Json::Value dateValue);


 private:
  std::string name;
  std::string title;
  std::string selftext;
  std::string date;
  std::string permalink;
  std::string metadata;
  
  static size_t processChildren(Json::Value data,
			      std::vector<RedditPost> & posts,
			      size_t & maxPosts,
			      std::string metadata="");
    

};

#endif
