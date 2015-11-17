#include <iostream>
#include <utility>
#include "tddFuncs.h"

#include <map>
#include <vector>

#include <string>
#include <cstring>

// for http://en.cppreference.com/w/cpp/container/priority_queue
#include <queue>  

using std::cout;
using std::cerr;
using std::endl;

class TfIdfItem {  
public:

 TfIdfItem() :  // Required to exist by TfIdfHeap class, but should not be used
    tfIdf(-1.0),
    tf(-1),
    idf(-1.0),
    word("invalid"),
    metadata("default constructor for TfIdfItem") {}

 TfIdfItem(  double tfIdf,
	     int tf,
	     double idf,
	     std::string word,
	      std::string metadata
	      ) 
    {} // @@@ STUB.  You must implement this properly.
  
  
  double tfIdf;
  int tf;
  double idf;
  std::string word;
  std::string metadata;
  
  bool operator()( const TfIdfItem & lhs,
		   const TfIdfItem & rhs ) const {

    // Sort on tfIdf.  To break ties, first tf, then word (lexicographic order)
    // @@@ STUB.   Consult WordHeap.h for a model.
    // @@@ You may need two levels of if/else for this one.
    return false;
  }
  
};
  
class TfIdfHeap {  
public:
  TfIdfHeap() {}
  void push( const TfIdfItem & item )  { heap.push(item); }
  TfIdfItem popMax() {
    TfIdfItem item = heap.top();
    heap.pop();
    return item;
  }
  size_t size() { return 1;  } // @@@ STUB!!!
private:
  std::priority_queue<TfIdfItem, std::vector<TfIdfItem>,TfIdfItem> heap;  
};



