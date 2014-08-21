// cust.h
// Loker, Nathaniel
// nloker
#ifndef PQUEUE_H 
#define PQUEUE_H 
#include<iostream>
#include<string>
#include"cust.h"
using namespace std;

class Pqueue{
  public:
    Pqueue();
    ~Pqueue();
    void enqueue(Cust *cust, int priority);
    bool empty();
    int size_of_queue();
    Cust* dequeue();
    void print(ostream &os);
    int get_priority();

  private:
      class Node
      {
        public:
          Node(Cust *cust, int priority, Node *node)
          {m_cust = cust; m_next = node; m_priority = priority;}
          Cust *m_cust;
          Node *m_next;
          int m_priority;
      };
      Node *m_head;
      int m_size;

};
#endif



