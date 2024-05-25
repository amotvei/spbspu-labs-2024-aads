#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>

namespace taskaev
{
  template < typename Key, typename Value, typename Comparator >
  class BSTree
  {
  public:
    class ConstIterator;
    class Node;
    {
    public:
      friend class BSTree;
      explicit Node(const Key key, const Value val):
        data_(std::pair< Key, Value >(key, val)),
        right_(nullptr),
        left_(nullptr),
        parent_(nullptr),
        height_(1)
      {}
      Node* right_;
      Node* left_;
      Node* parent_;
      size_t height_;
      std::pair< Key, Value > data_;
    };
    BSTree();
    BSTree(const BSTree& other) = default;
    BSTree(BSTree&& other) = default;
    ~BSTree();

    bool empty() const noexcept;
    void clear() noexcept;
    size_t size() const noexcept;
  private:
    Node* root_;
    Comparator comp_;
    size_t size_;
  };
}
using namespace taskaev;

template < typename Key, typename Value, typename Comparator>
class taskaev::BSTree< Key, Value, Comparator>::ConstIterator
{
  friend class BSTree;
public:
  ConstIterator();
  ConstIterator(Node* node, Node* root);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;

  ConstIterator& operator=(const ConstIterator&) = default;

  ConstIterator& operator++();
  ConstIterator operator++(int);
  ConstIterator& operator--();
  ConstIterator operator--(int);

  bool operator!=(const ConstIterator& rhs) const;
  bool operator==(const ConstIterator& rhs) const;

private:
  Node* node_;
  Node* root_;
};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::ConstIterator::ConstIterator() :
  node_(nullptr),
  root_(nullptr)
{};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::ConstIterator::ConstIterator(Node* node, Node* root) :
  node_(node),
  root_(root)
{}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator& BSTree< Key, Value, Comparator >::ConstIterator::operator++()
{
  assert(node_ != nullptr);
  if (node_->right_ != nullptr)
  {
    node_ = node_->right_;
    while (node_->left_ != nullptr)
    {
      node_ = node_->left_;
    }
  }
  else
  {
    Node* p = node_->parent_;
    while (node_->parent_ != nullptr && node_ == node_->parent_->right_)
    {
      node_ = node_->parent_;
    }
    node_ = node_->parent_;
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::ConstIterator::operator++(int)
{
  assert(node_ != nullptr);
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator& BSTree< Key, Value, Comparator >::ConstIterator::operator--()
{
  assert(node_ != nullptr);
  if (node_->left_ != nullptr)
  {
    node_ = node_->left_;
    while (node_->right_ != nullptr)
    {
      node_ = node_->right_;
    }
  }
  else
  {
    Node* tempNode = node_;
    node_ = node_->parent_;
    while (node_ && tempNode == node_->left_)
    {
      tempNode = node_;
      if (node_->parent_)
      {
        node_ = node_->parent_;
      }
      else
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::ConstIterator::operator--(int)
{
  assert(node_ != nullptr);
  ConstIterator result(*this);
  --(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::ConstIterator::operator!=(const ConstIterator& rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::ConstIterator::operator==(const ConstIterator& rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Comparator >
class BSTree< Key, Value, Comparator >::Iterator
{
public:
  friend class BSTree;
  Iterator();
  Iterator(ConstIterator someIterator);
  ~Iterator() = default;
  Iterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  Iterator operator++();
  Iterator operator++(int);

  Iterator operator--();
  Iterator operator--(int);

  bool operator!=(const Iterator& rhs) const;
  bool operator==(const Iterator& rhs) const;
private:
  ConstIterator iterator_;
};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::Iterator::Iterator() :
  iterator_(nullptr)
{};

template< typename Key, typename Value, typename Comparator >
BSTree< Key, Value, Comparator >::Iterator::Iterator(ConstIterator iter) :
  iterator_(iter)
{}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator++()
{
  assert(iterator_.node_ != nullptr);
  iterator_++;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator++(int)
{
  ++iterator_;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator--()
{
  iterator_--;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator--(int)
{
  --iterator_;
  return iterator_;
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Comparator >
bool BSTree< Key, Value, Comparator >::Iterator::operator==(const Iterator& rhs) const
{
  return iterator_ == rhs.iterator_;
}