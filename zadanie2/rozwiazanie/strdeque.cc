#include <cassert>
#include <climits>
#include <deque>
#include <iostream>
#include <map>
#include <utility>

#include "cstrdeque"
#include "cstrdequeconst"

using namespace std;

#ifndef NDEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

typedef deque<string> str_deque;
typedef map<unsigned long, str_deque> str_deques_map;
typedef str_deques_map::iterator iter;

namespace {

static str_deques_map& deques() {
  static str_deques_map map;
  return map;
}

static void print_debug(string const& debug_message) {
  if (debug) {
    cerr << debug_message << endl;
  }
}

static bool& free_ids() {
  static bool c = true;
  return c;
}

unsigned long give_free_key() {
  static unsigned long next_free_id = 0;

  if (next_free_id == deques().max_size() - 1 || 
      next_free_id == ULONG_MAX) {
    free_ids() = false;
  }

  return next_free_id++;
}
}

unsigned long jnp1::strdeque_new() {
  assert(free_ids());
  unsigned long key = give_free_key();

  deques()[key];
  print_debug("Created a new deque no " + to_string(key));
  return key;
}

void jnp1::strdeque_delete(unsigned long id) {
  iter deque = deques().find(id);

  if (id == ::jnp1::emptystrdeque()) {
    print_debug("Tried to delete the const deque"
                " no " + to_string(id));
    return;
  }

  if (deque == deques().end()) {
    print_debug("Tried to delete a non-existing deque"
                " no " + to_string(id));
    return;
  }

  deques().erase(deque);
  print_debug("Deleted a deque no " + to_string(id));
}

size_t jnp1::strdeque_size(unsigned long id) {
  iter deque = deques().find(id);

  if (deque == deques().end()) {
    print_debug("Chcecked the size of a non-existing deque"
                " no " + to_string(id));
    return 0;
  }

  size_t ret = deque->second.size();
  print_debug("Size of a deque no " + to_string(id) + 
              " is " + to_string(ret));
  return ret;
}

void jnp1::strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
  if (value == NULL) {
    print_debug("Attempted to insert NULL into a deque"
                " no " + to_string(id));
    return;
  }

  if (id == ::jnp1::emptystrdeque()) {
    print_debug("Attempted to insert into the const deque");
    return;
  }

  iter deque = deques().find(id);

  if (deque == deques().end()) {
    print_debug("Attempted to insert into a non-existing deque"
                " no " + to_string(id));
    return;
  }

  size_t size = deque->second.size();

  if (pos >= size) {
    pos = size;
  }

  str_deque::iterator place = deque->second.begin() + pos;
  deque->second.insert(place, string(value));
  print_debug("Inserted on a position " + to_string(pos) + 
              " in deque no " + to_string(id));
}

void jnp1::strdeque_remove_at(unsigned long id, size_t pos) {
  if (id == ::jnp1::emptystrdeque()) {
    print_debug("Attempted to remove from the const deque");
    return;
  }

  iter deque = deques().find(id);

  if (deque == deques().end()) {
    print_debug("Attempted to remove from a non-existing deque"
                " no " + to_string(id));
    return;
  }

  if (pos >= deque->second.size() && pos != 0) {
    print_debug("Attempted to remove from a non-existing position "
                "in deque no " + to_string(id));
    return;
  }

  deque->second.erase(deque->second.begin() + pos);
  print_debug("Removed an element from a position " + to_string(pos) +
              " in deque no " + to_string(id));
  return;
}

const char* jnp1::strdeque_get_at(unsigned long id, size_t pos) {
  iter deque = deques().find(id);

  if (deque == deques().end()) {
    print_debug("Attempted to get a string from a non-existing deque"
                " no " + to_string(id));
    return NULL;
  }

  if (id == ::jnp1::emptystrdeque()) {
    print_debug("Attempted to get a string from the const deque");
    return NULL;
  }

  if (pos >= deque->second.size() && pos != 0) {
    print_debug("Attempted to get a pointer to a non-existing string"
                " no " + to_string(pos) +
                " in deque no " + to_string(id));
    return NULL;
  }

  print_debug("Got a pointer to a deque no " + to_string(id) +
              " on position " + to_string(pos));
  return deque->second[pos].c_str();
}

void jnp1::strdeque_clear(unsigned long id) {
  if (id == ::jnp1::emptystrdeque()) {
    print_debug("Attempted to clear the const deque");
    return;
  }

  iter deque = deques().find(id);

  if (deque == deques().end()) {
    print_debug("Attempted to clear a non-existing deque"
                " no " + to_string(id));
    return;
  }

  deque->second.clear();
  print_debug("Cleared a deque no " + to_string(id));
}

int jnp1::strdeque_comp(unsigned long id1, unsigned long id2) {
  str_deque deque1 = deques().count(id1) > 0
                       ? deques().find(id1)->second
                       : deques().find(::jnp1::emptystrdeque())->second;
  str_deque deque2 = deques().count(id2) > 0
                       ? deques().find(id2)->second
                       : deques().find(::jnp1::emptystrdeque())->second;

  if (deque1 < deque2) {
    print_debug("Deque no " + to_string(id1) + 
                " is smaller than deque no " + to_string(id2));
    return -1;
  } else if (deque1 > deque2) {
    print_debug("Deque no " + to_string(id1) + 
                " is bigger than deque no " + to_string(id2));
    return 1;
  }

  print_debug("Deque no " + to_string(id1) + 
              " is equal to deque no " + to_string(id2));
  return 0;
}
