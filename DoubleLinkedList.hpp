#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
  T data;
  Node<T>* next;
  Node<T>* prev;
  template <typename U>
  Node(U&& element)
      : next{nullptr}, prev{nullptr}, data{std::forward<U>(element)} {}
  Node(const T& element) : next{nullptr}, prev{nullptr}, data{element} {}
};
template <typename T>
class DoubleLinkedList {
 public:
  DoubleLinkedList();                                    //
  DoubleLinkedList(const DoubleLinkedList&);             //
  DoubleLinkedList(DoubleLinkedList&&);                  //
  DoubleLinkedList& operator=(DoubleLinkedList&&);       //
  DoubleLinkedList& operator=(const DoubleLinkedList&);  //
  ~DoubleLinkedList();                                   //
  DoubleLinkedList(const std::initializer_list<T>&);
  void append(const DoubleLinkedList<T>&);
  template <typename U>
  DoubleLinkedList& push_back(U&&);  //
  DoubleLinkedList& pop_back();      //
  void print_reverse();
  DoubleLinkedList& pop_front();  //
  DoubleLinkedList& erase_if(const T&);
  T& front() const { return head_->data; };  //
  T& back() const { return tail_->data; };   //
  bool operator==(const DoubleLinkedList&) const;
  bool operator!=(const DoubleLinkedList&) const;
  template <typename U>
  DoubleLinkedList& push_front(U&&);          //
  size_t size() const { return size_; };      //
  bool empty() const { return size_ == 0; };  //
  class Iterator;
  Iterator find(const T&) const;
  Iterator erase(Iterator);
  Iterator begin() const;  //
  Iterator end() const;    //
  DoubleLinkedList& insert(Iterator, const T&);
  friend std::ostream& operator<<(std::ostream& os,
                                  const DoubleLinkedList& lista) {
    auto* tmpNode = lista.head_;
    os << "[";
    while (tmpNode) {
      os << tmpNode->data << " ";
      tmpNode = tmpNode->next;
    }
    os << "]" << std::endl;
    return os;
  }
  void swap(DoubleLinkedList& lista) {
    auto* tmpHead = lista.head_;
    auto* tmpTail = lista.tail_;
    lista.head_ = head_;
    head_ = tmpHead;
    lista.tail_ = tail_;
    tail_ = tmpTail;
  }
  void append(DoubleLinkedList&& lista) {
    lista.head_->prev = tail_;
    tail_->next = lista.head_;
    tail_ = lista.tail_;
    size_ += lista.size_;
    lista.head_ = lista.tail_ = nullptr;
  }
  void resize(size_t newSize) {
    if (newSize < size_) {
      while (newSize != size_) {
        pop_back();
      }
    } else if (newSize > size_) {
      while (newSize != size_) {
        push_back(0);
      }
    } else {
      throw std::invalid_argument{"Wrong input"};
    }
  }
  void reverse() {
    DoubleLinkedList<T> tmpList;
    auto* tmpNode = tail_;
    while (tmpNode) {
      tmpList.push_back(tmpNode->data);
      tmpNode = tmpNode->prev;
    }
    *this = tmpList;
  }

