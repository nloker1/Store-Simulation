#include"cust.h"
#include<assert.h>


Cust::Cust(string name, int arrival, int items, bool type): m_name(name), m_arrival(arrival), m_items(items), m_type(type)
{
}

void Cust::print(ostream &os)
{
  string type;
  if(!m_type)
    type = "robber";
  else
    type = "shopper";

  os << m_name << " " << type << " " <<  m_arrival << " " << m_items  << endl;
}

void Cust::print_entered(ostream &os, int clock)
{
  assert(clock == m_arrival);
  os << clock << ": " << m_name << " entered store" << endl;
}

void Cust::print_done_shopping(ostream &os, int clock)
{
  os << clock << ": " << m_name << " done shopping" << endl;
}

void Cust::print_started_checkout(ostream &os, int clock, int i)
{
  os << clock << ": " << m_name << " started checkout with checker " << i << endl;
}

void Cust::print_checkout_shopper(ostream &os, int clock, int i)
{ 
  string plural;
  if(m_items == 1)
    plural = "item";
  else
    plural = "items";

  os << clock << ": " << m_name << " paid $" << m_items * 5 << " for " << m_items <<  " " << plural << " to checker " << i << endl;
}

void Cust::print_checkout_robber(ostream &os, int clock, int i, int cash_in_reg)
{
  string plural;
  if(m_items == 1)
    plural = "item";
  else
    plural = "items";

  os << clock << ": " << m_name << " stole $" << cash_in_reg << " and " << m_items << " " << plural << " from checker " << i << endl;
}

int Cust::arrival_time()
{
  return m_arrival;
}

int Cust::num_items()
{
  return m_items;
}

bool Cust::get_m_type()
{
  return m_type;
}



