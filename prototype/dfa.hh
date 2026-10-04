#ifndef COMPILERS_DFA_HH
#define COMPILERS_DFA_HH

#include <iostream>
#include <vector>
#include <ranges>
#include <unordered_map>

using namespace std;

class Node;

class FollowPosTb {
public:
  FollowPosTb() = default;

  bool add(Node *from, Node *to) {
    tb[from].push_back(to);
    return true;
  }

  vector<Node *> query(Node *from) {
    return tb[from];
  }

  unordered_map<Node *, vector<Node *>> tb;
};

class Node {
  static int i;

public:
  Node() {
    node = ++i;
  }

  virtual void print() = 0;
  virtual bool nullable() = 0;
  virtual vector<Node *> firstpos() = 0;
  virtual vector<Node *> lastpos() = 0;

  virtual void build_followup(FollowPosTb *tb) = 0;

  int node;
};

class Cat : public Node {
public:
  Cat(Node *left, Node *right): left(left), right(right) {
  }

  void print() override {
    left->print();
    right->print();
  }

  bool nullable() override {
    return left->nullable() && right->nullable();
  }

  vector<Node *> firstpos() override {
    vector<Node *> ret;

    vector<Node *> l = left->firstpos();
    ret.reserve(ret.size() + l.size());
    ret.insert(ret.end(), l.begin(), l.end());

    if (left->nullable()) {
      vector<Node *> r = right->firstpos();
      ret.reserve(ret.size() + r.size());
      ret.insert(ret.end(), r.begin(), r.end());
    }

    return std::move(ret);
  }

  vector<Node *> lastpos() override {
    vector<Node *> ret;

    vector<Node *> r = right->lastpos();
    ret.reserve(ret.size() + r.size());
    ret.insert(ret.end(), r.begin(), r.end());

    if (right->nullable()) {
      vector<Node *> l = left->lastpos();
      ret.reserve(ret.size() + l.size());
      ret.insert(ret.end(), l.begin(), l.end());
    }

    return std::move(ret);
  }

  void build_followup(FollowPosTb *tb) override {
    left->build_followup(tb);
    right->build_followup(tb);

    // for each position i in lastpos(left), all positions from firstpos(right) are in followpos(i)
    vector<Node *> ll = left->lastpos();
    vector<Node *> rf = right->firstpos();
    for (auto node : ll) {
      std::ranges::for_each(rf, [tb, node](Node *n) {
        tb->add(node, n);
      });
    }
  }

  Node *left;
  Node *right;
};

class Or : public Node {
public:
  Or(Node *left, Node *right): left(left), right(right) {
  }

  void print() override {
    std::cout << "(";
    left->print();
    std::cout << "|";
    right->print();
    std::cout << ")";
  }

  bool nullable() override {
    return left->nullable() || right->nullable();
  }

  vector<Node *> firstpos() override {
    vector<Node *> ret;

    vector<Node *> l = left->firstpos();
    vector<Node *> r = right->firstpos();
    ret.reserve(ret.size() + l.size() + r.size());
    ret.insert(ret.end(), l.begin(), l.end());
    ret.insert(ret.end(), r.begin(), r.end());

    return std::move(ret);
  }

  vector<Node *> lastpos() override {
    vector<Node *> ret;

    vector<Node *> l = left->lastpos();
    vector<Node *> r = right->lastpos();
    ret.reserve(ret.size() + l.size() + r.size());
    ret.insert(ret.end(), l.begin(), l.end());
    ret.insert(ret.end(), r.begin(), r.end());

    return std::move(ret);
  }

  void build_followup(FollowPosTb *tb) override {
    left->build_followup(tb);
    right->build_followup(tb);

    // ??
  }

  Node *left;
  Node *right;
};

class Star : public Node {
public:
  Star(Node *left): left(left) {
  }

  void print() override {
    std::cout << "(";
    left->print();
    std::cout << ")*";
  }

  bool nullable() override {
    return true;
  }

  vector<Node *> firstpos() override {
    return std::move(left->firstpos());
  }

  vector<Node *> lastpos() override {
    return std::move(left->lastpos());
  }

  void build_followup(FollowPosTb *tb) override {
    left->build_followup(tb);

    vector<Node *> lst = left->lastpos();
    vector<Node *> fst = left->firstpos();

    for (auto node : lst) {
      std::ranges::for_each(fst, [tb, node](Node *n) {
        tb->add(node, n);
      });
    }
  }

  Node *left;
};

class Ch : public Node {
public:
  Ch(char ch): ch(ch) {
  }

  void print() override {
    std::cout << ch;
  }

  bool nullable() override {
    return false;
  }

  vector<Node *> firstpos() override {
    return {1, this};
  }

  vector<Node *> lastpos() override {
    return {1, this};
  }

  void build_followup(FollowPosTb *tb) override {
    // do nothing
  }

  char ch;
};

void Lexer_example();

#endif //COMPILERS_DFA_HH
