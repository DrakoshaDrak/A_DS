#include "QuickSort.h"

template<typename T1, typename T2>
void quickSortPairs(Vector<Pair<T1, T2>>& pairs)
{
  if(pairs.getSize() <= 1)
  {
    return;
  }

  Pair<T1, T2> pivot = pairs[pairs.getSize() / 2];
  Vector<Pair<T1, T2>> left, right, equal;
  for (size_t i = 0; i < pairs.getSize(); ++i)
  {
    if(comparePair(pairs[i], pivot))
    {
      left.push_back(pairs[i]);
    }
    else if(comparePair(pivot, pairs[i]))
    {
      right.push_back(pairs[i]);
    }
    else
    {
      equal.push_back(pairs[i]);
    }
  }
  quickSortPairs(left);
  quickSortPairs(right);
  pairs.clear();
  for (size_t i = 0; i < left.getSize(); ++i)
  {
    pairs.push_back(left[i]);
  }
  for (size_t i = 0; i < equal.getSize(); ++i)
  {
    pairs.push_back(equal[i]);
  }
  for (size_t i = 0; i < right.getSize(); ++i)
  {
    pairs.push_back(right[i]);
  }
}

template<typename T1, typename T2>
bool comparePair(const Pair<T1, T2>& pair1, const Pair<T1, T2>& pair2)
{
  if(pair1.second_ > pair2.second_)
  {
    return true;
  }
  else if(pair1.second_ < pair2.second_)
  {
    return false;
  }
  else
  {
    return pair1.first_ < pair2.first_;
  }
}