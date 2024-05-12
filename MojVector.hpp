#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
template <typename T>
class MojVector {
 public:
  class Iterator;
  MojVector() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}
  MojVector(const std::initializer_list<T>& lista)
      : capacity_{lista.size()}, size_{lista.size()}, arr_{new T[capacity_]} {
    std::copy(lista.begin(), lista.end(), arr_);
  }
  MojVector(const MojVector& copyObj)
      : capacity_{copyObj.capacity_},
        size_{copyObj.size_},
        arr_{new T[capacity_]} {
    std::copy(copyObj.arr_, copyObj.arr_ + size_, arr_);
  }

  MojVector(MojVector&& moveObj)
      : capacity_{moveObj.capacity_}, size_{moveObj.size_}, arr_{moveObj.arr_} {
    moveObj.arr_ = nullptr;
    moveObj.capacity_ = moveObj.size_ = 0;
  }
  MojVector& operator=(const MojVector& copyObj) {
    if (&copyObj == this) return *this;
    delete[] arr_;
    capacity_ = copyObj.capacity_;
    size_ = copyObj.size_;
    arr_ = new T[capacity_];
    std::copy(copyObj.arr_, copyObj.arr_ + size_, arr_);
    return *this;
  }
  MojVector& operator=(MojVector&& moveObj) {
    delete[] arr_;
    capacity_ = moveObj.capacity_;
    size_ = moveObj.size_;
    arr_ = moveObj.arr_;
    moveObj.arr_ = nullptr;

    moveObj.capacity_ = moveObj.size_ = 0;
    return *this;
  }
  ~MojVector() { delete[] arr_; }
  // vremenska kompleksnost O(1)
  MojVector& push_back(T element) {
    if (size_ == capacity_) realoc();
    arr_[size_++] = element;
    return *this;
  }

  size_t size() const { return size_; }
  // vremenska kompleksnost O(1)
  T& at(size_t index) const {
    if (index >= size_) throw std::out_of_range{"Index van opsega"};
    return arr_[index];
  }

  void realoc() {
    T* tmp = new T[capacity_];
    std::copy(arr_, arr_ + size_, tmp);
    delete[] arr_;
    capacity_ *= 2;
    arr_ = new T[capacity_];
    std::copy(tmp, tmp + size_, arr_);
    delete[] tmp;
  }

  // vremenska kompleksnost O(1)
  T& operator[](size_t index) const {
    if (index > size_ - 1 || index < 0)

      throw std::out_of_range{"Indeksiranje van granica"};
    else
      return arr_[index];
  }

  // vremenska kompleksnost O(1)
  void clear() {
    delete[] arr_;
    *this = MojVector{};
  }

  void resize(size_t newCap) {
    size_t tmpSize=newCap;
    T* tmp = new T[tmpSize];
    std::copy(arr_, arr_+tmpSize, tmp);
    delete [] arr_;
    arr_=new T[newCap];
    std::copy(tmp, tmp+tmpSize, arr_);
    while(size_<=newCap){
    this->push_back(0);
    ++size_;
    }
    size_ = tmpSize;
    capacity_=newCap;
    delete[]tmp;


  }
  // vremenska kompleksnost O(1)
  bool empty() const { return size_ == 0; }

  // vremenska kompleksnost O(1)
  MojVector& pop_back() {
    if (empty()) throw std::out_of_range{"Vektor je prazan"};
    --size_;
    return *this;
  }
  // vremenska kompleksnost O(1)
  T back() const {
    if (empty()) throw std::out_of_range{"Vektor je prazan"};
    return arr_[size_ - 1];
  }
  // vremenska kompleksnost O(1)
  T front() const {
    if (empty()) throw std::out_of_range{"Vektor je prazan"};
    return arr_[0];
  }

  // vremenska kompleksnost O(1)
  bool full() const { return size_ == capacity_; }
  // vremenska kompleksnost O(1)
  size_t capacity() const { return capacity_; }

  // vremenska kompleksnost O(1)
  bool operator==(const MojVector& vek) const {
    if (size_ == vek.size_) {
      for (auto i = 0u; i < size_; ++i) {
        if (vek.arr_[i] != arr_[i]) {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  // vremenska kompleksnost O(N)
  MojVector& push_front(T element) {
    if (full()) realoc();
    for (auto i = size_; i > 0; --i) {
      arr_[i] = arr_[i - 1];
    }
    arr_[0] = element;
    ++size_;
    return *this;
  }
  // vremenska kompleksnost O(1)
  bool operator!=(const MojVector& vek) const {
    return !(*this == vek);
  }
  // vremenska kompleksnost O(1)
  Iterator begin() const { return Iterator{arr_}; };
  // vremenska kompleksnost O(1)
  Iterator end() const { return Iterator{arr_ + size_}; }
  // vremenska kompleksnost O(1)
  Iterator find(T element) const {
    for (auto i = 0u; i < size_; ++i) {
      if (arr_[i] == element) return Iterator{arr_+i};
    }
    return end();
  };
  // vremenska kompleksnost O(1)
  Iterator rbegin() const {
    return std::reverse_iterator<const Iterator>(end());
  }
  // vremenska kompleksnost O(1)
  Iterator rend() const {
    return std::reverse_iterator<const Iterator>(begin());
  }

  // vremenska kompleksnost O(N)
  Iterator erase(Iterator pos);

  // vremenska kompleksnost O(N)
  MojVector& insert(Iterator it, T element);

  Iterator erase(Iterator beginIt, Iterator endIt);

 private:
  size_t capacity_;
  size_t size_;
  T* arr_;
};
template <typename T>
class MojVector<T>::Iterator : public std::iterator<std::random_access_iterator_tag, T> {
 public:
  Iterator() : ptr_{nullptr} {}
  Iterator(const Iterator& it) : ptr_{it.ptr_} {}
  Iterator(Iterator&& it) : ptr_{it.ptr_} { it.ptr_ = nullptr; }
  Iterator(T* ptr) : ptr_{ptr} {}
  Iterator(T& element) : ptr_{&element} {}
  Iterator& operator=(const Iterator& it) {
    if (&it != this) ptr_ = it.ptr_;
    return *this;
  }
  Iterator& operator=(Iterator&& it) {
    ptr_ = it.ptr_;
    it.ptr_ = nullptr;
    return *this;
  }
  bool operator<(const Iterator& it) const{ return ptr_ < it.ptr_; }
  bool operator>(const Iterator& it) { return ptr_ > it.ptr_; }
  bool operator<=(const Iterator& it) const{ return ptr_ <= it.ptr_; }
  bool operator>=(const Iterator& it) { return ptr_ >= it.ptr_; }
  T& operator*() const { return *ptr_; }
  Iterator& operator++() {
    ++ptr_;
    return *this;
  }
  Iterator operator++(int) {
    auto tmpIt = *this;
    ++ptr_;
    return tmpIt;
  }
  size_t operator-(const Iterator& tmp) { return ptr_ - tmp.ptr_; }
  Iterator& operator--() {
    --ptr_;
    return *this;
  }
  Iterator operator--(int) {
    auto tmpIt = *this;
    --ptr_;
    return tmpIt;
  }
  Iterator operator+(size_t index) { return Iterator{ptr_ + index}; }
  Iterator operator-(size_t index) { return Iterator{ptr_ - index}; }
  bool operator==(const Iterator& it) const { return it.ptr_ == ptr_; }
  bool operator!=(const Iterator& it) const { return !(*this == it); }

  ~Iterator() { ptr_ = nullptr; }

 private:
  T* ptr_;
};
template <typename T>
typename MojVector<T>::Iterator MojVector<T>::erase(Iterator pos) {
  if (pos == end()) return end();
  auto ret = pos;
  auto it = pos + 1;
  while (it != end()) {
    *pos++ = *it++;
  }
  --size_;
  return ret;
}

template <typename T>
MojVector<T>& MojVector<T>::insert(typename MojVector<T>::Iterator pos,
                                   T element) {
  T* new_arr = new T[capacity_ + 1];
  MojVector<T>::Iterator it = begin();
  int i = 0;
  while (it != pos) {
    new_arr[i] = *it;
    i++;  // pomjeramo se na sljedece mjesto u nizu
    it++;
  }
  new_arr[i] = element;
  i++;
  it = end();
  while (pos != it) {
    new_arr[i] = *pos;
    pos++;
    i++;
  }
  delete[] arr_;
  arr_ = new_arr;
  capacity_++;
  size_++;
  return *this;
}
template <typename T>
typename MojVector<T>::Iterator MojVector<T>::erase(Iterator beginIt,
                                                    Iterator endIt) {
  if (beginIt == endIt) return endIt;
  auto start = beginIt;
  auto kraj = endIt;
  while (kraj != end()) {
    *start++ = *kraj++;
  }
  size_t broj = endIt - beginIt;
  size_ -= broj;
  return kraj;
}


