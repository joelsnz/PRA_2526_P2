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

    BSNode<T>* search(BSNode<T>* n, T e) const {
      if(n == nullptr)
        throw std::runtime_error("Element not found");
      if(n->elem < e)
        return search(n->right, e);
      if(n->elem > e)
        return search(n->left, e);
      else return n;
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
      if(n == nullptr) {
        this->nelem++;
        return new BSNode<T>(e);
      }
      else if(n->elem == e)
        throw std::runtime_error("Duplicated element");
      else if(n->elem < e)
        n->right = insert(n->right, e);
      else
        n->left = insert(n->left, e);
      return n;
    }

    void print_inorder(std::ostream &out, const BSNode<T>* n) const {
      if(n != nullptr) {
        print_inorder(out, n->left);
        out << *n << " ";
        print_inorder(out, n->right);
      }
    }

    T max(BSNode<T>* n) const {
      if(n == nullptr)
        throw std::runtime_error("Element not found");
      if(n->right != nullptr)
        return max(n->right);
      return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
      if(n->right == nullptr)
        return n->left;
      n->right = remove_max(n->right);
      return n;
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
      if(n == nullptr)
        throw std::runtime_error("Element not found");
      else if(n->elem < e)
        n->right = remove(n->right, e);
      else if(n->elem > e)
        n->left = remove(n->left, e);
      else {
        this->nelem--;
        if(n->left != nullptr && n->right != nullptr) {
          n->elem = max(n->left);
          n->left = remove_max(n->left);
        } else
          n = (n->left != nullptr) ? n->left : n->right;
      }
      return n;
    }

    void delete_cascade(BSNode<T>* n) {
      if(n != nullptr) {
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
      }
    }

  public:
    BSTree() : root(nullptr), nelem(0) {}

    ~BSTree() {
      delete_cascade(this->root);
    }

    int size() const { return this->nelem; }

    T search(T e) const {
      return search(root, e)->elem;
    }

    T operator[](T e) const {
      return this->search(e);
    }

    void insert(T e) { this->root = insert(root, e); }

    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
      bst.print_inorder(out, bst.root);
      return out;
    }

    void remove(T e) { this->remove(this->root, e); }
};

#endif // BSTREE_H
