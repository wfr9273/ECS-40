#ifndef LIST_H
#define LIST_H

template <typename T>
class List;

template <typename T>
class ListNode
{
	friend class List<T>;
  T data;
	ListNode<T> *next;
	ListNode<T> *prev;
	ListNode(T data, ListNode<T> *n, ListNode<T>* p);
	~ListNode();

}; // class ListNode

template <typename T>
class List
{
  ListNode<T> *head;
  ListNode<T> *curr;

  public:
  List();
  ~List();
  void insert(T data);
  bool find(T data);
  void print();
}; // class List

#include "list.cpp"
#endif // LIST_H
