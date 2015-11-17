#include "GenericTfIdfDocument.h"
#include "SimpleTfIdfDocument.h"

#include "tddFuncs.h"
#include <iostream>

using std::cerr;
using std::endl;

using namespace std;

int main() {
  cerr << "Running tests from: " << __FILE__ << endl;

  SimpleTfIdfDocument d("doc00","This is some text","Some metadata");

  ASSERT_EQUALS("doc00",d.getId());
  ASSERT_EQUALS("This is some text",d.getText());
  ASSERT_EQUALS("Some metadata",d.getMetadata());

  GenericTfIdfDocument &gd = d;
  
  ASSERT_EQUALS("doc00",gd.getId());
  ASSERT_EQUALS("This is some text",gd.getText());
  ASSERT_EQUALS("Some metadata",gd.getMetadata());

  return 0;
}
