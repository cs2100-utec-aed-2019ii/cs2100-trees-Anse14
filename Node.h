#ifndef HNODO
#define HNODO
#include "./circularlist.h"
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
    if(value->key >= key)
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
  void updatelist(CircularList<Node<T>*> *&list, int expected, int realsize)
  {
    if(left || right)
    {
      if(left){left->updatelist(list, expected+1, realsize);}
      if(right){right->updatelist(list, expected+1, realsize);}
    }
    else
    {
      if(expected == realsize){list->push_back(this);}
    }
  }
  void get_leafs(CircularList<Node<T>*> *&list)
  {
    if(!left && !right)
    {
      list->push_back(this);
      return;
    }
    if(left){left->get_leafs(list);};
    if(right){right->get_leafs(list);};
  }
  bool get_path(Node<T> *value, CircularList<T> *list)
  {
    if(value == left || value == right)
    {
      list->push_back(value->key);
    }
  }
  bool isFull(int expected, int height)
  {
    if(expected != (height-1))
    {
      bool result = false;
      bool result2 = false;
      if(left){result = left->isFull(expected+1,height);}
      if(right){result2 = right->isFull(expected+1, height);}
      return (result && result2);
    }
    return (!!right && !!left);
  }
  bool isBSTnode()
  {
    bool leftt = (left)? (left->key < key) && left->isBSTnode() : true ;
    bool rightt = (right)? (right->key >= key) && right->isBSTnode() : true ;
    return (leftt && rightt);
  }
  Node<T>* ancestor(Node<T> *value)
  {
    if(left == value || right == value){return this;}
    else
    {
      Node<T> *temp = (left)? left->ancestor(value) : nullptr;
      Node<T> *temp2 = (right)? right->ancestor(value) : nullptr;
      return (temp)? temp : temp2;
    }
  }
  CircularList<std::string>* get_level(int a)
  {
    CircularList<std::string> *return_value = new CircularList<std::string>;
    lvl(0, a, return_value);
    return return_value;
  }
  void lvl(int position, int expected, CircularList<std::string>  *&list)
  {
    if(position == expected)
    {
      list->push_back(std::to_string(key));
      return;
    }
    if(left){left->lvl(position+1, expected, list);} else {list->push_back(" ");};
    if(right){right->lvl(position+1, expected, list);} else {list->push_back(" ");};
  }
  CircularList<Node<T>*>* get_leveln(int a)
  {
    CircularList<Node<T>*> *return_value = new CircularList<Node<T>*>;
    lvl(0, a, return_value);
    return return_value;
  }
  void lvl(int position, int expected, CircularList<Node<T>*> *&list)
  {
    if(position == expected)
    {
      list->push_back(this);
      return;
    }
    if(left){left->lvl(position+1, expected, list);}
    if(right){right->lvl(position+1, expected, list);}
  }
  static bool equal(Node<T> *a, Node<T> *b)
  {
    bool leftt = a->left;
    leftt = leftt == !!(b->left);
    bool rightt = a->right;
    rightt = rightt == !!(b->right);
    bool keys = a->key == b->key;
    bool result = leftt && rightt && keys;
    if(a->left && b->left){leftt = equal(a->left, b->left);}
    if(a->right && b->right){rightt = equal(a->right, b->right);}
    return (result && leftt && rightt);
  }
};

#endif
