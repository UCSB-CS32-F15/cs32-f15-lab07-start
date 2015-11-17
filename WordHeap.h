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

class WordItem {  
public:

 WordItem() :  // Required to exist by WordHeap class, but should not be used
  count(-1),
    word("invalid"),
    metadata("default constructor for WordItem") {}

 WordItem( const int count,
	   const std::string word,
	   const std::string metadata
	      ) :
  count(count),
    word(word),
    metadata(metadata) {}
  
  int count;
  std::string word;
  std::string metadata;
  
  bool operator()( const WordItem & lhs,
		   const WordItem & rhs ) const {
    // Sort on count.  Break ties with lexicographic order
    if (lhs.count != rhs.count) return (lhs.count < rhs.count);
    return lhs.word < rhs.word;
  }
  
};
  
class WordHeap {  
public:
  WordHeap() {}
  void push( const WordItem & item )  { heap.push(item); }
  WordItem popMax() {
    WordItem item = heap.top();
    heap.pop();
    return item;
  }
  size_t size() { return heap.size(); }
 private:
  std::priority_queue<WordItem, std::vector<WordItem>,WordItem> heap;  
};



