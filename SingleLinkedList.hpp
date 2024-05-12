#include <iostream>
#include <stdexcept>
template <typename T>
struct Node {
  Node<T>* next;
  T data;
  Node(const T& element) : next{nullptr}, data{element} {}
};
template <typename T>
class SingleLinkedList {
 public:
  class Iterator;
  SingleLinkedList();                                    //
  SingleLinkedList(const SingleLinkedList&);             //
  SingleLinkedList(SingleLinkedList&&);                  //
  SingleLinkedList& operator=(const SingleLinkedList&);  //
  SingleLinkedList& operator=(SingleLinkedList&&);       //
  ~SingleLinkedList();                                   //
  SingleLinkedList& push_back(const T&);                 //
  SingleLinkedList& push_front(const T&);                //
  SingleLinkedList& pop_front();                         //
  SingleLinkedList& pop_back();                          //
  bool empty() const { return head_ == nullptr; };       //
  size_t size() const { return size_; };                 //
  SingleLinkedList& extend(const SingleLinkedList&);     //
  Iterator find(const T& element) const;
  SingleLinkedList& insert(Iterator pos, const T& element);
  Iterator erase(Iterator pos);
  Iterator begin() const;         //
  Iterator end() const;           //
  const Iterator cbegin() const;  //
  const Iterator cend() const;    //
  friend std::ostream& operator<<(std::ostream& os,
                                  const SingleLinkedList& lista) {
    auto* tmpNode = lista.head_;
    while (tmpNode) {
      os << tmpNode->data;
      tmpNode = tmpNode->next;
    }
    return os;
  }

 private:
  void copyList(const SingleLinkedList&);  //
  void dealloc();                          //
  Node<T>* head_;
  Node<T>* tail_;
  size_t size_;
};
template <typename T>
class SingleLinkedList<T>::Iterator {
 public:
  Iterator() = default;
  Iterator(const Iterator&);
  Iterator(Iterator&&);
  ~Iterator();
  Iterator(Node<T>* ptr) : ptr_{ptr} {};
  Iterator(T& element) : ptr_{&element} {};
  Iterator operator++() { return ptr_->next; };
  Iterator operator++(int) {
    auto ret = *this;
    ptr_ = ptr_->next;
    return ret;
  };
  bool operator==(const Iterator& it) const { return ptr_ == it.ptr_; };
  bool operator!=(const Iterator& it) const { return ptr_ != it.ptr_; };
  T& operator*() const { return ptr_->data; };
  Iterator& operator=(const Iterator& it) {
    if (this != &it) {
      ptr_ = it.ptr_;
    }
    return *this;
  };
  Iterator& operator=(Iterator&& it) {
    ptr_ = it.ptr_;
    it.ptr_ = nullptr;
    return *this;
  };

 private:
  Node<T>* ptr_{nullptr};
};
template <typename T>
void SingleLinkedList<T>::dealloc() {
  auto* tmpNode = head_;
  while (tmpNode != nullptr) {
    head_ = head_->next;
    delete tmpNode;
    tmpNode = head_;
  }
  size_ = 0;
  head_ = tail_ = nullptr;
}
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::push_back(const T& element) {
  Node<T>* newNode = new Node<T>{element};
  if (empty()) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    tail_->next = newNode;
    tail_ = newNode;
  }
  size_++;
  return *this;
}
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::push_front(const T& element) {
  Node<T>* newNode = new Node<T>{element};
  if (empty()) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode->next = head_;
    head_ = newNode;
  }
  return *this;
}
template <typename T>
void SingleLinkedList<T>::copyList(const SingleLinkedList& lista) {
  auto* tmpNode = lista.head_;
  while (tmpNode != nullptr) {
    push_back(tmpNode->data);
    tmpNode = tmpNode->next;
  }
}
template <typename T>
SingleLinkedList<T>::SingleLinkedList()
    : head_{nullptr}, tail_{nullptr}, size_{0} {}
template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList& lista) {
  copyLista(lista);
}
template <typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList&& tmp) {
  head_ = tmp.head_;
  tail_ = tmp.tail_;
  size_ = tmp.size_;
  tmp.head_ = tmp.tail_ = nullptr;
}
template <typename T>
SingleLinkedList<T>::~SingleLinkedList<T>() {
  dealloc();
}
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(
    const SingleLinkedList& lista) {
  dealloc();
  copyList(lista);
  return *this;
}
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList&& tmp) {
  dealloc();
  head_ = tmp.head_;
  tail_ = tmp.tail_;
  size_ = tmp.size_;
  tmp.head_ = tmp.tail_ = nullptr;
  tmp.size_ = 0;
  return *this;
}
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::pop_back() {
  auto* tmp = head_;
  if (!empty()) {
    while (tmp->next != tail_) {
      tmp = tmp->next;
    }
    delete tail_;
    tail_ = tmp;
    tail_->next = nullptr;
    --size_;
  }
  return *this;
}
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::pop_front() {
  if (!empty()) {
    auto* tmp = head_;
    head_ = head_->next;
    delete tmp;
    --size_;
  }
  return *this;
}
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::extend(
    const SingleLinkedList<T>& lista) {
  if (this == &lista) return *this;
  auto* tmp = lista.head_;
  while (tmp != nullptr) {
    push_back(tmp->data);
    tmp = tmp->next;
  }
  return *this;
}
template <typename T>
SingleLinkedList<T>::Iterator::Iterator(const Iterator& it) : ptr_{it.ptr_} {}
template <typename T>
SingleLinkedList<T>::Iterator::Iterator(Iterator&& it) : ptr_{it.ptr_} {
  it.ptr_ = nullptr;
}
template <typename T>
SingleLinkedList<T>::Iterator::~Iterator() {
  ptr_ = nullptr;
};
template <typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::begin() const {
  return Iterator{head_};
}
template <typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::end() const {
  return Iterator{tail_};
}
template <typename T>
const typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::cbegin()
    const {
  return Iterator{head_};
}
template <typename T>
const typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::cend() const {
  return Iterator{tail_};
}
template <typename T>
typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::find(
    const T& element) const {
  if (empty()) return end();
  auto it = begin();
  while (it != end()) {
    if (*it == element) {
      return it;
    }
    it++;
  }
  return end();
}
// template <typename T>
// SingleLinkedList<T>& SingleLinkedList<T>::insert(Iterator pos,
//                                                  const T& element) {
//
//
// }
