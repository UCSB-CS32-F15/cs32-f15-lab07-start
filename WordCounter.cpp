#include "WordCounter.h"
#include <cassert>
#include <sstream>
#include <locale>


size_t WordCounter::getNumWords() const {
  // return the number of words we have added to the map
  return size_t(42); // @@@ STUB   REMOVE THIS COMMENT ALONG WITH THIS LINE
}


int WordCounter::getWordCount(std::string word) const {
  // Try catch because word might not be in the map
  try {
    return 42; // @@@ STUB
    // @@@ replace with invocation of .at member function
    //  on the map object.  Recommmend NOT using [] operator,
    //  since it may have unintended consequences.
  } catch (const std::out_of_range& oor) {
    return 0; // it isn't in map, so "zero".
  }
}

int WordCounter::incrWordCount(std::string word) {
  // add the word to the map if not already there,
  // and if it is, increment its count
  return 42; // @@@ STUB;
}


void WordCounter::addAllWords(std::string text) {

  // http://www.cplusplus.com/reference/locale/ctype/is/
  // http://stackoverflow.com/a/236146/1077990

  std::string word;
  std::istringstream iss(text);
  while( iss >> word ) {
    this->incrWordCount(WordCounter::stripWord(word));
  }  
}


bool WordCounter::isWordChar(char c) {
  return true; // @@ STUB replace with code from lab06
}

std::string WordCounter::stripWord(std::string word) {
  return word + "stub";
  
  // @@@ REPLACE WITH CODE FROM lab06
}


WordCounterIterator WordCounter::begin() const {
  return WordCounterIterator(this->wordToCount.begin());
}

WordCounterIterator WordCounter::end() const {
  return WordCounterIterator(this->wordToCount.end());
}