 private:
  void copyList(const DoubleLinkedList&);
  void dealoc();
  size_t size_{0};
  Node<T>* head_;
  Node<T>* tail_;
};
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  dealoc();
}
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const std::initializer_list<T>& lista) {
  for (auto i = lista.begin(); i != lista.end(); ++i) {
    push_back(*i);
  }
}
template <typename T>
void DoubleLinkedList<T>::copyList(const DoubleLinkedList& lista) {
  auto* tmpNode = lista.head_;
  while (tmpNode) {
    push_back(tmpNode->data);
    tmpNode = tmpNode->next;
  }
}
template <typename T>
void DoubleLinkedList<T>::append(const DoubleLinkedList& lista) {
  auto* tmpNode = lista.head_;
  while (tmpNode) {
    push_back(tmpNode->data);
    tmpNode = tmpNode->next;
  }
}
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head_{nullptr}, tail_{nullptr} {};
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& lista) {
  copyList(lista);
}
template <typename T>
void DoubleLinkedList<T>::dealoc() {
  auto* tmpNode = head_;
  while (tmpNode) {
    head_ = head_->next;
    delete tmpNode;
    tmpNode = head_;
  }
  size_ = 0;
  head_ = tail_ = nullptr;
}
template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& lista) {
  if (this == &lista) return *this;
  dealoc();
  head_ = lista.head_;
  tail_ = lista.tail_;
  size_ = lista.size_;
  lista.head_ = lista.tail_ = nullptr;
  lista.size_ = 0;
  return *this;
}
template <typename T>
bool DoubleLinkedList<T>::operator==(const DoubleLinkedList& rhs) const {
  if (size_ == rhs.size_) {
    auto it = begin();
    auto it_rhs = rhs.begin();
    while (it != end()) {
      if (*it != *it_rhs) return false;
      ++it;
      ++it_rhs;
    }
    return true;
  }
  return false;
}
template <typename T>
bool DoubleLinkedList<T>::operator!=(const DoubleLinkedList& rhs) const {
  return !(*this == rhs);
}
template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(
    const DoubleLinkedList& lista) {
  if (this == &lista) return *this;
  dealoc();
  copyList(lista);
  return *this;
}
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& tmp)
    : head_{tmp.head_}, tail_{tmp.tail_}, size_{tmp.size_} {
  tmp.head_ = tmp.tail_ = nullptr;
  tmp.size_ = 0;
}
template <typename T>
template <typename U>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(U&& element) {
  Node<T>* newNode = new Node<T>{element};
  if (empty()) {
    head_ = tail_ = newNode;
  } else {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  }
  ++size_;
  return *this;
}
template <typename T>
template <typename U>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(U&& element) {
  Node<T>* newNode = new Node<T>{element};
  if (empty()) {
    head_ = tail_ = newNode;
  } else {
    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
  }
  ++size_;
  return *this;
}
template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front() {
  if (empty()) throw std::out_of_range{"List is empty"};
  if (size_ == 1) {
    delete head_;
    head_ = tail_ = nullptr;
  } else {
    auto* tmpNode = head_;
    head_ = head_->next;
    head_->prev = nullptr;
    delete tmpNode;
  }
  --size_;
  return *this;
}
template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back() {
  if (empty()) throw std::out_of_range{"List is empty"};
  if (size_ == 1) {
    delete head_;
    head_ = tail_ = nullptr;
  } else {
    auto* tmpNode = tail_;  //
    tail_ = tail_->prev;
    tail_->next = nullptr;
    delete tmpNode;
  }
  --size_;
  return *this;
}
template <typename T>
class DoubleLinkedList<T>::Iterator {
 public:
  Iterator();                                                            //
  Iterator(const Iterator&);                                             //
  Iterator(Iterator&&);                                                  //
  Iterator& operator=(Iterator&&);                                       //
  Iterator& operator=(const Iterator&);                                  //
  ~Iterator();                                                           //
  Iterator(Node<T>*);                                                    //
  Iterator(T&);                                                          //
  Iterator& operator++();                                                //
  Node<T>* node() const;                                                 //
  Iterator operator++(int);                                              //
  Iterator& operator--();                                                //
  Iterator operator--(int);                                              //
  T& operator*();                                                        //
  bool operator==(const Iterator& it) const { return ptr_ == it.ptr_; }  //
  bool operator!=(const Iterator& it) const { return ptr_ != it.ptr_; }  //

