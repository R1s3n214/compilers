#ifndef C_DEMO_LEXER_HH
#define C_DEMO_LEXER_HH

#include <iostream>
#include <vector>

using namespace std;

class Token {
};

class Lexer {
public:
  Lexer(): state(0) {
  }

  int state;
};

class Node {
public:
  Node() = default;

  virtual void print() = 0;
  virtual bool nullable() = 0;
  virtual vector<int> firstpos() = 0;
  virtual vector<int> lastpos() = 0;

  virtual void build_followup() = 0;

  virtual void build() = 0;

  int node;
};

class Cat : public Node {
public:
  Cat(Node *left, Node *right): left(left), right(right) {
  }

  virtual void print() override {
    left->print();
    right->print();
  }

  virtual void build() override {
  }

  bool nullable() override {
    return left->nullable() && right->nullable();
  }

  vector<int> firstpos() override {
  }

  Node *left;
  Node *right;
};

class Or : public Node {
public:
  Or(Node *left, Node *right): left(left), right(right) {
  }

  virtual void print() override {
    std::cout << "(";
    left->print();
    std::cout << "|";
    right->print();
    std::cout << ")";
  }

  virtual void build() override {
  }

  bool nullable() override {
    return left->nullable() || right->nullable();
  }

  Node *left;
  Node *right;
};

class Star : public Node {
public:
  Star(Node *left): left(left) {
  }

  virtual void print() override {
    std::cout << "(";
    left->print();
    std::cout << ")*";
  }

  virtual void build() override {
  }

  bool nullable() override {
    return true;
  }

  Node *left;
};

class Ch : public Node {
public:
  Ch(char ch): ch(ch) {
  }

  virtual void print() override {
    std::cout << ch;
  }

  virtual void build() override {
  }

  bool nullable() override {
    return false;
  }

  char ch;
};

#endif //C_DEMO_LEXER_HH
