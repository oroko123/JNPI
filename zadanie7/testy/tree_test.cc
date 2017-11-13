// Opis testów
// grupa 1 przykład z treści zadania
// grupa 2 leniwość
// grupa 3 mapowanie na inny typ
// grupa 4 accumulate i fold
// grupa 5 bst
// grupa 6 pozostałe testy i przykłady z forum

// Najpierw sprawdzamy, czy tree.h włącza wszystkie potrzebne pliki nagłówkowe.
#include "tree.h"

#include <cassert>
#include <string>

#if TEST_NUM == 100

#include <sstream>

#else

using namespace std;

#endif

#if TEST_NUM >= 200 && TEST_NUM <= 202

static int call_counter = 0;

static int increment(int x) {
  ++call_counter;
  return x + 1;
}

#endif

int main() {
  #if TEST_NUM == 100
  static const std::string correct_cout_1(
    "1 2 3 4 5\n"
    "3 1 2 5 4\n"
    "2 1 4 5 3\n"
    "size: 5\n"
    "height: 3\n"
    "bst: 1\n"
    "custom print: 1:2:3:4:5:\n"
    "-2: -1 0 1 2 3\n"
    "-4: -3 -2 -1 0 1\n"
    "odd: -1 1 3\n"
    "sum: 15\n"
    "sum: 15\n"
  );
  static const std::string correct_cout_2(
    "1 2 3 4 5 \n"
    "3 1 2 5 4 \n"
    "2 1 4 5 3 \n"
    "size: 5\n"
    "height: 3\n"
    "bst: 1\n"
    "custom print: 1:2:3:4:5:\n"
    "-2: -1 0 1 2 3 \n"
    "-4: -3 -2 -1 0 1 \n"
    "odd: -1 1 3 \n"
    "sum: 15\n"
    "sum: 15\n"
  );
  static const std::string correct_cout_3(
    "1 2 3 4 5 \b\n"
    "3 1 2 5 4 \b\n"
    "2 1 4 5 3 \b\n"
    "size: 5\n"
    "height: 3\n"
    "bst: 1\n"
    "custom print: 1:2:3:4:5:\n"
    "-2: -1 0 1 2 3 \b\n"
    "-4: -3 -2 -1 0 1 \b\n"
    "odd: -1 1 3 \b\n"
    "sum: 15\n"
    "sum: 15\n"
  );

  std::streambuf* oldCoutStreamBuffer = std::cout.rdbuf();
  std::ostringstream capturedCout;
  std::cout.rdbuf(capturedCout.rdbuf());

  auto two = Tree<int>::createValueNode(2);
  auto one = Tree<int>::createValueNode(1, Tree<int>::createEmptyNode(), two);
  auto four = Tree<int>::createValueNode(4);
  auto five = Tree<int>::createValueNode(5,
                                         Tree<int>::createValueNode(4),
                                         Tree<int>::createEmptyNode());
  auto root = Tree<int>::createValueNode(3, one, five);
  Tree<int> tree(root);

  tree.print(Tree<int>::inorder);
  tree.print(Tree<int>::preorder);
  tree.print(Tree<int>::postorder);

  std::cout << "size: " << tree.size() << std::endl;
  std::cout << "height: " << tree.height() << std::endl;
  std::cout << "bst: " << tree.is_bst() << std::endl;

  std::cout << "custom print: ";
  tree.apply([](int e){std::cout << e << ":";}, Tree<int>::inorder);
  std::cout << std::endl;

  int x = 2;
  Tree<int> minus_x = tree.map([&](int e)->int{return e - x;});
  Tree<int> lazy_minus_x = tree.lazy_map([&](int e)->int{return e - x;});
  x = 4;
  std::cout << "-2: ";
  minus_x.print();
  std::cout << "-4: ";
  lazy_minus_x.print();

  Tree<int> odd = minus_x.filter([](int e)->bool{return (e & 1) == 1;});
  std::cout << "odd: ";
  odd.print();

  int sum1 = tree.accumulate(std::plus<int>(), 0, Tree<int>::inorder);
  std::cout << "sum: " << sum1 << std::endl;

  int sum2 = tree.fold([](int val, int l, int r)->int{return val + l + r;}, 0);
  std::cout << "sum: " << sum2 << std::endl;

  assert(capturedCout.str() == correct_cout_1 ||
         capturedCout.str() == correct_cout_2 ||
         capturedCout.str() == correct_cout_3 );

  std::cout.rdbuf(oldCoutStreamBuffer);
  #endif

  #if TEST_NUM == 200
  Tree<int> A(Tree<int>::createValueNode(1));
  assert(call_counter == 0);

  Tree<int> B = A.map(increment);
  assert(call_counter == 1);

  Tree<int> C = B.map(increment);
  assert(call_counter == 2);

  C.apply([&](int x){assert(x == 3);}, Tree<int>::inorder);
  assert(call_counter == 2);

  C.apply([&](int x){assert(x != 1);}, Tree<int>::inorder);
  assert(call_counter == 2);

  A.apply([&](int x){assert(x == 1);}, Tree<int>::inorder);
  B.apply([&](int x){assert(x == 2);}, Tree<int>::inorder);
  #endif

  #if TEST_NUM == 201
  Tree<int> A(Tree<int>::createValueNode(1));
  assert(call_counter == 0);

  Tree<int> B = A.lazy_map(increment);
  assert(call_counter == 0);

  Tree<int> C = B.lazy_map(increment);
  assert(call_counter == 0);

  C.apply([&](int x){assert(x == 3);}, Tree<int>::inorder);
  assert(call_counter == 2);

  C.apply([&](int x){assert(x != 1);}, Tree<int>::inorder);
  assert(call_counter == 2);

  A.apply([&](int x){assert(x == 1);}, Tree<int>::inorder);
  B.apply([&](int x){assert(x == 2);}, Tree<int>::inorder);
  #endif

  #if TEST_NUM == 202
  Tree<int> A(Tree<int>::createValueNode(1,
                                         Tree<int>::createValueNode(0),
                                         Tree<int>::createEmptyNode()));
  Tree<int> B = A.lazy_map(increment);
  assert(call_counter == 0);

  B.apply([&](int x){assert(x == call_counter);}, Tree<int>::inorder);
  assert(call_counter == 2);
  #endif

  #if TEST_NUM == 203
  Tree<int> A(Tree<int>::createValueNode(1));
  int v = 2;
  Tree<int> B = A.lazy_map([&](int x)->int{return x - v;});
  B.apply([&](int x){assert(x == -1);}, Tree<int>::inorder);
  v = 6;
  B.apply([&](int x){assert(x == -1);}, Tree<int>::inorder);
  #endif

  #if TEST_NUM == 300
  Tree<int> A(Tree<int>::createValueNode(-1));
  Tree<unsigned> B = A.map([](int x)->unsigned{return (unsigned)x;});
  B.apply([](unsigned x){assert(x == 4294967295);}, Tree<unsigned>::inorder);
  #endif

  #if TEST_NUM == 301
  Tree<int> A(Tree<int>::createValueNode(-1));
  Tree<unsigned> B = A.lazy_map([](int x)->unsigned{return (unsigned)x;});
  B.apply([](unsigned x){assert(x == 4294967295);}, Tree<unsigned>::inorder);
  #endif

  #if TEST_NUM == 400
  Tree<int> tree(Tree<int>::createValueNode(3,
                                            Tree<int>::createValueNode(5),
                                            Tree<int>::createValueNode(7)));
  int v = tree.accumulate([](int x, int y)->int{return x - y;},
                          0,
                          Tree<int>::preorder);
  assert(v == -15);
  #endif

  #if TEST_NUM == 401
  Tree<int> tree(Tree<int>::createValueNode(3,
                                            Tree<int>::createValueNode(5),
                                            Tree<int>::createValueNode(7)));
  int v = tree.accumulate([](int x, int y)->int{return y - x;},
                          0,
                          Tree<int>::postorder);
  assert(v == 1);
  #endif

  #if TEST_NUM == 402
  static const int values[] = {5, 7, 3};
  size_t i = 0;
  Tree<int> tree(Tree<int>::createValueNode(3,
                                            Tree<int>::createValueNode(5),
                                            Tree<int>::createValueNode(7)));
  tree.fold([&](int v, int l, int r)->int{
    assert(i < sizeof(values)/sizeof(values[0]) && v == values[i++]);
    return v + l + r;
  }, 0);
  assert(i == sizeof(values)/sizeof(values[0]));
  #endif

  #if TEST_NUM == 403
  Tree<int> tree(Tree<int>::createValueNode(13));
  assert(string("OK") == tree.fold([&](int v, string l, string r)->string{return string("OK");}, string("")));
  #endif

  #if TEST_NUM == 404
  Tree<int> tree(Tree<int>::createValueNode(13));
  assert(17U == tree.fold([](unsigned v, unsigned l, unsigned r)->unsigned{return 17U;}, 0U));
  #endif

  #if TEST_NUM == 500
  Tree<int> tree(Tree<int>::createValueNode(1));
  assert(tree.is_bst());
  #endif

  #if TEST_NUM == 501
  Tree<int> tree(Tree<int>::createValueNode(2,
                                            Tree<int>::createValueNode(1),
                                            Tree<int>::createEmptyNode()));
  assert(tree.is_bst());
  #endif

  #if TEST_NUM == 502
  Tree<int> tree(Tree<int>::createValueNode(1,
                                            Tree<int>::createValueNode(2),
                                            Tree<int>::createEmptyNode()));
  assert(!tree.is_bst());
  #endif

  #if TEST_NUM == 503
  Tree<int> tree(Tree<int>::createValueNode(2,
                                            Tree<int>::createEmptyNode(),
                                            Tree<int>::createValueNode(1)));
  assert(!tree.is_bst());
  #endif

  #if TEST_NUM == 504
  Tree<int> tree(Tree<int>::createValueNode(1,
                                            Tree<int>::createEmptyNode(),
                                            Tree<int>::createValueNode(2)));
  assert(tree.is_bst());
  #endif

  #if TEST_NUM == 505
  /*
  Tree<int> tree(Tree<int>::createValueNode(1,
                                            Tree<int>::createValueNode(1),
                                            Tree<int>::createValueNode(1)));
  assert(!tree.is_bst());
  */
  #endif

  #if TEST_NUM == 506
  Tree<int> tree1(Tree<int>::createValueNode(1,
                                             Tree<int>::createValueNode(1),
                                             Tree<int>::createEmptyNode()));
  Tree<int> tree2(Tree<int>::createValueNode(1,
                                             Tree<int>::createEmptyNode(),
                                             Tree<int>::createValueNode(1)));
  /* assert(tree1.is_bst() ^ tree2.is_bst()); */
  assert(tree1.is_bst() || tree2.is_bst());
  #endif

  #if TEST_NUM == 600
  Tree<int> tree1(Tree<int>::createValueNode(7,
                                             Tree<int>::createEmptyNode(),
                                             Tree<int>::createEmptyNode()));
  assert(1 == tree1.size());
  assert(1 == tree1.height());
  assert(9 == tree1.fold([](int v, int l, int r)->int{return v + l + r;}, 1));

  Tree<int> tree2 = tree1.filter([](int e){return e != 1;});
  assert(1 == tree2.size());
  assert(1 == tree2.height());
  assert(9 == tree2.fold([](int v, int l, int r)->int{return v + l + r;}, 1));

  Tree<int> tree3 = tree1.filter([](int e){return e == 1;});
  assert(0 == tree3.size());
  assert(0 == tree3.height());
  assert(1 == tree3.fold([](int v, int l, int r)->int{return v + l + r;}, 1));
  #endif

  #if TEST_NUM == 601
  static const int values[] = {4, 2, 5, 6, 3, 7};
  size_t i = 0;
  Tree<int> tree(Tree<int>::createValueNode(1,
                 Tree<int>::createValueNode(2,
                 Tree<int>::createValueNode(4),
                 Tree<int>::createValueNode(5)),
                 Tree<int>::createValueNode(3,
                 Tree<int>::createValueNode(6),
                 Tree<int>::createValueNode(7))));
  Tree<int> free = tree.filter([](int e){return e != 1;});
  free.apply([&](int e){assert(i < sizeof(values)/sizeof(values[0]) &&
                               e == values[i++]);},
             Tree<int>::inorder);
  assert(i == sizeof(values)/sizeof(values[0]));
  #endif

  #if TEST_NUM == 602
  static const char* values[] = {"B", "A", "C"};
  size_t i = 0;
  Tree<string> tree(Tree<string>::createValueNode(string("A"),
                    Tree<string>::createValueNode(string("B")),
                    Tree<string>::createValueNode(string("C"))));
  tree.apply([&](string e){assert(i < sizeof(values)/sizeof(values[0]) &&
                                  e == string(values[i++]));},
             Tree<string>::inorder);
  assert(i == sizeof(values)/sizeof(values[0]));
  #endif
}
