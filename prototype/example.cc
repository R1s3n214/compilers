#include "Lexer.hh"

//                Cat
//               /   \
//            Cat     b
//           /   \
//        Cat     b
//       /   \
//    Star    a
//      |
//      Or
//    /    \
//   a      b

void Lexer_example() {
  Ch c1('a'), c2('b');
  Or o(&c1, &c2);
  Star s(&o);
  Cat cat1(&s, &c1);
  Cat cat2(&cat1, &c2);
  Cat cat3(&cat2, &c2);
}
