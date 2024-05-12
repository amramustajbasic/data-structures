#pragma once
#include <stddef.h>

#include <stdexcept>
template <typename T>
class Red {
 public:
  Red();                       //
  Red(const Red&);             //
  Red(Red&&);                  //
  Red& operator=(const Red&);  //
  Red& operator=(Red&&);       //
  ~Red();                      //
  T pop();
  template <typename U>
  Red& push(U&&);
  T& front();
  bool empty() const { return size_ == 0; };             //
  bool full() const { return back_ + 1 == capacity_; };  //
  size_t size() const { return size_; };                 //
  size_t capacity() const { return capacity_; }          //
  void clear();

 private:
  void realoc() {
    T* tmp = arr_;
    delete[] arr_;
    capacity_ *= 2;
    arr_ = new T[capacity_];
    std::copy(tmp + front_, tmp + back_ + 1, arr_);
    delete[] tmp;
    front_ = 0;
    back_ = size_ - 1;
  };
  void copyRed();
  size_t size_;
  size_t capacity_;
  T* arr_;
  size_t front_{0};
  size_t back_{0};
};

template <typename T>
Red<T>& Red<T>::operator=(Red&& tmp) {
  if (this == &tmp) return *this;
  front_ = tmp.front_;
  back_ = tmp.back_;
  size_ = tmp.size_;
  if (arr_) delete[] arr_;
  arr_ = tmp.arr_;
  capacity_ = tmp.capacity_;
  tmp.arr_ = nullptr;
  tmp.size_ = tmp.capacity_ = 0;
  return *this;
}

template <typename T>
Red<T>::Red() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}
template <typename T>
Red<T>::Red(const Red& rhs)
    : capacity_{rhs.capacity_},
      size_{rhs.size_},
      arr_{new T[capacity_]},
      front_{rhs.front_},
      back_{rhs.back_} {
  std::copy(rhs.arr_ + front_, rhs.arr_ + back_ + 1, arr_ + front_);
}
template <typename T>
Red<T>::Red(Red&& tmp)
    : capacity_{tmp.capacity_},
      size_{tmp.size_},
      arr_{tmp.arr_},
      front_{tmp.front_},
      back_{tmp.back_} {
  tmp.arr_ = nullptr;
}
template <typename T>
Red<T>& Red<T>::operator=(const Red& rhs) {
  if (this == &rhs) return *this;
  copyRed(rhs);
  return *this;
}
template <typename T>
Red<T>::~Red<T>() {
  delete[] arr_;
  size_ = capacity_ = front_ = back_ = 0;
}
template <typename T>
template <typename U>
Red<T>& Red<T>::push(U&& element) {
  if (full()) realoc();
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
