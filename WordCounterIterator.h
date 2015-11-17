#ifndef WORD_COUNTER_ITERATOR_H
#define WORD_COUNTER_ITERATOR_H

#include <iterator>
#include <map>

// The purpose of the WordCounterIterator is to adapt the iterator
// that is inside the WordCounter object, the one that is for a map,
// and allow it to iterate over strings instead of pairs.

typedef std::map<std::string,int>::const_iterator OurIteratorType;

class WordCounterIterator :
  public std::iterator<std::input_iterator_tag, std::string *> {
  
public:
  
  WordCounterIterator(OurIteratorType iter) :  iter(iter) {}
  
  // prefix e.g.  ++iter
  
  WordCounterIterator & operator++() {
    iter++;
    return (*this);
  }
  
  // (int) is dummy argument to show postfix ++ 
  // e.g. iter++
  /* see   http://www.learncpp.com/cpp-tutorial/97-overloading-the-increment-and-decrement-operators/ ) */
  
  WordCounterIterator operator++( int ) {
    WordCounterIterator tmp(*this); 
    operator++(); 
    return tmp;
  }
  
  bool operator==(const WordCounterIterator& rhs)  {
    return (iter==rhs.iter);
  }
  
  bool operator!=(const WordCounterIterator& rhs) {
    return !( *this == rhs) ;
  }
  
  const std::string & operator*() {
    return iter->first;
  }
  
private:
  // This will be an iterator
  // from the map object inside a WordCounter
  OurIteratorType iter;
};

#endif
