#include "RedditPost.h"

std::vector<RedditPost>
RedditPost::redditJsonPageToRedditPosts(std::string jsonForSinglePage, 
					std::string &nextPageUrlSuffix,
					size_t maxPosts,
					std::string metadata) {
  
  std::vector<RedditPost> posts; // empty vector
  std::istringstream iss(jsonForSinglePage);
  
  Json::Value jsonValue;
  iss >> jsonValue;
  
  Json::Value data = jsonValue["data"];
  (void) processChildren(data, posts, maxPosts,metadata);
  std::string after = data["after"].asString();
  nextPageUrlSuffix = "&after=" + after;
  //this is how reddit knows to go to page 2, 3, etc
  
  return posts;
}

std::string RedditPost::convertNumericTimeToString(Json::Value dateValue) {
    double secondsSinceEpochDouble = dateValue.asDouble();
    time_t secondsSinceEpochTime = (time_t) secondsSinceEpochDouble;

    std::locale::global(std::locale("en_US.utf8"));
    char buffer[1024];
    std::strftime(buffer,
		  sizeof(buffer),
		  "%Y-%0m-%0e %0H:%0M",
		  gmtime(&secondsSinceEpochTime));
      
    return std::string(buffer);
  }

size_t RedditPost::processChildren(Json::Value data,
			      std::vector<RedditPost> & posts,
				 size_t & maxPosts,
				 std::string metadata) {
    Json::Value children = data["children"];
    size_t numChildren=0;
    for (Json::Value::iterator it = children.begin();
	 (maxPosts > 0) && (it != children.end()) ; ++it) {
      ++numChildren;
      Json::Value childData = (*it)["data"];
      
      // Skip NSFW and blank posts
      
      if (childData["over_18"].asBool() == false) {
	std::string name = childData["name"].asString();

	
	// @@@ NEXT TWO LINES ARE STUBBED.  You should not have difficulty
	// @@@ figuring out what the correct code should be.  Just
	// @@@ follow the examples of nearby code.  In general,
	// @@@ we could add anything found in the Reddit json to
	// @@@ our object by pulling this out.
	// @@@ AFTER FIXING THE CODE, REMOVE THIS COMMENT BLOCK.
	
	std::string title = "stub title"; // @@@ STUB!
	std::string selftext = "stub selftext"; // @@@ STUB!

	std::string permalink = childData["permalink"].asString();	
	std::string date =
	  convertNumericTimeToString(childData["created_utc"]);
	if (selftext != "") {
	  
	  // @@@ STUB!!!
	  // @@@ Construct a RedditPost instance called rp
	  // passing in the variables :
	  //   name,title,selftext,date,permalink,metadata
	  // @@@ THEN ADD A LINE OF CODE BELOW THIS COMMENT
	  // @@@ THAT ADDS rp to the posts data structure.
	  // @@@ Hint: look at the type of posts, which is an
	  // @@@ argument passed by reference, and look at
	  // @@@ the documentation for that STL datatype.

	  // @@@ Insert rp into posts here.
	  
	  maxPosts--;
	}
      } // if childData
      
    } // for all children
    return numChildren;
  }

std::string RedditPost::toJSON() const {
  std::ostringstream oss;
  Json::Value root;

  // @@@ STUB:  Two important lines of code are missing.
  
  root["name"]=this->name;
  root["title"]=this->title;
  root["date"]=this->date;
  root["permalink"]=this->permalink;

  oss << root;
  return oss.str();
}

std::vector<RedditPost>
RedditPost::simplifiedJsonArrayToRedditPosts(std::string jsonArrayAsString) {

  std::vector<RedditPost> posts; 
  std::istringstream iss(jsonArrayAsString);
  Json::Value array;
  iss >> array;

  int i=0;
  for (auto element : array) {
    ++i;
    std::string name = element["name"].asString();
    std::string title = element["title"].asString();
    std::string selftext = element["selftext"].asString();
    std::string date = element["stub"].asString(); // @@@ STUB
    std::string permalink = "ha ha stub!!!";  // @@@ STUB
    std::string metadata = element["metadata"].asString();
    RedditPost rp(name,title,selftext,date,permalink, metadata);
    posts.push_back(rp);
  }
  
  return posts;
}


std::string RedditPost::toJSONArray(std::vector<RedditPost> posts) {

  std::ostringstream oss;
  
  bool first=true;
  for (auto rp: posts) {
    oss << (first ? "[" : ",") << std::endl;
    first = false;
    oss << rp.toJSON();
  }
  oss << (first ?  "[]" : "\n]" ) << std::endl;
  return oss.str();
}
