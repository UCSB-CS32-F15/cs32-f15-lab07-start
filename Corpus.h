#ifndef CORPUS_H
#define CORPUS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <utility>

#include <iostream>

#include "GenericTfIdfDocument.h"
#include "WordCounter.h"

using std::cerr;
using std::endl;

// A Corpus is an indexed collection of Documents

typedef std::unordered_map<std::string, int> MapStringToInt;


class Corpus {

 public:
  Corpus() {}
  // Note: if duplicate ids, last one added with a particular id wins.
  Corpus(std::vector<GenericTfIdfDocument *> docs);
  GenericTfIdfDocument * getDocumentById(std::string id);
  int getNumDocsContainingWord(std::string word);
  int getNumDocuments();
  double getIdf(std::string word);
  double getTf(std::string word, std::string id);
  double getTfIdf(std::string word, std::string id);

  WordCounter getWordCounter (std::string id) {
    return idToWordCounter.at(id);
  }
  
  int getDocWordCount(std::string id, std::string word) const {
    return -42; // @@@ STUB.   
  };

  void addDocument(GenericTfIdfDocument *d);
  
 private:

  MapStringToInt numDocsContainingWord;
  std::map<std::string, GenericTfIdfDocument *> idToDocument;
  std::map<std::string, WordCounter> idToWordCounter;
  

  void updateNumDocsContainingWord();

};
#endif // CORPUS_H
