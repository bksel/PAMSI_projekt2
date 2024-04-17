//
// Created by ksel on 17/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_LIST_UNILATERALLIST_H_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_LIST_UNILATERALLIST_H_

#include <cstdlib>
#include <exception>
namespace adt {

namespace _uni_list {
template<typename T>
struct Node
{
  T data;
  Node* next = nullptr;
};
} // _uni_list

template<typename T>
class UnilateralList
{
  _uni_list::Node<T>* head = nullptr;
  u_int _size = 0;

public:
  class EmptyListException : public std::exception
  {
  public:
    [[nodiscard]] const char* what() const noexcept override
    {
      return "EmptyListException: The list is empty.";
    }
  };


  UnilateralList() = default;
  void push(const T& data);
  T pop();
  [[nodiscard]] u_int size() const { return _size; }
  [[nodiscard]] bool empty() const { return _size == 0; }
};



template<typename T>
T
UnilateralList<T>::pop()
{
  if (empty())
    throw EmptyListException();
  auto* node = head;
  head = head->next;
  T data = node->data;
  delete node;
  --_size;
  return data;
}

template<typename T>
void
UnilateralList<T>::push(const T& data)
{
  auto* new_node = new _uni_list::Node<T>{ data, head };
  head = new_node;
  ++_size;
}


} // adt

#endif // MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_LIST_UNILATERALLIST_H_
