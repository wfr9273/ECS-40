#include <iostream>
#include "directory.h"

using namespace std;

template <typename T>
ListNode<T>::ListNode(T dat, ListNode<T>* n, ListNode<T>* p)
                     : data(dat), next(n), prev(p)
{
}  // constructor ListNode

template <typename T>
ListNode<T>::~ListNode()
{
  if (data)
    delete data;
} // destructor ListNode

template <typename T>
List<T>::List()
{
  head = NULL;
  curr = NULL;
} // List Constructor

template <typename T>
List<T>::~List()
{
  curr = head;

  while (head)
  {
    head = curr->next;

    if(!curr) // if curr not NULL
      delete curr;
  } // while head not NULL
} // List Destructor

template <typename T>
void List<T>::insert(T data)
{
  if (!head)
  {
    head = new ListNode<T>(data, NULL, NULL);
    return;
  } // empty list

  if (!curr)  // curr = NULL
    curr = head;

  while(curr)
  {

    if (*curr->data == *data)
    {
      curr->data->insert(data);
      return;
    }  // if directory

    else if (*curr->data < *data) // if current data smaller than insert
    {
      if (curr->next){
        if (*curr->next->data < *data) // next node is not the place to insesrt
          curr = curr->next;
        else if (*curr->next->data > *data){
		      curr->next->prev = new ListNode<T>(data, curr->next, curr);
          curr->next = curr->next->prev;
          return;
        } // if next node is greater than to insert, insert here
        else{
          curr = curr->next;
          continue;
        } // next is directory
      } // if curr is not the last node
      else{
        curr->next = new ListNode<T>(data, NULL, curr);
        return;
      } // curr is the last node
    } // else if

    else
    {
      if (curr->prev){
        if (*curr->prev->data > *data) // curr->prev is not the position to insert
          curr = curr->prev;
        else if (*curr->prev->data < *data){
		      curr->prev->next = new ListNode<T>(data, curr, curr->prev);
          curr->prev = curr->prev->next;
          return;
        }  // curr is the next of the insert position
        else{
			    curr = curr->prev;
			    continue;
		    } // if prev is directory
      } // if not 1st node
      else{
		      head = new ListNode<T>(data, curr, NULL);
          curr->prev = head;
          return;
      } // 1st node
    } // if the current data is greater than the one to insert
  } // while curr not NULL
} //insert()

template <typename T>
bool List<T>::find(T data)
{
  if (!curr) // curr is NULL
    curr = head;

  while(curr)
  {
    if (*curr->data == *data) // find directory
      return curr->data->find(data);

    else if (*curr->data < *data){
	  if (curr->next){
	    if (*curr->next->data > *data)
		    return false;
	    else
          curr = curr->next;
      } // not last node
    else // last node
        return false;
      }

    else if (*curr->data > *data){
	  if (curr->prev){
	    if (*curr->prev->data < *data)
		  return false;
	    else
          curr = curr->prev;
      }
      else
        return false;}
    else
      break;
  }
  return false;
} // find()

template <typename T>
void List<T>::print()
{
  for (curr = head; curr; curr = curr->next)
    cout << curr->data->getName() << endl;
} // print()
