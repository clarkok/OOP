#ifndef _OOP_VECTOR_H_
#define _OOP_VECTOR_H_

#include <cstdlib>
#include <cstring>
#include <algorithm>

namespace OOP {
  class IndexOutofBounds {};

  template <typename T>
  class Vector
  {
    T *data_;
    int capacity_;
    int size_;
  public:
    Vector()
    : data_(nullptr), capacity_(0), size_(0)
    { }

    Vector(int capacity_)
    : data_(reinterpret_cast<T*>(std::malloc(capacity_ * sizeof(T)))),
      capacity_(capacity_),
      size_(size_)
    { }

    Vector(const Vector<T> &r)
    : data_(reinterpret_cast<T*>(std::malloc(r.capacity() * sizeof(T)))),
      capacity_(capacity_),
      size_(size_)
    { std::memcpy(data_, r.data_, size_ * sizeof(T)); }

    virtual ~Vector()
    { if (data_) std::free(data_); }

    T &
    operator [] (int index)
    {
      if (index >= size_ || index < 0)
        throw IndexOutofBounds();
      return data_[index];
    }

    decltype(capacity_)
    capacity() const
    { return capacity_; }

    decltype(size_)
    size() const
    { return size_; }

    decltype(capacity_)
    resize(int delta)
    {
      if (delta + capacity_ <= 0) {
        if (data_)
          std::free(data_);
        data_ = nullptr;
        capacity_ = size_ = 0;
        return 0;
      }
      int new_capacity = delta + capacity_;
      T* new_data = nullptr;
      if (new_capacity)
        new_data = reinterpret_cast<T*>(std::malloc(new_capacity * sizeof(T)));
      if (size_)
        std::memcpy(new_data, data_, size_ = std::min(size_, new_capacity));
      if (data_)
        std::free(data_);
      data_ = new_data;
      capacity_ = new_capacity;
      return capacity_;
    }

    template<class... Args>
    decltype(size_)
    push_back(Args&&... args)
    {
      if (size_ + 1 >= capacity_)
        resize(capacity_);
      new (data_ + size_) T(args...);
      return ++size_;
    }
  };
}

#endif // _OOP_VECTOR_H_
