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
  BSTreeDict() { this->tree = new BSTree<V>(); }

  ~BSTreeDict() { delete this->tree; }

  friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
    out << bs->tree;
    return out;
  }

  V operator[](std::string key) { return this->tree[key].elem; }

  virtual void insert(std::string key, V value) {
    
  }

  virtual V search(std::string key) {

  }

  virtual V remove(std::string key) {

  }

  virtual int entries() const {

  }
};

#endif // BSTREEDICT_H
