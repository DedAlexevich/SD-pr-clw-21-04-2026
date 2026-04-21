#include <iostream>

template< class T >
struct BiTree {
  T val;
  BiTree< T >* left, * right, * parent;
};

template< class T >
struct BiTreeIt {
  BiTree< T >* curr;
};

template< class T>
BiTree< T >* minimum(BiTree< T >* root)
{
  if (!root) {
    return root;
  }
  while (root->lt) {
    root = root->lt;
  }
  return root;
}

template< class T>
BiTree< T >* maximum(BiTree< T >* root)
{
  if (!root) {
    return root;
  }
  while (root->rt) {
    root = root->rt;
  }
  return root;
}

template< class T, class F >
F traverse(BiTree< T >* root, F f)
{
  if (!root) {
    return f;
  }
  BiTree< T >* next = minimum(root);
  while (next) {
    f(next->val);
    if (next->rt) {
      next = next->rt;
      next = minimum(next);
    } else {
      BiTree<T> parent = next->parent;
      while (parent && parent->lt != next) {
        next = parent;
        parent = next->parent;
      }
      next = parent;
    }
  }
}

template< class T >
T& value(BiTreeIt<T> it)
{
  return it.curr->val;
}

template< class T >
BiTreeIt< T > next(BiTreeIt<T> it)
{
  BiTree< T >* next = it.curr;
  if (next->rt) {
    next = next->rt;
    next = minimum(next);
  } else {
    BiTree<T> parent = next->parent;
    while (parent && parent->lt != next) {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return {next};
}

template< class T >
BiTreeIt< T > prev(BiTreeIt<T> it)
{
  BiTree< T >* next = it.curr;
  if (next->lt) {
    next = next->lt;
    next = maximum(next);
  } else {
    BiTree<T> parent = next->parent;
    while (parent && parent->rt != next) {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return {next};
}

template< class T >
bool hasNext(BiTreeIt<T> it)
{
  return next(it).curr;
}

template< class T >
bool hasPrev(BiTreeIt<T> it)
{
  return prev(it).curr;
}





int main()
{

  return 0;
}
