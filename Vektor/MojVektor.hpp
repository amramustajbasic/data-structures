#pragma once
#include <algorithm>
#include <stdexcept>
class MojVektor {
   public:
    class Iterator;
    MojVektor();
    MojVektor(const std::initializer_list<int>& lista);
    MojVektor(const MojVektor&);
    MojVektor& operator=(const MojVektor& tmp);
    MojVektor(MojVektor&& tmp);
    MojVektor& operator=(MojVektor&& tmp);
    ~MojVektor();

    MojVektor& push_back(int element);
    MojVektor& push_front(int element);
    size_t size() const;
    int& at(size_t index) const;
    int& operator[](size_t index) const;
    void clear();
    void resize(size_t newSize);
    MojVektor& pop_back();
    MojVektor& pop_front();
    int& back() const;
    int& front() const;
    bool empty() const;
    bool full() const;
    size_t capacity() const;
    bool operator==(const MojVektor& tmp) const;
    bool operator!=(const MojVektor& other) const;

    Iterator begin() const;

    Iterator end() const;

    Iterator find(const int& element) const;
    Iterator rbegin() const;
    Iterator rend() const;
    Iterator erase(Iterator beginIt, Iterator endIt);
    Iterator insert(Iterator pos, int element);
    Iterator erase(Iterator pos);
    int* data();

   private:
    void realoc();
    size_t capacity_;
    size_t size_;
    int* arr_;
};
std::ostream& operator<<(std::ostream&, const MojVektor&);

class MojVektor::Iterator
    : public std::iterator<std::random_access_iterator_tag, int> {
   public:
    Iterator();
    Iterator(const Iterator& it);
    Iterator(Iterator&& it);
    Iterator(int* ptr);
    Iterator(int& element);
    Iterator& operator=(const Iterator& it);
    Iterator& operator=(Iterator&& it);
    bool operator<(const Iterator& it) const;
    bool operator>(const Iterator& it) const;
    bool operator<=(const Iterator& it) const;
    bool operator>=(const Iterator& it) const;
    int& operator*() const;
    int* operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    int* operator[](int index) const;
    size_t operator-(const Iterator& tmp);
    Iterator& operator--();
    Iterator operator--(int);
    Iterator operator+(size_t index);
    Iterator operator-(size_t index);
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;

    ~Iterator();

   private:
    int* ptr_;
};
