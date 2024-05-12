#pragma once
// Sadrzi size_t
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

namespace Types {

template <typename T>
class Stack {
  public:
  Stack();
  Stack(const Stack&);
  Stack(Stack&&);
  Stack& operator=(const Stack&);
  Stack& operator=(Stack&&);
  T pop();
  T& top() const;
  // Savrseno proslijedjivane (forward referenca)
  template <typename U>
  Stack<T>& push(U&&);
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  ~Stack();

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

template <typename T>
Stack<T>::Stack() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}

template <typename T>
Stack<T>::Stack(const Stack& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]} {
  std::copy(other.arr_, other.arr_ + size_, arr_);
}

template <typename T>
Stack<T>::Stack(Stack&& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_} {
  other.arr_ = nullptr;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) {
  if(arr_) delete [] arr_;
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = other.arr_;
  other.arr_ = nullptr;
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  if (this == &other) return *this;
  if(arr_) delete [] arr_;
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = new T[capacity_];
  std::copy(other.arr_, other.arr_ + size_, arr_);
  return *this;
}
template <typename T>
T& Stack<T>::top() const {
  if (empty()) throw std::out_of_range{"The stack is empty"};
  return arr_[size_ - 1];
}

template <typename T>
T Stack<T>::pop() {
  if (empty()) throw std::out_of_range{"The stack is empty"};
  T element = arr_[--size_];
  //ili 
  // T element = std::move(arr_[size_-1]);
  // --size_;
  return element;
}
template <typename T>
void Stack<T>::realoc() {
  T* tmp = new T[size_];
  std::copy(arr_, arr_ + size_, tmp);
  delete[] arr_;
  capacity_ *= 2;
  arr_ = new T[capacity_];
  std::copy(tmp, tmp + size_, arr_);
  delete[] tmp;
}

template <typename T>
template <typename U>
Stack<T>& Stack<T>::push(U&& element) {
  if (size_ == capacity_) realoc();
  arr_[size_++] = std::forward<U>(element);
  return *this;
}
template <typename T>
bool Stack<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t Stack<T>::size() const {
  return size_;
}

template <typename T>
size_t Stack<T>::capacity() const {
  return capacity_;
}

template <typename T>
Stack<T>::~Stack() {
  delete[] arr_;
  size_ = capacity_ = 0;
}

} /* Types */
