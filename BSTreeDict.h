#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include "BSTree.h"
#include "Dict.h"
#include "TableEntry.h"
#include <ostream>
#include <stdexcept>

template <typename V> class BSTreeDict : public Dict<V> {
private:
  BSTree<TableEntry<V>> *tree;

public:
  BSTreeDict() { tree = new BSTree<TableEntry<V>>(); }

  ~BSTreeDict() { delete tree; }

  friend std::ostream &operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
    out << *(bs.tree);
    return out;
  }

  V operator[](std::string key) {
    return tree->search(TableEntry<V>(key)).value;
  }

  void insert(std::string key, V value) override {
    tree->insert(TableEntry<V>(key, value));
  }

  V search(std::string key) override { return (*this)[key]; }

  V remove(std::string key) override {
    V ret = search(key);
    tree->remove(TableEntry<V>(key));
    return ret;
  }

  int entries() const override { return tree->size(); }
};

#endif // BSTREEDICT_H
