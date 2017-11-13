#include <iostream>

#include "cstrdeque"
#include "cstrdequeconst"

using namespace std;

#ifndef NDEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

static void print_debug(string const& debug_message) {
  if (debug) {
    cerr << debug_message << endl;
  }
}

static bool &initialized() {
  static bool in = false;
  return in;
}

unsigned long jnp1::emptystrdeque() {
  static int number = ::jnp1::strdeque_new();
  if (!initialized()) {
    print_debug("Unique empty queue initialized");
    initialized() = true;
  }
  return number;
}
