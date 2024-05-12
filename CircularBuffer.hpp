#pragma once
#include <algorithm>
#include <iostream>
#include <stddef.h>
#include <stdexcept>

namespace Types {

template <typename T>
class CircularBuffer {
  public:
  CircularBuffer();
  CircularBuffer(const CircularBuffer&);
  CircularBuffer(CircularBuffer&&);
  CircularBuffer& operator=(const CircularBuffer&);
  CircularBuffer& operator=(CircularBuffer&&);
  ~CircularBuffer();
  template <typename U>
  CircularBuffer& push(U&&);
  T pop();
  T& top() const;
  size_t capacity() const;
  size_t size() const;
  bool empty() const;
  bool full() const;
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularBuffer& buffer) {
    if (buffer.front_ <= buffer.back_) {
      os << "[";
      for (auto i = buffer.front_; i <= buffer.back_; ++i) {
        os << buffer.arr_[i] << " ";
      }
      os << "]" << std::endl;
    } else {
      os << "[";
      for (auto i = buffer.front_; i < buffer.capacity_; ++i) {
        os << buffer.arr_[i] << " ";
      }
      for (auto i = 0u; i <= buffer.back_; ++i) {
        os << buffer.arr_[i] << " ";
      }
      os << "]" << std::endl;
    }
    return os;
  }

  private:
  void realoc();
  size_t capacity_{0};
  size_t size_{0};
  size_t front_{0};
  size_t back_{0};
  T* arr_{nullptr};
};

template <typename T>
CircularBuffer<T>::CircularBuffer()
    : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}

template <typename T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer& other) {
  *this = other;
}

template <typename T>
CircularBuffer<T>::CircularBuffer(CircularBuffer&& other)
    : capacity_{other.capacity_}, size_{other.size_}, front_{other.front_},
      back_{other.back_}, arr_{other.arr_} {
  other.arr_ = nullptr;
}

template <typename T>
CircularBuffer<T>& CircularBuffer<T>::operator=(CircularBuffer&& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  back_ = other.back_;
  front_ = other.front_;
  arr_ = other.arr_;
  other.arr_ = nullptr;
}

template <typename T>
CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer& other) {
  if (&other != this) {
    delete[] arr_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    back_ = other.back_;
    front_ = other.front_;
    arr_ = new T[capacity_];
    std::copy(other.arr_, other.capacity_, arr_);
  }
  return *this;
}

template <typename T>
CircularBuffer<T>::~CircularBuffer() {
  delete[] arr_;
}

template <typename T>
size_t CircularBuffer<T>::size() const {
  return size_;
}

template <typename T>
size_t CircularBuffer<T>::capacity() const {

  return capacity_;
}

template <typename T>
bool CircularBuffer<T>::empty() const {
  return size_ == 0;
}

template <typename T>
bool CircularBuffer<T>::full() const {
  return capacity_ == size_;
}

template <typename T>
template <typename U>
CircularBuffer<T>& CircularBuffer<T>::push(U&& element) {
  if (size_ == capacity_) {
    realoc();
  }
  size_t index;
  if (empty() || back_ == capacity_) {
    index = back_ = 0;
  } else {
    index = ++back_;
  }
  arr_[index] = std::forward<U>(element);
  ++size_;
  return *this;
}
template <typename T>
void CircularBuffer<T>::realoc() {
  T* tmp = arr_;
  size_t initialCapacity = capacity_;
  capacity_ *= 2;
  arr_ = new T[capacity_];
  std::copy(tmp, tmp + initialCapacity, arr_);
  delete[] tmp;
}

template <typename T>
T CircularBuffer<T>::pop() {
  if (empty()) throw std::out_of_range{"The queue is empty"};
  --size_;
  return arr_[front_++];
}

template <typename T>
T& CircularBuffer<T>::top() const {
  if (empty()) throw std::out_of_range{"The queue is empty"};
  return arr_[front_];
}
} /* Types */
