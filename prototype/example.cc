#include "dfa.hh"

#include <iostream>

//                     cat3 : Cat
//                     /       \
//              cat2 : Cat      c2 : b
//               /      \
//        cat1 : Cat      c2 : b
//         /      \
//    s : Star     c1 : a
//       |
//     o : Or
//     /    \
// c1 : a  c2 : b

void query_print(FollowPosTb *tb, Node *q_node) {
  auto q1 = tb->query(q_node);
  for (auto n: q1) {
    std::cout
      << std::format("node {} follows up: {}", q_node->node, n->node)
      << std::endl;
  }
}

void Lexer_example() {
  Ch c1('a'), c2('b'), c3('a'), c4('b'), c5('b');
  Or o(&c1, &c2);
  Star s(&o);
  Cat cat1(&s, &c3);
  Cat cat2(&cat1, &c4);
  Cat cat3(&cat2, &c5);

  FollowPosTb tb;
  cat3.build_followup(&tb);

  query_print(&tb, &c1);
  query_print(&tb, &c2);
  query_print(&tb, &c3);
  query_print(&tb, &c4);
  query_print(&tb, &c5);
}
