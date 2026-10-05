// Compilers: Principles, Techniques, & Tools (2nd Edition)
// 4.4.2 FIRST and FOLLOW

#ifndef COMPILER_SYNTAX_HH
#define COMPILER_SYNTAX_HH

#include <vector>
#include <string>
#include <ranges>
#include <algorithm>

using namespace std;

class Grammar;
class TerminalSymbol;

class NullTable {
public:
  void set_value(Grammar *key, bool value) {
    // todo:
  }

  bool query(Grammar *key) {
    // todo:
    return false;
  }
};

class FirstTable {
public:
  void add(Grammar *f, Grammar *t) {
    // todo:
  }

  vector<TerminalSymbol *> query(Grammar *g) {
    // todo
    return {};
  }
};

class FollowTable {
};

class Token {
public:
  virtual const string &type() = 0;
};

class Grammar {
public:
  Grammar() = default;
  virtual ~Grammar() = default;

  virtual void build_nullable(NullTable *tb) = 0;
  virtual void build_first(FirstTable *ftb, NullTable *ntb) = 0;
  virtual void build_follow(FollowTable *tb) = 0;

  virtual bool is_terminal() = 0;
};

struct Production {
  vector<Grammar *> symbol;
};

class TerminalSymbol : public Grammar {
public:
  TerminalSymbol() = default;

  void build_nullable(NullTable *tb) override {
    tb->set_value(this, false);
  }

  void build_first(FirstTable *ftb, NullTable *ntb) override {
    ftb->add(this, this);
  }

  void build_follow(FollowTable *tb) override {
  }

  bool is_terminal() override {
    return true;
  }

  Token *t;
};

class NonterminalSymbol : public Grammar {
public:
  NonterminalSymbol() = default;

  void build_nullable(NullTable *tb) override {
    bool this_nullable = false;
    for (auto &p: next) {
      bool p_nullable = true;
      for (auto &g: p.symbol) {
        g->build_nullable(tb);
        if (!tb->query(g)) {
          p_nullable = false;
          // break;
        }
      }
      if (p_nullable) {
        this_nullable = true;
      }
    }
    tb->set_value(this, has_null ? true : this_nullable);
  }

  void build_first(FirstTable *ftb, NullTable *ntb) override {
    for (auto &p: next) {
      for (auto &g: p.symbol) {
        g->build_first(ftb, ntb);
        std::ranges::for_each(ftb->query(g), [ftb, this](TerminalSymbol *g) {
          ftb->add(this, g);
        });
        if (!ntb->query(g)) {
          break;
        }
      }
    }
  }

  void build_follow(FollowTable *tb) override {
  }

  bool is_terminal() override {
    return false;
  }

  vector<Production> next;
  bool has_null;
};

void syntax_example() {
  NullTable ntb;
  FirstTable ftb;

  // some grammar
  Grammar *g;
  g->build_nullable(&ntb);
  g->build_first(&ftb, &ntb);
}

#endif
