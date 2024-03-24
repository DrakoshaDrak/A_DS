#pragma once
#include <iostream>

const int SMAX = 100;

template<typename T>
class Stack
{
public:
  virtual ~Stack() {}
  virtual void push(const T& e) = 0;
  virtual T pop() = 0;
  virtual bool isEmpty() = 0;
  virtual bool isFull() = 0;
};

template<typename T>
class StackArray : public Stack<T>
{
private:
  T* stack_;
  int size_;
  int top_;
public:
  StackArray(int size) : size_(size), top_(-1)
  {
    stack_ = new T[size_];
  }

  ~StackArray()
  {
    delete[] stack_;
  }

  void push(const T& elem) override
  {
    stack_[++top_] = elem;
  }
  
  T pop() override
  {
    return stack_[top_--];
  }

  bool isEmpty() override
  {
    return top_ == -1;
  }

  bool isFull() override
  {
    return !(top_ == -1);
  }
};