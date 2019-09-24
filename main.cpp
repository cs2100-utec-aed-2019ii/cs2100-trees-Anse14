#include <iostream>
#include "./Tree.h"
using namespace std;

int main()
{
  Tree<int> *a = new Tree<int>;
  a->insert(5);
  a->insert(3);
  a->insert(4);
  a->insert(2);
  a->insert(7);
  a->inorder();
  a->preorder();
  a->postorder();
  delete a;
  return 0;
}
