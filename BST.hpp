#pragma once
#include <iostream>
template <typename T>
struct Node {
  Node* left;
  Node* right;
  T data;
};

template <typename T>
class BST {
  public:
  BST() = default;
  bool empty() { return root_ == nullptr; }
  BST(const BST&);
  BST(BST&& bst) : root_{bst.root_} { bst.root_ = nullptr; }
  BST& operator=(BST&& bst) {
    destroy(root_);
    root_ = bst.root_;
    bst.root_ = nullptr;
  }
  BST& operator=(const BST& bst) { destroy(*this); }

  private:
  void destroy(Node<T>* node) {
    if (node == nullptr) {
      return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
  }
  Node<T>* root_{nullptr};
};
