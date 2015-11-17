#ifndef REDDIT_POST_TFIDF_DOCUMENT_H
#define REDDIT_POST_TFIDF_DOCUMENT_H

#include "RedditPost.h"

class RedditPostTfIdfDocument: public GenericTfIdfDocument
{
public:
 RedditPostTfIdfDocument(const RedditPost &rp) : rp(rp) {}
  const RedditPost &rp;  
  std::string getId() { return rp.getPermalink();}
  std::string getText() { return rp.getTitle()+" "+rp.getSelftext();}
  std::string getMetadata() { return rp.getDate();}
};
#endif
