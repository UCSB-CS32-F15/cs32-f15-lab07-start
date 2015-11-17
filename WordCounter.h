#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <iostream>
#include "WordCounterIterator.h"

class WordCounter {
public:
  
  WordCounter(std::string text)  {
    this->addAllWords(text);
  }
  
  size_t getNumWords() const; // returns number of words in vocabulary
  
  int getWordCount(std::string word) const;
  // if word does not exist in vocabulary, return 0, otherwise return count.
  
  // overloaded version that can take a C-string  
  int getWordCount(const char * const word) const {
    return getWordCount(std::string(word));
  }

  int incrWordCount(std::string word);
  
  static bool isWordChar(char c);
  
  static std::string stripWord(std::string word);
  
  //New stuff
  WordCounterIterator begin() const;
  WordCounterIterator end() const;
  
private:
  // For this version of a WordCounter, you must use
  //  an std::map object.   We'll walk you through it.
  
  std::map<std::string, int> wordToCount;
  void addAllWords(std::string text);
  
};

#endif // WORDCOUNTER_H
