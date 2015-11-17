#include "tddFuncs.h"
#include <iostream>
#include <cstring>
using std::cerr;
using std::endl;

void assertEquals(const char * const expected, 
		  const char * const actual, 
		  std::string message) {
  if ( !strcmp(expected,actual) ) {  // if they are equal
    cerr << "PASSED: " << message << endl;;
  } else {
    cerr << "   FAILED: " << message << endl 
	 << "     Expected: " << expected << " Actual: " << actual << endl; 
  }
}



void approxEquals(double expected, 
			      double actual, 
				  double tolerance,
				  std::string message) {
  if (fabs(expected-actual) <= tolerance) {
    std::cerr << "PASSED: " << message << std::endl;;
  } else {
    std::cerr << "   FAILED: " << message << std::endl
	      << "     Expected: "  << expected << " Actual: " << actual << " Tolerance: " << tolerance << std::endl; 
  }
}


void assertEquals(const char * const expected, 
		  std::string actual, 
		  std::string message) {
  assertEquals(std::string(expected),actual,message);
}

void assertTrue(bool expression,
		  std::string message) {
  if (expression) {
    cerr << "PASSED: " << message << endl;;
  } else {
    cerr << "   FAILED: " << message << endl 
	 << "     Expected true, but was false " << endl;
  }
}

