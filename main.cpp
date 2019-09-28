#include <iostream>
#include "./Tree.h"
using namespace std;

int main()
{
  Tree<int> *a = new Tree<int>;
  Tree<int> *b = new Tree<int>;
  a->insert(5);
  a->insert(3);
  a->insert(4);
  a->insert(2);
  a->insert(7);

  b->insert(5);
  b->insert(3);
  b->insert(4);
  b->insert(2);
  b->insert(7);
  cout << "Inorder: ";
  a->inorder();
  cout << "Preorder: ";
  a->preorder();
  cout << "Postorder: ";
  a->postorder();
  cout << "Altura: " << a->height() << endl;
  cout << "List: ";
  a->elements->for_each([](Node<int> *i)
  {
    cout << i->key << " ";
  });
  cout << endl;
  cout << "List: ";
  b->elements->for_each([](Node<int> *i)
  {
    cout << i->key << " ";
  });
  cout << endl;
  cout << "Igualdad: " << Tree<int>::equal(a, b) << endl;
  cout << "Is Bst: " << a->isBST() << endl;
  cout << "Padres de List: ";
  a->elements->for_each([a](Node<int> *i)
  {
    cout << a->ancestor(i)->key << " ";
  });
  cout << endl;
  b->deleten(b->root);
  cout << "ES COMPLETO?: " << a->isComplete() << endl;
  cout << "IS FULL?: " << a->isFull() << endl;
  cout << endl;
  a->print();
  a->print_caminos();
  cout << a->next(a->root->left)->key << endl;
  a->insert(1);
  cout << "a esta balanceado?: " << a->isBalanced() << endl;
  delete a;
  delete b;
  return 0;
}
