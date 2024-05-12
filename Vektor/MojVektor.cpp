#include "MojVektor.hpp"

#include <iostream>
#include <iterator>
MojVektor::MojVektor() : capacity_{10}, size_{0}, arr_{new int[capacity_]} {}
MojVektor::MojVektor(const std::initializer_list<int>& lista)
    : capacity_{lista.size()}, size_{lista.size()}, arr_{new int[capacity_]} {
    std::copy(lista.begin(), lista.end(), arr_);
}
MojVektor::MojVektor(const MojVektor& tmp)
    : capacity_{tmp.capacity_}, size_{tmp.size_}, arr_{new int[capacity_]} {
    std::copy(tmp.arr_, tmp.arr_ + size_, arr_);
}
MojVektor& MojVektor::operator=(const MojVektor& tmp) {
    if (this == &tmp) {
        return *this;
    }
    if (arr_ != nullptr) {
        delete[] arr_;
    }
    capacity_ = tmp.capacity_;
    size_ = tmp.size_;
    arr_ = new int[capacity_];
    std::copy(tmp.arr_, tmp.arr_ + size_, arr_);
    return *this;
}
MojVektor::MojVektor(MojVektor&& tmp)
    : capacity_{tmp.capacity_}, size_{tmp.size_}, arr_{tmp.arr_} {
    tmp.capacity_ = 0;
    tmp.size_ = 0;
    tmp.arr_ = nullptr;
}
MojVektor& MojVektor::operator=(MojVektor&& tmp) {
    if (arr_ != nullptr) {
        delete[] arr_;
    }
    capacity_ = tmp.capacity_;
    size_ = tmp.size_;
    arr_ = tmp.arr_;
    tmp.capacity_ = 0;
    tmp.size_ = 0;
    tmp.arr_ = nullptr;
    return *this;
}
MojVektor::~MojVektor() { clear(); }
MojVektor& MojVektor::push_back(int element) {
    if (size_ == capacity_) {
        realoc();
    }
    arr_[size_] = element;
    size_++;
    return *this;
}
MojVektor& MojVektor::push_front(int element) {
    if (size_ == capacity_) {
        realoc();
    }
    for (int i = size_; i > 0; --i) {
        arr_[i] = arr_[i - 1];
    }
    arr_[0] = element;
    ++size_;
    return *this;
}
size_t MojVektor::size() const { return size_; }
int& MojVektor::at(size_t index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range{"Invalid index"};
    }
    return arr_[index];
}
int& MojVektor::operator[](size_t index) const { return arr_[index]; }
void MojVektor::clear() {
    size_ = 0;
    capacity_ = 0;
    delete[] arr_;
    arr_ = nullptr;
}
void MojVektor::resize(size_t newSize) {
    if (newSize <= size_) {
        size_ = newSize;
    } else {
        size_t tmpSize = newSize;
        int* tmp = new int[tmpSize];
        std::copy(arr_, arr_ + tmpSize, tmp);
        delete[] arr_;
        arr_ = new int[newSize];
        std::copy(tmp, tmp + tmpSize, arr_);

        while (size_ < newSize) {
            this->push_back(0);
            ++size_;
        }
        size_ = tmpSize;
        capacity_ = newSize;
        delete[] tmp;
    }
}
MojVektor& MojVektor::pop_back() {
    if (empty()) {
        throw std::out_of_range{"Vector is empty"};
    }
    size_--;
    return *this;
}
MojVektor& MojVektor::pop_front() {
    if (size_ == 0) throw std::out_of_range{"Vector is empty"};
    for (int i = 0; i < size_ - 1; ++i) {
        arr_[i] = arr_[i + 1];
    }
    --size_;
    return *this;
}
int& MojVektor::back() const {
    if (size_ == 0) throw std::out_of_range{"Vector is empty"};

    return arr_[size_ - 1];
}
int& MojVektor::front() const {
    if (size_ == 0) throw std::out_of_range{"Vector is empty"};
    return arr_[0];
}
// Vraca true ako je vektor prazan
bool MojVektor::empty() const { return size_ == 0; }
bool MojVektor::full() const { return capacity_ == size_; }

// Vraca kapacitet vektora
size_t MojVektor::capacity() const { return capacity_; }
// Omogucava poredjenje dva objekta tipa MojVektor
bool MojVektor::operator==(const MojVektor& tmp) const {
    if (tmp.size_ != size_) {
        return false;
    }
    if (tmp.arr_ == arr_) {
        return true;
    }
    for (int i = 0; i < tmp.size_; ++i) {
        if (tmp[i] != arr_[i]) {
            return false;
        }
    }
    return true;
}
bool MojVektor::operator!=(const MojVektor& tmp) const {
    return !(*this == tmp);
}

