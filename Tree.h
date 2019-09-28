#ifndef HTREE
#define HTREE
#include "./Node.h"
#include "./circularlist.h"
#include <iostream>
#include <sstream>
#include <cmath>

template<typename T, typename O>
O ttoo(T value)
{
  std::stringstream a(value);
  O result;
  a >> result;
  return result;
}

template <typename T>
class Tree {
private:
  int inictabs(int n, int m)
  {
    return pow(2, m-(n+1))-1;
  }
  int tabsm(int x, int y)
  {
    if(x == 0){return 0;}
    return pow(2, y-x);
  }
  void pslash(int x, int y, CircularList<std::string>* values)
  {
    if(x==y){return;}
    bool a = true;
    for(int i = 0; i < inictabs(x, y); i++){std::cout << "\t";}
    for(int i = 0; i < pow(2, x); i++)
    {
      std::cout << ((values->at(i) != " ")? ((a)? "/" : "\\") : " ");
      a = !a;
      for(int i = 0; i < tabsm(x, y); i++){std::cout << "\t";}
    }
    std::cout << std::endl;
  }
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
      temp = ancestor(value);
      if(temp->right == value){delete value; temp->right = nullptr;}
      if(temp->left == value){delete value; temp->left = nullptr;}
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
  bool isFull()
  {
    return root->isFull(1, height());
  }
  bool isComplete()
  {
    bool completeswitch = false;
    int altura = height();
    CircularList<std::string>* valores;
    for(int i = 0; i < altura; i++)
    {
      valores = root->get_level(i);
      if(i == altura-1)
      {
        for(int j = 0; j < pow(2, i); j++)
        {
          if(completeswitch)
          {
            if(valores->at(j) != " ")
            {
              return false;
            }
          }
          else
          {
            if(valores->at(j) == " ")
            {
              completeswitch = true;
            }
          }
        }
      }
      else
      {
        for(int j = 0; j < pow(2, i); j++)
        {
          if(valores->at(j) == " ")
          {
            return false;
          }
        }
      }
      delete valores;
    }
    return true;
  }
  bool isBST()
  {
    return root->isBSTnode();
  }
  Node<T>* ancestor(Node<T> *value)
  {
    if(root == value){return root;}
    else { return root->ancestor(value);}
  }
  void print()
  {
    int altura = this->height();
    CircularList<std::string>* temp;
    for(int i = 0; i < altura; i++)
    {
      temp = root->get_level(i);
      for(int j = 0; j < inictabs(i, altura); j++){std::cout << "\t";}
      for(int j = 0; j < pow(2, i); j++)
      {
        std::cout << temp->at(j);
        for(int e = 0; e < tabsm(i, altura); e++)
        {
          std::cout << "\t";
        }
      }
      std::cout << std::endl;
      pslash(i+1, altura, root->get_level(i+1));
    }
  }
  void print_caminos()
  {
    CircularList<Node<T>*> *list = new CircularList<Node<T>*>;
    Node<T> *temp = nullptr;
    root->get_leafs(list);
    for(int i = 0; i < list->get_size(); i++)
    {
      temp = list->at(i);
      std::cout << "Camino a " << temp->key << ": ";
      while(temp != root)
      {
        std::cout << temp->key << " - ";
        temp = root->ancestor(temp);
      }
      std::cout << temp->key;
      std::cout << std::endl;
    }
    delete list;
  }
  Node<T>* next(Node<T>* value)
  {
    CircularList<Node<T>*>* temp;
    Node<T> *result;
    int altura = height();
    bool encontrado = false;
    for(int i = 0; i < altura; i++)
    {
      temp = root->get_leveln(i);
      for(int j = 0; j < temp->get_size(); j++)
      {
        if(value == temp->at(j))
        {
          result = temp->at(j+1);
          encontrado = true;
          break;
        }
      }
      if(encontrado){break;}
    }
    delete temp;
    return result;
  }
  bool isBalanced()
  {
    CircularList<std::string>* temp;
    bool trigger1 = true;
    bool trigger2 = true;
    for(int i = 0; i < height(); i++)
    {
      temp = root->get_level(i);
      for(int j = 0; j < temp->get_size(); j++)
      {
        if(temp->at(j) == " ")
        {
          if(trigger1)
          {
            trigger1 = false;
            break;
          }
          else
          {
            trigger2 = false;
            break;
          }
        }
      }
      delete temp;
    }
    if(trigger1 || trigger2)
    {
      return true;
    }
    return false;
  }
  static bool equal(Tree<T> *a, Tree<T> *b)
  {
    return Node<T>::equal(a->root, b->root);
  }
  static Tree<T>* converttobst(Tree<T>* value)
  {
    Tree<T> *result = new Tree<T>;
    CircularList<std::string> *temp;
    for(int i = 0; i < value->height(); i++)
    {
      temp = value->root->get_level(i);
      for(int j = 0; j < temp->get_size(); j++)
      {
        result->inser(ttoo<std::string, T>(temp->at(j)));
      }
      delete temp;
    }
    return result;
  }
};

#endif
