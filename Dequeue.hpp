#pragma once
#include <algorithm>
#include <iostream>
#include <stddef.h>

namespace Types {
template <typename T>
class Dequeue {
  public:
  Dequeue();
  Dequeue(const Dequeue&);
  Dequeue(Dequeue&&);
  Dequeue& operator=(const Dequeue&);
  Dequeue& operator=(Dequeue&&);
  ~Dequeue();
  template <typename U>
  Dequeue& push_front(U&&);
  template <typename U>
  Dequeue& push_back(U&&);
  // Pop an element from the begin
  T pop_front();
  // Pop an element from the end
  T pop_back();
  T& front();
  T& back();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  void clear();
  friend std::ostream& operator<<(std::ostream& os, const Dequeue& dequeue) {
    os << "[";
    for (auto i = dequeue.front_; i <= dequeue.back_; ++i) {
      os << dequeue.arr_[i] << " ";
    }
    os << "]" << std::endl;
    return os;
  }

  private:
  void realloc();
  void copyDequeue(const Dequeue&);
  size_t capacity_;
  size_t size_;
  T* arr_;
  size_t back_{0};
  size_t front_{0};
};

template <typename T>
Dequeue<T>::Dequeue() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}
template <typename T>
void Dequeue<T>::copyDequeue(const Dequeue& other) {
  if (arr_) delete[] arr_;
  front_ = other.front_;
  back_ = other.back_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  if (arr_) arr_ = new T[capacity_];
  std::copy(other.arr_ + other.front_, other.arr_ + back_ + 1, arr_ + front_);
}
template <typename T>
Dequeue<T>::Dequeue(const Dequeue& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]},
      back_{other.back_}, front_{other.front_} {
  // back_ + 1 (include the last element from the array)
  std::copy(other.arr_ + front_, other.arr_ + back_ + 1, arr_ + front_);
}

template <typename T>
Dequeue<T>::Dequeue(Dequeue&& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_},
      back_{other.back_}, front_{other.front_} {
  other.arr_ = nullptr;
}
template <typename T>
Dequeue<T>& Dequeue<T>::operator=(const Dequeue& other) {
  if (this == &other) return *this;
  copyDequeue(other);
  return *this;
}
template <typename T>
Dequeue<T>& Dequeue<T>::operator=(Dequeue&& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  front_ = other.front_;
  back_ = other.back_;
  if (arr_) delete[] arr_;
  arr_ = other.arr_;
  other.arr_ = nullptr;
}
template <typename T>
Dequeue<T>::~Dequeue() {
  delete[] arr_;
  size_ = capacity_ = front_ = back_ = 0;
  arr_ = nullptr;
}
template <typename T>
void Dequeue<T>::realloc() {
  T* tmp = arr_;
  // Proizvoljno prosirenje kapaciteta (najcesce 1.5 ili 2 puta)
  capacity_ *= 1.5;
  arr_ = new T[capacity_];
  std::copy(tmp + front_, tmp + front_ + size_, arr_);
  delete[] tmp;
  // normalizacija indexa
  back_ = size_ - 1;
  front_ = 0;
}
template <typename T>
template <typename U>
Dequeue<T>& Dequeue<T>::push_front(U&& element) {
  if (full()) realloc();
  size_t index;
  if (front_ == 0 && !empty()) {
    // Ako nije moguce dodati na prvu poziciju, napraviti prostor za novi
    // element
    for (auto i = back_ + 1; i > front_; --i) {
      arr_[i] = arr_[i - 1];
    }
    index = 0;
    // Dodajemo element na pocetak, back_ moramo pomjeriti jednu poziciju desno
    // kako bi u svakom trenutku pokazivao na zadnji element u nizu.
    ++back_;
  } else {
    if (empty()) {
      // Dodajemo prvi element na pocetak
      index = 0;
    } else {
      // Pomjeriti front u lijevu stranu
      index = --front_;
    }
  }
  ++size_;
  arr_[index] = std::forward<U>(element);
  return *this;
}

template <typename T>
template <typename U>
Dequeue<T>& Dequeue<T>::push_back(U&& element) {
  if (full()) realloc();
  size_t index;
  if (empty()) {
    index = 0;
  } else {
    index = ++back_;
  }
  ++size_;
  arr_[index] = std::forward<U>(element);
  return *this;
}
template <typename T>
T Dequeue<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range{"The queue is empty"};
  }
  --size_;
  return arr_[front_++];
}

template <typename T>
T Dequeue<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range{"The queue is empty"};
  }
  --size_;
  // Ako imamo samo jedan element u nizu, back_ i front_ imaju potencijalno
  // vrijednost 0 (ne nuzno), back_-- ce u tom slucaju otici u minus. A kako je
  // tip size_t, back_-- ce dobiti ogromnu pozitivnu vrijednost. Da bi rijesili
  // taj slucaj vrsimo provjeru da li je back_ == 0. Skraceno pomocu ternarnog
  // operatora (Elvis operator).
  // Identicna implentacija:
  //   if (back_ != 0)
  //     return arr_[back_--];
  //   else
  //     return arr_[0];
  return arr_[back_ != 0 ? back_-- : 0];
}

template <typename T>
bool Dequeue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
bool Dequeue<T>::full() const {
  return back_ == capacity_;
}

template <typename T>
T& Dequeue<T>::front() {
  if (empty()) {
    throw std::out_of_range{"The Dequeue is empty"};
  }
  return arr_[front_];
}

template <typename T>
T& Dequeue<T>::back() {
  if (empty()) {
    throw std::out_of_range{"The Dequeue is empty"};
  }
  return arr_[back_];
}

template <typename T>
size_t Dequeue<T>::size() const {
  return size_;
}

template <typename T>
size_t Dequeue<T>::capacity() const {
  return capacity_;
}

template <typename T>
void Dequeue<T>::clear() {
  delete[] arr_;
  front_ = back_ = 0;
  size_ = capacity_ = 0;
  arr_ = nullptr;
}

} /* Types */
