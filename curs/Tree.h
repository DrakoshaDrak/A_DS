#pragma once
#include "Vector.h"
#include "Pair.h"
#include <iostream>
#include "String.h"

const char* E_ER = "The alphabet mast contain at least 2 elements.";
const char* T_ER = "Tree is empty.";
const char* S_EM = "Decryption string is empty.";

template<typename T>
class Tree
{
private:
  template<typename T>
   struct Node
   {
     wchar_t data_;
     String value_;
     Node<T> *left_;
     Node<T> *right_;
     Node(const T& data, String value) : data_(data), value_(value), left_(nullptr), right_(nullptr) {}
     Node() : data_(L'\0'), value_(L"\0"), left_(nullptr), right_(nullptr) {}
   };
   Node<T> *root_;

   void deleteTree(Node<T> *node)
   {
     if(node != nullptr)
     {
       deleteTree(node->left_);
       deleteTree(node->right_);
       delete node;
     }
   }

   void buildSubtree(Node<T>*& node, const Vector<Pair<wchar_t, int>>& freqs, String val)
   {
     if(freqs.getSize() == 1)
     {
       node->data_ = freqs[0].first_;
       node->value_ = val;
       return;
     }
     size_t index = 0;
     int minRashod = std::numeric_limits<int>::max();
     int maxSum = 0;
     Vector<Pair<wchar_t, int>> vec1;
     Vector<Pair<wchar_t, int>> vec2;
     for(size_t i = 0; i < freqs.getSize(); i++)
     {
       int tempSum = 0;
       for(size_t j = i + 1; j < freqs.getSize(); j++)
       {
         tempSum += freqs[j].second_;
       }
       maxSum += freqs[i].second_;
       if(((maxSum >= tempSum) || (maxSum <= tempSum))&& (std::abs(maxSum - tempSum) < minRashod))
       {
         vec1.push_back(freqs[i]);
         minRashod = std::abs(maxSum - tempSum);
       }
       else
       {
         index = i;
         break;
       }
     }
     for(size_t i = index; i < freqs.getSize(); i++)
     {
       vec2.push_back(freqs[i]);
     }
     node->value_ = val;
     node->left_ = new Node<T>();
     node->right_ = new Node<T>();
     buildSubtree(node->left_, vec1, L"0");
     buildSubtree(node->right_, vec2, L"1");
   }

   bool findElem(Node<T>* node, const wchar_t& value, String& rez)
   {
     if(node == nullptr)
     {
       return false;
     }
     if(findElem(node->right_, value, rez))
     {
       rez = node->value_ + rez;
       return true;
     }
     if(node->data_ == value)
     {
       rez = node->value_ + rez;
       return true;
     }
     if(findElem(node->left_, value, rez))
     {
       rez = node->value_ + rez;
       return true;
     }
     return false;
   }

   void decode(Node<T>* node, const String& str, String& rez, size_t& ind)
   {
     if(node == nullptr)
     {
       return;
     }
     if(node->left_ == nullptr && node->right_ == nullptr)
     {
       rez += node->data_;
       return;
     }
     if(ind < str.size())
     {
       if(str[ind] == L'0')
       {
         ind++;
         return decode(node->left_, str, rez, ind);
       }
       else if(str[ind] == L'1')
       {
         ind++;
         return decode(node->right_, str, rez, ind);
       }
     }
   }

public:
  Tree() : root_(new Node<T>()) {}
  ~Tree()
  {
    deleteTree(root_);
  }

  void buildTree(const Vector<Pair<wchar_t, int>>& frequency)
  {
    if(frequency.getSize() < 2)
    {
      throw std::runtime_error(E_ER);
    }

    buildSubtree(root_, frequency, L"");
  }

  String find(const wchar_t& value)
  {
    String rez = L"";
    findElem(root_, value, rez);
    return rez;
  }

  String decode(const String& str)
  {
    if(root_ == nullptr)
    {
      throw std::runtime_error(T_ER);
    }

    String rez = L"";
    size_t ind = 0;
    while(ind < str.size())
    {
      decode(root_, str, rez, ind);
    }
    if(rez.empty())
    {
      throw std::runtime_error(S_EM);
    }
    return rez;
  }
};