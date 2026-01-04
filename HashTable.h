#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../PRA_2526_P1/ListLinked.h"
#include "Dict.h"
#include "TableEntry.h"

#include <ostream>
#include <stdexcept>

template <typename V>

class HashTable : public Dict<V> {
private:
  int n;
  int max;
  ListLinked<TableEntry<V>> *table;

  int h(std::string key) {
    int sum = 0;

    for (char c : key)
      sum += int(c);

    return sum % this->max;
  }

public:
  HashTable(int size) : Dict<V>(), n{0}, max{size} {
    table = new ListLinked<TableEntry<V>>[max];
  }

  ~HashTable() { delete[] table; }

  int capacity() const { return max; }

  friend std::ostream &operator<<(std::ostream &out, const HashTable<V> &th) {
    out << "HashTable [entries: " << th.entries();
    out << ", capacity: " << th.capacity() << "]" << std::endl;
    out << "==============" << std::endl << std::endl;

    for (int i = 0; i < th.max; i++) {
      out << "== Cubeta " << i << " ==" << std::endl << std::endl;
      out << th.table[i] << std::endl << std::endl;
    }
    out << "==============" << std::endl;

    return out;
  }

  V operator[](std::string key) {
    for (int i = 0; i < n; i++) {
      int pos = table[i].search(key);
      if (pos != -1)
        return table[i][pos].value;
    }
    throw std::runtime_error("Key '" + key + "' not found");
  }

  void insert(std::string key, V value) override {
    int pos = h(key);
    if (table[pos].search(key) != -1)
      throw std::runtime_error("Key '" + key + "' already exists");
    table[pos].prepend(TableEntry<V>(key, value));
    n++;
  }

  V search(std::string key) override {
    int idx = h(key);
    int pos = table[idx].search(TableEntry<V>(key));

    if (pos == -1)
      throw std::runtime_error("Key '" + key + "' not found");

    return table[idx].get(pos).value;
  }

  V remove(std::string key) override {
    int idx = h(key);
    int pos = table[idx].search(TableEntry<V>(key));

    if (pos == -1)
      throw std::runtime_error("Key '" + key + "' not found");

    n--;

    return table[idx].remove(pos).value;
  }

  int entries() const override { return n; }
};

#endif // HASHTABLE_H
