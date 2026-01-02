#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {
private:
  BSTree<TableEntry<V>>* tree;
  
public:
  BSTreeDict() { this->tree = new BSTree<TableEntry<V>>(); }

  ~BSTreeDict() { delete this->tree; }

  friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
    out << *(bs.tree);
    return out;
  }

  V operator[](std::string key) {
    return this->tree->search(TableEntry<V>(key)).value;
  }

  void insert(std::string key, V value) override {
    this->tree->insert(TableEntry<V>(key, value));
  }

  V search(std::string key) override {
    return (*this)[key];
  }

  V remove(std::string key) override {
    V ret = this->search(key);
    this->tree->remove(TableEntry<V>(key));
    return ret;
  }

  int entries() const override { return this->tree->size(); }
};

#endif // BSTREEDICT_H

