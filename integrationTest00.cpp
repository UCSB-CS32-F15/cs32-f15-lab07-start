// integrationTest00.cpp
//   integrate reading reddit JSON into vector<RedditPost>
//      + creating RedditPostVectorTfIdfDocument from vector<RedditPost>
//      + getting string from RedditPostVectorTfIdfDocument
//      + getting string from GenericTfidfDocument
//      + creating WordCounter from string with many words
//      + using heap to get top 10 words.

#include "RedditPost.h"
#include "RedditPostVectorTfIdfDocument.h"
#include "GenericTfIdfDocument.h"
#include "WordCounter.h"
#include "WordHeap.h"

#include <iostream>
#include <fstream>
#include "tddFuncs.h"

#include <vector>
#include <sstream>


using namespace std;

// See: http://stackoverflow.com/questions/7597260/how-to-get-the-tail-of-a-stdstring
std::string lastNChars(std::string str, int n) {
  int startPos = std::max<int>(str.size()-n,0);
  return str.substr(startPos);
}


int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  std::string filename("sampleRedditResultsPage.json");
  std::ifstream ifs(filename);
  if (!ifs) {
    cerr << "ERROR: Could not open: " << filename << endl;
    exit(1);    
  }
  std::stringstream jsonSS;
  jsonSS << ifs.rdbuf();

  std::string urlPagingSuffix;

  std::vector<RedditPost> tenPosts =
    RedditPost::redditJsonPageToRedditPosts(jsonSS.str(),
					    urlPagingSuffix);

  std::string expectedFirstPostTitle = 
    "Reminder: Tomorrow (11/12) Is the Last Day to Change Grading Option for Classes";
  
  ASSERT_EQUALS(size_t(10),tenPosts.size());
  ASSERT_EQUALS("t3_3rlph8",urlPagingSuffix);
  ASSERT_EQUALS_UNLESS(expectedFirstPostTitle,
		       tenPosts[0].getTitle(),
		       tenPosts.size()<1);

  std::vector<RedditPost> posts = 
    RedditPost::redditJsonPageToRedditPosts(jsonSS.str(),
    urlPagingSuffix,100);
  
  ASSERT_EQUALS(size_t(24),posts.size());
  ASSERT_EQUALS("t3_3rlph8",urlPagingSuffix);
  ASSERT_EQUALS_UNLESS(expectedFirstPostTitle,
		       posts[0].getTitle(),
		       posts.size()<1);

  std::string expectedLastPostTitle=
    "It would be very helpful if any of you fellow gauchos would be willing to fill out a relatively quick survey for me. Thanks!!!";
  
  ASSERT_EQUALS_UNLESS(expectedLastPostTitle,
		       posts[23].getTitle(),
		       posts.size()<24);
  std::string expectedLastPostSelftext = "I am currently in a writing class and I need participants for my survey. Thank you!!\nhttps://www.surveymonkey.com/r/GVGMMLH";

  ASSERT_EQUALS_UNLESS(expectedLastPostSelftext,
		       posts[23].getSelftext(),
		       posts.size()<24);
  
  RedditPostVectorTfIdfDocument rpvtd(posts,"dummyDocId");

  std::string rpvtdText = rpvtd.getText();

  ASSERT_EQUALS(expectedFirstPostTitle,
		rpvtdText.substr(0,expectedFirstPostTitle.size()));
  
  // NOTE: extra \n added by transformation to RedditPostVectorTfidfDocument
  expectedLastPostSelftext += "\n"; 
  ASSERT_EQUALS(expectedLastPostSelftext,
		lastNChars(rpvtdText,expectedLastPostSelftext.size()));

  // Must use pointer for GenericTfIdfDocument
  // Can't create an "instance" of a pure virtual abstract class
  
  GenericTfIdfDocument *gdp = &rpvtd;

  std::string gdpText = gdp->getText();

  ASSERT_EQUALS(expectedFirstPostTitle,
		gdpText.substr(0,expectedFirstPostTitle.size()));
  ASSERT_EQUALS(expectedLastPostSelftext,
		lastNChars(gdpText,expectedLastPostSelftext.size()));
   
  WordCounter wc(gdpText);

  ASSERT_EQUALS(46,wc.getWordCount("the"));
  ASSERT_EQUALS(2,wc.getWordCount("survey"));
  ASSERT_EQUALS(1,wc.getWordCount("Gaucho"));

  WordHeap wh;
  
  // Test that we can iterate through without segfaulting
  //   and that number of words matches up after we do
  int countWords = 0;
  for (auto iter=wc.begin(); iter!=wc.end(); ++iter) {
    ++countWords;
    std::string word=*iter;
    int wordCount=wc.getWordCount(word);
    WordItem item(wordCount,word,"testing");
    wh.push(item);
  }
  
  ASSERT_EQUALS(655,countWords);
  ASSERT_EQUALS(size_t(655),wc.getNumWords());
  ASSERT_EQUALS(size_t(655),wh.size());

  // get top five words with their counts
  
  ostringstream oss;
  
  WordItem item;
  for (int i=0; i<5 && wh.size() > 0; i++) {
    item = wh.popMax();
    oss << item.count << "," << item.word << endl;
  }

  std::string expectedTopFive ="46,the\n" 
    "40,I\n"
    "36,to\n"
    "34,a\n"
    "28,and\n";
  ASSERT_EQUALS(expectedTopFive,oss.str());
  
  return 0;
}
