#pragma once
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include <vector>

template<typename T>
class BinarySearchTree
{
private:
   template<typename T>
   struct Node
   {
     T key_;
     Node<T> *left_;
     Node<T> *right_;
     Node<T> *p_;
     Node(T key) : key_(key), left_(nullptr), right_(nullptr), p_(nullptr) {}
   };

   Node<T>* root_;

   Node<T>* searchNodeIterative (const T& key) const;
   void output(std::ostream& out, Node<T>* root) const;
   int getNumberOfNodes(const Node<T>* node) const;
   int getHeight(const Node<T>* node) const;
   void inorderWalk(Node<T>* node) const;
   void deleteTree(Node<T>* node);
   void inorderWalk(Node<T>* node, std::vector<T>& vec) const;
public:
   BinarySearchTree();
   BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
   BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
   BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
   BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;
   virtual ~BinarySearchTree();

   bool searchKeyIterative(const T& key) const;
   bool insertNode(const T& key);
   bool deleteNode(const T& key);
   void output(std::ostream& out) const;
   int getNumberOfNodes() const;
   int getHeight() const;
   void inorderWalkIterative() const;
   void inorderWalk() const;
   void walkByLevel() const;
   bool isSimilar(const BinarySearchTree<T>& other) const;
   bool isIdenticalKey(const BinarySearchTree<T> & other) const;
};
