#ifndef REDDIT_POST_VECTOR_TFIDF_DOCUMENT_H
#define REDDIT_POST_VECTOR_TFIDF_DOCUMENT_H

#include "RedditPost.h"
#include "GenericTfIdfDocument.h"

#include <sstream>
#include <iostream>

class RedditPostVectorTfIdfDocument: public GenericTfIdfDocument {
public:
 RedditPostVectorTfIdfDocument(std::vector<RedditPost> posts,
			       std::string id) : posts(posts), id(id) {}
  std::vector<RedditPost> posts; // public so we don't need a getter  
  std::string getId() { return "foobar"; } // @@@ STUB 
  std::string getText() {
    std::ostringstream oss;
    for (RedditPost rp: posts) {
      oss << rp.getTitle()+" "+rp.getSelftext() << std::endl;
    }
    return oss.str();
  }
  std::string getMetadata() { return "";} // ok for it to be blank
 private:
  std::string id;
};
#endif
