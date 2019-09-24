#ifndef HNODO
#define HNODO
#include <iostream>

template <typename T>
void swapp(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
class Node{
public:
  T key;
  Node<T> *left, *right;
  Node(T key){
    this->key = key;
    this->left = this->right = nullptr;
  }
  void autodelete()
  {
    if(left){left->autodelete();delete left;}
    if(right){right->autodelete();delete right;}
  }
  void insert(Node<T> *value)
  {
    if(value->key > key)
    {
      if(right)
      {
        right->insert(value);
      }
      else
      {
        right = value;
      }
    }
    else
    {
      if(left)
      {
        left->insert(value);
      }
      else
      {
        left = value;
      }
    }
  }
  Node<T>* getmax()
  {
    if(right)
    {
      return right->getmax();
    }
    else
    {
      return this;
    }
  }
  Node<T>* getmin()
  {
    if(left)
    {
      return left->getmin();
    }
    else
    {
      return this;
    }
  }
  int height()
  {
    int valright = (right)? right->height() : 0;
    int valleft = (left)? left->height() : 0;
    return (valright > valleft)? valright+1 : valleft+1;
  }
  void inorder()
  {
    if(left){left->inorder();}
    std::cout << key << " ";
    if(right){right->inorder();}
  }
  void preorder()
  {
    std::cout << key << " ";
    if(left){left->preorder();}
    if(right){right->preorder();}
  }
  void postorder()
  {
    if(left){left->postorder();}
    if(right){right->postorder();}
    std::cout << key << " ";
  }
};

#endif
