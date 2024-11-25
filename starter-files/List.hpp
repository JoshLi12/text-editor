#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert

using namespace std;


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    if (first == nullptr && last == nullptr && _size == 0) {
      return true;
    }
    return false;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const {
    return _size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node* p = new Node;
    p->datum = datum;

    if (empty()) {
      first = p;
      last = p;
    } else {
      p->next = first;
      first->prev = p;
      first = p;
    }

    ++_size;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *p = new Node;
    p->datum = datum;

    if (last == nullptr) {
      first = p;
      last = p;
    } else {
      p->prev = last;
      last->next = p;
      last = p;
    }
    last->next = nullptr;

    ++_size;

  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node* to_delete = first;
    if (size() == 1) {
      first = nullptr;
      last = nullptr;
    }
    else {
      first = first->next;
      first->prev = nullptr;
    }
    delete to_delete;
    --_size;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node* to_delete = last;
    if (size() == 1) {
      first = nullptr;
      last = nullptr;
    }
    else {
      last = last->prev;
      last->next = nullptr;
    }
    
    delete to_delete;
    --_size;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) {
      pop_front();
    }

    first = nullptr;
    last = nullptr;
    _size = 0;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  //constructor
  List() : first(nullptr), last(nullptr), _size(0) {}

  // destructor
  ~List() {
    clear();
  }

  // copy constructor
  List(const List<T>& other) : first(nullptr), last(nullptr), _size(0) {
    copy_all(other);
  }

  // assignment operator
  List & operator=(const List &rhs) {
    if (this == &rhs) {return * this;}
    clear();
    copy_all(rhs);
    return *this;
  }



private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    Node* current = other.first;

    while (current) {
      push_back(current->datum);
      current = current->next;
    }

  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  size_t _size;

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}

    Iterator(const Iterator &other) : list_ptr(other.list_ptr), 
    node_ptr(other.node_ptr) {}

    Iterator &operator=(const Iterator &other) {
      list_ptr = other.list_ptr;
      node_ptr = other.node_ptr;
      return *this;
    }


    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able tso copy, assign, and destroy Iterators.




    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // Deference operator
    T &operator*() const {
      assert(node_ptr != nullptr);
      return node_ptr->datum;

    }

    // prefix implement ++
    Iterator &operator++() {
      assert(node_ptr);

      node_ptr = node_ptr->next;
      return *this;
    }

    // postfix implement ++
    Iterator operator++(int) {
      Iterator copy = *this;
      operator++();
      return copy;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    bool operator==(const Iterator &other) const {
      return list_ptr == other.list_ptr && node_ptr == other.node_ptr;
    }

    bool operator!=(const Iterator &other) const {
      return !(list_ptr == other.list_ptr && node_ptr == other.node_ptr);
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      cout << &operator*();
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(this, nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i) {
    Node* to_delete = i.node_ptr;

    if (this->size() == 1) {
      first = nullptr;
      last = nullptr;
    }
    else if (to_delete == first) {
      first = to_delete->next;
      first->prev = nullptr;
    }
    else if (to_delete == last) {
      last = to_delete->prev;
      last->next = nullptr;
    }
    else {
      to_delete->prev->next = to_delete->next;
    }

    Iterator output(this, to_delete->next);
    delete to_delete;
    --_size;

    return output;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum) {
    Node* p = new Node;
    p->datum = datum;

    Node* current = i.node_ptr;

    if (empty()) {
      first = p;
      last = p;
    }
    else if (current == first) {
      first->prev = p;
      p->next = first;
      first = p;
    }
    else if (current == nullptr) {
      last->next = p;
      p->prev = last;
      last = p;
    }
    else {
      p->prev = current->prev;
      p->next = current;
      current->prev->next = p;
      current->prev = p;
      
      
    }
    ++_size;
    return Iterator(this, p);
  }

};

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
