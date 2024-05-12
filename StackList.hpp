#pragma once
#include <iostream>
#include <stdexcept>
template <typename T>
struct Node {
  T data;
  Node* next;
  template <typename U>
  Node(U&& referenca) : data{std::forward<U>(referenca)}, next{nullptr} {}
};
template <typename T>
class Stack {
  public:
  Stack() : head_{nullptr}, tail_{nullptr} {};
  Stack(const Stack& tmp) { copyList(tmp); };
  Stack(Stack&& tmp) : size_{tmp.size_}, head_{tmp.head_}, tail_{tmp.tail_} {
    tmp.head_ = tmp.tail_ = nullptr;
  };
  Stack& operator=(const Stack& tmp) {
    if (this == &tmp) return *this;
    dealoc();
    copyList(tmp);
    return *this;
  };
  Stack& operator=(Stack&& tmp) {
    if (this == &tmp) return *this;
    dealoc();
    size_ = tmp.size_;
    head_ = tmp.head_;
    tail_ = tmp.tail_;
    tmp.tail_ = tmp.head_ = nullptr;
    return *this;
  };
  ~Stack() { dealoc(); };
  T pop();
  template <typename U>
  Stack& push(U&&);
  T& top() const;
  size_t size() const;
  bool empty() const;

  private:
  void copyList(const Stack&);
  void dealoc();
  Node<T>* head_;
  Node<T>* tail_;
  size_t size_{0};
};
template <typename T>
void Stack<T>::copyList(const Stack& stek) {
  auto* tmpNode = stek.head_;
  while (tmpNode) {
    push(tmpNode->data);
    tmpNode = tmpNode->next;
  }
}
template <typename T>
void Stack<T>::dealoc() {
  auto* tmpNode = head_;
  while (tmpNode != nullptr) {
    head_ = head_->next;
    delete tmpNode;
    tmpNode = head_;
  }
  head_ = tail_ = nullptr;
  size_ = 0;
}
template <typename T>
template <typename U>
Stack<T>& Stack<T>::push(U&& element) {
  Node<T>* newNode = new Node<T>{element};
  if (head_ == nullptr) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode->next = head_;
    head_ = newNode;
  }
  size_++;
  return *this;
}

template <typename T>
T Stack<T>::pop() {
  if (empty()) throw std::out_of_range{"Stack is empty"};
  auto* tmp = head_;
  head_ = head_->next;
  T returnData = std::move(tmp->data);
  delete tmp;
  size_--;
  return returnData;
}
template <typename T>
T& Stack<T>::top() const {
  return head_->data;
}
template <typename T>
bool Stack<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t Stack<T>::size() const {
  return size_;
}
