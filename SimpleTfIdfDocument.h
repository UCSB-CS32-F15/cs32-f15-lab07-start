#ifndef SIMPLE_TFIDF_DOCUMENT_H
#define SIMPLE_TFIDF_DOCUMENT_H

#include "GenericTfIdfDocument.h"

class SimpleTfIdfDocument: public GenericTfIdfDocument
{
public:
  SimpleTfIdfDocument(std::string id,
		      std::string text,
		      std::string metadata="") :
    id(id),
    text(text),
    metadata(metadata) {}
  
  std::string getId() { return this->id;}
  std::string getText() { return "stub";} // @@@ DO THE RIGHT THING
  std::string getMetadata() { return this->metadata;}
  
private:
  
  std::string id;
  std::string text;
  std::string metadata;
};
#endif
