#pragma once

const int QMAX = 100;

template<typename T>
class Queue
{
public:
  virtual ~Queue() {}
  virtual void enQueue(const T& e) = 0;
  virtual T deQueue() = 0;
  virtual bool isEmpty() = 0;
};

template<typename T>
class QueueArray : Queue<T>
{
private:
  T* arr_;
  int begin_, end_, size_;
public:
  QueueArray(int size) : size_(size), begin_(-1), end_(-1)
  {
    arr_ = new T[size_];
  }

  ~QueueArray()
  {
    delete[] arr_;
  }

  void enQueue(const T& e) override
  {
    if(isEmpty())
    {
      begin_ = end_ = 0;
    }
    else
    {
      end_ = (end_ + 1) % size_;
    }
    arr_[end_] = e;
  }

  T deQueue() override
  {
    T tempArr = arr_[begin_];
    if(begin_ == end_)
    { 
      begin_ = end_ = -1;
    }
    else
    {
      begin_ = (begin_ + 1) % size_;
    }
    return tempArr;
  }

  bool isEmpty() override
  {
    return begin_ ==-1 && end_ == -1;
  }
};