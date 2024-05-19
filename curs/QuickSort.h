#pragma once
#include "Vector.h"
#include "Pair.h"

template<typename T1, typename T2>
void quickSortPairs(Vector<Pair<T1, T2>>& pairs);
template<typename T1, typename T2>
bool comparePair(const Pair<T1, T2>& pair1, const Pair<T1, T2>& pair2);