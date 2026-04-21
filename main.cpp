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

enum class Direction {
  fall_left,
  parent
};

template< class T >
BiTree<T> nextAssigned(BiTree< T >* root)
{
  if (!root) {
    return nullptr;
  }
  BiTree< T >* next = minimum(root);
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
  return next;
}

template< class T >
std::pair< size_t, BiTree<T>* > fall_left(BiTree<T>* root)
{
  size_t path = 0;
  while (root->left) {
    root = root->left;
    path++;
  }
  return {path, root};
}

template< class T >
std::pair< size_t, BiTree<T>* > parent(BiTree<T>* root)
{
  if (!root) {
    return {0, nullptr};
  }
  size_t path = 0;
  BiTree<T> parent = root->parent;
  while (parent && parent->left != root) {
    root = parent;
    parent = root->parent;
    path++;
  }
  return {path, parent};
}

template< class T >
std::tuple< Direction, size_t, BiTree< T >* > nextStruct(BiTree<T>* root)
{
  if (root->rt) {
    auto res = fall_left(root->rt);
    return {Direction::fall_left, res.first, res.second};
  }
  auto res = parent(root);
  return {Direction::parent, res.first, res.second};
}

template< class T >
bool isEqualStruct(BiTree< T >* lhs, BiTree< T >* rhs)
{
  auto lhs_begin = fall_left(lhs);
  auto rhs_begin = fall_left(rhs);
  if (lhs_begin.first != rhs_begin.first) {
    return false;
  }
  auto ln = nextStruct(lhs_begin.second);
  auto rn = nextStruct(rhs_begin.second);
  while (std::get< 0 >(ln) == std::get< 0 >(rn) &&
        std::get< 1 >(ln) == std::get< 1 >(rn) &&
        std::get< 2 >(ln) && std::get< 2 >(rn)) {
    ln = nextStruct(std::get< 2 >(ln));
    rn = nextStruct(std::get< 2 >(rn));
  }
  return ln == rn;
}



int main()
{

  return 0;
}
