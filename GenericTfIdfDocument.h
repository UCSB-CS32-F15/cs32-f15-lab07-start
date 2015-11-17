#ifndef GENERIC_TFIDF_DOCUMENT_H
#define GENERIC_TFIDF_DOCUMENT_H

#include <string>

class GenericTfIdfDocument
{
 public:
  virtual std::string getId() = 0; // unique identifier
  virtual std::string getText() = 0; // the text to index
  virtual std::string getMetadata() = 0; // may be blank; not used in tfIdf.  Could be date, for example.
  virtual ~GenericTfIdfDocument() = 0;
};

inline GenericTfIdfDocument::~GenericTfIdfDocument() {}

#endif
