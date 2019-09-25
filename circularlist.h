#ifndef CircularList_H
#define CircularList_H
#include <functional>

template<typename T>
struct ClistNode
{
  T value;
  ClistNode<T> *next;
  ClistNode():value(0), next(nullptr){}
};

template<typename T>
class CircularList
{
private:
  ClistNode<T> *head;
  unsigned int size;
public:
  CircularList():head(nullptr),size(0){}
  ~CircularList(){clear();}
  void push_back(T value)
  {
    size++;
    if(head)
    {
      ClistNode<T> *temp = head->next;
      while(temp->next != head)
      {
        temp = temp->next;
      }
      temp->next = nullptr;
      temp->next = new ClistNode<T>;
      temp->next->next = head;
      temp->next->value = value;
      return;
    }
    head = new ClistNode<T>;
    head->value = value;
    head->next = head;
  }
  void pop_back()
  {
    size--;
    if(head)
    {
      if(!(head->next)){delete head; return;}
      ClistNode<T> *temp = head->next;
      while(temp->next->next != head)
      {
        temp = temp->next;
      }
      delete temp->next;
      temp->next = head;
    }
  }
  T at(unsigned int position)
  {
    ClistNode<T> *temp = head;
    for(int i = 0; i < position; i++)
    {
      temp = temp->next;
    }
    return temp->value;
  }
  bool isEmpty()
  {
    return (size != 0)? false : true;
  }
  int get_size()
  {
    return size;
  }
  void clear()
  {
    while(!isEmpty())
    {
      pop_back();
    }
  }
  void for_each(std::function<void(T)> element)
  {
    if(!head){return;}
    ClistNode<T> *temp = head;
    do
    {
      element(temp->value);
      temp = temp->next;
    }
    while(temp != head);
  }
};

#endif
