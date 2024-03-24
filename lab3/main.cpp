#include <iostream>
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include "Queue.h"

#define boolStr(b) ((b) ? "True\n" : "False\n");

void test1();
void test2();
void test3();
void test4();

int main()
{
    setlocale(LC_ALL, "ru");

  int prog = 0;
  std::cout << "Какой тест вы хотите запустить \n 1) Корректная отработка всех методов. \n 2) Запись двух одинаковых значений. \n 3) Удаление несуществующего значения. \n 4) Нахождение несуществующего значения. \nВведите номер теста: ";
  std::cin >> prog;

  switch (prog)
  {
  case 1:
    test1();
    break;
  case 2:
    test2();
    break;
  case 3:
    test3();
    break;
  case 4:
    test4();
    break;
  default:
    std::cout << "Вы не выбрали ни один тест, выход.";
    break;
  }
  return 0;
}

void test1()
{
  BinarySearchTree<int> tree;
  tree.insertNode(10);
  tree.insertNode(5);
  tree.insertNode(2);
  tree.insertNode(19);
  tree.insertNode(9);
  tree.insertNode(4);
  tree.insertNode(11);
  tree.insertNode(23);
  tree.insertNode(7);
  BinarySearchTree<int> tree2;
  tree2.insertNode(10);
  tree2.insertNode(5);
  tree2.insertNode(2);
  tree2.insertNode(19);
  tree2.insertNode(9);
  tree2.insertNode(4);
  tree2.insertNode(11);
  tree2.insertNode(23);
  tree2.insertNode(7);
  std::cout << boolStr(tree.searchKeyIterative(9));
  std::cout << boolStr(tree.deleteNode(11));
  tree.output(std::cout);
  std::cout << "\n";
  std::cout << tree.getNumberOfNodes() << "\n";
  std::cout << tree.getHeight() << "\n";
  tree.inorderWalkIterative();
  std::cout << "\n";
  tree.inorderWalk();
  std::cout << "\n";
  tree.walkByLevel();
  std::cout << "\n";
  std::cout << boolStr(tree.isSimilar(tree2));
  std::cout << boolStr(tree.isIdenticalKey(tree2));
}

void test2()
{
  BinarySearchTree<int> tree;
  tree.insertNode(10);
  std::cout << boolStr(tree.insertNode(5));
  tree.insertNode(2);
  std::cout << boolStr(tree.insertNode(5));
}

void test3()
{
  BinarySearchTree<int> tree2;
  tree2.insertNode(10);
  tree2.insertNode(5);
  tree2.insertNode(2);
  tree2.insertNode(19);
  std::cout << boolStr(tree2.deleteNode(20));
}

void test4()
{
  BinarySearchTree<int> tree2;
  tree2.insertNode(10);
  tree2.insertNode(5);
  tree2.insertNode(2);
  tree2.insertNode(19);
  std::cout << boolStr(tree2.searchKeyIterative(1));
}