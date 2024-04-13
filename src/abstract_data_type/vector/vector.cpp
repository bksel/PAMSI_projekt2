//
// Created by ksel on 05/03/24.
//

#ifndef MINIPROJEKT1_VECTOR_CPP
#define MINIPROJEKT1_VECTOR_CPP

// #include <cstdlib>
#include <fmt/core.h>
#include <stdexcept>

namespace adt {

template<typename T>
class vector
{

  u_int _capacity;
  u_int _elements_in_array;
  T* _elements;

public:
  vector();

  explicit vector(u_int N);
  explicit vector(T* A, u_int N);

  // initializer list constructor

  vector(std::initializer_list<T> list);

  ~vector();
  vector(const vector& other);
  vector& operator=(const vector& other);
  [[nodiscard]] bool empty() const;
  [[nodiscard]] u_int size() const;
  void reserve(u_int n);
  void erase(u_int n);
  void clear();
  T& operator[](u_int i);
  T& operator[](u_int i) const;
  T& at(u_int i);
  void push_back(const T& val);
  class Iterator
  {
    T* _data;

  public:
    explicit Iterator(T* data)
      : _data(data)
    {
    }
    Iterator& operator++()
    {
      _data++;
      return *this;
    }
    Iterator& operator--()
    {
      _data--;
      return *this;
    }
    T& operator*() { return *_data; }
    T* get_raw_pointer() { return _data; }
    u_int operator-(const Iterator& other)
    {
      if (_data < other._data) {
        throw std::runtime_error("negative memory address");
      }
      return _data - other._data;
    }
    Iterator operator+(u_int n) const { return Iterator(_data + n); }

    Iterator operator-(u_int n) const { return Iterator(_data - n); }

    // -> operator
    T* operator->() { return _data; }

    bool operator==(const Iterator& other) const
    {
      return _data == other._data;
    }

    bool operator!=(const Iterator& other) const
    {
      return _data != other._data;
    }
  };

  Iterator begin() { return Iterator(_elements); }
  Iterator begin() const { return Iterator(_elements); }

  Iterator end() { return Iterator(_elements + _elements_in_array); }
  Iterator end() const { return Iterator(_elements + _elements_in_array); }

  u_int get_iterator_index(Iterator it) { return it._data - _elements; }
};
template<typename T>
vector<T>::vector(std::initializer_list<T> list)
{
  _capacity = list.size() * 2;
  _elements_in_array = list.size();
  _elements = new T[_capacity];
  std::copy(list.begin(), list.end(), _elements);
}
template<typename T>
T&
vector<T>::operator[](u_int i) const
{
  return _elements[i];
}

template<typename T>
vector<T>&
vector<T>::operator=(const vector& other)
{
  if (this != &other) {
    delete[] _elements;

    _capacity = other._capacity;
    _elements_in_array = other._elements_in_array;
    _elements = new T[_capacity];
    std::copy(other._elements, other._elements + _elements_in_array, _elements);
  }
  return *this;
}

template<typename T>
vector<T>::vector(const vector& other)
  : _capacity(other._capacity)
  , _elements_in_array(other._elements_in_array)
{
  _elements = new T[_capacity];
  std::copy(other._elements, other._elements + _elements_in_array, _elements);
}

template<typename T>
void
vector<T>::clear()
{
  _elements_in_array = 0;
}

template<typename T>
vector<T>::vector(T* A, u_int N)
{
  _capacity = N;
  _elements_in_array = N;
  _elements = A;
}

template<typename T>
void
vector<T>::push_back(const T& val)
{
  if (_elements_in_array == _capacity) {
    reserve(_capacity * 2);
  }
  _elements[_elements_in_array++] = val;
}

template<typename T>
vector<T>::vector()
  : _capacity(0)
  , _elements_in_array(0)
  , _elements(NULL)
{
}

template<typename T>
vector<T>::vector(u_int N)
  : _capacity(N)
  , _elements_in_array(N)
  , _elements(new T[N])
{
}

template<typename T>
bool
vector<T>::empty() const
{
  return _elements_in_array == 0;
}

template<typename T>
u_int
vector<T>::size() const
{
  return _elements_in_array;
}

template<typename T>
void
vector<T>::reserve(u_int n)
{
  if (n > _capacity) {
    auto new_elements = new T[n];
    for (u_int i = 0; i < _elements_in_array; i++) {
      new_elements[i] = _elements[i];
    }
    delete[] _elements;
    _elements = new_elements;
    _capacity = n;
  }
}

template<typename T>
void
vector<T>::erase(u_int n)
{
  for (u_int i = n; i < _elements_in_array - 1; ++i) {
    _elements[i] = _elements[i + 1];
  }
  --_elements_in_array;
}

template<typename T>
T&
vector<T>::at(u_int i)
{
  if (i >= _elements_in_array) {
    throw std::out_of_range("Index out of range");
  }
  return _elements[i];
}

template<typename T>
T&
vector<T>::operator[](u_int i)
{
  return _elements[i];
}

template<typename T>
vector<T>::~vector()
{

  if (_elements == nullptr) {
    return;
  }

  delete[] _elements;
}

} // adt

#endif // MINIPROJEKT1_VECTOR_CPP
