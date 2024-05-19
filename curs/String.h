#pragma once
#include <iostream>
#include <sstream>
#include <cstring>
#include <exception>

const char* const S_R = "Index out of range in String";
const size_t maxSize = 25000;

class String
{
private:
  wchar_t* data_;
  size_t length_;
public:
  String() : data_(nullptr), length_(0) {}
  String(const wchar_t* str)
  {
    length_ = std::wcslen(str);
    data_ = new wchar_t[length_ + 1];
    wcscpy_s(data_, length_ + 1, str);
  }
  String(const String& other)
  {
    length_ = other.length_;
    if(other.data_)
    {
      data_ = new wchar_t[length_ + 1];
      wcscpy_s(data_, length_ + 1, other.data_);
    }
    else
    {
      data_ = nullptr;
    }
  }
  String(String&& other) noexcept
  {
    data_ = other.data_;
    length_ = other.length_;
    other.data_ = nullptr;
    other.length_ = 0;
  }
  ~String()
  {
    delete[] data_;
  }

  String& operator=(const String& other)
  {
    if(this != &other)
    {
      delete[] data_;
      length_ = other.length_;
      data_ = new wchar_t[length_ + 1];
      wcscpy_s(data_, length_ + 1, other.data_);
    }
    return *this;
  }
  wchar_t& operator[](size_t index)
  {
    if(index >= length_ || index < 0)
    {
      throw std::runtime_error(S_R);
    }
    return data_[index];
  }
  wchar_t& operator[](size_t index) const
  {
    if(index >= length_ || index < 0)
    {
      throw std::runtime_error(S_R);
    }
    return data_[index];
  }
  wchar_t* begin()
  {
    return data_;
  }
  wchar_t* end()
  {
    return data_ + length_;
  }
  const wchar_t* begin() const
  {
    return data_;
  }
  const wchar_t* end() const
  {
    return data_ + length_;
  }
  wchar_t* data() const
  {
    return data_;
  }
  size_t size() const
  {
    return length_;
  }
  friend std::wostream& operator<<(std::wostream& op, const String& str)
  {
    return op << str.data_;
  }
  String& operator+=(const String& other)
  {
    if(other.data_ == nullptr)
    {
      return *this;
    }
    if(data_ == nullptr)
    {
      length_ = other.length_;
      data_ = new wchar_t[length_ + 1];
      wcscpy_s(data_, length_ + 1, other.data_);
    }
    else
    {
      wchar_t* nData = new wchar_t[length_ + other.length_ + 1];
      wcscpy_s(nData, length_ + other.length_ + 1, data_);
      wcscat_s(nData, length_ + other.length_ + 1, other.data_);
      delete[] data_;
      data_ = nData;
      length_ += other.length_;
    }
    return *this;
  }
  String& operator+=(wchar_t ch)
  {
    wchar_t* nData = new wchar_t[length_ + 2];
    if(data_ != nullptr)
    {
      wcscpy_s(nData, length_ + 1, data_);
      delete[] data_;
    }
    nData[length_] = ch;
    nData[length_ + 1] = '\0';
    data_ = nData;
    length_++;
    return *this;
  }
  String operator+(const String& other) const
  {
    String rez;
    rez.length_ = length_ + other.length_;
    rez.data_ = new wchar_t[rez.length_ + 1];
    if(data_ != nullptr)
    {
      wcscpy_s(rez.data_, length_ + 1, data_);
    }
    if(other.data_ != nullptr)
    {
      wcscat_s(rez.data_, rez.length_ + 1, other.data_);
    }
    return rez;
  }

  void clear()
  {
    data_ = nullptr;
    length_ = 0;
  }

  friend std::wistream& operator>>(std::wistream& in, String& str)
  {
    delete[] str.data_;
    str.data_ = nullptr;
    str.length_ = 0;

    wchar_t temp[maxSize];
    in.getline(temp, sizeof(temp)/sizeof(temp[0]));
    str.length_ = std::wcslen(temp);
    str.data_ = new wchar_t[str.length_ + 1];
    wcscpy_s(str.data_, str.length_ +1, temp);
    return in;
  }

  bool empty()
  {
    return length_ == 0;
  }

  bool empty() const
  {
    return length_ == 0;
  }

  bool operator==(std::nullptr_t) const
  {
    return data_ == nullptr;
  }

  friend bool operator==(const String& str, std::nullptr_t)
  {
    return str.data_ == nullptr;
  }

  bool operator==(const String& other) const
  {
    return (std::wcscmp(data_, other.data_) == 0);
  }

};