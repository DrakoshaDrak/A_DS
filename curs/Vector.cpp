#include "Vector.h"

const char* const O_R = "Index out of range in Vector";

template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template<typename T>
Vector<T>::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_)
{
  data_ = new T[capacity_];
  for(size_t i = 0; i < size_; i++)
  {
    data_[i] = other.data_[i];
  }
}

template<typename T>
Vector<T>::~Vector()
{
  clear();
}

template<typename T>
void Vector<T>::push_back(const T &value)
{
  if(size_ >= capacity_)
  {
    if(capacity_ == 0)
    {
      capacity_ = 1;
    }
    else
    {
      capacity_ *= 2;
    }
    T* newData = new T[capacity_];
    for(size_t i = 0; i < size_; i++)
    {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
  }
  data_[size_++] = value;
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
  if(index >= size_ || index < 0)
  {
    throw std::runtime_error(O_R);
  }
  return data_[index];
}

template<typename T>
size_t Vector<T>::getSize() const
{
  return size_;
}

template<typename T>
T* Vector<T>::begin()
{
  return data_;
}

template<typename T>
T* Vector<T>::end()
{
  return data_ + size_;
}

template<typename T>
T* Vector<T>::begin() const
{
  return data_;
}

template<typename T>
T* Vector<T>::end() const
{
  return data_ + size_;
}

template<typename T>
void Vector<T>::clear() 
{ 
  if(data_)
  {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
  if(this != &other)
  {
    clear();
    if(capacity_ < other.capacity_)
    {
      delete[] data_;
      data_ = new T[other.capacity_];
      capacity_ = other.capacity_;
    }
    size_ = other.size_;
    for(size_t i = 0; i < size_; i++)
    {
      data_[i] = other.data_[i];
    }
  }
  return *this;
}

template<typename T>
Pair<wchar_t, int> Vector<T>::operator[](size_t index) const
{
  if(index >= size_ || index < 0)
  {
    throw std::runtime_error(O_R);
  }
  return Pair<wchar_t, int>(data_[index].first_, data_[index].second_);
}