#ifndef TDDFUNCS_H
#define TDDFUNCS_H

#include <math.h>
#include <string>
#include <iostream>

// template requires == and << 

template<typename T> void assertEquals(T expected, 
				       T actual, 
				       std::string message) {
  if (expected==actual) {
    std::cout << "PASSED: " << message << std::endl;;
  } else {
    std::cout << "   FAILED: " << message << std::endl
	      << "     Expected: "  << expected << " Actual: " << actual << std::endl; 
  }
}

void approxEquals(double expected, 
			      double actual, 
				  double tolerance,
				  std::string message);

// specialized because char * doesn't work properly on ==
void assertEquals(const char * const expected, 
		  const char * const actual, 
		  std::string message);

// specialized for the same reason, and because expected is often a string literal
void assertEquals(const char * const expected, 
		  std::string actual, 
		  std::string message);

#define ASSERT_EQUALS(expected,actual) \
    assertEquals(expected,actual,#actual)

#define APPROX_EQUALS(expected,actual,tolerance) \
    approxEquals(expected,actual,tolerance,#actual)

void assertTrue(bool expression, std::string message="");

#define ASSERT_TRUE(expression) assertTrue(expression,#expression)

#endif // TDDFUNCS_H
