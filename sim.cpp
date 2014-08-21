// sim.cpp
// Loker, Nathaniel
// nloker
#include"pqueue.h"
#include"cust.h"
#include<fstream>
#include<stdlib.h>

struct Checker
{
  int cash_in_reg, break_duration, done_checking, break_done;
  bool available;
  Cust* cust_pointer;

};

void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_duration, ostream &os);

bool leg_int(char *str)
{
  int count=0;
  while(str[count] != 0)
  {
    if(isdigit(str[count]) == false)
      return false;
    count++;
  }
    return true;
}

int main(int argc, char* argv[])
{
  int num_checkers, break_duration;
  if(argc != 5)
  {
    cerr << "Error: invalid number of command line arguments." << endl;
    return 1;
  }

  ifstream is(argv[3], ios::in);

  if(!is)
  {
    cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
    return 1;
  }

  ofstream os(argv[4], ios::out);

  if(!os)
  {
    cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
    return 1;
  }
  
  if(!leg_int(argv[1]))
  {
    cerr << "Error: invalid number of checkers specified." << endl;
    return 1;
  }

  num_checkers = atoi(argv[1]);
  if(num_checkers < 0)
  {
    cerr << "invalid number of checkers specified." << endl;
    return 1;
  }
  
  if(!leg_int(argv[2]))
  {
    cerr << "Error: invalid checker break duration specified." << endl;
    return 1;
  }
  break_duration = atoi(argv[2]);
  if(break_duration < 0)
  {
    cerr << "Error: invalid checker break duration specified." << endl;
    return 1;
  }

  Pqueue arrival_q;
  string name, shopper;
  int arrival, num_items;
  bool type; 
  while(is >> name)
  {
    is >> shopper >> arrival >> num_items;
    if(shopper == "shopper")
      type = true;
    else 
      type = false;
    
      
    arrival_q.enqueue(new Cust(name, arrival, num_items, type), arrival);
  }

  run_simulation(arrival_q, num_checkers, break_duration, os);

   return 0;
}



void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_duration, ostream &os)
{
  int holder,i,clock=0,num_customers;
  Checker* checkers = new Checker[num_checkers];
  holder = num_checkers; 
  num_customers = arrival_queue.size_of_queue();
  while(holder > 0)
  {
    for(i=0; i < num_checkers; i++)
    {
    checkers[i].cash_in_reg = 500;
    checkers[i].break_duration = break_duration;
    checkers[i].break_done = 0;
    checkers[i].available = true;
    checkers[i].done_checking = 0;
    checkers[i].cust_pointer = NULL;
    }
    holder--;
  }

  Cust* cust=NULL;
  int num_items, done_shopping; 
  Pqueue shopping_q;
  Pqueue checkout_q;
  for(clock = 0; 0 < num_customers; clock++)
  {
    
    while(clock == arrival_queue.get_priority())
    {
      cust = arrival_queue.dequeue();
      cust -> print_entered(os, clock);

      num_items = cust -> num_items();
      done_shopping = (cust -> arrival_time()) + (num_items*3);
      shopping_q.enqueue(cust, done_shopping);
      
    }

    while(clock == shopping_q.get_priority())
    {
      cust = shopping_q.dequeue();
      cust -> print_done_shopping(os,clock);
      checkout_q.enqueue(cust, 0);
    }

    for(i=0; i<num_checkers; i++)
    {
      if(clock == checkers[i].done_checking)
      {
        if(checkers[i].cust_pointer != NULL && (checkers[i].cust_pointer -> get_m_type()))
        {
         // os << "where is homer " << endl;
          checkers[i].cash_in_reg += (checkers[i].cust_pointer->num_items()*5); 
          checkers[i].cust_pointer -> print_checkout_shopper(os, clock, i);
          delete checkers[i].cust_pointer;
          checkers[i].cust_pointer = NULL;
          num_customers--;
          checkers[i].available = true;
        }

        else if(checkers[i].cust_pointer != NULL && (!checkers[i].cust_pointer -> get_m_type()))
        {
          //os << "weee" << endl;
          checkers[i].cust_pointer -> print_checkout_robber(os, clock, i, checkers[i].cash_in_reg);


          checkers[i].cash_in_reg = 0;
          delete checkers[i].cust_pointer;
          checkers[i].cust_pointer = NULL;
          num_customers --;
          checkers[i].available = false;
          checkers[i].break_done = clock + checkers[i].break_duration;
        }
      }
      if (checkers[i].break_done == clock)
        checkers[i].available = true;
    }

 
   
    for(i=0; i<num_checkers; i++)
    {
       while(!checkout_q.empty() && checkers[i].available)
       {  
         checkers[i].break_done = 0;
         checkers[i].cust_pointer = checkout_q.dequeue();
         checkers[i].available = false;
         if(checkers[i].cust_pointer -> get_m_type())
         {
           checkers[i].done_checking = (clock + (checkers[i].cust_pointer -> num_items()) * 2);
          // os << "Debugging what is done_checking time? " << endl;
           //os << checkers[i].done_checking << endl;
         }
         else if(!(checkers[i].cust_pointer -> get_m_type()))
         {
           checkers[i].available = false;
           checkers[i].done_checking = clock + 7; 
         }
         checkers[i].cust_pointer -> print_started_checkout(os, clock, i);
       }
    }
   }
  for(i=0; i<num_checkers; i++)
  {
    os << "registers[" << i << "] = $" << checkers[i].cash_in_reg << endl;
  }
  os << "time = " << clock << endl;

}
