#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Vector.h"
#include "Pair.h"
#include "QuickSort.h"
#include "Tree.h"
#include "String.h"

class ShannonFano
{
private:
  Vector<wchar_t> alphabet_;
  size_t strSize_;
  Vector<Pair<wchar_t, int>> absolutFrequ_;
  Tree<Pair<wchar_t, int>> tree_;
public:

  ShannonFano() = default;

  ShannonFano(ShannonFano&& other) noexcept : alphabet_(std::move(other.alphabet_)),
                                              strSize_(other.strSize_),
                                              absolutFrequ_(std::move(other.absolutFrequ_)) {}

  void findUniqChar(const String &str)
  {
    int count = 0;
    strSize_ = str.size();
    for(wchar_t ch : str)
    {
      bool found = false;
      for(auto& itm : absolutFrequ_)
      {
        if(itm.first_ == ch)
        {
          itm.second_++;
          found = true;
          break;
        }
      }
      if(!found)
      {
        absolutFrequ_.push_back({ch, 1});
      }
    }
  }

  void absolutSort()
  {
    quickSortPairs(absolutFrequ_);
  }

  Vector<Pair<wchar_t, int>> getFrequ() const
  {
    return absolutFrequ_;
  }

  void print()
  {
    for(auto& itm : absolutFrequ_)
    {
      std::wcout << itm.first_ << " " << itm.second_ << "\n";
    }
  }

  void treeSet()
  {
    tree_.buildTree(absolutFrequ_);
  }

  String treeDrowRez(const wchar_t ch)
  {
    String fRez = tree_.find(ch);
    return fRez;
  }

  String treeDecode(const String& str)
  {
    String decode = tree_.decode(str);
    std::wcout << decode;
    return decode;
  }
  void alphabetFile(Vector<Pair<wchar_t, int>> vec)
  {
    absolutFrequ_ = vec;
  }
};