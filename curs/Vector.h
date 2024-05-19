#pragma once
#include <iostream>
#include "Pair.h"
#include "String.h"

template<typename T>
class Vector 
{
private:
  T* data_;
  size_t size_;
  size_t capacity_;
public:
  Vector();
  Vector(const Vector& other);
  ~Vector();

  void push_back(const T &value);
  T& operator[](size_t index);
  size_t getSize() const;
  T* begin();
  T* end();
  T* begin() const;
  T* end() const;
  void clear();

  Vector<T>& operator=(const Vector<T>& other);
  Pair<wchar_t, int> operator[](size_t index) const;
};
