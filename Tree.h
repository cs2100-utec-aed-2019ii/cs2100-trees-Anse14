#ifndef HTREE
#define HTREE
#include "./Node.h"
#include <iostream>

template <typename T>
class Tree {
public:
  Node<T> * root;
  Tree():root(nullptr){}
  ~Tree()
  {
    if(root){root->autodelete();delete root;}
  }
  void insert(T value)
  {
    Node<T> *temp = new Node<T>(value);
    insert(temp);
  }
  void insert(Node<T> *value)
  {
    value->right = nullptr;
    value->left = nullptr;
    if(root)
    {
      if(value->key > root->key)
      {
        if(root->right)
        {
          root->right->insert(value);
        }
        else
        {
          root->right = value;
        }
      }
      else
      {
        if(root->left)
        {
          root->left->insert(value);
        }
        else
        {
          root->left = value;
        }
      }
    }
    else
    {
      root = value;
    }
  }
  void deleten(Node<T> *&value)
  {
    Node<T> *temp;
    if(value->left)
    {
      temp = value->left->getmax();
      swapp(value->key, temp->key);
      deleten(temp);
    }
    else if(value->right)
    {
      temp = value->right->getmin();
      swapp(value->key, temp->key);
      deleten(temp);
    }
    else
    {
      delete value;
      value = nullptr;
    }
  }
  int height()
  {
    return (root->height())+1;
  }
  void inorder()
  {
    root->inorder();
    std::cout << std::endl;
  }
  void preorder()
  {
    root->preorder();
    std::cout << std::endl;
  }
  void postorder()
  {
    root->postorder();
    std::cout << std::endl;
  }
};

#endif
