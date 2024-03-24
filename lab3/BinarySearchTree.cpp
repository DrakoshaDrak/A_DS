#include "BinarySearchTree.h"


template<typename T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& scr) noexcept : root_(scr.root_)
{
  scr.root_ = nullptr;
}

template<typename T>
BinarySearchTree <T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& src) noexcept
{
  if(this != &src)
  {
    delete root_;
    root_ = src.root_;
    src.root_ = nullptr;
  }
  return *this;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
  deleteTree(root_);
}

template<typename T>
typename BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::searchNodeIterative (const T& key) const
{
  Node<T>* current = root_;

  while(current != nullptr)
  {
    if(key == current->key_)
    {
      return current;
    }

    if(current->left_ != nullptr)
    {
      current = current->left_;
    }
    else
    {
      current = current->right_;
    }
  }

  return nullptr;
}

template<typename T>
void BinarySearchTree<T>::deleteTree(Node<T>* node)
{
  if(node != nullptr)
  {
    deleteTree(node->left_);
    deleteTree(node->right_);
    delete node;
  }
}

template<typename T>
bool BinarySearchTree<T>::insertNode(const T& key)
{
  Node<T>* newNode = new Node<T>(key);
  if(root_ == nullptr)
  {
    root_ = newNode;
    return true;
  }
  
  Node<T>* current = root_;
  Node<T>* parent = nullptr;
  while(current != nullptr)
  {
    parent = current;
    if(key < current->key_)
    {
      current  = current->left_;
    }
    else if(key > current->key_)
    {
      current = current->right_;
    }
    else
    {
      delete newNode;
      return false;
    }
  }

  if (key < parent->key_)
  {
    parent->left_ = newNode;
  }
  else
  {
    parent->right_ = newNode;
  }

  return true;
  
}

template<typename T>
bool BinarySearchTree<T>::deleteNode(const T& key)
{
  Node<T>* current = root_;
  Node<T>* parent = nullptr;

  while(current != nullptr)
  {
    if(key == current->key_)
    {
      break;
    }
    parent = current;
    if(key < current->key_)
    {
      current = current->left_;
    }
    else
    {
      current = current->right_;
    }
  }

  if(current == nullptr)
  {
    return false;
  }

  if(current->left_ == nullptr && current->right_ == nullptr)
  {
    if(parent == nullptr)
    {
      root_ = nullptr;
    }
    else if(parent->left_ == current)
    {
      parent->left_ = nullptr;
    }
    else
    {
      parent->right_ = nullptr;
    }
    delete current;
  }

  else if(current->left_ == nullptr || current->right_ == nullptr)
  {
    Node<T>* child = (current->left_ != nullptr) ? current->left_ : current->right_;
    if(parent == nullptr)
    {
      root_ = child;
    }
    else if(parent->left_ == current)
    {
      parent->left_ = child;
    }
    else
    {
      parent->right_ = child;
    }
    delete current;
  }

  else
  {
    Node<T>* inheritor = current->right_;
    parent = current;
    while(inheritor->left_ != nullptr)
    {
      parent = inheritor;
      inheritor = inheritor->left_;
    }
    current->key_ = inheritor->key_;
    if(parent->left_ = inheritor)
    {        
      parent->left_ = inheritor->right_;
    }
    else
    {
      parent->right_ = inheritor->right_;
    }
    delete inheritor;
  }
  return true;
}

template<typename T>
bool BinarySearchTree<T>::searchKeyIterative(const T& key) const
{
  Node<T>* current = root_;
  while(current != nullptr)
  {
    if(key == current->key_)
    {
      return true;
    }
    else if(key < current->key_)
    {
      current = current->left_;
    }
    else
    {
      current = current->right_;
    }
  }
  return false;
}

template<typename T>
int BinarySearchTree<T>::getNumberOfNodes() const
{
  return getNumberOfNodes(root_);
}

template<typename T>
int BinarySearchTree<T>::getNumberOfNodes(const Node<T>* node) const
{
  if(node == nullptr)
  {
    return 0;
  }

  int countLeft = getNumberOfNodes(node->left_);
  int countRight = getNumberOfNodes(node->right_);

  return (1+countLeft+countRight);
}

template<typename T>
int BinarySearchTree<T>::getHeight() const
{
  return getHeight(root_);
}

template<typename T>
int BinarySearchTree<T>::getHeight(const Node<T>* node) const
{
  if(node == nullptr)
  {
    return -1;
  }

  int heightLeft = getHeight(node->left_);
  int heightRight = getHeight(node->right_);

  return (1+std::max(heightLeft,heightRight));
}

template<typename T>
void BinarySearchTree<T>::output(std::ostream& out) const
{
  output(out, root_);
}

template<typename T>
void BinarySearchTree<T>::output(std::ostream& out, Node<T>* root) const
{
  if(root == nullptr)
  {
    out << "()";
    return;
  }
  out << "(" << root->key_;
  out << " ";
  output(out, root->left_);
  out << " ";
  output(out, root->right_);
  out << ")";
}

template<typename T>
void BinarySearchTree<T>::inorderWalkIterative() const
{
  if(root_ == nullptr)
  {
    return;
  }

  StackArray<const Node<T>*> stackTree(100);
  const Node<T>* current = root_;

  while(current != nullptr || !stackTree.isEmpty())
  {
    while(current != nullptr)
    {
      stackTree.push(current);
      current = current->left_;
    }

    current = stackTree.pop();
    std::cout << current->key_ << " ";
    current = current->right_;
  }
}

template<typename T>
void BinarySearchTree<T>::inorderWalk() const
{
  inorderWalk(root_);
}

template<typename T>
void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
{
  if(node != nullptr)
  {
    inorderWalk(node->left_);
    std::cout << node->key_ << " ";
    inorderWalk(node->right_);
  }
}

template<typename T>
void BinarySearchTree<T>::inorderWalk(Node<T>* node, std::vector<T>& vec) const
{
  if(node != nullptr)
  {
    inorderWalk(node->left_, vec);
    vec.push_back(node->key_);
    inorderWalk(node->right_, vec);
  }
}

template<typename T> 
void BinarySearchTree<T>::walkByLevel() const
{
  if(root_ == nullptr)
  {
    return;
  }

  QueueArray<const Node<T>*> queueTree(100);
  queueTree.enQueue(root_);

  while(!queueTree.isEmpty())
  {
    const Node<T>* current = queueTree.deQueue();
    std::cout << current->key_ << " ";
    if(current->left_ != nullptr)
    {
      queueTree.enQueue(current->left_);
    }
    if(current->right_ != nullptr)
    {
      queueTree.enQueue(current->right_);
    }
  }
}

template<typename T>
bool BinarySearchTree<T>::isSimilar(const BinarySearchTree<T>& other) const
{
  std::vector<T> tree1;
  inorderWalk(root_, tree1);
  std::vector<T> tree2;
  inorderWalk(other.root_, tree2);

  if(tree1.size() != tree2.size())
  {
    return false;
  }

  for(size_t i = 0; i < tree1.size(); i++)
  {
    if(tree1[i] != tree2[i])
    {
      return false;
    }
  }
  return true;
}

template<typename T>
bool BinarySearchTree<T>::isIdenticalKey(const BinarySearchTree<T> & other) const
{
  std::vector<T> vec1, vec2;

  inorderWalk(root_, vec1);
  inorderWalk(other.root_, vec2);

  for(size_t i = 0; i < vec1.size(); i++)
  {
    for(size_t j = 0; j < vec2.size(); j++)
    {
      if(vec1[i] == vec2[j])
      {
        return true;
      }
    }
  }
  return false;
}