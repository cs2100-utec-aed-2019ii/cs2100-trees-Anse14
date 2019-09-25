#ifndef HTREE
#define HTREE
#include "./Node.h"
#include "./circularlist.h"
#include <iostream>

template <typename T>
class Tree {
public:
  Node<T> * root;
  CircularList<Node<T>*> *elements;
  Tree():root(nullptr){elements = new CircularList<Node<T>*>;}
  ~Tree()
  {
    delete elements;
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
    updatelist();
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
    updatelist();
  }
  int height()
  {
    return (root->height());
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
  void updatelist()
  {
    elements->clear();
    root->updatelist(elements, 1, height());
  }
  void isComplete()
  {
    return root->isComplete();
  }
  bool isBST()
  {
    return root->isBSTnode();
  }
  static bool equal(Tree<T> *a, Tree<T> *b)
  {
    return Node<T>::equal(a->root, b->root);
  }
};

#endif
