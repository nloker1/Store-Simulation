#include"pqueue.h"
#include"cust.h"
Pqueue::Pqueue()
{
  m_head = NULL;
  m_size = 0;
}
Pqueue::~Pqueue()
{
  Node *ptr = m_head;
  while(ptr != NULL)
  {
    Node *tmp = m_head;
    m_head = m_head->m_next;
    delete tmp -> m_cust;
    delete tmp;
  }
}


void Pqueue::enqueue(Cust *cust, int priority)
{
  if(m_head == NULL || priority < m_head -> m_priority)
  {
    m_head = new Node(cust, priority, m_head);
    m_size++;
    return;
  }
  Node *ptr = m_head;
  while(ptr -> m_next != NULL && ptr -> m_next -> m_priority <= priority)
  {
    ptr = ptr -> m_next;
  }
  ptr -> m_next = new Node(cust, priority, ptr->m_next);
  m_size++;
  return;
}

bool Pqueue::empty()
{
  if(m_head == NULL)
    return true;
  else
    return false;
}
  

Cust* Pqueue::dequeue()
{ 
  if(m_head == NULL)
    return NULL;
  Node* tmp = m_head;
  Cust* first = m_head -> m_cust;
  m_head = m_head -> m_next;
  delete tmp;
  m_size--;
  return first;

}

int Pqueue::size_of_queue()
{
  return m_size;
}
int Pqueue::get_priority()
{
  int priority;
  if(m_head == NULL)
  {
    priority = -1;
    return priority;
  }
  priority = m_head->m_priority;
  return priority;
}
  



