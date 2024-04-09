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
class vector {

  u_int _capacity;
  u_int _elements_in_array;
  T *_elements;

 public:
  vector();

  /*
   * Creates a vector of given size of elements, elements are not initialized,
   * they are just allocated
   *
   * */
  explicit vector(u_int N);

  explicit vector(T *A, u_int N);
  ~vector();

  // Copy constructor
  vector(const vector &other);

  // Copy assignment operator
  vector &operator=(const vector &other);

  /**
   * @brief Checks if the vector is empty.
   * 
   * @return true if the vector is empty, false otherwise.
   */
  [[nodiscard]] bool empty() const;

  /**
   * @brief Returns the number of elements in the vector.
   *
   * @return The number of elements in the vector.
   */
  [[nodiscard]] u_int size() const;

  /**
   * @brief Reserves memory for at least `n` elements in the vector.
   *
   * This function reserves memory to accommodate at least `n` elements in the vector.
   * If `n` is less than or equal to the current capacity, this function does nothing.
   * Otherwise, it allocates a new block of memory and copies the existing elements to the new block.
   * After calling this function, the vector's capacity will be equal to or greater than `n`.
   *
   * @param n The minimum number of elements to reserve memory for.
   */
  void reserve(u_int n);

  /**
   * @brief Removes the element at the specified index from the vector.
   *
   * This function removes the element at the specified index from the vector and shifts all subsequent elements to the left.
   * The size of the vector is reduced by 1.
   *
   * @param n The index of the element to be removed.
   */
  void erase(u_int n);

  /**
   * @brief Clears all elements from the vector.
   *
   * This function removes all elements from the vector, leaving it with a size of 0.
   * The capacity of the vector remains unchanged.
   */
  void clear();

  /**
   * @brief Accesses the element at the specified index.
   * 
   * This function allows accessing the element at the specified index in the vector.
   * The index must be within the valid range of the vector, correctness of indez is not checked.
   * 
   * @param i The index of the element to access.
   * @return A reference to the element at the specified index.
   */

  T &operator[](u_int i);

  T &operator[](u_int i) const;


  /**
   * Returns a reference to the element at the specified index.
   *
   * @param i The index of the element to access.
   * @return A reference to the element at the specified index.
   * @throws std::out_of_range if the index is out of range.
   */


  T &at(u_int i);

  /**
   * @brief Adds an element to the end of the vector.
   *
   * This function appends the given value `val` to the end of the vector.
   *
   * @param val The value to be added to the vector.
   */
  void push_back(const T &val);

  /**
   * @class Iterator
   * @brief Represents an iterator for the Vector class.
   * 
   * The Iterator class provides functionality to iterate over the elements of a Vector.
   */
  class Iterator {
	T *_data;

   public:
	/**
	 * @brief Constructs an Iterator object.
	 *
	 * @param data A pointer to the data element.
	 */
	explicit Iterator(T *data)
		: _data(data) {
	}

	/**
	 * @brief Increments the iterator to the next element.
	 *
	 * @return A reference to the updated iterator.
	 */
	Iterator &operator++() {
	  _data++;
	  return *this;
	}

	/**
	 * @brief Decrements the iterator to the previous element.
	 *
	 * @return A reference to the updated iterator.
	 */
	Iterator &operator--() {
	  _data--;
	  return *this;
	}

	/**
	 * @brief Dereferences the iterator to access the element it points to.
	 *
	 * @return A reference to the element.
	 */
	T &operator*() { return *_data; }

	// return the address of the element
	T *get_raw_pointer() { return _data; }

	// Iterators subtraction
	u_int operator-(const Iterator &other) {
	  if (_data<other._data) {
		throw std::runtime_error("negative memory address");
	  }
	  return _data - other._data;
	}

	// Iterators addition
	Iterator operator+(u_int n) const {
	  return Iterator(_data + n);
	}



	/**
	 * @brief Compares two iterators for equality.
	 *
	 * @param other The iterator to compare with.
	 * @return True if the iterators are equal, false otherwise.
	 */
	bool operator==(const Iterator &other) const {
	  return _data==other._data;
	}

	/**
	 * @brief Compares two iterators for inequality.
	 *
	 * @param other The iterator to compare with.
	 * @return True if the iterators are not equal, false otherwise.
	 */
	bool operator!=(const Iterator &other) const {
	  return _data!=other._data;
	}
  };

  Iterator begin() { return Iterator(_elements); }
  const Iterator begin() const { return Iterator(_elements); }

  Iterator end() { return Iterator(_elements + _elements_in_array); }
  const Iterator end() const { return Iterator(_elements + _elements_in_array); }

  u_int get_iterator_index(Iterator it) { return it._data - _elements; }
};
template<typename T>
T &vector<T>::operator[](u_int i) const {
  return _elements[i];
}

template<typename T>
vector<T> &
vector<T>::operator=(const vector &other) {
  if (this!=&other) {
	delete[] _elements;

	_capacity = other._capacity;
	_elements_in_array = other._elements_in_array;
	_elements = new T[_capacity];
	std::copy(other._elements, other._elements + _elements_in_array, _elements);
  }
  return *this;
}

template<typename T>
vector<T>::vector(const vector &other)
	: _capacity(other._capacity), _elements_in_array(other._elements_in_array) {
  _elements = new T[_capacity];
  std::copy(other._elements, other._elements + _elements_in_array, _elements);
}

template<typename T>
void
vector<T>::clear() {
  _elements_in_array = 0;
}

template<typename T>
vector<T>::vector(T *A, u_int N) {
  _capacity = N;
  _elements_in_array = N;
  _elements = A;
}

template<typename T>
void
vector<T>::push_back(const T &val) {
  if (_elements_in_array==_capacity) {
	reserve(_capacity*2);
  }
  _elements[_elements_in_array++] = val;
}

template<typename T>
vector<T>::vector()
	: _capacity(0), _elements_in_array(0), _elements(NULL) {
}

template<typename T>
vector<T>::vector(u_int N)
	: _capacity(N), _elements_in_array(N), _elements(new T[N]) {
}

template<typename T>
bool
vector<T>::empty() const {
  return _elements_in_array==0;
}

template<typename T>
u_int
vector<T>::size() const {
  return _elements_in_array;
}

template<typename T>
void
vector<T>::reserve(u_int n) {
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
vector<T>::erase(u_int n) {
  for (u_int i = n; i < _elements_in_array - 1; ++i) {
	_elements[i] = _elements[i + 1];
  }
  --_elements_in_array;
}

template<typename T>
T &
vector<T>::at(u_int i) {
  if (i >= _elements_in_array) {
	throw std::out_of_range("Index out of range");
  }
  return _elements[i];
}

template<typename T>
T &
vector<T>::operator[](u_int i) {
  return _elements[i];
}

template<typename T>
vector<T>::~vector() {

  if (_elements==nullptr) {
	return;
  }


  delete[] _elements;
}

} // adt

#endif // MINIPROJEKT1_VECTOR_CPP