void MojVektor::realoc() {
    int* tmp = new int[capacity_];
    std::copy(arr_, arr_ + size_, tmp);
    delete[] arr_;
    capacity_ *= 2;
    arr_ = new int[capacity_];
    std::copy(tmp, tmp + size_, arr_);
    delete[] tmp;
    tmp = nullptr;
}
std::ostream& operator<<(std::ostream& os, const MojVektor& tmp) {
    os << "{";
    for (auto i = 0; i < tmp.size(); ++i) {
        if (i == tmp.size() - 1) {
            os << tmp[i];
            break;
        }
        os << tmp[i] << ", ";
    }
    os << "}";
    return os;
}
int* MojVektor::data() { return arr_; }
MojVektor::Iterator MojVektor::begin() const { return Iterator{arr_}; }
MojVektor::Iterator MojVektor::end() const { return Iterator{arr_ + size_}; }
MojVektor::Iterator MojVektor::rbegin() const {
    return end()-1;
}
MojVektor::Iterator MojVektor::rend() const {
    return begin()-1;
}

MojVektor::Iterator::Iterator() : ptr_{nullptr} {}
MojVektor::Iterator::Iterator(const Iterator& it) : ptr_{it.ptr_} {}
MojVektor::Iterator::Iterator(Iterator&& it) : ptr_{it.ptr_} {
    it.ptr_ = nullptr;
}
MojVektor::Iterator::Iterator(int* ptr) : ptr_{ptr} {}
MojVektor::Iterator::Iterator(int& element) : ptr_{&element} {}
MojVektor::Iterator& MojVektor::Iterator::operator=(const Iterator& it) {
    ptr_ = it.ptr_;
    return *this;
}
MojVektor::Iterator& MojVektor::Iterator::operator=(Iterator&& it) {
    ptr_ = it.ptr_;
    it.ptr_ = nullptr;
    return *this;
}
bool MojVektor::Iterator::operator<(const Iterator& it) const {
    return ptr_ < it.ptr_;
}
bool MojVektor::Iterator::operator>(const Iterator& it) const {
    return ptr_ > it.ptr_;
}
bool MojVektor::Iterator::operator<=(const Iterator& it) const {
    return ptr_ <= it.ptr_;
}
bool MojVektor::Iterator::operator>=(const Iterator& it) const {
    return ptr_ >= it.ptr_;
}
int& MojVektor::Iterator::operator*() const { return *ptr_; }
int* MojVektor::Iterator::operator->() const { return ptr_; }
int* MojVektor::Iterator::operator[](int index) const { return ptr_ + index; }
MojVektor::Iterator& MojVektor::Iterator::operator++() {
    ++ptr_;
    return *this;
}
MojVektor::Iterator MojVektor::Iterator::operator++(int) {
    auto tmpIt = *this;
    ++ptr_;
    return tmpIt;
}
size_t MojVektor::Iterator::operator-(const Iterator& tmp) {
    return ptr_ - tmp.ptr_;
}
MojVektor::Iterator& MojVektor::Iterator::operator--() {
    --ptr_;
    return *this;
}
MojVektor::Iterator MojVektor::Iterator::operator--(int) {
    auto tmpIt = *this;
    --ptr_;
    return tmpIt;
}
MojVektor::Iterator MojVektor::Iterator::operator+(size_t index) {
    return Iterator{ptr_ + index};
}
MojVektor::Iterator MojVektor::Iterator::operator-(size_t index) {
    return Iterator{ptr_ - index};
}
bool MojVektor::Iterator::operator==(const Iterator& it) const {
    return it.ptr_ == ptr_;
}
bool MojVektor::Iterator::operator!=(const Iterator& it) const {
    return !(*this == it);
}

MojVektor::Iterator::~Iterator() { ptr_ = nullptr; }

MojVektor::Iterator MojVektor::find(const int& element) const {
    for (auto i = 0; i < size_; i++) {
        if (arr_[i] == element) {
            return Iterator{arr_ + i};
        }
    }
    return end();
}

MojVektor::Iterator MojVektor::erase(Iterator pos) {
    if (pos == end()) return end();
    auto ret = pos;
    auto it = pos + 1;
    while (it != end()) {
        *pos = *it;
    }
    ++pos;
    ++it;
    --size_;
    return ret;
}
MojVektor::Iterator MojVektor::erase(Iterator beginIt, Iterator endIt) {
    if (beginIt == endIt) return endIt;
    auto start = beginIt;
    auto kraj = endIt;
    auto ret1 = endIt;
    while (kraj != end()) {
        *start++ = *kraj++;
    }
    size_t broj = endIt - beginIt;
    if (endIt == end()) {
        size_ -= broj;
        ret1 = end();
    } else {
        size_ -= broj;
    }
    return ret1;
}

MojVektor::Iterator MojVektor::insert(Iterator pos, int element) {
    if (pos == end()) throw std::out_of_range{"Out of range"};
    int* new_arr = new int[capacity_ + 1];
    MojVektor::Iterator it = begin();
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
    return find(element);
}