 private:
  Node<T>* ptr_;
};
template <typename T>
DoubleLinkedList<T>::Iterator::Iterator() : ptr_{nullptr} {}
template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(const Iterator& it) : ptr_{it.ptr_} {}
template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(Iterator&& it) : ptr_{it.ptr_} {
  it.ptr_ = nullptr;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator&
DoubleLinkedList<T>::Iterator::operator=(const Iterator& it) {
  ptr_ = it.ptr_;
  return *this;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator&
DoubleLinkedList<T>::Iterator::operator=(Iterator&& it) {
  ptr_ = it.ptr_;
  it.ptr_ = nullptr;
  return *this;
}
template <typename T>
DoubleLinkedList<T>::Iterator::~Iterator() {
  ptr_ = nullptr;
}
template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(Node<T>* ptr) : ptr_{ptr} {}
template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(T& element) : ptr_{&element} {}
template <typename T>
Node<T>* DoubleLinkedList<T>::Iterator::node() const {
  return ptr_;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator&
DoubleLinkedList<T>::Iterator::operator++() {
  ptr_ = ptr_->next;
  return *this;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator&
DoubleLinkedList<T>::Iterator::operator--() {
  ptr_ = ptr_->prev;
  return *this;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator
DoubleLinkedList<T>::Iterator::operator++(int) {
  auto ret = *this;
  ptr_ = ptr_->next;
  return ret;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator
DoubleLinkedList<T>::Iterator::operator--(int) {
  auto ret = *this;
  ptr_ = ptr_->prev;
  return ret;
}
template <typename T>
T& DoubleLinkedList<T>::Iterator::operator*() {
  return ptr_->data;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const {
  return Iterator{head_};
}
template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const {
  return Iterator{tail_->next};
}
// ovo je insert iza pos
// template <typename T>
// DoubleLinkedList<T>& DoubleLinkedList<T>::insert(
//     Iterator pos, const T& element) {
//   if (pos == end()) {
//     return *this;
//   }
//   auto* posNode = pos.node();
//   Node<T>* node = new Node<T>(element);
//   node->next = posNode->next;
//   node->prev = posNode;
//   posNode->next = node;
//   ++size_;
//   return *this;
// }
template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::insert(Iterator pos,
                                                 const T& element) {
  if (pos == end()) {
    return *this;
  }
  if (pos == begin()) {
    push_front(element);
  } else {
    auto* posNode = pos.node();
    Node<T>* newNode = new Node<T>(element);
    newNode->prev = posNode->prev;
    posNode->prev = newNode;
    newNode->next = posNode;
    newNode->prev->next = newNode;
    ++size_;
  }
  return *this;
}
template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(
    Iterator pos) {
  if (pos == end()) {
    return end();
  }
  Node<T>* temp = head_;
  if (temp != nullptr && pos.node() == temp) {
    head_ = temp->next;
    head_->prev = nullptr;
    delete temp;
    return Iterator(head_);  // ovo je ok
  } else {
    while (temp->next != pos.node()) {
      temp = temp->next;
    }
    if (temp == nullptr) return end();
    if (pos.node() == tail_) {
      pop_back();
      return end();
    }
    temp->next = pos.node()->next;
    temp->prev = pos.node()->prev;
    delete pos.node();
    --size_;
    return Iterator{temp};
  }  // prolazi test ali nisam siguran je li 100% tacan
}
template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(
    const T& element) const {
  if (empty()) return end();
  auto it = begin();
  while (it != end()) {
    if (*it == element) return it;
    ++it;
  }
  return end();
}
template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::erase_if(const T& element) {
  if (empty()) throw std::out_of_range{"List is empty"};
  auto it = begin();
  while (it != end()) {
    if (*it == element) {
      it = erase(it);  // erase vraca iterator na sljedeci node
      // shodno tome ako se izvrsi erase nema potrebe da se
      // izvrsi ++it
    } else {
      ++it;
    }
  }
  return *this;
}
template <typename T>
void DoubleLinkedList<T>::print_reverse() {
  auto* tmp = tail_;
  while (tmp) {
    std::cout << tmp->data << std::endl;
  }
  tmp = tmp->prev;
}
