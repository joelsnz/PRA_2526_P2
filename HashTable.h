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

    for(char c : key)
      sum += int(c);

    return sum % this->max;
  }

public:
  HashTable(int size) : Dict<V>(), n{0}, max{size} {
    this->table = new ListLinked<TableEntry<V>>[max];
  }

  ~HashTable() { delete[] this->table; }

  int capacity() const { return this->max; }

  friend std::ostream &operator<<(std::ostream &out,
                                  const HashTable<V> &th) {
    out << "HashTable [entries: " << th.entries();
    out << ", capacity: " << th.capacity() << "]" << std::endl;
    out << "==============" << std::endl << std::endl;

    for(int i = 0; i < th.max; i++) {
      out << "== Cubeta " << i << " ==" << std::endl << std::endl;
      out << th.table[i] << std::endl << std::endl;
    }

    return out;
  }

  V operator[](std::string key) {
    for(int i = 0; i < this->n; i++) {
      int pos = this->table[i].search(key);
      if(pos != -1) return this->table[i][pos].value;
    }
    throw std::runtime_error("No existe la clave " + key);
  }

  void insert(std::string key, V value) override {
    int pos = h(key);
    if(this->table[pos].search(key) != -1)
      throw std::runtime_error("La llave " + key + " ya existe");
    this->table[pos].prepend(TableEntry<V>(key, value));
    n++;
  }

  V search(std::string key) override {
    int idx = h(key);
    int pos = table[idx].search(TableEntry<V>(key));

    if(pos == -1)
      throw std::runtime_error("Clave no encontrada: " + key);

    return table[idx].get(pos).value;
  }

  V remove(std::string key) override {
    int idx = h(key);
    int pos = table[idx].search(TableEntry<V>(key));

    if(pos == -1)
      throw std::runtime_error("Clave no encontrada: " + key);

    this->n--;

    return this->table[idx].remove(pos).value;
  }

  int entries() const override { return this->n; }
};

#endif // HASHTABLE_H
