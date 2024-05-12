#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

namespace Types {
template <typename T>
class Queue {
  public:
  Queue();
  Queue(const Queue&);
  Queue(Queue&&);
  Queue& operator=(const Queue&);
  Queue& operator=(Queue&&);
  ~Queue();
  // Add new element at the end of the queue
  template <typename U>
  Queue& push(U&&);
  // Pop an element from the begin
  T pop();
  T& front();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  void clear();

  private:
  void copyQueue(const Queue&);
  size_t capacity_;
  size_t size_;
  T* arr_;
  // Index sa koje strane se dodaje
  size_t back_{0};
  // Index sa koje strane se uklanja
  size_t front_{0};
};

template <typename T>
Queue<T>::Queue() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}
template <typename T>
void Queue<T>::copyQueue(const Queue& other) {
  front_ = other.front_;
  back_ = other.back_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  if (arr_) delete[] arr_;
  arr_ = new T[capacity_];
  std::copy(other.arr_ + other.front_, other.arr_ + back_ + 1, arr_ + front_);
}
template <typename T>
Queue<T>::Queue(const Queue& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]},
      back_{other.back_}, front_{other.front_} {
  std::copy(other.arr_ + front_, other.arr_ + back_ + 1, arr_ + front_);
}

template <typename T>
Queue<T>::Queue(Queue&& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_},
      back_{other.back_}, front_{other.front_} {
  other.arr_ = nullptr;
}
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
  if (this == &other) return *this;
  copyQueue(other);
  return *this;
}
template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  front_ = other.front_;
  back_ = other.back_;
  if (arr_) delete[] arr_;
  arr_ = other.arr_;
  other.arr_ = nullptr;
}
template <typename T>
Queue<T>::~Queue() {
  delete[] arr_;
  size_ = capacity_ = front_ = back_ = 0;
}
template <typename T>
template <typename U>
Queue<T>& Queue<T>::push(U&& element) {
  if (back_ == capacity_) {
    T* tmp = arr_;
    capacity_ *= 1.5;
    arr_ = new T[capacity_];
    std::copy(tmp + front_, tmp + front_ + size_, arr_);
    delete[] tmp;
    // normalizacija indexa
    back_ = size_ - 1;
    front_ = 0;
  }
  // Ako je red prazan, front i back pokazuju na isti element nakon dodavanja
  // prvog elementa
  // Pozicija na koju dodajemo
  size_t index;
  if (empty()) {
    index = 0;
  } else {
    index = ++back_;
  }
  arr_[index] = std::forward<U>(element);
  ++size_;
  return *this;
}

template <typename T>
T Queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range{"The queue is empty"};
  }
  // Pomjeramo index sa cije strane uklanjamo element
  --size_;
  return arr_[front_++];
}

template <typename T>
bool Queue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
bool Queue<T>::full() const {
  return back_ == capacity_;
}

template <typename T>
T& Queue<T>::front() {
  if (empty()) {
    throw std::out_of_range{"Queue is empty"};
  }
  return arr_[front_];
}

template <typename T>
size_t Queue<T>::size() const {
  return size_;
}

template <typename T>
size_t Queue<T>::capacity() const {
  return capacity_;
}

template <typename T>
void Queue<T>::clear() {
  delete[] arr_;
  front_ = back_ = 0;
  size_ = capacity_ = 0;
}

} /* temp */
