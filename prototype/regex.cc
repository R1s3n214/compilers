#include "regex.hh"

void ast_to_dfa(Node *ast) {
  // Dstates = ast->firstpos();
  // while (S state in Dstates without mark) {
  //   mark S;
  //   for (each input character **i**) {
  //     U = {};
  //     for (s in S)
  //       if (s == i)
  //         U = U union s->followup();
  //     if U not in Dstates
  //       add U to Dstates
  //     Dtran[S, a] = U;
  //   }
  // }
}
