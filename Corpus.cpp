#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <utility>

#include <iostream>

#include "GenericTfIdfDocument.h"
#include "Corpus.h"

using std::cerr;
using std::endl;

// A Corpus is an indexed collection of Documents
// Documents are indexed by id.  Each document also has a WordCounter,
// tied to it by its id.
// Note: if duplicate ids, last one added with a particular id wins,
//  i.e it replaces the old one.

void Corpus::addDocument(GenericTfIdfDocument * d) {
  // Don't use this syntax; it invokes default constructor first. Ick.
  //   idToDocument[d.getId()] = d;

  // cerr << __FILE__ << ":" << __LINE__ << " Adding " << d->getId() << endl;
  // cerr << __FILE__ << ":" << __LINE__ << " text: " << d->getText() << endl;
    
  std::pair<std::string,GenericTfIdfDocument *> thisPair (d->getId(), d);   
  idToDocument.insert(thisPair);
  
  WordCounter wc(d->getText());
  std::pair<std::string,WordCounter> idWCPair (d->getId(), wc);
  idToWordCounter.insert(idWCPair);
  
  for (auto word: wc) {
    // @@@ STUB... You need to write one line of code to
    // update the numDocsContainingWord variable.  It should be
    // incremented by one for each word in this document.
    // The loop above causes "word" to automatically assume
    // each of those values (i.e. each word in the WordCounter
    // object) one at a time.

    // @@@ ONE LINE OF CODE GOES HERE.
  }

}

Corpus::Corpus(std::vector<GenericTfIdfDocument *> docs)  {
  for (auto d: docs) {
    this->addDocument(d);
  }
}

GenericTfIdfDocument * Corpus::getDocumentById(std::string id) {
  // note: next line throws out_of_range exception if word 
  //  is not in the corpus
  return idToDocument.at(id);
}

int Corpus::getNumDocsContainingWord(std::string word) {
  // note: next line throws out_of_range exception if word 
  //  is not in the corpus
  try {
    return numDocsContainingWord.at(word);
  } catch (std::out_of_range) {
    std::cerr << "ERROR: getNumDocsContainingWord invoked on word not in Corpus: " << word << std::endl;
    exit(5);
  }
}

int Corpus::getNumDocuments() {
  return idToDocument.size();
}

double Corpus::getIdf(std::string word) {
  int numDocs = getNumDocuments();
  int numDocsContainingWord = getNumDocsContainingWord(word);  
  return log10( double( numDocs ) / (double) numDocsContainingWord );
}

double Corpus::getTfIdf(std::string word, std::string id) {
  // @@@ STUB: compute tf and idf, and return their product  
  return -42.12345; // @@@ STUB.
}

double Corpus::getTf(std::string word, std::string id) {
  WordCounter & wc = idToWordCounter.at(id);
  return wc.getWordCount(word);
}
