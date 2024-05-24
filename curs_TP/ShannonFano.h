#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "Tree.h"

bool comparePair(const std::pair<wchar_t, int> pair1, const std::pair<wchar_t, int> pair2);

class ShannonFano
{
private:
  std::vector<std::wstring> alphabet_;
  size_t strSize_;
  std::vector<std::pair<wchar_t, int>> absolutFrequ_;
  Tree<std::pair<std::wstring, int>> tree_;
public:

  ShannonFano() = default;

  ShannonFano(ShannonFano&& other) noexcept : alphabet_(std::move(other.alphabet_)),
                                              strSize_(other.strSize_),
                                              absolutFrequ_(std::move(other.absolutFrequ_)) {}

  void findUniqChar(const std::wstring &str)
  {
    int count = 0;
    strSize_ = str.size();
    for(wchar_t ch : str)
    {
      bool found = false;
      for(auto& itm : absolutFrequ_)
      {
        if(itm.first == ch)
        {
          itm.second++;
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
    std::sort(absolutFrequ_.begin(), absolutFrequ_.end(), comparePair);
  }

  std::vector<std::pair<wchar_t, int>> getFrequ() const
  {
    return absolutFrequ_;
  }

  void print()
  {
    for(auto& itm : absolutFrequ_)
    {
      std::wcout << itm.first << " " << itm.second << "\n";
    }
  }

  void treeSet()
  {
    tree_.buildTree(absolutFrequ_);
  }

  std::wstring treeDrowRez(const wchar_t ch)
  {
    std::wstring fRez = tree_.find(ch);
    return fRez;
  }

  std::wstring treeDecode(const std::wstring& str)
  {
    std::wstring decode = tree_.decode(str);
    std::wcout << decode;
    return decode;
  }
  void alphabetFile(std::vector<std::pair<wchar_t, int>> vec)
  {
    absolutFrequ_ = vec;
  }
};

bool comparePair(const std::pair<wchar_t, int> pair1, const std::pair<wchar_t, int> pair2)
{
  if(pair1.second > pair2.second)
  {
    return true;
  }
  else if(pair1.second < pair2.second)
  {
    return false;
  }
  else
  {
    return pair1.first < pair2.first;
  }
}