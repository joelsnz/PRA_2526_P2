#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
  private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) {
      if(n == nullptr)
        throw std::runtime_error("Elemento no encontrado");
      if(n.elem < e)
        return search(n.left, e);
      if(n.elem > e)
        return search(n.right, e);
      else return n;
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
      if(n == nullptr)
        throw std::runtime_error("Elemento no encontrado");
      if(n.elem == e)
        throw std::runtime_error("Elemento duplicado");
      if(n.elem < e)
        insert(n.right, e);
      else
        insert(n.left, e);
      return n;
    }

    void print_inorder(std::ostream &out, const BSTree<T>* n) {
      if(n == nullptr)
        print_inorder(out
    }

  public:
    BSTree() {
      this->nelem = 0;
      root = nullptr;
    }

    int size() const { return this->nelem; }

    T search(T e) const {
      return this->search(root, e).elem;
    }

    T operator[](T e) const {
      return this->search(e);
    }

    void insert(T e) { insert(root, e); }

    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
      print_inorder(out, bst);
      return out
    }
};

#endif // BSTREE_H
