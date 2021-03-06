#include "RedditPost.h"
#include "GenericTfIdfDocument.h"
#include "RedditPostVectorTfIdfDocument.h"
#include "Corpus.h"
#include "WordCounter.h"

#include <iostream>
#include <utility>
#include "tddFuncs.h"

#include <cmath>

#include "UCSubreddits.h"
#include <map>
#include <vector>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <cstring>

#include "TfIdfHeap.h"


using std::cout;
using std::cerr;
using std::endl;



int main(int argc, char *argv[]) {

  std::string numPosts("10");
  int numWords(10);
  std::string urlPrefix("http://www.cs.ucsb.edu/~pconrad/cs32/15F/labs/lab07/data/");

  if (argc > 1 && ( !strcmp("-h",argv[1]) || !strcmp("--help",argv[1]) ) ) {
    cerr << "Usage: " << argv[0] << " numPosts numWords urlPrefix" << endl;
    exit(1);
  }
    
  if (argc>1) numPosts = std::string(argv[1]);
  if (argc>2) numWords = atoi(argv[2]);
  if (argc>3) urlPrefix = std::string(argv[3]);

  cerr << "Running from: " << __FILE__ << endl;
  cerr << "Computing top " << numWords<< " by tfIdf score for all UCs" << endl;
  cerr << " using data from " << urlPrefix << endl;

  UCSubreddits ucsr;

  std::vector<GenericTfIdfDocument *> docs;
  
  for (std::string thisUC: ucsr.ucSubreddits ) {
    cerr << "Getting posts for " << thisUC << endl;
    std::string nextPageID;

    std::string url = std::string("") + urlPrefix + "/"
      + numPosts + "/" + thisUC + ".txt";

    std::ostringstream oss;
    curlpp::Cleanup myCleanup;
    oss << curlpp::options::Url(url);

    std::vector<RedditPost> posts=
      RedditPost::simplifiedJsonArrayToRedditPosts(oss.str());
      
    RedditPostVectorTfIdfDocument *dp = new RedditPostVectorTfIdfDocument(posts,thisUC);
    //cerr << __FILE__ << ":" << __LINE__ << " dp->getText()=" << dp->getText() << endl;
    GenericTfIdfDocument *gp = dp;
    docs.push_back(gp);
    //cerr << __FILE__ << ":" << __LINE__ << " gp->getText()=" << gp->getText() << endl;
  }

  Corpus c;
  for (auto d: docs) {
    //  cerr << __FILE__ << ":" << __LINE__ << " d->getId()=" << d->getId() << endl;
    // cerr << __FILE__ << ":" << __LINE__ << " d->getText()=" << d->getText() << endl;
    c.addDocument(d);
  }
  

  
  for (std::string uc: ucsr.ucSubreddits ) {    
    // now item is a pair<std::string, std::vector<Document> >
    //  and item.first is the uc, and item.second is the vector
    
    WordCounter thisUCWordCounter = c.getWordCounter(uc);
    TfIdfHeap thisUCTfIdfs;
    
    for (auto word: thisUCWordCounter) {
      TfIdfItem item(c.getTfIdf(word,uc),
		     c.getTf(word,uc),
		     c.getIdf(word),
		     word,
		     uc);
      thisUCTfIdfs.push(item);
    }
    
    for (int i=0; i < numWords && thisUCTfIdfs.size() > 0 ; i++) {
      TfIdfItem item =  thisUCTfIdfs.popMax(); 
      cout << item.metadata << ","
	   << item.tfIdf << ","
	   << item.word << endl;
    }
  }

  for (auto p: docs) {
    delete p;
  }
  
  return 0;
}
